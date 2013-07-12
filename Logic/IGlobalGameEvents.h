#ifndef IGlobalGameEvents_h__
#define IGlobalGameEvents_h__

struct IGlobalGameEvents
{
  virtual ~IGlobalGameEvents() {}

  virtual void OnAddScore( int val ) {};
  virtual void OnLifeLost() {};
  virtual void OnWin() {};
  virtual void OnLose() {};
};


#endif // IGlobalGameEvents_h__
