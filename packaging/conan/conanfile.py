# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Aspose Pty Ltd
#
# DRAFT. Not submittable: source() points at a tag that does not exist yet.
# See ../README.md.

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get

import os

required_conan_version = ">=2.0"


class AsposeSlidesFossConan(ConanFile):
    name = "aspose-slides-foss"
    description = (
        "C++ library for creating, reading and editing PowerPoint .pptx "
        "presentations."
    )
    license = "MIT"
    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp"
    topics = ("pptx", "powerpoint", "presentation", "ooxml", "office")

    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    # No shared option on purpose: nothing in the sources is annotated for
    # symbol export, so a shared build would produce a library that exports
    # nothing. The project's CMakeLists.txt forces a static archive.

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        # pugixml is transitive_headers because this library's own installed
        # headers include <pugixml.hpp>: a consumer compiles against it, not
        # merely links against it.
        self.requires("pugixml/1.14", transitive_headers=True, transitive_libs=True)
        self.requires("miniz/3.0.2")

    def validate(self):
        check_min_cppstd(self, 20)

    def source(self):
        get(self, **self.conan_data["sources"][self.version], strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        # Conan resolves the dependencies; the build must not fetch its own.
        tc.cache_variables["ASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES"] = False
        tc.cache_variables["ASPOSE_SLIDES_FOSS_BUILD_TESTS"] = False
        tc.cache_variables["BUILD_TESTING"] = False
        tc.generate()
        CMakeDeps(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE",
             src=self.source_folder,
             dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "THIRD_PARTY_NOTICES",
             src=self.source_folder,
             dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["aspose_slides_foss"]
        # The names a consumer's find_package() and target_link_libraries()
        # must see. They have to match what the project's own installed
        # CMake package exports, or a Conan build and a plain CMake build
        # would need different consumer code.
        self.cpp_info.set_property("cmake_file_name", "AsposeSlidesFoss")
        self.cpp_info.set_property("cmake_target_name",
                                   "AsposeSlidesFoss::AsposeSlidesFoss")
        self.cpp_info.requires = ["pugixml::pugixml", "miniz::miniz"]
