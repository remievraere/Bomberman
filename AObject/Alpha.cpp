// Started by Simon Bulcke
// Last update by Simon Bulcke
//


#include	"Alpha.hh"

Alpha::Alpha()
{
  int	i;
  int	x;
  int	y;

  i = 0;
  y = 16;
  while (i < 251)
    {
      x = 1;
      while (x < 17)
	{
	  _alpha.push_back(glm::vec2(x++, y));
	  i++;
	}
      y--;
    }
}

Alpha::~Alpha()
{
}

bool		Alpha::initialize(std::string string, glm::vec3 pos, glm::vec3 scale, glm::vec4 color)
{
  if (_textAlpha.load("./Graphics/Alpha.tga") == false)
    {
      std::cerr << "Cannot load the alphabet" << std::endl;
      return (false);
    }
  _string = string;
  setPos(pos);
  _scale = scale.x;
  _color = color;
  setScale(scale);
  return (true);
}

gdl::Geometry		Alpha::setChar(char c)
{
  gdl::Geometry		geo;
  float			i;

  i = 0.0625f;
  geo.setColor(_color);
  geo.pushVertex(glm::vec3(1, -1, 1));
  geo.pushVertex(glm::vec3(1, 1, 1));
  geo.pushVertex(glm::vec3(-1, 1, 1));
  geo.pushVertex(glm::vec3(-1, -1, 1));
  geo.pushUv(glm::vec2((_alpha[c].x - 1) * i, (_alpha[c].y - 1) * i));
  geo.pushUv(glm::vec2((_alpha[c].x - 1) * i, _alpha[c].y * i));
  geo.pushUv(glm::vec2(_alpha[c].x * i, _alpha[c].y * i));
  geo.pushUv(glm::vec2(_alpha[c].x * i, (_alpha[c].y - 1) * i));
  geo.build();
  return (geo);
}

void		Alpha::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  int		i;

  (void)clock;
  i = 0;
  _textAlpha.bind();
  while (i < _string.length())
    {
      setChar(_string.at(i)).draw(shader, getTransformation(), GL_QUADS);
      translate(glm::vec3(-_scale * 1.5, 0, 0));
      i++;
    }
}

glm::vec3	Alpha::getPos()const
{
  return (_position);
}

std::string	Alpha::getType()const
{
  return ("Alpha");
}

char		Alpha::getT()const
{
  return ('A');
}

std::string	Alpha::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z;
  return (data.str());
}
