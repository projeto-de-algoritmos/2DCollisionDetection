#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

#include <string>
#include <cstdint>

// Every project asset/property should be referenced here

namespace Assets
{
    // Button assets
    const std::string   BUTTON_FONT_NAME = "arial.ttf",
                        BUTTON_BACKGROUND_IMAGE_NAME = "button_background.png",
                        BUTTON_SHADE_NAME = "button_shade.png";

    // Window assets
    const std::string   WINDOW_TITLE = "2DCollisionDetection",
                        ICON_IMAGE_NAME = "PALogo.png";
    const uint16_t      WINDOW_WIDTH = 720,
                        WINDOW_HEIGHT = 480;
    
}

#endif