// Started by Simon Bulcke
// Last update by Simon Bulcke
//

#ifndef				ALPHA_HH_
# define			ALPHA_HH_

# include			"../Bomberman.hh"
# include			"../AObject.hh"

class Alpha : public AObject
{
private:

  gdl::Texture			_textAlpha;
  gdl::Geometry			_geometry;
  std::string			_string;
  std::vector<glm::vec2>	_alpha;
  int				_scale;
  glm::vec4			_color;

public:

  Alpha();
  virtual			~Alpha();
  virtual void			draw(gdl::AShader&, gdl::Clock const&);
  bool				initialize(std::string, glm::vec3, glm::vec3, glm::vec4);
  std::string			getType()const;
  glm::vec3			getPos()const;
  gdl::Geometry			setChar(char);
  char				getT()const;
  std::string			getData()const;

};

#endif		/* ALPHA_HH */
