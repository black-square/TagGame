#include "stdafx.h"
#include "StateTest.h"
#include "Graphics/Texture.h"
#include "Gui/Widgets.h"
#include "Logic/TrapObj.h"
#include "Logic/EnemyObj.h"
#include "LogicConsts.h"

GuiStateTest::GuiStateTest():
  m_pTexGrid( boost::make_shared<Texture>("./_data/grid.png") ),
  m_pTexMark( boost::make_shared<Texture>("./_data/white.png")  )
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
  m_field.Set( Point(7,4), boost::make_shared<TrapObj>( m_field, m_pTexMark ) );
  
  m_field.Set( Point(10, 10), boost::make_shared<EnemyObj>( m_field, m_pTexMark ) );
  m_field.Set( Point(20, 10), boost::make_shared<EnemyObj>( m_field, m_pTexMark ) );  
  
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnRender( float deltaTime ) const
{
  ForEach( m_field.GetSize(), [&]( Point cur ) {
    Draw( *m_pTexGrid, round<Point>(m_field.ToScreen(cur)) );
  });

  ForEach( m_field, [deltaTime]( const IGameObject *pObj ) 
  {
    pObj->Render( deltaTime );
  });
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnUpdate()
{
  ForEach( m_field, []( IGameObject *pObj ) 
  {
    pObj->Update();
  }); 


  const auto pPlayer = m_pPlayer.lock();

  if( pPlayer )
  {
    ForEachRadius( m_field, pPlayer->GetPos(), Editor::EnemyVisibleDistance(), [&pPlayer]( IGameObject::TPtrParam pObj ) 
    { 
      pObj->PlayerVisible( pPlayer.get() );    
    });
  }
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnLButtonDown( Point pos )
{
  const auto pPlayer = m_pPlayer.lock();

  if( pPlayer )
    pPlayer->MoveTo( m_field.FromScreen(GameField::TScreenPos(pos)) );  
}

//////////////////////////////////////////////////////////////////////////