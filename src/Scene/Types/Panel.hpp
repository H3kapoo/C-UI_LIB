#include "ISceneElement.hpp"
#include "../../Primitives/Quad.hpp"
#include "../../Window/Input.hpp"

enum class PickSide {
    N, E, S, W, SE, SW, NE, NW, OUT_OF_BOUNDS
};

class Panel : public ISceneElement {
public:
    bool isSelected{ false };

private:
    std::string name_;
    ISceneElementPtr parent_{ nullptr };
    int zIndex_{ 0 }; // 1 (backmost)  100 (frontmost)
    int grabOffset_{ 20 }; // distance from border in which it is considered a grab
    Bounds bounds_;
    Bounds lastBounds_;
    bool failedToGrabSide_{ false };
    PickSide currentlyPickedSide_{ PickSide::OUT_OF_BOUNDS };
    glm::vec2 boundsDiffBotRight_{ 0 }, boundsDiffTopLeft_{ 0 };
    glm::vec2 minScale_{ 70 };
    std::unique_ptr<Quad> quad_;
    std::shared_ptr<Shader> shader_;
    std::vector<ISceneElementPtr> elements_;
private:
    void updateAndRender(const glm::mat4& projMat) override;
    void adjustElementsBounds();
    void handleGrabFromPosition(const glm::vec2& pos);
    void resetGrabbing();
    const Bounds constrainGrabBoundsFromSide(const Bounds& bounds, const PickSide& side);
    PickSide getPickedSide(const glm::vec2& pos) const;

public:
    Panel(const std::string& name, const Bounds& bounds);
    // void setParent(ISceneElementPtr parent) override;
    void setBounds(const Bounds& bounds) override;
    void setZIndex(int index) override;
    void addElement(ISceneElementPtr element);
    void removeElement(ISceneElement& element);
    void setBackgroundColor(const glm::vec3 color);
    const Bounds& getBounds() override;
    const int getZIndex() const override;
    const std::string getName() override;

};

using PanelPtr = std::shared_ptr<Panel>;
