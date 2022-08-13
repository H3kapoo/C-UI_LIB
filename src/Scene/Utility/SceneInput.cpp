#include "SceneInput.hpp"

namespace hekui {
    SceneInput::SceneInput(GLFWwindow* window)
    {
        if (window == nullptr)
        {
            std::cerr << "No window set for Input class!" << std::endl;
            return;
        }

        window_ = window;

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        lastMouseX_ = width / 2;  // center of the screen
        lastMouseY_ = height / 2; // center of the screen

        mouseOffsetX_ = 0;
        mouseOffsetY_ = 0;
    }

    void SceneInput::onKeyboardEvent(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            currentlyPressedKeys_[key] = true;
            oncePressedKeys_[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            currentlyPressedKeys_[key] = false;
            previouslyPressedKeys_[key] = true;
            oncePressedKeys_[key] = false;
        }
    }

    void SceneInput::onMouseCursorPosEvent(double xPos, double yPos)
    {
        if (currentlyPressedKeys_[GLFW_MOUSE_BUTTON_LEFT] && xPos != lastMouseX_ && yPos != lastMouseY_)
            isMouseDragging_ = true;
        else isMouseDragging_ = false;
        mouseOffsetX_ = xPos - lastMouseX_;
        // mouseOffsetY_ = lastMouseY_ - yPos; // mouse inverted;
        mouseOffsetY_ = xPos - lastMouseY_;
        lastMouseX_ = xPos;
        lastMouseY_ = yPos;
    }

    void SceneInput::onMouseButtonEvent(int button, int action, int mods) {
        if (action == GLFW_PRESS)
        {
            currentlyPressedKeys_[button] = true;
            oncePressedKeys_[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            currentlyPressedKeys_[button] = false;
            previouslyPressedKeys_[button] = true;
            oncePressedKeys_[button] = false;

            isMouseDragging_ = false; // hacky way for LEFT mouse dragg
        }
    }
    void SceneInput::clear()
    {
        mouseOffsetX_ = 0;
        mouseOffsetY_ = 0;
        memset(previouslyPressedKeys_, 0, 256);
    }

    bool SceneInput::isKeyReleased(GLenum key)
    {
        bool eval = previouslyPressedKeys_[key] && !currentlyPressedKeys_[key];
        if (!currentlyPressedKeys_[key])
            return eval;
        return false;
    }

    bool SceneInput::isKeyPressed(GLenum key)
    {
        return currentlyPressedKeys_[key];
    }

    bool SceneInput::isKeyPressedOnce(GLenum key)
    {
        bool eval = oncePressedKeys_[key] && currentlyPressedKeys_[key];
        if (currentlyPressedKeys_[key]) oncePressedKeys_[key] = false;
        return eval;
    }

    bool SceneInput::isMouseButtonPressed(GLenum button)
    {
        return currentlyPressedKeys_[button];
    }

    bool SceneInput::isMouseButtonPressedOnce(GLenum button)
    {
        bool eval = oncePressedKeys_[button] && currentlyPressedKeys_[button];
        if (currentlyPressedKeys_[button]) oncePressedKeys_[button] = false;
        return eval;
    }

    bool SceneInput::isMouseButtonReleased(GLenum button)
    {
        bool eval = previouslyPressedKeys_[button] && !currentlyPressedKeys_[button];
        if (!currentlyPressedKeys_[button])
            return eval;
        return false;
    }

    bool SceneInput::isMouseDragging() { return isMouseDragging_; }

    float SceneInput::getMouseDeltaX() { return mouseOffsetX_; }

    float SceneInput::getMouseDeltaY() { return mouseOffsetY_; }

    float SceneInput::getMouseX() { return lastMouseX_; }

    float SceneInput::getMouseY() { return lastMouseY_; }
}