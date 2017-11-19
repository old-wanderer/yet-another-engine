find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
else()
    message(WARNING "gleew not found")
endif()

# символьная ссылка на директорию с ресурсами, для билда надо будет заменить
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resource ${CMAKE_BINARY_DIR}/examples/resource)

include_directories(../engine/include)
include_directories(../engine/libs/glm)
include_directories(../engine/libs/glfw/include)

add_executable(Scene3D_example Scene3D_example/main.cpp)
add_executable(3DObject_import_example 3DObject_import_example/main.cpp)

target_link_libraries(Scene3D_example yet_another_engine_lib)
target_link_libraries(3DObject_import_example yet_another_engine_lib)

