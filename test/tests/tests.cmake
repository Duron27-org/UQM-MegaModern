############################################################


set(uqm_tests_master_files "")

############################################################
# Sub-directories
include("tests/core/core.cmake")
list(APPEND uqm_tests_master_files ${uqm_tests_core_master_files})
include("tests/lib/lib.cmake")
list(APPEND uqm_tests_master_files ${uqm_tests_lib_master_files})
include("tests/options/options.cmake")
list(APPEND uqm_tests_master_files ${uqm_tests_options_files})

############################################################
# Local files
set(uqm_tests_files
	"tests/tests.cmake"
)

source_group("tests" FILES ${uqm_tests_files})
list(APPEND uqm_tests_master_files ${uqm_tests_files})
