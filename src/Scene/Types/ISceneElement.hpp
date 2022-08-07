#pragma once

#include <string>

#include "../../Primitives/Quad.hpp"

struct Bounds {
    glm::vec2 topLeft, bottomRight;
    Bounds() : topLeft{ 0 }, bottomRight{ 0 } {}
    Bounds(glm::vec2 topLeft, glm::vec2 bottomRight) : topLeft{ topLeft }, bottomRight{ bottomRight } {}

    friend std::ostream& operator<< (std::ostream& stream, const Bounds& bounds) {
        stream << "TOP_LEFT ( " << bounds.topLeft.x << " ," << bounds.topLeft.y << ")" <<
            "-- BOTTOM_RIGHT ( " << bounds.bottomRight.x << " ," << bounds.bottomRight.y << ")";
        return stream;
    }
};

class ISceneElement
{
public:
    virtual void setBounds(const Bounds& bounds) = 0;
    virtual const Bounds& getBounds() = 0;
    virtual void render(const glm::mat4& projMat) = 0;
};

using ISceneElementPtr = std::shared_ptr<ISceneElement>;
