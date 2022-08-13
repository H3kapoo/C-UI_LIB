#pragma once

#include <glm/glm.hpp>
#include <iostream>

namespace hekui {
    enum class PickSide {
        N, E, S, W, SE, SW, NE, NW, OUT_OF_BOUNDS
    };

    struct Bounds {
    private:

    public:
        glm::vec2 topLeft, bottomRight;
        Bounds() : topLeft{ 0 }, bottomRight{ 0 } {}
        Bounds(glm::vec2 topLeft, glm::vec2 bottomRight) : topLeft{ topLeft }, bottomRight{ bottomRight } {}

        bool isCleared() {
            return (topLeft.x == 0 && topLeft.y == 0 && bottomRight.x == 0 && bottomRight.y == 0);
        }

        void clear() { topLeft = { 0,0 }; bottomRight = { 0,0 }; }

        static const PickSide getPickSide(const Bounds& bounds, int grabOffset, const glm::vec2& pos)
        {
            // this check could be removed
            // if (currentlyPickedSide != PickSide::OUT_OF_BOUNDS)
            //     return currentlyPickedSide;

            // these lambdas should be removed from here in some utility package
            const auto isOnTopRegion = [&]() {
                return (pos.y <= bounds.topLeft.y + grabOffset &&
                    pos.y >= bounds.topLeft.y &&
                    pos.x < bounds.bottomRight.x&& pos.x > bounds.topLeft.x);
            };

            const auto isOnBotRegion = [&]() {
                return (pos.y >= bounds.bottomRight.y - grabOffset &&
                    pos.y <= bounds.bottomRight.y &&
                    pos.x < bounds.bottomRight.x&& pos.x > bounds.topLeft.x);
            };

            const auto isOnLeftRegion = [&]() {
                return (pos.x <= bounds.topLeft.x + grabOffset &&
                    pos.x >= bounds.topLeft.x &&
                    pos.y > bounds.topLeft.y && pos.y < bounds.bottomRight.y);
            };

            const auto isOnRightRegion = [&]() {
                return (pos.x >= bounds.bottomRight.x - grabOffset &&
                    pos.x <= bounds.bottomRight.x &&
                    pos.y > bounds.topLeft.y && pos.y < bounds.bottomRight.y);
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

        static const Bounds constrainBoundsFromSide(const Bounds& bounds, const PickSide& side, const glm::vec2& minScale)
        {
            auto scaleX = bounds.bottomRight.x - bounds.topLeft.x;
            auto scaleY = bounds.bottomRight.y - bounds.topLeft.y;
            Bounds outBounds = bounds;

            switch (side)
            {
            case PickSide::NE:
            {
                if (scaleX < minScale.x)
                {
                    scaleX = minScale.x;
                    outBounds.bottomRight.x = bounds.topLeft.x + scaleX;
                }
                if (scaleY < minScale.y)
                {
                    scaleY = minScale.y;
                    outBounds.topLeft.y = bounds.bottomRight.y - scaleY;
                }
                break;
            }
            case PickSide::NW:
            {
                if (scaleX < minScale.x)
                {
                    scaleX = minScale.x;
                    outBounds.topLeft.x = bounds.bottomRight.x - scaleX;
                }
                if (scaleY < minScale.y)
                {
                    scaleY = minScale.y;
                    outBounds.topLeft.y = bounds.bottomRight.y - scaleY;
                }
                break;
            }
            case PickSide::SE:
            {
                if (scaleX < minScale.x)
                {
                    scaleX = minScale.x;
                    outBounds.bottomRight.x = bounds.topLeft.x + scaleX;
                }
                if (scaleY < minScale.y)
                {
                    scaleY = minScale.y;
                    outBounds.bottomRight.y = bounds.topLeft.y + scaleY;
                }
                break;
            }
            case PickSide::SW:
            {
                if (scaleX < minScale.x)
                {
                    scaleX = minScale.x;
                    outBounds.topLeft.x = bounds.bottomRight.x - scaleX;
                }
                if (scaleY < minScale.y)
                {
                    scaleY = minScale.y;
                    outBounds.bottomRight.y = bounds.topLeft.y + scaleY;
                }
                break;
            }
            case PickSide::N:
            {
                if (scaleY < minScale.y)
                {
                    scaleY = minScale.y;
                    outBounds.topLeft.y = bounds.bottomRight.y - scaleY;
                }
                break;
            }
            case PickSide::S:
            {
                if (scaleY < minScale.y)
                {
                    scaleY = minScale.y;
                    outBounds.bottomRight.y = bounds.topLeft.y + scaleY;
                }
                break;
            }
            case PickSide::E:
            {
                if (scaleX < minScale.x)
                {
                    scaleX = minScale.x;
                    outBounds.bottomRight.x = bounds.topLeft.x + scaleX;
                }
                break;
            }    case PickSide::W:
            {
                if (scaleX < minScale.x)
                {
                    scaleX = minScale.x;
                    outBounds.topLeft.x = bounds.bottomRight.x - scaleX;
                }
                break;
            }
            }

            return outBounds;
        }

        static const Bounds getNewBoundsFromGrabSide(const Bounds& bounds,
            const PickSide& currentlyPickedSide, const glm::vec2& pos,
            const Bounds& boundsDiff)
        {
            Bounds newBounds = bounds;
            if (currentlyPickedSide != PickSide::OUT_OF_BOUNDS)
            {
                switch (currentlyPickedSide)
                {
                case PickSide::NE:
                    newBounds.bottomRight = { pos.x + boundsDiff.bottomRight.x, bounds.bottomRight.y };
                    newBounds.topLeft = { bounds.topLeft.x ,pos.y + boundsDiff.topLeft.y };
                    break;
                case PickSide::NW:
                    newBounds.topLeft = { pos.x + boundsDiff.topLeft.x, pos.y + boundsDiff.topLeft.y };
                    break;
                case PickSide::SE:
                    newBounds.bottomRight = { pos.x + boundsDiff.bottomRight.x, pos.y + boundsDiff.bottomRight.y };
                    break;
                case PickSide::SW:
                    newBounds.topLeft = { pos.x + boundsDiff.topLeft.x , bounds.topLeft.y };
                    newBounds.bottomRight = { bounds.bottomRight.x, pos.y + boundsDiff.bottomRight.y };
                    break;
                case PickSide::N:
                    // uncomment if u want to scale North
                    // newBounds.topLeft = { bounds.topLeft.x, pos.y + boundsDiffTopLeft_.y };
                    newBounds.topLeft = { pos.x + boundsDiff.topLeft.x, pos.y + boundsDiff.topLeft.y };
                    newBounds.bottomRight = { pos.x + boundsDiff.bottomRight.x, pos.y + boundsDiff.bottomRight.y };

                    break;
                case PickSide::S:
                    newBounds.bottomRight = { bounds.bottomRight.x, pos.y + boundsDiff.bottomRight.y };
                    break;
                case PickSide::E:
                    newBounds.bottomRight = { pos.x + boundsDiff.bottomRight.x, bounds.bottomRight.y };
                    break;
                case PickSide::W:
                    newBounds.topLeft = { pos.x + boundsDiff.topLeft.x , bounds.topLeft.y };
                    break;
                }
            }

            return newBounds;
        }

        friend std::ostream& operator<< (std::ostream& stream, const Bounds& bounds) {
            stream << "TOP_LEFT ( " << bounds.topLeft.x << " ," << bounds.topLeft.y << ")" <<
                "-- BOTTOM_RIGHT ( " << bounds.bottomRight.x << " ," << bounds.bottomRight.y << ")";
            return stream;
        }
    };
}
