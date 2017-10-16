cmake_minimum_required(VERSION 3.7)
project(yet_another_engine)

set(CMAKE_CXX_STANDARD 11)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
else()
    message(WARNING "gleew not found")
endif()



include_directories(./include)
include_directories(./libs/glfw/include)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(yet_another_engine ${SOURCE_FILES})

target_link_libraries(yet_another_engine glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})