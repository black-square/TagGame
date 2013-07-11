#include "stdafx.h"
#include "MovementLogic.h"
#include "GameConsts.h"

void MovementLogic::Update( IGameObject *pThis, GameField &field, TFieldPos &pos )
{
  if( m_fieldMovementTimer.TickWithRestart(Editor::LogicUpdateTime()) )
  {
    ASSERT( pos != m_dstPos );

    TFieldPos nextPos( pos );

    m_discretePath.Next( nextPos );

    if( nextPos == m_dstPos )
      m_fieldMovementTimer.Stop();

    auto &pObj = field.Get( nextPos );

    if( pObj )
    {
      pObj->Touch(pThis);
      m_fieldMovementTimer.Stop();
    }
    else
    {
      field.Move( pos, nextPos );
      pos = nextPos;
    }     
  }
}
//////////////////////////////////////////////////////////////////////////

void MovementLogic::MoveTo( const GameField &field, TFieldPos pos, TFieldPos dstPos )
{
  ASSERT( field.IsValid(pos) );

  if( pos == dstPos )
    return;

  m_dstPos = dstPos;
  m_discretePath.Start( pos, dstPos );
  
  if( !m_fieldMovementTimer.IsInProgress() ) 
    m_fieldMovementTimer.Start(); 
}
//////////////////////////////////////////////////////////////////////////

void MovementLogic::SetPos( const GameField &field, TFieldPos pos )
{
  ASSERT( field.IsValid(pos) ); 
  m_dstPos = pos;
  m_fieldMovementTimer.Stop();
}
//////////////////////////////////////////////////////////////////////////

void MovementLogic::Stop()
{
  m_fieldMovementTimer.Stop();  
}
