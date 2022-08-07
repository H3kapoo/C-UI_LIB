#pragma once

#include <memory>
#include <cstring>
#include "Window.hpp"

class Input
{
public:
    static void clear()
    {
        mouseOffsetX = 0;
        mouseOffsetY = 0;
        memset(previouslyPressedKeys, 0, 256);
    }

    static void setWindow(std::shared_ptr<Window> window)
    {
        if (window == nullptr)
        {
            std::cerr << "No window set for Input class!" << std::endl;
            return;
        }

        window_ = window;
        lastMouseX = window->getWidth() / 2;  // center of the screen
        lastMouseY = window->getHeight() / 2; // center of the screen
        mouseOffsetX = 0;
        mouseOffsetY = 0;
        glfwSetCursorPosCallback(window_->getHandle(), mouseCallback);
        glfwSetMouseButtonCallback(window->getHandle(), mouseButtonCallback);
        glfwSetKeyCallback(window_->getHandle(), keyboardCallback);
    }

    static bool isKeyReleased(GLenum key)
    {
        bool eval = previouslyPressedKeys[key] && !currentlyPressedKeys[key];
        if (!currentlyPressedKeys[key])
            return eval;
        return false;
    }

    static bool isKeyPressed(GLenum key)
    {
        return currentlyPressedKeys[key];
    }

    static bool isKeyPressedOnce(GLenum key)
    {
        bool eval = oncePressedKeys[key] && currentlyPressedKeys[key];
        if (currentlyPressedKeys[key]) oncePressedKeys[key] = false;
        return eval;
    }

    static bool isMouseButtonPressed(GLenum button)
    {
        return currentlyPressedKeys[button];
    }

    static bool isMouseButtonPressedOnce(GLenum button)
    {
        bool eval = oncePressedKeys[button] && currentlyPressedKeys[button];
        if (currentlyPressedKeys[button]) oncePressedKeys[button] = false;
        return eval;
    }


    static bool isMouseButtonReleased(GLenum button)
    {
        bool eval = previouslyPressedKeys[button] && !currentlyPressedKeys[button];
        if (!currentlyPressedKeys[button])
            return eval;
        return false;
    }

    static bool isMouseDragging() { return isMouseDragging_; }
    static float getMouseDeltaX() { return mouseOffsetX; }

    static float getMouseDeltaY() { return mouseOffsetY; }

    static float getMouseX() { return lastMouseX; }

    static float getMouseY() { return lastMouseY; }

private:
    static bool oncePressedKeys[256];
    static bool currentlyPressedKeys[256];
    static bool previouslyPressedKeys[256];
    static bool isMouseDragging_;
    static float lastMouseX, lastMouseY;
    static float mouseOffsetX, mouseOffsetY;
    static std::shared_ptr<Window> window_;

    static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            currentlyPressedKeys[key] = true;
            oncePressedKeys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            currentlyPressedKeys[key] = false;
            previouslyPressedKeys[key] = true;
            oncePressedKeys[key] = false;
        }
    }

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            currentlyPressedKeys[button] = true;
            oncePressedKeys[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            currentlyPressedKeys[button] = false;
            previouslyPressedKeys[button] = true;
            oncePressedKeys[button] = false;

            isMouseDragging_ = false; // hacky way for LEFT mouse dragg
        }
    }

    static void mouseCallback(GLFWwindow* window, double xPos, double yPos)
    {
        if (currentlyPressedKeys[GLFW_MOUSE_BUTTON_LEFT])
            isMouseDragging_ = true;
        mouseOffsetX = xPos - lastMouseX;
        // mouseOffsetY = lastMouseY - yPos; // mouse inverted;
        mouseOffsetY = xPos - lastMouseY;
        lastMouseX = xPos;
        lastMouseY = yPos;
    }

public:
    Input() = delete;
    Input(Input const&) = delete;
    void operator=(Input const&) = delete;
};
