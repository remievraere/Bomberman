// Started by Remi Evraere
// Last update by Simon Bulcke
//

#include	"Number.hh"

Number::Number()
{
  _alpha.push_back(glm::vec2(1, 13));
  _alpha.push_back(glm::vec2(2, 13));
  _alpha.push_back(glm::vec2(3, 13));
  _alpha.push_back(glm::vec2(4, 13));
  _alpha.push_back(glm::vec2(5, 13));
  _alpha.push_back(glm::vec2(6, 13));
  _alpha.push_back(glm::vec2(7, 13));
  _alpha.push_back(glm::vec2(8, 13));
  _alpha.push_back(glm::vec2(9, 13));
  _alpha.push_back(glm::vec2(10, 13));
  _alpha.push_back(glm::vec2(14, 6));
}

Number::~Number()
{
}

bool		Number::initialize(int number, glm::vec3 pos, glm::vec3 scale, glm::vec4 color)
{
  if (_textAlpha.load("./Graphics/Alpha.tga") == false)
    {
      std::cerr << "Cannot load the alphabet" << std::endl;
      return (false);
    }
  _number = number;
  setPos(pos);
  _scale = scale.x;
  _color = color;
  setScale(scale);
  return (true);
}

gdl::Geometry	Number::setNumber(int c)
{
  gdl::Geometry	geo;
  float		i;

  i = 0.0625f;
  geo.setColor(_color);
  geo.pushVertex(glm::vec3(1, -1, 1));
  geo.pushVertex(glm::vec3(1, 1, 1));
  geo.pushVertex(glm::vec3(-1, 1, 1));
  geo.pushVertex(glm::vec3(-1, -1, 1));

  geo.pushUv(glm::vec2((_alpha[c].x - 1) * i, (_alpha[c].y - 1) * i));
  geo.pushUv(glm::vec2((_alpha[c].x - 1) * i, (_alpha[c].y) * i));
  geo.pushUv(glm::vec2((_alpha[c].x) * i, (_alpha[c].y) * i));
  geo.pushUv(glm::vec2((_alpha[c].x) * i, (_alpha[c].y - 1) * i));
  geo.build();
  return (geo);
}

void		Number::drawNumber(int nb, gdl::AShader &shader, gdl::Clock const &clock)
{
  int		tmp;

  tmp = nb % 10;
  nb = nb / 10;
  if (nb != 0)
    drawNumber(nb, shader, clock);
  setNumber(tmp).draw(shader, getTransformation(), GL_QUADS);
  translate(glm::vec3(-_scale * 1.4, 0, 0));
}

void		Number::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _textAlpha.bind();
  if (_number < 0)
    {
      setNumber(10).draw(shader, getTransformation(), GL_QUADS);
      translate(glm::vec3(-_scale * 1.25, 0, 0));
      _number *= -1;
    }
  drawNumber(_number, shader, clock);
}

glm::vec3	Number::getPos()const
{
  return (_position);
}

std::string	Number::getType()const
{
  return ("Number");
}

char		Number::getT()const
{
  return ('J');
}

std::string	Number::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z;
  return (data.str());
}
