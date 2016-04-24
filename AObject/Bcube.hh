// Started by Kevin Fandi
// Last update by Kevin Fandi
//


#ifndef		BCUBE_HH_
# define	BCUBE_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		Bcube : public AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;

public:

  Bcube();
  Bcube(int x, int y, int z);
  virtual	~Bcube();
  bool		initialize(std::string);
  virtual bool	initialize();
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  glm::vec3	getPos()const;
  void		createGeometry();
  char		getT()const;
  std::string	getData()const;

};

#endif		/* BCUBE_HH_ */
