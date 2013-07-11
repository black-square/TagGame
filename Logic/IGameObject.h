#ifndef IGameObject_h__
#define IGameObject_h__

struct IGameObject
{
  enum Type
  {
    Player,
    Enemy,
    Trap
  };

  typedef Point TFieldPos;
  typedef boost::shared_ptr<IGameObject> TPtr;
  typedef const TPtr &TPtrParam;

  virtual Type GetType() const = 0; 

  virtual void Update( float deltaTime ) {}
  virtual void Render() const {}
  virtual void SetPos( TFieldPos pos ) {}

  virtual void Touch( IGameObject *pWho ) {}
  virtual void Stop() {}
  virtual void Kill() {}

  virtual ~IGameObject() {}
};

#endif // IGameObject_h__
