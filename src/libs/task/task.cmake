############################################################


set(uqm_src_libs_task_master_files "")


############################################################
# Local files
set(uqm_src_libs_task_files
	"src/libs/task/task.cmake"
	"src/libs/task/tasklib.cpp"
)

source_group("src\\libs\\task" FILES ${uqm_src_libs_task_files})
list(APPEND uqm_src_libs_task_master_files ${uqm_src_libs_task_files})
