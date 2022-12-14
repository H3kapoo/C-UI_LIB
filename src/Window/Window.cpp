#include "Window.hpp"

bool Window::inited = false;
bool Window::windowDirty_ = false;

Window::Window(const char* title) : Window(title, 840, 640) {}

Window::Window(const char* title, int width, int height) : width_(width), height_(height)
{

    if (width < 1 || height < 1)
    {
        std::cerr << "Can't create window of such small or negative size!" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glEnable(GL_DEPTH_TEST);

    windowHandle_ = glfwCreateWindow(width_, height_, title, nullptr, nullptr);
    if (windowHandle_ == nullptr)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        windowingTerminate();
        return;
    }

    std::cout << "Successfully created window " << title << std::endl;

    glfwSetFramebufferSizeCallback(windowHandle_,
        [](GLFWwindow* window, int width, int height) {
            Window::windowDirty_ = true;
        });

    makeContextCurrent();
}

void Window::makeContextCurrent() const
{
    glfwMakeContextCurrent(windowHandle_);
}

void Window::swapBuffers()
{
    if (Window::windowDirty_)
    {
        glfwGetFramebufferSize(windowHandle_, &width_, &height_);
        glViewport(0, 0, width_, height_);
        Window::windowDirty_ = false;
    }
    glfwSwapBuffers(windowHandle_);
}

GLFWwindow* Window::getHandle() const
{
    return windowHandle_;
}

bool Window::windowingInit()
{
    if (glfwInit())
        return true;
    return false;
}

void Window::windowingTerminate()
{
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(windowHandle_);
}

int Window::getWidth()
{
    return width_;
}

int Window::getHeight()
{
    return height_;
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::closeWindow() const
{
    glfwSetWindowShouldClose(windowHandle_, true);
}

void Window::setCursorMode(const CursorMode& mode)
{
    glfwSetInputMode(windowHandle_, GLFW_CURSOR, mode);
}
