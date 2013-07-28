#include "stdafx.h"
#include "Body.h"
#include "Engine/Core/Interp.hpp"
#include "GameConsts.h"

namespace
{
IBody::Direction CalcDirection( IBody::TPoint curPos, IBody::TPoint dstPos )
{
  const IBody::TPoint delta    =  dstPos - curPos;
  const IBody::TPoint absDelta = abs(delta);

  if( absDelta.x > absDelta.y )
    return delta.x > 0 ? IBody::Right : IBody::Left;
  else
    return delta.y > 0 ? IBody::Up : IBody::Down;
}
//////////////////////////////////////////////////////////////////////////

Point CalcTexPos( IBody::TPoint curPos, Size texSize, int vertDiff = 0 )
{
  return round<Point>(curPos) + 
    Point(Editor::GetCellSizePx() / 2, Editor::GetCellSizePx() + vertDiff ) -
    Point( texSize.w / 2, texSize.h );
}
}
//////////////////////////////////////////////////////////////////////////

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

  Direction curDir = Up;

  if( m_curTime < m_totalTime ) 
  {
    if( m_animTmr.TickWithRestartNonStop(deltaTime) )
      if( ++m_curFrame >= Editor::AnimFramesCount() )
        m_curFrame = 0;  

    curDir = CalcDirection( m_pos, m_dstPos );
  }

  m_blinkValue.Tick( deltaTime );

  Draw( *m_pTex, 
    CalcTexPos( m_pos, m_pTex->GetSize(), -2 ), 
    m_curFrame * TotalDir + curDir, 
    Color::make_white_a(Color::max() - m_blinkValue.Get()) 
  );
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
  m_blinkValue.InitStepTime( Color::min(), 200, 0.001f );
}
//////////////////////////////////////////////////////////////////////////

void Body::StopBlinking()
{
  m_blinkValue.InitFixed(Color::min() );
}
//////////////////////////////////////////////////////////////////////////

StaticBody::StaticBody( Texture::TPtrParam pTex ):
  m_pTex(pTex),
  m_animTmr(Editor::AnimSpeedStatic()),
  m_curFrame( std::rand() % Editor::AnimFramesCountStatic() )
{
  m_animTmr.Start();
}
//////////////////////////////////////////////////////////////////////////

void StaticBody::Render( float deltaTime )
{
  if( m_animTmr.TickWithRestartNonStop(deltaTime) )
    if( ++m_curFrame >= Editor::AnimFramesCountStatic() )
      m_curFrame = 0;  

  Draw( *m_pTex, 
    CalcTexPos( m_pos, m_pTex->GetSize(), 2 ), 
    m_curFrame 
  );
}
