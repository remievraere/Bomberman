// Started by Remi Evraere
// Last update by Simon Bulcke
//


#include	"Character.hh"
#include	"Bomb.hh"

Character::Character()
{
}

Character::Character(int x, int y, int z, int id, std::string name)
{
  _speed = 5.0f;
  _position.x = x;
  _position.y = y;
  _position.z = z;
  _id = id;
  _allowed_bomb = 1;
  _bomb_id = 0;
  _range = 2;
  _dir = UP;
  _name = name;
  _score = 0;
}

Character::Character(float x, float z, Direction dir, float s, int id, int nb, int id_bomb, int range, std::string name, int score)
{
  _position.x = x;
  _position.y = 0;
  _position.z = z;
  _dir = dir;
  if (s > 10)
    _speed = 10;
  else
    _speed = s;
  _id = id;
  _allowed_bomb = nb;
  _bomb_id = id_bomb;
  _range = range;
  _name = name;
  _score = score;
}

Character::~Character()
{
}

glm::vec3	Character::getPos() const
{
  return (_position);
}

std::string	Character::getType()const
{
  return ("Character");
}

void		Character::seekBomb(int id)
{
  int		i;

  i = 0;
  while (i < _bombs.size())
    {
      if (_bombs[i]->getBombId() == id)
        _bombs.erase(_bombs.begin() + i);
      i++;
    }
}

bool		Character::initialize()
{
  glm::vec3	size;

  size.x = 0.003;
  size.y = 0.003;
  size.z = 0.003;
  scale(size);
  if (_model.load("./Graphics/Game/Models/marvin.fbx") == false)
    return (false);
  if (_model.createSubAnim(0, "run", 30, 55) == false)
    return (false);
  if (_model.setCurrentSubAnim("run", true) == false)
    return (false);
  return (true);
}

void		Character::moveUp(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 0);
  _dir = UP;
}

void		Character::moveDown(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 180);
  _dir = DOWN;
}

void		Character::moveLeft(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 90);
  _dir = LEFT;
}

void		Character::moveRight(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 270);
  _dir = RIGHT;
}

void		Character::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void		Character::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}

int		Character::getId()const
{
  return (_id);
}

Direction	Character::getDirection()const
{
  return (_dir);
}

int		Character::getAllowed()const
{
  return (this->_allowed_bomb);
}

int		Character::getBombsList()const
{
  return (this->_bombs.size());
}

void		Character::pushBomb(Bomb *bomb)
{
  this->_bombs.push_back(bomb);
}

int		Character::getBombId()const
{
  return (this->_bomb_id);
}

void		Character::setBombId(int bomb)
{
  this->_bomb_id = bomb;
}

void		Character::setAllowedBomb(int allowed)
{
  _allowed_bomb += allowed;
  if (_allowed_bomb > 10)
    _allowed_bomb = 10;
}

void		Character::setSpeed(float speed)
{
  if (speed > 10)
    _speed = 10;
  else
    _speed += speed;
  if( _speed > 15)
    _speed = 15;

}

int		Character::getRange()const
{
  return (_range);
}

void		Character::setRange(int range)
{
  _range += range;
  if (_range > 20)
    _range = 20;
}

void            Character::setScore(int score)
{
  _score += score;
}

int             Character::getScore()const
{
  return (_score);
}

std::string     Character::getName()const
{
  return (_name);
}

char		Character::getT()const
{
  return ('E');
}

std::string	Character::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z << "ID=" << _id << "DIR=";
  switch (_dir)
    {
    case DOWN :
      {
	data << "DOWN";
	break;
      }
    case UP :
      {
	data << "UP";
	break;
      }
    case LEFT :
      {
	data << "LEFT";
	break;
      }
    case RIGHT :
      {
	data << "RIGHT";
	break;
      }
    }
  data << "S=" << _speed << "NB=" << _allowed_bomb << "BID=" << _bomb_id << "RANGE=" << _range << "NAME=" << _name << "SCORE=" << _score;
  return (data.str());
}
