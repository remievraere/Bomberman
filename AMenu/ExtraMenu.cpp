// Started by Simon Bulcke
// Last update by Simon Bulcke
//

#include	"ExtraMenu.hh"

ExtraMenu::ExtraMenu()
{
  _selected = 0;
}

ExtraMenu::~ExtraMenu()
{

}

bool		ExtraMenu::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/BMainMenu.tga", 800, 600) == false)
    return (false);
  _background->scale(glm::vec3(1.2, 1.2, 1.2));
  _editor = new SkyBox();
  _rate = new SkyBox();
  if (((SkyBox*)_editor)->initialize(1, glm::vec3(10, 0, 0), "./Graphics/Menu/Editor.tga") == false)
    return (false);
  if (((SkyBox*)_rate)->initialize(1, glm::vec3(-10, 0, 0), "./Graphics/Menu/Rates.tga") == false)
    return (false);
  return (true);
}

void		ExtraMenu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _editor->setScale(glm::vec3(2, 2, 2));
  _rate->setScale(glm::vec3(2, 2, 2));
  _background->draw(shader, clock);
  _editor->rotate(glm::vec3(0, 1, 0), 0.05);
  if (_selected == 0)
    _editor->setScale(glm::vec3(4, 4, 4));
  _editor->draw(shader, clock);
  if (_selected == 1)
    _rate->setScale(glm::vec3(4, 4, 4));
  _rate->rotate(glm::vec3(0, 1, 0), 0.05);
  _rate->draw(shader, clock);
}

Module		ExtraMenu::update(gdl::Clock const &clock, gdl::Input &input)
{
  if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return (QUIT);
  if (input.getKey(SDLK_TAB))
    return (MENU);
  if (input.getKey(SDLK_w))
    _selected = 0;
  if (input.getKey(SDLK_x))
    _selected = 1;
  if (input.getKey(SDLK_RETURN))
    {
      switch (_selected)
	{
	case 0 :
	  return (EDIT_MAP);
	case 1 :
	  return (RATE);
	}
    }
  return (EXTRA);
}
