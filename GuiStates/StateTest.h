#ifndef StateTest_h__
#define StateTest_h__

#include "Gui/State.h"
#include "Logic/PlayerObj.h"

class GuiStateTest: public Gui::State
{   
public:
  typedef GuiStateTest ThisType;
 
public:
  GuiStateTest();

private:
  void OnRender() const override;
  void OnUpdate( float deltaTime ) override;
  void OnLButtonDown( Point pos ) override;

private:
  GameField m_field;
  PlayerObj m_player;

  Texture::TPtr m_pTex;
};

#endif // StateTest_h__