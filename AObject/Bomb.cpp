// Started by Clovis Masson
// Last update by Clovis Masson
//


#include	"Bomb.hh"

Bomb::Bomb(int id, int range, int bomb_id)
{
  _position.y = -0.5;
  _id = id;
  _range = range;
  _time = 0;
  _explode = false;
  _bomb_id = bomb_id;
}

Bomb::Bomb(float x, float z, float time, int id, int range, bool explo, int bid)
{
  _position.x = x;
  _position.y = -0.5;
  _position.z = z;
  _time = time;
  _id = id;
  _range = range;
  _explode = explo;
  _bomb_id = bid;
}

Bomb::Bomb(glm::vec3 t)
{
  _position.x = t.x;
  _position.y = t.y;
  _position.z = t.z;
}

Bomb::~Bomb()
{
}

int		Bomb::getBombId()const
{
  return (_bomb_id);
}

glm::vec3	Bomb::getPos()const
{
  return (_position);
}

std::string	Bomb::getType()const
{
  return ("Bomb");
}

bool		Bomb::initialize()
{
  glm::vec3	size;

  size.x = 0.4;
  size.y = 0.4;
  size.z = 0.4;
  scale(size);
  setRotation(glm::vec3(0, 1, 0), 270);
  if (_model.load("./Graphics/Game/Models/Bomb/bomb.fbx") == false)
    return (false);
  return (true);
}

void		Bomb::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
  _time += static_cast<float>(clock.getElapsed());
  if (_time > 3)
    this->_explode = true;
}

void		Bomb::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}

float		Bomb::getTime()const
{
  return (_time);
}

void		Bomb::setTime(float time)
{
  _time = time;
}

int		Bomb::getRange()const
{
  return (this->_range);
}

void		Bomb::setRange(int range)
{
  _range += range;
}

bool		Bomb::getExplode()const
{
  return (this->_explode);
}

int		Bomb::getId()const
{
  return (this->_id);
}

char		Bomb::getT()const
{
  return ('C');
}

std::string	Bomb::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z << "TIME=" << _time << "ID=" << _id << "RANGE=" << _range << "EXPLO=";
  if (_explode == true)
    data << "true";
  else
    data << "false";
  data << "BID=" << _bomb_id;
  return (data.str());
}
