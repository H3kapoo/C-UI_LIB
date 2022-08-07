#include "ISceneElement.hpp"
#include "../../Primitives/Quad.hpp"

enum class PickSide {
    N, E, S, W, SE, SW, NE, NW, OUT_OF_BOUNDS
};

class Panel : public ISceneElement {
private:
    std::string name_;
    int zIndex_{ 0 };
    int grabOffset_{ 20 }; // distance from border in which it is considered a grab
    Bounds bounds_;
    Bounds lastBounds_;
    bool failedToGrabSide{ false };
    PickSide currentlyPickedSide_{ PickSide::OUT_OF_BOUNDS };
    glm::vec2 boundsDiffBotRight_{ 0 }, boundsDiffTopLeft_{ 0 };
    glm::vec2 minScale_{ 70 };
    std::unique_ptr<Quad> quad_;
    std::shared_ptr<Shader> shader_;
    std::vector<std::shared_ptr<ISceneElement>> elements_;
public:
    Panel(const std::string& name, const Bounds& bounds);
    void addElement(std::shared_ptr<ISceneElement> element);
    void removeElement(ISceneElement& element);
    void setBackgroundColor(const glm::vec3 color);
    void render(const glm::mat4& projMat) override;
    void handleGrabFromPosition(const glm::vec2& pos);
    void resetGrabbing();
    void setBounds(const Bounds& bounds) override;
    const Bounds constrainGrabBoundsFromSide(const Bounds& bounds, const PickSide& side);

    PickSide getPickedSide(const glm::vec2& pos) const;
    const Bounds& getBounds() override;
    void setZIndex(int index);
    void adjustElementsBounds();
};

using PanelPtr = std::shared_ptr<Panel>;
