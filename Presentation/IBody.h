
#ifndef IBody_h__
#define IBody_h__

#include "IEffects.h"

struct IBody
{
  typedef boost::shared_ptr<IBody> TPtr;
  typedef const TPtr &TPtrParam;
  typedef PointBase<float> TPoint;

  enum Direction
  {
    Up,
    Left,
    Right,
    Down,
    TotalDir
  };
  
  virtual ~IBody() {}
  virtual void Render( float deltaTime ) {}
  virtual void MoveTo( TPoint dst, float time ) {}
  virtual void SetPos( TPoint dst ) {}
  virtual TPoint GetPos() const = 0;
  virtual void Stop() {}
  virtual IEffects *Effects() const { static IEffects dummy; return &dummy; }
  virtual void StartBlinking() {}
  virtual void StopBlinking() {}
};


#endif // IBody_h__
