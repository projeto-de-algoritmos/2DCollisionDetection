#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <functional>

// Every project asset/property should be referenced here

namespace Assets
{
    static void checkboxEmptyReaction(bool a)
    {
        a = !a;
    }

    // Button assets
    const std::string   BUTTON_FONT_NAME = "arial.ttf",
                        BUTTON_BACKGROUND_IMAGE_NAME = "button_background.png",
                        BUTTON_HIGHLIGHT_NAME = "button_highlight.png",
                        BUTTON_SHADE_NAME = "button_shade.png";
    const SDL_Color     BUTTON_FONT_COLOR = {0xff, 0xff, 0xff, 0xff};
    const uint16_t      BUTTON_FONT_SIZE = 16,
                        BUTTON_WIDTH = 150,
                        BUTTON_HEIGHT = 50;

    // Window assets
    const std::string   WINDOW_TITLE = "2DCollisionDetection",
                        WINDOW_ICON_IMAGE_NAME = "assets/balls_logo.png";
    const uint16_t      WINDOW_WIDTH = 720,
                        WINDOW_HEIGHT = 480;
    
    // Ball assets
    const std::string   BALL_TEXTURE_NAME = "ball_texture.png",
                        BALL_HIGHLIGHT_NAME = "ball_highlight.png";
    const uint16_t      BALL_RADIUS = 15;

    // Table / Ball Assets
    const uint16_t      TABLE_WIDTH = WINDOW_WIDTH,
                        TABLE_HEIGHT = WINDOW_HEIGHT;

    // Timer assets
    const double_t      _60_FPS_FRAMETIME = 1.0 / 60.0,
                        _30_FPS_FRAMETIME = 1.0 / 30.0;

    // Table assets
    const std::string   TABLE_TEXTURE_NAME = "table_texture.jpg";

    // Checkbox assets
    const uint16_t                  CHECKBOX_WIDTH_HEIGHT = 25,
                                    CHECKBOX_FONT_SIZE = 16;
    const std::string               CHECKBOX_CHECKED_TEXTURE = "checkbox_checked_texture.png",
                                    CHECKBOX_CHECKED_HIGHLIGHT = "checkbox_checked_hightlight.png",
                                    CHECKBOX_UNCHECKED_TEXTURE = "checkbox_unchecked_texture.png",
                                    CHECKBOX_UNCHECKED_HIGHLIGHT = "checkbox_unchecked_highlight.png",
                                    CHECKBOX_FONT_NAME = "arial.ttf";
    const SDL_Color                 CHECKBOX_FONT_COLOR = {0xff, 0xff, 0xff, 0xff};
    const std::function<void(bool)> CHECKBOX_EMPTY_REACTION = checkboxEmptyReaction;

    // Dynamic Text Assets
    const std::string   DYNAMICTEXT_FONT_NAME = "arial.ttf";
    const SDL_Color     DYNAMICTEXT_FONT_COLOR = {0xff, 0xff, 0xff, 0xff};
    const uint16_t      DYNAMICTEXT_FONT_SIZE = 13;
}

#endif