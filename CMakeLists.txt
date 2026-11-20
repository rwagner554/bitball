cmake_minimum_required(VERSION 3.21)

project(bitball LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# SDL3
#
# third_party/SDL3 is the prebuilt SDL3-devel-*-VC package: headers, import
# libraries and DLLs for x86/x64/arm64, plus SDL3Config.cmake.
#
# SDL3Config.cmake picks its lib/<arch> directory from SDL_CPU_<arch>
# variables, which a source build sets for itself. Prebuilt-package users have
# to supply them, so derive them from the target platform here.
# ---------------------------------------------------------------------------
if(CMAKE_GENERATOR_PLATFORM MATCHES "^[Aa][Rr][Mm]64")
  set(SDL_CPU_ARM64 ON)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(SDL_CPU_X64 ON)
else()
  set(SDL_CPU_X86 ON)
endif()

# The shipped config starts with cmake_minimum_required(VERSION 3.0...3.28),
# which CMake 4.x rejects outright. Let it keep 3.5-era behaviour so we don't
# have to patch a vendored file.
if(NOT DEFINED CMAKE_POLICY_VERSION_MINIMUM)
  set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
endif()

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL3")
find_package(SDL3 3.2 CONFIG REQUIRED)

# ---------------------------------------------------------------------------
# OpenGL loader (GLAD)
#
# Windows only exports OpenGL 1.1 from opengl32.dll, so anything newer
# (shaders included) has to be resolved at runtime. third_party/glad is GLAD's
# generated output for OpenGL 3.3 core: glad/gl.h declares every core entry
# point, glad.c loads them through the function pointer we hand it.
#
# Regenerate/upgrade with:
#   py -m glad --api gl=3.3 --profile core \
#       --out-path third_party/glad --generator c --reproducible
# ---------------------------------------------------------------------------
add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad SYSTEM PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include")

# ---------------------------------------------------------------------------
# Game executable
# ---------------------------------------------------------------------------
# All build products land in <repo>/bin/<Config>/, not inside build/. Using a
# generator expression here stops multi-config generators (Visual Studio) from
# appending their own configuration subdirectory on top.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

add_executable(bitball
  src/main.cpp
  src/Bit/Bit.cpp
)

target_include_directories(bitball PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(bitball PRIVATE SDL3::SDL3)

if(MSVC)
  target_compile_options(bitball PRIVATE /W4 /permissive- /utf-8)
endif()

# SDL3 is linked dynamically, so the DLL has to sit next to the .exe.
add_custom_command(TARGET bitball POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "$<TARGET_FILE:SDL3::SDL3-shared>"
          "$<TARGET_FILE_DIR:bitball>"
  COMMENT "Copying SDL3.dll next to bitball.exe"
)

# F5 in Visual Studio / VSCode should launch the game, not ALL_BUILD.
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT bitball)
