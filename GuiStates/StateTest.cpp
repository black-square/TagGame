#include "stdafx.h"
#include "StateTest.h"
#include "Graphics/Texture.h"
#include "Gui/Widgets.h"
#include "Logic/TrapObj.h"
#include "Logic/EnemyObj.h"
#include "GameConsts.h"
#include "Presentation/Body.h"
#include "Core/Rect.hpp"

GuiStateTest::GuiStateTest():
  m_pTexGrid( boost::make_shared<Texture>("./_data/grid.png") ),
  m_pTexMark( boost::make_shared<Texture>("./_data/white.png")  ),
  m_camera( Camera::SizeF(Editor::FieldSizePx()), Camera::SizeF(Editor::VisibleFieldSizePx()) )
{
  /*
  AddWidget( boost::make_shared<Gui::Image>( 
    Rect( Point(0, 0), g_screenSize ), 
    boost::make_shared<Texture>("./_data/backg_main.png") 
  ));
  */

  const Texture::TPtr pTexPlayer = boost::make_shared<Texture>( "./_data/mark.png" );
  m_pEffects = boost::make_shared<Effects>();

  const auto pPlayer = boost::make_shared<PlayerObj>( m_field, boost::make_shared<Body>(pTexPlayer, m_pEffects), m_pTexMark );
  m_pPlayer = pPlayer;
  m_field.Set( Point(3,2), pPlayer ); 

  for( int x = 0; x < m_field.GetSize().w; x +=4 )
    for( int y = 0; y < m_field.GetSize().h; y +=4 )
      m_field.Set( Point(x ,y), boost::make_shared<TrapObj>( m_field, m_pTexMark ) );
  
  m_field.Set( Point(10, 10), boost::make_shared<EnemyObj>( m_field, boost::make_shared<Body>(pTexPlayer, m_pEffects), m_pTexMark ) );
  m_field.Set( Point(20, 10), boost::make_shared<EnemyObj>( m_field, boost::make_shared<Body>(pTexPlayer, m_pEffects), m_pTexMark ) );

     
}
//////////////////////////////////////////////////////////////////////////

void GuiStateTest::OnRender( float deltaTime ) const
{
  const auto pPlayer = m_pPlayer.lock();

  if( pPlayer )
    m_camera.SetDestPos( pPlayer->GetBody()->GetPos() );
  
  m_camera.Update( deltaTime );
  m_camera.SetTransform();

  ForEach( m_field.GetSize(), [&]( Point cur ) {
    Draw( *m_pTexGrid, round<Point>(m_field.ToScreen(cur)) );
  });

  ForEach( m_field, [deltaTime]( const IGameObject *pObj ) 
  {
    pObj->Render( deltaTime );
  });  

  m_pEffects->Render(deltaTime);

  m_camera.RestoreTransform();
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

  const auto fieldPos = m_field.FromScreen(m_camera.screenToField(GameField::TScreenPos(pos)));

  if( pPlayer && m_field.IsValid(fieldPos) )
    pPlayer->MoveTo( fieldPos );  
}

//////////////////////////////////////////////////////////////////////////