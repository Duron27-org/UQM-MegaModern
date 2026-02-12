############################################################


set(uqm_tests_libs_master_files "")


############################################################
# Local files
set(uqm_tests_libs_files
	"tests/libs/libs.cmake"
	"tests/libs/test_callback.cpp"
)

source_group("tests\\libs" FILES ${uqm_tests_libs_files})
list(APPEND uqm_tests_libs_master_files ${uqm_tests_libs_files})
