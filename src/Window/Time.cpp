#include "Time.hpp"

double Time::deltaTime = 0;
double Time::lastFrameDelta = 0;
int Time::waitedFrames = 0;
int Time::framesToWait = 4;
