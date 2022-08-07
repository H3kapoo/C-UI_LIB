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

    // glm::mat4 proj = glm::ortho(0.0f, (float)window->getWidth(), (float)window->getHeight(), 0.0f, -1.0f, 100.0f);

    // std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    // Quad quad(shader);

    // glm::vec3 pos{ 500, 300, -1 }; // negative because neg Z goes into the screen
    // glm::vec2 scale{ 100,100 };
    // glm::mat4 model = glm::mat4(1.0f);

    // shader->setMatrix4("model", model);
    // shader->setMatrix4("proj", proj);
    // shader->setVec3f("color", glm::vec3(0.5, 0.5, 0.5));

    // std::shared_ptr<Shader> pivotShader = std::make_shared<Shader>();
    // Quad pivotQuad(pivotShader);

    // glm::vec3 pivotPos{ 300, 250, 0 };
    // glm::mat4 pivotModel = glm::mat4(1.0f);

    // pivotShader->setMatrix4("model", pivotModel);
    // pivotShader->setMatrix4("proj", proj);
    // pivotShader->setVec3f("color", glm::vec3(0.3, 0.3, 0.3));

    UIManagerPtr scene = std::make_shared<UIManager>(window);
    PanelPtr panel = std::make_shared<Panel>("MyPanel", Bounds({ 100,100 }, { 200,200 }));
    panel->setZIndex(-1);
    PanelPtr panel2 = std::make_shared<Panel>("MyPanel2", Bounds({ 120,120 }, { 150,150 }));
    panel2->setZIndex(0);


    scene->addElement(panel);

    panel->setBackgroundColor(glm::vec3(1, 1, 1));
    // panel->addElement(panel2);
    // panel2->setBackgroundColor(glm::vec3(0.5f));
    Bounds testBounds{ { 200,200 }, { 400,400 } };
    panel->setBounds(testBounds);

    glEnable(GL_DEPTH_TEST);
    glm::vec3 pos{ 100 };
    glm::vec3 scale{ 100 };

    while (!window->shouldClose())
    {
        Time::computeDelta(); // must be called at the start
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
            window->closeWindow();
        // scale outside

        /*
        if (Input::isKeyPressed(GLFW_KEY_D))
        {
            testBounds.topLeft.x += 5;
            testBounds.bottomRight.x += 5;
        }

        if (Input::isKeyPressed(GLFW_KEY_A))
        {
            testBounds.topLeft.x -= 5;
            testBounds.bottomRight.x -= 5;
        }
        if (Input::isKeyPressed(GLFW_KEY_W))
        {
            testBounds.topLeft.y -= 5;
            testBounds.bottomRight.y -= 5;
        }

        if (Input::isKeyPressed(GLFW_KEY_S))
        {
            testBounds.topLeft.y += 5;
            testBounds.bottomRight.y += 5;
        }

        if (Input::isKeyPressed(GLFW_KEY_L))
        {
            testBounds.bottomRight.x += 5;
        }
        */
        if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            panel->handleGrabFromPosition({ Input::getMouseX(), Input::getMouseY() });
        }

        if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT))
        {
            panel->resetGrabbing();
        }
        /*
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(pos));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0));
        model = glm::scale(model, glm::vec3(scale, 1.0f));
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0));

        pivotPos = glm::vec3(
            pos.x, // + 40,//std::floor(scale.x * 0.3f),
            pos.y, // + 40,//std::floor(scale.y * 0.3f),
            0
        );

        pivotModel = glm::mat4(1.0f);
        pivotModel = glm::translate(pivotModel, glm::vec3(pivotPos));
        pivotModel = glm::rotate(pivotModel, glm::radians(glm::degrees(0.0f)), glm::vec3(0, 0, 1));
        pivotModel = glm::scale(pivotModel, glm::vec3(glm::vec2(11.0f), 1.0f));

        // scale outside
        if (Input::isKeyPressed(GLFW_KEY_D))
        {
            scale.x += 5;
        }
        if (Input::isKeyPressed(GLFW_KEY_A))
        {
            pos.x -= 5;
            scale.x += 5;
        }

        if (Input::isKeyPressed(GLFW_KEY_W))
        {
            pos.y -= 5;
            scale.y += 5;
        }

        if (Input::isKeyPressed(GLFW_KEY_S))
        {
            scale.y += 5;
        }

        // scale inside
        if (Input::isKeyPressed(GLFW_KEY_J))
        {
            scale.x -= 5;
        }
        if (Input::isKeyPressed(GLFW_KEY_L))
        {
            pos.x += 5;
            scale.x -= 5;
        }

        if (Input::isKeyPressed(GLFW_KEY_I))
        {
            scale.y -= 5;
        }
        if (Input::isKeyPressed(GLFW_KEY_K))
        {
            pos.y += 5;
            scale.y -= 5;
        }

        if (scale.x < 10) scale.x = 10;
        if (scale.y < 10) scale.y = 10;

        std::cout << "XS: " << scale.x << " YS: " << scale.y << std::endl;
        // do render stuff here
        quad.setModelMatrix(model);
        pivotQuad.setModelMatrix(pivotModel);
        quad.draw();
        pivotQuad.draw();
        */
        // render the scene
        scene->render();

        window->swapBuffers();
        Input::clear(); // must be called before pollEvs
        Window::pollEvents();
    }

    // clean up
    Window::windowingTerminate();
    return 0;
}