// Started by Medhi Kolai
// Last update by Medhi Kolai
//

#include	"ECube.hh"

ECube::ECube()
{
}

ECube::ECube(float x, float z, float time, bool explo, int id)
{
  _position.x = x;
  _position.y = 0;
  _position.z = z;
  _time = time;
  _explode = explo;
  _idchar = id;
}

ECube::ECube(int x, int y, int z, int id)
{
  _position.x = x;
  _position.y = y;
  _position.z = z;
  _time = 0;
  _explode = false;
  _idchar = id;
}

ECube::~ECube()
{
}

glm::vec3	ECube::getPos()const
{
  return (this->_position);
}

std::string	ECube::getType()const
{
  return ("ECube");
}

void		ECube::createGeometry()
{
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.build();
}

bool		ECube::initialize()
{
  if (_texture.load("./Graphics/Game/ThemeSpa/Lava.tga") == false)
    {
      std::cerr << "Cannot load the Ecube texture" << std::endl;
      return (false);
    }
  createGeometry();
  return (true);
}

bool		ECube::initialize(std::string path)
{
  if (_texture.load(path) == false)
    {
      std::cerr << "Cannot load the Ecube " << path << " texture" << std::endl;
      return (false);
    }
  createGeometry();
  return (true);
}

void		ECube::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
  _time += static_cast<float>(clock.getElapsed());
  if (_time > 1)
    _explode = true;
}

void		ECube::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

void		ECube::setTime(float time)
{
  _time = time;
}

float		ECube::getTime()const
{
  return (_time);
}

bool		ECube::getExplode()const
{
  return (this->_explode);
}

int		ECube::getId()const
{
  return (this->_idchar);
}

char		ECube::getT()const
{
  return ('G');
}

std::string	ECube::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z << "TIME=" << _time << "EXPLO=";
  if (_explode == false)
    data << "false";
  else
    data << "true";
  data << "ID=" << _idchar;
  return (data.str());
}
