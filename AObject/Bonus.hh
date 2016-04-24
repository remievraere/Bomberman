// Started by Remi Evraere
// Last update by Remi Evraere
//


#ifndef		BONUS_HH_
# define	BONUS_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Bonus : public AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  Ebonus	_bonus;

public:

  Bonus();
  Bonus(float x, float z);
  Bonus(int x, int y, int z);
  virtual	~Bonus();
  bool		initialize(Ebonus);
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  glm::vec3	getPos()const;
  Ebonus	getBonus()const;
  char		getT()const;
  std::string	getData()const;

};

#endif		/* BONUS_HH_ */
