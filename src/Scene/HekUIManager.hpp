#pragma once

#include <functional>
#include <unordered_map>

#include "Objects/SceneObjectBase.hpp"
#include "../Window/Window.hpp"
namespace hekui
{
    class HekUIManager
    {
        int maxLayers_{ 100 };
        glm::mat4 projMat_;
        GLFWwindow* windowHandle_;

    public:
        HekUIManager(GLFWwindow* windowHandle)
        {
            // windowHandle_ = windowHandle;
            // static auto funct = std::bind(&hekui::HekUIManager::func, this, root_,
            //     std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

            // glfwSetMouseButtonCallback(windowHandle_,
            //     [](GLFWwindow* window, int button, int action, int mods)
            //     {
            //         funct(window, button, action, mods);
            //     });

        }

    };

    using HekUIManagerPtr = std::shared_ptr<HekUIManager>;
}