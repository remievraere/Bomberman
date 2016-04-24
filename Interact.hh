// Started by Clovis Masson
// Last update by Simon Bulcke
//


#ifndef			INTERACT_HH_
# define		INTERACT_HH_

# include		<cstdlib>
# include		<ctime>

# include		"Bomberman.hh"
# include		"AObject.hh"
# include		"GameEngine.hh"

# include		"./AObject/Objects.hh"

class				Interact
{
private:

public:

  Interact();
  ~Interact();
  int		checkBonus(std::vector<AObject*>, float, float);
};

#endif		/* INTERACT_HH_ */
