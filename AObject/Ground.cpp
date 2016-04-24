// Started by Medhi Kolai
// Last update by Medhi Kolai
//

#include "Ground.hh"

Ground::Ground()
{
}

Ground::Ground(int x, int y, int z)
{
  this->_position.x = x;
  this->_position.y = y;
  this->_position.z = z;
}

Ground::~Ground()
{
}

glm::vec3	Ground::getPos()const
{
  return (this->_position);
}

std::string	Ground::getType()const
{
  return("Ground");
}

bool Ground::initialize()
{
  if (_texture.load("./Graphics/Game/ThemeSpa/Ground.tga") == false)
    {
      std::cerr << "Cannot load the ground texture" << std::endl;
      return (false);
    }
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.build();
  return (true);
}

bool		Ground::initialize(std::string path)
{
  if (_texture.load(path) == false)
    {
      std::cerr << "Cannot load the ground " << path << " texture" << std::endl;
      return (false);
    }
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.build();
  return (true);
}

void		Ground::setColor(glm::vec4 color)
{
  _geometry.setColor(color);
}

void		Ground::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void		Ground::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

char		Ground::getT()const
{
  return ('H');
}

std::string	Ground::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z;
  return (data.str());
}
