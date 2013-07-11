#include "stdafx.h"
#include "TrapObj.h"

void TrapObj::Render( float deltaTime ) const
{
  Draw( *m_pTex, Rect( round<Point>(m_field.ToScreen(m_pos)), Size(15, 15)), 0, Color::make_yellow() );
}
//////////////////////////////////////////////////////////////////////////

void TrapObj::Touch( IGameObject *pWho )
{
  ASSERT( pWho != 0 );

  switch( pWho->GetType() )
  {
  case Player:
    pWho->Stop();
    break;

  case Enemy:
    pWho->Kill();
    break;     
  }
}
