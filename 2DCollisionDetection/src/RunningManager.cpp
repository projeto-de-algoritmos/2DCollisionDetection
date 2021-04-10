#include "RunningManager.hpp"
#include "CollisionDetection.hpp"
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

void RunningManager::UpdateBallsPosition()
{
    for (auto ball : balls) {
        if (friction_enabled)
            ball->updateVelocity(RunningManager::PhysicsDeltaTime(), friction_amount);

        ball->updateBallPosition(RunningManager::PhysicsDeltaTime());
        ball->turnOffBallHighlight();
    }
    RunningManager::ResetPhysicsTimer();
}

void RunningManager::SetFriction(bool enable)
{
    friction_enabled = enable;
}

void RunningManager::InitializeUIElments()
{
    menu_background = SolidImage::newSolidImage(Assets::MAIN_MENU_BACKGROUND, Assets::WINDOW_WIDTH, Assets::WINDOW_HEIGHT);

    
    start_button = Button::newButton("Iniciar");
    start_button->setClickReaction(StartSimulation);
    start_button->setRelativeX(Assets::WINDOW_WIDTH / 2 + 5);
    start_button->setRelativeY(Assets::WINDOW_HEIGHT - start_button->getHeight() - 10);

    table_background = SolidImage::newSolidImage(Assets::TABLE_TEXTURE_NAME, Assets::TABLE_WIDTH, Assets::TABLE_HEIGHT);
    table_background->hide();

    srand((unsigned)time(0));
    for (int i = 0; i < 15; i++) {
        balls.push_back(Ball::newBall(rand() % 720, rand() % 480, rand() % 200 + 100, rand() % 200 + 100));
        balls.back()->hide();
    }

    top_border = SolidImage::newSolidImage("top_border.png", 200, 60);
    top_border->setRelativeX(Assets::WINDOW_WIDTH / 2 - top_border->getWidth() / 2);
    top_border->setRelativeY(0);
    top_border->hide();

    // Simulation Options
    options_background = SolidImage::newSolidImage(Assets::OPTIONS_BACKGROUND_NAME, Assets::OPTIONS_WIDTH, Assets::OPTIONS_HEIGHT);
    options_background->setRelativeX(Assets::WINDOW_WIDTH / 2 - options_background->getWidth() / 2);
    options_background->setRelativeY(0);
    options_background->hide();

    options_label = SolidText::newSolidText("Opcoes", Assets::SOLIDTEXT_FONT_NAME, 24);
    options_label->hide();

    options_icon = SolidImage::newSolidImage(Assets::OPTIONS_ICON_NAME, Assets::OPTIONS_ICON_WIDTH, Assets::OPTIONS_ICON_HEIGHT);
    options_icon->setParent(options_background);
    options_icon->setRelativeX(options_background->getWidth() / 2 - (options_icon->getWidth() + options_label->getWidth()) / 2 - 5);
    options_icon->setRelativeY(10);
    options_icon->hide();

    options_label->setParent(options_icon);
    options_label->setRelativeX(options_icon->getWidth() + 5);
    options_label->setRelativeY(options_icon->getHeight() / 2 - options_label->getHeight() / 2);

    open_options = Button::newButton("Opcoes");
    open_options->setClickReaction(RunningManager::OpenSimulationOptions);
    open_options->setRelativeX(Assets::WINDOW_WIDTH / 2 + 5);
    open_options->setRelativeY(Assets::WINDOW_HEIGHT - open_options->getHeight() - 10);
    open_options->hide();
    open_options->deactivate();

    collisions_options_label = SolidText::newSolidText("Fisica");
    collisions_options_label->setParent(options_icon);
    collisions_options_label->setRelativeX(0);
    collisions_options_label->setRelativeY(options_icon->getHeight() + 5);
    collisions_options_label->hide();

    physx_checkbox = Checkbox::newCheckbox("Habilitar Colisao");
    physx_checkbox->setParent(collisions_options_label);
    physx_checkbox->setRelativeX(0);
    physx_checkbox->setRelativeY(collisions_options_label->getHeight() + 1);
    physx_checkbox->setCheckReaction(RunningManager::SetPhysics);
    physx_checkbox->hide();
    physx_checkbox->deactivate();

    quad_tree_checkbox = Checkbox::newCheckbox("Habilitar Quad-Tree");
    quad_tree_checkbox->setParent(physx_checkbox);
    quad_tree_checkbox->setRelativeX(0);
    quad_tree_checkbox->setRelativeY(quad_tree_checkbox->getHeight() + 1);
    quad_tree_checkbox->setCheckReaction(RunningManager::SetEfficientAlgorithm);
    quad_tree_checkbox->hide();
    quad_tree_checkbox->deactivate();

    friction_checkbox = Checkbox::newCheckbox("Habilitar Atrito");
    friction_checkbox->setParent(quad_tree_checkbox);
    friction_checkbox->setRelativeX(0);
    friction_checkbox->setRelativeY(quad_tree_checkbox->getHeight() + 1);
    friction_checkbox->setCheckReaction(RunningManager::SetFriction);
    friction_checkbox->hide();
    friction_checkbox->deactivate();

    speed_options_label = SolidText::newSolidText("Velocidade");
    speed_options_label->setParent(friction_checkbox);
    speed_options_label->setRelativeX(0);
    speed_options_label->setRelativeY(friction_checkbox->getHeight() + 10);
    speed_options_label->hide();

    _025x_speed = Checkbox::newCheckbox("0.25x");
    _025x_speed->setParent(speed_options_label);
    _025x_speed->setRelativeX(0);
    _025x_speed->setRelativeY(speed_options_label->getHeight() + 1);
    _025x_speed->hide();
    _025x_speed->deactivate();
    _025x_speed->setCheckReaction(RunningManager::Set025xSpeed);

    _1x_speed = Checkbox::newCheckbox("1.0x");
    _1x_speed->setParent(_025x_speed);
    _1x_speed->setRelativeX(0);
    _1x_speed->setRelativeY(_025x_speed->getHeight() + 1);
    _1x_speed->hide();
    _1x_speed->deactivate();
    _1x_speed->setCheckReaction(RunningManager::Set1xSpeed);

    _2x_speed = Checkbox::newCheckbox("2.0x");
    _2x_speed->setParent(_1x_speed);
    _2x_speed->setRelativeX(0);
    _2x_speed->setRelativeY(_1x_speed->getHeight() + 1);
    _2x_speed->hide();
    _2x_speed->deactivate();
    _2x_speed->setCheckReaction(RunningManager::Set2xSpeed);

    force_field_label = SolidText::newSolidText("Campo de Forca");
    force_field_label->setParent(_2x_speed);
    force_field_label->setRelativeX(0);
    force_field_label->setRelativeY(_2x_speed->getHeight() + 10);
    force_field_label->hide();

    push_force_checkbox = Checkbox::newCheckbox("Atrair bolas ao pressionar e arrastar");
    push_force_checkbox->setParent(force_field_label);
    push_force_checkbox->setRelativeX(0);
    push_force_checkbox->setRelativeY(force_field_label->getHeight()+1);
    push_force_checkbox->hide();
    push_force_checkbox->setCheckReaction(RunningManager::SetForceFieldPush);

    pull_force_checkbox = Checkbox::newCheckbox("Repelir bolas ao pressionar e arrastar");
    pull_force_checkbox->setParent(push_force_checkbox);
    pull_force_checkbox->setRelativeX(0);
    pull_force_checkbox->setRelativeY(push_force_checkbox->getHeight()+1);
    pull_force_checkbox->hide();
    pull_force_checkbox->deactivate();
    pull_force_checkbox->setCheckReaction(RunningManager::SetForceFieldPull);

    push_force_checkbox->check();
    push_force_checkbox->deactivate();
    push_force_checkbox->hide();

    close_options = Button::newButton("Fechar");
    close_options->setClickReaction(RunningManager::CloseSimulationOptions);
    close_options->setParent(pull_force_checkbox);
    close_options->setGlobalX(Assets::WINDOW_WIDTH / 2 - close_options->getWidth() / 2);
    close_options->setRelativeY(pull_force_checkbox->getHeight() + 5);
    close_options->hide();
    close_options->deactivate();
    
    _1x_speed->check();
    _1x_speed->hide();

    // Statistics counters
    fps_counter = DynamicText::newDynamicText("00", Assets::DYNAMICTEXT_FONT_NAME, 20, {0xff, 0xff, 0x0, 0xff});
    fps_counter->setRelativeX(Assets::TABLE_WIDTH - fps_counter->getWidth() - 10);
    fps_counter->setRelativeY(10);
    fps_counter->hide();
    
    query_label = SolidText::newSolidText("Comparacoes por frame:");
    query_label->setRelativeX(Assets::WINDOW_WIDTH / 2 - query_label->getWidth() / 2);
    query_label->hide();

    query_counter = DynamicText::newDynamicText("000");
    query_counter->setParent(query_label);
    query_counter->setRelativeX(query_label->getWidth() / 2 - query_counter->getWidth() / 2);
    query_counter->setRelativeY(query_label->getHeight() + 5);
    query_counter->hide();

    quit_button = Button::newButton("Sair");
    quit_button->setClickReaction(RunningManager::FinishProgramExecution);
    quit_button->setRelativeX(Assets::WINDOW_WIDTH / 2 - quit_button->getWidth() - 5);
    quit_button->setRelativeY(Assets::WINDOW_HEIGHT - quit_button->getHeight() - 10);

    force_field = ForceField::newForceField(Assets::TABLE_WIDTH, Assets::TABLE_HEIGHT, 15);
    force_field->deactivate();
    force_field->hide();
}

void RunningManager::StartSimulation()
{
    simulation_started = true;
    start_button->hide();
    start_button->deactivate();

    menu_background->hide();
    table_background->show();
    top_border->show();

    open_options->show();
    open_options->activate();

    for (auto ball : balls)
        ball->show();

    fps_counter->show();
    query_counter->show();
    query_label->show();

    force_field->activate();
}

void RunningManager::ApplyBallsPhysics()
{
    if (!simulation_started)
        return;

    if (RunningManager::EfficientAlgorithmIsEnabled())
        ColDetect::EfficientCollisionDetection(balls, Assets::TABLE_WIDTH, Assets::TABLE_HEIGHT);
    else
        ColDetect::NaiveCollisionDetection(balls);
}

void RunningManager::UpdateStatisticCounters()
{
    if (simulation_started) {
        fps_counter->setText(std::to_string(int32_t(RunningManager::MeanFramesPerSecond())));
        query_counter->setText(std::to_string(int32_t(RunningManager::MeanOperationsPerFrame())));
    }
}

void RunningManager::OpenSimulationOptions()
{
    options_background->show();
    options_label->show();
    options_icon->show();

    collisions_options_label->show();
    speed_options_label->show();
    _025x_speed->show();
    _025x_speed->activate();

    _1x_speed->show();
    _1x_speed->activate();

    _2x_speed->show();
    _2x_speed->activate();

    physx_checkbox->show();
    physx_checkbox->activate();

    quad_tree_checkbox->show();
    quad_tree_checkbox->activate();

    friction_checkbox->show();
    friction_checkbox->activate();

    force_field_label->show();

    push_force_checkbox->show();
    push_force_checkbox->activate();

    pull_force_checkbox->show();
    pull_force_checkbox->activate();

    close_options->show();
    close_options->activate();

    query_counter->hide();
    query_label->hide();
}

void RunningManager::CloseSimulationOptions()
{
    options_background->hide();
    options_label->hide();
    options_icon->hide();

    collisions_options_label->hide();
    speed_options_label->hide();
    _025x_speed->hide();
    _025x_speed->deactivate();

    _1x_speed->hide();
    _1x_speed->deactivate();

    _2x_speed->hide();
    _2x_speed->deactivate();

    physx_checkbox->hide();
    physx_checkbox->deactivate();

    quad_tree_checkbox->hide();
    quad_tree_checkbox->deactivate();

    friction_checkbox->hide();
    friction_checkbox->deactivate();

    force_field_label->hide();
    
    push_force_checkbox->hide();
    push_force_checkbox->deactivate();

    pull_force_checkbox->hide();
    pull_force_checkbox->deactivate();

    close_options->hide();
    close_options->deactivate();

    query_counter->show();
    query_label->show();
}

void RunningManager::Set025xSpeed(bool check)
{
    if (check) {
        physics_timer.setTimeScale(0.25);
        _1x_speed->uncheck();
        _2x_speed->uncheck();
    }
    else if (!_1x_speed->isChecked() && !_2x_speed->isChecked())
        _1x_speed->check();
}

void RunningManager::Set1xSpeed(bool check)
{
    if (check) {
        physics_timer.setTimeScale(1.0);
        _025x_speed->uncheck();
        _2x_speed->uncheck();
    }
    else if (!_025x_speed->isChecked() && !_2x_speed->isChecked())
        _1x_speed->check();
}

void RunningManager::Set2xSpeed(bool check)
{
    if (check) {
        physics_timer.setTimeScale(2.0);
        _025x_speed->uncheck();
        _1x_speed->uncheck();
    }
    else if (!_025x_speed->isChecked() && !_1x_speed->isChecked())
        _1x_speed->check();
}

void RunningManager::ApplyForceField(const Vector2D & center, double_t mag)
{
    for (auto ball : balls) {
        Vector2D force(ball->getXCoordinate() - center.x(), ball->getYCoordinate() - center.y());
        if (push_force)
            force = force * (-mag / force.magnitude());
        else
            force = force * (mag / force.magnitude());
        ball->setVelocity(ball->getVelocity() + force);
    }
}

void RunningManager::SetForceFieldPush(bool enable)
{
    if (enable) {
        push_force = true;
        pull_force_checkbox->uncheck();
    }
    else if (!pull_force_checkbox->isChecked())
        push_force_checkbox->check();
}

void RunningManager::SetForceFieldPull(bool enable)
{
    if (enable) {
        push_force = false;
        push_force_checkbox->uncheck();
    }
    else if (!push_force_checkbox->isChecked())
        pull_force_checkbox->check();
}

RunningManager::ForceField * RunningManager::ForceField::newForceField(uint16_t width, uint16_t height, double_t force_mag)
{
    ForceField * ff = new ForceField(width, height);
    ff->_force_mag = force_mag;

    return ff;
}

RunningManager::ForceField::ForceField(uint16_t width, uint16_t height):
InteractiveComponent(width, height)
{

}

RunningManager::ForceField::ForceField(RunningManager::ForceField & ff):
InteractiveComponent(0,0)
{

}

RunningManager::ForceField::~ForceField()
{

}

void RunningManager::ForceField::reactToDragging(const SDL_Point & cc)
{
    ApplyForceField(Vector2D(cc.x, cc.y), _force_mag);
}
