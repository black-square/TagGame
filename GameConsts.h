#ifndef LogicConsts_h__
#define LogicConsts_h__

namespace Editor //Should be read from an editor
{
  inline float LogicUpdateTime() { return 0.1f; }  
  inline int   EnemyVisibleDistance() { return 5; }
  inline int   EnemyShoutDistance() { return 10; }
  inline float PlayerCellMoveTime() { return 0.15f; }
  inline float EnemyCellMoveTime() { return 0.20f; } 

  inline int  GetCellSizePx(){ return 16; }
  inline Size GetScreenSizePx(){ return Size(1024, 512); }

  const int FieldSize = 64;

  inline Size FieldSizePx(){ return Size(FieldSize, FieldSize) * GetCellSizePx(); }
  inline Size VisibleFieldSize(){ return Size(32, 18); }
  inline Size VisibleFieldSizePx(){ return VisibleFieldSize() * GetCellSizePx(); }
}



#endif // LogicConsts_h__
