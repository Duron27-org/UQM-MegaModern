from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain


class UrQuanMastersConan(ConanFile):
    settings = 'os', 'arch', 'compiler', 'build_type'

    options = {
        'enable_asan': [True, False],
        'enable_linter': [True, False],
    }

    def configure(self):
        pass
        #if self.options.enable_asan and self.settings.build_type != 'Debug':
        #    raise ConanInvalidConfiguration('ASan requires Debug build')
    
    requires = (
        'cli11/2.6.0',
        'ogg/1.3.5',
        'fmt/12.1.0',
        'gsl-lite/1.0.1',
        'gtest/1.17.0',
        'libpng/1.6.54',
        'magic_enum/0.9.7',
        'openal-soft/1.23.1',
        'sdl/2.32.10',
        'spdlog/1.17.0',
        'utfcpp/4.0.8',
        'vorbis/1.3.7',
        'zlib/1.3.1',
    )

    generators = (
        'CMakeDeps',
    )

    default_options = {
        'enable_asan': False,
        'enable_linter': False,
        'openal-soft/*:shared': True,
    }

    def layout(self):
        cmake_layout(self)
        
    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['ENABLE_ASAN'] = bool(self.options.enable_asan)
        tc.variables['ENABLE_LINTER'] = bool(self.options.enable_linter)
        tc.generate()