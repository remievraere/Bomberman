// Started by Simon Bulcke
// Last update by Remi Evraere
//


#ifndef		BOMBERMAN_HH_
# define	BOMBERMAN_HH_

# include	<Game.hh>
# include	<Clock.hh>
# include	<Input.hh>
# include	<SdlContext.hh>
# include	<Geometry.hh>
# include	<Texture.hh>
# include	<BasicShader.hh>
# include	<Model.hh>

# include	<glm/glm.hpp>
# include	<glm/gtc/matrix_transform.hpp>

# include	<OpenGL.hh>

# include	<SFML/Audio.hpp>

# include	<iostream>
# include	<cstdlib>
# include	<fstream>
# include	<vector>
# include	<sstream>
# include	<cstdlib>
# include	<ctime>

enum		Module
  {
    //1st part
    ANIM,
    MENU,
    //2menu
    GAME,
    EXTRA,
    TOOLS,
    //3 GAME :
    NEW_GAME,
    LOAD_GAME,
    READ_SAVE,

    LOAD_MAP,
    DUAL_GAME,
    RAND_MAP,
    //3 EXTRA :
    EDIT_MAP,
    RATE,

    //4 NEW_GAME
    FREE_MODE,
    ARCADE,
    SURVIVAL,

    //special
    QUIT,
    BACK,
    ERROR,
  };

enum		Direction
  {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    STAY,
    UNDEFINED
  };

enum		Ebonus
  {
    SPEED,
    STRENGHT,
    ADDBOMB
  };

enum		EPause
  {
    PAUSE,
    BACKMENU,
    QUITGAME,
    CONTINU,
    SAVE
  };

enum		GameMode
  {
    FREE,
    SURV,
    ARCA,
  };
//Get T index
//A = Alpha
//B = Bcube
//C = Bomb
//D = Bonus
//E = Character
//F = Cube
//G = ECube
//H = Ground
//I = Ia
//J = Number
//K = Plan
//L = SkyBox

#endif		/* BOMBERMAN_HH_ */
