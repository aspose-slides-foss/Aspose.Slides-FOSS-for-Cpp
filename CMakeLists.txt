cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)
project(aspose_slides_foss LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/FS /EHsc)
endif()

# AddressSanitizer.
#
# Memory-lifetime faults are not reliably visible in an ordinary build: reading
# through a pointer to a freed object usually returns whatever the allocator
# left behind, so the same defect crashes on one machine and silently returns
# plausible numbers on another. ASan turns that into a deterministic, located
# failure, which is the difference between a bug report and a rumour. Off by
# default because it costs roughly 2x run time; CI should run the suite at
# least once with it on.
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

# Library
file(GLOB_RECURSE LIB_SOURCES src/*.cpp)
file(GLOB_RECURSE LIB_HEADERS include/*.h)
add_library(${PROJECT_NAME} ${LIB_SOURCES} ${LIB_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# pugixml (lightweight XML parser)
include(FetchContent)
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.14
)
FetchContent_MakeAvailable(pugixml)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml::pugixml)

# miniz (ZIP archive library)
FetchContent_Declare(
    miniz
    GIT_REPOSITORY https://github.com/richgel999/miniz.git
    GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(miniz)
target_link_libraries(${PROJECT_NAME} PUBLIC miniz)

# GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

# Tests
enable_testing()
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::gtest_main GTest::gmock)
# The conformance harness (tests/conformance) is included as
# "conformance/conformance.h". It is test-only and deliberately absent from the
# installed interface.
target_include_directories(${PROJECT_NAME}_tests PRIVATE tests)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
