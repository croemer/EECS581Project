#include "../../../Headers/UI/Alerts/Alert.h"

#include "../../../Headers/UI/Buttons/ClickButtonBase.h"
#include "../../../Headers/UI/Text/TextLabel.h"
#include "../../../Headers/UI/WIdgetHelper.h"


namespace Engine
{

  namespace UI
  {

    std::shared_ptr<Alert> Alert::Create(std::shared_ptr<UILayer> Layer, std::shared_ptr<WidgetHelper> Helper, const std::string &Message, std::shared_ptr<sf::Font> Font, const sf::Vector2f &Position)
    {
      if (!Helper || !Helper->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      if (!Layer || !Layer->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));


      try
      {
        std::shared_ptr<Alert> AL(new Alert);

        AL->Helper = Helper;
        AL->ChildHelper = WidgetHelper::Create();
        AL->ChildLayer = UILayer::Create(AL->Helper);
        AL->MyLayer = Layer;

        try
        {
          AL->SetUpWidget();
        }
        catch (EngineRuntimeError &err)
        {
          err.AddCause(ExceptionCause::InitializationError);
          err.AddMessage(EXCEPTION_MESSAGE("Alert failed SetUp()"));

          throw;
        }


        AL->BGRect.setPosition(Position);

        AL->CanBeDragged = false;
        AL->Position = Position;

        AL->Font = Font;
        AL->AlertMessage = std::make_shared<sf::Text>();
        AL->AlertMessage->setFont(*(AL->Font));
        AL->AlertMessage->setString("SampleAlert!");
        AL->AlertMessage->setCharacterSize(14);

        auto Rect = AL->AlertMessage->getGlobalBounds();

        sf::Vector2f AlertSize = { 500, 500 };
        sf::Vector2f ButtonSize = { 100, 40 };
        sf::FloatRect TotalBounds = { Position, AlertSize };

        AL->GlobalWidgetBounds.ForceRegion(TotalBounds);

        auto FRECT = AL->AlertMessage->getGlobalBounds();
        AL->AlertMessage->setPosition({ (TotalBounds.width - FRECT.width) / 2.f, (TotalBounds.height - FRECT.height) / 2.f });

        //Create OKButton
        AL->AcknowledgeButton = UI::ClickButtonBase::Create(AL->ChildLayer, AL->ChildHelper, { 200, 450 }, ButtonSize);

        AL->OKText = TextLabel::Create(AL->AcknowledgeButton, AL->ChildHelper, TextAlignment::CenterJustified, "OK", sf::Color::White, Font, 10, { 0,0,1000,1000 }, { 0,0 });
        AL->AlertText = TextLabel::Create(AL->AcknowledgeButton, AL->ChildHelper, TextAlignment::CenterJustified, "OK", sf::Color::White, Font, 10, { 0, 0, 1000, 1000 }, { 0, 0 });

        AL->BGRect.setSize({ AlertSize });
        AL->BGRect.setFillColor(sf::Color(96, 96, 96, 100));
        AL->BGRect.setOutlineColor(sf::Color::Red);
        AL->BGRect.setOutlineThickness(-2);

        //Close the popup when the user releases the mouse on it
        AL->AcknowledgeButton->MouseReleaseCB =
          [ AL ]()
        {
          AL->OnAcknowledged();
          AL->CloseWasPressed();
          UI::Alert::ClosePopup(AL);
        };

        return AL;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Failed to create Alert"));

        throw;
      }

    }

    void Alert::ConsumeEvent(const InputEvent & IEvent)
    {
      ChildLayer->HandleEvent(IEvent);
    }

    void Alert::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void Alert::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void Alert::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void Alert::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void Alert::OnMousePress(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseRelease(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseOver(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseLeave(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void Alert::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void Alert::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void Alert::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void Alert::TickUpdate(const double & delta)
    {
    }

    void Alert::Render(std::shared_ptr<sf::RenderTexture>& Texture)
    {
      Texture->draw(BGRect);

      Texture->draw(*AlertMessage);
      AlertText->Render(Texture);

      AcknowledgeButton->Render(Texture);
    }

    void Alert::Move(const sf::Vector2f & Delta)
    {
    }

    void Alert::ShowAlert(std::shared_ptr<Alert> Message)
    {
      DEBUG_ONLY std::cerr << "Popup ID : " << Message->WidgetID << " Showing" << std::endl;
      Message->IsOnAlert = true;
      Message->Helper->TakeFocus(Message);
    }

    void Alert::HideAlert(std::shared_ptr<Alert> Message)
    {
      DEBUG_ONLY std::cerr << "Popup ID : " << Message->WidgetID << " Hiding" << std::endl;
      Message->IsOnAlert = false;
      Message->Helper->ReleaseFocus(Message);
    }

    Alert::~Alert()
    {
    }

    Alert::Alert()
    {
    }

    void Alert::OnAcknowledged()
    {
      DEBUG_ONLY std::cerr << "ACKNOWLEDGED ALERT" << std::endl;
    }

  }

}