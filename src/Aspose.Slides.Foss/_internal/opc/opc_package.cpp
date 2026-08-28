// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

/// @file opc_package.cpp
/// @brief Implementation of InMemoryOpcPackage ZIP I/O methods.

#include "Aspose/Slides/Foss/_internal/opc/opc_package.h"

#include <miniz.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Aspose::Slides::Foss::Internal::opc {

namespace {

/// Load all parts from a miniz ZIP reader into the parts map.
void load_from_zip_reader(mz_zip_archive& zip,
                          std::unordered_map<std::string, std::vector<uint8_t>>& parts) {
    auto num_files = mz_zip_reader_get_num_files(&zip);
    for (mz_uint i = 0; i < num_files; ++i) {
        mz_zip_archive_file_stat stat;
        if (!mz_zip_reader_file_stat(&zip, i, &stat)) {
            mz_zip_reader_end(&zip);
            throw std::runtime_error("Failed to read ZIP entry info");
        }

        // Skip directories.
        if (mz_zip_reader_is_file_a_directory(&zip, i)) {
            continue;
        }

        std::string name(stat.m_filename);
        std::vector<uint8_t> data(static_cast<size_t>(stat.m_uncomp_size));

        if (!data.empty()) {
            if (!mz_zip_reader_extract_to_mem(&zip, i, data.data(), data.size(), 0)) {
                mz_zip_reader_end(&zip);
                throw std::runtime_error("Failed to extract ZIP entry: " + name);
            }
        }

        parts[std::move(name)] = std::move(data);
    }
}

/// Write all parts into a miniz ZIP writer, then finalize.
void save_to_zip_writer(mz_zip_archive& zip,
                        const std::unordered_map<std::string, std::vector<uint8_t>>& parts) {
    for (const auto& [name, content] : parts) {
        // MZ_DEFAULT_COMPRESSION is -1 and the parameter is unsigned. miniz
        // reads the argument back as a signed int and treats a negative value
        // as "use the default level", so the wrap-around is the documented way
        // to ask for it; the cast says so rather than leaving a signed-to-
        // unsigned conversion for a reader to wonder about.
        if (!mz_zip_writer_add_mem(&zip, name.c_str(), content.data(),
                                   content.size(),
                                   static_cast<mz_uint>(MZ_DEFAULT_COMPRESSION))) {
            mz_zip_writer_end(&zip);
            throw std::runtime_error("Failed to write ZIP entry: " + name);
        }
    }

    if (!mz_zip_writer_finalize_archive(&zip)) {
        mz_zip_writer_end(&zip);
        throw std::runtime_error("Failed to finalize ZIP archive");
    }
}

} // namespace

InMemoryOpcPackage InMemoryOpcPackage::open(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Package file not found: " + path.string());
    }

    mz_zip_archive zip{};
    if (!mz_zip_reader_init_file(&zip, path.string().c_str(), 0)) {
        throw std::runtime_error("Not a valid ZIP archive: " + path.string());
    }

    InMemoryOpcPackage package;
    package.source_path_ = path.string();
    try {
        load_from_zip_reader(zip, package.parts_);
    } catch (...) {
        mz_zip_reader_end(&zip);
        throw;
    }
    mz_zip_reader_end(&zip);

    return package;
}

InMemoryOpcPackage InMemoryOpcPackage::open(std::istream& stream) {
    // Read entire stream into memory for miniz.
    std::ostringstream oss;
    oss << stream.rdbuf();
    std::string buf = oss.str();

    mz_zip_archive zip{};
    if (!mz_zip_reader_init_mem(&zip, buf.data(), buf.size(), 0)) {
        throw std::runtime_error("Not a valid ZIP archive in stream");
    }

    InMemoryOpcPackage package;
    try {
        load_from_zip_reader(zip, package.parts_);
    } catch (...) {
        mz_zip_reader_end(&zip);
        throw;
    }
    mz_zip_reader_end(&zip);

    return package;
}

InMemoryOpcPackage InMemoryOpcPackage::create_new() {
    return InMemoryOpcPackage{};
}

void InMemoryOpcPackage::save(const std::filesystem::path& path) const {
    mz_zip_archive zip{};
    if (!mz_zip_writer_init_file(&zip, path.string().c_str(), 0)) {
        throw std::runtime_error("Failed to create ZIP file: " + path.string());
    }

    try {
        save_to_zip_writer(zip, parts_);
    } catch (...) {
        mz_zip_writer_end(&zip);
        throw;
    }
    mz_zip_writer_end(&zip);
}

void InMemoryOpcPackage::save(std::ostream& stream) const {
    // Write to an in-memory buffer, then copy to stream.
    mz_zip_archive zip{};
    if (!mz_zip_writer_init_heap(&zip, 0, 0)) {
        throw std::runtime_error("Failed to initialize ZIP writer");
    }

    try {
        save_to_zip_writer(zip, parts_);
    } catch (...) {
        mz_zip_writer_end(&zip);
        throw;
    }

    void* buf = nullptr;
    size_t buf_size = 0;
    if (!mz_zip_writer_finalize_heap_archive(&zip, &buf, &buf_size)) {
        mz_zip_writer_end(&zip);
        throw std::runtime_error("Failed to finalize ZIP archive to memory");
    }

    stream.write(static_cast<const char*>(buf), static_cast<std::streamsize>(buf_size));
    std::free(buf);
    mz_zip_writer_end(&zip);
}

void InMemoryOpcPackage::set_part(std::string_view part_name, std::string_view content) {
    std::vector<uint8_t> bytes(content.begin(), content.end());
    parts_[std::string(part_name)] = std::move(bytes);
}

std::vector<std::string> InMemoryOpcPackage::get_part_names() const {
    std::vector<std::string> names;
    names.reserve(parts_.size());
    for (const auto& [name, _] : parts_) {
        names.push_back(name);
    }
    return names;
}

std::optional<std::string> InMemoryOpcPackage::source_path() const {
    return source_path_;
}

void InMemoryOpcPackage::close() {
    parts_.clear();
    source_path_.reset();
}

} // namespace Aspose::Slides::Foss::Internal::opc
