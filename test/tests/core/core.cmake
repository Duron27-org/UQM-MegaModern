############################################################


set(uqm_tests_core_master_files "")

include("../src/core/string/string.cmake")
list(APPEND uqm_tests_core_master_files 
	"../src/core/string/StringUtils.h"
	"../src/core/string/StringUtils.cpp"
)

############################################################
# Local files
set(uqm_tests_core_files
	"tests/core/testStringUtils.cpp"
)

source_group("tests\\core" FILES ${uqm_tests_core_files})
list(APPEND uqm_tests_core_master_files ${uqm_tests_core_files})
