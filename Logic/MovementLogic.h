#ifndef MovementLogic_h__
#define MovementLogic_h__

#include "IGameObject.h"
#include "GameField.h"
#include "Core/TimeHelpers.hpp"
#include "Core/DiscretePath.hpp"

class MovementLogic
{
public:
  typedef GameField::TFieldPos TFieldPos;
  typedef GameField::TScreenPos TScreenPos; 

public:
  explicit MovementLogic( float cellMoveTime ):
    m_fieldMovementTimer( cellMoveTime )
  {}  

  void Update( IGameObject *pThis, GameField &field );
  void MoveTo( const GameField &field, TFieldPos dstPos );
  void SetPos( const GameField &field, TFieldPos pos );
  TFieldPos GetPos() const { return m_pos; }
  void Stop();
  bool IsInProgress() const { return m_fieldMovementTimer.IsInProgress(); }
  TFieldPos GetDstPos() const { return m_dstPos; }
  float GetTotalMoveTime() const;
  float GetCellMoveTime() const { return m_fieldMovementTimer.GetTotalTime(); }

private:
  TFieldPos m_pos;
  TFieldPos m_dstPos;
  DiscretePath<TFieldPos::TValueType> m_discretePath;
  SimpleTimer<float> m_fieldMovementTimer;
};


#endif // MovementLogic_h__



