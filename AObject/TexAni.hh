// Started by Remi Evraere
// Last update by Simon Bulcke
//


#ifndef		TEXANI_HH_
# define	TEXANI_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		TexAni : public AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;
  float		_time;
  bool		_explode;
public:

  TexAni();
  TexAni(int x, int y, int z);
  virtual	~TexAni();
  virtual bool	initialize();
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  glm::vec3	getPos() const;
  void		setTime(float);
  float		getTime()const;
  bool		getExplode()const;
  char		getT()const;
  std::string	getData()const;

};

#endif		/* TEXANI_HH_ */
