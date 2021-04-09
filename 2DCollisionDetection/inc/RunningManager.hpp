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
#include <cmath>
#include <cstdint>

namespace RunningManager
{
    static Timer timer;
    static SDL_Event event;
    static bool program_running = true;
    static Timer physics_timer;
    static bool physics = false;
    static bool quad_tree = false;

    // In secs
    static double_t statistics_window_time = 0.5;

    static Timer statistics_timer;
    static int32_t operations_perfomed;
    static int32_t frames_performed;
    static double_t mean_operations_performed = 0;

    static double_t mean_fps = 0;

    void StartFrame();
    void FinishFrame();
    void HandleUserInput();
    void FinishProgramExecution();
    bool ProgramIsRunning();
    void StartDependencies();
    void SetVerboseMode();
    void ReleaseDependencies();
    void RenderScreen();
    double_t PhysicsDeltaTime();
    void ResetPhysicsTimer();
    bool PhysicsIsEnabled();
    void SetPhysics(bool enable);
    bool EfficientAlgorithmIsEnabled();
    void SetEfficientAlgorithm(bool enable);

    static void UpdateStatistics();
    void IncrementOperationsPerfomed();
    double_t MeanOperationsPerFrame();
    double_t MeanFramesPerSecond();
}

#endif
