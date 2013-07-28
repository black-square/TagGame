#include "stdafx.h"
#include "StateMain.h"
#include "Engine/Gui/Widgets.h"
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
  const Font::TPtr pBtnFont = boost::make_shared<Font>( "./_data/gm.ttf", 20);

  AddWidget( boost::make_shared<Gui::Label>(
    Point(Editor::VisibleFieldSizePx().w / 2, 10),
    boost::make_shared<Font>( "./_data/gm.ttf", 60), 
    "Tag Game",
    Color::make_white(),
    Gui::Label::Center
  ));

  AddWidget( boost::make_shared<Gui::Label>(
    Point(Editor::VisibleFieldSizePx().w / 2, Editor::VisibleFieldSizePx().h - 35 ),
    boost::make_shared<Font>( "./_data/gm.ttf", 30), 
    "mango2d engine demo",
    Color::make_white(),
    Gui::Label::Center
  ));

  AddWidget( boost::make_shared<Gui::Button>(
    Rect( Point(Editor::VisibleFieldSizePx().w / 2 - 100, Editor::VisibleFieldSizePx().h / 2), Size(200, 40) ),
    pBtnFont, pBtnTex,
    [this](){ GetManager()->SetState( boost::make_shared<GuiStateTest>() ); },
    "Start Game"
  ));
}
//////////////////////////////////////////////////////////////////////////


