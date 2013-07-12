#include "stdafx.h"
#include "Body.h"
#include "Core/Interp.hpp"
#include "GameConsts.h"

Body::Body( Texture::TPtrParam pTex, IEffects::TPtrParam pEff ):
  m_curTime(0),
  m_totalTime(0),
  m_pTex(pTex),
  m_pEff(pEff), 
  m_animTmr(0.2f),
  m_curFrame(0)
{
  m_animTmr.Start();
}
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

  if( m_animTmr.TickWithRestartNonStop(deltaTime) && m_curTime < m_totalTime )
    if( ++m_curFrame > 2 )
      m_curFrame = 0;  

  int curDir = 0;

  if( m_curTime < m_totalTime )
  {
    const TPoint delta    =  m_dstPos - m_pos;
    const TPoint absDelta = abs(delta);

    if( absDelta.x > absDelta.y )
      curDir = delta.x > 0 ? 2 : 1;
    else
      curDir = delta.y > 0 ? 0 : 3;
  }
  
  const Point pos = 
    round<Point>(m_pos) + 
    Point(Editor::GetCellSizePx() / 2, Editor::GetCellSizePx() - 2 ) -
    Point( m_pTex->GetSize().w / 2, m_pTex->GetSize().h );

  Draw( *m_pTex, pos, m_curFrame * 4 + curDir );
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
//////////////////////////////////////////////////////////////////////////
