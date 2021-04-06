#include "Checkbox.hpp"

Checkbox * Checkbox::newCheckbox(const std::string & button_texture,
                           const std::string & button_highlight,
                           const std::string & button_shadow,
                           uint16_t button_width,
                           uint16_t button_height,
                           const std::string & label,
                           const std::string & font_name,
                           uint16_t font_size,
                           const SDL_Color & font_color)
{
    Checkbox * checkbox = new Checkbox();
    checkbox->_button = Button::newButton("", button_texture, Assets::BUTTON_FONT_NAME, Assets::BUTTON_FONT_COLOR, Assets::BUTTON_FONT_SIZE, Assets::CHECKBOX_LENGTH, Assets::CHECKBOX_LENGTH);
    checkbox->_label = SolidText::newSolidText(label, font_name, font_size, font_color);

    checkbox->_button->setParent(checkbox);
    checkbox->_label->setParent(checkbox);

    checkbox->_label->setRelativeX(checkbox->_button->getWidth() + 10);

    checkbox->hide();

    return checkbox;
}

bool Checkbox::isChecked() const noexcept
{
    return _is_checked;
}

void Checkbox::setReaction(std::function<void ()> reaction)
{
    _button->setClickReaction(reaction);
}

Checkbox::Checkbox():
VisualComponent(0, 0)
{

}

Checkbox::~Checkbox()
{
    
}