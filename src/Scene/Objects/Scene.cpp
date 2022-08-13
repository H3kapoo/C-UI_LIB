#include "Scene.hpp"

namespace hekui {

    Scene::Scene(GLFWwindow* windowHandle)
    {
        windowHandle_ = windowHandle;
        sceneInput_ = std::make_shared<SceneInput>(windowHandle_);

        int width, height;
        glfwGetWindowSize(windowHandle_, &width, &height);
        projMat_ = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, (float)maxLayers_);
        bounds_ = Bounds({ 0,0 }, { width,height });
    }

    void Scene::onMouseCursorPosEvent(double xPos, double yPos)
    {
        sceneInput_->onMouseCursorPosEvent(xPos, yPos);
    }

    void Scene::onMouseButtonEvent(int button, int action, int mods)
    {
        sceneInput_->onMouseButtonEvent(button, action, mods);
    }

    void Scene::onKeyboardEvent(int key, int scancode, int action, int mods)
    {
        sceneInput_->onKeyboardEvent(key, scancode, action, mods);
    }

    // overrides
    void Scene::update() {

        // reset on mouse release
        if (sceneInput_->isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT))
        {
            selectedObject_ = nullptr;
            // boundsDiffSet_ = false;
            selectedPickSide_ = PickSide::OUT_OF_BOUNDS;
            selectedBoundsDiff_.clear();
        }

        // move with the selected object
        if (selectedObject_) {
            // calculate new bounds by pickSide
            const auto bounds = selectedObject_->getBounds();
            const glm::vec2 mouseXY = { sceneInput_->getMouseX(),sceneInput_->getMouseY() };

            if (selectedBoundsDiff_.isCleared())
            {
                selectedBoundsDiff_ = { bounds.topLeft - mouseXY,bounds.bottomRight - mouseXY };
                // boundsDiffSet_ = true;
            }

            auto newBounds = Bounds::getNewBoundsFromGrabSide(bounds, selectedPickSide_,
                mouseXY, selectedBoundsDiff_);
            selectedObject_->setBounds(newBounds);
        }

        // if we dont have a selected object, find one
        if (!selectedObject_ && sceneInput_->isMouseButtonPressedOnce(GLFW_MOUSE_BUTTON_LEFT)) {
            for (const auto& child : children_)
            {
                // child->setBounds();
                const glm::vec2 mouseXY = { sceneInput_->getMouseX(),sceneInput_->getMouseY() };

                const auto pickSide = Bounds::getPickSide(child->getBounds(), 20, mouseXY);
                if (pickSide != PickSide::OUT_OF_BOUNDS)
                {
                    selectedObject_ = child;
                    selectedPickSide_ = pickSide;
                    break;
                }
            }
        }

        // clear input cache every frame
        sceneInput_->clear();
    }

    void Scene::render() const {
        for (const auto& child : children_)
        {
            child->render(projMat_);
        }
    }

    void Scene::addChild(const SceneObjectBasePtr& child) {
        children_.push_back(child);
        child->setZIndex(nextZIndex++);
    }

    void Scene::reset() {
    }

    const std::string Scene::getName() const {
        return name_;
    }
}