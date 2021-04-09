#include "RunningManager.hpp"
#include "Assets.hpp"
#include "SolidImage.hpp"
#include "Ball.hpp"
#include "CollisionDetection.hpp"
#include "Checkbox.hpp"

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

        RunningManager::RenderScreen();
    }

    RunningManager::ReleaseDependencies();
    return 0;
}
