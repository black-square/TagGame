#include "stdafx.h"
#include "StateTest.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Gui/Widgets.h"
#include "Logic/TrapObj.h"
#include "Logic/EnemyObj.h"
#include "GameConsts.h"
#include "Presentation/Body.h"

GuiStateTest::GuiStateTest():
  m_pTexGrid( boost::make_shared<Texture>("./_data/grid.png") ),
  m_camera( Camera::SizeF(Editor::FieldSizePx()), Camera::SizeF(Editor::VisibleFieldSizePx()) ),
  m_score(0),
  m_enemyCount(0)
{
  const auto pTexPlayer = boost::make_shared<Texture>( "./_data/mark.png" );
  const auto pTexMark = boost::make_shared<Texture>("./_data/white.png");
  const auto pTexChar = boost::make_shared<Texture>( "./_data/char1.png", 12 );
  const auto pTexEnemy = boost::make_shared<Texture>( "./_data/char2.png", 12 );
 
  m_pEffects = boost::make_shared<Effects>();

  const Font::TPtr pFont = boost::make_shared<Font>( "./_data/gm.ttf", 25);

  m_pScoreLbl = boost::make_shared<Gui::Label>(
    Point(10, 10),
    pFont, 
    "Score: 0",
    Color::make_yellow(),
    Gui::Label::Left
  );

  AddWidget(m_pScoreLbl);

  m_pLivesLbl = boost::make_shared<Gui::Label>(
    Point( Editor::VisibleFieldSizePx().w - 10, 10 ),
    pFont, 
    "Lives: 0",
    Color::make_yellow(),
    Gui::Label::Right
    );

  AddWidget(m_pLivesLbl);

  m_pWinLoseLbl = boost::make_shared<Gui::Label>(
    Point( Editor::VisibleFieldSizePx().w / 2, Editor::VisibleFieldSizePx().h / 2 ),
    boost::make_shared<Font>( "./_data/gm.ttf", 40), 
    "",
    Color::make_white(),
    Gui::Label::Center
    );

  AddWidget(m_pWinLoseLbl);

  const auto pPlayer = m_field.MakeShared<PlayerObj>( m_field, boost::make_shared<Body>(pTexChar, m_pEffects), pTexMark, this );
  m_pPlayer = pPlayer;
  m_field.Set( Point(3,2), pPlayer ); 

  for( int x = 0; x < m_field.GetSize().w; x +=4 )
    for( int y = 0; y < m_field.GetSize().h; y +=4 )
      m_field.Set( Point(x ,y), m_field.MakeShared<TrapObj>( m_field, pTexPlayer ) );

  for( int x = 0; x < 2; ++x )
    for( int y = 0; y < 4; ++y )
    {
      m_field.Set( Point(22, 10) + Point(x, y) * 4, m_field.MakeShared<EnemyObj>( m_field, boost::make_shared<Body>(pTexEnemy, m_pEffects), pTexMark, this ) );
      ++m_enemyCount;
    }
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnRenderBelow( float deltaTime ) const
{
  const auto pPlayer = m_pPlayer.lock();

  if( pPlayer )
    m_camera.SetDestPos( pPlayer->GetBody()->GetPos() );
  
  m_camera.Update( deltaTime );
  m_camera.SetTransform();

  ForEach( m_field.GetSize(), [this]( Point cur ) {
    Draw( *m_pTexGrid, round<Point>(m_field.ToScreen(cur)) );
  });

  ForEach( m_field.GetSize(), [this, deltaTime]( Point cur ) 
  {
    auto &pVal = m_field.Get(cur);

    if( pVal )
      pVal->Render( deltaTime );
  });  

  m_pEffects->Render(deltaTime);

  m_camera.RestoreTransform(); 
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnUpdateStep()
{
  ForEachSafeDelete( m_field, [this]( IGameObject *pObj ) 
  {
    pObj->Update();
    m_field.DestroyDeleatedObjects();
  }); 

  const auto pPlayer = m_pPlayer.lock();

  if( pPlayer )
  {
    ForEachRadius( m_field, pPlayer->GetPos(), Editor::EnemyVisibleDistance(), [&pPlayer]( IGameObject::TPtrParam pObj ) 
    { 
      pObj->PlayerVisible( pPlayer );    
    });
  }
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnLButtonDown( Point pos )
{
  const auto pPlayer = m_pPlayer.lock();

  const auto fieldPos = m_field.FromScreen(m_camera.screenToField(GameField::TScreenPos(pos)));

  if( pPlayer && m_field.IsValid(fieldPos) )
    pPlayer->MoveTo( fieldPos );  
}

void GuiStateTest::OnAddScore( int val )
{
  m_score += val;
  m_pScoreLbl->SetText( MakeString( FMT("Score: %d") % m_score ), Color::make_yellow() );
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnSetLives( int val )
{
  m_pLivesLbl->SetText( MakeString( FMT("Lives: %d") % val ), Color::make_yellow() );

  if( val == 0 )
    OnLose();
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnEnemyDestroyed()
{
  if( --m_enemyCount <= 0 )
    OnWin();  
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnWin()
{
  m_pWinLoseLbl->SetText( "You win!" ); 
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnLose()
{
  m_pWinLoseLbl->SetText( "You lose!" );
}

//////////////////////////////////////////////////////////////////////////