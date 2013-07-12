#ifndef StateTest_h__
#define StateTest_h__

#include "Gui/State.h"
#include "Logic/PlayerObj.h"
#include "Particles/ParticlesManager.h"
#include "Presentation/Effects.h"

class GuiStateTest: public Gui::State
{   
public:
  typedef GuiStateTest ThisType;
 
public:
  GuiStateTest();

private:
  void OnRender( float deltaTime ) const override;
  void OnUpdate() override;
  void OnLButtonDown( Point pos ) override;

private:
  GameField m_field;
  Texture::TPtr m_pTexGrid;
  Texture::TPtr m_pTexMark;
  boost::weak_ptr<PlayerObj> m_pPlayer;
  Effects::TPtr m_pEffects;
};

#endif // StateTest_h__