// Started by Simon Bulcke
// Last update by Clovis Masson
//

#ifndef		MAINMENU_HH_
# define	MAINMENU_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"

class		MainMenu : public AMenu
{
private:

  AObject	*_background;
  AObject	*_game;
  AObject	*_tools;
  AObject	*_extras;
  AObject	*_head;
  int		_selected;
  int		_j;
  int		_k;

public:

  MainMenu();
  virtual ~MainMenu();
  virtual bool	initialize();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif		/* MAINMENU_HH_ */
