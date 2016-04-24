// Started by Medhi Kolai
// Last update by Medhi Kolai
//

#ifndef		GROUND_HH_
# define	GROUND_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Ground : public AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;

public:

  Ground();
  Ground(int, int, int);
  virtual	~Ground();
  bool		initialize(std::string);
  virtual bool	initialize();
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  glm::vec3	getPos()const;
  void		setColor(glm::vec4);
  char		getT()const;
  std::string	getData()const;

};

#endif		/* GROUND_HH_ */
