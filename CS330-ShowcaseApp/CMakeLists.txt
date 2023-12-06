set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})

add_subdirectory(external/cmakelibs/glfw)
add_subdirectory(external/shared/glm)
add_subdirectory(external/shared/stb_image)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE GLAD_SOURCES external/shared/glad/*.c)


add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCES}
        include/types.h
        src/mesh.cpp
        include/mesh.h
        src/shader.cpp
        include/shader.h
        src/camera.cpp
        include/camera.h
        external/shared/stb_image/stb.cpp
        src/texture.cpp
        include/texture.h
        src/light.cpp
        include/light.h
        src/game_object.cpp
        include/game_object.h
        src/model.cpp
        include/model.h
        src/cat_area.cpp
        include/cat_area.h
        include/shapes.h)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include/
        external/shared/glad/include
        glfw
        glm
        stb
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glm
        OpenGL::GL
        stb
)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

add_dependencies(${PROJECT_NAME} copy_assets)