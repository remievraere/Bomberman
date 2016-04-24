// Started by Medhi Kolai
// Last update by Clovis Masson
//

#include	"Plan.hh"

Plan::Plan()
{
}

Plan::~Plan()
{
}

bool		Plan::initialize(std::string path)
{
  if (_texture.load(path) == false)
    {
      std::cerr << "Bomberman : Cannot load the plan texture" << std::endl;
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

bool		Plan::initialize(std::string path, int width, int height)
{
  if (_texture.load(path) == false)
    {
      std::cerr << "Bomberman : Cannot load the plan texture" << std::endl;
      return (false);
    }
  width /= 27;
  height /= 27;
  _geometry.pushVertex(glm::vec3(width, -height, 0));
  _geometry.pushVertex(glm::vec3(width, height, 0));
  _geometry.pushVertex(glm::vec3(-width, height, 0));
  _geometry.pushVertex(glm::vec3(-width, -height, 0));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.build();
  _position.z += 5;
  return (true);
}

void		Plan::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

glm::vec3	Plan::getPos()const
{
  return (this->_position);
}

void		Plan::setColor(glm::vec4 color)
{
  _geometry.setColor(color);
}

std::string	Plan::getType()const
{
  return ("Plan");
}

char		Plan::getT()const
{
  return ('K');
}

std::string	Plan::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z;
  return (data.str());
}
