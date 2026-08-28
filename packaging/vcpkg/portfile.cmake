# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Aspose Pty Ltd
#
# DRAFT. Not submittable: REF names a tag that does not exist yet and SHA512 is
# a placeholder. See ../README.md.

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO aspose-slides-foss/Aspose.Slides-FOSS-for-Cpp
    REF "v${VERSION}"
    # Replace with the SHA512 of the archive GitHub generates for that tag:
    #   vcpkg install aspose-slides-foss --overlay-ports=... prints the actual
    #   hash on the first mismatch, or compute it from the downloaded archive.
    SHA512 0
    HEAD_REF main
)

# The library has no symbol-export annotations, so it is static only; see the
# comment on add_library() in the project's CMakeLists.txt. There is no shared
# variant to offer and therefore no feature to switch on.
vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        # vcpkg resolves pugixml and miniz itself. Without this the build would
        # clone its own copies, and the package would contain code vcpkg cannot
        # see, version or patch.
        -DASPOSE_SLIDES_FOSS_FETCH_DEPENDENCIES=OFF
        -DASPOSE_SLIDES_FOSS_BUILD_TESTS=OFF
        -DBUILD_TESTING=OFF
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME AsposeSlidesFoss
    CONFIG_PATH lib/cmake/AsposeSlidesFoss
)

# Headers are installed once, from the release tree. The project's own doc
# directory goes too: vcpkg keeps its own bill of materials, and
# vcpkg_install_copyright below writes the licence in the layout the tool
# expects.
file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/debug/include"
    "${CURRENT_PACKAGES_DIR}/debug/share"
    "${CURRENT_PACKAGES_DIR}/share/doc"
)

vcpkg_install_copyright(
    FILE_LIST
        "${SOURCE_PATH}/LICENSE"
        "${SOURCE_PATH}/THIRD_PARTY_NOTICES"
)
