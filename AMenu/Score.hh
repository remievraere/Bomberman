// Started by Remi Evraere
// Last update by Medhi Kolai
//


#ifndef		SCORE_HH_
# define	SCORE_HH_

# include	"../Bomberman.hh"
# include	"../AMenu.hh"
# include	"../GameEngine.hh"

class		Score : public AMenu
{
private:
  std::vector<std::string>	_name;
  std::vector<int>		_score;
  AObject	*_background;
  int		_selected;

public:

  Score();
  virtual ~Score();
  virtual bool	initialize();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual Module	update(gdl::Clock const &clock, gdl::Input &input);

  void		bestScore(std::vector<AObject*>);
  void		saveScore();
  Module	printScore();
};

# endif		/* SCORE_HH_ */
