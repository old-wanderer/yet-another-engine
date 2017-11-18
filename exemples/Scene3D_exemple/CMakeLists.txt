
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
else()
    message(WARNING "gleew not found")
endif()

# символьная ссылка на директорию с ресурсами, для билда надо будет заменить
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resource ${CMAKE_BINARY_DIR}/exemples/Scene3D_exemple/resource)

include_directories(../../engine/include)
include_directories(../../engine/libs/glm)
include_directories(../../engine/libs/glfw/include)

add_executable(exemple_1 main.cpp)

target_link_libraries(exemple_1 yet_another_engine_lib)

