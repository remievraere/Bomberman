//
// Anim.hh for Anim in /home/fandi_k/Projets/cpp_bomberman
// 
// Made by kevin fandi
// Login   <fandi_k@epitech.net>
// 
// Started on  Wed Jun  4 14:03:57 2014 kevin fandi
// Last update Mon Jun  9 17:16:16 2014 kevin fandi
//

#ifndef ANIM_HH_
# define ANIM_HH_

# include <sstream>
# include "GameEngine.hh"

class GameEngine;

class Menu;

class Camera;

class Anim
{
private:

  GameEngine	*_g;
  Camera	*_cam;

public:
  Anim(GameEngine*, Camera*);
  ~Anim();
  Module		animation();
};

#endif /*ANIM_HH_*/
