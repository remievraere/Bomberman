// Started by Clovis Masson
// Last update by Simon Bulcke
//


#include	"Interact.hh"

Interact::Interact()
{
}

Interact::~Interact()
{
}

int		Interact::checkBonus(std::vector<AObject*> Elem, float x, float z)
{
  int		i = 0;

  while (i < Elem.size())
    {
      if (Elem[i]->getType() == "Bonus")
	if (Elem[i]->getPosX() == x && Elem[i]->getPosZ() == z)
	  return (i);
      i++;
    }
  return (-1);
}
