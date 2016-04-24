// Started by Kevin Fandi
// Last update by Kevin Fandi
//

#include	"GameMenu.hh"

GameMenu::GameMenu()
{
  _selected = 0;
}

GameMenu::~GameMenu()
{
  delete _background;
  delete _loadGame;
  delete _newGame;
}

bool		GameMenu::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/BMainMenu.tga", 800, 600) == false)
    return (false);
  _background->scale(glm::vec3(1.2, 1.2, 1.2));
  _newGame = new SkyBox();
  _loadGame = new SkyBox();
  if (((SkyBox*)_newGame)->initialize(1, glm::vec3(10, 0, 0), "./Graphics/Menu/NewGame.tga") == false)
    return (false);
  if (((SkyBox*)_loadGame)->initialize(1, glm::vec3(-10, 0, 0), "./Graphics/Menu/LoadGame.tga") == false)
    return (false);
  return (true);
}

void		GameMenu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _newGame->setScale(glm::vec3(2, 2, 2));
  _loadGame->setScale(glm::vec3(2, 2, 2));
  _background->draw(shader, clock);
  _newGame->rotate(glm::vec3(0,1,0), 0.05);
  if (_selected == 0)
    _newGame->setScale(glm::vec3(4,4,4));
  _newGame->draw(shader, clock);
  _loadGame->rotate(glm::vec3(0,1,0), 0.05);
  if (_selected == 1)
    _loadGame->setScale(glm::vec3(4,4,4));
  _loadGame->draw(shader, clock);
}

Module		GameMenu::update(gdl::Clock const &clock, gdl::Input &input)
{
  if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return (QUIT);
  if (input.getKey(SDLK_TAB))
    return (MENU);
  if (input.getKey(SDLK_w))
    {
      /*      _selected++;
	      if (_selected > 2)
	      _selected = 0;*/
      _selected = 0;
    }
  if (input.getKey(SDLK_x))
    {
      /*      _selected--;
	      if (_selected < 0)
	      _selected = 2;*/
      _selected = 1;
    }
  if (input.getKey(SDLK_RETURN))
    {
      switch (_selected)
	{
	case 0 :
	  {
	    return (NEW_GAME);
	    break;
	  }
	case 1 :
	  {
	    return (LOAD_GAME);
	    break;
	  }
	}
    }
  /*  if (input.getKey(SDLK_a))
      return (LOAD_MAP);
      if (input.getKey(SDLK_z))
      return (DUAL_GAME);
      if (input.getKey(SDLK_b))
      return (RAND_MAP);
      if (input.getKey(SDLK_r))
      return (GAME);
      if (input.getKey(SDLK_e))
      return (EDIT_MAP);*/
  return (GAME);
}
