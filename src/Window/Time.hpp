//
// Created by hekapoo on 20.05.2022.
//

#pragma once

#include <GLFW/glfw3.h>

class Time
{
private:
    static double deltaTime;
    static double lastFrameDelta;
    static int waitedFrames, framesToWait;

    Time(){};

public:
    static void computeDelta()
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrameDelta;
        lastFrameDelta = currentFrame;
    }

    static double getDeltaTime()
    {
        // first few times this is called will return large numbers
        // until it stabilises, just wait X frames before actually
        // returning a valid delta
        if (waitedFrames < framesToWait)
        {
            waitedFrames++;
            return 1000;
        }
        return deltaTime;
    }

    static float getNowTime() { return glfwGetTime(); }

    Time(Time const &) = delete;
    void operator=(Time const &) = delete;
};
