#pragma once

#include "SceneObjectBase.hpp"

namespace hekui
{
    class Panel : public SceneObjectBase
    {
    private:
        std::unique_ptr<Quad> quad_;
        std::shared_ptr<Shader> shader_;
        Bounds bounds_;
        Bounds lastBounds_;
        glm::vec2 minScale_{ 70 };
        glm::vec2 boundsDiffBotRight_{ 0 }, boundsDiffTopLeft_{ 0 };
        PickSide currentlyPickedSide_{ PickSide::OUT_OF_BOUNDS };
        int zIndex_{ 1 }; // 1 (backmost)  100 (frontmost)
        int grabOffset_{ 20 }; // distance from border in which it is considered a grab
        std::string name_;
        SceneObjectBaseVec children_;
        SceneObjectBasePtr parent_{ nullptr };

    protected:
        void setParent(const SceneObjectBasePtr& parent);
        void setBounds(const Bounds& bounds);
        void setZIndex(int index);
        void update() override;
        void render(const glm::mat4& projMat) const override;
        void setSelected();
        const int getZIndex() const;
        void reset();
    public:
        Panel(const std::string& name, const Bounds& bounds);
        const std::string getName() const override;
        const Bounds& getBounds() const override;
        void addChild(const SceneObjectBasePtr& child) override;
        void setBackgroundColor(const glm::vec3 color) override;
    };

    using PanelPtr = std::shared_ptr<Panel>;
}