#include "stdafx.h"
#include "Body.h"
#include "Core/Interp.hpp"

Body::Body( Texture::TPtrParam pTex ):
  m_curTime(0),
  m_totalTime(0),
  m_pTex(pTex)
{}
//////////////////////////////////////////////////////////////////////////

void Body::Render( float deltaTime )
{
  if( m_curTime >= m_totalTime )
    m_pos = m_dstPos;
  else
  {
    m_curTime += deltaTime;
    m_pos = Lerp( m_fromPos, m_dstPos, m_curTime / m_totalTime );
  }

  Draw( *m_pTex, Rect( round<Point>(m_pos), Size(15, 15)) );
}
//////////////////////////////////////////////////////////////////////////

void Body::MoveTo( TPoint dst, float time )
{
  ASSERT( time > 0 );
  
  m_fromPos = m_pos;
  m_dstPos = dst;
  m_curTime = 0;
  m_totalTime = time;
}
//////////////////////////////////////////////////////////////////////////

void Body::SetPos( TPoint dst )
{
  m_pos = dst;
  m_fromPos = dst;
  m_dstPos = dst;
  m_curTime = 0;
  m_totalTime = 0;
}
//////////////////////////////////////////////////////////////////////////

void Body::Stop()
{
  m_dstPos = m_pos;
  m_curTime = 0;
  m_totalTime = 0;
}
