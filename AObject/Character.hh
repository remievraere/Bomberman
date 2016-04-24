// Started by Remi Evraere
// Last update by Simon Bulcke
//

#ifndef			CHARACTER_HH_
# define		CHARACTER_HH_

# include		"../Bomberman.hh"
# include		"../AObject.hh"

class Bomb;

class Character : public AObject
{
private:

  gdl::Model		_model;
  float			_speed;
  int			_id;
  Direction		_dir;
  std::vector<Bomb*>	_bombs;
  int			_allowed_bomb;
  int			_bomb_id;
  int			_range;
  std::string           _name;
  int                   _score;

public:

  Character();
  Character(int, int, int, int, std::string);
  Character(float, float, Direction, float, int, int, int, int, std::string, int);
  virtual		~Character();
  virtual bool		initialize();
  virtual void		update(gdl::Clock const&, gdl::Input&);
  virtual void		draw(gdl::AShader&, gdl::Clock const&);
  glm::vec3		getPos()const;
  int			getId()const;
  std::string		getType()const;
  void			moveUp(gdl::Clock const&, gdl::Input&);
  void			moveDown(gdl::Clock const&, gdl::Input&);
  void			moveLeft(gdl::Clock const&, gdl::Input&);
  void			moveRight(gdl::Clock const&, gdl::Input&);
  int			getAllowed()const;
  int			getBombsList()const;
  void			pushBomb(Bomb*);
  Direction		getDirection()const;
  int			getBombId()const;
  void			setBombId(int);
  void			seekBomb(int);
  void			setAllowedBomb(int);
  void			setSpeed(float);
  int			getRange()const;
  void			setRange(int);
  void			setScore(int);
  int			getScore()const;
  std::string		getName()const;
  char			getT()const;
  std::string		getData()const;
};

#endif			/* CHARACTER_HH_ */
