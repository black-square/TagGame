#include "stdafx.h"
#include "PlayerObj.h"
#include "GameConsts.h"

PlayerObj::PlayerObj( GameField &field, IBody::TPtrParam pBody, Texture::TPtrParam pTex, IGlobalGameEvents *pGameEvents ): 
  m_field(field), 
  m_moveLogic( Editor::PlayerCellMoveTime(), pBody.get() ),
  m_pBody(pBody),
  m_pTex(pTex),
  m_pGameEvents(pGameEvents)
{}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Update()
{
  m_moveLogic.Update( this, m_field );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Render( float deltaTime ) const
{
  Draw( *m_pTex, round<Point>(m_field.ToScreen(m_moveLogic.GetPos())), 0, Color::make_white_a(40) );
  m_pBody->Render( deltaTime );   
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::MoveTo( TFieldPos pos )
{
  m_moveLogic.MoveTo(this, m_field, pos );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::SetPos( TFieldPos pos ) 
{
  m_moveLogic.SetPos( m_field, pos );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Stop()
{
  m_pBody->Effects()->Play( m_field.ToScreenCenter(GetPos()), IEffects::PlayerStoped );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Kill( IGameObject *pKiller )
{
  m_pBody->Effects()->Play( m_field.ToScreenCenter(GetPos()), IEffects::PlayerDied );
  m_field.Set( m_moveLogic.GetPos() );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Touch( IGameObject *pWho )
{
  ASSERT( pWho != 0 );

  if( pWho->GetType() == IGameObject::Enemy )
  {
    m_pGameEvents->OnLifeLost(); 
    pWho->Kill(this);
    Kill( this );  
  }  
}