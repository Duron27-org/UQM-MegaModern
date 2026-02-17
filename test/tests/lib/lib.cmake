############################################################


set(uqm_tests_lib_master_files "")

list(APPEND uqm_tests_lib_master_files 
	"../src/lib/Math2D/Math2D.h"
	"../src/lib/Math2D/Math2D.cpp"
	"../src/lib/Math2D/Math2DStringUtils.h"
	"../src/lib/Math2D/Math2DStringUtils.cpp"
)


############################################################
# Local files
set(uqm_tests_lib_files
	"tests/lib/lib.cmake"
	"tests/lib/test_Math2D.cpp"
)

source_group("tests\\lib" FILES ${uqm_tests_lib_files})
list(APPEND uqm_tests_lib_master_files ${uqm_tests_lib_files})
