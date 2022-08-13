#include "Input.hpp"

std::function<void(double xPos, double yPos)> Input::notifyMouseCursorPosEvent = [](double xPos, double yPos) {};
std::function<void(int button, int action, int mods)> Input::notifyMouseButtonEvent = [](int button, int action, int mods) {};
std::function<void(int key, int scancode, int action, int mods)> Input::notifyKeyboardEvent = [](int key, int scancode, int action, int mods) {};

std::shared_ptr<Window> Input::window_ = nullptr;
bool Input::isMouseDragging_ = false;
bool Input::oncePressedKeys[256] = { 0 };
bool Input::previouslyPressedKeys[256] = { 0 };
bool Input::currentlyPressedKeys[256] = { 0 };
float Input::lastMouseX = 0;
float Input::lastMouseY = 0;
float Input::mouseOffsetX = 0;
float Input::mouseOffsetY = 0;
