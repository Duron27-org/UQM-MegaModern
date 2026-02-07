# Run conan
`conan install . -of conanbuild --build=missing`
or for debug:
`conan install . -of conanbuild --build=missing --profile=debug`

# Generate cmake build files
cmake . -G Ninja -B conanbuild -DCMAKE_TOOLCHAIN_FILE="conanbuild/build/[BUILD_TARGET]/generators/conan_toolchain.cmake"  -DCMAKE_BUILD_TYPE=[BUILD_TARGET]

# Build
cmake --build conanbuild

# for ASAN, build with the "RelWithDebInfo" configuration target (I have an ASAN profile named "asan" that sets the build type to "RelWithDebInfo" and enables ASAN):)
conan install . -of conanbuild --build=missing -o enable_asan=True --profile=asan
cmake . -G Ninja -B conanbuild -DCMAKE_TOOLCHAIN_FILE="conanbuild/build/RelWithDebInfo/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=RelWithDebInfo