#include "stdafx.h"
#include "PlayerObj.h"
#include "Audio/SoundManager.h"
#include "GameConsts.h"

PlayerObj::PlayerObj( GameField &field, IBody::TPtrParam pBody, Texture::TPtrParam pTex ): 
  m_field(field), 
  m_moveLogic( Editor::PlayerCellMoveTime() ),
  m_pBody(pBody),
  m_pTex(pTex)
{}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Update()
{
  m_moveLogic.Update( this, m_field );

  if( !m_moveLogic.IsInProgress() )
    m_pBody->MoveTo( m_field.ToScreen(m_moveLogic.GetPos()), m_moveLogic.GetCellMoveTime() );
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
  m_moveLogic.MoveTo(m_field, pos );
  m_pBody->MoveTo( m_field.ToScreen(pos), m_moveLogic.GetTotalMoveTime() + m_moveLogic.GetCellMoveTime() / 2 );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::SetPos( TFieldPos pos ) 
{
  m_moveLogic.SetPos( m_field, pos );
  m_pBody->SetPos( m_field.ToScreen(pos) );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Stop()
{
  PlaySound("./_data/fall.wav"); 
}
