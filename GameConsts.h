#ifndef LogicConsts_h__
#define LogicConsts_h__

namespace Editor //Should be read from an editor
{
  inline float LogicUpdateTime() { return 0.1f; }  
  inline int   EnemyVisibleDistance() { return 5; }
  inline int   EnemyShoutDistance() { return 7; }
  inline float PlayerCellMoveTime() { return 0.15f; }
  inline float EnemyCellMoveTime() { return 0.22f; } 

  inline Size GetFieldSize(){ return Size(61, 61); }

  inline int  GetCellSizePx(){ return 16; }
  inline Size GetScreenSizePx(){ return Size(1024, 512); }

  inline Size FieldSizePx(){ return GetFieldSize() * GetCellSizePx(); }
  inline Size VisibleFieldSize(){ return Size(32, 18); }
  inline Size VisibleFieldSizePx(){ return VisibleFieldSize() * GetCellSizePx(); }

  inline int AnimFramesCount() { return 3; }
  inline int AnimFramesCountStatic() { return 6; }
  inline int StaticFramesCount() { return 3; }
  inline float AnimSpeed() { return 0.2f; }
  inline float AnimSpeedStatic() { return 0.14f; }
  inline float BlinkSpeed() { return 0.1f; } 

  inline int LivesCount() { return 3; }
  inline int EnemyKillScore() { return 100; } 
  inline float InvulnerabilityTime() { return 3.0f; }
}



#endif // LogicConsts_h__
