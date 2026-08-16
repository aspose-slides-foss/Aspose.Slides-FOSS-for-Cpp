# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Aspose Pty Ltd
#
# A consumer of the *installed* package, not of this source tree. It is a
# project in its own right: it never adds the library's directory, and the only
# thing it is given is a prefix to look in.
#
#   cmake -S . -B build -DCMAKE_PREFIX_PATH=<install-prefix>
#   cmake --build build
#   ./build/consumer_example out.pptx
#
# If find_package cannot see the package, or the exported target does not carry
# its include directories, its C++ standard or its dependencies, this fails to
# configure or fails to link. That is the point: it is the check that the
# install rules produce something usable from outside.

cmake_minimum_required(VERSION 3.20)

project(aspose_slides_foss_consumer LANGUAGES CXX)

find_package(AsposeSlidesFoss CONFIG REQUIRED)

add_executable(consumer_example main.cpp)
target_link_libraries(consumer_example PRIVATE AsposeSlidesFoss::AsposeSlidesFoss)
