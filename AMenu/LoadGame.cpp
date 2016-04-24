// Started by Remi Evraere
// Last update by Remi Evraere
//

#include	"LoadGame.hh"

LoadGame::LoadGame(Run *run)
{
  _selected = 0;
  _run = run;
}

LoadGame::~LoadGame()
{
}

bool		LoadGame::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/Background.tga") == false)
    return (false);
  _background->scale(glm::vec3(10000, 10000, 10000));
  Readdir	*save = new Readdir("./save");
  _list = save->getRes();
  if (_list.size() <= 0)
    _selected = -1;
  return (true);
}

void		LoadGame::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  int		i;
  int		j;
  Alpha		*write;

  write = new Alpha();
  _background->draw(shader, clock);
  if (_selected == -1)
    {
      write->initialize("No save", glm::vec3(27, 0, 0), glm::vec3(2, 2, 2), glm::vec4(1, 0, 0, 1));
      write->draw(shader, clock);
    }
  else
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
}

Module		LoadGame::update(gdl::Clock const &clock, gdl::Input &input)
{
  if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return (QUIT);
  if (input.getKey(SDLK_TAB))
    return (MENU);
  if (input.getKey(SDLK_UP) && _selected != -1)
    {
      _selected--;
      if (_selected < 0)
	_selected = _list.size() - 1;
    }
  if (input.getKey(SDLK_DOWN) && _selected != -1)
    {
      _selected++;
      if (_selected > _list.size() - 1)
	_selected = 0;
    }
  if (input.getKey(SDLK_RETURN))
    {
      if (_selected != -1)
	{
	  _run->setMapPath(_list[_selected]);
	  return (READ_SAVE);
	}
      else
	return (MENU);
    }
  return (LOAD_GAME);
}
