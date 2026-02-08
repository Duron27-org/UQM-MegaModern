############################################################


set(tst_tests_master_files "")

############################################################
# Sub-directories
include("tests/libs/libs.cmake")
list(APPEND tst_tests_master_files ${tst_tests_libs_master_files})

############################################################
# Local files
set(tst_tests_files
	"tests/tests.cmake"
)

source_group("tests" FILES ${tst_tests_files})
list(APPEND tst_tests_master_files ${tst_tests_files})
