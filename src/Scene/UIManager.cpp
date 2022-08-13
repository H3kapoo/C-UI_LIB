#include "UIManager.hpp"


UIManager::UIManager(const std::shared_ptr<Window> window)
{
    window_ = window;
    projMat_ = glm::ortho(0.0f, (float)window_->getWidth(),
        (float)window_->getHeight(), 0.0f, 0.0f, (float)maxLayers_);
}

void UIManager::addRoot(std::shared_ptr<ISceneElement> rootElement) {
    root_ = rootElement;
}

void UIManager::updateAndRender()
{
    // std::cout << "is in front -> " << elements_[0]->getName() << std::endl;
    // if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        // handleGrabFromPosition({ Input::getMouseX(), Input::getMouseY() });


    // simpler solution for now
    projMat_ = glm::ortho(0.0f, (float)window_->getWidth(),
        (float)window_->getHeight(), 0.0f, 0.0f, (float)maxLayers_);

    root_->updateAndRender(projMat_);
}
