cmake_minimum_required (VERSION 2.6)
project (BugDepth)


option(BUILD_TESTING "Build tests." OFF)

add_subdirectory(src)

if(BUILD_TESTING)
	add_subdirectory(test)
endif(BUILD_TESTING)
