# Run conan
`conan install . -of conanbuild --build=missing`
or for debug:
`conan install . -of conanbuild --build=missing --profile=debug`

# Generate cmake build files
cmake . -G Ninja -B conanbuild -DCMAKE_TOOLCHAIN_FILE="conanbuild/build/Debug/generators/conan_toolchain.cmake"       

# Build
cmake --build conanbuild