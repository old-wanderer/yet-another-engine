cmake_minimum_required(VERSION 3.7)
project(yet_another_engine)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGl REQUIRED)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
else()
    message(WARNING "gleew not found")
endif()

# символьная ссылка на директорию с ресурсами, для билда надо будет заменить
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resource ${CMAKE_BINARY_DIR}/resource)

include_directories(./include)
include_directories(./libs/glfw/include)
include_directories(./libs/glm)

link_directories(./libs/glfw/lib)
link_directories(./libs/assimp/lib)
link_directories(/usr/local/Cellar/libpng/1.6.34/lib)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp include/*.h)

add_executable(yet_another_engine ${SOURCE_FILES})

target_link_libraries(yet_another_engine ${OPENGL_glu_LIBRARY})
target_link_libraries(yet_another_engine glfw)
target_link_libraries(yet_another_engine assimp)
target_link_libraries(yet_another_engine png)
