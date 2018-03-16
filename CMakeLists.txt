cmake_minimum_required (VERSION 3.1)
project (BugDepth)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

option(BUILD_TESTING "Build tests." OFF)

find_package( OpenCV REQUIRED )

add_subdirectory(src)

if(BUILD_TESTING)
	add_subdirectory(test)
endif(BUILD_TESTING)
