// Started by Remi Evraere
// Last update by Remi Evraere
//

#ifndef		LOADGAME_HH_
# define	LOADGAME_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"
# include	"../GameEngine.hh"

class		LoadGame : public AMenu
{
private:

  std::vector<std::string>	_list;
  AObject*			_background;
  Run*				_run;
  int				_selected;

public:

  LoadGame(Run *run);
  virtual ~LoadGame();
  virtual bool			initialize();
  virtual void			draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module		update(gdl::Clock const &clock, gdl::Input &input);
};

#endif		/* LOADGAME_HH_ */
