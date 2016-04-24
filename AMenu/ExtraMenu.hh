// Started by Simon Bulcke
// Last update by Simon Bulcke
//

#ifndef		EXTRAMENU_HH_
# define	EXTRAMENU_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"

class		ExtraMenu : public AMenu
{
private:

  AObject	*_background;
  AObject	*_editor;
  AObject	*_rate;
  int		_selected;

public:

  ExtraMenu();
  virtual ~ExtraMenu();
  virtual bool	initialize();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif		/* EXTRAMENU_HH_ */
