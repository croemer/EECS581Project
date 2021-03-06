#ifndef SFENGINE_UI_MENU_WIDGET_H
#define SFENGINE_UI_MENU_WIDGET_H

#include "../Widget.h"

#include <stack>

namespace Engine
{

  namespace UI
  {

    class MenuScreen;

    class MenuWidget : public WidgetBase
    {
    public:
      static std::shared_ptr<MenuWidget> Create(std::shared_ptr<UILayer> TopLayer, std::shared_ptr<WidgetHelper> TopHelper, const sf::Vector2f &Position, const sf::Vector2f &Size);
      void Open();
      static void SetDefaultScreen(std::weak_ptr<MenuScreen> Screen, std::shared_ptr<MenuWidget> Menu);
      void AddScreen(std::weak_ptr<MenuScreen> Screen);
      static void AddScreen(std::weak_ptr<MenuScreen> Screen, std::shared_ptr<MenuWidget> Menu);
      static void SetFont(std::shared_ptr<MenuWidget> Menu, std::shared_ptr<sf::Font> Font);
      static void SetTitle(std::shared_ptr<MenuWidget> Menu, const std::string &string, unsigned int size, const sf::Color &Color);

      void ShowScreen(std::weak_ptr<MenuScreen> Screen);
      void RemoveScreen(std::weak_ptr<MenuScreen> Screen);
      void Back();
      void Close();
      void Hide();
      void Disable();
      void Clear();
      static void ShowDefaultScreen(std::weak_ptr<MenuWidget> Menu);

      static void OpenMenu(std::weak_ptr<MenuWidget> Menu);

      virtual std::string ClassName() override {
        return "MenuWidget";
      }

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

      std::function<void(void)> MenuClosedCB = []() {};
      std::function<void(void)> MenuOpenedCB = []() {};

      void IntakeEvent(const InputEvent &IEvent);

      virtual ~MenuWidget() {
        DEBUG_ONLY std::cerr << "\n\nMenu Widget Being Destroyed\n\n" << std::endl;

      }
      void CloseMenu();

    protected:
      MenuWidget() = default;
      bool _IsInFocus = false;

      std::shared_ptr<sf::RenderTexture> MenuTexture;
      sf::Sprite MenuSprite;

      float TransitionTime = 100.f;
      float CurrentTime = 0.f;
      bool IsTransitioning = false;
      sf::View TransitioningView;
      sf::FloatRect TransitioningViewRect;

      sf::Vector2f Position;
      sf::Vector2f Size;

      std::shared_ptr<sf::Font> MenuFont;
      sf::Text MenuText;
      std::shared_ptr<WidgetHelper> MenuHelper;
      std::weak_ptr<MenuScreen> DefaultScreen;

      sf::Text TestString;
      std::map<std::uint32_t, std::weak_ptr<MenuScreen>> Screens;

      std::stack<std::weak_ptr<MenuScreen>> ScreenStack;
    };

  }

}


#endif
