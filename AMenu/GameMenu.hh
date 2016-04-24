// Started by Kevin Fandi
// Last update by Kevin Fandi
//

#ifndef		GAMEMENU_HH_
# define	GAMEMENU_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"

class		GameMenu : public AMenu
{
private:

  AObject	*_background;
  AObject	*_newGame;
  AObject	*_loadGame;
  int		_selected;

public:

  GameMenu();
  virtual ~GameMenu();
  virtual bool	initialize();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif		/* GAMEMENU_HH_ */
