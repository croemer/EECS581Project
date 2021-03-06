#include "../../Headers/Actor/Actor.h"

namespace Engine
{


  GenericActor::GenericActor(const std::string &texfile, const std::string &texID)
  {
    
  }

  void GenericActor::BuildAnimations(const std::string & filename, const std::string & texturefile, GenericActor * Actor)
  {
    std::string animname = "";
    std::size_t numframes = 0;

    std::shared_ptr<sf::Texture> AnimTexture = std::make_shared<sf::Texture>();
    if (!AnimTexture->loadFromFile(texturefile)) {
      std::cerr << "Unable to load animation file: " << texturefile << std::endl;
      return;
    }

    int left{ 0 }, top{ 0 }, width{ 0 }, height{ 0 };
    sf::IntRect Frame = { 0,0,0,0 };
    std::ifstream in(filename);
    std::size_t frametime = 0;
    while (in >> animname) {
      in >> numframes >> frametime;
      auto anim = std::make_shared<Animation>();
      
      for (std::size_t i = 0; i < numframes; ++i) {
        in >> left >> top >> width >> height;
        Frame.left = left; Frame.top = top; Frame.width = width; Frame.height = height;
        anim->AddFrame(Frame);
        anim->SetFrameTime(frametime);
        Actor->AddAnimation(animname, anim);
      }

    }
    in.close();
  }

  void GenericActor::BindScriptMethods(chaiscript::ModulePtr mptr)
  {
    //UGHSDJLGHSD LJHFSDLFHS DLFH SDF
    //It's SO UGLY!
    chaiscript::utility::add_class<Engine::GenericActor>(
		*mptr,
		"GenericActor",
		{ chaiscript::constructor<Engine::GenericActor()>() },
		{ {
			chaiscript::fun(static_cast<void(GenericActor::*)(const std::string &)>(&GenericActor::SetID)), "SetID" },
			{ chaiscript::fun(static_cast<std::string(GenericActor::*)(void) const>(&GenericActor::GetID)), "GetID" },
			{ chaiscript::fun(static_cast<const sf::Vector2f &(GenericActor::*)(void) const>(&GenericActor::GetActorPosition)), "GetPosition" },
			{ chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorPosition)), "SetPosition" },
			{ chaiscript::fun(static_cast<void(GenericActor::*)(float, float)>(&GenericActor::SetActorPosition)), "SetPosition" },
			{ chaiscript::fun(static_cast<void(GenericActor::*)(const std::string &)>(&GenericActor::SetAnimation)), "SetAnimation" },
			{ chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorAcceleration)), "SetAcceleration" },
			{ chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorVelocity)), "SetVelocity" },
			{ chaiscript::fun(static_cast<void(GenericActor::*)(const double &)>(&GenericActor::TickUpdate)), "TickUpdate" },
			{ chaiscript::fun(static_cast<void(GenericActor::*)(const std::string &)>(&GenericActor::UseTemporaryAnimation)), "AnimateAction" }
		}
    );
  }
   
  GenericActor::GenericActor()
  {

  }

  GenericActor::GenericActor(const GenericActor &actor)
  {

  }

  void GenericActor::AddAnimation(const std::string &ID, std::shared_ptr<Animation> info)
  {
    Animations[ID] = info;
  }

  void GenericActor::SetAnimation(const std::string & ID)
  {
    if (CurrentAnimation)
      CurrentAnimation->Stop();

    auto anim = Animations.find(ID);
    if (anim != Animations.end()) {
      CurrentAnimation = anim->second.get();
      CurrentAnimation->Play();
    }
  }

  void GenericActor::UseTemporaryAnimation(const std::string & ID)
  {
    if (CurrentAnimation) {
      PreviousAnimation = CurrentAnimation;
    }
    auto it = Animations.find(ID);
    if (it != Animations.end()) {
      it->second->AnimationComplete = [this]() {this->UsePreviousAnimation(); };
      it->second->Play(false, true);
      CurrentAnimation = it->second.get();
      CurrentAnimation->Play();
      CurrentAnimation->SetFrameTime(40);
      CurrentAnimation->SetPosition(Position);
      CurrentAnimation->SetSize(Size);
    }
  }

  void GenericActor::UsePreviousAnimation()
  {
    if (PreviousAnimation && CurrentAnimation) {
      CurrentAnimation->Stop();
      CurrentAnimation->AnimationComplete = []() {};
      CurrentAnimation = PreviousAnimation;
      CurrentAnimation->Play();
    }
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
    if (CurrentAnimation)
      CurrentAnimation->Render(Target);
  }

  void GenericActor::TickUpdate(const double &delta)
  {
    if (CurrentAnimation) {
      CurrentAnimation->TickUpdate(delta);
      CurrentAnimation->SetPosition(Position);
      CurrentAnimation->SetSize(Size);
    }
  }

  bool GenericActor::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }

  void GenericActor::SetActorPosition(const sf::Vector2f &pos)
  {
    Position = pos;
    
  }

  void GenericActor::SetActorPosition(float x, float y)
  {
    SetActorPosition({ x, y });
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

  void GenericActor::GenerateActorMesh()
  {
    CollisionMesh = BuildBallMesh('B', Position, Velocity, static_cast<int>(std::ceil(Size.y / 2.f )), 1, 1, sf::Color::Transparent);
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