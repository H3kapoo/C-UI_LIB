cmake_minimum_required(VERSION 3.16)

project(openGL_UI)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} 
    main.cpp
    src/Window/Window.cpp
    src/Window/Input.cpp
    src/Window/Time.cpp
    src/Buffers/Vao.cpp
    src/Buffers/Vbo.cpp
    src/Buffers/Ibo.cpp
    src/Shaders/Shader.cpp
    src/Primitives/Quad.cpp
    src/Scene/UIManager.cpp
    src/Scene/Types/ISceneElement.cpp
    src/Scene/Types/Panel.cpp
)
target_link_libraries(${PROJECT_NAME} glfw3 GLEW GL GLU X11 pthread ${CMAKE_DL_LIBS})