#include "stdafx.h"
#include "EnemyObj.h"
#include "GameConsts.h"

EnemyObj::EnemyObj( GameField &field, IBody::TPtrParam pBody, Texture::TPtrParam pTex ): 
  m_field(field), 
  m_moveLogic(Editor::EnemyCellMoveTime(), pBody.get() ),
  m_pBody(pBody),
  m_pTex(pTex)
{

}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::Update()
{ 
  if( !m_moveLogic.Update(this, m_field) )
    return;  
  
  const auto pTarget = m_pTarget.lock();
  const auto visDistSquared = Editor::EnemyVisibleDistance() * Editor::EnemyVisibleDistance();

  if( !pTarget || vecLengthSquared(m_moveLogic.GetPos() - pTarget->GetPos()) > visDistSquared )
  {
    m_pTarget.reset();
    return;  
  }

  if( !m_moveLogic.IsInProgress() || m_moveLogic.GetDstPos() != pTarget->GetPos() )
    if( !m_moveLogic.MoveTo( this, m_field, pTarget->GetPos() ) )
      return; 
    
  ForEachRadius( m_field, m_moveLogic.GetPos(), Editor::EnemyShoutDistance(), [this]( IGameObject::TPtrParam pObj ) 
  { 
    pObj->PlayerCouldBeAtPos( m_moveLogic.GetDstPos() );    
  }); 
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::Render( float deltaTime ) const
{
#if 0
  ForEachRadius( m_moveLogic.GetPos(), Editor::EnemyShoutDistance(), [&]( Point cur ) 
  {
    Draw( *m_pTex, round<Point>(m_field.ToScreen(cur)), 0, change_a( Color::make_magenta(), 50) );
  });

  ForEachRadius( m_moveLogic.GetPos(), Editor::EnemyVisibleDistance(), [&]( Point cur ) 
  {
    Draw( *m_pTex, round<Point>(m_field.ToScreen(cur)), 0, change_a( Color::make_magenta(), 25) );
  });

#endif

  Draw( *m_pTex, round<Point>(m_field.ToScreen(m_moveLogic.GetPos())), 0, Color::make_white_a(40) );

  m_pBody->Render( deltaTime );  
}
//////////////////////////////////////////////////////////////////////////

void EnemyObj::MoveTo( TFieldPos pos )
{
  m_moveLogic.MoveTo( this, m_field, pos );
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
  m_pBody->Effects()->Play( m_field.ToScreenCenter(GetPos()), IEffects::EnemyDied );  
  m_field.Set( m_moveLogic.GetPos() );
}
