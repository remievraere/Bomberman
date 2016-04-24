// Started by Medhi Kolai
// Last update by Clovis Masson
//


#ifndef		PLAN_HH_
# define	PLAN_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Plan : public AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;

public:

  Plan();
  virtual	~Plan();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  bool		initialize(std::string path);
  bool		initialize(std::string path, int width, int height);
  std::string	getType()const;
  glm::vec3	getPos()const;
  void		setColor(glm::vec4 color);
  char		getT()const;
  std::string	getData()const;

};

#endif		/* PLAN_HH_ */
