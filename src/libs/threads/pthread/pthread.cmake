############################################################


set(uqm_src_libs_threads_pthread_master_files "")


############################################################
# Local files
set(uqm_src_libs_threads_pthread_files
#	"src/libs/threads/pthread/posixthreads.cpp"
#	"src/libs/threads/pthread/posixthreads.h"
	"src/libs/threads/pthread/pthread.cmake"
)

source_group("src\\libs\\threads\\pthread" FILES ${uqm_src_libs_threads_pthread_files})
list(APPEND uqm_src_libs_threads_pthread_master_files ${uqm_src_libs_threads_pthread_files})
