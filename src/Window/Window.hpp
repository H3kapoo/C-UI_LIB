#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

enum CursorMode
{
    NORMAL = GLFW_CURSOR_NORMAL,
    HIDDEN = GLFW_CURSOR_HIDDEN,
    DISABLED = GLFW_CURSOR_DISABLED
};

class Window
{
private:
    static bool inited;
    int width_, height_;
    GLFWwindow* windowHandle_ = nullptr; // no need for freeing, glfw does it automatically
public:
    Window(const char* title);
    Window(const char* title, int width, int height);

    void setCursorMode(const CursorMode& mode);
    void makeContextCurrent() const;
    bool shouldClose() const;
    void closeWindow() const;
    void swapBuffers() const;
    GLFWwindow* getHandle() const;
    int getWidth();
    int getHeight();

public:
    static bool windowingInit();
    static void pollEvents();
    static void windowingTerminate();
};
