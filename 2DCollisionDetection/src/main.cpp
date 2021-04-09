#include "RunningManager.hpp"
#include "Assets.hpp"
#include "SolidImage.hpp"
#include "Ball.hpp"
#include "CollisionDetection.hpp"
#include "Checkbox.hpp"
#include "DynamicText.hpp"

#include <vector>
#include <iostream>
#include <ctime>

int main()
{
    RunningManager::StartDependencies();
    //RunningManager::SetVerboseMode();

    SolidImage::newSolidImage(Assets::TABLE_TEXTURE_NAME, Assets::WINDOW_WIDTH, Assets::WINDOW_HEIGHT);


    srand((unsigned)time(0));
    std::vector<Ball *> balls;
    for (int i = 0; i < 15; i++)
        balls.push_back(Ball::newBall(rand() % 720, rand() % 480, rand() % 200 + 100, rand() % 200 + 100));

    Button * button = Button::newButton("Sair");
    button->setClickReaction(RunningManager::FinishProgramExecution);
    button->setRelativeX(Assets::WINDOW_WIDTH / 2 - button->getWidth() / 2);
    button->setRelativeY(Assets::WINDOW_HEIGHT - button->getHeight() - 10);

    Checkbox * physx_checkbox = Checkbox::newCheckbox("Habilitar Fisica");
    physx_checkbox->setRelativeX(10);
    physx_checkbox->setRelativeY(10);
    physx_checkbox->setCheckReaction(RunningManager::SetPhysics);

    Checkbox * quad_tree_checkbox = Checkbox::newCheckbox("Habilitar Quad-Tree");
    quad_tree_checkbox->setParent(physx_checkbox);
    quad_tree_checkbox->setRelativeX(0);
    quad_tree_checkbox->setRelativeY(quad_tree_checkbox->getHeight() + 10);
    quad_tree_checkbox->setCheckReaction(RunningManager::SetEfficientAlgorithm);

    SolidImage * top_border = SolidImage::newSolidImage("top_border.png", 206, 60);
    top_border->setRelativeX(Assets::WINDOW_WIDTH / 2 - top_border->getWidth() / 2);

    DynamicText * fps_counter = DynamicText::newDynamicText("00");
    fps_counter->setRelativeX(Assets::TABLE_WIDTH - fps_counter->getWidth() - 10);
    fps_counter->setRelativeY(10);

    SolidText * query_label = SolidText::newSolidText("Queries por frame:");
    query_label->setParent(top_border);
    query_label->setRelativeX(top_border->getWidth() / 2 - query_label->getWidth() / 2);

    DynamicText * query_counter = DynamicText::newDynamicText("000");
    query_counter->setParent(query_label);
    query_counter->setRelativeX(query_label->getWidth() / 2 - query_counter->getWidth() / 2);
    query_counter->setRelativeY(query_label->getHeight() + 5);

    while (RunningManager::ProgramIsRunning()) {
        RunningManager::StartFrame();
        RunningManager::HandleUserInput();

        for (auto ball : balls) {
            ball->updateBallPosition(RunningManager::PhysicsDeltaTime());
            ball->turnOffBallHighlight();
        }
        RunningManager::ResetPhysicsTimer();
        
        if (RunningManager::EfficientAlgorithmIsEnabled())
            ColDetect::EfficientCollisionDetection(balls, Assets::TABLE_WIDTH, Assets::TABLE_HEIGHT);
        else
            ColDetect::NaiveCollisionDetection(balls);

        fps_counter->setText(std::to_string(int32_t(RunningManager::MeanFramesPerSecond())));
        query_counter->setText(std::to_string(int32_t(RunningManager::MeanOperationsPerFrame())));

        RunningManager::RenderScreen();
        RunningManager::FinishFrame();
    }

    RunningManager::ReleaseDependencies();
    return 0;
}
