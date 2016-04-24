// Started by Medhi Kolai
// Last update by Medhi Kolai
//

#ifndef		ECUBE_HH_
# define	ECUBE_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		ECube : public AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  float		_time;
  bool		_explode;
  int           _idchar;

public:

  ECube();
  ECube(int x, int y, int z, int);
  ECube(float, float, float, bool, int);
  virtual	~ECube();
  bool		initialize(std::string);
  virtual bool	initialize();
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  glm::vec3	getPos()const;
  void		setTime(float);
  float		getTime()const;
  bool		getExplode()const;
  int           getId()const;
  char		getT()const;
  std::string	getData()const;
  void		createGeometry();
};

#endif		/* ECUBE_HH_ */
