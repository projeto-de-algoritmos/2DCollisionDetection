#include "RunningManager.hpp"
#include <functional>

int main()
{
    RunningManager::StartDependencies();
    RunningManager::SetVerboseMode();

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
