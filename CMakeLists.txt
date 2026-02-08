#TODO: CLEAN THIS UP! IT'S A MESS!

cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
project(UrQuanMastersMegaModern CXX)

include(CMake/helpers.cmake)
#set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    if (NOT CMAKE_GENERATOR MATCHES "Visual Studio")
        find_program(CLANG_CL clang-cl)
        if (NOT CLANG_CL)
            message(FATAL_ERROR "clang-cl not found")
        endif()
        message(STATUS "Using clang-cl")
        set(CMAKE_C_COMPILER   ${CLANG_CL} CACHE STRING "" FORCE)
        set(CMAKE_CXX_COMPILER ${CLANG_CL} CACHE STRING "" FORCE)
    endif()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

option(ENABLE_LINTER "Enable Linter" OFF)
if (ENABLE_LINTER)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS  "Enabling clang-tidy")
        set(CMAKE_C_CLANG_TIDY clang-tidy)
        set(CMAKE_CXX_CLANG_TIDY clang-tidy)
    endif()
endif()


set(APP_TARGET UrQuanMasters)

################################################################################
# Source groups
################################################################################

set(Doc_files
"BUGS"
"ChangeLog"
"TODO.txt"
)
source_group("Doc" FILES ${Doc_files})

set(uqm_project_files_master ${Doc_files})

include("doc/doc.cmake")
list(APPEND uqm_project_files_master ${uqm_doc_master_files})
include("src/src.cmake")
list(APPEND uqm_project_files_master ${uqm_src_master_files})

set(ALL_FILES
    ${Doc_files}
    ${uqm_project_files_master}
)

################################################################################
# Target
################################################################################
add_executable(${APP_TARGET} ${ALL_FILES})

################################################################################
# Dependencies
################################################################################

find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(Ogg REQUIRED)
find_package(Vorbis REQUIRED)
find_package(OpenAL REQUIRED)

find_package(GTest QUIET)
if (GTest_FOUND)
    add_subdirectory(test)
endif()

################################################################################
# Include directories
################################################################################
target_include_directories(${APP_TARGET} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${APP_TARGET} PRIVATE
    "$<$<CONFIG:Debug>:"
        "DEBUG;"
        "_DEBUG;"
        "DEBUG_TRACK_SEM;"
        "DEBUG_DCQ_THREADS"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "WIN32;"
    "_CONSOLE;"
    "_VW=320;"
    "_VH=240;"
    "GFXMODULE_SDL;"
    "THREADLIB_SDL;"
    "HAVE_OPENAL;"
    "HAVE_ZIP;"
    "HAVE_JOYSTICK;"
    "NETPLAY;"
   # "ZLIB_DLL;"
    "USE_INTERNAL_MIKMOD;"
    "USE_INTERNAL_LUA;"
    "USE_PLATFORM_ACCEL;"
    "_CRT_SECURE_NO_WARNINGS;"
    "_MBCS;"
# required to suppress issue in SDL_endian.h regarding a redefinition of the _m_prefetch intrinsic under clang.
    "__PRFCHWINTRIN_H" 
)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
#add_compile_options(/fsanitize=address /Zi /BLAH)
if (ENABLE_ASAN)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if (NOT "$<CONFIG>" STREQUAL "Release")
            message (FATAL_ERROR "ASAN requires a release build in clang (RelWithDbgInfo does not count!)")
        endif()

        message(STATUS "Enabling ASAN for Clang")
        if (WIN32)
            target_compile_options(${APP_TARGET} PRIVATE
                -fsanitize=address
                -fsanitize-address-use-after-scope
                -Xclang -fno-optimize-sibling-calls
                /Oy-
                -O1
            )
            #lld-link does not understand -sanitize=address So we must manually link the library
            # Find local Asan runtime
            explicitly_link_clang_asan_on_windows(${APP_TARGET})
            
        else()
            target_compile_options(${APP_TARGET} PRIVATE
                -fsanitize=address
                -fsanitize-address-use-after-scope
                -fno-optimize-sibling-calls
                -fno-omit-frame-pointer
                -O1
            )
            target_link_options(${APP_TARGET} PRIVATE
                -fsanitize=address
            )
        endif()
    # MSVC (Visual Studio cl.exe)
    elseif (MSVC)
        message(STATUS "Enabling ASAN for MSVC")
        target_compile_options(${APP_TARGET} PRIVATE /fsanitize=address /Zi)
        target_link_options(${APP_TARGET} PRIVATE /fsanitize=address)
    else()
        message(FATAL_ERROR "AddressSanitizer not supported with this compiler on Windows")
    endif()
endif()





################################################################################
# Compile and link options
################################################################################
#target_compile_features(${APP_TARGET} PRIVATE cxx_std_17)

# if(MSVC)
#     target_compile_options(${APP_TARGET} PRIVATE
#         $<$<CONFIG:Debug>:
#             /Od;
#             /RTC1;
#             /Gy-;
#             /W3;
#             /fp:except-;
#             /GR
#         >
#         $<$<CONFIG:Release>:
#             /O2;
#             /Oi;
#             /GF;
#             /Gy;
#             /W2
#         >
#         /MP;
#         /sdl-;
#         ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
#         /TP;
#         ${DEFAULT_CXX_EXCEPTION_HANDLING}
#     )
#     target_link_options(${APP_TARGET} PRIVATE
#         $<$<CONFIG:Debug>:
#             /NODEFAULTLIB:msvcrt.lib;
#             /DEBUG;
#             /SUBSYSTEM:CONSOLE;
#             /NXCOMPAT:NO;
#             /DYNAMICBASE:NO;
#             /INCREMENTAL
#         >
#         $<$<CONFIG:Release>:
#             /NODEFAULTLIB:msvcrtd.lib;
#             /DEBUG;
#             /SUBSYSTEM:WINDOWS;
#             /INCREMENTAL:NO
#         >
#         /NOLOGO
#     )
# endif()


################################################################################
# Dependencies
################################################################################
target_link_libraries(${APP_TARGET}
    PRIVATE
        SDL2::SDL2main 
        PNG::PNG 
        ZLIB::ZLIB 
        vorbis::vorbis 
        Ogg::ogg 
        OpenAL::OpenAL
        ws2_32
        $<$<CONFIG:Release>:user32>
)

#print_library_properties(SDL2::SDL2main)

# Copy runtime DLLs as needed.
add_custom_command(TARGET ${APP_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:${APP_TARGET}>
        $<TARGET_FILE_DIR:${APP_TARGET}>
    COMMAND_EXPAND_LISTS
)


########################
## Debugging
########################
    set_target_properties(${APP_TARGET} PROPERTIES 
        VS_DEBUGGER_COMMAND_ARGUMENTS 
        "-n ${CMAKE_CURRENT_LIST_DIR}/content"
    )

