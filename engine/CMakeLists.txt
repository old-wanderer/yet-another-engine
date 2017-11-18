find_package(OpenGl REQUIRED)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
else()
    message(WARNING "gleew not found")
endif()

include_directories(include)
include_directories(libs/glm)

link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib/libglfw.dylib)
link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/lib/libassimp.dylib)
link_libraries(/usr/local/Cellar/libpng/1.6.34/lib/libpng.dylib)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp include/*.h)

add_library(yet_another_engine_lib STATIC ${SOURCE_FILES})
target_link_libraries(yet_another_engine_lib ${OPENGL_glu_LIBRARY})
target_include_directories(yet_another_engine_lib PUBLIC ${CMAKE_BINARY_DIR})
