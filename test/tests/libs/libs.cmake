############################################################


set(tst_tests_libs_master_files "")


############################################################
# Local files
set(tst_tests_libs_files
	"tests/libs/libs.cmake"
	"tests/libs/test_callback.cpp"
)

source_group("tests\\libs" FILES ${tst_tests_libs_files})
list(APPEND tst_tests_libs_master_files ${tst_tests_libs_files})
