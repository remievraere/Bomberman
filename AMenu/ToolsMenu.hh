// Started by Medhi Kolai
// Last update by Clovis Masson
//


#ifndef		TOOLSMENU_HH_
# define	TOOLSMENU_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"
# include	"../GameEngine.hh"

class		ToolsMenu : public AMenu
{
private :

  AObject	*_background;
  int		_selected;
  Run		*_run;

public :

  ToolsMenu(Run *run);
  virtual ~ToolsMenu();
  virtual bool	initialize();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif		/* TOOLSMENU_HH_ */
