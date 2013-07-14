#ifndef IGlobalGameEvents_h__
#define IGlobalGameEvents_h__

struct IGlobalGameEvents
{
  virtual ~IGlobalGameEvents() {}

  virtual void OnAddScore( int val ) {};
  virtual void OnSetLives( int val ) {};
  virtual void OnEnemyDestroyed() {};
};


#endif // IGlobalGameEvents_h__
