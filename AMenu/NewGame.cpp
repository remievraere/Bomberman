// Started by Simon Bulcke
// Last update by Simon Bulcke
//

#include	"NewGame.hh"

NewGame::NewGame()
{
  _selected = 0;
}

NewGame::~NewGame()
{
}

bool		NewGame::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/BFreeMode.tga", 800, 600) == false)
    return (false);
  _background->scale(glm::vec3(1.2, 1.2, 1.2));
  _freeMode = new Plan();
  _sfreeMode = new Plan();
  ((Plan*)_sfreeMode)->setColor(glm::vec4(1, 0, 0, 1));
  if (((Plan*)_freeMode)->initialize("./Graphics/Menu/FreeMode.tga", 620, 38) == false)
    return (false);
  if (((Plan*)_sfreeMode)->initialize("./Graphics/Menu/FreeMode.tga", 620, 38) == false)
    return (false);
  _freeMode->setPos(glm::vec3(0, 10, 0));
  _sfreeMode->setPos(glm::vec3(0, 10, 0));
  _arcade = new Plan();
  _sarcade = new Plan();
  ((Plan*)_sarcade)->setColor(glm::vec4(1, 0, 0, 1));
  if (((Plan*)_arcade)->initialize("./Graphics/Menu/Arcade.tga", 418, 37) == false)
    return (false);
  if (((Plan*)_sarcade)->initialize("./Graphics/Menu/Arcade.tga", 418, 37) == false)
    return (false);
  _arcade->setPos(glm::vec3(0, 0, -1));
  _sarcade->setPos(glm::vec3(0, 0, -1));
  _survival = new Plan();
  _ssurvival = new Plan();
  ((Plan*)_ssurvival)->setColor(glm::vec4(1, 0, 0, 1));
  if (((Plan*)_survival)->initialize("./Graphics/Menu/Survival.tga", 226, 54) == false)
    return (false);
  if (((Plan*)_ssurvival)->initialize("./Graphics/Menu/Survival.tga", 226, 54) == false)
    return (false);
  _survival->setPos(glm::vec3(0, -10, 0));
  _survival->scale(glm::vec3(1.3, 1.3, 1.3));
  _ssurvival->setPos(glm::vec3(0, -10, 0));
  _ssurvival->scale(glm::vec3(1.3, 1.3, 1.3));
  return (true);
}

void		NewGame::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _background->draw(shader, clock);
  if (_selected == 0)
    {
      _sfreeMode->draw(shader, clock);
      _arcade->draw(shader, clock);
      _survival->draw(shader, clock);
    }
  else if (_selected == 1)
    {
      _sarcade->draw(shader, clock);
      _freeMode->draw(shader, clock);
      _survival->draw(shader, clock);
    }
  else if (_selected == 2)
    {
      _ssurvival->draw(shader, clock);
      _freeMode->draw(shader, clock);
      _arcade->draw(shader, clock);
    }
}

Module		NewGame::update(gdl::Clock const &clock, gdl::Input &input)
{
  if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return (QUIT);
  if (input.getKey(SDLK_TAB))
    return (MENU);
  if (input.getKey('a'))
    _selected = 0;
  if (input.getKey('z'))
    _selected = 1;
  if (input.getKey('e'))
    _selected = 2;
  if (input.getKey(SDLK_RETURN))
    {
      if (_selected == 0)
	return (FREE_MODE);
      if (_selected == 1)
	return (ARCADE);
      if (_selected == 2)
	return (SURVIVAL);
    }
  return (NEW_GAME);
}
