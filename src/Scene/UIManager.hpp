#include "Types/ISceneElement.hpp"
#include "../Window/Window.hpp"

#include <memory>

class UIManager
{
private:
    glm::mat4 projMat_;
    std::shared_ptr<Window> window_;
    std::vector<std::shared_ptr<ISceneElement>> elements_;
public:
    UIManager(const std::shared_ptr<Window> window);
    void addElement(std::shared_ptr<ISceneElement> element);
    void removeElement(ISceneElement& element);
    // static const glm::mat4& getProjMat();
    void render();
};

using UIManagerPtr = std::shared_ptr<UIManager>;
