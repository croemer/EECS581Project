#ifndef SFENGINE_DRAGGABLE_RECT_H
#define SFENGINE_DRAGGABLE_RECT_H

#include "DraggableBase.h"

namespace Engine
{

  namespace UI
  {

    class DraggableRect : public DraggableBase
    {
    public:
      static std::shared_ptr<DraggableRect> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size);

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

      sf::RectangleShape Shape;

      std::function<void(const sf::Vector2f &Delta)> OnDragged = [](auto delta) {};

      virtual ~DraggableRect() = default;
    protected:
      DraggableRect();

    };

  }

}


#endif
