// Started by Remi Evraere
// Last update by Simon Bulcke
//

#ifndef		NUMBER_HH_
# define	NUMBER_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Number : public AObject
{
private:

  gdl::Texture	_textAlpha;
  gdl::Geometry	_geometry;
  int		_number;
  std::vector<glm::vec2>	_alpha;
  int				_scale;
  glm::vec4			_color;

public:

  Number();
  virtual	~Number();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  bool		initialize(int number, glm::vec3 pos, glm::vec3 scale, glm::vec4 color);
  std::string	getType()const;
  glm::vec3	getPos()const;
  gdl::Geometry	setNumber(int);
  void		drawNumber(int nb, gdl::AShader &shader, gdl::Clock const &clock);
  char		getT()const;
  std::string	getData()const;

};

#endif		/* NUMBER_HH_ */
