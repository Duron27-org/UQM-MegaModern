cmake_minimum_required(VERSION 3.21)

# This is a subproject, not a standalone root project
# Do NOT call project() again unless you want separate languages/toolchains



# ---- Test sources ----------------------------------------------------------

set(uqm_test_sources_all "main.cpp")

include("tests/tests.cmake")
list(APPEND uqm_test_sources_all ${uqm_tests_master_files})

set(UQM_TEST_SOURCES
    ${uqm_test_sources_all}
)
message(STATUS "Test sources: ${UQM_TEST_SOURCES}")
message(STATUS "CMake source dir: ${CMAKE_SOURCE_DIR}")

# ---- Test executable -------------------------------------------------------

add_executable(UQM_Tests
    ${UQM_TEST_SOURCES}
)
target_link_libraries(UQM_Tests PRIVATE uqm_project_features)

target_compile_options(UQM_Tests
    PRIVATE
        $<$<CONFIG:RelWithDebInfo>:/Zi /Od>
)

target_link_options(UQM_Tests
    PRIVATE
        $<$<CONFIG:RelWithDebInfo>:/DEBUG>
)

# ---- Include paths ---------------------------------------------------------

# Include the main project's src/ directory
target_include_directories(UQM_Tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# ---- Link libraries --------------------------------------------------------

find_package(fmt REQUIRED)
find_package(gsl-lite REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

# GTest::gtest and GTest::gtest_main are the modern imported targets
target_link_libraries(UQM_Tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        fmt::fmt
        gsl-lite::gsl-lite
        spdlog::spdlog

)

# ---- Compiler options (inherit from main project if needed) ---------------

# If you want tests to match main compile settings:
# target_link_libraries(UQM_Tests PRIVATE UrQuanMasters)

# ---- Enable GTest integration ---------------------------------------------

include(GoogleTest)
gtest_discover_tests(UQM_Tests)