#include "stdafx.h"
#include "StateMain.h"
#include "Gui/Widgets.h"
#include "StateTest.h"
#include "GameConsts.h"

//////////////////////////////////////////////////////////////////////////
GuiStateMain::GuiStateMain()
{
  AddWidget( boost::make_shared<Gui::Image>(
    Rect( Point(0, 0), Editor::GetScreenSizePx() ),
    boost::make_shared<Texture>( "./_data/backg_main.png" )
    ));
 
  const Texture::TPtr pBtnTex = boost::make_shared<Texture>( "./_data/button_01.png", 2 );
  const Font::TPtr pBtnFont = boost::make_shared<Font>( "./_data/gm.ttf", 25);

  AddWidget( boost::make_shared<Gui::Label>(
    Point(377, 10),
    boost::make_shared<Font>( "./_data/gm.ttf", 150), 
    "The Game",
    Color::make_white(),
    Gui::Label::Center
  ));

  AddWidget( boost::make_shared<Gui::Label>(
    Point(377, 545),
    boost::make_shared<Font>( "./_data/gm.ttf", 50), 
    "Dmitry Shesterkin   dfb@yandex.ru",
    Color::make_white(),
    Gui::Label::Center
  ));

  AddWidget( boost::make_shared<Gui::Button>(
    Rect( Point(252, 220), Size(250, 50) ),
    pBtnFont, pBtnTex,
    BIND_THIS(StartMainGameState),
    "Start Game"
  ));

  AddWidget( boost::make_shared<Gui::Button>(
    Rect( Point(252, 300), Size(250, 50) ),
    pBtnFont, pBtnTex,
    BIND_THIS(StartTestState),
    "Test state"
  ));

  AddWidget( boost::make_shared<Gui::Button>(
    Rect( Point(252, 380), Size(250, 50) ),
    pBtnFont, pBtnTex,
    BIND_THIS(StartAutoplayState),
    "Autoplay Test"
  ));
}
//////////////////////////////////////////////////////////////////////////

void GuiStateMain::StartAutoplayState()
{

}
//////////////////////////////////////////////////////////////////////////

void GuiStateMain::StartMainGameState()
{

}
//////////////////////////////////////////////////////////////////////////

void GuiStateMain::StartTestState()
{
  GetManager()->SetState( boost::make_shared<GuiStateTest>() );
}

