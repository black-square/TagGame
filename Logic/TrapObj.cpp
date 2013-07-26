#include "stdafx.h"
#include "TrapObj.h"

void TrapObj::Render( float deltaTime ) const
{
  Draw( *m_pTex, round<Point>(m_field.ToScreen(m_pos)) );
}
//////////////////////////////////////////////////////////////////////////

void TrapObj::Touch( IGameObject::TPtrParam pWho )
{
  ASSERT( pWho != 0 );

  switch( pWho->GetType() )
  {
  case Player:
    pWho->Stop();
    break;

  case Enemy:
    pWho->Kill( m_field.Get(this) );
    break;
      
  default:
    break;
  }
}
