cmake_minimum_required(VERSION 3.21)

# This is a subproject, not a standalone root project
# Do NOT call project() again unless you want separate languages/toolchains

# ---- Test sources ----------------------------------------------------------

set(UQM_TEST_SOURCES
    main.cpp
    tests/test_foo.cpp
)

# ---- Test executable -------------------------------------------------------

add_executable(UQM_Tests
    ${UQM_TEST_SOURCES}
)

# ---- Include paths ---------------------------------------------------------

# Include the main project's src/ directory
target_include_directories(UQM_Tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# ---- Link libraries --------------------------------------------------------

# GTest::gtest and GTest::gtest_main are the modern imported targets
target_link_libraries(UQM_Tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)

# ---- Compiler options (inherit from main project if needed) ---------------

# If you want tests to match main compile settings:
# target_link_libraries(UQM_Tests PRIVATE UrQuanMasters)

# ---- Enable GTest integration ---------------------------------------------

include(GoogleTest)
gtest_discover_tests(UQM_Tests)