#include "../../Headers/Engine/BaseEngineInterface.h"

namespace Engine
{
  BaseEngineInterface::BaseEngineInterface()
  {
    
  }

  void BaseEngineInterface::SerializeOut(std::ostream &out)
  {

  }

  BaseEngineInterface::BaseEngineInterface(const BaseEngineInterface &b)
  {

  }
  BaseEngineInterface::~BaseEngineInterface()
  {

  }
  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item, const sf::Vector2i &i)
  {

  }

  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &)
  {

  }

  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &)
  {

  }

  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item)
  {

  }

  std::string BaseEngineInterface::GetID() const
  {
    return ItemID;
  }

  void BaseEngineInterface::SetID(const std::string &ID)
  {
    ItemID = ID;
  }
}
