#ifndef MovementLogic_h__
#define MovementLogic_h__

#include "IGameObject.h"
#include "GameField.h"
#include "Engine/Core/TimeHelpers.hpp"
#include "Engine/Core/DiscretePath.hpp"
#include "Presentation/IBody.h"

class MovementLogic
{
public:
  typedef GameField::TFieldPos TFieldPos;
  typedef GameField::TScreenPos TScreenPos; 

public:
  MovementLogic( float cellMoveTime, IBody *pBody ):
    m_fieldMovementTimer( cellMoveTime ), m_pBody(pBody)
  {}  

  bool Update( IGameObject *pThis, GameField &field );
  bool MoveTo( IGameObject *pThis, const GameField &field, TFieldPos dstPos );
  void SetPos( const GameField &field, TFieldPos pos );
  TFieldPos GetPos() const { return m_discretePath.GetPos(); }
  void Stop();
  bool IsInProgress() const { return m_fieldMovementTimer.IsInProgress(); }
  TFieldPos GetDstPos() const { ASSERT( IsInProgress() ); return m_discretePath.GetDstPos(); }
  float GetTotalMoveTime() const;
  float GetCellMoveTime() const { return m_fieldMovementTimer.GetTotalTime(); }

private:
  bool CheckNextPos( IGameObject *pThis, const GameField &field );

private:
  DiscretePath<TFieldPos::TValueType> m_discretePath;
  SimpleTimer<float> m_fieldMovementTimer;
  IBody *m_pBody;
};


#endif // MovementLogic_h__



