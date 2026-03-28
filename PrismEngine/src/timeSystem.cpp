#include "timeSystem.h"
#include "timeResource.h"
#include <chrono>
#include <SDL_timer.h>

void prism::scene::TimeSystem::start()
{
    lastTime = std::chrono::steady_clock::now();
}

void prism::scene::TimeSystem::update()
{
    frameStartTime = std::chrono::steady_clock::now();

    auto currentTime = std::chrono::steady_clock::now();
    double_t rawDeltaTime = std::chrono::duration<double_t>(currentTime - lastTime).count();
    lastTime = currentTime;

    TimeResource* time = scene->getResource<TimeResource>();
    if (!time) return;
    time->update(rawDeltaTime);

    if (time->isFpsCap())
    {
        double_t waitTime = time->calculateWaitTime(frameStartTime);

        if (waitTime > 0.0)
        {
            SDL_Delay(static_cast<Uint32>(waitTime * 1000.0));
        }
    }
}