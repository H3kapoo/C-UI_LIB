
#include "Panel.hpp"

Panel::Panel(const std::string& name, const Bounds& bounds)
{
    shader_ = std::make_shared<Shader>();
    quad_ = std::make_unique<Quad>(shader_); // will be inited with Quad shader
    name_ = name;
    bounds_ = bounds;
    lastBounds_ = bounds;
    setBounds(bounds);
}

void Panel::setBackgroundColor(const glm::vec3 color)
{
    shader_->setVec3f("color", color);
}

void Panel::setBounds(const Bounds& bounds)
{
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

void Panel::handleGrabFromPosition(const glm::vec2& pos)
{
    // no need to calculate something if we didnt pick anything
    if (failedToGrabSide_)
        return;

    if (currentlyPickedSide_ == PickSide::OUT_OF_BOUNDS)
    {
        currentlyPickedSide_ = getPickedSide(pos); // should be called here, once
        if (currentlyPickedSide_ == PickSide::OUT_OF_BOUNDS) failedToGrabSide_ = true;
        boundsDiffBotRight_ = bounds_.bottomRight - pos;
        boundsDiffTopLeft_ = bounds_.topLeft - pos;
    }

    if (currentlyPickedSide_ != PickSide::OUT_OF_BOUNDS)
    {
        switch (currentlyPickedSide_)
        {
        case PickSide::NE:
            bounds_.bottomRight = { pos.x + boundsDiffBotRight_.x, bounds_.bottomRight.y };
            bounds_.topLeft = { bounds_.topLeft.x ,pos.y + boundsDiffTopLeft_.y };
            break;
        case PickSide::NW:
            bounds_.topLeft = { pos.x + boundsDiffTopLeft_.x, pos.y + boundsDiffTopLeft_.y };
            break;
        case PickSide::SE:
            bounds_.bottomRight = { pos.x + boundsDiffBotRight_.x, pos.y + boundsDiffBotRight_.y };
            break;
        case PickSide::SW:
            bounds_.topLeft = { pos.x + boundsDiffTopLeft_.x , bounds_.topLeft.y };
            bounds_.bottomRight = { bounds_.bottomRight.x, pos.y + boundsDiffBotRight_.y };
            break;
        case PickSide::N:
            // uncomment if u want to scale North
            // bounds_.topLeft = { bounds_.topLeft.x, pos.y + boundsDiffTopLeft_.y };
            bounds_.topLeft = { pos.x + boundsDiffTopLeft_.x, pos.y + boundsDiffTopLeft_.y };
            bounds_.bottomRight = { pos.x + boundsDiffBotRight_.x, pos.y + boundsDiffBotRight_.y };

            break;
        case PickSide::S:
            bounds_.bottomRight = { bounds_.bottomRight.x, pos.y + boundsDiffBotRight_.y };
            break;
        case PickSide::E:
            bounds_.bottomRight = { pos.x + boundsDiffBotRight_.x, bounds_.bottomRight.y };
            break;
        case PickSide::W:
            bounds_.topLeft = { pos.x + boundsDiffTopLeft_.x , bounds_.topLeft.y };
            break;
        }
    }
    setBounds(constrainGrabBoundsFromSide(bounds_, currentlyPickedSide_));
}

const Bounds Panel::constrainGrabBoundsFromSide(const Bounds& bounds, const PickSide& side)
{
    auto scaleX = bounds.bottomRight.x - bounds.topLeft.x;
    auto scaleY = bounds.bottomRight.y - bounds.topLeft.y;
    Bounds outBounds = bounds;

    switch (side)
    {
    case PickSide::NE:
    {
        if (scaleX < minScale_.x)
        {
            scaleX = minScale_.x;
            outBounds.bottomRight.x = bounds.topLeft.x + scaleX;
        }
        if (scaleY < minScale_.y)
        {
            scaleY = minScale_.y;
            outBounds.topLeft.y = bounds.bottomRight.y - scaleY;
        }
        break;
    }
    case PickSide::NW:
    {
        if (scaleX < minScale_.x)
        {
            scaleX = minScale_.x;
            outBounds.topLeft.x = bounds.bottomRight.x - scaleX;
        }
        if (scaleY < minScale_.y)
        {
            scaleY = minScale_.y;
            outBounds.topLeft.y = bounds.bottomRight.y - scaleY;
        }
        break;
    }
    case PickSide::SE:
    {
        if (scaleX < minScale_.x)
        {
            scaleX = minScale_.x;
            outBounds.bottomRight.x = bounds.topLeft.x + scaleX;
        }
        if (scaleY < minScale_.y)
        {
            scaleY = minScale_.y;
            outBounds.bottomRight.y = bounds.topLeft.y + scaleY;
        }
        break;
    }
    case PickSide::SW:
    {
        if (scaleX < minScale_.x)
        {
            scaleX = minScale_.x;
            outBounds.topLeft.x = bounds.bottomRight.x - scaleX;
        }
        if (scaleY < minScale_.y)
        {
            scaleY = minScale_.y;
            outBounds.bottomRight.y = bounds.topLeft.y + scaleY;
        }
        break;
    }
    case PickSide::N:
    {
        if (scaleY < minScale_.y)
        {
            scaleY = minScale_.y;
            outBounds.topLeft.y = bounds.bottomRight.y - scaleY;
        }
        break;
    }
    case PickSide::S:
    {
        if (scaleY < minScale_.y)
        {
            scaleY = minScale_.y;
            outBounds.bottomRight.y = bounds.topLeft.y + scaleY;
        }
        break;
    }
    case PickSide::E:
    {
        if (scaleX < minScale_.x)
        {
            scaleX = minScale_.x;
            outBounds.bottomRight.x = bounds.topLeft.x + scaleX;
        }
        break;
    }    case PickSide::W:
    {
        if (scaleX < minScale_.x)
        {
            scaleX = minScale_.x;
            outBounds.topLeft.x = bounds.bottomRight.x - scaleX;
        }
        break;
    }
    }

    return outBounds;
}

void Panel::resetGrabbing()
{
    currentlyPickedSide_ = PickSide::OUT_OF_BOUNDS;
    failedToGrabSide_ = false;
}

const Bounds& Panel::getBounds() {
    return bounds_;
}

void Panel::adjustElementsBounds()
{
    std::cout << bounds_ << std::endl;
    std::cout << "----\n";
    std::cout << lastBounds_ << std::endl;
    // this should adjust in terms of what props the container has
    // for now must move along with parent
    // for (const auto& element : elements_)
    // {
    //     // const auto  topLeft = {};
    //     const auto currentCoundsTop = bounds_.topLeft - lastBounds_.topLeft;
    //     const auto currentCoundsBot = bounds_.bottomRight - lastBounds_.bottomRight;
    //     const auto elBounds = element->getBounds();
    //     element->setBounds({ elBounds.topLeft + currentCoundsTop, elBounds.bottomRight + currentCoundsBot });

    //     // element->setBounds({ {0,0},{0,0} });
    // }
}

void Panel::addElement(ISceneElementPtr element) {
    elements_.push_back(element);
}

void Panel::removeElement(ISceneElement& element) {
    //TODO
}

void Panel::setZIndex(int index)
{
    zIndex_ = index < 0 ? 0 : index;

    quad_->setPos(glm::vec3(bounds_.topLeft, -zIndex_));
}

const int Panel::getZIndex() const {
    return zIndex_;
}

const std::string Panel::getName()
{
    return name_;
}

PickSide Panel::getPickedSide(const glm::vec2& pos) const
{
    if (currentlyPickedSide_ != PickSide::OUT_OF_BOUNDS)
        return currentlyPickedSide_;

    // these lambdas should be removed from here in some utility package
    const auto isOnTopRegion = [&]() {
        return (pos.y <= bounds_.topLeft.y + grabOffset_ &&
            pos.y >= bounds_.topLeft.y &&
            pos.x < bounds_.bottomRight.x&& pos.x > bounds_.topLeft.x);
    };

    const auto isOnBotRegion = [&]() {
        return (pos.y >= bounds_.bottomRight.y - grabOffset_ &&
            pos.y <= bounds_.bottomRight.y &&
            pos.x < bounds_.bottomRight.x&& pos.x > bounds_.topLeft.x);
    };

    const auto isOnLeftRegion = [&]() {
        return (pos.x <= bounds_.topLeft.x + grabOffset_ &&
            pos.x >= bounds_.topLeft.x &&
            pos.y > bounds_.topLeft.y && pos.y < bounds_.bottomRight.y);
    };

    const auto isOnRightRegion = [&]() {
        return (pos.x >= bounds_.bottomRight.x - grabOffset_ &&
            pos.x <= bounds_.bottomRight.x &&
            pos.y > bounds_.topLeft.y && pos.y < bounds_.bottomRight.y);
    };


    if (isOnRightRegion() && isOnTopRegion())
        return PickSide::NE;

    if (isOnRightRegion() && isOnBotRegion())
        return PickSide::SE;

    if (isOnLeftRegion() && isOnTopRegion())
        return PickSide::NW;

    if (isOnLeftRegion() && isOnBotRegion())
        return PickSide::SW;

    if (isOnTopRegion())
        return PickSide::N;

    if (isOnBotRegion())
        return PickSide::S;

    if (isOnLeftRegion())
        return PickSide::W;

    if (isOnRightRegion())
        return PickSide::E;

    return PickSide::OUT_OF_BOUNDS;
}

// void Panel::setParent(ISceneElementPtr parent)
// {
//     parent_ = parent;
// }

void Panel::updateAndRender(const glm::mat4& projMat) {
    if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        handleGrabFromPosition({ Input::getMouseX(), Input::getMouseY() });

    if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT))
        resetGrabbing();

    quad_->draw(projMat);
    for (const auto& element : elements_)
        element->updateAndRender(projMat);
}
