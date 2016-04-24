// Started by Clovis Masson
// Last update by Clovis Masson
//

#ifndef		FREEMODE_HH_
# define	FREEMODE_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"
# include	"../GameEngine.hh"

class		FreeMode : public AMenu
{
private:

  std::vector<std::string>	_list;
  AObject*			_background;
  Run				*_run;
  int				_selected;
  int				_selectedMap;
  int				_step;
  std::string			_fpname;
  std::string			_spname;
  int				_nbIa;
  int				_mapX;
  int				_mapY;
  int				_BDensity;
  int				_CDensity;

public:

  FreeMode(Run *run);
  virtual ~FreeMode();
  virtual bool			initialize();
  virtual void			draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module		update(gdl::Clock const &clock, gdl::Input &input);
};

#endif		/* FREEMODE_HH_ */
