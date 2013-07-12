#ifndef IBody_h__
#define IBody_h__

struct IBody
{
  typedef boost::shared_ptr<IBody> TPtr;
  typedef const TPtr &TPtrParam;
  typedef PointBase<float> TPoint;
  
  virtual ~IBody() {}
  virtual void Render( float deltaTime ) {}
  virtual void MoveTo( TPoint dst, float time ) {}
  virtual void SetPos( TPoint dst ) {}
  virtual void Stop() {}
};


#endif // IBody_h__
