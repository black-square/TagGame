#ifndef IEffects_h__
#define IEffects_h__

struct IEffects
{
  enum Effect
  {
    EnemyDied,
    PlayerStoped
  };

  typedef boost::shared_ptr<IEffects> TPtr;
  typedef const TPtr &TPtrParam;
  typedef PointBase<float> TPoint;

  virtual ~IEffects() {}

  virtual void Play( TPoint pos, Effect effect ) {}
};


#endif // IEffects_h__
