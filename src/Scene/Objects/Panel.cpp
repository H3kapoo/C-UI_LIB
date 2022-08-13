#include "Panel.hpp"


namespace hekui
{
    Panel::Panel(const std::string& name, const Bounds& bounds) {
        shader_ = std::make_shared<Shader>();
        quad_ = std::make_unique<Quad>(shader_); // will be inited with Quad shader
        name_ = name;
        bounds_ = bounds;
        lastBounds_ = bounds;
        setBounds(bounds);
    }

    void Panel::setBounds(const Bounds& bounds) {
        bounds_ = bounds;

        auto scaleX = bounds_.bottomRight.x - bounds_.topLeft.x;
        auto scaleY = bounds_.bottomRight.y - bounds_.topLeft.y;

        quad_->setPos(glm::vec3(bounds_.topLeft, -zIndex_));
        quad_->setScale({ scaleX, scaleY });

        lastBounds_ = bounds_;

        // make shader aware of the changes
        shader_->setVec3f("bottomRight", glm::vec3(bounds_.bottomRight, 0));
        shader_->setVec3f("topLeft", glm::vec3(bounds_.topLeft, 0));

        // this should only be set once, not over and over
        shader_->setInt("borderWidth", grabOffset_);

        // adjustElementsBounds();
    }

    const Bounds& Panel::getBounds() const {
        return bounds_;
    }

    void Panel::addChild(const SceneObjectBasePtr& child) {

    }

    void Panel::setParent(const SceneObjectBasePtr& parent) {
        parent_ = parent;
    }

    void Panel::setBackgroundColor(const glm::vec3 color)
    {
        shader_->setVec3f("color", color);
    }

    void Panel::update() {
        std::cout << "UPDATING" << std::endl;
    }

    void Panel::render(const glm::mat4& projMat) const {
        quad_->draw(projMat);
        for (const auto& child : children_)
            child->render(projMat);
    }

    void Panel::setSelected() {
    }

    void Panel::setZIndex(int index) {
        zIndex_ = index < 0 ? 0 : index;

        quad_->setPos(glm::vec3(bounds_.topLeft, -zIndex_));
    }

    const int Panel::getZIndex() const {
        return zIndex_;
    }

    void Panel::reset() {
    }

    const std::string Panel::getName() const {
    }
}