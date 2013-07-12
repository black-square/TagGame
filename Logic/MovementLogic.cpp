#include "stdafx.h"
#include "MovementLogic.h"
#include "GameConsts.h"

void MovementLogic::Update( IGameObject *pThis, GameField &field )
{
  if( m_fieldMovementTimer.TickWithRestart(Editor::LogicUpdateTime()) )
  {
    ASSERT( m_pos != m_dstPos );

    TFieldPos nextPos( m_pos );

    m_discretePath.Next( nextPos );

    if( nextPos == m_dstPos )
      m_fieldMovementTimer.Stop();

    auto &pObj = field.Get( nextPos );

    if( pObj )
    {
      m_fieldMovementTimer.Stop();
      pObj->Touch(pThis);
    }
    else
    {
      field.Move( m_pos, nextPos );
      m_pos = nextPos;
    }     
  }
}
//////////////////////////////////////////////////////////////////////////

void MovementLogic::MoveTo( const GameField &field, TFieldPos dstPos )
{
  ASSERT( field.IsValid(m_pos) );

  if( m_pos == dstPos )
    return;

  m_dstPos = dstPos;
  m_discretePath.Start( m_pos, dstPos );
  
  if( !m_fieldMovementTimer.IsInProgress() ) 
    m_fieldMovementTimer.Start(); 
}
//////////////////////////////////////////////////////////////////////////

void MovementLogic::SetPos( const GameField &field, TFieldPos pos )
{
  ASSERT( field.IsValid(pos) );
  m_pos = pos; 
  m_dstPos = pos;
  m_fieldMovementTimer.Stop();
}
//////////////////////////////////////////////////////////////////////////

void MovementLogic::Stop()
{
  m_fieldMovementTimer.Stop();  
}
//////////////////////////////////////////////////////////////////////////

float MovementLogic::GetTotalMoveTime() const
{
  ASSERT( IsInProgress() );

  const TFieldPos delta( abs(GetDstPos() - m_pos) );

  return std::max( delta.x, delta.y ) * GetCellMoveTime();
}
