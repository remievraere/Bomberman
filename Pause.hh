// Started by Remi Evraere
// Last update by Kevin Fandi
//


#ifndef			PAUSE_HH_
# define		PAUSE_HH_

# include		"Bomberman.hh"
# include		"AObject.hh"
# include		"GameEngine.hh"
# include		"./AObject/Objects.hh"

class Pause
{
private:

  int			cursor;

public:
  Pause();
  ~Pause();
  EPause		menuPause(Camera *, GameEngine *);
  EPause		menuPauseSurvival(Camera *, GameEngine *, std::string);
};

#endif			/* PAUSE_HH_ */
