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

// newer includes
#include "src/Scene/HekUIManager.hpp"
#include "src/Scene/Objects/Scene.hpp"
#include "src/Scene/Objects/Panel.hpp"

int main()
{
    if (!Window::windowingInit())
        return -1;

    const auto  window = std::make_shared<Window>("UI Stuff", 1280, 720);
    window->setCursorMode(CursorMode::NORMAL);

    if (glewInit())
        return -1;

    Input::setWindow(window);

    hekui::ScenePtr hekScene = std::make_shared<hekui::Scene>(window->getHandle());

    // setting up listeners for the scene
    // this should be abstracted somehow somewhere else
    Input::notifyMouseCursorPosEvent = hekScene->mouseCursorPosBinder();
    // std::bind(&hekui::Scene::onMouseCursorPosEvent, hekScene, std::placeholders::_1, std::placeholders::_2);
    Input::notifyMouseButtonEvent =
        std::bind(&hekui::Scene::onMouseButtonEvent, hekScene, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    Input::notifyKeyboardEvent =
        std::bind(&hekui::Scene::onKeyboardEvent, hekScene, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
            std::placeholders::_4);


    hekui::PanelPtr hekPanel = std::make_shared<hekui::Panel>("MyPanel", hekui::Bounds({ 100,100 }, { 300,200 }));
    hekPanel->setBackgroundColor(glm::vec3(1, 1, 1));
    hekScene->addChild(hekPanel);

    while (!window->shouldClose())
    {
        Time::computeDelta(); // must be called at the start
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
            window->closeWindow();

        hekScene->update();
        hekScene->render();

        window->swapBuffers();
        Input::clear(); // must be called before pollEvs
        Window::pollEvents();
    }

    // clean up
    Window::windowingTerminate();
    return 0;
}