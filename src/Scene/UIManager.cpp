#include "UIManager.hpp"


UIManager::UIManager(const std::shared_ptr<Window> window)
{
    window_ = window;
    projMat_ = glm::ortho(0.0f, (float)window_->getWidth(),
        (float)window_->getHeight(), 0.0f, -1.0f, 100.0f);
}

void UIManager::addElement(std::shared_ptr<ISceneElement> element) {
    elements_.push_back(element);
}

void UIManager::removeElement(ISceneElement& element) {
    // elements_.push_back(element);
}

void UIManager::render()
{
    for (const auto& element : elements_)
    {
        element->render(projMat_);
    }
}
