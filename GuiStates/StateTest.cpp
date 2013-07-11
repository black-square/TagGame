#include "stdafx.h"
#include "StateTest.h"
#include "Graphics/Texture.h"
#include "Gui/Widgets.h"

GuiStateTest::GuiStateTest():
  m_player(m_field, Point(0, 0), boost::make_shared<Texture>("./_data/mark.png") ),
  m_pTex( boost::make_shared<Texture>("./_data/grid.png") )
{
  /*
  AddWidget( boost::make_shared<Gui::Image>( 
    Rect( Point(0, 0), g_screenSize ), 
    boost::make_shared<Texture>("./_data/backg_main.png") 
  ));
  */
  
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnRender() const
{
  const Size size( m_field.GetSize() );
  Point cur;

  for( cur.x = 0; cur.x < size.w; ++cur.x )
    for( cur.y = 0; cur.y < size.h; ++cur.y )
      Draw( *m_pTex, round<Point>(m_field.ToScreen(cur)) ); 



  m_player.Render();
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnUpdate( float deltaTime )
{
  m_player.Update( deltaTime );
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnLButtonDown( Point pos )
{
  m_player.MoveTo( m_field.FromScreen(GameField::TScreenPos(pos)) );  
}

//////////////////////////////////////////////////////////////////////////