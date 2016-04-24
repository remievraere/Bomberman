// Started by Simon Bulcke
// Last update by Simon Bulcke
//

#ifndef		NEWGAME_HH_
# define	NEWGAME_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"
# include	"../GameEngine.hh"

class		NewGame : public AMenu
{
private:

  AObject*			_background;
  AObject*			_freeMode;
  AObject*			_arcade;
  AObject*			_survival;
  AObject*			_sfreeMode;
  AObject*			_sarcade;
  AObject*			_ssurvival;
  int				_selected;

public:

  NewGame();
  virtual ~NewGame();
  virtual bool	initialize();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif		/* NEWGAME_HH_ */
