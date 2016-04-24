// Started by Remi Evraere
// Last update by Kevin Fandi
//


#include		"Pause.hh"

Pause::Pause()
{
  cursor = 0;
}

Pause::~Pause()
{
}

EPause			Pause::menuPause(Camera *cam, GameEngine *_g)
{
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  Plan			*plan;
  std::vector<Alpha*>	alpha;
  int			i;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  plan = new Plan();
  alpha.push_back(new Alpha());
  alpha.push_back(new Alpha());
  alpha.push_back(new Alpha());
  alpha.push_back(new Alpha());
  if (plan->initialize("./Graphics/Menu/pause.tga", 800, 600) == false)
    return (CONTINU);
  plan->scale(glm::vec3(1.2, 1.2, 1.2));
  context.updateInputs(input);
  if (input.getKey(SDLK_DOWN))
    {
      cursor += 1;
      if (cursor == 4)
	cursor = 0;
    }
  else if (input.getKey(SDLK_UP))
    {
      cursor -= 1;
      if (cursor == -1)
	cursor = 3;
    }
  else if (input.getKey(SDLK_RETURN))
    {
      delete plan;
      if (cursor == 0)
	return (CONTINU);
      else if (cursor == 1)
	return (SAVE);
      else if (cursor == 2)
	return (BACKMENU);
      else if (cursor = 3)
	return (QUITGAME);
    }
  i = 0;
  while (i < alpha.size())
    {
      if (i == cursor)
	{
	  switch (i)
	    {
	    case 0 :
	      {
		alpha[i]->initialize("CONTINUE", glm::vec3(23, 10,0), glm::vec3(2,2,2), glm::vec4(1, 1, 0, 1));
		break;
	      }
	    case 1 :
	      {
		alpha[i]->initialize("SAVE", glm::vec3(23, 3,0), glm::vec3(2,2,2), glm::vec4(1, 1, 0, 1));
		break;
	      }
	    case 2 :
	      {
		alpha[i]->initialize("BACK TO MENU", glm::vec3(23, -4,0), glm::vec3(2,2,2), glm::vec4(1, 1, 0, 1));
		break;
	      }
	    case 3 :
	      {
		alpha[i]->initialize("QUIT", glm::vec3(23, -11, 0), glm::vec3(2,2,2), glm::vec4(1, 1, 0, 1));
		break;
	      }
	    }
	}
      else if (i == 0)
	alpha[0]->initialize("CONTINUE", glm::vec3(23, 10,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
      else if (i == 1)
	alpha[1]->initialize("SAVE", glm::vec3(23, 3,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
      else if (i == 2)
	alpha[2]->initialize("BACK TO MENU", glm::vec3(23, -4,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
      else if (i == 3)
	alpha[3]->initialize("QUIT", glm::vec3(23, -11,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
      i++;
    }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cam->setPos(glm::vec3(0, 0, -40));
  cam->setFocus(glm::vec3(0, 0, 0));
  cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  plan->draw(shader, clock);
  i = 0;
  while (i < alpha.size())
    {
      alpha[i++]->draw(shader, clock);
    }
  shader.bind();
  context.flush();
  delete plan;
  return (PAUSE);
}

EPause			Pause::menuPauseSurvival(Camera *cam, GameEngine *_g, std::string path)
{
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  gdl::SdlContext	context;
  Plan			*plan;
  std::vector<Alpha*>	alpha;
  int			i;

  input = _g->getInput();
  clock = _g->getClock();
  shader = _g->getShader();
  context = _g->getContext();
  plan = new Plan();
  alpha.push_back(new Alpha());
  alpha.push_back(new Alpha());
  alpha.push_back(new Alpha());
  if (plan->initialize(path, 800, 600) == false)
    return (CONTINU);
  plan->scale(glm::vec3(1.2, 1.2, 1.2));
  context.updateInputs(input);
  if (input.getKey(SDLK_DOWN))
    {
      cursor += 1;
      if (cursor == 3)
	cursor = 0;
    }
  else if (input.getKey(SDLK_UP))
    {
      cursor -= 1;
      if (cursor == -1)
	cursor = 2;
    }
  else if (input.getKey(SDLK_RETURN))
    {
      delete plan;
      if (cursor == 0)
	return (CONTINU);
      else if (cursor == 1)
	return (BACKMENU);
      else if (cursor = 2)
	return (QUITGAME);
    }
  i = 0;
  while (i < alpha.size())
    {
      if (i == cursor)
	{
	  switch (i)
	    {
	    case 0 :
	      {
		alpha[i]->initialize("CONTINUE", glm::vec3(25, 7,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
		break;
	      }
	    case 1 :
	      {
		alpha[i]->initialize("BACK TO MENU", glm::vec3(25, 0,0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
		break;
	      }
	    case 2 :
	      {
		alpha[i]->initialize("QUIT", glm::vec3(25, -7, 0), glm::vec3(2,2,2), glm::vec4(1, 0, 0, 1));
		break;
	      }
	    }
	}
      else if (i == 0)
	alpha[0]->initialize("CONTINUE", glm::vec3(25, 7,0), glm::vec3(2,2,2), glm::vec4(1, 1, 1, 1));
      else if (i == 1)
	alpha[1]->initialize("BACK TO MENU", glm::vec3(25, 0,0), glm::vec3(2,2,2), glm::vec4(1, 1, 1, 1));
      else if (i == 2)
	alpha[2]->initialize("QUIT", glm::vec3(25, -7,0), glm::vec3(2,2,2), glm::vec4(1, 1, 1, 1));
      i++;
    }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cam->setPos(glm::vec3(0, 0, -40));
  cam->setFocus(glm::vec3(0, 0, 0));
  cam->setProj(glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));
  _g->refreshCam();
  plan->draw(shader, clock);
  i = 0;
  while (i < alpha.size())
    {
      alpha[i++]->draw(shader, clock);
    }
  shader.bind();
  context.flush();
  delete plan;
  return (PAUSE);
}
