add_library(braid-util STATIC
	"src/LogHandler.cc"
)

target_include_directories(braid-util PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(braid-util PUBLIC braid-task)
