#ifndef IGameObject_h__
#define IGameObject_h__

#include "Core/TinyList.hpp"

struct GameObjectListTag{};

struct IGameObject:  TinyLink<GameObjectListTag>
{
  typedef boost::shared_ptr<IGameObject> TPtr;
  typedef const TPtr &TPtrParam;
  typedef boost::weak_ptr<IGameObject> TWeakPtr;
  typedef const TWeakPtr &TWeakPtrParam;
  
  enum Type
  {
    Player,
    Enemy,
    Trap
  };

  typedef Point TFieldPos;

  virtual Type GetType() const = 0; 
  virtual TFieldPos GetPos() const = 0;

  virtual void Update() {}
  virtual void Render( float deltaTime ) const {}
  virtual void SetPos( TFieldPos pos ) {}

  virtual void Touch( IGameObject::TPtrParam pWho ) {}
  virtual void Stop() {}
  virtual void Kill( IGameObject::TPtrParam pKiller ) {}
  virtual void PlayerVisible( IGameObject::TPtrParam pPlayer ) {}
  virtual void PlayerCouldBeAtPos( TFieldPos pos ) {}

  virtual ~IGameObject() {}
};

#endif // IGameObject_h__
