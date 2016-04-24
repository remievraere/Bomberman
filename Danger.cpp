// Started by Simon Bulcke
// Last update by Medhi Kolai
//


#include	"Danger.hh"

Danger::Danger()
{
}

Danger::~Danger()
{
}

void	Danger::clearBombs()
{
  _dangerPos.clear();
}

bool	Danger::isExploded(Bomb *bomb)
{
  if (bomb->getExplode() == true)
    return true;
  return false;
}

void	Danger::setDangerZone(Bomb *bomb)
{
  int		i;
  glm::vec3	pos;
  glm::vec3	tmp;

  pos = bomb->getPos();
  tmp = pos;
  _dangerPos.push_back(pos);
  for (i = 0; i < bomb->getRange(); i++)
    {
      pos.x += 1;
      _dangerPos.push_back(pos);
    }
  pos = tmp;
  for (i = 0; i < bomb->getRange(); i++)
    {
      pos.x -= 1;
      _dangerPos.push_back(pos);
    }
  pos = tmp;
  for (i = 0; i < bomb->getRange(); i++)
    {
      pos.z += 1;
      _dangerPos.push_back(pos);
    }
  pos = tmp;
  for (i = 0; i < bomb->getRange(); i++)
    {
      pos.z -= 1;
      _dangerPos.push_back(pos);
    }
}

void	Danger::pushDanger(glm::vec3 pos)
{
  _dangerPos.push_back(pos);
}

bool	Danger::isSafe(glm::vec3 pos)
{
  int	i;

  i = 0;
  while (i < _dangerPos.size())
    {
      if (pos.x >= _dangerPos[i].x - 1 && pos.x <= _dangerPos[i].x + 1 && pos.z >= _dangerPos[i].z - 1 && pos.z <= _dangerPos[i].z + 1)
	return (false);
      i++;
    }
  return true;
}
