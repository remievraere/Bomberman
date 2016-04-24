// Started by Simon Bulcke
// Last update by Remi Evraere
//


#include		"Map.hh"

Map::Map(int x, int y, int density_cube, int density_bcube, int nb_player, int nb_ia,
	 std::string fpname, std::string spname, std::string cube,
	 std::string box, std::string bcube, std::string ground)
{
  int			i;
  int			j;
  int			loaded;
  int			dens_mod = 0;

  _mode = FREE;
  _skybox = new SkyBox();
  _danger = new Danger();
  _fpname = fpname;
  _spname = spname;
  _pathground = ground;
  _nbElem = 0;
  _id = 0;
  _x = x;
  _y = y;
  i = 0;
  loaded = 0;
  srand(time(0));
  try
    {
      if (((SkyBox*)_skybox)->initialize(100, glm::vec3(0,0,0), box) ==false)
	throw "Bomberman : Cannot load SkyBox";
      while (i < x)
	{
	  j = 0;
	  while (j < y)
	    {
	      if ((j == 1 && (i > 0 && i < x - 1)) || j == y - 2 && (i > 0 && i < x - 1));
	      else if ((i == 1 && (j > 0 && j < y - 1)) || i == x - 2 && (j > 0 && j < y - 1));
	      else if ((j == 0 || j == y - 1) || (i == 0 || i == x - 1))
		{
		  _Elem.push_back(new Cube(-i, 0, -j));
		  if (static_cast<Cube*>(_Elem[_nbElem++])->initialize(cube) == false)
		    throw "Bomberman: Cube init fail";
		}
	      else if (dens_mod % 2 == 0)
		{
		  if (density_bcube > (rand() % 10) + 1)
		    {
		      if (getElem(-i, -j) == NULL)
			{
			  _Elem.push_back(new Bcube(-i, 0, -j));
			  if (static_cast<Bcube*>(_Elem[_nbElem++])->initialize(bcube) == false)
			    throw "Bomberman: Cube init fail";
			}
		    }
		  else if (density_cube > (rand() % 10) + 1)
		    {
		      if (getElem(-i, -j) == NULL)
			{
			  _Elem.push_back(new Cube(-i, 0, -j));
			  if (static_cast<Cube*>(_Elem[_nbElem++])->initialize(cube) == false)
			    throw "Bomberman: Cube init fail";
			}
		    }
		}
	      else
		{
		  if (density_cube > (rand() % 10) + 1)
		    {
		      if (getElem(-i, -j) == NULL)
			{
			  _Elem.push_back(new Cube(-i, 0, -j));
			  if (static_cast<Cube*>(_Elem[_nbElem++])->initialize(cube) == false)
			    throw "Bomberman: Cube init fail";
			}
		    }
		  else if (density_bcube > (rand() % 10) + 1)
		    {
		      if (getElem(-i, -j) == NULL)
			{
			  _Elem.push_back(new Bcube(-i, 0, -j));
			  if (static_cast<Bcube*>(_Elem[_nbElem++])->initialize(cube) == false)
			    throw "Bomberman: Cube init fail";
			}
		    }
		}
	      j++;
	    }
	  i++;
	  j = loaded;
	  loaded = (int)(((double)i/(double)_x) * 100.0);
	  if (j != loaded)
	    std::cout << "Loading : " << loaded << "%..." << std::endl;
	}
      if (nb_player > 0)
	if (!addPlayers(nb_player, nb_ia))
	  throw "Bomberman : Cannot add Player";
    }
  catch (const char *str)
    {
      _Elem.clear();
      _x = -1;
      _y = -1;
      std::cerr << str << std::endl;
    }
}

Map::Map(std::string path, int nb_player, int nb_ia, std::string fpname,
	 std::string spname, std::string cube, std::string box,
	 std::string bcube, std::string ground)
{
  std::fstream		file;
  std::string		line;
  int			max_x;
  int			map_x;
  int			map_y;
  int			fail;

  fail = 0;
  _mode = FREE;
  _danger = new Danger();
  _skybox = new SkyBox();
  this->_fpname = fpname;
  this->_spname = spname;
  _pathground = ground;
  _nbElem = 0;
  _id = 0;
  initAllowedCharInMap();
  max_x = -1;
  map_y = 0;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try
    {
      if (((SkyBox*)_skybox)->initialize(100, glm::vec3(0,0,0), box) ==false)
	throw "Bomberman : Cannot load SkyBox";
      if (checkMap(path) == false)
	throw "Bomberman : Invalid map";
      file.open(path.c_str(), std::fstream::in);
      while (file.good())
	{
	  map_x = 0;
	  std::getline(file, line);
	  if (fail > 0)
	    throw "Bomberman : Invalid map";
	  if (max_x == -1)
	    {
	      _x = line.length();
	      max_x = line.length();
	    }
	  else if (max_x != line.length() || line.length() < 1 || line.at(line.length()-1) != '1' && line.at(0) != '1')
	    throw "Bomberman : Invalid map";
	  while (map_x < line.length())
	    {
	      if (!checkChar(line.at(map_x)))
		throw "Bomberman : Invalid map : Unknow element";
	      switch (line.at(map_x))
		{
		case '1' :
		  {
		    if (map_y == 1 && map_x != (_x - 1) && map_x != 0)
		      fail++;
		    if (map_y == _y - 2 && (map_x != (_x - 1) && map_x != 0))
		      fail++;
		    else if (map_y > 0 && (map_x == (_x - 2) || map_x == 1))
		      fail++;
		    _Elem.push_back(new Cube(-map_x, 0, -map_y));
		    if (static_cast<Cube*>(_Elem[_nbElem++])->initialize(cube) == false)
		      throw "Bomberman : Cube init fail";
		    break;
		  }
		case '2' :
		  {
		    if (map_y == 1 && map_x != (_x - 1) && map_x != 0)
		      fail++;
		    if (map_y > 0 && (map_x == (_x - 2) || map_x == 1))
		      fail++;
		    _Elem.push_back(new Bcube(-map_x, 0, -map_y));
		    if (static_cast<Bcube*>(_Elem[_nbElem++])->initialize(bcube) == false)
		      throw "Bomberman : Bcube init fail";
		    break;
		  }
		}
	      map_x++;
	    }
	  map_y++;
	}
      _y = map_y;
      if (nb_player > 0)
	if (!addPlayers(nb_player, nb_ia))
	  throw "Bomberman : Cannot add Player";
      file.close();
    }
  catch (std::ifstream::failure e)
    {
      _Elem.clear();
      _x = -1;
      _y = -1;
      std::cerr << "Bomberman : Exception " << e.what() << std::endl;
    }
  catch (const char *str)
    {
      _Elem.clear();
      _x = -1;
      _y = -1;
      std::cerr << str << std::endl;
    }
}

Map::Map(std::string path)
{
  std::fstream	file;
  std::string	line;
  int		nbLine;
  char		c;
  int		x;
  int		y;
  int		fail;

  _danger = new Danger();
  _skybox = new SkyBox();
  _pathground = "./Graphics/Game/ThemeSpa/Ground.tga";
  initAllowedCharInMap();
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  nbLine = 0;
  _x = -1;
  _y = -1;
  _nbElem = 0;
  try
    {
      if (((SkyBox*)_skybox)->initialize(100, glm::vec3(0,0,0), "./Graphics/Game/ThemeSpa/SkyBox.tga") == false)
	throw "Bomberman : Cannot load SkyBox";
      file.open(path.c_str(), std::fstream::in);
      while (file.good())
	{
	  std::getline(file, line);
	  switch (nbLine)
	    {
	    case 0 :
	      {
		std::istringstream(line) >> _x;
		break;
	      }
	    case 1 :
	      {
		std::istringstream(line) >> _y;
		break;
	      }
	    case 2 :
	      {
		if (line.at(0) != 'S' && line.at(0) != 'F' && line.at(0) != 'A' && _Elem.size() == 0)
		  {
		    y = 0;
		    fail = 0;
		    while (y < _y)
		      {
			if (y > 0)
			  std::getline(file, line);
			if (fail > 0)
			  throw "Bomberman : Invalid map";
			x = 0;
			if (_x != line.length())
			  throw "Bomberman : Invalid map 1";
			while (x < _x)
			  {
			    if (!checkChar(line.at(x)))
			      throw "Bomberman : Invalid map : Unknow element";
			    switch (line.at(x))
			      {
			      case '1' :
				{
				  if (y == 1 && x != (_x - 1) && x != 0)
				    fail++;
				  if (y == (_y - 2) && (x != (_x - 1) && x != 0))
				    fail++;
				  if (y > 0 && (x == (_x - 2) || x == 1))
				    fail++;
				  _Elem.push_back(new Cube(-x, 0, -y));
				  if (_Elem[_nbElem++]->initialize() == false)
				    throw "Bomberman : Cube init fail";
				  break;
				}
			      case '2' :
				{
				  if (y == 1 && x != (_x - 1) && x != 0)
				    fail++;
				  if (y > 0 && (x == (_x - 2) || x == 1))
				    fail++;
				  _Elem.push_back(new Bcube(-x, 0, -y));
				  if (_Elem[_nbElem++]->initialize() == false)
				    throw "Bomberman : Bcube init fail";
				  break;
				}
			      }
			    x++;
			  }
			y++;
		      }
		  }
		break;
	      }
	    default :
	      {
		switch (line.at(0))
		  {
		  case 'G' ://ECube
		    {
		      if (parseECube(line) == false)
			throw "Bomberman : Invalid ECube savefile";
		      break;
		    }
		  case 'C' ://Bomb
		    {
		      if (parseBomb(line) == false)
			throw "Bomberman : Invalid Bomb savefile";
		      break;
		    }
		  case 'I' ://Ia
		    {
		      if (parseIa(line) == false)
			throw "Bomberman : Invalid Ia savefile";
		      break;
		    }
		  case 'E' ://Character
		    {
		      if (parseCharacter(line) == false)
			throw "Bomberman : Invalid Character savefile";
		      break;
		    }
		  case 'D' ://Bonus
		    {
		      if (parseBonus(line) == false)
			throw "Bomberman : Invalid Bonus savefile";
		      break;
		    }
		  default :
		    throw "Bomberman : Invalid savefile unknow elem";
		  }
	      }
	    }
	  nbLine++;
	}
      if (fillBombToPlayers() == false)
	throw "Bomberman : Invalid savefile";
      std::cout << "X = " << _x << std::endl;
      std::cout << "Y = " << _y << std::endl;
    }
  catch (std::ifstream::failure e)
    {
      _Elem.clear();
      _x = -1;
      _y = -1;
      std::cerr << "Bomberman : Exception " << e.what() << std::endl;
    }
  catch (const char *str)
    {
      _Elem.clear();
      _x = -1;
      _y = -1;
      std::cerr << str << std::endl;
    }
}

Map::~Map()
{
  size_t	i;

  i = 0;
  while (i < _Elem.size())
    delete _Elem[i++];
  _Elem.clear();
}

bool			Map::checkMap(std::string path)
{
  std::fstream		file;
  std::string		line;
  int			x;
  int			y;
  int			fail;

  fail = 0;
  y = 0;
  file.open(path.c_str(), std::fstream::in);
  while (file.good())
    {
      x = 0;
      std::getline(file, line);
      while (x < line.length())
	{
	  if (y == 0)
	    {
	      if (line.at(x) != '1' && x != line.length())
		fail++;
	    }
	  else if (y > 0)
	    {
	      if (line.at(0) != '1' || line.at(line.length() - 1) != '1')
		fail++;
	    }
	  x++;
	}
      y++;
    }
  x = 0;
  while (x < line.length())
    {
      if (line.at(x) != '1')
	fail++;
      x++;
    }
  _y = y;
  file.close();
  if (fail > 0)
    return (false);
  return (true);
}

bool			Map::isEmpty()
{
  if (!_Elem.empty())
    return (false);
  return (true);
}

void			Map::Print()
{
  int			i;

  i = 0;
  std::cout << "--------------------MAP---------------------" << std::endl;
  if (!_Elem.empty())
    {
      while (i < _Elem.size())
	{
	  if (_Elem[i]->getType() != "Ground" && _Elem[i]->getType() != "Cube" && _Elem[i]->getType() != "Bcube")
	    {
	      std::cout << "type = " << _Elem[i]->getType() << std::endl;
	      _Elem[i]->Print();
	    }
	  i++;
	}
    }
  else
    std::cout << "Bomberman : Map is empty" << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
}

void			Map::update(gdl::Clock clock, gdl::Input input)
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    _Elem[i++]->update(clock, input);
}

void			Map::draw(gdl::BasicShader shader,
				  gdl::Clock clock)
{
  AObject		*ground;
  int			i;
  int			j;
  int			angle;
  glm::vec3		pos;
  glm::vec3		posPlayer;

  _skybox->draw(shader, clock);
  angle = 0;
  ground = new Ground();
  if (static_cast<Ground*>(ground)->initialize(_pathground) == true)
    {
      shader.bind();
      posPlayer = getCharPos(_idDraw);
      i = posPlayer.x + 15;
      while (i > posPlayer.x - 15)
	{
	  angle = 15;
	  j = posPlayer.z + 15;
	  while (j > posPlayer.z - 5)
	    {
	      if (i < posPlayer.x + angle && i > posPlayer.x - angle)
		{
		  if (i < 0 && i > -_x && j < 0 && j > -_y)
		    {
		      ground->setPos(glm::vec3(i, -1, j));
		      ground->draw(shader, clock);
		    }
		}
	      if (j % 2 ==0)
		angle--;
	      j--;
	    }
	  i--;
	}
      delete ground;
      i = 0;
      while (i < _Elem.size())
	{
	  pos = _Elem[i]->getPos();
	  if ((pos.x < posPlayer.x + 15 && pos.x > posPlayer.x - 15) && (pos.z < posPlayer.z + 15 && pos.z > posPlayer.z - 5) && ((pos.x < posPlayer.x + 8 && pos.x > posPlayer.x - 8) || pos.z > posPlayer.z + 3))
	    _Elem[i]->draw(shader, clock);
	  i++;
	}
    }
}

void			Map::drawEdit(gdl::BasicShader shader,
				      gdl::Clock clock)
{
  Ground		*ground;
  int			i;
  int			j;
  int			angle;
  glm::vec3		pos;
  glm::vec3		posPlayer;

  _skybox->draw(shader, clock);
  angle = 0;
  ground = new Ground();
  if (static_cast<Ground*>(ground)->initialize("./Graphics/Game/ThemeSpa/Ground.tga") == true)
    {
      shader.bind();
      posPlayer = _posDraw;
      i = posPlayer.x + 15;
      while (i > posPlayer.x - 15)
	{
	  angle = 16;
	  j = posPlayer.z + 15;
	  while (j > posPlayer.z - 5)
	    {
	      if (i < posPlayer.x + angle && i > posPlayer.x - angle)
		{
		  if (i < 0 && i > -_x && j < 0 && j > -_y)
		    {
		      ground->setPos(glm::vec3(i, -1, j));
		      ground->draw(shader, clock);
		    }
		}
	      if (j % 2 ==0)
		angle--;
	      j--;
	    }
	  i--;
	}
      delete ground;
      i = 0;
      while (i < _Elem.size())
	{
	  pos = _Elem[i]->getPos();
	  if ((pos.x < posPlayer.x + 15 && pos.x > posPlayer.x - 15) && (pos.z < posPlayer.z + 15 && pos.z > posPlayer.z - 5) && ((pos.x < posPlayer.x + 8 && pos.x > posPlayer.x - 8) || pos.z > posPlayer.z + 3))
	    _Elem[i]->draw(shader, clock);
	  i++;
	}
    }
}

void			Map::drawDualScreen(gdl::BasicShader shader,
					    gdl::Clock clock)
{
  AObject		*ground;
  int			i;
  int			j;
  int			angle;
  glm::vec3		pos;
  glm::vec3		posPlayer;

  _skybox->draw(shader, clock);
  angle = 0;
  ground = new Ground();
  if (static_cast<Ground*>(ground)->initialize("./Graphics/Game/ThemeSpa/Ground.tga") == true)
    {
      shader.bind();
      posPlayer = getCharPos(_idDraw);
      i = posPlayer.x + 6;
      while (i > posPlayer.x - 7)
	{
	  angle = 9;
	  j = posPlayer.z + 14;
	  while (j > posPlayer.z - 7)
	    {
	      //	  if (getElem(i, j) == NULL)
	      // {
	      if (i < posPlayer.x + angle && i > posPlayer.x - angle)
		{
		  if (i < 0 && i > -_x && j < 0 && j > -_y)
		    {
		      ground->setPos(glm::vec3(i, -1, j));
		      ground->draw(shader, clock);
		    }
		}
	      //}
	      if (j % 3 == 0)
		angle--;
	      j--;
	    }
	  i--;
	}
      delete ground;
      i = 0;
      while (i < _Elem.size())
	{
	  pos = _Elem[i]->getPos();
	  if ((pos.x < posPlayer.x + 10 && pos.x > posPlayer.x - 10) && (pos.z < posPlayer.z + 15 && pos.z > posPlayer.z - 5) && ((pos.x < posPlayer.x + 8 && pos.x > posPlayer.x - 8) || pos.z > posPlayer.z + 3))
	    _Elem[i]->draw(shader, clock);
	  i++;
	}
    }
}

glm::vec3		Map::getCharPos(int id)
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character")
	{
	  if (((Character*)_Elem[i])->getId() == id)
	    return (_Elem[i]->getPos());
	}
      i++;
    }
  return (glm::vec3(-1, -1, -1));
}

int			Map::getElemSize()const
{
  return (_Elem.size());
}

AObject*		Map::getElem(int i)const
{
  return (_Elem[i]);
}

AObject*		Map::getElem(int x, int y)const
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getPosX() == x && _Elem[i]->getPosZ() == y && _Elem[i]->getType() != "Ground" && _Elem[i]->getType() != "Character")
	return (_Elem[i]);
      i++;
    }
  return (NULL);
}

bool			Map::checkChar(char c)const
{
  int			i;

  i = 0;
  while (i < _AllowedChar.size())
    {
      if (c == _AllowedChar[i])
	return (true);
      i++;
    }
  return (false);
}

void			Map::initAllowedCharInMap()
{
  _AllowedChar.push_back('1');
  _AllowedChar.push_back(' ');
  _AllowedChar.push_back('2');
}

int			Map::getCharId(int nb)const
{
  int			i;
  int			nbChar;

  nbChar = 0;
  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character")
	{
	  if (nbChar == nb)
	    return (((Character*)_Elem[i])->getId());
	  nbChar++;
	}
      i++;
    }
  return (-1);
}

int			Map::getIaSize()const
{
  int			i;
  int			count;

  count = 0;
  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Ia")
	count++;
      i++;
    }
  return (count);
}

Ia*			Map::getIaObj(int nb)const
{
  int			i;
  int			e;

  e = 0;
  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Ia")
	{
	  if (e == nb)
	    return ((Ia*)_Elem[i]);
	  e++;
	}
      i++;
    }
  return (NULL);
}

Character*		Map::getCharObj(int nb)const
{
  int			i;
  int			charpos;
  int			nbChar;

  nbChar = 0;
  charpos = -1;
  while (charpos == -1)
    {
      i = 0;
      while (i < _Elem.size())
	{
	  if (_Elem[i]->getType() == "Character")
	    {
	      if (nbChar == nb)
		charpos = i;
	      nbChar++;
	    }
	  i++;
	}
      if (charpos == -1)
	{
	  std::cout << "Bomberman : Le joueur a été transféré dans un";
	  std::cout << " espace spatio temporel encore inconnu a ce jour.";
	  std::cout << std::endl;
	  exit(-1);
	}
    }
  return ((Character*)_Elem[charpos]);
}

void			Map::setIdDraw(int id)
{
  _idDraw = id;
}

bool			Map::setCollision(glm::vec3 pos, int id,
					  Direction d)
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() != "Ground")
	{
	  switch (d)
	    {
	    case UP :
	      {
		if ((_Elem[i]->getPos().x - pos.x) < 0.5 &&
		    (_Elem[i]->getPos().x - pos.x) > -0.5 &&
		    (_Elem[i]->getPos().z > pos.z) &&
		    (_Elem[i]->getPos().z - 1) < pos.z &&
		    _Elem[i]->getType() != "Bonus" &&
		    _Elem[i]->getType() != "ECube")
		  return false;
		break;
	      }
	    case DOWN :
	      {
		if ((_Elem[i]->getPos().x - pos.x) < 0.5 &&
		    (_Elem[i]->getPos().x - pos.x) > -0.5 &&
		    (_Elem[i]->getPos().z < pos.z) &&
		    (_Elem[i]->getPos().z + 1) > pos.z &&
		    _Elem[i]->getType() != "Bonus" &&
		    _Elem[i]->getType() != "ECube")
		  return false;
		break;
	      }
	    case RIGHT :
	      {
		if ((_Elem[i]->getPos().z - pos.z) < 0.5 &&
		    (_Elem[i]->getPos().z - pos.z) > -0.5 &&
		    (_Elem[i]->getPos().x < pos.x) &&
		    (_Elem[i]->getPos().x + 1) > pos.x &&
		    _Elem[i]->getType() != "Bonus" &&
		    _Elem[i]->getType() != "ECube")
		  return false;
		break;
	      }
	    case LEFT :
	      {
		if ((_Elem[i]->getPos().z - pos.z) < 0.5 &&
		    (_Elem[i]->getPos().z - pos.z) > -0.5 &&
		    (_Elem[i]->getPos().x > pos.x) &&
		    (_Elem[i]->getPos().x - 1) < pos.x &&
		    _Elem[i]->getType() != "Bonus" &&
		    _Elem[i]->getType() != "ECube")
		  return false;
		break;
	      }
	    }
	}
      i++;
    }
  return true;
}

void			Map::setPosDraw(glm::vec3 pos)
{
  _posDraw = pos;
}

void			Map::save(std::vector<AObject*> Objects, std::string path)
{
  int			i;
  int			j;

  i = 0;
  j = 0;
  path = path.insert(0, "./map/");
  std::ofstream fichier(path.c_str(), std::ios::out);
  if (fichier)
    {
      while (i < _y)
	{
	  j = 0;
	  while (j < _x)
	    {
	      if (i == 0 || i == _y - 1)
		fichier << '1';
	      else if (j == 0 || j == _x - 1)
		fichier << '1';
	      else if (isAnObjects(Objects, j, i) == "Bcube")
		fichier << '2';
	      else if (isAnObjects(Objects, j, i) == "Cube")
		fichier << '1';
	      else
		fichier << ' ';
	      j++;
	    }
	  if (i + 1 < _y)
	    fichier << '\n';
	  i++;
	}
      fichier.close();
      std::cout << "Map saved on " << path << std::endl;
    }
  else
    std::cout << "Cannot save on this file" << std::endl;
}

std::string		Map::isAnObjects(std::vector<AObject*> Objects,
					 int x, int z)const
{
  int			i;

  i = 0;
  while (i < Objects.size())
    {
      if (-x == Objects[i]->getPosX() && -z == Objects[i]->getPosZ())
	return (Objects[i]->getType());
      i++;
    }
  return ("null");
}

Direction		Map::offense_mode(Ia *ia)
{
  glm::vec3		pos;
  glm::vec3		pos_to;
  Direction		i;
  float			d_min;
  bool			cond;
  int			e;

  e = 0;
  cond = false;
  pos = ia->getPos();
  pos_to = getClosest(pos, ia->getAlly());
  d_min = 10000000.0;
  i = STAY;
  if (distance(pos, pos_to) < ia->getRange())
    {
      switch (ia->getDirection())
	{
	case UP:
	  {
	    if (setCollision(glm::vec3(pos.x, pos.y, pos.z + 0.5), 0, UP) == true)
	      {
		if (ifBomb() == false || ifExplosion() == false)
		  return (UNDEFINED);
		putBomb(ia);
	      }
	    break;
	  }
	case DOWN:
	  {
	    if (setCollision(glm::vec3(pos.x, pos.y, pos.z - 0.5), 0, DOWN) == true)
	      {
		if (ifBomb() == false || ifExplosion() == false)
		  return (UNDEFINED);
		putBomb(ia);
	      }
	    break;
	  }
	case LEFT:
	  {
	    if (setCollision(glm::vec3(pos.x + 0.5, pos.y, pos.z), 0, LEFT) == true)
	      {
		if (ifBomb() == false || ifExplosion() == false)
		  return (UNDEFINED);
		putBomb(ia);
	      }
	    break;
	  }
	case RIGHT:
	  {
	    if (setCollision(glm::vec3(pos.x - 0.5, pos.y, pos.z), 0, RIGHT) == true)
	      {
		if (ifBomb() == false || ifExplosion() == false)
		  return (UNDEFINED);
		putBomb(ia);
	      }
	    break;
	  }
	}
    }
  if (ia->getOffense() == 1)
    {
      if (setCollision(glm::vec3(pos.x, pos.y, pos.z + 0.5), 0, UP) == true && _danger->isSafe(glm::vec3(pos.x, pos.y, pos.z + 1)) == true && ia->getLevel() > 4)
	{
	  if (d_min > distance(glm::vec3(pos.x, pos.y, pos.z + 1), pos_to))
	    {
	      d_min = distance(glm::vec3(pos.x, pos.y, pos.z + 1), pos_to);
	      i = UP;
	    }
	}
      if (setCollision(glm::vec3(pos.x, pos.y, pos.z - 0.5), 0, DOWN) == true && _danger->isSafe(glm::vec3(pos.x, pos.y, pos.z - 1)) == true && ia->getLevel() > 4)
	{
	  if (d_min > distance(glm::vec3(pos.x, pos.y, pos.z - 1), pos_to))
	    {
	      d_min = distance(glm::vec3(pos.x, pos.y, pos.z - 1), pos_to);
	      i = DOWN;
	    }
	}
      if (setCollision(glm::vec3(pos.x + 0.5, pos.y, pos.z), 0, LEFT) == true && _danger->isSafe(glm::vec3(pos.x + 1, pos.y, pos.z)) == true && ia->getLevel() > 4)
	{
	  if (d_min > distance(glm::vec3(pos.x + 1, pos.y, pos.z), pos_to))
	    {
	      d_min = distance(glm::vec3(pos.x + 1, pos.y, pos.z), pos_to);
	      i = LEFT;
	    }
	}
      if (setCollision(glm::vec3(pos.x - 0.5, pos.y, pos.z), 0, RIGHT) == true && _danger->isSafe(glm::vec3(pos.x - 1, pos.y, pos.z)) == true && ia->getLevel() > 4)
	{
	  if (d_min > distance(glm::vec3(pos.x - 1, pos.y, pos.z), pos_to))
	    {
	      d_min = distance(glm::vec3(pos.x - 1, pos.y, pos.z), pos_to);
	      i = RIGHT;
	    }
	}
      if (i == STAY)
	return (defense_mode(ia));
      else
	{
	  ia->setDirection(i);
	  return (i);
	}
    }
  if (ia->getOffense() == 0)
    {
      switch (ia->getDirection())
	{
	case UP :
	  {
	    if (setCollision(glm::vec3(pos.x, pos.y, pos.z + 0.5), 0, ia->getDirection()) == true)
	      return (ia->getDirection());
	  }
	case DOWN :
	  {
	    if (setCollision(glm::vec3(pos.x, pos.y, pos.z - 0.5), 0, ia->getDirection()) == true)
	      return (ia->getDirection());
	  }
	case LEFT :
	  {
	    if (setCollision(glm::vec3(pos.x + 0.5, pos.y, pos.z), 0, ia->getDirection()) == true)
	      return (ia->getDirection());
	  }
	case RIGHT :
	  {
	    if (setCollision(glm::vec3(pos.x - 0.5, pos.y, pos.z), 0, ia->getDirection()) == true)
	      return (ia->getDirection());
	  }
	}
      while (cond == false)
	{
	  i = Direction((rand() % STAY));
	  if (i != ia->getDirection())
	    {
	      switch (i)
		{
		case UP :
		  {
		    if (setCollision(glm::vec3(pos.x, pos.y, pos.z + 0.5), 0, UP) == true)
		      {
			ia->setDirection(UP);
			return (UP);
		      }
		    break;
		  }
		case DOWN :
		  {
		    if (setCollision(glm::vec3(pos.x, pos.y, pos.z - 0.5), 0, DOWN) == true)
		      {
			ia->setDirection(DOWN);
			return (DOWN);
		      }
		    break;
		  }
		case LEFT :
		  {
		    if (setCollision(glm::vec3(pos.x + 0.5, pos.y, pos.z), 0, LEFT) == true)
		      {
			ia->setDirection(LEFT);
			return (LEFT);
		      }
		    break;
		  }
		case RIGHT :
		  {
		    if (setCollision(glm::vec3(pos.x - 0.5, pos.y, pos.z), 0, RIGHT) == true)
		      {
			ia->setDirection(RIGHT);
			return (RIGHT);
		      }
		    break;
		  }
		}
	    }
	  return (defense_mode(ia));
	}
    }
  return (i);
}

Direction		Map::defense_mode(Ia *ia)
{
  glm::vec3		pos;
  glm::vec3		pos_to;
  float			d_min;
  Direction		i;

  pos_to = getClosest(pos, ia->getAlly());
  pos = ia->getPos();
  d_min = 1000000;
  i = STAY;
  if (ia->getLevel() > 4)
    {
      if (_danger->isSafe(glm::vec3(pos.x, pos.y, pos.z + 1)) == true && setCollision(glm::vec3(pos.x, pos.y, pos.z + 0.5), 0, UP) == true)
	{
	  if (distance(glm::vec3(pos.x, pos.y, pos.z + 1), pos_to) < d_min)
	    i = UP;
	}
      if (_danger->isSafe(glm::vec3(pos.x, pos.y, pos.z - 1)) == true && setCollision(glm::vec3(pos.x, pos.y, pos.z - 0.5), 0, DOWN) == true)
	{
	  if (distance(glm::vec3(pos.x, pos.y, pos.z - 1), pos_to) < d_min)
	    i = DOWN;
	}
      if (_danger->isSafe(glm::vec3(pos.x + 1, pos.y, pos.z)) == true && setCollision(glm::vec3(pos.x + 0.5, pos.y, pos.z), 0, LEFT) == true)
	{
	  if (distance(glm::vec3(pos.x + 1, pos.y, pos.z), pos_to) < d_min)
	    i = LEFT;
	}
      if (_danger->isSafe(glm::vec3(pos.x - 1, pos.y, pos.z)) == true && setCollision(glm::vec3(pos.x - 0.5, pos.y, pos.z), 0, RIGHT) == true)
	{
	  if (distance(glm::vec3(pos.x - 1, pos.y, pos.z), pos_to) < d_min)
	    i = RIGHT;
	}
    }
  if (i != STAY)
    return (i);
  else
    {
      if (setCollision(glm::vec3(pos.x, pos.y, pos.z + 0.5), 0, UP) == true && distance(glm::vec3(pos.x, pos.y, pos.z + 1), pos_to) < d_min)
	{
	  d_min = distance(glm::vec3(pos.x, pos.y, pos.z + 1), pos_to);
	  i = UP;
	}
      if (setCollision(glm::vec3(pos.x, pos.y, pos.z - 0.5), 0, DOWN) == true && distance(glm::vec3(pos.x, pos.y, pos.z - 1), pos_to) < d_min)
	{
	  d_min = distance(glm::vec3(pos.x, pos.y, pos.z - 1), pos_to);
	  i = DOWN;
	}
      if (setCollision(glm::vec3(pos.x + 0.5, pos.y, pos.z), 0, LEFT) == true && distance(glm::vec3(pos.x + 1, pos.y, pos.z), pos_to) < d_min)
	{
	  d_min = distance(glm::vec3(pos.x + 1, pos.y, pos.z), pos_to);
	  i = LEFT;
	}
      if (setCollision(glm::vec3(pos.x - 0.5, pos.y, pos.z), 0, RIGHT) == true && distance(glm::vec3(pos.x - 1, pos.y, pos.z), pos_to) < d_min)
	{
	  d_min = distance(glm::vec3(pos.x - 1, pos.y, pos.z), pos_to);
	  i = RIGHT;
	}
      return (i);
    }
}

Direction		Map::setIaMove(Ia *ia)
{
  int			i;

  i = ((rand() % 8) + 1);
  if (this->_danger->isSafe(ia->getPos()) == false && ia->getDefense() == 1 && i <= ia->getLevel())
    return (defense_mode(ia));
  return (offense_mode(ia));
}

bool			Map::ifBomb()
{
  AObject* bomb = new Bomb(0, 0, 0);
  if (((Bomb*)bomb)->initialize() == false)
    {
      std::cout << "Bomberman : Can't inialize Bomb" << std::endl;
      delete bomb;
      return (false);
    }
  delete bomb;
  return (true);
}

bool			Map::ifExplosion()
{
  ECube *ecube = new ECube(0, 0, 0, 0);
  if (static_cast<ECube*>(ecube)->initialize("./Graphics/Game/ThemeSpa/Lava.tga") == false)
    {
      std::cout << "Bomberman : Can't inialize Explosion" << std::endl;
      delete ecube;
      return (false);
    }
  delete ecube;
  return (true);
}

void			Map::putBomb(Character *ch)
{
  Direction		dir;
  glm::vec3		charpos;

  dir = ch->getDirection();
  charpos = ch->getPos();
  if (ch->getBombsList() < ch->getAllowed())
    {
      AObject* bomb = new Bomb(ch->getId(), ch->getRange(), ch->getBombId());
      if (((Bomb*)bomb)->initialize() == false)
	std::cout << "Bomberman : Can't inialize Bomb" << std::endl;
      switch (dir)
	{
	case UP :
	  {
	    if (setCollision(glm::vec3(charpos.x, charpos.y, charpos.z + 0.5), 0, UP) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x), charpos.y - 0.5, round(charpos.z) + 1));
		_Elem.push_back(bomb);
		ch->setBombId(ch->getBombId() + 1);
		ch->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	case DOWN :
	  {
	    if (setCollision(glm::vec3(charpos.x, charpos.y, charpos.z - 0.5), 0, DOWN) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x), charpos.y - 0.5, round(charpos.z) - 1));
		_Elem.push_back(bomb);
		ch->setBombId(ch->getBombId() + 1);
		ch->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	case LEFT :
	  {
	    if (setCollision(glm::vec3(charpos.x + 1-0.5, charpos.y, charpos.z), 0, LEFT) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x) + 1, charpos.y - 0.5, round(charpos.z)));
		_Elem.push_back(bomb);
		ch->setBombId(ch->getBombId() + 1);
		ch->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	case RIGHT :
	  {
	    if (setCollision(glm::vec3(charpos.x - 0.5, charpos.y, charpos.z), 0, RIGHT) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x) - 1, charpos.y - 0.5, round(charpos.z)));
		_Elem.push_back(bomb);
		ch->setBombId(ch->getBombId() + 1);
		ch->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	}
    }
}

void			Map::putBomb(Ia *ia)
{
  Direction		dir;
  glm::vec3		charpos;

  dir = ia->getDirection();
  charpos = ia->getPos();
  if (ia->getBombsList() < ia->getAllowed())
    {
      AObject* bomb = new Bomb(ia->getId(), ia->getRange(), ia->getBombId());

      if (((Bomb*)bomb)->initialize() == false)
	std::cout << "Bomberman : Can't inialize Bomb" << std::endl;
      switch (dir)
	{
	case UP :
	  {
	    if (setCollision(glm::vec3(charpos.x, charpos.y, charpos.z + 0.5), 0, UP) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x), charpos.y, round(charpos.z + 1)));
		_Elem.push_back(bomb);
		ia->setBombId(ia->getBombId() + 1);
		ia->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	case DOWN :
	  {
	    if (setCollision(glm::vec3(charpos.x, charpos.y, charpos.z - 0.5), 0, DOWN) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x), charpos.y, round(charpos.z - 1)));
		_Elem.push_back(bomb);
		ia->setBombId(ia->getBombId() + 1);
		ia->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	case LEFT :
	  {
	    if (setCollision(glm::vec3(charpos.x + 1-0.5, charpos.y, charpos.z), 0, LEFT) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x) + 1, charpos.y, round(charpos.z)));
		_Elem.push_back(bomb);
		ia->setBombId(ia->getBombId() + 1);
		ia->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	case RIGHT :
	  {
	    if (setCollision(glm::vec3(charpos.x - 0.5, charpos.y, charpos.z), 0, RIGHT) == true)
	      {
		bomb->setPos(glm::vec3(round(charpos.x) - 1, charpos.y, round(charpos.z)));
		_Elem.push_back(bomb);
		ia->setBombId(ia->getBombId() + 1);
		ia->pushBomb((Bomb*)bomb);
	      }
	    break;
	  }
	}
    }
}

bool			Map::isId(int id, AObject *obj)
{
  if (obj->getType() == "Character")
    {
      if (static_cast<Character*>(obj)->getId() == id)
	return true;
    }
  if (obj->getType() == "Ia")
    {
      if (static_cast<Ia*>(obj)->getId() == id)
	return true;
    }
  return false;
}

void			Map::findBomb(Bomb *bomb)
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character")
	{
	  if (isId(bomb->getId(), _Elem[i]) == true)
	    static_cast<Character*>(_Elem[i])->seekBomb(bomb->getBombId());
	}
      if (_Elem[i]->getType() == "Ia")
	{
	  if (isId(bomb->getId(), _Elem[i]) == true)
	    static_cast<Ia*>(_Elem[i])->seekBomb(bomb->getBombId());
	}
      i++;
    }
}

void			Map::parsBomb()
{
  int			i;

  i = 0;
  _danger->clearBombs();
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Bomb")
	{
	  _danger->setDangerZone((Bomb*)_Elem[i]);
	  if (_danger->isExploded((Bomb*)_Elem[i]) == true)
	    {
	      findBomb((Bomb*)_Elem[i]);
	      addExplosion(static_cast<Bomb*>(_Elem[i]));
	      _Elem.erase(_Elem.begin() + i);
	      eraseOnBonus();
	    }
	}
      else if (_Elem[i]->getType() == "ECube")
	{
	  _danger->pushDanger(_Elem[i]->getPos());
	  if (((ECube*)_Elem[i])->getExplode() == true)
	    _Elem.erase(_Elem.begin() + i);
	}
      i++;
    }
}

void			Map::addExplosion(Bomb* bomb)
{
  AObject*		ecube;
  int			i;
  int			ret;

  ecube = new ECube(bomb->getPosX(), 0, bomb->getPosZ(), bomb->getId());
  if (static_cast<ECube*>(ecube)->initialize("./Graphics/Game/ThemeSpa/Lava.tga") == false)
    std::cout << "Bomberman : Can't inialize ECube" << std::endl;
  _Elem.push_back(ecube);
  for (i = 0; i < bomb->getRange();i++)
    {
      if ((ret = stopExplosion(bomb->getPosX() + i + 1, bomb->getPosZ())) == false)
	{
	  ecube = new ECube(bomb->getPosX() + i + 1, 0, bomb->getPosZ(), bomb->getId());
	  if (static_cast<ECube*>(ecube)->initialize("./Graphics/Game/ThemeSpa/Lava.tga") == false)
	    std::cout << "Bomberman : Can't inialize ECube" << std::endl;
	  _Elem.push_back(ecube);
	}
      else
	i = bomb->getRange();
    }
  for (i = 0; i < bomb->getRange();i++)
    {
      if (stopExplosion(bomb->getPosX() - i - 1, bomb->getPosZ()) == false)
	{
	  ecube = new ECube(bomb->getPosX() - i - 1, 0, bomb->getPosZ(), bomb->getId());
	  if (static_cast<ECube*>(ecube)->initialize("./Graphics/Game/ThemeSpa/Lava.tga") == false)
	    std::cout << "Bomberman : Can't inialize ECube" << std::endl;
	  _Elem.push_back(ecube);
	}
      else
	i = bomb->getRange();
    }
  for (i = 0; i < bomb->getRange();i++)
    {
      if (stopExplosion(bomb->getPosX(), bomb->getPosZ() + i + 1) == false)
	{
	  ecube = new ECube(bomb->getPosX(), 0, bomb->getPosZ() + i + 1, bomb->getId());
	  if (static_cast<ECube*>(ecube)->initialize("./Graphics/Game/ThemeSpa/Lava.tga") == false)
	    std::cout << "Bomberman : Can't inialize ECube" << std::endl;
	  _Elem.push_back(ecube);
	}
      else
	i = bomb->getRange();
    }
  for (i = 0; i < bomb->getRange();i++)
    {
      if (stopExplosion(bomb->getPosX(), bomb->getPosZ() - i - 1) == false)
	{
	  ecube = new ECube(bomb->getPosX(), 0, bomb->getPosZ() - i - 1, bomb->getId());
	  if (static_cast<ECube*>(ecube)->initialize("./Graphics/Game/ThemeSpa/Lava.tga") == false)
	    std::cout << "Bomberman : Can't inialize ECube" << std::endl;
	  _Elem.push_back(ecube);
	}
      else
	i = bomb->getRange();
    }
}

bool			Map::stopExplosion(float x, float z)
{
  AObject*		bonus;
  Ebonus		bns;
  int			rnd;
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Bcube")
	{
	  if (_Elem[i]->getPosX() == x && _Elem[i]->getPosZ() == z)
	    {
	      rnd = rand() % 3;
	      if (rnd == 0)
		bns = SPEED;
	      else if (rnd == 1)
		bns = ADDBOMB;
	      else
		bns = STRENGHT;
	      bonus = new Bonus(_Elem[i]->getPosX(), 0, _Elem[i]->getPosZ());
	      if ((static_cast<Bonus*>(bonus))->initialize(bns) == false)
		{
		  std::cout << "Bomberman : Can't inialize Bonus" << std::endl;
		  return (false);
		}
	      //	      bonus->setScale(glm::vec3(0.5, 0.5, 0.5));
	      _Elem.push_back(bonus);
	      return (true);
	    }
	}
      else if (_Elem[i]->getType() == "Cube")
	{
	  if (_Elem[i]->getPosX() == x && _Elem[i]->getPosZ() == z)
	    return (true);
	}
      i++;
    }
  return (false);
}

void			Map::pickBonus(Character *character)
{
  int			i;

  _interact = new Interact();
  if ((i = _interact->checkBonus(_Elem, character->getPosX(), character->getPosZ())) != -1)
    {
      if (static_cast<Bonus*>(_Elem[i])->getBonus() == ADDBOMB)
	{
	  character->setAllowedBomb(1);
	  _Elem.erase(_Elem.begin() + i);
	}
      else if (static_cast<Bonus*>(_Elem[i])->getBonus() == SPEED)
	{
	  character->setSpeed(0.1);
	  _Elem.erase(_Elem.begin() + i);
	}
      else
	{
	  character->setRange(1);
	  _Elem.erase(_Elem.begin() + i);
	}
    }
}

void			Map::eraseOnBonus()
{
  int			i;
  int			j;
  int			stockx;
  int			stockz;

  i = 0;
  j = _Elem.size();
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Bonus")
	{
	  stockx = _Elem[i]->getPosX();
	  stockz = _Elem[i]->getPosZ();
	  j = 0;
	}
      while (j < _Elem.size())
	{
	  if (stockx == _Elem[j]->getPosX() &&
	      stockz == _Elem[j]->getPosZ() &&
	      _Elem[j]->getType() == "Bcube")
	    {
	      _Elem.erase(_Elem.begin() + j);
	      i--;
	    }
	  j++;
	}
      i++;
    }
}

void			Map::moveBonus()
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Bonus")
	_Elem[i]->rotate(glm::vec3(0, 1, 0), 5);
      i++;
    }
}

float			Map::distance(glm::vec3 begin, glm::vec3 end)const
{
  return sqrt(((begin.x - end.x) * (begin.x - end.x)) +
	      ((begin.z - end.z) * (begin.z - end.z)));
}

  glm::vec3		Map::getClosest(glm::vec3 pos, int mode)const
  {
    int			i;
    float			d_min;
    glm::vec3		pos_to;

    d_min = 1000000;
    i = 0;
    while (i < _Elem.size())
      {
	if (_Elem[i]->getType() == "Character")
	  if (d_min > distance(pos, _Elem[i]->getPos()))
	    {
	      d_min = distance(pos, _Elem[i]->getPos());
	      pos_to = _Elem[i]->getPos();
	    }
	if (_Elem[i]->getType() == "Ia" && mode == 0)
	  {
	    if (d_min > distance(pos, _Elem[i]->getPos()) && _Elem[i]->getPos() != pos)
	      {
		d_min = distance(pos, _Elem[i]->getPos());
		pos_to = _Elem[i]->getPos();
	      }
	  }
	i++;
      }
    return (pos_to);
  }

int			Map::checkDeath(Character *character)
{
  Score*		score;
  int			i;
  int			j;

  i = 0;
  j = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "ECube")
	{
	  //	  if (_Elem[i]->getPosX() - 0.5 < character->getPosX
	  if (_Elem[i]->getPosX() == character->getPosX() && _Elem[i]->getPosZ() == character->getPosZ())
	    {
	      while (j < _Elem.size())
		{
		  if (_Elem[j]->getType() == "Character")
		    if (static_cast<ECube*>(_Elem[i])->getId() == static_cast<Character*>(_Elem[j])->getId())
		      static_cast<Character*>(_Elem[j])->setScore(-50);
		  j++;
		}
	      if (_mode == FREE)
		{
		  score = new Score();
		  score->bestScore(_Elem);
		}
	      return (static_cast<ECube*>(_Elem[i])->getId());
	    }
	}
      i++;
    }
  return (-1);
}


int			Map::checkIaDeath()
{
  int			i;
  int			j;
  int			k;

  i = 0;
  j = 0;
  k = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Ia")
	{
	  j = 0;
	  while (j < _Elem.size())
	    {
	      if (_Elem[j]->getType() == "ECube")
		{
		  if (_Elem[i]->getPosX() == _Elem[j]->getPosX() && _Elem[i]->getPosZ() == _Elem[j]->getPosZ())
		    {
		      _Elem.erase(_Elem.begin() + i);
		      k = 0;
		      while (k < _Elem.size())
			{
			  if (_Elem[k]->getType() == "Character")
			    if (static_cast<ECube*>(_Elem[j])->getId() == static_cast<Character*>(_Elem[k])->getId())
			      static_cast<Character*>(_Elem[k])->setScore(100);
			  k++;
			}
		    }
		}
	      j++;
	    }
	}
      i++;
    }
  return (-1);
}

void			Map::stayIn()
{
  glm::vec3		pos;
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character" || _Elem[i]->getType() == "Ia")
	{
	  pos = _Elem[i]->getPos();
	  if (pos.x > 0)
	    _Elem[i]->setPos(glm::vec3(-1, pos.y, pos.z));
	  if (pos.z > 0)
	    _Elem[i]->setPos(glm::vec3(pos.x, pos.y, -1));
	  if (pos.x < (_x * -1))
	    _Elem[i]->setPos(glm::vec3(_x + 1, pos.y, pos.z));
	  if (pos.z < (_y * -1))
	    _Elem[i]->setPos(glm::vec3(pos.x, pos.y, _y + 1));
	}
      i++;
    }
}

void		Map::saveMap(std::string path)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  path = path.insert(0, "./save/");
  std::ofstream fichier(path.c_str(), std::ios::out);
  if (fichier)
    {
      fichier << _x << std::endl;
      fichier << _y << std::endl;
      while (i < _y)
	{
	  j = 0;
	  while (j < _x)
	    {
	      if (i == 0 || i == _y - 1)
		fichier << '1';
	      else if (j == 0 || j == _x - 1)
		fichier << '1';
	      else if (isAnObjects(_Elem, j, i) == "Bcube")
		fichier << '2';
	      else if (isAnObjects(_Elem, j, i) == "Cube")
		fichier << '1';
	      else
		fichier << ' ';
	      j++;
	    }
	  fichier << '\n';
	  i++;
	}
      i = 0;
      while (i < _Elem.size())
	{
	  if (_Elem[i]->getType() == "ECube")
	    {
	      fichier << _Elem[i]->getT();
	      fichier << _Elem[i]->getData();
	      if (i + 1 < _Elem.size())
		fichier << "\n";
	    }
	  else if (_Elem[i]->getType() == "Bomb")
	    {
	      fichier << _Elem[i]->getT();
	      fichier << _Elem[i]->getData();
	      if (i + 1 < _Elem.size())
		fichier << "\n";
	    }
	  else if (_Elem[i]->getType() == "Ia")
	    {
	      fichier << _Elem[i]->getT();
	      fichier << _Elem[i]->getData();
	      if (i + 1 < _Elem.size())
		fichier << "\n";
	    }
	  else if (_Elem[i]->getType() == "Character")
	    {
	      fichier << _Elem[i]->getT();
	      fichier << _Elem[i]->getData();
	      if (i + 1 < _Elem.size())
		fichier << "\n";
	    }
	  else if (_Elem[i]->getType() == "Bonus")
	    {
	      fichier << _Elem[i]->getT();
	      fichier << _Elem[i]->getData();
	      if (i + 1 < _Elem.size())
		fichier << "\n";
	    }
	  i++;
	}
      fichier.close();
      std::cout << "Map saved on " << path << std::endl;
    }
  else
    std::cout << "Cannot save on this file" << std::endl;
}

  int			Map::getNbPlayer()const
  {
    int			i;
    int			nb;

    i = 0;
    nb = 0;
    if (_Elem.empty())
      return (-1);
    while (i < _Elem.size())
      {
	if (_Elem[i]->getType() == "Character")
	  nb++;
	i++;
      }
    return (nb);
  }

bool		Map::parseECube(std::string line)
{
  int	pos1;
  int	pos2;
  std::string	tmp;
  float	x;
  float	y;
  float	time;
  bool	explo;
  int	id;

  pos1 = line.find("X=");
  pos2 = line.find("Z=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> x;

  pos1 = line.find("Z=");
  pos2 = line.find("TIME=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> y;


  pos1 = line.find("TIME=");
  pos2 = line.find("EXPLO=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 5 && pos1 < pos2)
    tmp = line.substr(pos1 + 5, pos2 - (pos1+5));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> time;
  if (time > 1.0 || time < 0.0)
    time = 0.0;

  pos1 = line.find("EXPLO=");
  pos2 = line.find("ID=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2-(pos1+6));
  else
    return (false);
  if (tmp == "false")
    explo = false;
  else if (tmp == "true")
    explo = true;
  else
    return (false);

  pos1 = line.find("ID=");
  pos2 = line.length();
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 3 && pos1 < pos2)
    tmp = line.substr(pos1 + 3, pos2-(pos1+3));
  else
    return (false);
  if (tmp.length() > 7)
    return (false);
  std::istringstream(tmp) >> id;
  _Elem.push_back(new ECube(x, y, time, explo, id));
  if (_Elem[_nbElem++]->initialize() == false)
    return (false);
  return (true);
}

bool		Map::parseBomb(std::string line)
{
  std::string	tmp;
  float	x;
  float	y;
  float	time;
  int	id;
  int	range;
  bool	explo;
  int	bid;
  int	pos1;
  int	pos2;

  pos1 = line.find("X=");
  pos2 = line.find("Z=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> x;

  pos1 = line.find("Z=");
  pos2 = line.find("TIME=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> y;


  pos1 = line.find("TIME=");
  pos2 = line.find("ID=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 5 && pos1 < pos2)
    tmp = line.substr(pos1 + 5, pos2-(pos1+5));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> time;
  if (time > 3.0 || time < 0.0)
    time = 0;

  pos1 = line.find("ID=");
  pos2 = line.find("RANGE=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 3 && pos1 < pos2)
    tmp = line.substr(pos1 + 3, pos2-(pos1+3));
  else
    return (false);
  if (tmp.length() > 7)
    return (false);
  std::istringstream(tmp) >> id;

  pos1 = line.find("RANGE=");
  pos2 = line.find("EXPLO=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2-(pos1+6));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> range;
  if (range < 0 || range > 60)
    range = 2;


  pos1 = line.find("EXPLO=");
  pos2 = line.find("BID=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2-(pos1+6));
  else
    return (false);
  //std::cout << "Tmp = " << tmp << std::endl;
  if (tmp == "false")
    explo = false;
  else if (tmp == "true")
    explo = true;
  else
    return (false);
  pos1 = line.find("BID=");
  pos2 = line.length();
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 4 && pos1 < pos2)
    tmp = line.substr(pos1 + 4, pos2-(pos1+4));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> bid;
  _Elem.push_back(new Bomb(x, y, time, id, range, explo, bid));
  if (_Elem[_nbElem++]->initialize() == false)
    return (false);
  return (true);
}

bool			Map::checkSaveId(int id)
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character" && static_cast<Character*>(_Elem[i])->getId() == id)
	return (false);
      if (_Elem[i]->getType() == "Ia" && static_cast<Ia*>(_Elem[i])->getId() == id)
	return (false);
      i++;
    }
  return (true);
}

bool			Map::parseCharacter(std::string line)
{
  float	x;
  float	y;
  int	id;
  Direction	dir;
  float	speed;
  int	allowed;
  int	id_bomb;
  int	range;
  int	pos1;
  int	pos2;
  std::string	tmp;
  std::string	name;
  int		score;

  pos1 = line.find("X=");
  pos2 = line.find("Z=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 8)
    return (false);
  std::istringstream(tmp) >> x;


  pos1 = line.find("Z=");
  pos2 = line.find("ID=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 8)
    return (false);
  std::istringstream(tmp) >> y;

  pos1 = line.find("ID=");
  pos2 = line.find("DIR=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 3 && pos1 < pos2)
    tmp = line.substr(pos1 + 3, pos2-(pos1+3));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> id;
  if (checkSaveId(id) == false)
    return (false);



  pos1 = line.find("DIR=");
  pos2 = line.find("S=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 4 && pos1 < pos2)
    tmp = line.substr(pos1 + 4, pos2-(pos1+4));
  else
    return (false);
  if (tmp == "RIGHT")
    dir = RIGHT;
  else if (tmp == "LEFT")
    dir = LEFT;
  else if (tmp == "UP")
    dir = UP;
  else if (tmp == "DOWN")
    dir = DOWN;
  else
    return (false);



  pos1 = line.find("S=");
  pos2 = line.find("NB=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> speed;
  if (speed > 15.0 || speed <= 0.0)
    speed = 10;



  pos1 = line.find("NB=");
  pos2 = line.find("BID=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 3 && pos1 < pos2)
    tmp = line.substr(pos1 + 3, pos2-(pos1+3));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> allowed;
  if (allowed > 100 || allowed <= 0)
    allowed = 1;



  pos1 = line.find("BID=");
  pos2 = line.find("RANGE=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 4 && pos1 < pos2)
    tmp = line.substr(pos1 + 4, pos2-(pos1+4));
  else
    return (false);
  if (tmp.length() > 7)
    return (false);
  std::istringstream(tmp) >> id_bomb;

  pos1 = line.find("RANGE=");
  pos2 = line.find("NAME=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2-(pos1+6));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> range;
  if (range > 100 || range <= 0)
    range = 2;


  pos1 = line.find("NAME=");
  pos2 = line.find("SCORE=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 5 && pos1 < pos2)
    tmp = line.substr(pos1 + 5, pos2 - (pos1 + 5));
  else
    return (false);
  name = tmp;

  pos1 = line.find("SCORE=");
  pos2 = line.length();
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2 - (pos1 + 6));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> score;
  _Elem.push_back(new Character(x, y, dir, speed, id, allowed, id_bomb, range, name, score));
  if (_Elem[_nbElem++]->initialize() == false)
    return (false);
  return (true);
}

bool		Map::parseBonus(std::string line)
{
  std::string	tmp;
  float	x;
  float	y;
  Ebonus	bonus;
  int	pos1;
  int	pos2;

  pos1 = line.find("X=");
  pos2 = line.find("Z=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> x;

  pos1 = line.find("Z=");
  pos2 = line.find("TYPE=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);

  std::istringstream(tmp) >> y;


  pos1 = line.find("TYPE=");
  pos2 = line.length();
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 5 && pos1 < pos2)
    tmp = line.substr(pos1 + 5, pos2-(pos1+5));
  else
    return (false);
  if (tmp == "SPEED")
    bonus = SPEED;
  else if (tmp == "STRENGHT")
    bonus = STRENGHT;
  else if (tmp == "ADDBOMB")
    bonus = ADDBOMB;
  else
    return (false);
  _Elem.push_back(new Bonus(x, y));
  if (((Bonus*)_Elem[_nbElem++])->initialize(bonus) == false)
    return (false);
  return (true);
  //			throw "Bomberman : Cannot initialize Bomb";
}

bool			Map::parseIa(std::string line)
{
  float	x;
  float	y;
  int	id;
  Direction	dir;
  float	speed;
  int	allowed;
  int	bid;
  int	range;
  int	modea;
  int	modeb;
  int	ally;
  int	time;
  int	pos1;
  int	pos2;
  int lvl;
  int	bonus;
  std::string	tmp;

  pos1 = line.find("X=");
  pos2 = line.find("Z=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 8)
    return (false);
  std::istringstream(tmp) >> x;


  pos1 = line.find("Z=");
  pos2 = line.find("ID=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 2 && pos1 < pos2)
    tmp = line.substr(pos1 + 2, pos2-(pos1+2));
  else
    return (false);
  if (tmp.length() > 8)
    return (false);
  std::istringstream(tmp) >> y;


  pos1 = line.find("ID=");
  pos2 = line.find("ALLOWED=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 3 && pos1 < pos2)
    tmp = line.substr(pos1 + 3, pos2-(pos1+3));
  else
    return (false);
  if (tmp.length() > 8)
    return (false);
  std::istringstream(tmp) >> id;
  if (checkSaveId(id) == false)
    return (false);

  pos1 = line.find("ALLOWED=");
  pos2 = line.find("DIR=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 8 && pos1 < pos2)
    tmp = line.substr(pos1 + 8, pos2-(pos1+8));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> allowed;
  if (allowed > 100 || allowed <= 0)
    allowed = 1;



  pos1 = line.find("DIR=");
  pos2 = line.find("BID=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 4 && pos1 < pos2)
    tmp = line.substr(pos1 + 4, pos2-(pos1+4));
  else
    return (false);
  if (tmp == "RIGHT")
    dir = RIGHT;
  else if (tmp == "LEFT")
    dir = LEFT;
  else if (tmp == "UP")
    dir = UP;
  else if (tmp == "DOWN")
    dir = DOWN;
  else
    return (false);



  pos1 = line.find("BID=");
  pos2 = line.find("RANGE=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 4 && pos1 < pos2)
    tmp = line.substr(pos1 + 4, pos2-(pos1+4));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  //std::cout << "Tmp = " << tmp << std::endl;
  std::istringstream(tmp) >> bid;


  pos1 = line.find("RANGE=");
  pos2 = line.find("LVL=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2-(pos1+6));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> range;
  if (range > 100 || range <= 0)
    range = 2;



  pos1 = line.find("LVL=");
  pos2 = line.find("MODEA=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 4 && pos1 < pos2)
    tmp = line.substr(pos1 + 4, pos2-(pos1+4));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> lvl;
  if (lvl < 1 || lvl > 8)
    lvl = 4;

  pos1 = line.find("MODEA=");
  pos2 = line.find("MODEB=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2-(pos1+6));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> modea;
  if (modea < 0 || modea > 1)
    modea = 1;


  pos1 = line.find("MODEB=");
  pos2 = line.find("BONUS=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2 - (pos1 + 6));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> modeb;
  if (modeb < 0 || modeb > 1)
    modeb = 1;

  pos1 = line.find("BONUS=");
  pos2 = line.find("ALLY=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2 - (pos1 + 6));
  else
    return (false);
  if (tmp.length() > 6)
    return (false);
  std::istringstream(tmp) >> bonus;
  if (bonus < 0 || bonus > 1)
    bonus = 0;

  pos1 = line.find("ALLY=");
  pos2 = line.find("TIME=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 5 && pos1 < pos2)
    tmp = line.substr(pos1 + 5, pos2 - (pos1 + 5));
  else
    return (false);
  std::istringstream(tmp) >> ally;

  pos1 = line.find("TIME=");
  pos2 = line.find("SPEED=");
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 5 && pos1 < pos2)
    tmp = line.substr(pos1 + 5, pos2 - (pos1 + 5));
  else
    return (false);
  if (tmp.length() > 8)
    return (false);
  std::istringstream(tmp) >> time;
  if (time > 3.0 || time < 0.0)
    time = 0.0;



  pos1 = line.find("SPEED=");
  pos2 = line.length();
  tmp = "";
  if (pos1 != -1 && pos2 != -1 && line.length() >= pos1 + 6 && pos1 < pos2)
    tmp = line.substr(pos1 + 6, pos2 - (pos1 + 6));
  else
    return (false);
  if (tmp.length() > 8)
    return (false);
  std::istringstream(tmp) >> speed;
  if (speed <= 0 || speed > 15)
    speed = 5.0;


  _Elem.push_back(new Ia(x, y, id, dir, allowed, bid, range, lvl, modea, modeb, ally, time, speed));
  if (static_cast<Ia*>(_Elem[_nbElem++])->initialize("./Graphics/Game/Models/ia_ours/jax.obj", glm::vec3(1.5, 1.5, 1.5)) == false)
    return (false);
  return (true);
}

void			Map::eraseChar(Character *character)
{
  int			i = 0;

  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character")
	if (static_cast<Character*>(_Elem[i])->getId() == character->getId())
	  {
	    _Elem.erase(_Elem.begin() + i);
	    return;
	  }
      i++;
    }
}

void		Map::setNewWave(int wave)
{
  float		increase;
  int		i;

  i = 0;
  increase = 0.4 * wave;
  _nbElem = _Elem.size();
  if (wave == 1)
    {
      _Elem.push_back(new Ia((_x * -1) + 2, 0, (_y * -1) + 2, _id++));
      static_cast<Ia*>(_Elem[_nbElem])->initialize("./Graphics/Game/Models/ia_zombie/Lambent_Male.obj", glm::vec3(0.9, 0.5, 0.9));	

      static_cast<Ia*>(_Elem[_nbElem])->setLevel(2);
      static_cast<Ia*>(_Elem[_nbElem])->setSpeed(2.0);
      static_cast<Ia*>(_Elem[_nbElem])->setDefense(1);
      static_cast<Ia*>(_Elem[_nbElem])->setOffense(1);
      static_cast<Ia*>(_Elem[_nbElem])->setBonus(0);
      static_cast<Ia*>(_Elem[_nbElem])->setAllowed(1);
      static_cast<Ia*>(_Elem[_nbElem])->setAlly(1);
      static_cast<Ia*>(_Elem[_nbElem])->setTimer(3);
      static_cast<Ia*>(_Elem[_nbElem])->setRange(2);
      _nbElem++;
    }
  else
    {
      if (!addPlayers(0, wave))//addIa(wave))
	std::cout << "Bomberman : Cannot add Ia" << std::endl;
      while (i < _Elem.size())
	{
	  if (_Elem[i]->getType() == "Ia")
	    {
	      static_cast<Ia*>(_Elem[i])->setLevel(1 + wave);
	      static_cast<Ia*>(_Elem[i])->setSpeed(2.0 + increase);
	      static_cast<Ia*>(_Elem[i])->setDefense(1);
	      static_cast<Ia*>(_Elem[i])->setOffense(1);
	      static_cast<Ia*>(_Elem[i])->setBonus(0);
	      static_cast<Ia*>(_Elem[i])->setAllowed(1);
	      static_cast<Ia*>(_Elem[i])->setAlly(1);
	      static_cast<Ia*>(_Elem[i])->setTimer(3);
	      static_cast<Ia*>(_Elem[i])->setRange(2);
	    }
	  i++;
	}
    }
}

int			Map::findPlayer(int id)const
{
  int			i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character")
	{
	  if (((Character*)_Elem[i])->getId() == id)
	    return (1);
	}
      if (_Elem[i]->getType() == "Ia")
	{
	  if (((Ia*)_Elem[i])->getId() == id)
	    return (2);
	}
      i++;
    }
  return (-1);
}

Ia*		Map::getIa(int id)const
{
  int		i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Ia")
	{
	  if (((Ia*)_Elem[i])->getId() == id)
	    return ((Ia*)_Elem[i]);
	}
      i++;
    }
  return (NULL);
}

Character*	Map::getChar(int id)const
{
  int		i;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Character")
	{
	  if (((Character*)_Elem[i])->getId() == id)
	    return ((Character*)_Elem[i]);
	}
      i++;
    }
  return (NULL);
}

bool		Map::fillBombToPlayers()
{
  int	i;
  int	pers;

  i = 0;
  while (i < _Elem.size())
    {
      if (_Elem[i]->getType() == "Bomb")
	{
	  pers = findPlayer(((Bomb*)_Elem[i])->getId());
	  switch (pers)
	    {
	    case -1 :
	      {
		return (false);
		break;
	      }
	    case 1 :
	      {
		Character*	player;

		if ((player = getChar(((Bomb*)_Elem[i])->getId())) == NULL)
		  return (false);
		break;
	      }
	    case 2 :
	      {
		Ia*		player;

		if ((player = getIa(((Bomb*)_Elem[i])->getId())) == NULL)
		  return (false);
		break;
	      }
	    }
	}
      i++;
    }
  return (true);
}

bool		Map::addPlayers(int nb_player, int nb_ia)
{
  int		totsize;
  int		totplayer;
  float		interval;
  int		posx;
  int		posy;
  int		pos;
  int		diff;
  int		i;
  int		posj2;

  if (_x <= 0 || _y <= 0 || nb_player < 0 || nb_ia < 0)
    return (false);
  totplayer = nb_player + nb_ia;
  totsize = ((_x - 2) * 2) + (((_y - 2) * 2) - 4);
  interval = (float)totsize / (float)totplayer;
  interval = trunc(interval);
  if (interval == 0)
    return (false);
  pos = 0;
  posx = 1;
  posy = 1;
  i = 0;
  posj2 = round(totplayer / 2) * interval;
  while (totplayer > 0 && i < 10000)
    {
      if (pos == 0 && nb_player > 0)
	{
	  _Elem.push_back(new Character(-posx, 0, -posy, _id++, _fpname));
	  if (_Elem[_nbElem++]->initialize() == false)
	    return (false);
	  totplayer--;
	  nb_player--;
	}
      else if (pos == posj2 && nb_player > 0)
	{
	  _Elem.push_back(new Character(-posx, 0, -posy, _id++, _spname));
	  if (_Elem[_nbElem++]->initialize() == false)
	    return (false);
	  totplayer--;
	  nb_player--;
	}
      else if (nb_ia > 0)
	{
	  _Elem.push_back(new Ia(-posx, 0, -posy, _id++));
	  if (_mode == SURV)
	    {
	      if (static_cast<Ia*>(_Elem[_nbElem++])->initialize("./Graphics/Game/Models/ia_zombie/Lambent_Male.obj", glm::vec3(0.9, 0.5, 0.9)) == false)
		return (false);
	    }
	  else
	    if (static_cast<Ia*>(_Elem[_nbElem++])->initialize("./Graphics/Game/Models/ia_ours/jax.obj", glm::vec3(1.5, 1.5, 1.5)) == false)
	      return (false);
	  //	  if (_Elem[_nbElem++]->initialize() == false)
	  // return (false);
	  totplayer--;
	  nb_ia--;
	}
      pos += interval;
      if (pos < (_x - 2) + interval)
	{
	  posx += interval;
	  if (posx > (_x - 2))
	    {
	      diff = posx - (_x - 2);
	      posx = _x - 2;
	      posy += diff;
	      if (posy > (_y - 2))
		{
		  diff = posy - (_y - 2);
		  posy = _y - 2;
		  posx -= diff;
		  if (posx < 1)
		    {
		      diff = posx * -1;
		      posx = 1;
		      posy -= diff;
		    }
		}
	    }
	}
      else if (pos < (_x - 2) + (_y - 2) + interval)
	{
	  posx = _x - 2;
	  posy += interval;
	  if (posy > (_y - 2))
	    {
	      diff = posy - (_y - 2);
	      posy = _y - 2;
	      posx -= diff;
	      if (posx < 1)
		{
		  diff = posx * -1;
		  posx = 1;
		  posy -= diff;
		}
	    }
	}
      else if (pos < (_x - 2) + (_y - 2) + (_x - 2) + interval)
	{
	  posy = _y - 2;
	  posx -= interval;
	  if (posx < 1)
	    {
	      diff = posx * -1;
	      posx = 1;
	      posy -= diff;
	    }
	}
      else
	posy -= interval;
      i++;
    }
  if (i >= 10000)
    return (false);
  return (true);
}

void			Map::setMode(GameMode mode)
{
  _mode = mode;
}

void			Map::callScore()
{
  Score*		score;

  if (_mode == FREE)
    {
      score = new Score();
      score->bestScore(_Elem);
    }
}
