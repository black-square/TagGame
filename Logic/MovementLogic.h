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

  void Update( IGameObject *pThis, GameField &field, TFieldPos &pos );
  void MoveTo( const GameField &field, TFieldPos pos, TFieldPos dstPos );
  void SetPos( const GameField &field, TFieldPos pos );
  void Stop();
  bool IsInProgress() const { return m_fieldMovementTimer.IsInProgress(); }
  TFieldPos GetDstPos() const { ASSERT( IsInProgress() ); return m_dstPos; }


private:
  TFieldPos m_dstPos;
  DiscretePath<TFieldPos::TValueType> m_discretePath;
  SimpleTimer<float> m_fieldMovementTimer;
};


#endif // MovementLogic_h__



