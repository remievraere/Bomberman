// Started by Simon Bulcke
// Last update by Remi Evraere
//


#include		"GameEngine.hh"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

bool			GameEngine::initialize()
{
  _cam = new Camera();
  _anim = new Anim(this, _cam);
  _run = new Run(this, _map, _cam);

  if (!_context.start(800, 600, "Bomberman"))
    {
      printf("context_fail\n");
      return (false);
    }
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER) || !_shader.load("./shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    {
      printf("cannot load shaders\n");
      return false;
    }
  _cam->setPos(glm::vec3(0, 10, -40));
  _cam->setFocus(glm::vec3(0, 0, 0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  refreshCam();
  _shader.setUniform("projection", _cam->getProj());
  return true;
}

Module			GameEngine::runGame(Module m)
{
  sf::Music		music;

  music.setVolume(_run->getSoundVol());
  switch (m)
    {
    case ANIM :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/anim.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	return (_anim->animation());
      }
    case MENU :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/begin.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	return (_run->runMenu());
      }
    case GAME :
      {
	return (_run->runGameMenu());
      }
    case EXTRA :
      return (_run->runExtra());
    case TOOLS :
      return (_run->runTools());
    case LOAD_GAME :
      return (_run->runLoadGame());
    case SURVIVAL :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/survival.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	music.setLoop(true);
	return (_run->runSurvival());
      }
    case FREE_MODE :
      return (_run->runFreeMode());
    case ARCADE :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/arcade.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	music.setLoop(true);
	return (_run->runArcade());
      }
    case LOAD_MAP :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/game_2.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	music.setLoop(true);
	return (_run->runLoadMap());
      }
    case NEW_GAME :
      return (_run->runNewGame());
    case DUAL_GAME :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/game.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	music.setLoop(true);
	return (_run->runDualGame());
      }
    case EDIT_MAP :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/edit.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	music.setLoop(true);
	return (_run->runEditMap());
      }
    case RATE :
      return (_run->runScore());
    case READ_SAVE :
      {
	if (!music.openFromFile("./Graphics/Soundtrack/game_2.ogg"))
	  std::cout << "Error Music" << std::endl;
	music.play();
	music.setLoop(true);
	return (_run->runReadSave());
      }
    }
}

glm::vec3		GameEngine::setCam(glm::vec3 v)
{
  v.y += 5;
  v.z -= 5;
  return (v);
}

void			GameEngine::refreshCam()
{
  glm::mat4		transformation;

  _cam->setTransfo(glm::lookAt(_cam->getPos(), _cam->getFocus(), glm::vec3(0, 1, 0)));
  _shader.bind();
  _shader.setUniform("view", _cam->getTransfo());
}

bool			GameEngine::update()
{
}

void			GameEngine::draw()
{
}

gdl::SdlContext		GameEngine::getContext()const
{
  return (_context);
}

gdl::Clock		GameEngine::getClock()const
{
  return (_clock);
}

gdl::Input		GameEngine::getInput()const
{
  return (_input);
}

gdl::BasicShader	GameEngine::getShader()const
{
  return (_shader);
}
