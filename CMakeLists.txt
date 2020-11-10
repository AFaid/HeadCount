cmake_minimum_required(VERSION 3.1.0)
project(headcount)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# OpenCV
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# Executable
file(GLOB SOURCES src/*.h src/*.cpp)
file(GLOB RESOURCES *.qrc)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${RESOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets ${OpenCV_LIBS})
