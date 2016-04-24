// Started by Simon Bulcke
// Last update by Simon Bulcke
//

#ifndef		SKYBOX_HH_
# define	SKYBOX_HH_

# include	"../Bomberman.hh"
# include	"../AObject.hh"

class		SkyBox : public	AObject
{
private:

  gdl::Texture	_texture;
  gdl::Geometry	_geometry;

public:

  SkyBox();
  virtual	~SkyBox();
  bool		initialize(int size, glm::vec3 pos, std::string path);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  std::string	getType()const;
  glm::vec3	getPos()const;
  char		getT()const;
  std::string	getData()const;

};

#endif		/* SKYBOX_HH_ */
