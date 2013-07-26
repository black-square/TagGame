#include "stdafx.h"
#include "Body.h"
#include "Engine/Core/Interp.hpp"
#include "GameConsts.h"

Body::Body( Texture::TPtrParam pTex, IEffects::TPtrParam pEff ):
  m_curTime(0),
  m_totalTime(0),
  m_pTex(pTex),
  m_pEff(pEff), 
  m_animTmr(Editor::AnimSpeed()),
  m_curFrame(0),
  m_blinkValue(Color::min())
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
    if( ++m_curFrame >= Editor::AnimFramesCount() )
      m_curFrame = 0;  

  enum Direction
  {
    Up,
    Left,
    Right,
    Down,
    TotalDir
  };

  Direction curDir = Up;

  if( m_curTime < m_totalTime )
  {
    const TPoint delta    =  m_dstPos - m_pos;
    const TPoint absDelta = abs(delta);

    if( absDelta.x > absDelta.y )
      curDir = delta.x > 0 ? Right : Left;
    else
      curDir = delta.y > 0 ? Up : Down;
  }
  
  const Point pos = 
    round<Point>(m_pos) + 
    Point(Editor::GetCellSizePx() / 2, Editor::GetCellSizePx() - 2 ) -
    Point( m_pTex->GetSize().w / 2, m_pTex->GetSize().h );

  m_blinkValue.Tick( deltaTime );

  Draw( *m_pTex, pos, m_curFrame * TotalDir + curDir, Color::make_white_a(Color::max() - m_blinkValue.Get()) );
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

void Body::StartBlinking()
{
  m_blinkValue.InitStepTime( Color::min(), 150, 0.002f );
}
//////////////////////////////////////////////////////////////////////////

void Body::StopBlinking()
{
  m_blinkValue.InitFixed(Color::min() );
}