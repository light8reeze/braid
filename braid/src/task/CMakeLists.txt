add_library(braid-task STATIC 
							"src/task/TaskSerializer.cc"
							"src/task/TaskDistributor.cc")


find_package(Boost 1.83 REQUIRED)

target_include_directories(braid-task PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_include_directories(braid-task PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(braid-task PUBLIC "braid-util")
