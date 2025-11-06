# CMakeList.txt: FirstServer에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (first-server "FirstServer.cpp" "FirstServer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET first-server PROPERTY CXX_STANDARD 20)
endif()

# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.

find_library(LIBURING_LIB uring REQUIRED)
find_path(LIBURING_INCLUDE liburing.h REQUIRED)

target_link_libraries(first-server ${LIBURING_LIB})
target_include_directories(first-server PRIVATE ${LIBURING_INCLUDE})