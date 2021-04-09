#include "RunningManager.hpp"
#include <iostream>

void RunningManager::StartFrame()
{
    double_t elapsed_time = timer.getElapsedTime();
    if (elapsed_time < Assets::_60_FPS_FRAMETIME)
        SDL_Delay(int32_t((Assets::_60_FPS_FRAMETIME - elapsed_time) * 1000.0));
    
    timer.reset();
}

void RunningManager::FinishFrame()
{
    frames_performed++;
}

void RunningManager::HandleUserInput()
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

void RunningManager::FinishProgramExecution()
{
    program_running = false;
}

bool RunningManager::ProgramIsRunning()
{
    return program_running;
}

void RunningManager::StartDependencies()
{
    Graphics::startUp();
    VisualComponent::startUp();
    InteractiveComponent::startUp();
}

void RunningManager::SetVerboseMode()
{
    AssetsManager::setVerboseMode();
    VisualComponent::setVerboseMode();
}

void RunningManager::ReleaseDependencies()
{
    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();
}

void RunningManager::RenderScreen()
{
    VisualComponent::drawComponents();
}

double_t RunningManager::PhysicsDeltaTime()
{
    return physics_timer.getElapsedTime();
}

void RunningManager::ResetPhysicsTimer()
{
    physics_timer.reset();
}

bool RunningManager::PhysicsIsEnabled()
{
    return physics;
}

void RunningManager::SetPhysics(bool enable)
{
    physics = enable;
}

bool RunningManager::EfficientAlgorithmIsEnabled()
{
    return quad_tree;
}

void RunningManager::SetEfficientAlgorithm(bool enable)
{
    quad_tree = enable;
}

void RunningManager::IncrementOperationsPerfomed()
{
    operations_perfomed++;
}

void RunningManager::UpdateStatistics()
{
    //std::cout << "sta timer: " << statistics_timer.getElapsedTime() << "\n";
    if (statistics_timer.getElapsedTime() < statistics_window_time)
        return;
    
    mean_operations_performed = double_t(operations_perfomed) / double_t(frames_performed);
    mean_fps = double_t(frames_performed) / statistics_timer.getElapsedTime();
    frames_performed = 0;
    operations_perfomed = 0;
    statistics_timer.reset();
}

double_t RunningManager::MeanOperationsPerFrame()
{
    UpdateStatistics();
    return mean_operations_performed;
}

double_t RunningManager::MeanFramesPerSecond()
{
    UpdateStatistics();
    return mean_fps;
}