#ifndef LogicConsts_h__
#define LogicConsts_h__

namespace Editor //Should be read from an editor
{
  inline float LogicUpdateTime() { return 0.1f; }  
  inline int   EnemyVisibleDistance() { return 5; }
  inline int   EnemyShoutDistance() { return 10; }
  inline float PlayerCellMoveTime() { return 0.1f; }
  inline float EnemyCellMoveTime() { return 0.15f; } 

  inline Size  GetScreenSizePx(){ return Size(1024, 512); }
}



#endif // LogicConsts_h__
