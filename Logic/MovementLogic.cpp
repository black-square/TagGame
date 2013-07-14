#include "stdafx.h"
#include "MovementLogic.h"
#include "GameConsts.h"

bool MovementLogic::CheckNextPos( IGameObject *pThis, const GameField &field )
{
  auto &pObj = field.Get( m_discretePath.GetNextPos() );

  if( pObj )
  {
    m_fieldMovementTimer.Stop();
    m_pBody->MoveTo( field.ToScreen(GetPos()), GetCellMoveTime() );
    pObj->Touch(field.Get(pThis));
    return false;
  }

  return true;
}
//////////////////////////////////////////////////////////////////////////

bool MovementLogic::Update( IGameObject *pThis, GameField &field )
{
  if( m_fieldMovementTimer.TickWithRestart(Editor::LogicUpdateTime()) )
  {
    ASSERT( GetPos() != GetDstPos() );

    if( !CheckNextPos(pThis, field) )
      return false;

    field.Move( m_discretePath.GetPos(), m_discretePath.GetNextPos() );
    m_discretePath.Step();
    
    if( GetPos() == GetDstPos() )
    {
      m_fieldMovementTimer.Stop();
      return true;
    }

    if( !CheckNextPos(pThis, field) )
      return false;   
  }

  return true;
}
//////////////////////////////////////////////////////////////////////////

bool MovementLogic::MoveTo( IGameObject *pThis, const GameField &field, TFieldPos dstPos )
{
  ASSERT( field.IsValid(dstPos) );

  if( GetPos() == dstPos )
    return false;

  m_discretePath.Start( dstPos );

  if( !CheckNextPos(pThis, field) )
    return false;
  
  if( !m_fieldMovementTimer.IsInProgress() ) 
    m_fieldMovementTimer.Start(); 

  m_pBody->MoveTo( field.ToScreen(GetDstPos()), GetTotalMoveTime() );

  return true;
}
//////////////////////////////////////////////////////////////////////////

void MovementLogic::SetPos( const GameField &field, TFieldPos pos )
{
  ASSERT( field.IsValid(pos) );

  m_discretePath.SetPos(pos);
  m_fieldMovementTimer.Stop();

  m_pBody->SetPos( field.ToScreen(pos) );
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

  const TFieldPos delta( abs(GetDstPos() - GetPos()) );

  return std::max( delta.x, delta.y ) * GetCellMoveTime();
}
