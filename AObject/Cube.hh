// Started by Clovis Masson
// Last update by Clovis Masson
//

#ifndef		CUBE_HH_
# define	CUBE_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Cube : public AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;

public:

  Cube();
  Cube(int x, int y, int z);
  virtual	~Cube();
  bool		initialize(std::string);
  virtual bool	initialize();
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  glm::vec3	getPos()const;
  char		getT()const;
  std::string	getData()const;
  void		createGeometry();

};

#endif		/* CUBE_HH_ */
