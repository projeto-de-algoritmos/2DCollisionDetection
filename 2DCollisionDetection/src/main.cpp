#include "RunningManager.hpp"
#include <functional>

int main()
{
    RunningManager::StartDependencies();
    RunningManager::SetVerboseMode();

    Button::newButton("Sair")->setClickReaction(RunningManager::FinishProgramExecution);

    while (RunningManager::ProgramIsRunning()) {
        RunningManager::StartFrame();
        RunningManager::HandleUserInput();

        // Collision code here ----


        // ------

        RunningManager::RenderScreen();
        RunningManager::FinishFrame();
    }

    RunningManager::ReleaseDependencies();
    return 0;
}