#include "stdafx.h"
#include "EnemyObj.h"
#include "GameConsts.h"
#include "Audio/SoundManager.h"

EnemyObj::EnemyObj( GameField &field, Texture::TPtrParam pTex ): 
  m_field(field), 
  m_moveLogic(Editor::EnemyCellMoveTime()),
  m_pTex(pTex)
{

}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::Update()
{ 
  const auto pSelfGuard( shared_from_this() );  //Protect from deletion before return

  m_moveLogic.Update( this, m_field );
  
  const auto pTarget = m_pTarget.lock();
  const auto visDistSquared = Editor::EnemyVisibleDistance() * Editor::EnemyVisibleDistance();

  if( !pTarget || vecLengthSquared(m_moveLogic.GetPos() - pTarget->GetPos()) > visDistSquared )
  {
    m_pTarget.reset();
    return;  
  }

  if( !m_moveLogic.IsInProgress() || m_moveLogic.GetDstPos() != pTarget->GetPos() )
    MoveTo( pTarget->GetPos() ); 
    
  ForEachRadius( m_field, m_moveLogic.GetPos(), Editor::EnemyShoutDistance(), [this]( IGameObject::TPtrParam pObj ) 
  { 
    pObj->PlayerCouldBeAtPos( m_moveLogic.GetDstPos() );    
  }); 
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::Render( float deltaTime ) const
{
  ForEachRadius( m_moveLogic.GetPos(), Editor::EnemyShoutDistance(), [&]( Point cur ) 
  {
    Draw( *m_pTex, round<Point>(m_field.ToScreen(cur)), 0, change_a( Color::make_magenta(), 50) );
  });

  ForEachRadius( m_moveLogic.GetPos(), Editor::EnemyVisibleDistance(), [&]( Point cur ) 
  {
    Draw( *m_pTex, round<Point>(m_field.ToScreen(cur)), 0, change_a( Color::make_magenta(), 25) );
  });

  Draw( *m_pTex, Rect( round<Point>(m_field.ToScreen(m_moveLogic.GetPos())), Size(15, 15)), 0, Color::make_red() );  
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::MoveTo( TFieldPos pos )
{
  m_moveLogic.MoveTo(m_field, pos );
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::SetPos( TFieldPos pos ) 
{
  m_moveLogic.SetPos( m_field, pos );
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::PlayerVisible( IGameObject *pPlayer )
{
  ASSERT( pPlayer != 0 );

  if( !m_pTarget.expired() )
    return;

  m_pTarget = pPlayer->shared_from_this();
  MoveTo( pPlayer->GetPos() );
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::PlayerCouldBeAtPos( TFieldPos pos )
{
  if( !m_pTarget.expired() )
    return;

  MoveTo( pos );  
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::Kill()
{
  m_field.Set( m_moveLogic.GetPos() );
  PlaySound("./_data/expl.wav");
}
