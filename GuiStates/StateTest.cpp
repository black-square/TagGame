#include "stdafx.h"
#include "StateTest.h"
#include "Graphics/Texture.h"
#include "Gui/Widgets.h"
#include "Logic/TrapObj.h"

GuiStateTest::GuiStateTest():
  m_pTex( boost::make_shared<Texture>("./_data/grid.png") )
{
  /*
  AddWidget( boost::make_shared<Gui::Image>( 
    Rect( Point(0, 0), g_screenSize ), 
    boost::make_shared<Texture>("./_data/backg_main.png") 
  ));
  */

  const Texture::TPtr pTexPlayer = boost::make_shared<Texture>( "./_data/mark.png" );

  const auto pPlayer = boost::make_shared<PlayerObj>( m_field, pTexPlayer );
  m_pPlayer = pPlayer;
  m_field.Set( Point(3,2), pPlayer ); 
  m_field.Set( Point(7,4), boost::make_shared<TrapObj>( m_field, pTexPlayer ) );  
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnRender() const
{
  ForEach( m_field.GetSize(), [&]( Point cur) {
    Draw( *m_pTex, round<Point>(m_field.ToScreen(cur)) );
  });

  ForEach( m_field, []( IGameObject::TPtrParam pObj) 
  {
    pObj->Render();
  });
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnUpdate( float deltaTime )
{
  ForEach( m_field, [deltaTime]( IGameObject::TPtrParam pObj) 
  {
    pObj->Update( deltaTime );
  }); 
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnLButtonDown( Point pos )
{
  const auto pPLayer = m_pPlayer.lock();

  if( pPLayer )
    pPLayer->MoveTo( m_field.FromScreen(GameField::TScreenPos(pos)) );  
}

//////////////////////////////////////////////////////////////////////////