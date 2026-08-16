# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Aspose Pty Ltd

cmake_minimum_required(VERSION 3.20)

project(AsposeSlidesFoss
        VERSION 0.1.0
        DESCRIPTION "MIT-licensed C++ library for reading, creating and writing PowerPoint .pptx presentations"
        HOMEPAGE_URL "https://github.com/aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp"
        LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(FetchContent)
include(GNUInstallDirs)

# ---------------------------------------------------------------------------
# Options
#
# Tests and install rules default to on only when this is the project being
# built, and off when it has been pulled into someone else's build: a consumer
# who adds this directory wants the library, not another test suite in their
# ctest run and not another set of files in their install prefix.
#
# Spelled out rather than using PROJECT_IS_TOP_LEVEL, which is CMake 3.21 and
# would raise the minimum this project asks for above the 3.20 it documents.
# ---------------------------------------------------------------------------

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(ASPOSE_SLIDES_FOSS_TOP_LEVEL ON)
else()
    set(ASPOSE_SLIDES_FOSS_TOP_LEVEL OFF)
endif()

option(ASPOSE_SLIDES_FOSS_BUILD_TESTS
       "Build the test suite. Downloads GoogleTest when no installed copy is found."
       ${ASPOSE_SLIDES_FOSS_TOP_LEVEL})
option(ASPOSE_SLIDES_FOSS_INSTALL
       "Generate the install and export rules for this project"
       ${ASPOSE_SLIDES_FOSS_TOP_LEVEL})
option(ASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES
       "Fetch pugixml and miniz with FetchContent when no installed copy is found"
       ON)
option(ASPOSE_SLIDES_FOSS_WARNINGS_AS_ERRORS
       "Treat compiler warnings in this project's own sources as errors"
       OFF)

# BUILD_TESTING is the name CTest gives this switch and the one CI and package
# managers set. Honour it, so -DBUILD_TESTING=OFF is enough to get a build that
# never reaches for a test framework.
if(DEFINED BUILD_TESTING AND NOT BUILD_TESTING)
    set(ASPOSE_SLIDES_FOSS_BUILD_TESTS OFF)
endif()

# AddressSanitizer.
#
# Memory-lifetime faults are not reliably visible in an ordinary build: reading
# through a pointer to a freed object usually returns whatever the allocator
# left behind, so the same defect crashes on one machine and silently returns
# plausible numbers on another. ASan turns that into a deterministic, located
# failure, which is the difference between a bug report and a rumour. Off by
# default because it costs roughly 2x run time; CI runs the suite with it on.
#
#   cmake -S . -B build-asan -DASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS=ON
#   cmake --build build-asan
option(ASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS
       "Build the library and tests with AddressSanitizer" OFF)
if(ASPOSE_SLIDES_FOSS_SANITIZE_ADDRESS)
    if(MSVC)
        add_compile_options(/fsanitize=address /Zi)
        # ASan and incremental linking are mutually exclusive.
        add_link_options(/INCREMENTAL:NO)
    else()
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
        add_link_options(-fsanitize=address)
    endif()
endif()

if(MSVC)
    # /FS  serialises writes to the shared PDB across parallel compiles.
    # /EHsc is MSVC's standard C++ exception model; without it the library's
    #       throw sites produce C4530 and unwinding is not guaranteed.
    # /MP   compiles the translation units of one target in parallel; the
    #       Visual Studio generator otherwise builds them one at a time.
    add_compile_options(/FS /EHsc /MP)
endif()

# ---------------------------------------------------------------------------
# Dependencies
#
# Each is looked for as an installed package first, so a distribution build
# (vcpkg, Conan, a Linux distro) uses the copy its package manager already
# resolved and audited. FetchContent is the fallback for a developer who just
# cloned the repository, and it pins an exact tag rather than a branch.
# ---------------------------------------------------------------------------

set(ASPOSE_SLIDES_FOSS_PUGIXML_VERSION    "1.14")
set(ASPOSE_SLIDES_FOSS_PUGIXML_TAG        "v1.14")
set(ASPOSE_SLIDES_FOSS_MINIZ_VERSION      "3.0.2")
set(ASPOSE_SLIDES_FOSS_MINIZ_TAG          "3.0.2")
set(ASPOSE_SLIDES_FOSS_GOOGLETEST_VERSION "1.15.2")
set(ASPOSE_SLIDES_FOSS_GOOGLETEST_TAG     "v1.15.2")

# miniz 3.0.2 and pugixml 1.14 declare a cmake_minimum_required below 3.5,
# which CMake 4 refuses outright. This asks CMake to treat a project that does
# so as if it had requested 3.5 policies. It is set here, after this project's
# own project() call, so it reaches the dependencies added below and not this
# project, which is configured under the policies it asks for itself. On CMake
# 3.x the variable does not exist and is ignored.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

find_package(pugixml ${ASPOSE_SLIDES_FOSS_PUGIXML_VERSION} CONFIG QUIET)
if(pugixml_FOUND)
    message(STATUS "pugixml: using installed package ${pugixml_VERSION}")
elseif(ASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES)
    FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        GIT_TAG ${ASPOSE_SLIDES_FOSS_PUGIXML_TAG}
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(pugixml)
    message(STATUS "pugixml: fetched ${ASPOSE_SLIDES_FOSS_PUGIXML_TAG}")
else()
    message(FATAL_ERROR
            "pugixml was not found and ASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES is OFF")
endif()

find_package(miniz ${ASPOSE_SLIDES_FOSS_MINIZ_VERSION} CONFIG QUIET)
if(miniz_FOUND)
    set(ASPOSE_SLIDES_FOSS_MINIZ_TARGET miniz::miniz)
    message(STATUS "miniz: using installed package ${miniz_VERSION}")
elseif(ASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES)
    # miniz's own name for its target, which is what the build tree offers;
    # the exported package renames it to miniz::miniz.
    set(ASPOSE_SLIDES_FOSS_MINIZ_TARGET miniz)
    # miniz generates install rules only when it is the top-level project.
    # Turn that on: when miniz is fetched rather than found, this build is the
    # only thing that can put it in the install prefix, and an installed
    # AsposeSlidesFoss whose consumer cannot resolve miniz does not link.
    # Both names belong to miniz and are set only on the path that adds it.
    set(INSTALL_PROJECT ON CACHE BOOL "" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        miniz
        GIT_REPOSITORY https://github.com/richgel999/miniz.git
        GIT_TAG ${ASPOSE_SLIDES_FOSS_MINIZ_TAG}
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(miniz)
    message(STATUS "miniz: fetched ${ASPOSE_SLIDES_FOSS_MINIZ_TAG}")
else()
    message(FATAL_ERROR
            "miniz was not found and ASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES is OFF")
endif()

# ---------------------------------------------------------------------------
# Version header
# ---------------------------------------------------------------------------

set(ASPOSE_SLIDES_FOSS_GENERATED_INCLUDE_DIR
    "${PROJECT_BINARY_DIR}/generated/include")
configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/version.h.in"
    "${ASPOSE_SLIDES_FOSS_GENERATED_INCLUDE_DIR}/Aspose/Slides/Foss/version.h"
    @ONLY)

# ---------------------------------------------------------------------------
# Library
#
# The sources are listed rather than globbed. A glob is evaluated once, at
# configure time: adding or deleting a file leaves the build system describing
# a source tree that no longer exists, and CMake has no way to know it should
# re-run. The failure is a link error or, worse, a stale object silently kept
# in the archive.
#
# Headers are deliberately not listed. They are not inputs to the compiler
# driver -- the dependency scanner finds them -- and listing them buys nothing
# but a folder in an IDE at the cost of a second list to keep in step with the
# first. What is installed is decided by install(DIRECTORY include/), below.
# ---------------------------------------------------------------------------

set(ASPOSE_SLIDES_FOSS_SOURCES
    src/Aspose.Slides.Foss/_internal/export/exporter_base.cpp
    src/Aspose.Slides.Foss/_internal/export/exporter_registry.cpp
    src/Aspose.Slides.Foss/_internal/export/pptx_exporter.cpp
    src/Aspose.Slides.Foss/_internal/opc/opc_package.cpp
    src/Aspose.Slides.Foss/_internal/opc/part_utils.cpp
    src/Aspose.Slides.Foss/_internal/pptx/app_properties_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/bulk_text_format.cpp
    src/Aspose.Slides.Foss/_internal/pptx/comment_authors_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/comments_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/core_properties_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/custom_properties_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/effect_color.cpp
    src/Aspose.Slides.Foss/_internal/pptx/layout_slide_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/master_slide_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/notes_slide_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/shape_factory.cpp
    src/Aspose.Slides.Foss/_internal/pptx/shape_type_mapping.cpp
    src/Aspose.Slides.Foss/_internal/pptx/slide_part.cpp
    src/Aspose.Slides.Foss/_internal/pptx/table_style_mapping.cpp
    src/Aspose.Slides.Foss/_internal/pptx/template.cpp
    src/Aspose.Slides.Foss/adjust_value.cpp
    src/Aspose.Slides.Foss/adjust_value_collection.cpp
    src/Aspose.Slides.Foss/auto_shape.cpp
    src/Aspose.Slides.Foss/base_handout_notes_slide_header_footer_manager.cpp
    src/Aspose.Slides.Foss/bullet_format.cpp
    src/Aspose.Slides.Foss/camera.cpp
    src/Aspose.Slides.Foss/cell.cpp
    src/Aspose.Slides.Foss/cell_collection.cpp
    src/Aspose.Slides.Foss/cell_format.cpp
    src/Aspose.Slides.Foss/column.cpp
    src/Aspose.Slides.Foss/column_collection.cpp
    src/Aspose.Slides.Foss/comment.cpp
    src/Aspose.Slides.Foss/comment_author.cpp
    src/Aspose.Slides.Foss/comment_author_collection.cpp
    src/Aspose.Slides.Foss/comment_collection.cpp
    src/Aspose.Slides.Foss/connector.cpp
    src/Aspose.Slides.Foss/document_properties.cpp
    src/Aspose.Slides.Foss/drawing/color.cpp
    src/Aspose.Slides.Foss/drawing/point_f.cpp
    src/Aspose.Slides.Foss/drawing/size.cpp
    src/Aspose.Slides.Foss/drawing/size_f.cpp
    src/Aspose.Slides.Foss/effect_format.cpp
    src/Aspose.Slides.Foss/effects/blur.cpp
    src/Aspose.Slides.Foss/effects/fill_overlay.cpp
    src/Aspose.Slides.Foss/effects/glow.cpp
    src/Aspose.Slides.Foss/effects/inner_shadow.cpp
    src/Aspose.Slides.Foss/effects/outer_shadow.cpp
    src/Aspose.Slides.Foss/effects/preset_shadow.cpp
    src/Aspose.Slides.Foss/effects/reflection.cpp
    src/Aspose.Slides.Foss/effects/soft_edge.cpp
    src/Aspose.Slides.Foss/fill_format.cpp
    src/Aspose.Slides.Foss/gradient_format.cpp
    src/Aspose.Slides.Foss/gradient_stop.cpp
    src/Aspose.Slides.Foss/gradient_stop_collection.cpp
    src/Aspose.Slides.Foss/group_shape.cpp
    src/Aspose.Slides.Foss/image.cpp
    src/Aspose.Slides.Foss/image_collection.cpp
    src/Aspose.Slides.Foss/image_utils.cpp
    src/Aspose.Slides.Foss/images.cpp
    src/Aspose.Slides.Foss/layout_slide.cpp
    src/Aspose.Slides.Foss/light_rig.cpp
    src/Aspose.Slides.Foss/line_format.cpp
    src/Aspose.Slides.Foss/master_slide.cpp
    src/Aspose.Slides.Foss/master_slide_collection.cpp
    src/Aspose.Slides.Foss/notes_size.cpp
    src/Aspose.Slides.Foss/notes_slide.cpp
    src/Aspose.Slides.Foss/notes_slide_header_footer_manager.cpp
    src/Aspose.Slides.Foss/notes_slide_manager.cpp
    src/Aspose.Slides.Foss/paragraph.cpp
    src/Aspose.Slides.Foss/paragraph_collection.cpp
    src/Aspose.Slides.Foss/paragraph_format.cpp
    src/Aspose.Slides.Foss/pattern_format.cpp
    src/Aspose.Slides.Foss/picture.cpp
    src/Aspose.Slides.Foss/picture_fill_format.cpp
    src/Aspose.Slides.Foss/picture_frame_lock.cpp
    src/Aspose.Slides.Foss/picture_utilities.cpp
    src/Aspose.Slides.Foss/placeholder.cpp
    src/Aspose.Slides.Foss/portion.cpp
    src/Aspose.Slides.Foss/portion_collection.cpp
    src/Aspose.Slides.Foss/portion_format.cpp
    src/Aspose.Slides.Foss/pp_image.cpp
    src/Aspose.Slides.Foss/presentation.cpp
    src/Aspose.Slides.Foss/pvi_object.cpp
    src/Aspose.Slides.Foss/row.cpp
    src/Aspose.Slides.Foss/row_collection.cpp
    src/Aspose.Slides.Foss/shape.cpp
    src/Aspose.Slides.Foss/shape_bevel.cpp
    src/Aspose.Slides.Foss/shape_collection.cpp
    src/Aspose.Slides.Foss/slide.cpp
    src/Aspose.Slides.Foss/slide_collection.cpp
    src/Aspose.Slides.Foss/table.cpp
    src/Aspose.Slides.Foss/table_format.cpp
    src/Aspose.Slides.Foss/text_frame.cpp
    src/Aspose.Slides.Foss/text_frame_format.cpp
    src/Aspose.Slides.Foss/three_d_format.cpp
)

# Static only. Nothing in this library is annotated for symbol export, so a
# Windows DLL built from these sources would export no symbols at all and fail
# to link against anything. Forcing the type here means BUILD_SHARED_LIBS=ON --
# which package managers set globally -- produces a library that works rather
# than one that silently cannot be used.
add_library(AsposeSlidesFoss STATIC ${ASPOSE_SLIDES_FOSS_SOURCES})
add_library(AsposeSlidesFoss::AsposeSlidesFoss ALIAS AsposeSlidesFoss)

set_target_properties(AsposeSlidesFoss PROPERTIES
    OUTPUT_NAME aspose_slides_foss
    EXPORT_NAME AsposeSlidesFoss)

# PUBLIC: the headers this library installs are C++20 headers, so a consumer
# that compiles them needs the same standard. Expressed as a compile feature
# rather than CMAKE_CXX_STANDARD so it travels with the exported target.
target_compile_features(AsposeSlidesFoss PUBLIC cxx_std_20)
set_target_properties(AsposeSlidesFoss PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(AsposeSlidesFoss PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${ASPOSE_SLIDES_FOSS_GENERATED_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# pugixml is PUBLIC because 44 of this library's public headers include
# <pugixml.hpp>; see "Public headers and pugixml" in README.md. miniz is
# PRIVATE: it appears in no header. A static archive still records it as a
# link-time requirement, which is why it is installed alongside.
target_link_libraries(AsposeSlidesFoss
    PUBLIC pugixml::pugixml
    PRIVATE ${ASPOSE_SLIDES_FOSS_MINIZ_TARGET})

# Warnings, on this project's own sources only (PRIVATE): a consumer's build
# should never be made noisier or more fragile by a header of ours.
if(MSVC)
    # C4250, "inherits <member> via dominance", fires 1430 times in a clean
    # build of this library and says nothing: the interface hierarchy uses
    # virtual inheritance, and dominance is precisely the rule the language
    # defines for choosing the override. Left on it buries the warnings that do
    # mean something -- there were seven of those against those 1430. With it
    # off and those seven fixed, the library compiles at /W4 in silence, which
    # is what makes ASPOSE_SLIDES_FOSS_WARNINGS_AS_ERRORS usable here.
    target_compile_options(AsposeSlidesFoss PRIVATE /W4 /wd4250)

    # std::sscanf is deprecated only by MSVC, and only in favour of sscanf_s,
    # which no other toolchain has. Both calls here parse a fixed "%d-%d-%d..."
    # date out of a NUL-terminated std::string and write into ints -- there is
    # no buffer for the checked variant to check.
    target_compile_definitions(AsposeSlidesFoss PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(AsposeSlidesFoss PRIVATE -Wall -Wextra)
endif()
if(ASPOSE_SLIDES_FOSS_WARNINGS_AS_ERRORS)
    if(MSVC)
        target_compile_options(AsposeSlidesFoss PRIVATE /WX)
    else()
        target_compile_options(AsposeSlidesFoss PRIVATE -Werror)
    endif()
endif()

# ---------------------------------------------------------------------------
# Software bill of materials
#
# Generated from the same variables that drive FetchContent above, so it cannot
# describe a dependency set the build does not actually use.
# ---------------------------------------------------------------------------

string(TIMESTAMP ASPOSE_SLIDES_FOSS_SBOM_TIMESTAMP "%Y-%m-%dT%H:%M:%SZ" UTC)
string(UUID ASPOSE_SLIDES_FOSS_SBOM_UUID
       NAMESPACE "6ba7b810-9dad-11d1-80b4-00c04fd430c8"
       NAME "AsposeSlidesFoss-${PROJECT_VERSION}"
       TYPE SHA1)
set(ASPOSE_SLIDES_FOSS_SBOM_PATH
    "${PROJECT_BINARY_DIR}/aspose-slides-foss-cpp.cdx.json")
configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/sbom.cdx.json.in"
    "${ASPOSE_SLIDES_FOSS_SBOM_PATH}"
    @ONLY)

# ---------------------------------------------------------------------------
# Install and export
# ---------------------------------------------------------------------------

if(ASPOSE_SLIDES_FOSS_INSTALL)
    # No INCLUDES DESTINATION here: the target already carries
    # $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>, and naming it twice
    # writes the same directory into the exported target twice.
    install(TARGETS AsposeSlidesFoss
            EXPORT AsposeSlidesFossTargets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING PATTERN "*.h")

    install(FILES
                "${ASPOSE_SLIDES_FOSS_GENERATED_INCLUDE_DIR}/Aspose/Slides/Foss/version.h"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Aspose/Slides/Foss)

    # share/doc/AsposeSlidesFoss, not share/AsposeSlidesFoss: the latter is
    # where vcpkg relocates a package's CMake configuration, and two different
    # kinds of file in one directory is how one of them gets deleted by a
    # cleanup step that meant the other.
    install(FILES
                "${PROJECT_SOURCE_DIR}/LICENSE"
                "${PROJECT_SOURCE_DIR}/THIRD_PARTY_NOTICES"
                "${ASPOSE_SLIDES_FOSS_SBOM_PATH}"
            DESTINATION ${CMAKE_INSTALL_DOCDIR})

    install(EXPORT AsposeSlidesFossTargets
            FILE AsposeSlidesFossTargets.cmake
            NAMESPACE AsposeSlidesFoss::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AsposeSlidesFoss)

    # The same targets, usable straight out of the build tree by a project that
    # pulls this one in with FetchContent or add_subdirectory.
    export(EXPORT AsposeSlidesFossTargets
           FILE "${PROJECT_BINARY_DIR}/AsposeSlidesFossTargets.cmake"
           NAMESPACE AsposeSlidesFoss::)

    # What the installed config has to look for depends on how this build
    # resolved its dependencies. A fetched pugixml or miniz is installed into
    # this same prefix by its own rules, so find_dependency finds it there; an
    # external one is found wherever the consumer's CMAKE_PREFIX_PATH points.
    # Either way the call is the same, which is why this is one string.
    set(ASPOSE_SLIDES_FOSS_DEPENDENCY_FINDS
"find_dependency(pugixml)
find_dependency(miniz)")

    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/AsposeSlidesFossConfig.cmake.in"
        "${PROJECT_BINARY_DIR}/AsposeSlidesFossConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AsposeSlidesFoss)

    # SameMinorVersion, not SameMajorVersion: before 1.0 the major number says
    # nothing, and a 0.x series makes no compatibility promise across minors.
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/AsposeSlidesFossConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMinorVersion)

    install(FILES
                "${PROJECT_BINARY_DIR}/AsposeSlidesFossConfig.cmake"
                "${PROJECT_BINARY_DIR}/AsposeSlidesFossConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AsposeSlidesFoss)
endif()

# ---------------------------------------------------------------------------
# Tests
#
# Everything below is inside the option: a consumer building only the library
# never downloads a test framework and never defines a test target.
# ---------------------------------------------------------------------------

if(ASPOSE_SLIDES_FOSS_BUILD_TESTS)
    # Never install GoogleTest into this project's prefix.
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    # Match the CRT this project uses; MSVC refuses to link a static-CRT
    # GoogleTest into a dynamic-CRT test binary.
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    find_package(GTest ${ASPOSE_SLIDES_FOSS_GOOGLETEST_VERSION} CONFIG QUIET)
    if(GTest_FOUND)
        message(STATUS "GoogleTest: using installed package ${GTest_VERSION}")
    else()
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG ${ASPOSE_SLIDES_FOSS_GOOGLETEST_TAG}
            GIT_SHALLOW TRUE
        )
        FetchContent_MakeAvailable(googletest)
        message(STATUS "GoogleTest: fetched ${ASPOSE_SLIDES_FOSS_GOOGLETEST_TAG}")
    endif()

    enable_testing()

    set(ASPOSE_SLIDES_FOSS_TEST_SOURCES
    tests/Aspose.Slides.Foss.IntegrationTests/comments_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/connector_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/document_properties_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/effect_format_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/fill_format_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/images_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/line_format_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/notes_slide_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/presentation_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/shapes_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/slides_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/table_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/text_formatting_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/text_test.cpp
    tests/Aspose.Slides.Foss.IntegrationTests/threed_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/adjust_value_test.cpp
    tests/Aspose.Slides.Foss.Tests/app_properties_part_test.cpp
    tests/Aspose.Slides.Foss.Tests/auto_shape_test.cpp
    tests/Aspose.Slides.Foss.Tests/base_portion_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/base_slide_test.cpp
    tests/Aspose.Slides.Foss.Tests/blur_test.cpp
    tests/Aspose.Slides.Foss.Tests/bullet_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/cell_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/cell_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/cell_test.cpp
    tests/Aspose.Slides.Foss.Tests/color_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/column_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/column_test.cpp
    tests/Aspose.Slides.Foss.Tests/comment_authors_part_test.cpp
    tests/Aspose.Slides.Foss.Tests/comment_test.cpp
    tests/Aspose.Slides.Foss.Tests/comments_part_test.cpp
    tests/Aspose.Slides.Foss.Tests/connector_test.cpp
    tests/Aspose.Slides.Foss.Tests/core_properties_part_test.cpp
    tests/Aspose.Slides.Foss.Tests/custom_properties_part_test.cpp
    tests/Aspose.Slides.Foss.Tests/document_properties_test.cpp
    tests/Aspose.Slides.Foss.Tests/drawing_test.cpp
    tests/Aspose.Slides.Foss.Tests/effect_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/enums_test.cpp
    tests/Aspose.Slides.Foss.Tests/fill_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/fill_overlay_test.cpp
    tests/Aspose.Slides.Foss.Tests/font_data_test.cpp
    tests/Aspose.Slides.Foss.Tests/glow_test.cpp
    tests/Aspose.Slides.Foss.Tests/gradient_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/gradient_stop_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/gradient_stop_test.cpp
    tests/Aspose.Slides.Foss.Tests/graphical_object_lock_test.cpp
    tests/Aspose.Slides.Foss.Tests/graphical_object_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_auto_shape_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_base_portion_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_bullet_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_cell_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_column_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_comment_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_geometry_shape_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_inner_shadow_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_layout_slide_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_layout_slide_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_light_rig_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_line_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_master_slide_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_master_slide_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_notes_size_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_notes_slide_manager_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_notes_slide_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_outer_shadow_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_paragraph_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_paragraph_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_paragraph_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_pattern_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_picture_fill_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_picture_frame_lock_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_portion_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_portion_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_preset_shadow_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_reflection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_row_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_shape_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_shape_frame_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_shape_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_slide_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_slide_component_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_slide_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_table_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_text_frame_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/i_text_frame_test.cpp
    tests/Aspose.Slides.Foss.Tests/image_test.cpp
    tests/Aspose.Slides.Foss.Tests/image_transform_operation_test.cpp
    tests/Aspose.Slides.Foss.Tests/line_fill_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/line_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/master_slide_collection_test.cpp
    tests/Aspose.Slides.Foss.Tests/master_slide_part_test.cpp
    tests/Aspose.Slides.Foss.Tests/notes_slide_header_footer_manager_test.cpp
    tests/Aspose.Slides.Foss.Tests/notes_slide_manager_test.cpp
    tests/Aspose.Slides.Foss.Tests/notes_slide_part_test.cpp
    tests/Aspose.Slides.Foss.Tests/paragraph_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/paragraph_slide_test.cpp
    tests/Aspose.Slides.Foss.Tests/picture_frame_test.cpp
    tests/Aspose.Slides.Foss.Tests/picture_test.cpp
    tests/Aspose.Slides.Foss.Tests/picture_utilities_test.cpp
    tests/Aspose.Slides.Foss.Tests/portion_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/portion_test.cpp
    tests/Aspose.Slides.Foss.Tests/presentation_io_test.cpp
    tests/Aspose.Slides.Foss.Tests/relationships_test.cpp
    tests/Aspose.Slides.Foss.Tests/row_test.cpp
    tests/Aspose.Slides.Foss.Tests/shape_bevel_test.cpp
    tests/Aspose.Slides.Foss.Tests/shape_type_test.cpp
    tests/Aspose.Slides.Foss.Tests/soft_edge_test.cpp
    tests/Aspose.Slides.Foss.Tests/table_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/table_test.cpp
    tests/Aspose.Slides.Foss.Tests/text_frame_format_test.cpp
    tests/Aspose.Slides.Foss.Tests/text_frame_test.cpp
    tests/Aspose.Slides.Foss.Tests/threed_format_test.cpp
    tests/conformance/comments_conformance_test.cpp
    tests/conformance/conformance.cpp
    tests/conformance/document_properties_conformance_test.cpp
    tests/conformance/effects_conformance_test.cpp
    tests/conformance/foreign_deck_conformance_test.cpp
    tests/conformance/harness_self_test.cpp
    tests/conformance/line_format_conformance_test.cpp
    tests/conformance/picture_frame_conformance_test.cpp
    tests/conformance/save_format_conformance_test.cpp
    tests/conformance/slides_conformance_test.cpp
    tests/conformance/table_conformance_test.cpp
    tests/conformance/test_png.cpp
    tests/conformance/text_body_conformance_test.cpp
    tests/conformance/three_d_conformance_test.cpp
)

    add_executable(aspose_slides_foss_tests ${ASPOSE_SLIDES_FOSS_TEST_SOURCES})

    # miniz is named here as well as in the library. The conformance harness
    # opens the saved package with its own ZIP reader rather than the
    # library's, which is the whole point of it: a harness that reused the
    # writer's own code could not tell a malformed package from a well-formed
    # one. That makes miniz a direct dependency of the tests, and it has to be
    # asked for directly -- the library links it PRIVATE and does not hand its
    # headers on.
    target_link_libraries(aspose_slides_foss_tests
        PRIVATE AsposeSlidesFoss::AsposeSlidesFoss
                ${ASPOSE_SLIDES_FOSS_MINIZ_TARGET}
                GTest::gtest_main
                GTest::gmock)

    # The conformance harness (tests/conformance) is included as
    # "conformance/conformance.h". It is test-only and deliberately absent from
    # the installed interface.
    target_include_directories(aspose_slides_foss_tests PRIVATE tests)

    include(GoogleTest)
    # PRE_TEST, not the POST_BUILD default: discovery runs when ctest runs, so
    # building the suite does not require being able to execute it.
    gtest_discover_tests(aspose_slides_foss_tests DISCOVERY_MODE PRE_TEST)
endif()
