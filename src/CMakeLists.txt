set(SOURCES
    main.cpp
    edgedetector.cpp
    accumulator.cpp
    argparser.cpp
    img.cpp)

add_executable(bugDepth ${SOURCES})

set(Qt5_DIR "/opt/qt/5.10.1/gcc_64/lib/cmake/Qt5/")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDE_DIRS})
target_link_libraries(bugDepth Qt5::Widgets Qt5::Gui "stdc++fs")
