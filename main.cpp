#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include "src/Window/Window.hpp"
#include "src/Window/Input.hpp"
#include "src/Window/Time.hpp"
#include "src/Shaders/Shader.hpp"
#include "src/Buffers/Vao.hpp"
#include "src/Buffers/Ibo.hpp"
#include "src/Primitives/Quad.hpp"
#include "src/Scene/UIManager.hpp"
#include "src/Scene/Types/Panel.hpp"

int main()
{
    if (!Window::windowingInit())
        return -1;

    const auto  window = std::make_shared<Window>("UI Stuff", 1280, 720);
    window->setCursorMode(CursorMode::NORMAL);

    if (glewInit())
        return -1;

    Input::setWindow(window);
    Bounds testBounds{ { 200,200 }, { 400,400 } };

    UIManagerPtr uiManager = std::make_shared<UIManager>(window);
    PanelPtr panel = std::make_shared<Panel>("MyPanel", Bounds({ 100,100 }, { 200,200 }));
    panel->setZIndex(2);
    panel->setBounds(testBounds);
    panel->setBackgroundColor(glm::vec3(1, 1, 1));

    PanelPtr panel2 = std::make_shared<Panel>("MyPanel2", Bounds({ 120,120 }, { 150,150 }));
    panel2->setZIndex(1);

    uiManager->addElement(panel);
    uiManager->addElement(panel2);


    glEnable(GL_DEPTH_TEST);
    int zindex = 0;

    while (!window->shouldClose())
    {
        Time::computeDelta(); // must be called at the start
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
            window->closeWindow();

        if (Input::isKeyPressedOnce(GLFW_KEY_D))
        {
            panel->setZIndex(--zindex);
        }

        if (Input::isKeyPressedOnce(GLFW_KEY_A))
        {
            panel->setZIndex(++zindex);
        }

        // render the scene
        uiManager->update();
        uiManager->render();

        window->swapBuffers();
        Input::clear(); // must be called before pollEvs
        Window::pollEvents();
    }

    // clean up
    Window::windowingTerminate();
    return 0;
}