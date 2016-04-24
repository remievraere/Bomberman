// Started by Simon Bulcke
// Last update by Remi Evraere
//

#ifndef			GAMEENGINE_HH_
# define		GAMEENGINE_HH_

# include		"Bomberman.hh"
# include		"AObject.hh"
# include		"AMenu.hh"
# include		"Map.hh"
# include		"Danger.hh"
# include		"Camera.hh"
# include		"Interact.hh"
# include		"Run.hh"
# include		"Pause.hh"
# include		"Anim.hh"
# include		"./Cfunc/Readdir.hh"
# include		"./AObject/Objects.hh"
# include		"./AMenu/Menus.hh"

class Camera;

class Map;

class Run;

class Anim;

class Thread;

class GameEngine : public gdl::Game
{
public:

  GameEngine();
  ~GameEngine();
  bool			initialize();
  bool			update();
  void			draw();
  glm::vec3		setCam(glm::vec3);
  glm::vec3		getCamPos()const;
  void			refreshCam();
  Module		runGame(Module m);
  gdl::SdlContext	getContext()const;
  gdl::Clock		getClock()const;
  gdl::Input		getInput()const;
  gdl::BasicShader	getShader()const;

private:

  Run			*_run;
  Anim			*_anim;
  Camera		*_cam;
  glm::vec3		_camPos;
  gdl::SdlContext	_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  Map			*_map;
};

#endif		/* GAMEENGINE_HH_ */
