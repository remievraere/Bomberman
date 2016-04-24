// Started by Medhi Kolai
// Last update by Clovis Masson
//

#include	"ToolsMenu.hh"

ToolsMenu::ToolsMenu(Run *run)
{
  _selected = 0;
  _run = run;
}

ToolsMenu::~ToolsMenu()
{

}

bool		ToolsMenu::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/BTools.tga", 800, 600) == false)
    return (false);
  _background->scale(glm::vec3(1.2, 1.2, 1.2));
  return (true);
}

void		ToolsMenu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  Alpha		*write = new Alpha();
  Number	*nb = new Number();

  _background->draw(shader, clock);
  if (_selected == 0)
    write->initialize("SOUND", glm::vec3(23, 3, 0), glm::vec3(2, 2, 2), glm::vec4(1, 0, 0, 1));
  else
    write->initialize("SOUND", glm::vec3(23, 3, 0), glm::vec3(2, 2, 2), glm::vec4(1, 1, 1, 1));
  write->draw(shader, clock);
  if (_selected == 1)
    write->initialize("MENU", glm::vec3(23, -4, 0), glm::vec3(2, 2, 2), glm::vec4(1, 0, 0, 1));
  else
    write->initialize("MENU", glm::vec3(23, -4, 0), glm::vec3(2, 2, 2), glm::vec4(1, 1, 1, 1));
  write->draw(shader, clock);
  nb->initialize(_run->getSoundVol(), glm::vec3(-2, 3, 0), glm::vec3(2, 2, 2), glm::vec4(1, 1, 1, 1));
  nb->draw(shader, clock);
}


Module		ToolsMenu::update(gdl::Clock const &clock, gdl::Input &input)
{
  if(input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return (QUIT);
  if (input.getKey(SDLK_TAB))
    return (MENU);
  if (input.getKey(SDLK_DOWN))
    {
      _selected++;
      if (_selected > 1)
	_selected = 0;
    }
  if (input.getKey(SDLK_UP))
    {
      _selected--;
      if (_selected < 0)
	_selected = 1;
    }
  if (input.getKey(SDLK_RETURN) && _selected == 1)
    return (MENU);
  if (input.getKey(SDLK_RIGHT) && _selected == 0)
    if (_run->getSoundVol()+5 <= 100)
      _run->setSoundVol(_run->getSoundVol()+5);
  if (input.getKey(SDLK_LEFT) && _selected == 0)
    if (_run->getSoundVol()-5 >= 0)
      _run->setSoundVol(_run->getSoundVol()-5);
  return (TOOLS);
}
