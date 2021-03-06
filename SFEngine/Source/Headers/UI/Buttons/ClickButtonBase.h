#ifndef SFENGINE_UI_CLICKBUTTON_H
#define SFENGINE_UI_CLICKBUTTON_H

#include "ButtonBase.h"

namespace Engine
{

  namespace UI
  {

    class ClickButtonBase : public ButtonBase
    {
    public:
      static std::shared_ptr<ClickButtonBase> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<sf::Texture> OverlayTexture);

      static void SetFont(std::shared_ptr<ClickButtonBase> Button, std::shared_ptr<sf::Font> Font);
      static void SetText(std::shared_ptr<ClickButtonBase> Button, const std::string &string, unsigned int size, const sf::Color &Color);

      virtual void ConsumeEvent(const InputEvent &IEvent) override;
      virtual void OnFocusGained(const FocusChangeEvent &FEvent) override;
      virtual void OnFocusLost(const FocusChangeEvent &FEvent) override;
      virtual void OnKeyPress(const InputEvent &IEvent) override;
      virtual void OnKeyRelease(const InputEvent &IEvent) override;
      virtual void OnMousePress(const InputEvent &IEvent) override;
      virtual void OnMouseRelease(const InputEvent &IEvent) override;
      virtual void OnMouseScroll(const InputEvent &IEvent) override;
      virtual void OnMouseOver(const InputEvent &IEvent) override;
      virtual void OnMouseLeave(const InputEvent &IEvent) override;
      virtual void OnMouseMove(const InputEvent &IEvent) override;
      virtual void OnDragBegin(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &IEvent) override;
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> Texture) override;
      virtual void Move(const sf::Vector2f &Delta) override;
      virtual void Resize(const sf::Vector2f &Size) override;
      virtual void ResetAppearance() override;

      virtual void SetTexture(std::shared_ptr<sf::Texture> Texture);
      virtual void SetTextureRect(sf::IntRect &Rect);

      virtual void SetOverlayTexture(std::shared_ptr<sf::Texture> Texture);
      virtual void SetOverlayHighlightedTextureRect(const sf::IntRect &Rect);
      virtual void SetOverlayPressedTextureRect(const sf::IntRect &Rect);
      virtual void SetOverlayNormalTextureRect(const sf::IntRect &Rect);

      virtual void SetBGColorNormal(const sf::Color &Color);
      virtual void SetBGColorHighlighted(const sf::Color &Color);
      virtual void SetBGColorPressed(const sf::Color &Color);

      virtual void SetBGColor(const sf::Color &Color);

      virtual void SetDrawTextureAndBG(bool b) {
        DrawTextureAndBG = b;
        if (b) {
          IconShape.setPosition(Position);
          IconShape.setSize(Size);
        }
      }
      virtual void SetIconTexture(std::shared_ptr<sf::Texture> Texture) {
        IconTexture = Texture;
        IconShape.setTexture(Texture.get());
      }
      virtual void SetIconTextureRect(sf::IntRect Rect) {
        IconShape.setTextureRect(Rect);
      }

      virtual ~ClickButtonBase() = default;
    protected:
      ClickButtonBase();

      std::shared_ptr<sf::Texture> BGTexture;
      std::shared_ptr<sf::Texture> Overlay;
      std::shared_ptr<sf::Texture> IconTexture;
      sf::IntRect BGTextureRect;
      sf::RectangleShape IconShape;

      bool DrawTextureAndBG;
      
      sf::IntRect OverlayNormalRect;
      sf::IntRect OverlayHighlightedRect;
      sf::IntRect OverlayPressedRect;
    };

  }

}

#endif
