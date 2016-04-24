// Started by Clovis Masson
// Last update by Clovis Masson
//

#ifndef		IA_HH_
# define	IA_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Bomb;

class		Ia : public AObject
{
private:

  gdl::Model		_model;
  float			_speed;
  int			_id;
  std::vector<Bomb*>	_bombs;
  int			_allowed_bomb;
  Direction		_dir;
  int			_bomb_id;
  int			_range;
  int			_level;
  int			_aggressive;
  int			_defensive;
  int			_bonus;
  int			_ally;
  int			_timer;

public:

  Ia();
  Ia(float, float, int, Direction, int, int, int, int, int, int, int, int, float);
  Ia(int x, int y, int z, int id);
  bool		initialize();
  virtual	~Ia();
  virtual bool	initialize(std::string, glm::vec3);
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  void		setIa();
  void		moveUp(gdl::Clock const &clock, gdl::Input &input);
  void		moveDown(gdl::Clock const &clock, gdl::Input &input);
  void		moveLeft(gdl::Clock const &clock, gdl::Input &input);
  void		moveRight(gdl::Clock const &clock, gdl::Input &input);
  glm::vec3	getPos()const;
  int		getId()const;
  std::string	getType()const;
  void		setDirection(Direction);
  int		getAllowed()const;
  int		getBombsList()const;
  void		pushBomb(Bomb *bomb);
  Direction	getDirection()const;
  int		getBombId()const;
  void		setBombId(int);
  void		seekBomb(int);
  int		getDefense()const;
  int		getOffense()const;
  int		getRange()const;
  int		getAlly()const;
  int		getLevel()const;
  char		getT()const;
  std::string	getData()const;
  void		setLevel(int);
  void		setOffense(int);
  void		setDefense(int);
  void		setSpeed(float);
  void		setBonus(int);
  void		setAllowed(int);
  void		setAlly(int);
  void		setRange(int);
  void		setTimer(int);
};

#endif		/* IA_HH_ */
