// Started by Remi Evraere
// Last update by Remi Evraere
//

#include	"Bonus.hh"

Bonus::Bonus()
{
}

Bonus::Bonus(float x, float z)
{
  _position.x = x;
  _position.y = 0;
  _position.z = z;
}

Bonus::Bonus(int x, int y, int z)
{
  _position.x = x;
  _position.y = y;
  _position.z = z;
}

Bonus::~Bonus()
{
}

glm::vec3	Bonus::getPos()const
{
  return (_position);
}

std::string	Bonus::getType()const
{
  return ("Bonus");
}

bool Bonus::initialize(Ebonus bonus)
{
  setScale(glm::vec3(0.5, 0.5, 0.5));
  _bonus = bonus;
  if (bonus == ADDBOMB)
    {
      if (_texture.load("./Graphics/Game/BonusA.tga") == false)
	{
	  std::cerr << "Cannot load the BonusA texture" << std::endl;
	  return (false);
	}
    }
  else if (bonus == SPEED)
    {
      if (_texture.load("./Graphics/Game/BonusS.tga") == false)
	{
	  std::cerr << "Cannot load the BonusS texture" << std::endl;
	  return (false);
	}
    }
  else
    if (_texture.load("./Graphics/Game/BonusP.tga") == false)
      {
	std::cerr << "Cannot load the BonusP texture" << std::endl;
	return (false);
      }
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
  return (true);
}

void		Bonus::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void		Bonus::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

Ebonus		Bonus::getBonus()const
{
  return (_bonus);
}

char		Bonus::getT()const
{
  return ('D');
}

std::string	Bonus::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z << "TYPE=";
  switch (_bonus)
    {
    case SPEED :
      {
	data << "SPEED";
	break;
      }
    case STRENGHT :
      {
	data << "STRENGHT";
	break;
      }
    case ADDBOMB :
      {
	data << "ADDBOMB";
	break;
      }
    }
  return (data.str());
}
