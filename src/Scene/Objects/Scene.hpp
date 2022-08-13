#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "SceneObjectBase.hpp"
#include "../Utility/SceneInput.hpp"

namespace hekui
{
    class Scene;

    class Scene {

    private:
        SceneInputPtr sceneInput_;

        int maxLayers_{ 100 };
        glm::mat4 projMat_;
        GLFWwindow* windowHandle_ = nullptr;
        Bounds bounds_;
        SceneObjectBaseVec children_;
        int nextZIndex{ 1 };
        std::string name_;

        SceneObjectBasePtr selectedObject_{ nullptr };
        PickSide selectedPickSide_ = PickSide::OUT_OF_BOUNDS;
        Bounds selectedBoundsDiff_{ {0,0},{0,0} };
        glm::vec2 boundsDiffBotRight_{ 0,0 }, boundsDiffTopLeft_{ 0,0 };
        bool boundsDiffSet_{ false };

    private:
        void onMouseCursorPosEvent(double xPos, double yPos);
    public:
        Scene(GLFWwindow* windowHandle);
        void onMouseButtonEvent(int button, int action, int mods);
        void onKeyboardEvent(int key, int scancode, int action, int mods);

    public:
        void addChild(const SceneObjectBasePtr& child);
        void update();
        void render() const;
        void reset();
        const std::string getName() const;
        std::function<void(double, double)> mouseCursorPosBinder()
        {
            return std::bind(&Scene::onMouseCursorPosEvent, this, std::placeholders::_1, std::placeholders::_2);
        }
    };

    using ScenePtr = std::shared_ptr<Scene>;
}