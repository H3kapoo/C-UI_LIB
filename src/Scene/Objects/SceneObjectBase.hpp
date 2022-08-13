#pragma once

#include <string>

#include "../../Primitives/Quad.hpp"
#include "../Utility/Bounds.hpp"

namespace hekui {

    class SceneObjectBase;
    using SceneObjectBasePtr = std::shared_ptr<SceneObjectBase>;

    class SceneObjectBase
    {
    public:
        virtual void setParent(const SceneObjectBasePtr& parent) = 0;
        virtual void setBounds(const Bounds& bounds) = 0;
        virtual void setZIndex(int index) = 0;
        virtual void render(const glm::mat4& projMat) const = 0;
        virtual void update() = 0;
        virtual void setBackgroundColor(const glm::vec3 color) = 0;

        virtual void setSelected() = 0;
        virtual const int getZIndex() const = 0;
        virtual void reset() = 0;

        virtual const std::string getName() const = 0;
        virtual const Bounds& getBounds() const = 0;
        virtual void addChild(const SceneObjectBasePtr& child) = 0;

    };

    using SceneObjectBaseVec = std::vector<SceneObjectBasePtr>;
}