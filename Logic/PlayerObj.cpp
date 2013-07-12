#include "stdafx.h"
#include "PlayerObj.h"
#include "Audio/SoundManager.h"
#include "GameConsts.h"

PlayerObj::PlayerObj( GameField &field, IBody::TPtrParam pBody, Texture::TPtrParam pTex ): 
  m_field(field), 
  m_moveLogic( Editor::PlayerCellMoveTime(), pBody.get() ),
  m_pBody(pBody),
  m_pTex(pTex)
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
  PlaySound("./_data/fall.wav"); 
}
