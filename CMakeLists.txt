cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(UrQuanMastersMegaModern CXX)

#set (CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")


################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

#if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"))
#    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
#endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)
include(CMake/helpers.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################



























set(PROJECT_NAME UrQuanMasters)

################################################################################
# Source groups
################################################################################
set(Doc
    "BUGS"
    "ChangeLog"
    "TODO.txt"
)
source_group("Doc" FILES ${Doc})

set(Doc__Devel
    "doc/devel/aniformat"
    "doc/devel/checklist"
    "doc/devel/debug"
    "doc/devel/dialogs"
    "doc/devel/files"
    "doc/devel/fntformat"
    "doc/devel/fontres"
    "doc/devel/generate"
    "doc/devel/gfxlib"
    "doc/devel/gfxres"
    "doc/devel/gfxversions"
    "doc/devel/glossary"
    "doc/devel/input"
    "doc/devel/lua"
    "doc/devel/luasyntax"
    "doc/devel/musicres"
    "doc/devel/pkgformat"
    "doc/devel/planetrender"
    "doc/devel/planetrotate"
    "doc/devel/plugins"
    "doc/devel/resources"
    "doc/devel/script"
    "doc/devel/sfx"
    "doc/devel/strtab"
    "doc/devel/threads"
    "doc/devel/timing"
)
source_group("Doc\\Devel" FILES ${Doc__Devel})

set(Doc__Users
    "doc/users/manual.txt"
    "doc/users/unixinstall"
)
source_group("Doc\\Users" FILES ${Doc__Users})

set(Resources
    "src/res/kohr-ah1.ico"
    "src/res/sis1.ico"
    "src/res/starcon2.ico"
    "src/res/ur-quan-icon-alpha.ico"
    "src/res/ur-quan-icon-std.ico"
    "src/res/ur-quan1.ico"
    "src/res/ur-quan2.ico"
)
source_group("Resources" FILES ${Resources})

set(Source_Files
    "src/config.h"
    "src/config_vc6.h"
    "src/endian_uqm.h"
    "src/options.cpp"
    "src/options.h"
    "src/port.cpp"
    "src/port.h"
    "src/types.h"
    "src/uqm.cpp"
    "src/uqmversion.h"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files___core__memory
    "src/core/memory/memory.h"
)
source_group("Source Files\\_core\\memory" FILES ${Source_Files___core__memory})

set(Source_Files__getopt
    "src/getopt/getopt.cpp"
    "src/getopt/getopt.h"
    "src/getopt/getopt1.cpp"
)
source_group("Source Files\\getopt" FILES ${Source_Files__getopt})

set(Source_Files__libs
    "src/libs/alarm.h"
    "src/libs/async.h"
    "src/libs/callback.h"
    "src/libs/compiler.h"
    "src/libs/declib.h"
    "src/libs/file.h"
    "src/libs/gfxlib.h"
    "src/libs/heap.h"
    "src/libs/inplib.h"
    "src/libs/list.h"
    "src/libs/log.h"
    "src/libs/mathlib.h"
    "src/libs/md5.h"
    "src/libs/memlib.h"
    "src/libs/misc.h"
    "src/libs/net.h"
    "src/libs/platform.h"
    "src/libs/reslib.h"
    "src/libs/sndlib.h"
    "src/libs/strlib.h"
    "src/libs/tasklib.h"
    "src/libs/threadlib.h"
    "src/libs/timelib.h"
    "src/libs/uio.h"
    "src/libs/unicode.h"
    "src/libs/vidlib.h"
)
source_group("Source Files\\libs" FILES ${Source_Files__libs})

set(Source_Files__libs__callback
    "src/libs/callback/alarm.cpp"
    "src/libs/callback/alarm.h"
    "src/libs/callback/async.cpp"
    "src/libs/callback/async.h"
    "src/libs/callback/callback.cpp"
    "src/libs/callback/callback.h"
)
source_group("Source Files\\libs\\callback" FILES ${Source_Files__libs__callback})

set(Source_Files__libs__decomp
    "src/libs/decomp/lzdecode.cpp"
    "src/libs/decomp/lzencode.cpp"
    "src/libs/decomp/lzh.h"
    "src/libs/decomp/update.cpp"
)
source_group("Source Files\\libs\\decomp" FILES ${Source_Files__libs__decomp})

set(Source_Files__libs__file
    "src/libs/file/dirs.cpp"
    "src/libs/file/files.cpp"
    "src/libs/file/filintrn.h"
)
source_group("Source Files\\libs\\file" FILES ${Source_Files__libs__file})

set(Source_Files__libs__graphics
    "src/libs/graphics/bbox.cpp"
    "src/libs/graphics/bbox.h"
    "src/libs/graphics/boxint.cpp"
    "src/libs/graphics/clipline.cpp"
    "src/libs/graphics/cmap.cpp"
    "src/libs/graphics/cmap.h"
    "src/libs/graphics/context.cpp"
    "src/libs/graphics/context.h"
    "src/libs/graphics/dcqueue.cpp"
    "src/libs/graphics/dcqueue.h"
    "src/libs/graphics/drawable.cpp"
    "src/libs/graphics/drawable.h"
    "src/libs/graphics/drawcmd.h"
    "src/libs/graphics/filegfx.cpp"
    "src/libs/graphics/font.cpp"
    "src/libs/graphics/font.h"
    "src/libs/graphics/frame.cpp"
    "src/libs/graphics/gfx_common.cpp"
    "src/libs/graphics/gfx_common.h"
    "src/libs/graphics/gfxintrn.h"
    "src/libs/graphics/gfxload.cpp"
    "src/libs/graphics/intersec.cpp"
    "src/libs/graphics/loaddisp.cpp"
    "src/libs/graphics/pixmap.cpp"
    "src/libs/graphics/prim.h"
    "src/libs/graphics/resgfx.cpp"
    "src/libs/graphics/tfb_draw.cpp"
    "src/libs/graphics/tfb_draw.h"
    "src/libs/graphics/tfb_prim.cpp"
    "src/libs/graphics/tfb_prim.h"
    "src/libs/graphics/widgets.cpp"
    "src/libs/graphics/widgets.h"
)
source_group("Source Files\\libs\\graphics" FILES ${Source_Files__libs__graphics})

set(Source_Files__libs__graphics__sdl
    "src/libs/graphics/sdl/2xscalers.cpp"
    "src/libs/graphics/sdl/2xscalers.h"
    "src/libs/graphics/sdl/2xscalers_3dnow.cpp"
    "src/libs/graphics/sdl/2xscalers_mmx.cpp"
    "src/libs/graphics/sdl/2xscalers_mmx.h"
    "src/libs/graphics/sdl/2xscalers_sse.cpp"
    "src/libs/graphics/sdl/biadv2x.cpp"
    "src/libs/graphics/sdl/bilinear2x.cpp"
    "src/libs/graphics/sdl/canvas.cpp"
    "src/libs/graphics/sdl/clipboard.cpp"
    "src/libs/graphics/sdl/hq2x.cpp"
    "src/libs/graphics/sdl/nearest2x.cpp"
    "src/libs/graphics/sdl/opengl.cpp"
    "src/libs/graphics/sdl/opengl.h"
    "src/libs/graphics/sdl/palette.cpp"
    "src/libs/graphics/sdl/palette.h"
    "src/libs/graphics/sdl/png2sdl.cpp"
    "src/libs/graphics/sdl/png2sdl.h"
    "src/libs/graphics/sdl/primitives.cpp"
    "src/libs/graphics/sdl/primitives.h"
    "src/libs/graphics/sdl/pure.cpp"
    "src/libs/graphics/sdl/pure.h"
    "src/libs/graphics/sdl/rotozoom.cpp"
    "src/libs/graphics/sdl/rotozoom.h"
    "src/libs/graphics/sdl/scaleint.h"
    "src/libs/graphics/sdl/scalemmx.h"
    "src/libs/graphics/sdl/scalers.cpp"
    "src/libs/graphics/sdl/scalers.h"
    "src/libs/graphics/sdl/sdl1_common.cpp"
    "src/libs/graphics/sdl/sdl2_common.cpp"
    "src/libs/graphics/sdl/sdl2_pure.cpp"
    "src/libs/graphics/sdl/sdl_common.cpp"
    "src/libs/graphics/sdl/sdl_common.h"
    "src/libs/graphics/sdl/sdluio.cpp"
    "src/libs/graphics/sdl/sdluio.h"
    "src/libs/graphics/sdl/triscan2x.cpp"
)
source_group("Source Files\\libs\\graphics\\sdl" FILES ${Source_Files__libs__graphics__sdl})

set(Source_Files__libs__heap
    "src/libs/heap/heap.cpp"
    "src/libs/heap/heap.h"
)
source_group("Source Files\\libs\\heap" FILES ${Source_Files__libs__heap})

set(Source_Files__libs__input
    "src/libs/input/inpintrn.h"
    "src/libs/input/input_common.cpp"
    "src/libs/input/input_common.h"
)
source_group("Source Files\\libs\\input" FILES ${Source_Files__libs__input})

set(Source_Files__libs__input__sdl_No._1
    "src/libs/input/sdl/input.cpp"
    "src/libs/input/sdl/input.h"
    "src/libs/input/sdl/keynames.cpp"
    "src/libs/input/sdl/keynames.h"
    "src/libs/input/sdl/vcontrol.cpp"
    "src/libs/input/sdl/vcontrol.h"
)
source_group("Source Files\\libs\\input\\sdl No. 1" FILES ${Source_Files__libs__input__sdl_No._1})

set(Source_Files__libs__list
    "src/libs/list/list.cpp"
    "src/libs/list/list.h"
)
source_group("Source Files\\libs\\list" FILES ${Source_Files__libs__list})

set(Source_Files__libs__log
    "src/libs/log/loginternal.h"
    "src/libs/log/msgbox.h"
    "src/libs/log/msgbox_win.cpp"
    "src/libs/log/uqmlog.cpp"
    "src/libs/log/uqmlog.h"
)
source_group("Source Files\\libs\\log" FILES ${Source_Files__libs__log})

set(Source_Files__libs__lua
    "src/libs/lua/lapi.cpp"
    "src/libs/lua/lapi.h"
    "src/libs/lua/lauxlib.cpp"
    "src/libs/lua/lauxlib.h"
    "src/libs/lua/lbaselib.cpp"
    "src/libs/lua/lbitlib.cpp"
    "src/libs/lua/lcode.cpp"
    "src/libs/lua/lcode.h"
    "src/libs/lua/lctype.cpp"
    "src/libs/lua/lctype.h"
    "src/libs/lua/ldebug.cpp"
    "src/libs/lua/ldebug.h"
    "src/libs/lua/ldo.cpp"
    "src/libs/lua/ldo.h"
    "src/libs/lua/ldump.cpp"
    "src/libs/lua/lfunc.cpp"
    "src/libs/lua/lfunc.h"
    "src/libs/lua/lgc.cpp"
    "src/libs/lua/lgc.h"
    "src/libs/lua/llex.cpp"
    "src/libs/lua/llex.h"
    "src/libs/lua/llimits.h"
    "src/libs/lua/lmathlib.cpp"
    "src/libs/lua/lmem.cpp"
    "src/libs/lua/lmem.h"
    "src/libs/lua/lobject.cpp"
    "src/libs/lua/lobject.h"
    "src/libs/lua/lopcodes.cpp"
    "src/libs/lua/lopcodes.h"
    "src/libs/lua/lparser.cpp"
    "src/libs/lua/lparser.h"
    "src/libs/lua/lstate.cpp"
    "src/libs/lua/lstate.h"
    "src/libs/lua/lstring.cpp"
    "src/libs/lua/lstring.h"
    "src/libs/lua/lstrlib.cpp"
    "src/libs/lua/ltable.cpp"
    "src/libs/lua/ltable.h"
    "src/libs/lua/ltablib.cpp"
    "src/libs/lua/ltm.cpp"
    "src/libs/lua/ltm.h"
    "src/libs/lua/lua.h"
    "src/libs/lua/luaconf.h"
    "src/libs/lua/lualib.h"
    "src/libs/lua/lundump.cpp"
    "src/libs/lua/lundump.h"
    "src/libs/lua/lvm.cpp"
    "src/libs/lua/lvm.h"
    "src/libs/lua/lzio.cpp"
    "src/libs/lua/lzio.h"
)
source_group("Source Files\\libs\\lua" FILES ${Source_Files__libs__lua})

set(Source_Files__libs__luauqm
    "src/libs/luauqm/luauqm.cpp"
    "src/libs/luauqm/luauqm.h"
    "src/libs/luauqm/scriptres.cpp"
    "src/libs/luauqm/scriptres.h"
)
source_group("Source Files\\libs\\luauqm" FILES ${Source_Files__libs__luauqm})

set(Source_Files__libs__math
    "src/libs/math/mthintrn.h"
    "src/libs/math/random.cpp"
    "src/libs/math/random.h"
    "src/libs/math/random2.cpp"
    "src/libs/math/sqrt.cpp"
)
source_group("Source Files\\libs\\math" FILES ${Source_Files__libs__math})

set(Source_Files__libs__md5
    "src/libs/md5/md5.cpp"
    "src/libs/md5/md5.h"
)
source_group("Source Files\\libs\\md5" FILES ${Source_Files__libs__md5})

set(Source_Files__libs__memory
    "src/libs/memory/w_memlib.cpp"
)
source_group("Source Files\\libs\\memory" FILES ${Source_Files__libs__memory})

set(Source_Files__libs__mikmod
    "src/libs/mikmod/drv_nos.cpp"
    "src/libs/mikmod/load_it.cpp"
    "src/libs/mikmod/load_mod.cpp"
    "src/libs/mikmod/load_s3m.cpp"
    "src/libs/mikmod/load_stm.cpp"
    "src/libs/mikmod/load_xm.cpp"
    "src/libs/mikmod/mdreg.cpp"
    "src/libs/mikmod/mdriver.cpp"
    "src/libs/mikmod/mikmod.h"
    "src/libs/mikmod/mikmod_build.h"
    "src/libs/mikmod/mikmod_internals.h"
    "src/libs/mikmod/mloader.cpp"
    "src/libs/mikmod/mlreg.cpp"
    "src/libs/mikmod/mlutil.cpp"
    "src/libs/mikmod/mmalloc.cpp"
    "src/libs/mikmod/mmerror.cpp"
    "src/libs/mikmod/mmio.cpp"
    "src/libs/mikmod/mplayer.cpp"
    "src/libs/mikmod/munitrk.cpp"
    "src/libs/mikmod/mwav.cpp"
    "src/libs/mikmod/npertab.cpp"
    "src/libs/mikmod/sloader.cpp"
    "src/libs/mikmod/virtch.cpp"
    "src/libs/mikmod/virtch2.cpp"
    "src/libs/mikmod/virtch_common.cpp"
)
source_group("Source Files\\libs\\mikmod" FILES ${Source_Files__libs__mikmod})

set(Source_Files__libs__network
    "src/libs/network/bytesex.h"
    "src/libs/network/netport.cpp"
    "src/libs/network/netport.h"
    "src/libs/network/network.h"
    "src/libs/network/network_win.cpp"
    "src/libs/network/wspiapiwrap.cpp"
    "src/libs/network/wspiapiwrap.h"
)
source_group("Source Files\\libs\\network" FILES ${Source_Files__libs__network})

set(Source_Files__libs__network__connect
    "src/libs/network/connect/connect.cpp"
    "src/libs/network/connect/connect.h"
    "src/libs/network/connect/listen.cpp"
    "src/libs/network/connect/listen.h"
    "src/libs/network/connect/resolve.cpp"
    "src/libs/network/connect/resolve.h"
)
source_group("Source Files\\libs\\network\\connect" FILES ${Source_Files__libs__network__connect})

set(Source_Files__libs__network__netmanager
    "src/libs/network/netmanager/ndesc.cpp"
    "src/libs/network/netmanager/ndesc.h"
    "src/libs/network/netmanager/ndindex.ci"
    "src/libs/network/netmanager/netmanager.h"
    "src/libs/network/netmanager/netmanager_common.ci"
    "src/libs/network/netmanager/netmanager_win.cpp"
    "src/libs/network/netmanager/netmanager_win.h"
)
source_group("Source Files\\libs\\network\\netmanager" FILES ${Source_Files__libs__network__netmanager})

set(Source_Files__libs__network__socket
    "src/libs/network/socket/socket.cpp"
    "src/libs/network/socket/socket.h"
    "src/libs/network/socket/socket_win.cpp"
    "src/libs/network/socket/socket_win.h"
)
source_group("Source Files\\libs\\network\\socket" FILES ${Source_Files__libs__network__socket})

set(Source_Files__libs__resource
    "src/libs/resource/direct.cpp"
    "src/libs/resource/filecntl.cpp"
    "src/libs/resource/getres.cpp"
    "src/libs/resource/index.h"
    "src/libs/resource/loadres.cpp"
    "src/libs/resource/propfile.cpp"
    "src/libs/resource/propfile.h"
    "src/libs/resource/resinit.cpp"
    "src/libs/resource/resintrn.h"
    "src/libs/resource/stringbank.cpp"
    "src/libs/resource/stringbank.h"
)
source_group("Source Files\\libs\\resource" FILES ${Source_Files__libs__resource})

set(Source_Files__libs__sound
    "src/libs/sound/audiocore.cpp"
    "src/libs/sound/audiocore.h"
    "src/libs/sound/fileinst.cpp"
    "src/libs/sound/music.cpp"
    "src/libs/sound/resinst.cpp"
    "src/libs/sound/sfx.cpp"
    "src/libs/sound/sndintrn.h"
    "src/libs/sound/sound.cpp"
    "src/libs/sound/sound.h"
    "src/libs/sound/stream.cpp"
    "src/libs/sound/stream.h"
    "src/libs/sound/trackint.h"
    "src/libs/sound/trackplayer.cpp"
    "src/libs/sound/trackplayer.h"
)
source_group("Source Files\\libs\\sound" FILES ${Source_Files__libs__sound})

set(Source_Files__libs__sound__decoders
    "src/libs/sound/decoders/aiffaud.cpp"
    "src/libs/sound/decoders/aiffaud.h"
    "src/libs/sound/decoders/decoder.cpp"
    "src/libs/sound/decoders/decoder.h"
    "src/libs/sound/decoders/dukaud.cpp"
    "src/libs/sound/decoders/dukaud.h"
    "src/libs/sound/decoders/modaud.cpp"
    "src/libs/sound/decoders/modaud.h"
    "src/libs/sound/decoders/oggaud.cpp"
    "src/libs/sound/decoders/oggaud.h"
    "src/libs/sound/decoders/wav.cpp"
    "src/libs/sound/decoders/wav.h"
)
source_group("Source Files\\libs\\sound\\decoders" FILES ${Source_Files__libs__sound__decoders})

set(Source_Files__libs__sound__mixer
    "src/libs/sound/mixer/mixer.cpp"
    "src/libs/sound/mixer/mixer.h"
    "src/libs/sound/mixer/mixerint.h"
)
source_group("Source Files\\libs\\sound\\mixer" FILES ${Source_Files__libs__sound__mixer})

set(Source_Files__libs__sound__mixer__mixsdl
    "src/libs/sound/mixer/sdl/audiodrv_sdl.cpp"
    "src/libs/sound/mixer/sdl/audiodrv_sdl.h"
)
source_group("Source Files\\libs\\sound\\mixer\\mixsdl" FILES ${Source_Files__libs__sound__mixer__mixsdl})

set(Source_Files__libs__sound__mixer__nosound
    "src/libs/sound/mixer/nosound/audiodrv_nosound.cpp"
    "src/libs/sound/mixer/nosound/audiodrv_nosound.h"
)
source_group("Source Files\\libs\\sound\\mixer\\nosound" FILES ${Source_Files__libs__sound__mixer__nosound})

set(Source_Files__libs__sound__openal
    "src/libs/sound/openal/audiodrv_openal.cpp"
    "src/libs/sound/openal/audiodrv_openal.h"
)
source_group("Source Files\\libs\\sound\\openal" FILES ${Source_Files__libs__sound__openal})

set(Source_Files__libs__strings
    "src/libs/strings/getstr.cpp"
    "src/libs/strings/sfileins.cpp"
    "src/libs/strings/sresins.cpp"
    "src/libs/strings/stringhashtable.cpp"
    "src/libs/strings/stringhashtable.h"
    "src/libs/strings/strings.cpp"
    "src/libs/strings/strintrn.h"
    "src/libs/strings/unicode.cpp"
)
source_group("Source Files\\libs\\strings" FILES ${Source_Files__libs__strings})

set(Source_Files__libs__task
    "src/libs/task/tasklib.cpp"
)
source_group("Source Files\\libs\\task" FILES ${Source_Files__libs__task})

set(Source_Files__libs__threads
    "src/libs/threads/thrcommon.cpp"
    "src/libs/threads/thrcommon.h"
)
source_group("Source Files\\libs\\threads" FILES ${Source_Files__libs__threads})

set(Source_Files__libs__threads__sdl_No._3
    "src/libs/threads/sdl/sdlthreads.cpp"
    "src/libs/threads/sdl/sdlthreads.h"
)
source_group("Source Files\\libs\\threads\\sdl No. 3" FILES ${Source_Files__libs__threads__sdl_No._3})

set(Source_Files__libs__time
    "src/libs/time/timecommon.cpp"
    "src/libs/time/timecommon.h"
)
source_group("Source Files\\libs\\time" FILES ${Source_Files__libs__time})

set(Source_Files__libs__time__sdl_No._4
    "src/libs/time/sdl/sdltime.cpp"
    "src/libs/time/sdl/sdltime.h"
)
source_group("Source Files\\libs\\time\\sdl No. 4" FILES ${Source_Files__libs__time__sdl_No._4})

set(Source_Files__libs__uio
    "src/libs/uio/charhashtable.cpp"
    "src/libs/uio/charhashtable.h"
#    "src/libs/uio/debug.cpp"
    "src/libs/uio/debug.h"
    "src/libs/uio/defaultfs.cpp"
    "src/libs/uio/defaultfs.h"
    "src/libs/uio/fileblock.cpp"
    "src/libs/uio/fileblock.h"
    "src/libs/uio/fstypes.cpp"
    "src/libs/uio/fstypes.h"
    "src/libs/uio/getint.h"
    "src/libs/uio/gphys.cpp"
    "src/libs/uio/gphys.h"
#    "src/libs/uio/hashtable.cpp"
    "src/libs/uio/hashtable.h"
    "src/libs/uio/io.cpp"
    "src/libs/uio/io.h"
    "src/libs/uio/ioaux.cpp"
    "src/libs/uio/ioaux.h"
    "src/libs/uio/iointrn.h"
    "src/libs/uio/match.cpp"
    "src/libs/uio/match.h"
    "src/libs/uio/mem.h"
#    "src/libs/uio/memdebug.cpp"
    "src/libs/uio/memdebug.h"
    "src/libs/uio/mount.cpp"
    "src/libs/uio/mount.h"
    "src/libs/uio/mounttree.cpp"
    "src/libs/uio/mounttree.h"
    "src/libs/uio/paths.cpp"
    "src/libs/uio/paths.h"
    "src/libs/uio/physical.cpp"
    "src/libs/uio/physical.h"
    "src/libs/uio/types.h"
    "src/libs/uio/uioport.h"
    "src/libs/uio/uiostream.cpp"
    "src/libs/uio/uiostream.h"
    "src/libs/uio/uioutils.cpp"
    "src/libs/uio/uioutils.h"
    "src/libs/uio/utils.cpp"
    "src/libs/uio/utils.h"
)
source_group("Source Files\\libs\\uio" FILES ${Source_Files__libs__uio})

set(Source_Files__libs__uio__stdio
    "src/libs/uio/stdio/stdio.cpp"
    "src/libs/uio/stdio/stdio.h"
)
source_group("Source Files\\libs\\uio\\stdio" FILES ${Source_Files__libs__uio__stdio})

set(Source_Files__libs__uio__zip
    "src/libs/uio/zip/zip.cpp"
    "src/libs/uio/zip/zip.h"
)
source_group("Source Files\\libs\\uio\\zip" FILES ${Source_Files__libs__uio__zip})

set(Source_Files__libs__video
    "src/libs/video/dukvid.cpp"
    "src/libs/video/dukvid.h"
    "src/libs/video/legacyplayer.cpp"
    "src/libs/video/vfileins.cpp"
    "src/libs/video/video.cpp"
    "src/libs/video/video.h"
    "src/libs/video/videodec.cpp"
    "src/libs/video/videodec.h"
    "src/libs/video/vidintrn.h"
    "src/libs/video/vidplayer.cpp"
    "src/libs/video/vidplayer.h"
    "src/libs/video/vresins.cpp"
)
source_group("Source Files\\libs\\video" FILES ${Source_Files__libs__video})

set(Source_Files__uqm
    "src/uqm/battle.cpp"
    "src/uqm/battle.h"
    "src/uqm/battlecontrols.cpp"
    "src/uqm/battlecontrols.h"
    "src/uqm/border.cpp"
    "src/uqm/build.cpp"
    "src/uqm/build.h"
    "src/uqm/cleanup.cpp"
    "src/uqm/clock.cpp"
    "src/uqm/clock.h"
    "src/uqm/cnctdlg.cpp"
    "src/uqm/cnctdlg.h"
    "src/uqm/coderes.h"
    "src/uqm/collide.cpp"
    "src/uqm/collide.h"
    "src/uqm/colors.h"
    "src/uqm/comm.cpp"
    "src/uqm/comm.h"
    "src/uqm/commanim.cpp"
    "src/uqm/commanim.h"
    "src/uqm/commglue.cpp"
    "src/uqm/commglue.h"
    "src/uqm/confirm.cpp"
    "src/uqm/cons_res.cpp"
    "src/uqm/cons_res.h"
    "src/uqm/controls.h"
    "src/uqm/corecode.h"
    "src/uqm/credits.cpp"
    "src/uqm/credits.h"
    "src/uqm/cyborg.cpp"
    "src/uqm/demo.h"
    "src/uqm/displist.cpp"
    "src/uqm/displist.h"
    "src/uqm/dummy.cpp"
    "src/uqm/dummy.h"
    "src/uqm/element.h"
    "src/uqm/encount.cpp"
    "src/uqm/encount.h"
    "src/uqm/flash.cpp"
    "src/uqm/flash.h"
    "src/uqm/fmv.cpp"
    "src/uqm/fmv.h"
    "src/uqm/galaxy.cpp"
    "src/uqm/gameev.cpp"
    "src/uqm/gameev.h"
    "src/uqm/gameinp.cpp"
    "src/uqm/gameopt.cpp"
    "src/uqm/gameopt.h"
    "src/uqm/gamestr.h"
    "src/uqm/gendef.cpp"
    "src/uqm/gendef.h"
    "src/uqm/getchar.cpp"
    "src/uqm/globdata.cpp"
    "src/uqm/globdata.h"
    "src/uqm/gravity.cpp"
    "src/uqm/grpinfo.cpp"
    "src/uqm/grpinfo.h"
    "src/uqm/grpintrn.h"
    "src/uqm/hyper.cpp"
    "src/uqm/hyper.h"
    "src/uqm/ifontres.h"
    "src/uqm/igfxres.h"
    "src/uqm/ikey_con.h"
    "src/uqm/imusicre.h"
    "src/uqm/init.cpp"
    "src/uqm/init.h"
    "src/uqm/intel.cpp"
    "src/uqm/intel.h"
    "src/uqm/intro.cpp"
    "src/uqm/ipdisp.cpp"
    "src/uqm/ipdisp.h"
    "src/uqm/isndres.h"
    "src/uqm/istrtab.h"
    "src/uqm/load.cpp"
    "src/uqm/load_legacy.cpp"
    "src/uqm/loadship.cpp"
    "src/uqm/master.cpp"
    "src/uqm/master.h"
    "src/uqm/menu.cpp"
    "src/uqm/menustat.h"
    "src/uqm/misc.cpp"
    "src/uqm/nameref.h"
    "src/uqm/oscill.cpp"
    "src/uqm/oscill.h"
    "src/uqm/outfit.cpp"
    "src/uqm/pickship.cpp"
    "src/uqm/pickship.h"
    "src/uqm/process.cpp"
    "src/uqm/process.h"
    "src/uqm/races.h"
    "src/uqm/resinst.h"
    "src/uqm/restart.cpp"
    "src/uqm/restart.h"
    "src/uqm/save.cpp"
    "src/uqm/save.h"
    "src/uqm/settings.cpp"
    "src/uqm/settings.h"
    "src/uqm/setup.cpp"
    "src/uqm/setup.h"
    "src/uqm/setupmenu.cpp"
    "src/uqm/setupmenu.h"
    "src/uqm/ship.cpp"
    "src/uqm/ship.h"
    "src/uqm/shipcont.h"
    "src/uqm/shipstat.cpp"
    "src/uqm/shipyard.cpp"
    "src/uqm/sis.cpp"
    "src/uqm/sis.h"
    "src/uqm/sounds.cpp"
    "src/uqm/sounds.h"
    "src/uqm/starbase.cpp"
    "src/uqm/starbase.h"
    "src/uqm/starcon.cpp"
    "src/uqm/starcon.h"
    "src/uqm/starmap.cpp"
    "src/uqm/starmap.h"
    "src/uqm/StarmapGlobalData.h"
    "src/uqm/state.cpp"
    "src/uqm/state.h"
    "src/uqm/status.cpp"
    "src/uqm/status.h"
    "src/uqm/tactrans.cpp"
    "src/uqm/tactrans.h"
    "src/uqm/trans.cpp"
    "src/uqm/units.h"
    "src/uqm/uqmdebug.cpp"
    "src/uqm/uqmdebug.h"
    "src/uqm/util.cpp"
    "src/uqm/util.h"
    "src/uqm/velocity.cpp"
    "src/uqm/velocity.h"
    "src/uqm/weapon.cpp"
    "src/uqm/weapon.h"
)
source_group("Source Files\\uqm" FILES ${Source_Files__uqm})

set(Source_Files__uqm__comm
    "src/uqm/comm/commall.h"
)
source_group("Source Files\\uqm\\comm" FILES ${Source_Files__uqm__comm})

set(Source_Files__uqm__comm__arilou.comm
    "src/uqm/comm/arilou/arilouc.cpp"
    "src/uqm/comm/arilou/resinst.h"
    "src/uqm/comm/arilou/strings.h"
)
source_group("Source Files\\uqm\\comm\\arilou.comm" FILES ${Source_Files__uqm__comm__arilou.comm})

set(Source_Files__uqm__comm__blackur.comm
    "src/uqm/comm/blackur/blackurc.cpp"
    "src/uqm/comm/blackur/resinst.h"
    "src/uqm/comm/blackur/strings.h"
)
source_group("Source Files\\uqm\\comm\\blackur.comm" FILES ${Source_Files__uqm__comm__blackur.comm})

set(Source_Files__uqm__comm__chmmr.comm
    "src/uqm/comm/chmmr/chmmrc.cpp"
    "src/uqm/comm/chmmr/resinst.h"
    "src/uqm/comm/chmmr/strings.h"
)
source_group("Source Files\\uqm\\comm\\chmmr.comm" FILES ${Source_Files__uqm__comm__chmmr.comm})

set(Source_Files__uqm__comm__comandr.comm
    "src/uqm/comm/comandr/comandr.cpp"
    "src/uqm/comm/comandr/resinst.h"
    "src/uqm/comm/comandr/strings.h"
)
source_group("Source Files\\uqm\\comm\\comandr.comm" FILES ${Source_Files__uqm__comm__comandr.comm})

set(Source_Files__uqm__comm__druuge.comm
    "src/uqm/comm/druuge/druugec.cpp"
    "src/uqm/comm/druuge/resinst.h"
    "src/uqm/comm/druuge/strings.h"
)
source_group("Source Files\\uqm\\comm\\druuge.comm" FILES ${Source_Files__uqm__comm__druuge.comm})

set(Source_Files__uqm__comm__ilwrath.comm
    "src/uqm/comm/ilwrath/ilwrathc.cpp"
    "src/uqm/comm/ilwrath/resinst.h"
    "src/uqm/comm/ilwrath/strings.h"
)
source_group("Source Files\\uqm\\comm\\ilwrath.comm" FILES ${Source_Files__uqm__comm__ilwrath.comm})

set(Source_Files__uqm__comm__melnorm.comm
    "src/uqm/comm/melnorm/melnorm.cpp"
    "src/uqm/comm/melnorm/resinst.h"
    "src/uqm/comm/melnorm/strings.h"
)
source_group("Source Files\\uqm\\comm\\melnorm.comm" FILES ${Source_Files__uqm__comm__melnorm.comm})

set(Source_Files__uqm__comm__mycon.comm
    "src/uqm/comm/mycon/myconc.cpp"
    "src/uqm/comm/mycon/resinst.h"
    "src/uqm/comm/mycon/strings.h"
)
source_group("Source Files\\uqm\\comm\\mycon.comm" FILES ${Source_Files__uqm__comm__mycon.comm})

set(Source_Files__uqm__comm__orz.comm
    "src/uqm/comm/orz/orzc.cpp"
    "src/uqm/comm/orz/resinst.h"
    "src/uqm/comm/orz/strings.h"
)
source_group("Source Files\\uqm\\comm\\orz.comm" FILES ${Source_Files__uqm__comm__orz.comm})

set(Source_Files__uqm__comm__pkunk.comm
    "src/uqm/comm/pkunk/pkunkc.cpp"
    "src/uqm/comm/pkunk/resinst.h"
    "src/uqm/comm/pkunk/strings.h"
)
source_group("Source Files\\uqm\\comm\\pkunk.comm" FILES ${Source_Files__uqm__comm__pkunk.comm})

set(Source_Files__uqm__comm__rebel.comm
    "src/uqm/comm/rebel/rebel.cpp"
    "src/uqm/comm/rebel/strings.h"
)
source_group("Source Files\\uqm\\comm\\rebel.comm" FILES ${Source_Files__uqm__comm__rebel.comm})

set(Source_Files__uqm__comm__shofixt.comm
    "src/uqm/comm/shofixt/resinst.h"
    "src/uqm/comm/shofixt/shofixt.cpp"
    "src/uqm/comm/shofixt/strings.h"
)
source_group("Source Files\\uqm\\comm\\shofixt.comm" FILES ${Source_Files__uqm__comm__shofixt.comm})

set(Source_Files__uqm__comm__slyhome.comm
    "src/uqm/comm/slyhome/resinst.h"
    "src/uqm/comm/slyhome/slyhome.cpp"
    "src/uqm/comm/slyhome/strings.h"
)
source_group("Source Files\\uqm\\comm\\slyhome.comm" FILES ${Source_Files__uqm__comm__slyhome.comm})

set(Source_Files__uqm__comm__slyland.comm
    "src/uqm/comm/slyland/resinst.h"
    "src/uqm/comm/slyland/slyland.cpp"
    "src/uqm/comm/slyland/strings.h"
)
source_group("Source Files\\uqm\\comm\\slyland.comm" FILES ${Source_Files__uqm__comm__slyland.comm})

set(Source_Files__uqm__comm__spahome.comm
    "src/uqm/comm/spahome/spahome.cpp"
    "src/uqm/comm/spahome/strings.h"
)
source_group("Source Files\\uqm\\comm\\spahome.comm" FILES ${Source_Files__uqm__comm__spahome.comm})

set(Source_Files__uqm__comm__spathi.comm
    "src/uqm/comm/spathi/resinst.h"
    "src/uqm/comm/spathi/spathic.cpp"
    "src/uqm/comm/spathi/strings.h"
)
source_group("Source Files\\uqm\\comm\\spathi.comm" FILES ${Source_Files__uqm__comm__spathi.comm})

set(Source_Files__uqm__comm__starbas.comm
    "src/uqm/comm/starbas/starbas.cpp"
    "src/uqm/comm/starbas/strings.h"
)
source_group("Source Files\\uqm\\comm\\starbas.comm" FILES ${Source_Files__uqm__comm__starbas.comm})

set(Source_Files__uqm__comm__supox.comm
    "src/uqm/comm/supox/resinst.h"
    "src/uqm/comm/supox/strings.h"
    "src/uqm/comm/supox/supoxc.cpp"
)
source_group("Source Files\\uqm\\comm\\supox.comm" FILES ${Source_Files__uqm__comm__supox.comm})

set(Source_Files__uqm__comm__syreen.comm
    "src/uqm/comm/syreen/resinst.h"
    "src/uqm/comm/syreen/strings.h"
    "src/uqm/comm/syreen/syreenc.cpp"
)
source_group("Source Files\\uqm\\comm\\syreen.comm" FILES ${Source_Files__uqm__comm__syreen.comm})

set(Source_Files__uqm__comm__talkpet.comm
    "src/uqm/comm/talkpet/resinst.h"
    "src/uqm/comm/talkpet/strings.h"
    "src/uqm/comm/talkpet/talkpet.cpp"
)
source_group("Source Files\\uqm\\comm\\talkpet.comm" FILES ${Source_Files__uqm__comm__talkpet.comm})

set(Source_Files__uqm__comm__thradd.comm
    "src/uqm/comm/thradd/resinst.h"
    "src/uqm/comm/thradd/strings.h"
    "src/uqm/comm/thradd/thraddc.cpp"
)
source_group("Source Files\\uqm\\comm\\thradd.comm" FILES ${Source_Files__uqm__comm__thradd.comm})

set(Source_Files__uqm__comm__umgah.comm
    "src/uqm/comm/umgah/resinst.h"
    "src/uqm/comm/umgah/strings.h"
    "src/uqm/comm/umgah/umgahc.cpp"
)
source_group("Source Files\\uqm\\comm\\umgah.comm" FILES ${Source_Files__uqm__comm__umgah.comm})

set(Source_Files__uqm__comm__urquan.comm
    "src/uqm/comm/urquan/resinst.h"
    "src/uqm/comm/urquan/strings.h"
    "src/uqm/comm/urquan/urquanc.cpp"
)
source_group("Source Files\\uqm\\comm\\urquan.comm" FILES ${Source_Files__uqm__comm__urquan.comm})

set(Source_Files__uqm__comm__utwig.comm
    "src/uqm/comm/utwig/resinst.h"
    "src/uqm/comm/utwig/strings.h"
    "src/uqm/comm/utwig/utwigc.cpp"
)
source_group("Source Files\\uqm\\comm\\utwig.comm" FILES ${Source_Files__uqm__comm__utwig.comm})

set(Source_Files__uqm__comm__vux.comm
    "src/uqm/comm/vux/resinst.h"
    "src/uqm/comm/vux/strings.h"
    "src/uqm/comm/vux/vuxc.cpp"
)
source_group("Source Files\\uqm\\comm\\vux.comm" FILES ${Source_Files__uqm__comm__vux.comm})

set(Source_Files__uqm__comm__yehat.comm
    "src/uqm/comm/yehat/resinst.h"
    "src/uqm/comm/yehat/strings.h"
    "src/uqm/comm/yehat/yehatc.cpp"
)
source_group("Source Files\\uqm\\comm\\yehat.comm" FILES ${Source_Files__uqm__comm__yehat.comm})

set(Source_Files__uqm__comm__zoqfot.comm
    "src/uqm/comm/zoqfot/resinst.h"
    "src/uqm/comm/zoqfot/strings.h"
    "src/uqm/comm/zoqfot/zoqfotc.cpp"
)
source_group("Source Files\\uqm\\comm\\zoqfot.comm" FILES ${Source_Files__uqm__comm__zoqfot.comm})

set(Source_Files__uqm__lua_28uqm29
    "src/uqm/lua/luacomm.cpp"
    "src/uqm/lua/luacomm.h"
    "src/uqm/lua/luadebug.cpp"
    "src/uqm/lua/luadebug.h"
    "src/uqm/lua/luaevent.cpp"
    "src/uqm/lua/luaevent.h"
    "src/uqm/lua/luainit.cpp"
    "src/uqm/lua/luainit.h"
    "src/uqm/lua/luastate.cpp"
    "src/uqm/lua/luastate.h"
)
source_group("Source Files\\uqm\\lua %28uqm%29" FILES ${Source_Files__uqm__lua_28uqm29})

set(Source_Files__uqm__lua_28uqm29__luafuncs
    "src/uqm/lua/luafuncs/commfuncs.cpp"
    "src/uqm/lua/luafuncs/commfuncs.h"
    "src/uqm/lua/luafuncs/customfuncs.cpp"
    "src/uqm/lua/luafuncs/customfuncs.h"
    "src/uqm/lua/luafuncs/eventfuncs.cpp"
    "src/uqm/lua/luafuncs/eventfuncs.h"
    "src/uqm/lua/luafuncs/logfuncs.cpp"
    "src/uqm/lua/luafuncs/logfuncs.h"
    "src/uqm/lua/luafuncs/statefuncs.cpp"
    "src/uqm/lua/luafuncs/statefuncs.h"
)
source_group("Source Files\\uqm\\lua %28uqm%29\\luafuncs" FILES ${Source_Files__uqm__lua_28uqm29__luafuncs})

set(Source_Files__uqm__planets
    "src/uqm/planets/calc.cpp"
    "src/uqm/planets/cargo.cpp"
    "src/uqm/planets/devices.cpp"
    "src/uqm/planets/elemdata.h"
    "src/uqm/planets/generate.h"
    "src/uqm/planets/gentopo.cpp"
    "src/uqm/planets/lander.cpp"
    "src/uqm/planets/lander.h"
    "src/uqm/planets/lifeform.h"
    "src/uqm/planets/orbits.cpp"
    "src/uqm/planets/oval.cpp"
    "src/uqm/planets/pl_stuff.cpp"
    "src/uqm/planets/plandata.h"
    "src/uqm/planets/planets.cpp"
    "src/uqm/planets/planets.h"
    "src/uqm/planets/plangen.cpp"
    "src/uqm/planets/pstarmap.cpp"
    "src/uqm/planets/report.cpp"
    "src/uqm/planets/roster.cpp"
    "src/uqm/planets/scan.cpp"
    "src/uqm/planets/scan.h"
    "src/uqm/planets/solarsys.cpp"
    "src/uqm/planets/solarsys.h"
    "src/uqm/planets/sundata.h"
    "src/uqm/planets/surface.cpp"
)
source_group("Source Files\\uqm\\planets" FILES ${Source_Files__uqm__planets})

set(Source_Files__uqm__planets__generate
    "src/uqm/planets/generate/genall.h"
    "src/uqm/planets/generate/genand.cpp"
    "src/uqm/planets/generate/genburv.cpp"
    "src/uqm/planets/generate/genchmmr.cpp"
    "src/uqm/planets/generate/gencol.cpp"
    "src/uqm/planets/generate/gendefault.cpp"
    "src/uqm/planets/generate/gendefault.h"
    "src/uqm/planets/generate/gendru.cpp"
    "src/uqm/planets/generate/genilw.cpp"
    "src/uqm/planets/generate/genmel.cpp"
    "src/uqm/planets/generate/genmyc.cpp"
    "src/uqm/planets/generate/genorz.cpp"
    "src/uqm/planets/generate/genpet.cpp"
    "src/uqm/planets/generate/genpku.cpp"
    "src/uqm/planets/generate/genrain.cpp"
    "src/uqm/planets/generate/gensam.cpp"
    "src/uqm/planets/generate/genshof.cpp"
    "src/uqm/planets/generate/gensly.cpp"
    "src/uqm/planets/generate/gensol.cpp"
    "src/uqm/planets/generate/genspa.cpp"
    "src/uqm/planets/generate/gensup.cpp"
    "src/uqm/planets/generate/gensyr.cpp"
    "src/uqm/planets/generate/genthrad.cpp"
    "src/uqm/planets/generate/gentrap.cpp"
    "src/uqm/planets/generate/genutw.cpp"
    "src/uqm/planets/generate/genvault.cpp"
    "src/uqm/planets/generate/genvux.cpp"
    "src/uqm/planets/generate/genwreck.cpp"
    "src/uqm/planets/generate/genyeh.cpp"
    "src/uqm/planets/generate/genzfpscout.cpp"
    "src/uqm/planets/generate/genzoq.cpp"
)
source_group("Source Files\\uqm\\planets\\generate" FILES ${Source_Files__uqm__planets__generate})

set(Source_Files__uqm__ships
    "src/uqm/ships/ship.h"
)
source_group("Source Files\\uqm\\ships" FILES ${Source_Files__uqm__ships})

set(Source_Files__uqm__ships__androsyn
    "src/uqm/ships/androsyn/androsyn.cpp"
    "src/uqm/ships/androsyn/androsyn.h"
    "src/uqm/ships/androsyn/icode.h"
    "src/uqm/ships/androsyn/resinst.h"
)
source_group("Source Files\\uqm\\ships\\androsyn" FILES ${Source_Files__uqm__ships__androsyn})

set(Source_Files__uqm__ships__arilou
    "src/uqm/ships/arilou/arilou.cpp"
    "src/uqm/ships/arilou/arilou.h"
    "src/uqm/ships/arilou/icode.h"
    "src/uqm/ships/arilou/resinst.h"
)
source_group("Source Files\\uqm\\ships\\arilou" FILES ${Source_Files__uqm__ships__arilou})

set(Source_Files__uqm__ships__blackurq
    "src/uqm/ships/blackurq/blackurq.cpp"
    "src/uqm/ships/blackurq/blackurq.h"
    "src/uqm/ships/blackurq/icode.h"
    "src/uqm/ships/blackurq/resinst.h"
)
source_group("Source Files\\uqm\\ships\\blackurq" FILES ${Source_Files__uqm__ships__blackurq})

set(Source_Files__uqm__ships__chenjesu
    "src/uqm/ships/chenjesu/chenjesu.cpp"
    "src/uqm/ships/chenjesu/chenjesu.h"
    "src/uqm/ships/chenjesu/icode.h"
    "src/uqm/ships/chenjesu/resinst.h"
)
source_group("Source Files\\uqm\\ships\\chenjesu" FILES ${Source_Files__uqm__ships__chenjesu})

set(Source_Files__uqm__ships__chmmr
    "src/uqm/ships/chmmr/chmmr.cpp"
    "src/uqm/ships/chmmr/chmmr.h"
    "src/uqm/ships/chmmr/icode.h"
    "src/uqm/ships/chmmr/resinst.h"
)
source_group("Source Files\\uqm\\ships\\chmmr" FILES ${Source_Files__uqm__ships__chmmr})

set(Source_Files__uqm__ships__druuge
    "src/uqm/ships/druuge/druuge.cpp"
    "src/uqm/ships/druuge/druuge.h"
    "src/uqm/ships/druuge/icode.h"
    "src/uqm/ships/druuge/resinst.h"
)
source_group("Source Files\\uqm\\ships\\druuge" FILES ${Source_Files__uqm__ships__druuge})

set(Source_Files__uqm__ships__human
    "src/uqm/ships/human/human.cpp"
    "src/uqm/ships/human/human.h"
    "src/uqm/ships/human/icode.h"
    "src/uqm/ships/human/resinst.h"
)
source_group("Source Files\\uqm\\ships\\human" FILES ${Source_Files__uqm__ships__human})

set(Source_Files__uqm__ships__ilwrath
    "src/uqm/ships/ilwrath/icode.h"
    "src/uqm/ships/ilwrath/ilwrath.cpp"
    "src/uqm/ships/ilwrath/ilwrath.h"
    "src/uqm/ships/ilwrath/resinst.h"
)
source_group("Source Files\\uqm\\ships\\ilwrath" FILES ${Source_Files__uqm__ships__ilwrath})

set(Source_Files__uqm__ships__lastbat
    "src/uqm/ships/lastbat/icode.h"
    "src/uqm/ships/lastbat/lastbat.cpp"
    "src/uqm/ships/lastbat/lastbat.h"
    "src/uqm/ships/lastbat/resinst.h"
)
source_group("Source Files\\uqm\\ships\\lastbat" FILES ${Source_Files__uqm__ships__lastbat})

set(Source_Files__uqm__ships__melnorme
    "src/uqm/ships/melnorme/icode.h"
    "src/uqm/ships/melnorme/melnorme.cpp"
    "src/uqm/ships/melnorme/melnorme.h"
    "src/uqm/ships/melnorme/resinst.h"
)
source_group("Source Files\\uqm\\ships\\melnorme" FILES ${Source_Files__uqm__ships__melnorme})

set(Source_Files__uqm__ships__mmrnmhrm
    "src/uqm/ships/mmrnmhrm/icode.h"
    "src/uqm/ships/mmrnmhrm/mmrnmhrm.cpp"
    "src/uqm/ships/mmrnmhrm/mmrnmhrm.h"
    "src/uqm/ships/mmrnmhrm/resinst.h"
)
source_group("Source Files\\uqm\\ships\\mmrnmhrm" FILES ${Source_Files__uqm__ships__mmrnmhrm})

set(Source_Files__uqm__ships__mycon
    "src/uqm/ships/mycon/icode.h"
    "src/uqm/ships/mycon/mycon.cpp"
    "src/uqm/ships/mycon/mycon.h"
    "src/uqm/ships/mycon/resinst.h"
)
source_group("Source Files\\uqm\\ships\\mycon" FILES ${Source_Files__uqm__ships__mycon})

set(Source_Files__uqm__ships__orz
    "src/uqm/ships/orz/icode.h"
    "src/uqm/ships/orz/orz.cpp"
    "src/uqm/ships/orz/orz.h"
    "src/uqm/ships/orz/resinst.h"
)
source_group("Source Files\\uqm\\ships\\orz" FILES ${Source_Files__uqm__ships__orz})

set(Source_Files__uqm__ships__pkunk
    "src/uqm/ships/pkunk/icode.h"
    "src/uqm/ships/pkunk/pkunk.cpp"
    "src/uqm/ships/pkunk/pkunk.h"
    "src/uqm/ships/pkunk/resinst.h"
)
source_group("Source Files\\uqm\\ships\\pkunk" FILES ${Source_Files__uqm__ships__pkunk})

set(Source_Files__uqm__ships__probe
    "src/uqm/ships/probe/icode.h"
    "src/uqm/ships/probe/probe.cpp"
    "src/uqm/ships/probe/probe.h"
    "src/uqm/ships/probe/resinst.h"
)
source_group("Source Files\\uqm\\ships\\probe" FILES ${Source_Files__uqm__ships__probe})

set(Source_Files__uqm__ships__shofixti
    "src/uqm/ships/shofixti/icode.h"
    "src/uqm/ships/shofixti/resinst.h"
    "src/uqm/ships/shofixti/shofixti.cpp"
    "src/uqm/ships/shofixti/shofixti.h"
)
source_group("Source Files\\uqm\\ships\\shofixti" FILES ${Source_Files__uqm__ships__shofixti})

set(Source_Files__uqm__ships__sis_ship
    "src/uqm/ships/sis_ship/icode.h"
    "src/uqm/ships/sis_ship/resinst.h"
    "src/uqm/ships/sis_ship/sis_ship.cpp"
    "src/uqm/ships/sis_ship/sis_ship.h"
)
source_group("Source Files\\uqm\\ships\\sis_ship" FILES ${Source_Files__uqm__ships__sis_ship})

set(Source_Files__uqm__ships__slylandr
    "src/uqm/ships/slylandr/icode.h"
    "src/uqm/ships/slylandr/resinst.h"
    "src/uqm/ships/slylandr/slylandr.cpp"
    "src/uqm/ships/slylandr/slylandr.h"
)
source_group("Source Files\\uqm\\ships\\slylandr" FILES ${Source_Files__uqm__ships__slylandr})

set(Source_Files__uqm__ships__spathi
    "src/uqm/ships/spathi/icode.h"
    "src/uqm/ships/spathi/resinst.h"
    "src/uqm/ships/spathi/spathi.cpp"
    "src/uqm/ships/spathi/spathi.h"
)
source_group("Source Files\\uqm\\ships\\spathi" FILES ${Source_Files__uqm__ships__spathi})

set(Source_Files__uqm__ships__supox
    "src/uqm/ships/supox/icode.h"
    "src/uqm/ships/supox/resinst.h"
    "src/uqm/ships/supox/supox.cpp"
    "src/uqm/ships/supox/supox.h"
)
source_group("Source Files\\uqm\\ships\\supox" FILES ${Source_Files__uqm__ships__supox})

set(Source_Files__uqm__ships__syreen
    "src/uqm/ships/syreen/icode.h"
    "src/uqm/ships/syreen/resinst.h"
    "src/uqm/ships/syreen/syreen.cpp"
    "src/uqm/ships/syreen/syreen.h"
)
source_group("Source Files\\uqm\\ships\\syreen" FILES ${Source_Files__uqm__ships__syreen})

set(Source_Files__uqm__ships__thradd
    "src/uqm/ships/thradd/icode.h"
    "src/uqm/ships/thradd/resinst.h"
    "src/uqm/ships/thradd/thradd.cpp"
    "src/uqm/ships/thradd/thradd.h"
)
source_group("Source Files\\uqm\\ships\\thradd" FILES ${Source_Files__uqm__ships__thradd})

set(Source_Files__uqm__ships__umgah
    "src/uqm/ships/umgah/icode.h"
    "src/uqm/ships/umgah/resinst.h"
    "src/uqm/ships/umgah/umgah.cpp"
    "src/uqm/ships/umgah/umgah.h"
)
source_group("Source Files\\uqm\\ships\\umgah" FILES ${Source_Files__uqm__ships__umgah})

set(Source_Files__uqm__ships__urquan
    "src/uqm/ships/urquan/icode.h"
    "src/uqm/ships/urquan/resinst.h"
    "src/uqm/ships/urquan/urquan.cpp"
    "src/uqm/ships/urquan/urquan.h"
)
source_group("Source Files\\uqm\\ships\\urquan" FILES ${Source_Files__uqm__ships__urquan})

set(Source_Files__uqm__ships__utwig
    "src/uqm/ships/utwig/icode.h"
    "src/uqm/ships/utwig/resinst.h"
    "src/uqm/ships/utwig/utwig.cpp"
    "src/uqm/ships/utwig/utwig.h"
)
source_group("Source Files\\uqm\\ships\\utwig" FILES ${Source_Files__uqm__ships__utwig})

set(Source_Files__uqm__ships__vux
    "src/uqm/ships/vux/icode.h"
    "src/uqm/ships/vux/resinst.h"
    "src/uqm/ships/vux/vux.cpp"
    "src/uqm/ships/vux/vux.h"
)
source_group("Source Files\\uqm\\ships\\vux" FILES ${Source_Files__uqm__ships__vux})

set(Source_Files__uqm__ships__yehat
    "src/uqm/ships/yehat/icode.h"
    "src/uqm/ships/yehat/resinst.h"
    "src/uqm/ships/yehat/yehat.cpp"
    "src/uqm/ships/yehat/yehat.h"
)
source_group("Source Files\\uqm\\ships\\yehat" FILES ${Source_Files__uqm__ships__yehat})

set(Source_Files__uqm__ships__zoqfot
    "src/uqm/ships/zoqfot/icode.h"
    "src/uqm/ships/zoqfot/resinst.h"
    "src/uqm/ships/zoqfot/zoqfot.cpp"
    "src/uqm/ships/zoqfot/zoqfot.h"
)
source_group("Source Files\\uqm\\ships\\zoqfot" FILES ${Source_Files__uqm__ships__zoqfot})

set(Source_Files__uqm__supermelee
    "src/uqm/supermelee/buildpick.cpp"
    "src/uqm/supermelee/buildpick.h"
    "src/uqm/supermelee/loadmele.cpp"
    "src/uqm/supermelee/loadmele.h"
    "src/uqm/supermelee/melee.cpp"
    "src/uqm/supermelee/melee.h"
    "src/uqm/supermelee/meleesetup.cpp"
    "src/uqm/supermelee/meleesetup.h"
    "src/uqm/supermelee/meleeship.h"
    "src/uqm/supermelee/pickmele.cpp"
    "src/uqm/supermelee/pickmele.h"
)
source_group("Source Files\\uqm\\supermelee" FILES ${Source_Files__uqm__supermelee})

set(Source_Files__uqm__supermelee__netplay
    "src/uqm/supermelee/netplay/checkbuf.cpp"
    "src/uqm/supermelee/netplay/checkbuf.h"
    "src/uqm/supermelee/netplay/checksum.cpp"
    "src/uqm/supermelee/netplay/checksum.h"
    "src/uqm/supermelee/netplay/crc.cpp"
    "src/uqm/supermelee/netplay/crc.h"
    "src/uqm/supermelee/netplay/nc_connect.ci"
    "src/uqm/supermelee/netplay/netconnection.cpp"
    "src/uqm/supermelee/netplay/netconnection.h"
    "src/uqm/supermelee/netplay/netinput.cpp"
    "src/uqm/supermelee/netplay/netinput.h"
    "src/uqm/supermelee/netplay/netmelee.cpp"
    "src/uqm/supermelee/netplay/netmelee.h"
    "src/uqm/supermelee/netplay/netmisc.cpp"
    "src/uqm/supermelee/netplay/netmisc.h"
    "src/uqm/supermelee/netplay/netoptions.cpp"
    "src/uqm/supermelee/netplay/netoptions.h"
    "src/uqm/supermelee/netplay/netplay.h"
    "src/uqm/supermelee/netplay/netrcv.cpp"
    "src/uqm/supermelee/netplay/netrcv.h"
    "src/uqm/supermelee/netplay/netsend.cpp"
    "src/uqm/supermelee/netplay/netsend.h"
    "src/uqm/supermelee/netplay/netstate.cpp"
    "src/uqm/supermelee/netplay/netstate.h"
    "src/uqm/supermelee/netplay/notify.cpp"
    "src/uqm/supermelee/netplay/notify.h"
    "src/uqm/supermelee/netplay/notifyall.cpp"
    "src/uqm/supermelee/netplay/notifyall.h"
    "src/uqm/supermelee/netplay/packet.cpp"
    "src/uqm/supermelee/netplay/packet.h"
    "src/uqm/supermelee/netplay/packethandlers.cpp"
    "src/uqm/supermelee/netplay/packethandlers.h"
    "src/uqm/supermelee/netplay/packetq.cpp"
    "src/uqm/supermelee/netplay/packetq.h"
    "src/uqm/supermelee/netplay/packetsenders.cpp"
    "src/uqm/supermelee/netplay/packetsenders.h"
)
source_group("Source Files\\uqm\\supermelee\\netplay" FILES ${Source_Files__uqm__supermelee__netplay})

set(Source_Files__uqm__supermelee__netplay__proto
    "src/uqm/supermelee/netplay/proto/npconfirm.cpp"
    "src/uqm/supermelee/netplay/proto/npconfirm.h"
    "src/uqm/supermelee/netplay/proto/ready.cpp"
    "src/uqm/supermelee/netplay/proto/ready.h"
    "src/uqm/supermelee/netplay/proto/reset.cpp"
    "src/uqm/supermelee/netplay/proto/reset.h"
)
source_group("Source Files\\uqm\\supermelee\\netplay\\proto" FILES ${Source_Files__uqm__supermelee__netplay__proto})

set(ALL_FILES
    ${Doc}
    ${Doc__Devel}
    ${Doc__Users}
    ${Resources}
    ${Source_Files}
    ${Source_Files___core__memory}
    ${Source_Files__getopt}
    ${Source_Files__libs}
    ${Source_Files__libs__callback}
    ${Source_Files__libs__decomp}
    ${Source_Files__libs__file}
    ${Source_Files__libs__graphics}
    ${Source_Files__libs__graphics__sdl}
    ${Source_Files__libs__heap}
    ${Source_Files__libs__input}
    ${Source_Files__libs__input__sdl_No._1}
    ${Source_Files__libs__list}
    ${Source_Files__libs__log}
    ${Source_Files__libs__lua}
    ${Source_Files__libs__luauqm}
    ${Source_Files__libs__math}
    ${Source_Files__libs__md5}
    ${Source_Files__libs__memory}
    ${Source_Files__libs__mikmod}
    ${Source_Files__libs__network}
    ${Source_Files__libs__network__connect}
    ${Source_Files__libs__network__netmanager}
    ${Source_Files__libs__network__socket}
    ${Source_Files__libs__resource}
    ${Source_Files__libs__sound}
    ${Source_Files__libs__sound__decoders}
    ${Source_Files__libs__sound__mixer}
    ${Source_Files__libs__sound__mixer__mixsdl}
    ${Source_Files__libs__sound__mixer__nosound}
    ${Source_Files__libs__sound__openal}
    ${Source_Files__libs__strings}
    ${Source_Files__libs__task}
    ${Source_Files__libs__threads}
    ${Source_Files__libs__threads__sdl_No._3}
    ${Source_Files__libs__time}
    ${Source_Files__libs__time__sdl_No._4}
    ${Source_Files__libs__uio}
    ${Source_Files__libs__uio__stdio}
    ${Source_Files__libs__uio__zip}
    ${Source_Files__libs__video}
    ${Source_Files__uqm}
    ${Source_Files__uqm__comm}
    ${Source_Files__uqm__comm__arilou.comm}
    ${Source_Files__uqm__comm__blackur.comm}
    ${Source_Files__uqm__comm__chmmr.comm}
    ${Source_Files__uqm__comm__comandr.comm}
    ${Source_Files__uqm__comm__druuge.comm}
    ${Source_Files__uqm__comm__ilwrath.comm}
    ${Source_Files__uqm__comm__melnorm.comm}
    ${Source_Files__uqm__comm__mycon.comm}
    ${Source_Files__uqm__comm__orz.comm}
    ${Source_Files__uqm__comm__pkunk.comm}
    ${Source_Files__uqm__comm__rebel.comm}
    ${Source_Files__uqm__comm__shofixt.comm}
    ${Source_Files__uqm__comm__slyhome.comm}
    ${Source_Files__uqm__comm__slyland.comm}
    ${Source_Files__uqm__comm__spahome.comm}
    ${Source_Files__uqm__comm__spathi.comm}
    ${Source_Files__uqm__comm__starbas.comm}
    ${Source_Files__uqm__comm__supox.comm}
    ${Source_Files__uqm__comm__syreen.comm}
    ${Source_Files__uqm__comm__talkpet.comm}
    ${Source_Files__uqm__comm__thradd.comm}
    ${Source_Files__uqm__comm__umgah.comm}
    ${Source_Files__uqm__comm__urquan.comm}
    ${Source_Files__uqm__comm__utwig.comm}
    ${Source_Files__uqm__comm__vux.comm}
    ${Source_Files__uqm__comm__yehat.comm}
    ${Source_Files__uqm__comm__zoqfot.comm}
    ${Source_Files__uqm__lua_28uqm29}
    ${Source_Files__uqm__lua_28uqm29__luafuncs}
    ${Source_Files__uqm__planets}
    ${Source_Files__uqm__planets__generate}
    ${Source_Files__uqm__ships}
    ${Source_Files__uqm__ships__androsyn}
    ${Source_Files__uqm__ships__arilou}
    ${Source_Files__uqm__ships__blackurq}
    ${Source_Files__uqm__ships__chenjesu}
    ${Source_Files__uqm__ships__chmmr}
    ${Source_Files__uqm__ships__druuge}
    ${Source_Files__uqm__ships__human}
    ${Source_Files__uqm__ships__ilwrath}
    ${Source_Files__uqm__ships__lastbat}
    ${Source_Files__uqm__ships__melnorme}
    ${Source_Files__uqm__ships__mmrnmhrm}
    ${Source_Files__uqm__ships__mycon}
    ${Source_Files__uqm__ships__orz}
    ${Source_Files__uqm__ships__pkunk}
    ${Source_Files__uqm__ships__probe}
    ${Source_Files__uqm__ships__shofixti}
    ${Source_Files__uqm__ships__sis_ship}
    ${Source_Files__uqm__ships__slylandr}
    ${Source_Files__uqm__ships__spathi}
    ${Source_Files__uqm__ships__supox}
    ${Source_Files__uqm__ships__syreen}
    ${Source_Files__uqm__ships__thradd}
    ${Source_Files__uqm__ships__umgah}
    ${Source_Files__uqm__ships__urquan}
    ${Source_Files__uqm__ships__utwig}
    ${Source_Files__uqm__ships__vux}
    ${Source_Files__uqm__ships__yehat}
    ${Source_Files__uqm__ships__zoqfot}
    ${Source_Files__uqm__supermelee}
    ${Source_Files__uqm__supermelee__netplay}
    ${Source_Files__uqm__supermelee__netplay__proto}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

################################################################################
# Dependencies
################################################################################

#one way of avoiding warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
#if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
#    cmake_policy(SET CMP0135 NEW)
#endif()

find_package (SDL2 QUIET)
if (SDL2_FOUND)
	message (STATUS "Found SDL2: ${SDL2_VERSION}")
else ()
	FetchSDL ()
	message (STATUS "Fetched SDL2: ${SDL2_VERSION}")
endif ()

find_package (ZLIB QUIET)
if (ZLIB_FOUND)
    message (STATUS "Found ZLIB: ${ZLIB_VERSION}")
else ()
    FetchZLIB ()
    message (STATUS "Fetched ZLIB: ${ZLIB_VERSION}")
endif ()

find_package (PNG QUIET)
if (PNG_FOUND)
	message (STATUS "Found libPNG: ${PNG_VERSION_STRING}")
else ()
	FetchPNG ()
	message (STATUS "Fetched libPNG: ${PNG_VERSION}")
endif ()


find_package (Ogg QUIET)
if (Ogg_FOUND)
	message (STATUS "Found ogg: ${Ogg_VERSION}")
else ()
	FetchOgg ()
	message (STATUS "Fetched ogg: ${OGG_VERSION}")
endif ()

find_package (Vorbis QUIET)
if (Vorbis_FOUND)
	message (STATUS "Found Vorbis: ${Vorbis_VERSION}")
	set (UQM_OGG_CODEC "standard")
else ()
	FetchVorbis ()
	message (STATUS "Fetched Vorbis: ${VORBIS_VERSION}")
endif ()

find_package(OpenAL)
if (OpenAL_FOUND)
    message (STATUS "Found OpenAL: ${OpenAL_VERSION}")
else()
    FetchOpenAL()
endif()


use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG       "${OUTPUT_DIRECTORY}$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    TARGET_NAME_RELEASE     "${OUTPUT_DIRECTORY}$<TARGET_FILE_NAME:${PROJECT_NAME}>"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG       "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_DIRECTORY_RELEASE     "${CMAKE_CURRENT_SOURCE_DIR}"
)
################################################################################
# Linker Language
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
    LINKER_LANGUAGE CXX
)
################################################################################
# MSVC runtime library
################################################################################
# get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
# string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
#     $<$<CONFIG:Debug>:
#         MultiThreadedDebugDLL
#     >
#     $<$<CONFIG:Release>:
#         MultiThreadedDLL
#     >cmd.exe /C 
#     $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
# )
# set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/regex"
    "${SDL2_INCLUDE_DIRS}"
	"${PNG_INCLUDE_DIRS}"
	"${ZLIB_INCLUDE_DIRS_UQM}"
    "${OGG_INCLUDE_DIRS}"
	"${VORBISFILE_INCLUDE_DIRS}"
    "${OPENAL_INCLUDE_DIRS}"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
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
    "ZLIB_DLL;"
    "USE_INTERNAL_MIKMOD;"
    "USE_INTERNAL_LUA;"
    "USE_PLATFORM_ACCEL;"
    "_CRT_SECURE_NO_WARNINGS;"
    "_MBCS;"
# required to suppress issue in SDL_endian.h regarding a redefinition of the _m_prefetch intrinsic under clang.
    "__PRFCHWINTRIN_H" 
)

################################################################################
# Compile and link options
################################################################################
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /RTC1;
            /Gy-;
            /W3;
            /fp:except-;
            /GR;
            /TP
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /GF;
            /Gy;
            /W2
        >
        /MP;
        /sdl-;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        /TP;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /NODEFAULTLIB:msvcrt.lib;
            /DEBUG;
            /SUBSYSTEM:CONSOLE;
            /NXCOMPAT:NO;
            /DYNAMICBASE:NO;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /NODEFAULTLIB:msvcrtd.lib;
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL:NO
        >
        /NOLOGO
    )
endif()



################################################################################
# Post build events
################################################################################
add_custom_command_if(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMANDS
    COMMAND       $<CONFIG:Debug> xcopy /Y "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>" "$ENV{LocalDebuggerWorkingDirectory}"
    COMMAND     $<CONFIG:Release> xcopy /Y "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>" "$ENV{LocalDebuggerWorkingDirectory}"
    COMMAND     $<CONFIG:Release> editbin /REBASE:BASE=0x400000 /DYNAMICBASE:NO "$ENV{LocalDebuggerWorkingDirectory}$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    COMMENT "Stripping debug info..."
)

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        "SDL2;"
        "SDL2main"
    ">"
    "$<$<CONFIG:Release>:"
        "SDL2;"
        "SDL2main;"
        "user32"
    ">"
    "libpng16;"
    "zdll;"
    "ws2_32"
)
#find_library(GOTLIBS, "${ADDITIONAL_LIBRARY_DEPENDENCIES}" PATHS "${CMAKE_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

