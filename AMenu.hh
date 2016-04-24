// Started by Medhi Kolai
// Last update by Medhi Kolai
//

#ifndef		AMENU_HH_
# define	AMENU_HH_

# include	"Bomberman.hh"
# include	"AObject.hh"
# include	"./AObject/Objects.hh"
//# include	"Run.hh"

class		Run;

class AMenu
{
public:

  AMenu();//Run *run);
  virtual ~AMenu();
  virtual bool	initialize();
  virtual Module	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif		/* AMENU_HH_ */
