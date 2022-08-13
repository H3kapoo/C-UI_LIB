#include "Types/ISceneElement.hpp"
#include "../Window/Window.hpp"

#include <memory>
#include <algorithm>

class UIManager
{
private:
    int maxLayers_{ 100 };
    glm::mat4 projMat_;
    std::shared_ptr<Window> window_;
    std::shared_ptr<ISceneElement> root_;

public:
    UIManager(const std::shared_ptr<Window> window);
    void addRoot(std::shared_ptr<ISceneElement> rootElement);
    void updateAndRender();
};

using UIManagerPtr = std::shared_ptr<UIManager>;
