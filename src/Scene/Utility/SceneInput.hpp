#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <functional>
#include <GLFW/glfw3.h>

namespace hekui {
    class SceneInput
    {
    private:
        //variables
        bool oncePressedKeys_[256] = { 0 };
        bool currentlyPressedKeys_[256] = { 0 };
        bool previouslyPressedKeys_[256] = { 0 };
        bool isMouseDragging_{ false };
        float lastMouseX_, lastMouseY_;
        float mouseOffsetX_, mouseOffsetY_;
        GLFWwindow* window_;

    public:
        SceneInput(GLFWwindow* window);
        void onKeyboardEvent(int key, int scancode, int action, int mods);
        void onMouseCursorPosEvent(double xPos, double yPos);
        void onMouseButtonEvent(int button, int action, int mods);
        void clear();
        bool isKeyReleased(GLenum key);
        bool isKeyPressed(GLenum key);
        bool isKeyPressedOnce(GLenum key);
        bool isMouseButtonPressed(GLenum button);
        bool isMouseButtonPressedOnce(GLenum button);
        bool isMouseButtonReleased(GLenum button);
        bool isMouseDragging();
        float getMouseDeltaX();
        float getMouseDeltaY();
        float getMouseX();
        float getMouseY();
    };
    using SceneInputPtr = std::shared_ptr<SceneInput>;
}
