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
  Texture::TPtr m_pTex;
  boost::weak_ptr<PlayerObj> m_pPlayer;
};

#endif // StateTest_h__