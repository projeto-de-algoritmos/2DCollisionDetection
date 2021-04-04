#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include "Button.hpp"
#include "Helpers.hpp"
#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include "VisualComponent.hpp"

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

    // Your code here ----



    // ----


    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();
    return 0;
}