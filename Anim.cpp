// Started by Kevin Fandi
// Last update by Kevin Fandi
//


#include		"Anim.hh"

Anim::Anim(GameEngine *g, Camera *camera)
{
  _g = g;
  _cam = camera;
}

Anim::~Anim()
{
}

Module			Anim::animation()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  int			i;
  AObject*		skybox;
  AObject*		bomb;
  AObject*		texani;

  i = 0;
  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : Animation" << std::endl;
  skybox = new SkyBox();
  if (((SkyBox *)skybox)->initialize(100, glm::vec3(0, 0, 0), "./Graphics/Menu/Anim/Anim1.tga") == false)
    {
      std::cout << "Bomberman : Can't initialize the skyBox" << std::endl;
      return (ERROR);
    }
  bomb = new Bomb(1, 0, 1);
  if (((Bomb*)bomb)->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize the bomb" << std::endl;
      return (ERROR);
    }
  bomb->setPos(glm::vec3(0, -24, 0));
  texani = new TexAni(1, 5, 1);
  if (((TexAni*)texani)->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize TexAni" << std::endl;
      return (ERROR);
    }
  _cam->setPos(glm::vec3(0,2,-2));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (static_cast<Bomb*>(bomb)->getExplode() == false)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
	return (QUIT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      skybox->draw(shader, clock);
      bomb->draw(shader, clock);
      bomb->update(clock, input);
      context.flush();
      if (static_cast<Bomb*>(bomb)->getTime() > 0.01 && static_cast<Bomb*>(bomb)->getTime() < 0.42)
	if (bomb->getPosY() != 0)
	  bomb->setPos(glm::vec3(0, bomb->getPosY() + 1, 0));
    }
  while (static_cast<TexAni*>(texani)->getExplode() == false)
    {
      _cam->setPos(glm::vec3(0,0,-1));
      _cam->setFocus(glm::vec3(0,0,0));
      _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
      _g->refreshCam();
      context.updateClock(clock);
      context.updateInputs(input);
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
	return (QUIT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      skybox->draw(shader, clock);
      texani->setPos(glm::vec3(0, 0, -0.85));
      texani->draw(shader, clock);
      texani->update(clock, input);
      context.flush();
    }
  delete bomb;
  return (MENU);
}
