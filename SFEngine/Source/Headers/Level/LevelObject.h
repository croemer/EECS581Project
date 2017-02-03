#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"

#include "../Physics/Mesh.h"
#include "../../../ThirdParty/PhysicsEngine.h"

namespace Engine
{
  class GenericActor;
  class Player;

  enum class OverlapAction
  {
    KILL_ACTOR = 0,
    DISALLOW_ACTOR_OVERLAP = 1,
    CUSTOM_ACTION
  };

  class LevelObject : public BaseEngineInterface
  {
  public:

    LevelObject();
    LevelObject(const LevelObject &obj);
    virtual ~LevelObject();

    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    void SetPosition(const sf::Vector2f &pos);

    virtual PhysicsEngineBaseMeshType* GetMesh() const {
      return ObjectMesh.get();
    }

    virtual PhysicsEngineSegmentType* GetSegments() const {
      return ObjectSegments.get();
    }

    virtual void UpdateMesh();
    virtual void UpdateSegments();

  protected:

    std::shared_ptr<PhysicsEngineBaseMeshType> ObjectMesh;
    std::shared_ptr<PhysicsEngineSegmentType> ObjectSegments;

    bool AllowsActorOverlap; //if false, then actors will never be allowed to cross over this object
    bool RenderOutlined;
    bool TestingCollisions;
  };
}



#endif