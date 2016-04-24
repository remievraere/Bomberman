// Started by Simon Bulcke
// Last update by Clovis Masson
//

#include	"MainMenu.hh"

MainMenu::MainMenu()
{
  _selected = 1;
  _j = 0;
  _k = 0;
}

MainMenu::~MainMenu()
{
  delete _background;
  delete _game;
  delete _extras;
  delete _tools;
}

bool		MainMenu::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/BMainMenu.tga", 800, 600) == false)
    return (false);
  _background->scale(glm::vec3(1.2, 1.2, 1.2));
  _game = new SkyBox();
  _extras = new SkyBox();
  _tools = new SkyBox();
  _head = new Plan();
  if (((Plan*)_head)->initialize("./Graphics/Menu/head.tga", 200, 229) == false)
    return (false);
  _head->setPos(glm::vec3(33, -25, 0)); //-25 -> bas // 19 -> haut // 33
  _head->scale(glm::vec3(0.2, 0.2, 0.2));
  if (((SkyBox*)_game)->initialize(1, glm::vec3(0, 0, 0), "./Graphics/Menu/Play.tga") == false)
    return (false);
  if (((SkyBox*)_extras)->initialize(1, glm::vec3(15, 0, 0), "./Graphics/Menu/Extras.tga") == false)
    return (false);
  if (((SkyBox*)_tools)->initialize(1, glm::vec3(-15, 0, 0), "./Graphics/Menu/Tools.tga") == false)
    return (false);
  return (true);
}

void		MainMenu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  int		i;

  i = 0;
  i = _j;
  if (_k % 20 == 0)
    _j++;
  _k++;
  while (i < 1000)
    {
      _head->draw(shader, clock);
      if (i <= 50)
	_head->setPos(glm::vec3((i - 25), -25, 0));
      else if (i <= 94)
      	_head->setPos(glm::vec3(-25, (i - 50) - 25, 0));
      else if (i <= 144)
	_head->setPos(glm::vec3((i - 94) - 25, 19, 0));
      else if (i <= 188)
	_head->setPos(glm::vec3(25, (i - 144) - 25, 0));
      i += 5;
    }
  if (_j >= 5)
    {
    _j = 0;
    _k = 0;
    }
  _game->setScale(glm::vec3(2, 2, 2));
  _extras->setScale(glm::vec3(2, 2, 2));
  _tools->setScale(glm::vec3(2, 2, 2));
  _background->draw(shader, clock);
  _game->rotate(glm::vec3(0,1,0), 0.05);
  if (_selected == 1)
    _game->setScale(glm::vec3(4, 4, 4));
  _game->draw(shader, clock);
  _extras->rotate(glm::vec3(0,1,0), 0.05);
  if (_selected == 0)
    _extras->setScale(glm::vec3(4, 4, 4));
  _extras->draw(shader, clock);
  _tools->rotate(glm::vec3(0, 1, 0), 0.05);
  if (_selected == 2)
    _tools->setScale(glm::vec3(4, 4, 4));
  _tools->draw(shader, clock);
}

Module		MainMenu::update(gdl::Clock const &clock, gdl::Input &input)
{
  if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    {
      return (QUIT);
    }
  if (input.getKey(SDLK_w, false))
    {
      /*      _selected++;
	      if (_selected > 2)
	      _selected = 0;*/
      _selected = 0;
    }
  if (input.getKey(SDLK_x, false))
    {
      /*      _selected--;
	      if (_selected < 0)
	      _selected = 2;*/
      _selected = 1;
    }
  if (input.getKey(SDLK_c))
    _selected = 2;
  if (input.getKey(SDLK_RETURN))
    {
      switch (_selected)
	{
	case 0 :
	  {
	    return (EXTRA);
	    break;
	  }
	case 1 :
	  {
	    return (GAME);
	    break;
	  }
	case 2 :
	  {
	    return (TOOLS);
	    break;
	  }
	}
    }
  /*  if (input.getKey(SDLK_a))
      return (LOAD_MAP);
  */
  /*  if (input.getKey(SDLK_z))
      return (DUAL_GAME);*/
  /*  if (input.getKey(SDLK_b))
      return (RAND_MAP);
      if (input.getKey(SDLK_r))
      return (GAME);
      if (input.getKey(SDLK_e))
      return (EDIT_MAP);*/
  return (MENU);
}
