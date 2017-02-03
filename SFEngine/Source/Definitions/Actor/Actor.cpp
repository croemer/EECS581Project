#include "../../Headers/Actor/Actor.h"

namespace Engine
{


  GenericActor::GenericActor(const std::string &texfile, const std::string &texID)
  {
    ResourceManager->RequestTexture(texfile, texID,
                                    [this](const std::shared_ptr<sf::Texture> t, const std::string &s)->void
    {this->ReceiveSprite(s, t); }
    );

    Handler.BindCallback(Events::KeyPressed,
                         [this](const sf::Keyboard::Key &k) {this->__HandleKeyPress(k); }
    );
  }

  void GenericActor::BindScriptMethods(chaiscript::ModulePtr mptr)
  {
    //UGHSDJLGHSD LJHFSDLFHS DLFH SDF
    //It's SO UGLY!
    chaiscript::utility::add_class<Engine::GenericActor>(*mptr, "GenericActor",
    { chaiscript::constructor<Engine::GenericActor()>() },
    { {
        chaiscript::fun(static_cast<void(GenericActor::*)(const std::string &)>(&GenericActor::SetID)), "SetID" },
        { chaiscript::fun(static_cast<std::string(GenericActor::*)(void) const>(&GenericActor::GetID)), "GetID" },
        { chaiscript::fun(static_cast<const sf::Vector2f &(GenericActor::*)(void) const>(&GenericActor::GetActorPosition)), "GetPosition" },
        { chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorPosition)), "SetPosition" }
    }
    );
  }

  GenericActor::GenericActor()
  {

  }

  GenericActor::GenericActor(const GenericActor &actor)
  {

  }

  void GenericActor::AddAnimation(const std::string &ID, AnimationInfo info)
  {
    Animations[ID] = {};

  }

  void GenericActor::__HandleKeyPress(const sf::Keyboard::Key &key)
  {
    
  }

  void GenericActor::SetTexture(const std::string &texfile, const std::string &texID)
  {

  }

  void GenericActor::ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex)
  {
    
  }

  GenericActor::~GenericActor()
  {

  }

  void GenericActor::SerializeOut(std::ofstream &out)
  {

  }

  void GenericActor::SerializeIn(std::ifstream &in)
  {

  }

  void GenericActor::OnShutDown()
  {

  }

  void GenericActor::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    
  }

  void GenericActor::TickUpdate(const double &delta)
  {
    
  }

  bool GenericActor::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }

  void GenericActor::SetActorPosition(const sf::Vector2f &pos)
  {
    Position = pos;
  }

  void GenericActor::SetActorSize(const sf::Vector2f &size)
  {
    Size = size;
  }

  void GenericActor::SetActorVelocity(const sf::Vector2f &vel)
  {
    Velocity = vel;
  }

  void GenericActor::SetActorAcceleration(const sf::Vector2f &acc)
  {
    Acceleration = acc;
  }

  const sf::Vector2f& GenericActor::GetActorPosition() const
  {
    return Position;
  }

  const sf::Vector2f& GenericActor::GetActorSize() const
  {
    return Size;
  }

  const sf::Vector2f& GenericActor::GetActorVelocity() const
  {
    return Velocity;
  }

  const sf::Vector2f& GenericActor::GetActorAcceleration() const
  {
    return Acceleration;
  }

}