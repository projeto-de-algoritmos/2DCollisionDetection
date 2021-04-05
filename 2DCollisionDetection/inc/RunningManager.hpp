#ifndef _RUNNING_MANAGER_HPP_
#define _RUNNING_MANAGER_HPP_

#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include "Button.hpp"
#include "Helpers.hpp"
#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include "VisualComponent.hpp"
//#include "Ball.hpp"
#include "Timer.hpp"
#include "Assets.hpp"
#include <SDL2/SDL.h>

namespace RunningManager
{
    static Timer timer;
    static SDL_Event event;
    static bool program_running = true;

    void StartFrame();
    void FinishFrame();
    void HandleUserInput();
    void FinishProgramExecution();
    bool ProgramIsRunning();
    void StartDependencies();
    void SetVerboseMode();
    void ReleaseDependencies();
    void RenderScreen();

    void StartFrame()
    {
        double_t elapsed_time = timer.getElapsedTime();
        if (elapsed_time < Assets::_60_FPS_FRAMETIME)
            SDL_Delay(int32_t((Assets::_60_FPS_FRAMETIME - elapsed_time) * 1000.0));
        
        timer.reset();
    }

    void HandleUserInput()
    {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                FinishProgramExecution();
            else if (event.type == SDL_KEYDOWN)
                InteractiveComponent::processKeyPressing(event.key.keysym.sym);
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                InteractiveComponent::processMouseButtonDown({event.button.x, event.button.y});
            else if (event.type == SDL_MOUSEBUTTONUP)
                InteractiveComponent::processMouseButtonUp({event.button.x, event.button.y});
            // Not necessary
            else if (event.type == SDL_MOUSEMOTION)
                InteractiveComponent::processMouseMotion({event.motion.x, event.motion.y});
        }
    }

    void FinishProgramExecution()
    {
        program_running = false;
    }

    bool ProgramIsRunning()
    {
        return program_running;
    }

    void StartDependencies()
    {
        Graphics::startUp();
        VisualComponent::startUp();
        InteractiveComponent::startUp();
    }

    void SetVerboseMode()
    {
        AssetsManager::setVerboseMode();
        VisualComponent::setVerboseMode();
    }

    void ReleaseDependencies()
    {
        VisualComponent::shutDown();
        AssetsManager::shutDown();
        Graphics::shutDown();
    }

    void RenderScreen()
    {
        VisualComponent::drawComponents();
    }
}

#endif
