// Started by Remi Evraere
// Last update by Simon Bulcke
//

#include		"TexAni.hh"

TexAni::TexAni()
{
}

TexAni::TexAni(int x, int y, int z)
{
  this->_position.x = x;
  this->_position.y = y;
  this->_position.z = z;
  this->_time = 0;
  this->_explode = false;
}

TexAni::~TexAni()
{
}

glm::vec3		TexAni::getPos()const
{
  return (this->_position);
}

std::string		TexAni::getType()const
{
  return ("TexAni");
}

bool			TexAni::initialize()
{
  if (_texture.load("./Graphics/Menu/Anim/Anim2.tga") == false)
    {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.build();
  return (true);
}

void			TexAni::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
  _time += static_cast<float>(clock.getElapsed());
  if (_time > 1)
    this->_explode = true;
}

void			TexAni::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

void			TexAni::setTime(float time)
{
  _time = time;
}

float			TexAni::getTime()const
{
  return (_time);
}

bool			TexAni::getExplode()const
{
  return (_explode);
}

char		TexAni::getT()const
{
  return ('F');
}

std::string	TexAni::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z;
  return (data.str());
}
