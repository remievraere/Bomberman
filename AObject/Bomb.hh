// Started by Clovis Masson
// Last update by Clovis Masson
//

#ifndef		BOMB_HH_
# define	BOMB_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Bomb : public AObject
{
private:

  gdl::Model	_model;
  float		_time;
  int		_id;
  int		_range;
  bool		_explode;
  int		_bomb_id;

public:

  Bomb(float, float, float, int, int, bool, int);
  Bomb(int, int, int);
  Bomb(glm::vec3);
  virtual	~Bomb();
  virtual bool	initialize();
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  int		getRange()const;
  void		setRange(int);
  int		getBombId()const;
  int		getId()const;
  float		getTime()const;
  void		setTime(float);
  bool		getExplode()const;
  glm::vec3	getPos() const;
  char		getT()const;
  std::string	getData()const;

};

#endif		/* BOMB_HH_ */
