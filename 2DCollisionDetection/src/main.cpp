#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include "Button.hpp"
#include "Helpers.hpp"
#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include "VisualComponent.hpp"
#include <SDL2/SDL.h>

int main()
{
    Graphics::startUp();
    VisualComponent::startUp();
    InteractiveComponent::startUp();

#define VERBOSE 0
#if VERBOSE
    AssetsManager::setVerboseMode();
    VisualComponent::setVerboseMode();
    
#endif

    // Loop code

    SDL_Event e;
    bool run = true;

    Graphics * graphics = Graphics::getInstance();

    while (run) {
        while (SDL_PollEvent(&e) != 0)
            if (e.type == SDL_QUIT)
                run = false;
        
        graphics->clearScreen();
        graphics->updateScreen();
        
        SDL_Delay(16);
    }

    // ----


    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();
    return 0;
}