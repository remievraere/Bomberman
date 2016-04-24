// Started by Simon Bulcke
// Last update by Medhi Kolai
//


#ifndef			DANGER_HH_
# define		DANGER_HH_

# include		<cstdlib>
# include		<ctime>

# include		"Bomberman.hh"
# include		"AObject.hh"
# include		"GameEngine.hh"

# include		"./AObject/Objects.hh"

class				Danger
{
private:

  std::vector<glm::vec3>	_dangerPos;
public:

  Danger();
  ~Danger();
  void		pushDanger(glm::vec3);
  void		setDangerZone(Bomb *bomb);
  void		clearBombs();
  bool		isSafe(glm::vec3);
  bool		isExploded(Bomb*);
};

#endif		/* DANGER_HH_ */
