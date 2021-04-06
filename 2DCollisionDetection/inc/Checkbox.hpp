#ifndef _CHECKBOX_HPP_
#define _CHECKBOX_HPP_

#include "VisualComponent.hpp"
#include "Button.hpp"
#include "SolidText.hpp"

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <functional>

class Checkbox : VisualComponent
{
public:
    Checkbox * newCheckbox(const std::string & button_texture,
                           const std::string & button_highlight,
                           const std::string & button_shadow,
                           uint16_t button_width,
                           uint16_t button_height,
                           const std::string & label,
                           const std::string & font_name,
                           uint16_t font_size,
                           const SDL_Color & font_color
                           );
    
    bool isChecked() const noexcept;
    
    void setReaction(std::function<void ()> reaction);

private:
    Checkbox();
    virtual ~Checkbox();

    bool _is_checked;
    Button * _button;
    SolidText * _label;

protected:

};

#endif