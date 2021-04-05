#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>

// Every project asset/property should be referenced here

namespace Assets
{
    // Button assets
    const std::string   BUTTON_FONT_NAME = "arial.ttf",
                        BUTTON_BACKGROUND_IMAGE_NAME = "button_background.png",
                        BUTTON_SHADE_NAME = "button_shade.png";
    const SDL_Color     BUTTON_FONT_COLOR = {0xff, 0xff, 0x0, 0xff};
    const uint16_t      BUTTON_FONT_SIZE = 16,
                        BUTTON_WIDTH = 120,
                        BUTTON_HEIGHT = 50;

    // Window assets
    const std::string   WINDOW_TITLE = "2DCollisionDetection",
                        WINDOW_ICON_IMAGE_NAME = "assets/balls_logo.png";
    const uint16_t      WINDOW_WIDTH = 720,
                        WINDOW_HEIGHT = 480;
    
}

#endif