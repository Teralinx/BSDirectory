#CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.25.1)

#set language standard
SET(CMAKE_CXX_STANDARD 17)
#set compiling code of irrelevent posion
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set project name
PROJECT(BSDirectory)

#add headers
FILE(GLOB_RECURSE cpps CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#add dependencies
#INCLUDE(FetchContent)
#FETCHCONTENT_DECLARE(protobuf
#                    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf
#                     GIT_TAG        v35.1)
#FETCHCONTENT_MAKEAVAILABLE(protobuf)
FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Widgets)
ADD_EXECUTABLE(${PROJECT_NAME} ${cpps})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE Qt5::Widgets)
