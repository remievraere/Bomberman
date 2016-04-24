// Started by Simon Bulcke
// Last update by Simon Bulcke
//


#include	"SkyBox.hh"

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

glm::vec3	SkyBox::getPos()const
{
  return (this->_position);
}

std::string	SkyBox::getType()const
{
  return ("SkyBox");
}

bool		SkyBox::initialize(int size, glm::vec3 pos, std::string path)
{
  if (_texture.load(path) == false)
    {
      std::cerr << "Cannot load " << path << " texture" << std::endl;
      return (false);
    }
  _geometry.pushVertex(glm::vec3(1, -1, 1));
  _geometry.pushVertex(glm::vec3(1, 1, 1));
  _geometry.pushVertex(glm::vec3(-1, 1, 1));
  _geometry.pushVertex(glm::vec3(-1, -1, 1));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(1, -1, -1));
  _geometry.pushVertex(glm::vec3(1, 1, -1));
  _geometry.pushVertex(glm::vec3(-1, 1, -1));
  _geometry.pushVertex(glm::vec3(-1, -1, -1));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(1, -1, -1));
  _geometry.pushVertex(glm::vec3(1, 1, -1));
  _geometry.pushVertex(glm::vec3(1, 1, 1));
  _geometry.pushVertex(glm::vec3(1, -1, 1));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(-1, -1, 1));
  _geometry.pushVertex(glm::vec3(-1, 1, 1));
  _geometry.pushVertex(glm::vec3(-1, 1, -1));
  _geometry.pushVertex(glm::vec3(-1, -1, -1));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(1, 1, 1));
  _geometry.pushVertex(glm::vec3(1, 1, -1));
  _geometry.pushVertex(glm::vec3(-1, 1, -1));
  _geometry.pushVertex(glm::vec3(-1, 1, 1));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(1, -1, -1));
  _geometry.pushVertex(glm::vec3(1, -1, 1));
  _geometry.pushVertex(glm::vec3(-1, -1, 1));
  _geometry.pushVertex(glm::vec3(-1, -1, -1));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.build();
  scale(glm::vec3(size, size, size));
  translate(pos);
  return (true);
}

void		SkyBox::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

char		SkyBox::getT()const
{
  return ('L');
}

std::string	SkyBox::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z;
  return (data.str());
}
