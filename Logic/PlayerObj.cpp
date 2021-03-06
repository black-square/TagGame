#include "stdafx.h"
#include "PlayerObj.h"
#include "GameConsts.h"

PlayerObj::PlayerObj( GameField &field, IBody::TPtrParam pBody, Texture::TPtrParam pTex, IGlobalGameEvents *pGameEvents ): 
  m_field(field), 
  m_moveLogic( Editor::PlayerCellMoveTime(), pBody.get() ),
  m_pBody(pBody),
  m_pTex(pTex),
  m_pGameEvents(pGameEvents),
  m_lives( Editor::LivesCount() ),
  m_invulnerabilityTimer( Editor::InvulnerabilityTime() )
{}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Update()
{
  m_moveLogic.Update( this, m_field );
  if( m_invulnerabilityTimer.Tick( Editor::LogicUpdateTime() ) )
    m_pBody->StopBlinking();
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Render( float deltaTime ) const
{
  Draw( *m_pTex, round<Point>(m_field.ToScreen(m_moveLogic.GetPos())), 0, Color::make_white_a(20) );
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
  m_pGameEvents->OnSetLives( m_lives );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Stop()
{
  m_pBody->Effects()->Play( m_field.ToScreenCenter(GetPos()), IEffects::PlayerStoped );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Kill( IGameObject::TPtrParam pKiller )
{
  m_pBody->Effects()->Play( m_field.ToScreenCenter(GetPos()), IEffects::PlayerDied );
  m_field.Set( m_moveLogic.GetPos() );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Touch( IGameObject::TPtrParam pWho )
{
  ASSERT( pWho != 0 );

  if( pWho->GetType() == IGameObject::Enemy && !m_invulnerabilityTimer.IsInProgress() )
  {
    --m_lives;
    m_pGameEvents->OnSetLives(m_lives); 

    const IGameObject::TPtr pThis( m_field.Get(this) );

    pWho->Kill( pThis );
    
    if( m_lives <= 0 )
      Kill( pThis );
    else
    {
      m_invulnerabilityTimer.Start();
      m_pBody->StartBlinking();
    }  
  }  
}