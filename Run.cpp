// Started by CLovis Masson
// Last update by Simon Bulcke
//

#include		"Run.hh"

Run::Run(GameEngine *g, Map *map, Camera *camera)
{
  _g = g;
  _map = map;
  _cam = camera;
  _mapPath = "";
  _fpname = "";
  _spname = "";
  _iaNb = 0;
  _mapX = 0;
  _mapY = 0;
  _BDensity = 0;
  _CDensity = 0;
  _soundVol = 50;
}

Run::~Run()
{
}

Module			Run::runMenu()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runMenu" << std::endl;
  _menu = new MainMenu();
  if (_menu->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize menu" << std::endl;
      return (ERROR);
    }
  _cam->setPos(glm::vec3(0,10,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = _menu->update(clock, input)) != MENU)
	{
	  delete _menu;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _menu->draw(shader, clock);
      context.flush();
    }
}


Module			Run::runGameMenu()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  int			i;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runGameMenu" << std::endl;
  _menu = new GameMenu();
  if (_menu->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize GameMenu" << std::endl;
      delete _menu;
      return (MENU);
    }
  _cam->setPos(glm::vec3(0,10,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = _menu->update(clock, input)) != GAME)
	{
	  delete _menu;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _menu->draw(shader, clock);
      context.flush();
    }
}

Module			Run::runFreeMode()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  int			i;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runFreeMode" << std::endl;
  _menu = new FreeMode(this);
  if (_menu->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize FreeMode" << std::endl;
      delete _menu;
      return (MENU);
    }
  _cam->setPos(glm::vec3(0,0,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = _menu->update(clock, input)) != FREE_MODE)
	{
	  delete _menu;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _menu->draw(shader, clock);
      context.flush();
    }
}

Module			Run::runLoadGame()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  int			i;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runLoadGame" << std::endl;
  _menu = new LoadGame(this);
  if (_menu->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize LoadGame" << std::endl;
      delete _menu;
      return (MENU);
    }
  _cam->setPos(glm::vec3(0,0,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = _menu->update(clock, input)) != LOAD_GAME)
	{
	  delete _menu;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _menu->draw(shader, clock);
      context.flush();
    }
}

Module			Run::runNewGame()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  int			i;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runNewGame" << std::endl;
  _menu = new NewGame();
  if (_menu->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize menu" << std::endl;
       delete _menu;
      return (MENU);
    }
  _cam->setPos(glm::vec3(0,0,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = _menu->update(clock, input)) != NEW_GAME)
	{
	  delete _menu;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _menu->draw(shader, clock);
      context.flush();
    }
}

Module			Run::startSoloGame()
{
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  Alpha*		alpha;
  int			whokill;
  int			i;
  Direction		dir;
  float			tmp;
  Pause*		pause;
  EPause		p;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  if (_map->isEmpty() == true)
    {
      std::cout << "Bomberman : Can't initalize map" << std::endl;
      delete _map;
      return (MENU);
    }
  _map->setIdDraw(_map->getCharId(0));
  while (1)
    {
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
	{
	  delete _map;
	  return (QUIT);
	}
      if (input.getKey(SDLK_TAB))
	{
	  delete _map;
	  return (MENU);
	}
      context.updateClock(clock);
      context.updateInputs(input);
      _map->pickBonus(_map->getCharObj(0));
      _map->moveBonus();
      _map->stayIn();
      if ((whokill = _map->checkDeath(_map->getCharObj(0))) != -1)
        {
	  showInfoPlan("./Graphics/Game/gameover.tga", 3);
          return (MENU);
        }
      _map->checkIaDeath();
      if (input.getKey(SDLK_UP) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, UP) == true)
	_map->getCharObj(0)->moveUp(clock, input);
      if (input.getKey(SDLK_DOWN) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, DOWN) == true)
	_map->getCharObj(0)->moveDown(clock, input);
      if (input.getKey(SDLK_LEFT) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, LEFT) == true)
	_map->getCharObj(0)->moveLeft(clock, input);
      if (input.getKey(SDLK_RIGHT) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, RIGHT) == true)
	_map->getCharObj(0)->moveRight(clock, input);
      if (input.getKey(SDLK_SPACE))
	{
	  if (_map->ifBomb() == false || _map->ifExplosion() == false)
	    return (MENU);
	  _map->putBomb(_map->getCharObj(0));
	}
      if (input.getKey(SDLK_p))
	{
	  input.removeKeyInput(SDLK_p);
	  pause = new Pause();
	  while ((p = pause->menuPause(_cam, _g)) == PAUSE)
	    context.updateClock(clock);
	  switch (p)
	    {
	    case BACKMENU :
	      {
		delete _map;
		delete pause;
		return (MENU);
	      }
	    case QUITGAME :
	      {
		delete _map;
		delete pause;
		return (QUIT);
	      }
	    case SAVE :
	      {
		_map->saveMap(nameSave());
		delete _map;
		delete pause;
		return (MENU);
	      }
	    }
	}
      _map->parsBomb();
      i = 0;
      if ( _map->getIaSize() == 0 && _map->getNbPlayer() == 1)
	{
	  showInfoPlan("./Graphics/Game/youwin.tga", 3);
	  _map->callScore();
          delete _map;
	  return (MENU);
	}
      while (i < _map->getIaSize())
	{
	  dir = _map->setIaMove(_map->getIaObj(i));
	  if (dir == UNDEFINED)
	    return (MENU);
	  if (dir == UP)
	    _map->getIaObj(i)->moveUp(clock, input);
	  if (dir == DOWN)
	    _map->getIaObj(i)->moveDown(clock, input);
	  if (dir == LEFT)
	    _map->getIaObj(i)->moveLeft(clock, input);
	  if (dir == RIGHT)
	    _map->getIaObj(i)->moveRight(clock, input);
	  i++;
	}
      _map->update(clock, input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _map->draw(shader, clock);
      _cam->setTransfo(glm::lookAt(_g->setCam(_map->getCharPos(_map->getCharId(0))), _map->getCharPos(_map->getCharId(0)), glm::vec3(0, 1, 0)));
      shader.bind();
      shader.setUniform("view", _cam->getTransfo());
      context.flush();
    }
}

Module			Run::runLoadMap()
{
  if (setScreen("./Graphics/Menu/Loading.tga") == false)
      return (MENU);
  std::cout << "Bomberman : runLoadMap" << std::endl;
  if (_mapPath != "" && _fpname != "")
    _map = new Map(_mapPath, 1, _iaNb, _fpname, _spname,
		   "./Graphics/Game/ThemeSpa/Cube.tga",
		   "./Graphics/Game/ThemeSpa/SkyBox.tga",
		   "./Graphics/Game/ThemeSpa/Bcube.tga",
		   "./Graphics/Game/ThemeSpa/Ground.tga");
  else if (_mapPath == "" && _fpname != "" && _mapX > 0 && _mapY > 0)
    _map = new Map(_mapX, _mapY, _BDensity, _CDensity, 1, _iaNb, _fpname, _spname,
		   "./Graphics/Game/ThemeSpa/Cube.tga",
		   "./Graphics/Game/ThemeSpa/SkyBox.tga",
		   "./Graphics/Game/ThemeSpa/Bcube.tga",
		   "./Graphics/Game/ThemeSpa/Ground.tga");
  else
    {
      std::cout << "Bomberman : Invalid game settings" << std::endl;
      return (MENU);
    }
  return (startSoloGame());
}

Module		Run::runSurvival()
{
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  int			i;
  int			wave;
  bool			new_wave;
  Direction		dir;
  int               whokill;

  new_wave = true;
  wave = -2;
  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  if (setScreen("./Graphics/Menu/Loading.tga") == false)
    return (MENU);
  std::cout << "Bomberman : runSurvival" << std::endl;
  _map = new Map("./map/survival", 1, 0, "jon snow", "",
		 "./Graphics/Game/ThemeApo/Cube.tga",
		 "./Graphics/Game/ThemeApo/apo_sky.tga",
		 "./Graphics/Game/ThemeApo/scary_wall21.tga",
		 "./Graphics/Game/ThemeApo/lava5.tga");
  if (_map->isEmpty() == true)
    {
      std::cout << "Bomberman : Can't initialize map" << std::endl;
      delete _map;
      return (MENU);
    }
  _map->setMode(SURV);
  _map->setIdDraw(_map->getCharId(0));
  while (1)
    {
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
	{
	  delete _map;
	  return (QUIT);
	}
      if (input.getKey(SDLK_TAB))
	{
	  delete _map;
	  return (MENU);
	}
      context.updateClock(clock);
      context.updateInputs(input);
      _map->pickBonus(_map->getCharObj(0));
      _map->moveBonus();
      _map->stayIn();
      if ((whokill = _map->checkDeath(_map->getCharObj(0))) != -1)
        {
	  showInfoPlan("./Graphics/Game/gameover.tga", 3);
          delete _map;
          return (MENU);
        }
      _map->checkIaDeath();
      if (input.getKey(SDLK_UP) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, UP) == true)
	_map->getCharObj(0)->moveUp(clock, input);
      if (input.getKey(SDLK_DOWN) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, DOWN) == true)
	_map->getCharObj(0)->moveDown(clock, input);
      if (input.getKey(SDLK_LEFT) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, LEFT) == true)
	_map->getCharObj(0)->moveLeft(clock, input);
      if (input.getKey(SDLK_RIGHT) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, RIGHT) == true)
	_map->getCharObj(0)->moveRight(clock, input);
      if (input.getKey(SDLK_SPACE))
	{
	  if (_map->ifBomb() == false || _map->ifExplosion() == false)
	    return (MENU);
	  _map->putBomb(_map->getCharObj(0));
	}
      if (input.getKey(SDLK_p))
	{
	  Pause			*pause;
	  EPause		p;

	  input.removeKeyInput(SDLK_p);
	  pause = new Pause();
	  while ((p = pause->menuPauseSurvival(_cam, _g, "./Graphics/Menu/survivalpause.tga")) == PAUSE)
	    context.updateClock(clock);
	  switch (p)
	    {
	    case BACKMENU :
	      {
		delete _map;
		delete pause;
		return (MENU);
	      }
	    case QUITGAME :
	      {
		delete _map;
		delete pause;
		return (QUIT);
	      }
	    }
	}
      _map->parsBomb();
      i = 0;
      while (i < _map->getIaSize())
	{
	  dir = _map->setIaMove(_map->getIaObj(i));
	  if (dir == UNDEFINED)
	    return (MENU);
	  if (dir == UP)
	    _map->getIaObj(i)->moveUp(clock, input);
	  if (dir == DOWN)
	    _map->getIaObj(i)->moveDown(clock, input);
	  if (dir == LEFT)
	    _map->getIaObj(i)->moveLeft(clock, input);
	  if (dir == RIGHT)
	    _map->getIaObj(i)->moveRight(clock, input);
	  i++;
	}
      float t = clock.getElapsed();
      if (new_wave == true && wave > 0)
	{
	  std::stringstream ss;
	  ss << wave;
	  std::string str = ss.str();

	  std::string w = "WAVE " + str;

          Alpha *alpha = new Alpha();
          alpha->initialize(w, glm::vec3(_map->getCharObj(0)->getPosX() + 5, 2, _map->getCharObj(0)->getPosZ() + 2), glm::vec3(1, 1, 1), glm::vec4(1, 0, 0, 1));

	  while (t < 3)
	    {
	      t += clock.getElapsed();
	      alpha->draw(shader, clock);
	      context.updateClock(clock);
	      context.flush();
	    }
	  _map->setNewWave(wave);
	  new_wave = false;
	  wave++;
	}
      if (_map->getIaSize() == 0)
	new_wave = true;
      _map->update(clock, input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _map->draw(shader, clock);
      _cam->setTransfo(glm::lookAt(_g->setCam(_map->getCharPos(_map->getCharId(0))), _map->getCharPos(_map->getCharId(0)), glm::vec3(0, 1, 0)));
      shader.bind();
      shader.setUniform("view", _cam->getTransfo());
      context.flush();
      if (wave <= 0)
	wave++;
    }
}

Module			Run::runExtra()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runExtra" << std::endl;
  _menu = new ExtraMenu();
  if (_menu->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize menu" << std::endl;
      delete _menu;
      return (MENU);
    }
  _cam->setPos(glm::vec3(0, 10,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = _menu->update(clock, input)) != EXTRA)
	{
	  delete _menu;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _menu->draw(shader, clock);
      context.flush();
    }
}

Module			Run::runArcade()
{
  gdl::Clock            clock;
  gdl::Input            input;
  gdl::BasicShader      shader;
  gdl::SdlContext       context;
  int                   i;
  Direction             dir;
  int                   lvl = 1;
  int                   whokill;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  if (setScreen("./Graphics/Menu/Loading.tga") == false)
    return (MENU);
  std::cout << "Bomberman : runArcade" << std::endl;
  _map = new Map("./map/arcade1", 1, 1, _fpname, _spname,
		 "./Graphics/Game/ThemeSpa/Cube.tga",
		 "./Graphics/Game/ThemeSpa/SkyBox.tga",
		 "./Graphics/Game/ThemeSpa/Bcube.tga",
		 "./Graphics/Game/ThemeSpa/Ground.tga");
  _map->setMode(ARCA);
  if (_map->isEmpty() == true)
    {
      std::cout << "Bomberman : Can't initalize map" << std::endl;
      delete _map;
      return (MENU);
    }
  _map->setIdDraw(_map->getCharId(0));
  while (1)
    {
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
        {
          delete _map;
          return (QUIT);
        }
      if (input.getKey(SDLK_TAB))
        {
          delete _map;
          return (MENU);
        }
      context.updateClock(clock);
      context.updateInputs(input);
      _map->pickBonus(_map->getCharObj(0));
      _map->moveBonus();
      _map->stayIn();
      if ((whokill = _map->checkDeath(_map->getCharObj(0))) != -1)
        {
	  showInfoPlan("./Graphics/Game/gameover.tga", 3);
	  delete _map;
          return (MENU);
        }
      _map->checkIaDeath();
      if (_map->getIaSize() <= 0)
        {
	  if (lvl < 6)
	    showInfoPlan("./Graphics/Game/nextlevel.tga", 1);
	  else
	    {
	      showInfoPlan("./Graphics/Game/youwin.tga", 3);
	      delete _map;
	      return (MENU);
	    }
          switch (lvl)
	    {
            case 1 :
              {
                delete _map;
		_map = new Map("./map/arcade2", 1, 2, _fpname, _spname,
			       "./Graphics/Game/ThemeApo/Cube.tga",
			       "./Graphics/Game/ThemeApo/apo_sky.tga",
			       "./Graphics/Game/ThemeApo/scary_wall21.tga",
			       "./Graphics/Game/ThemeApo/lava5.tga");
		if (_map->isEmpty() == true)
		  {
		    std::cout << "Bomberman : Can't initialize map" << std::endl;
		    delete _map;
		    return (MENU);
		  }
                _map->setIdDraw(_map->getCharId(0));
                break;
              }
	    case 2 :
	      {
                delete _map;
		_map = new Map("./map/arcade3", 1, 3, _fpname, _spname,
			       "./Graphics/Game/snow/Cube.tga",
			       "./Graphics/Game/snow/Skybox.tga",
			       "./Graphics/Game/snow/Bcube.tga",
			       "./Graphics/Game/snow/Ground.tga");
		if (_map->isEmpty() == true)
		  {
		    std::cout << "Bomberman : Can't initialize map" << std::endl;
		    delete _map;
		    return (MENU);
		  }
                _map->setIdDraw(_map->getCharId(0));
                break;
	      }
	    case 3 :
	      {
                delete _map;
		_map = new Map("./map/arcade4", 1, 4, _fpname, _spname,
			       "./Graphics/Game/aqua/Cube.tga",
			       "./Graphics/Game/aqua/Skybox.tga",
			       "./Graphics/Game/aqua/Bcube.tga",
			       "./Graphics/Game/aqua/Ground.tga");
		if (_map->isEmpty() == true)
		  {
		    std::cout << "Bomberman : Can't initialize map" << std::endl;
		    delete _map;
		    return (MENU);
		  }
                _map->setIdDraw(_map->getCharId(0));
                break;
	      }
	    case 4 :
	      {
                delete _map;
		_map = new Map("./map/arcade5", 1, 5, _fpname, _spname,
			       "./Graphics/Game/space/Cube.tga",
			       "./Graphics/Game/space/Skybox.tga",
			       "./Graphics/Game/space/Bcube.tga",
			       "./Graphics/Game/space/Ground.tga");
		if (_map->isEmpty() == true)
		  {
		    std::cout << "Bomberman : Can't initialize map" << std::endl;
		    delete _map;
		    return (MENU);
		  }
                _map->setIdDraw(_map->getCharId(0));
                break;
	      }
	    case 5 :
	      {
                delete _map;
		_map = new Map("./map/arcade6", 1, 6, _fpname, _spname,
			       "./Graphics/Game/minecraft/Cube.tga",
			       "./Graphics/Game/minecraft/Skybox.tga",
			       "./Graphics/Game/minecraft/Bcube.tga",
			       "./Graphics/Game/minecraft/Ground.tga");
		if (_map->isEmpty() == true)
		  {
		    std::cout << "Bomberman : Can't initialize map" << std::endl;
		    delete _map;
		    return (MENU);
		  }
		_map->setIdDraw(_map->getCharId(0));
		break;
	      }
            }
          lvl++;
        }
      if (input.getKey(SDLK_UP) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, UP) == true)
        _map->getCharObj(0)->moveUp(clock, input);
      if (input.getKey(SDLK_DOWN) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, DOWN) == true)
        _map->getCharObj(0)->moveDown(clock, input);
      if (input.getKey(SDLK_LEFT) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, LEFT) == true)
        _map->getCharObj(0)->moveLeft(clock, input);
      if (input.getKey(SDLK_RIGHT) && _map->setCollision(_map->getCharObj(0)->getPos(), 0, RIGHT) == true)
        _map->getCharObj(0)->moveRight(clock, input);
      if (input.getKey(SDLK_SPACE))
	{
	  if (_map->ifBomb() == false || _map->ifExplosion() == false)
	    return (MENU);
	  _map->putBomb(_map->getCharObj(0));
	}
      if (input.getKey(SDLK_p))
	{
	  Pause			*pause;
	  EPause		p;

	  input.removeKeyInput(SDLK_p);
	  pause = new Pause();
	  while ((p = pause->menuPauseSurvival(_cam, _g, "./Graphics/Menu/pause.tga")) == PAUSE)
	    context.updateClock(clock);
	  switch (p)
	    {
	    case BACKMENU :
	      {
		delete _map;
		delete pause;
		return (MENU);
	      }
	    case QUITGAME :
	      {
		delete _map;
		delete pause;
		return (QUIT);
	      }
	    }
	}
      _map->parsBomb();
      i = 0;
      while (i < _map->getIaSize())
        {
          dir = _map->setIaMove(_map->getIaObj(i));
	  if (dir == UNDEFINED)
	    return (MENU);
          if (dir == UP)
            _map->getIaObj(i)->moveUp(clock, input);
          if (dir == DOWN)
            _map->getIaObj(i)->moveDown(clock, input);
          if (dir == LEFT)
            _map->getIaObj(i)->moveLeft(clock, input);
          if (dir == RIGHT)
            _map->getIaObj(i)->moveRight(clock, input);
          i++;
        }
      _map->update(clock, input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _map->draw(shader, clock);
      _cam->setTransfo(glm::lookAt(_g->setCam(_map->getCharPos(_map->getCharId(0))), _map->getCharPos(_map->getCharId(0)), glm::vec3(0, 1, 0)));
      shader.bind();
      shader.setUniform("view", _cam->getTransfo());
      context.flush();
    }
}

Module		Run::runScore()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  Score			*score;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runScore" << std::endl;
  score = new Score();
  if (score->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize menu" << std::endl;
      delete score;
      return (ERROR);
    }
  _cam->setPos(glm::vec3(0,0,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  score->saveScore();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = score->update(clock, input)) != RATE)
	{
	  delete score;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      score->draw(shader, clock);
      context.flush();
    }
}

Module		Run::runReadSave()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  if (setScreen("./Graphics/Menu/Loading.tga") == false)
    return (MENU);
  std::cout << "Bomberman : runReadSave" << std::endl;
  _map = new Map("./save/"+_mapPath);
  if (_map->getNbPlayer() == 1)
    startSoloGame();
  else if (_map->getNbPlayer() == 2)
    startDualGame();
  else
    std::cout << "Bomberman : Invalid savefile" << std::endl;
  return (MENU);
}

Module			Run::startDualGame()
{
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  Alpha*		alpha;
  Direction		dir;
  int			i;
  int			whokill;
  float			tmp;
  Pause			*pause;
  EPause		p;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  if (_map->isEmpty() == true)
    {
      std::cout << "Bomberman : Can't initalize map" << std::endl;
      delete _map;
      return (MENU);
    }
  while (1)
    {
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
	{
	  delete _map;
	  return (QUIT);
	}
      if (input.getKey(SDLK_TAB))
	{
	  glViewport(0, 0, 800, 600);
	  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
	  shader.setUniform("projection", _cam->getProj());
	  delete _map;
	  return (MENU);
	}
      context.updateClock(clock);
      context.updateInputs(input);
      _map->pickBonus(_map->getCharObj(0));
      _map->pickBonus(_map->getCharObj(1));
      _map->moveBonus();
      _map->stayIn();
      if ((whokill = _map->checkDeath(_map->getCharObj(0))) != -1)
	{
	  glViewport(0, 0, 800, 600);
	  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
	  shader.setUniform("projection", _cam->getProj());
	  _map->eraseChar(_map->getCharObj(0));
	  showInfoPlan("./Graphics/Game/switch.tga", 5);
	  return (startSoloGame());
	}
      if ((whokill = _map->checkDeath(_map->getCharObj(1))) != -1)
	{
	  glViewport(0, 0, 800, 600);
	  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
	  shader.setUniform("projection", _cam->getProj());
	  _map->eraseChar(_map->getCharObj(1));
	  showInfoPlan("./Graphics/Game/switch.tga", 5);
	  return (startSoloGame());
	}
      _map->checkIaDeath();
      if (input.getKey(SDLK_UP) && _map->setCollision(_map->getCharObj(1)->getPos(), _map->getCharObj(0)->getId(), UP) == true)
	_map->getCharObj(1)->moveUp(clock, input);
      if (input.getKey(SDLK_DOWN) && _map->setCollision(_map->getCharObj(1)->getPos(), _map->getCharObj(0)->getId(), DOWN) == true)
	_map->getCharObj(1)->moveDown(clock, input);
      if (input.getKey(SDLK_LEFT) && _map->setCollision(_map->getCharObj(1)->getPos(), _map->getCharObj(0)->getId(), LEFT) == true)
	_map->getCharObj(1)->moveLeft(clock, input);
      if (input.getKey(SDLK_RIGHT) && _map->setCollision(_map->getCharObj(1)->getPos(), _map->getCharObj(0)->getId(), RIGHT) == true)
	_map->getCharObj(1)->moveRight(clock, input);
      if (input.getKey(SDLK_SPACE))
	{
	  if (_map->ifBomb() == false || _map->ifExplosion() == false)
	    return (MENU);
	  _map->putBomb(_map->getCharObj(1));
	}
      if (input.getKey(SDLK_z) && _map->setCollision(_map->getCharObj(0)->getPos(), _map->getCharObj(1)->getId(), UP) == true)
	_map->getCharObj(0)->moveUp(clock, input);
      if (input.getKey(SDLK_s) && _map->setCollision(_map->getCharObj(0)->getPos(), _map->getCharObj(1)->getId(), DOWN) == true)
	_map->getCharObj(0)->moveDown(clock, input);
      if (input.getKey(SDLK_q) && _map->setCollision(_map->getCharObj(0)->getPos(), _map->getCharObj(1)->getId(), LEFT) == true)
	_map->getCharObj(0)->moveLeft(clock, input);
      if (input.getKey(SDLK_d) && _map->setCollision(_map->getCharObj(0)->getPos(), _map->getCharObj(1)->getId(), RIGHT) == true)
	_map->getCharObj(0)->moveRight(clock, input);
      if (input.getKey(SDLK_x))
	{
	  if (_map->ifBomb() == false || _map->ifExplosion() == false)
	    return (MENU);
	  _map->putBomb(_map->getCharObj(0));
	}
      if (input.getKey(SDLK_p))
	{
	  input.removeKeyInput(SDLK_p);
	  glViewport(0, 0, 800, 600);
	  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
	  shader.setUniform("projection", _cam->getProj());
	  pause = new Pause();
	  while ((p = pause->menuPause(_cam, _g)) == PAUSE)
	    context.updateClock(clock);
	  switch (p)
	    {
	    case BACKMENU :
	      {
		delete _map;
		delete pause;
		return (MENU);
	      }
	    case QUITGAME :
	      {
		delete _map;
		delete pause;
		return (QUIT);
	      }
	    case SAVE :
	      {
		_map->saveMap(nameSave());
		delete _map;
		delete pause;
		return (MENU);
	      }
	    }
	}
      _map->parsBomb();
      i = 0;
      while (i < _map->getIaSize())
	{
	  dir = _map->setIaMove(_map->getIaObj(i));
	  if (dir == UNDEFINED)
	    return (MENU);
	  if (dir == UP)
	    _map->getIaObj(i)->moveUp(clock, input);
	  if (dir == DOWN)
	    _map->getIaObj(i)->moveDown(clock, input);
	  if (dir == LEFT)
	    _map->getIaObj(i)->moveLeft(clock, input);
	  if (dir == RIGHT)
	    _map->getIaObj(i)->moveRight(clock, input);
	  i++;
	}
      _cam->setProj(glm::perspective(60.0f, 400.0f / 600.0f, 0.1f, 10000.0f));
      _map->update(clock, input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _map->setIdDraw(_map->getCharId(1));
      _map->drawDualScreen(shader, clock);
      glViewport(0, 0, 400, 600);
      _cam->setTransfo(glm::lookAt(_g->setCam(_map->getCharPos(_map->getCharId(0))), _map->getCharPos(_map->getCharId(0)), glm::vec3(0, 1, 0)));
      shader.bind();
      shader.setUniform("view", _cam->getTransfo());
      shader.setUniform("projection", _cam->getProj());
      _map->setIdDraw(_map->getCharId(0));
      _map->drawDualScreen(shader, clock);
      glViewport(400, 0, 400, 600);
      _cam->setTransfo(glm::lookAt(_g->setCam(_map->getCharPos(_map->getCharId(1))), _map->getCharPos(_map->getCharId(1)), glm::vec3(0, 1, 0)));
      shader.bind();
      shader.setUniform("view", _cam->getTransfo());
      shader.setUniform("projection", _cam->getProj());
      context.flush();
    }
}

Module			Run::runDualGame()
{
  if (setScreen("./Graphics/Menu/Loading.tga") == false)
    return (MENU);
  std::cout << "Bomberman : runDualMap" << std::endl;
  if (_mapPath != "" && _fpname != "" && _spname != "")
    _map = new Map(_mapPath, 2, _iaNb, _fpname, _spname,
		   "./Graphics/Game/ThemeSpa/Cube.tga",
		   "./Graphics/Game/ThemeSpa/SkyBox.tga",
		   "./Graphics/Game/ThemeSpa/Bcube.tga",
		   "./Graphics/Game/ThemeSpa/Ground.tga");
  else if (_mapPath == "" && _fpname != "" && _spname != "" && _mapX != 0 && _mapY != 0)
    _map = new Map(_mapX, _mapY, _BDensity, _CDensity, 2, _iaNb, _fpname, _spname,
		   "./Graphics/Game/ThemeSpa/Cube.tga",
		   "./Graphics/Game/ThemeSpa/SkyBox.tga",
		   "./Graphics/Game/ThemeSpa/Bcube.tga",
		   "./Graphics/Game/ThemeSpa/Ground.tga");
  else
    {
      std::cout << "Bomberman : Invalid game settings" << std::endl;
      return (MENU);
    }
  return (startDualGame());
}

Module			Run::runEditMap()
{
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  gdl::Geometry		geo;
  std::vector<AObject*>	editObjects;
  std::vector<AObject*>	Objects;
  std::vector<Alpha*>	write;
  glm::vec3		cam;
  AObject*		cube;
  AObject*		select_bcube;
  AObject*		select_cube;
  AObject*		putcube;
  Ground		*ground;
  int			i;
  int			j;
  int			k;
  int			tmp_i;
  int			tmp_j;
  int			x;
  int			y;
  int			z;
  int			selected;
  AObject*		menuBottom;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  selected = 0;
  std::cout << "Bomberman : runEditMap" << std::endl;
  i = 10;
  j = 10;
  _map = new Map(i, j, 0, 0, 0, 0, _fpname, _spname,
		 "./Graphics/Game/ThemeSpa/Cube.tga",
		 "./Graphics/Game/ThemeSpa/SkyBox.tga",
		 "./Graphics/Game/ThemeSpa/Bcube.tga",
		 "./Graphics/Game/ThemeSpa/Ground.tga");
  cam.x = 0;
  cam.y = 3;
  cam.z = 0;
  cube = new Cube(0, 3, 0);
  menuBottom = new Plan();
  if (((Plan*)menuBottom)->initialize("./Graphics/Menu/Plan.tga") == false)
    {
      std::cout << "Bomberman : Cannot initialize plan" << std::endl;
      delete _map;
      return (MENU);
    }
  menuBottom->scale(glm::vec3(10000, 10000, 10000));
  editObjects.push_back(menuBottom);
  if (static_cast<Cube*>(cube)->initialize("./Graphics/Game/ThemeSpa/Cube.tga") == false)
    {
      std::cout << "Bomberman : Can't initialize Cube" << std::endl;
      delete _map;
      return (EXTRA);
    }
  Objects.push_back(cube);
  x = cam.x;
  y = 3;
  z = cam.z;
  select_bcube = new Bcube(19, 0, -10);
  if (static_cast<Bcube*>(select_bcube)->initialize("./Graphics/Game/ThemeSpa/Bcube.tga") == false)
    {
      std::cout << "Bomberman : Can't initialize Bcube" << std::endl;
      delete _map;
      return (EXTRA);
    }
  select_bcube->scale(glm::vec3(3, 3, 3));
  editObjects.push_back(select_bcube);

  select_cube = new Cube(19, 5, -10);
  if (static_cast<Cube*>(select_cube)->initialize("./Graphics/Game/ThemeSpa/Cube.tga") == false)
    {
      std::cout << "Bomberman : Can't initialize Cube" << std::endl;
      delete _map;
      return (EXTRA);
    }
  select_cube->scale(glm::vec3(3, 3, 3));
  editObjects.push_back(select_cube);
  ground = new Ground();
  ground->setColor(glm::vec4(1, 0, 0, 1));
  if (static_cast<Ground*>(ground)->initialize("./Graphics/Game/ThemeSpa/Ground.tga") == false)
    return (MENU);
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
	{
	  k = 0;
	  while (k < editObjects.size())
	    delete editObjects[k++];
	  editObjects.clear();
	  delete _map;
	  return (QUIT);
	}
      if (input.getKey(SDLK_TAB))
	{
	  k = 0;
	  while (k < editObjects.size())
	    delete editObjects[k++];
	  editObjects.clear();
	  delete _map;
	  glViewport(0, 0, 800, 600);
	  return (MENU);
	}
      if (input.getKey(SDLK_d)) //Augmente lageur
	{
	  i++;
	  delete _map;
	  input.removeKeyInput(SDLK_d);
	  _map = new Map(i, j, 0, 0, 0, 0, _fpname, _spname,
			 "./Graphics/Game/ThemeSpa/Cube.tga",
			 "./Graphics/Game/ThemeSpa/SkyBox.tga",
			 "./Graphics/Game/ThemeSpa/Bcube.tga",
			 "./Graphics/Game/ThemeSpa/Ground.tga");
	}
      if (input.getKey(SDLK_q) && i > 3)
	{
	  i--;
	  delete _map;
	  Objects = deleteCube(i, j, Objects);
	  input.removeKeyInput(SDLK_q);
	  _map = new Map(i, j, 0, 0, 0, 0, _fpname, _spname,
			 "./Graphics/Game/ThemeSpa/Cube.tga",
			 "./Graphics/Game/ThemeSpa/SkyBox.tga",
			 "./Graphics/Game/ThemeSpa/Bcube.tga",
			 "./Graphics/Game/ThemeSpa/Ground.tga");
	}
      if (input.getKey(SDLK_s))
	{
	  j++;
	  delete _map;
	  input.removeKeyInput(SDLK_s);
	  _map = new Map(i, j, 0, 0, 0, 0, _fpname, _spname,
			 "./Graphics/Game/ThemeSpa/Cube.tga",
			 "./Graphics/Game/ThemeSpa/SkyBox.tga",
			 "./Graphics/Game/ThemeSpa/Bcube.tga",
			 "./Graphics/Game/ThemeSpa/Ground.tga");
	}
      if (input.getKey(SDLK_z) && j > 3)
	{
	  j--;
	  delete _map;
	  Objects = deleteCube(i, j, Objects);
	  input.removeKeyInput(SDLK_z);
	  _map = new Map(i, j, 0, 0, 0, 0, _fpname, _spname,
			 "./Graphics/Game/ThemeSpa/Cube.tga",
			 "./Graphics/Game/ThemeSpa/SkyBox.tga",
			 "./Graphics/Game/ThemeSpa/Bcube.tga",
			 "./Graphics/Game/ThemeSpa/Ground.tga");
	}

      if (input.getKey(SDLK_RIGHT))
	{
	  x--;
	  cube->translate(glm::vec3(-1, 0, 0));
	  cam.x = cube->getPosX();
	  cam.y = cube->getPosY();
	  cam.z = cube->getPosZ();
	  input.removeKeyInput(SDLK_RIGHT);
	}
      if (input.getKey(SDLK_LEFT))
	{
	  x++;
	  cube->translate(glm::vec3(1, 0, 0));
	  cam.x = cube->getPosX();
	  cam.y = cube->getPosY();
	  cam.z = cube->getPosZ();
	  input.removeKeyInput(SDLK_LEFT);
	}
      if (input.getKey(SDLK_DOWN))
	{
	  z--;
	  cube->translate(glm::vec3(0, 0, -1));
	  cam.x = cube->getPosX();
	  cam.y = cube->getPosY();
	  cam.z = cube->getPosZ();
	  input.removeKeyInput(SDLK_DOWN);
	}
      if (input.getKey(SDLK_UP))
	{
	  z++;
	  cube->translate(glm::vec3(0, 0, 1));
	  cam.x = cube->getPosX();
	  cam.y = cube->getPosY();
	  cam.z = cube->getPosZ();
	  input.removeKeyInput(SDLK_UP);
	}
      if (input.getKey(SDLK_SPACE))
	{
	  input.removeKeyInput(SDLK_SPACE);
	  if ((x < -1 && x > -i + 2) && (z < -1 && z > -j + 2))
	    {
	      if (isFree(x, z, Objects) == false)
		{
		  if (selected == 0)
		    {
		      putcube = new Cube(cube->getPosX(), cube->getPosY() - 3, cube->getPosZ());
		      if (static_cast<Cube*>(putcube)->initialize("./Graphics/Game/ThemeSpa/Cube.tga") == false)
			return (MENU);
		      Objects.push_back(putcube);
		    }
		  else
		    {
		      putcube = new Bcube(cube->getPosX(), cube->getPosY() - 3, cube->getPosZ());
		      if (static_cast<Bcube*>(putcube)->initialize("./Graphics/Game/ThemeSpa/Bcube.tga") == false)
			return (MENU);
		      Objects.push_back(putcube);
		    }
		}
	      else
		Objects = deleteAtPos(x, z, Objects);
	    }
	}
      if (input.getKey(SDLK_RETURN))
	{
	  input.removeKeyInput(SDLK_RETURN);
	  if (selected == 0)
	    {
	      cube = new Bcube(x, y, z);
	      if (static_cast<Bcube*>(cube)->initialize("./Graphics/Game/ThemeSpa/Bcube.tga") == false)
		{
		  delete _map;
		  return (MENU);
		}
	      selected += 1;
	    }
	  else
	    {
	      cube = new Cube(cube->getPosX(), cube->getPosY(), cube->getPosZ());
	      if (static_cast<Cube*>(cube)->initialize("./Graphics/Game/ThemeSpa/Cube.tga") == false)
		{
		  delete _map;
		  return (MENU);
		}
	      selected = 0;
	    }
	  Objects.erase(Objects.begin());
	  Objects.insert(Objects.begin(), cube);
	}
      if (input.getKey(SDLK_v))
	{
	  k = 0;
	  while (k < editObjects.size())
	    delete editObjects[k++];
	  editObjects.clear();
	  std::string path;
	  path = nameSave();
	  if (path == "quit")
	    return (QUIT);
	  else if (path == "menu")
	    return (MENU);
	  _map->save(Objects, path);
	  glViewport(0, 0, 800, 600);
	  return (MENU);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      if (selected == 1)
	editObjects[1]->rotate(glm::vec3(0, 1, 0), 0.5);
      else
	editObjects[2]->rotate(glm::vec3(0, 1, 0), 0.5);

      glViewport(0, 100, 650, 600);
      _cam->setTransfo(glm::lookAt(_g->setCam(cam), cam, glm::vec3(0, 1, 0)));
      shader.setUniform("view", _cam->getTransfo());
      k = 0;
      while (k < Objects.size())
	Objects[k++]->update(clock, input);
      _map->update(clock, input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if ((x < -1 && x > -i + 2) && (z < -1 && z > -j + 2))
	{
	  ground->setPos(glm::vec3(x, -1, z));
	  ground->draw(shader, clock);
	}
      k = 0;
      while (k < Objects.size())
	Objects[k++]->draw(shader, clock);
      _map->setPosDraw(glm::vec3(cube->getPosX(), cube->getPosY(), cube->getPosZ()));
      _map->drawEdit(shader, clock);
      glViewport(0, 0, 800, 100);
      _cam->setPos(glm::vec3(0, 0, -40));
      _cam->setFocus(glm::vec3(0, 0, 0));
      _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
      _g->refreshCam();
      shader.bind();
      shader.setUniform("view", _cam->getTransfo());
      editObjects[0]->draw(shader, clock);
      glViewport(650, 0, 800, 600);
      _cam->setPos(glm::vec3(0, 0, -40));
      _cam->setFocus(glm::vec3(0, 0, 0));
      _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
      _g->refreshCam();
      shader.bind();
      shader.setUniform("view", _cam->getTransfo());
      k = editObjects.size() - 1;
      while (k >= 0)
	editObjects[k--]->draw(shader, clock);
      context.flush();
    }
}

Module			Run::runTools()
{
  Module		main;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  std::cout << "Bomberman : runToolsMenu" << std::endl;
  _menu = new ToolsMenu(this);
  if (_menu->initialize() == false)
    {
      std::cout << "Bomberman : Can't initialize menu" << std::endl;
      delete _menu;
      return (ERROR);
    }
  _cam->setPos(glm::vec3(0,0,-40));
  _cam->setFocus(glm::vec3(0,0,0));
  _cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  while (1)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      if ((main = _menu->update(clock, input)) != TOOLS)
	{
	  delete _menu;
	  return (main);
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      _menu->draw(shader, clock);
      context.flush();
    }
}

std::vector<AObject*>	Run::deleteCube(float x, float z,
					std::vector <AObject*> Objects)
{
  size_t		i;

  i = 0;
  while (i < Objects.size())
    {
      if ((Objects[i]->getPosX() <= (-x + 2) || Objects[i]->getPosZ() <= (-z + 2)) && Objects[i]->getPosY() != 3)
	if (Objects.size() > 0)
	  {
	    delete Objects[i];
	    Objects.erase(Objects.begin() + i--);
	  }
      i++;
    }
  return (Objects);
}

std::vector<AObject*>	Run::deleteAtPos(float x, float z,
					 std::vector<AObject*> Objects)
{
  size_t		i;

  i = 0;
  while (i < Objects.size())
    {
      if ((Objects[i]->getPosX() == x && Objects[i]->getPosZ() == z) && Objects[i]->getPosY() != 3)
	{
	  Objects.erase(Objects.begin() + i);
	}
      i++;
    }
  return (Objects);
}

bool			Run::isFree(float x, float z,
				    std::vector<AObject*> Objects)
{
  size_t		i;

  i = 0;
  while (i < Objects.size())
    {
      if (x == Objects[i]->getPosX() && z == Objects[i]->getPosZ() && Objects[i]->getPosY() == 0)
	return (true);
      i++;
    }
  return (false);
}

std::string		Run::nameSave()
{
  std::string		path;
  gdl::Input		input;
  gdl::SdlContext	context;
  bool			boucle;
  Plan			*plan;
  Alpha			*alpha;
  Alpha			*alpha1;
  gdl::BasicShader	shader;
  gdl::Clock		clock;
  int			keycode;

  clock = _g->getClock();
  shader = _g->getShader();
  plan = new Plan();
  alpha = new Alpha();
  alpha1 = new Alpha();
  if (plan->initialize("./Graphics/Menu/Background.tga") == false)
    return ("Default_Save");
  plan->scale(glm::vec3(10000, 10000, 10000));
  input = _g->getInput();
  context = _g->getContext();
  boucle = true;
  while (boucle == true)
    {
      glViewport(0, 0, 800, 600);
      context.updateInputs(input);
      alpha->initialize("Enter the savename", glm::vec3(23, 10,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
      alpha1->initialize(path, glm::vec3(23, 3,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
      keycode = 'a';
      while (keycode <= 'z')
	{
	  if (input.getKey(keycode))
	    {
	      path += keycode;
	      input.removeKeyInput(keycode);
	    }
	  keycode++;
	}
      if (input.getKey(SDLK_BACKSPACE))
	{
	  input.removeKeyInput(SDLK_BACKSPACE);
	  path = path.substr(0, path.length() - 1);
	}
      if (input.getKey(SDLK_RETURN) && path != "")
	{
	  boucle = false;
	  input.removeKeyInput(SDLK_RETURN);
	}
      if (input.getKey(SDLK_ESCAPE))
	{
	  return ("quit");
	}
      if (input.getKey(SDLK_TAB))
	{
	  return ("menu");
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      plan->draw(shader, clock);
      alpha->draw(shader, clock);
      alpha1->draw(shader, clock);
      shader.bind();
      context.flush();
    }
  return (path);
}

void			Run::setMapPath(std::string path)
{
  _mapPath = path;
}

void			Run::setFpname(std::string name)
{
  _fpname = name;
}

void			Run::setSpname(std::string name)
{
  _spname = name;
}

void			Run::setNbIa(int nb)
{
  if (nb < 0)
    nb = 0;
  _iaNb = nb;
}

void			Run::setMapX(int x)
{
  _mapX = x;
}

void			Run::setMapY(int y)
{
  _mapY = y;
}

void			Run::setBDensity(int d)
{
  _BDensity = d;
}

void			Run::setCDensity(int d)
{
  _CDensity = d;
}

int			Run::getSoundVol()const
{
  return (_soundVol);
}

void			Run::setSoundVol(int vol)
{
  _soundVol = vol;
}

bool			Run::setScreen(std::string path)
{
  gdl::Clock		clock;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  Plan			*load;

  load = new Plan();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  if (load->initialize(path, 800, 600) == false)
    {
      std::cout << "Bomberman : Cannot load " << path << std::endl;
      return (false);
    }
  load->scale(glm::vec3(1.2, 1.2, 1.2));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  load->draw(shader, clock);
  shader.bind();
  shader.setUniform("view", _cam->getTransfo());
  context.flush();
  return (true);
}

bool			Run::showInfoPlan(std::string path, int timeout)
{
  gdl::Clock            clock;
  gdl::Input            input;
  gdl::BasicShader      shader;
  gdl::SdlContext       context;
  Plan			*go;
  glm::vec3 pos;
  Character*		perso;
  int			id;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  go = new Plan();
  if (go->initialize(path, 800, 600) == false)
    {
      std::cout << "Bomberman : Cannot load " << path << std::endl;
      return (false);
    }
  go->scale(glm::vec3(0.04, 0.04, 0.04));
  go->setRotation(glm::vec3(1, 0, 0), 45);
  pos = _map->getCharPos(_map->getCharObj(0)->getId());
  if (pos.x == -1 && pos.y == -1 && pos.z == -1)
    return (false);
  pos.y += 4;
  pos.z -= 4;
  go->setPos(pos);
  go->draw(shader, clock);
  shader.bind();
  shader.setUniform("view", _cam->getTransfo());
  context.flush();
  float tmp = clock.getElapsed();
  while (tmp < timeout)
    {
      context.updateClock(clock);
      context.updateInputs(input);
      tmp += clock.getElapsed();
      go->draw(shader, clock);
      shader.bind();
      context.flush();
    }
  return (true);
}
