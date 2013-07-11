#ifndef IGameObject_h__
#define IGameObject_h__

struct IGameObject
{
  typedef boost::shared_ptr<IGameObject> TPtr;

  virtual void Update( float deltaTime ) {}
  virtual void Render() const {}

  virtual ~IGameObject() {}
};

#endif // IGameObject_h__
