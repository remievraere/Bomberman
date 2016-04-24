// Started by Clovis Masson
// Last update by Clovis Masson
//

#include	"Ia.hh"
#include	"Bomb.hh"

Ia::Ia()
{
}

Ia::Ia(int x, int y, int z, int id)
{
  setIa();
  _position.x = x;
  _position.y = y - 0.5;
  _position.z = z;
  _id = id;
  _bomb_id = 0;
  _dir = RIGHT;
}

Ia::Ia(float x, float y, int id, Direction dir, int allowed, int bid, int range, int lvl, int modea, int modeb, int ally, int time, float speed)
{
  _position.x = x;
  _position.y = 0;
  _position.z = y;
  _id = id;
  _dir = dir;
  _allowed_bomb = allowed;
  _bomb_id = bid;
  _range = range;
  _level = lvl;
  _aggressive = modea;
  _defensive = modeb;
  _ally = ally;
  _timer = time;
  _speed = speed;
}

Ia::~Ia()
{
}

glm::vec3	Ia::getPos()const
{
  return (_position);
}

std::string	Ia::getType()const
{
  return ("Ia");
}

void		Ia::setIa()
{
  std::fstream	file;
  std::string	line;
  std::string	tmp;
  int		pos;
  int		i;

  i = 0;
  try
    {
      file.open("ia.conf", std::fstream::in);
      while (file.good())
	{
	  std::getline(file, line);
	  switch(i)
	    {
	    case 3:
	      {
		if (line.compare(0, 16, "1 | ia_level -- ") == 0 && (line[16] - 48 > 0 && line[16] - 48 < 9))
		  _level = line[16] - 48;
		else
		  throw "Warning: AI's level must be between 1 and 8. Default : 5.";
		break;
	      }
	    case 4:
	      {
		if (line.compare(0, 20, "2 | ia_offensive -- ") == 0 && (line[20] - 48 >= 0 && line[20] - 48 <= 1))
		  _aggressive = line[20] - 48;
		else
		  throw "Warning: AI's reaction when not in danger should be either 1 or two. Default : 1.";
		break;
	      }
	    case 5:
	      {
		if (line.compare(0, 20, "3 | ia_defensive -- ") == 0 && (line[20] - 48 >= 0 && line[20] - 48 <= 1))
		  _defensive = line[20] - 48;
		else
		  throw "Warning: AI's reaction when in danger should be either 1 or two. Default : 1.";
		break;
	      }
	    case 6:
	      {
		float res;
		tmp = line.substr(16);
		std::istringstream(tmp) >> res;
		if (line.compare(0, 16, "4 | ia_speed -- ") == 0 && (res > 0.0 && res <= 15.0))
		  _speed = (float)res;
		else
		  throw "Warning: AI's speed must be positive and smaller than 15. Default : 5.";
		break;
	      }
	    case 7:
	      {
		if (line.compare(0, 16, "5 | ia_bonus -- ") == 0 && (line[16] - 48 >= 0 && line[16] - 48 <= 1))
		  _bonus = line[16] - 48;
		else
		  throw "Warning: AI's capacity of taking bonus should be either 1 or 0. Default : 0.";
		break;
	      }
	    case 8:
	      {
		int res;
		tmp = line.substr(15);
		std::istringstream(tmp) >> res;

		if (line.compare(0, 15, "6 | bomb_nb -- ") == 0 && (res >= 0 && res <= 30))
		  _allowed_bomb = res;
		else
		  throw "Warning: AI's bomb number must be positive and smaller than 30. Default : 1.";
		break;
	      }
	    case 9:
	      {
		if (line.compare(0, 15, "7 | ia_ally -- ") == 0 && (line[15] - 48 >= 0 && line[15] - 48 <= 1))
		  _ally = line[15] - 48;
		else
		  throw "Warning: AI's attitude with other AIs should be either 1 or 0. Default : 0.";
		break;
	      }
	    case 10:
	      {
		int res;
		tmp = line.substr(18);
		std::istringstream(tmp) >> res;

		if (line.compare(0, 18, "8 | bomb_range -- ") == 0 && (res > 0 && res <= 50))
		  _range = res;
		else
		  throw "Warning: Bomb's range must be positive and smaller than 50. Default : 2.";
		break;
	      }
	    case 11:
	      {
		int res;
		tmp = line.substr(17);
		std::istringstream(tmp) >> res;

		if (line.compare(0, 17, "9 | bomb_time -- ") == 0 && (res > 0 && res <= 50))
		  _timer = res;
		else
		  throw "Warning: Bomb's timer must be positive and smaller than 50. Default : 3.";
		break;
	      }
	    }
	  i++;
	}
      file.close();
    }
  catch (std::ifstream::failure e)
    {
      std::cerr << "Bomberman : Exception " << e.what() << std::endl;
    }
  catch (const char *str)
    {
      this->_level = 5;
      this->_aggressive = 1;
      this->_defensive = 1;
      this->_speed = 5;
      this->_bonus = 0;
      this->_allowed_bomb = 1;
      this->_ally = 0;
      this->_timer = 3;
      this->_range = 2;
      std::cerr << str << std::endl;
    }
}

bool		Ia::initialize(std::string path, glm::vec3 size)
{
  scale(size);
  // _speed = 10.0f;
  setRotation(glm::vec3(0, 1, 0), 270);
  if (_model.load(path) == false)
    return (false);
  //  std::cout << "Anim nb = " << _model.getAnimationFrameNumber(0) << std::endl;
  //  if (_model.createSubAnmin(0, "run", 0, 242)
  /*  if (_model.setCurrentAnim(0, true) == false)
      return (false);*/
  return (true);
}

bool		Ia::initialize()
{
  glm::vec3	size;

  size.x = 0.5;
  size.y = 0.5;
  size.z = 0.5;
  scale(size);
  // _speed = 10.0f;
  setRotation(glm::vec3(0, 1, 0), 270);
  if (_model.load("./Graphics/Game/Models/ia_zombie/Lambent_Male.obj") == false)
    return (false);
  //  std::cout << "Anim nb = " << _model.getAnimationFrameNumber(0) << std::endl;
  //  if (_model.createSubAnmin(0, "run", 0, 242)
  /*  if (_model.setCurrentAnim(0, true) == false)
      return (false);*/
  return (true);
}

void		Ia::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
}

void		Ia::moveUp(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 0);
}

void		Ia::moveDown(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 180);
}

void		Ia::moveLeft(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 90);
}

void		Ia::moveRight(gdl::Clock const &clock, gdl::Input &input)
{
  translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  setRotation(glm::vec3(0, 1, 0), 270);
}

void		Ia::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, this->getTransformation(), clock.getElapsed());
}

int		Ia::getId()const
{
  return (_id);
}

Direction	Ia::getDirection()const
{
  return (_dir);
}

int		Ia::getAllowed()const
{
  return (this->_allowed_bomb);
}

int		Ia::getBombsList()const
{
  return (this->_bombs.size());
}

void		Ia::pushBomb(Bomb *bomb)
{
  this->_bombs.push_back(bomb);
}

void		Ia::setDirection(Direction dir)
{
  _dir = dir;
}

int		Ia::getLevel()const
{
  return (_level);
}

int		Ia::getBombId()const
{
  return (this->_bomb_id);
}

void		Ia::setBombId(int bomb)
{
  this->_bomb_id = bomb;
}

void		Ia::seekBomb(int id)
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

int		Ia::getDefense()const
{
  return (this->_defensive);
}

int		Ia::getOffense()const
{
  return (this->_aggressive);
}

int		Ia::getRange()const
{
  return (_range);
}

int		Ia::getAlly()const
{
  return (_ally);
}

char		Ia::getT()const
{
  return ('I');
}

std::string	Ia::getData()const
{
  std::ostringstream	data;
  data << "X=" << _position.x << "Z=" << _position.z << "ID=" << _id << "ALLOWED=" << _allowed_bomb << "DIR=";
  switch (_dir)
    {
    case RIGHT :
      {
	data << "RIGHT";
	break;
      }
    case LEFT :
      {
	data << "LEFT";
	break;
      }
    case UP :
      {
	data << "UP";
	break;
      }
    case DOWN :
      {
	data << "DOWN";
	break;
      }
    }
  data << "BID=" << _bomb_id << "RANGE=" << _range << "LVL=" << _level << "MODEA=" << _aggressive << "MODEB=" << _defensive << "BONUS=" << _bonus << "ALLY=" << _ally << "TIME=" << _timer << "SPEED=" << _speed;
  return (data.str());
}

void		Ia::setLevel(int t)
{
  _level = t;
}

void		Ia::setOffense(int t)
{
  _aggressive = t;
}

void		Ia::setDefense(int t)
{
  _defensive = t;
}

void		Ia::setSpeed(float t)
{
  _speed = t;
}

void		Ia::setBonus(int t)
{
  _bonus = t;
}

void		Ia::setAllowed(int t)
{
  _allowed_bomb = t;
}

void		Ia::setAlly(int t)
{
  _ally = t;
}

void		Ia::setRange(int t)
{
  _range = t;
}

void		Ia::setTimer(int t)
{
  _timer = t;
}
