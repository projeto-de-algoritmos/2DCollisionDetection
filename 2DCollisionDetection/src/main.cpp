#include "RunningManager.hpp"
#include "Assets.hpp"
#include "SolidImage.hpp"

int main()
{
    RunningManager::StartDependencies();
    RunningManager::SetVerboseMode();

    SolidImage * table = SolidImage::newSolidImage(Assets::TABLE_TEXTURE_NAME, Assets::WINDOW_WIDTH, Assets::WINDOW_HEIGHT);

    Button * button = Button::newButton("Sair");
    button->setClickReaction(RunningManager::FinishProgramExecution);
    button->untie();

    while (RunningManager::ProgramIsRunning()) {
        RunningManager::StartFrame();
        RunningManager::HandleUserInput();

        // Collision code here ----


        // ------

        RunningManager::RenderScreen();
    }

    RunningManager::ReleaseDependencies();
    return 0;
}
