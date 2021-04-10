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
#include "Ball.hpp"
#include "Timer.hpp"
#include "Assets.hpp"
#include "Checkbox.hpp"
#include "DynamicText.hpp"
#include "Vector2D.hpp"

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdint>
#include <vector>

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

    // Physics
    static bool friction_enabled = false;
    static double_t friction_amount = 25;

    void UpdateBallsPosition();
    void SetFriction(bool enable);
    // -----------------------------------------------------------
    // UI ELEMENTS
    static bool simulation_started = false;

    static Button * start_button;
    static Button * quit_button;
    static Button * open_options;
    static Button * close_options;
 
    static SolidImage * menu_background;
    static SolidImage * table_background;
    static SolidImage * top_border;
    static SolidImage * options_background;
    static SolidImage * options_icon;

    static std::vector<Ball *> balls;

    static Checkbox * physx_checkbox;
    static Checkbox * quad_tree_checkbox;
    static Checkbox * friction_checkbox;
    static Checkbox * _2x_speed;
    static Checkbox * _1x_speed;
    static Checkbox * _025x_speed;
    static Checkbox * push_force_checkbox;
    static Checkbox * pull_force_checkbox;

    static DynamicText * fps_counter;
    static DynamicText * query_counter;

    static SolidText * query_label;
    static SolidText * options_label;
    static SolidText * collisions_options_label;
    static SolidText * speed_options_label;
    static SolidText * force_field_label;

    void InitializeUIElments();
    void StartSimulation();
    void ApplyBallsPhysics();
    void UpdateStatisticCounters();
    void OpenSimulationOptions();
    void CloseSimulationOptions();

    static void Set025xSpeed(bool a);
    static void Set1xSpeed(bool a);
    static void Set2xSpeed(bool a);

    static bool push_force = true;
    static void ApplyForceField(const Vector2D & center, double_t mag);
    void SetForceFieldPush(bool enable);
    void SetForceFieldPull(bool enable);

    class ForceField : public InteractiveComponent
    {
    public:
        static ForceField * newForceField(uint16_t width, uint16_t height, double_t force_mag);

    private:
        ForceField(uint16_t width = 0, uint16_t height = 0);
        ForceField(ForceField &);
        virtual ~ForceField();

        double _force_mag;
    
    protected:
        virtual void reactToDragging(const SDL_Point & cursor_coordinates) override;
    };

    static ForceField * force_field;
}

#endif
