// Started by Clovis Masson
// Last update by Clovis Masson
//

#include	"FreeMode.hh"

FreeMode::FreeMode(Run *run)
{
  _selected = 0;
  _run = run;
  _step = 0;
  _fpname = "";
  _spname = "";
  _nbIa = 0;
  _mapX = 10;
  _mapY = 10;
  _BDensity = 0;
  _CDensity = 0;
}

FreeMode::~FreeMode()
{
}

bool		FreeMode::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/Background.tga", 800, 600) == false)
    return (false);
  _background->scale(glm::vec3(1.2, 1.2, 1.2));
  Readdir	*map = new Readdir("./map");
  _list = map->getRes();
  _list.push_back("Random");
  return (true);
}

void		FreeMode::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  int		i;
  int		j;
  Alpha		*write = new Alpha();
  Number	*num = new Number();

  _background->draw(shader, clock);
  if (_step == 0)
    {
      i = _selected;
      j = 0;
      while (i >= 0)
	{
	  if (i == _selected)
	    {
	      write->initialize(_list[i], glm::vec3(27, 0, 0), glm::vec3(2, 2, 2), glm::vec4(1, 0, 0, 1));
	      write->draw(shader, clock);
	    }
	  else
	    {
	      write->initialize(_list[i], glm::vec3(27, j * 3.5, 0), glm::vec3(2, 2, 2), glm::vec4(0, 0, 0, 1));
	      write->draw(shader, clock);
	    }
	  j++;
	  i--;
	}
      i = _selected + 1;
      j = 1;
      while (i < _list.size())
	{
	  write->initialize(_list[i], glm::vec3(27, j * -3.5, 0), glm::vec3(2, 2, 2), glm::vec4(0, 0, 0, 1));
	  write->draw(shader, clock);
	  i++;
	  j++;
	}
    }
  else if (_step == 1)
    {
      if (_selected == 0)
	write->initialize("Player 1 : ", glm::vec3(27, 23, 0), glm::vec3(2, 2, 2), glm::vec4(1,0,0,1));
      else
	write->initialize("Player 1 : ", glm::vec3(27, 23, 0), glm::vec3(2, 2, 2), glm::vec4(0,0,0,1));
      write->draw(shader, clock);
      write->initialize(_fpname, glm::vec3(27, 20, 0), glm::vec3(2, 2, 2), glm::vec4(0, 1, 0, 1));
      write->draw(shader, clock);
      if (_selected == 1)
	write->initialize("Player 2 (Optional) : ", glm::vec3(27,17,0),glm::vec3(2, 2, 2), glm::vec4(1, 0, 0, 1));
      else
	write->initialize("Player 2 (Optional) : ", glm::vec3(27,17,0), glm::vec3(2, 2, 2), glm::vec4(0, 0, 0, 1));
      write->draw(shader, clock);
      write->initialize(_spname, glm::vec3(27, 14, 0), glm::vec3(2, 2, 2), glm::vec4(0, 1, 0, 1));
      write->draw(shader, clock);
      if (_selected == 2)
	write->initialize("IA Number : ", glm::vec3(27, 11, 0), glm::vec3(2, 2, 2), glm::vec4(1, 0, 0, 1));
      else
	write->initialize("IA Number : ", glm::vec3(27, 11, 0), glm::vec3(2, 2, 2), glm::vec4(0, 0, 0, 1));
      write->draw(shader, clock);
      num->initialize(_nbIa, glm::vec3(27, 8, 0), glm::vec3(2, 2, 2), glm::vec4(0, 1, 0, 1));
      num->draw(shader, clock);
      if (_selectedMap == _list.size() - 1)
	{
	  if (_selected == 3)
	    write->initialize("Map X : ", glm::vec3(27, 5, 0), glm::vec3(2, 2, 2), glm::vec4(1,0,0,1));
	  else
	    write->initialize("Map X : ", glm::vec3(27, 5, 0), glm::vec3(2, 2, 2), glm::vec4(0,0,0,1));
	  write->draw(shader, clock);
	  num->initialize(_mapX, glm::vec3(27,2,0), glm::vec3(2,2,2), glm::vec4(0,1,0,1));
	  num->draw(shader, clock);
	  if (_selected == 4)
	    write->initialize("Map Y : ", glm::vec3(27, -1, 0), glm::vec3(2, 2, 2), glm::vec4(1,0,0,1));
	  else
	    write->initialize("Map Y : ", glm::vec3(27, -1, 0), glm::vec3(2, 2, 2), glm::vec4(0,0,0,1));
	  write->draw(shader, clock);
	  num->initialize(_mapY, glm::vec3(27,-4,0), glm::vec3(2,2,2), glm::vec4(0,1,0,1));
	  num->draw(shader, clock);
	  if (_selected == 5)
	    write->initialize("Cube density : ", glm::vec3(27, -7, 0), glm::vec3(2, 2, 2), glm::vec4(1,0,0,1));
	  else
	    write->initialize("Cube density : ", glm::vec3(27, -7, 0), glm::vec3(2, 2, 2), glm::vec4(0,0,0,1));
	  write->draw(shader, clock);
	  num->initialize(_BDensity, glm::vec3(27,-10,0), glm::vec3(2,2,2), glm::vec4(0,1,0,1));
	  num->draw(shader, clock);
	  if (_selected == 6)
	    write->initialize("BCube density : ", glm::vec3(27, -13, 0), glm::vec3(2, 2, 2), glm::vec4(1,0,0,1));
	  else
	    write->initialize("BCube density : ", glm::vec3(27, -13, 0), glm::vec3(2, 2, 2), glm::vec4(0,0,0,1));
	  write->draw(shader, clock);
	  num->initialize(_CDensity, glm::vec3(27,-16,0), glm::vec3(2,2,2), glm::vec4(0,1,0,1));
	  num->draw(shader, clock);
	  write->initialize("ENTER TO START GAME", glm::vec3(27, -19, 0), glm::vec3(2, 2, 2), glm::vec4(0, 0, 0, 1));
	  write->draw(shader, clock);
	}
      else
	{
	  write->initialize("ENTER TO START GAME", glm::vec3(27, 0, 0), glm::vec3(2, 2, 2), glm::vec4(0, 0, 0, 1));
	  write->draw(shader, clock);
	}
    }
}

Module		FreeMode::update(gdl::Clock const &clock, gdl::Input &input)
{
  int		keycode;
  int		size;
  char		key[2];

  if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return (QUIT);
  if (input.getKey(SDLK_TAB))
    return (MENU);
  if (_step == 0)
    size = _list.size() - 1;
  else if (_step == 1 && _list.size() - 1 != _selectedMap)
    size = 2;
  else
    size = 6;
  if (input.getKey(SDLK_UP))
    {
      _selected--;
      if (_selected < 0)
	_selected = size;
    }
  if (input.getKey(SDLK_DOWN))
    {
      _selected++;
      if (_selected > size)
	_selected = 0;
    }
  if (input.getKey(SDLK_RETURN))
    {
      if (_step == 0)
	{
	  _step = 1;
	  _selectedMap = _selected;
	  _selected = 0;
	}
      else if (_step == 1)
	{
	  if (_selectedMap == _list.size() - 1)
	    {
	      _run->setMapX(_mapX);
	      _run->setMapY(_mapY);
	      _run->setBDensity(_BDensity);
	      _run->setCDensity(_CDensity);
	      _run->setMapPath("");
	    }
	  else
	    _run->setMapPath("./map/" + _list[_selectedMap]);
	  if (_fpname != "" && _spname != "")
	    {
	      _run->setFpname(_fpname);
	      _run->setSpname(_spname);
	      _run->setNbIa(_nbIa);
	      return (DUAL_GAME);
	    }
	  if (_fpname != "" && _nbIa > 0)
	    {
	      _run->setFpname(_fpname);
	      _run->setNbIa(_nbIa);
	      return (LOAD_MAP);
	    }
	  else
	    _selected = 0;
	}
    }
  if (_step == 1)
    {
      keycode = 'a';
      while (keycode <= 'z')
	{
	  if (input.getKey(keycode))
	    {
	      key[0] = keycode;
	      key[1] = 0;
	      if (_selected == 0)
		_fpname += key;
	      if (_selected == 1)
		_spname += key;
	    }
	  keycode++;
	}
      if (_selected == 2)
	{
	  if (input.getKey(SDLK_RIGHT) && _nbIa < 1000)
	    _nbIa++;
	  if (input.getKey(SDLK_LEFT))
	    {
	      _nbIa--;
	      if (_nbIa < 0)
		_nbIa = 0;
	    }
	}
      if (_selected == 3)
	{
	  if (input.getKey(SDLK_RIGHT) && _mapX < 1000)
	    _mapX++;
	  if (input.getKey(SDLK_LEFT))
	    {
	      _mapX--;
	      if (_mapX < 10)
		_mapX = 10;
	    }
	}
      if (_selected == 4)
	{
	  if (input.getKey(SDLK_RIGHT) && _mapY < 1000)
	    _mapY++;
	  if (input.getKey(SDLK_LEFT))
	    {
	      _mapY--;
	      if (_mapY < 10)
		_mapY = 10;
	    }
	}
      if (_selected == 5)
	{
	  if (input.getKey(SDLK_RIGHT) && _BDensity < 100)
	    _BDensity++;
	  if (input.getKey(SDLK_LEFT))
	    {
	      _BDensity--;
	      if (_BDensity < 0)
		_BDensity = 0;
	    }
	}
      if (_selected == 6)
	{
	  if (input.getKey(SDLK_RIGHT) && _CDensity < 100)
	    _CDensity++;
	  if (input.getKey(SDLK_LEFT))
	    {
	      _CDensity--;
	      if (_CDensity < 0)
		_CDensity = 0;
	    }
	}
      if (input.getKey(SDLK_BACKSPACE))
	{
	  if (_selected == 0)
	    _fpname = _fpname.substr(0, _fpname.length() - 1);
	  else if (_selected == 1)
	    _spname = _spname.substr(0, _spname.length() - 1);
	}
    }
  return (FREE_MODE);
}
