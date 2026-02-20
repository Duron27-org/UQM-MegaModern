############################################################


set(uqm_tests_uqm_master_files "")

list(APPEND uqm_tests_uqm_master_files 
	"../src/uqm/intel.h"
)

############################################################
# Local files
set(uqm_tests_uqm_files
	"tests/uqm/uqm.cmake"
	"tests/uqm/test_intel.cpp"
)

source_group("tests\\uqm" FILES ${uqm_tests_uqm_files})
list(APPEND uqm_tests_uqm_master_files ${uqm_tests_uqm_files})
