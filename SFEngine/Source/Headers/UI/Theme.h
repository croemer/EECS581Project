#ifndef SFENGINE_UI_THEME_H
#define SFENGINE_UI_THEME_H

#include <SFML/Graphics.hpp>

#include "Text\TextLabel.h"

namespace Engine
{

  namespace UI
  {

    struct Theme
    {
      sf::Vector2f ButtonSizeSmall; 
      sf::Vector2f ButtonSizeNormal; 
      sf::Vector2f ButtonSizeMedium; 
      sf::Vector2f ButtonSizeLarge;

      sf::Color ButtonColorNormal; 
      sf::Color ButtonColorHighlighted; 
      sf::Color ButtonColorPressed; 
      sf::Color ButtonColorDisabled;

      sf::Color ButtonOutlineColorNormal; 
      sf::Color ButtonOutlineColorHighlighted; 
      sf::Color ButtonOutlineColorPressed; 
      sf::Color ButtonOutlineColorDisabled;

      sf::Color MenuBackgroundColorNormal; 
      sf::Color MenuBackgroundColorDisabled;

      sf::Color MenuOutlineColorNormal; 
      sf::Color MenuOutlineColorDisabled;

      sf::Color WidgetBackgroundColorNormal;
      sf::Color WidgetBackgroundColorDisabled;

      sf::Color TextColorNormal; 
      sf::Color TextColorDisabled; 
      sf::Color TextColorError;

      unsigned int TextSizeSmall;
      unsigned int TextSizeNormal; 
      unsigned int TextSizeMedium; 
      unsigned int TextSizeLarge;

      TextAlignment ButtonTextAlignment; 
      TextAlignment WidgetTextAlignment; 
      TextAlignment MenuTextAlignment;
    };

    extern Theme DefaultDarkTheme;

  }

}

#endif