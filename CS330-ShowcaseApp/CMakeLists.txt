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
        include/texture.h)

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

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)