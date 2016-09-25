#ifndef SFENGINE_EVENT_HANDLER_H
#define SFENGINE_EVENT_HANDLER_H

#include "../BasicIncludes.h"

namespace Engine
{
  
  /**
   * A class to which event handling can be delegated
   * All event handlers are bound to no_action methods at compile time
   * So it will always be safe to call event handlers
   */

  enum class Events
  {
      MouseDown
    , MouseReleased
    , MouseOver
    , MouseExit
    , MouseMoved
    , KeyPressed
    , KeyReleased
    , TextEntered
    , WindowResized
    , LostFocus
    , GainedFocus
    , WindowClosed
    , MouseScrolled
  };

  class EventHandler
  {
  public:
    EventHandler();
    EventHandler(const EventHandler &);
    ~EventHandler();

    void InvokeCallback(const Events &type);
    void SetMousePositionArg(const sf::Vector2f &v);
    void SetMouseButtonArg(const sf::Mouse::Button &b);
    void SetKeyArg(const sf::Keyboard::Key &k);

    void BindCallback(const Events &type, std::function<void(const sf::Vector2i &)> &ftn);
    void BindCallback(const Events &type, std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> &ftn);
    void BindCallback(const Events &type, std::function<void(const sf::Keyboard::Key &)> &ftn);
    void BindCallback(const Events &type, std::function<void(void)> &ftn);

    bool PollEvents(sf::RenderWindow *win, sf::Event &evnt, const bool &makeCallbacks); 

  protected:
    sf::Vector2i v2iMousePosArg;
    sf::Mouse::Button enMouseButtonArg;
    sf::Keyboard::Key enKeyboardArg;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseMovement;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseOver;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseExit;
    std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftnCallback_MousePress;
    std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftnCallback_MouseRelease;
    std::function<void(const sf::Vector2i &)> ftnCallback_MouseScroll;
    std::function<void(const sf::Keyboard::Key &)> ftnCallback_KeyPress;
    std::function<void(const sf::Keyboard::Key &)> ftnCallback_KeyRelease;
    std::function<void(const sf::Keyboard::Key &)> ftnCallback_TextEntered;

    std::function<void(void)> ftnCallback_WindowClosed;
    std::function<void(void)> ftnCallback_WindowResized;
  };
}

#endif
