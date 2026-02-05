from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain


class UrQuanMastersConan(ConanFile):
    settings = 'os', 'arch', 'compiler', 'build_type'

    options = {
        'enable_asan': [True, False],
    }

    def configure(self):
        pass
        #if self.options.enable_asan and self.settings.build_type != 'Debug':
        #    raise ConanInvalidConfiguration('ASan requires Debug build')
    
    requires = (
        'zlib/1.3.1',
        'sdl/2.32.10',
        'libpng/1.6.54',
        'ogg/1.3.5',
        'vorbis/1.3.7',
        'openal-soft/1.23.1',
    )

    generators = (
        'CMakeDeps',
    )

    default_options = {
        'enable_asan': False,
        'openal-soft/*:shared': True,
    }

    def layout(self):
        cmake_layout(self)
        
    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['ENABLE_ASAN'] = bool(self.options.enable_asan)
        tc.generate()