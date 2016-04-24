// Started by Remi Evraere
// Last update by Medhi Kolai
//

#include	"Score.hh"

Score::Score()
{
  _selected = 0;
}

Score::~Score()
{
}

bool		Score::initialize()
{
  _background = new Plan();
  if (((Plan*)_background)->initialize("./Graphics/Menu/rates.tga", 800, 600) == false)
    return (false);
  _background->scale(glm::vec3(1.2, 1.2, 1.2));
  return (true);
}

void		Score::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  Alpha		*write = new Alpha();
  Number	*nb = new Number();

  _background->draw(shader, clock);
  int		i;
  int		j;
  int		better;
  int		max_score;
  int		old_best_score;
  std::vector<std::string>	still_in_list;

  i = 0;
  while (i < 5 && i < _name.size())
    {
      j = 0;
      better = 0;
      max_score = -51;
      old_best_score = 100001;
      while (j < _name.size())
  	{
  	  if (_score[j] > max_score && _score[j] < old_best_score)
  	    {
  	      int	k = 0;
  	      bool	can = true;
  	      while (k < still_in_list.size())
  		{
  		  if (_name[j] == still_in_list[k])
  		    can = false;
  		  k++;
  		}
  	      if (can == true)
  		{
  		  max_score = _score[j];
  		  better = j;
  		}
  	    }
	  j++;
  	}
      old_best_score = max_score;
      i++;
      still_in_list.push_back(_name[better]);
      write->initialize(_name[better], glm::vec3(23, 17 - (7 * i), 0), glm::vec3(2, 2, 2), glm::vec4(1, 1, 1, 1));
      nb->initialize(_score[better], glm::vec3(-15, 17 - (7 * i), 0), glm::vec3(2, 2, 2), glm::vec4(1, 1, 1, 1));
      write->draw(shader, clock);
      nb->draw(shader, clock);
    }
}


Module		Score::update(gdl::Clock const &clock, gdl::Input &input)
{
  if(input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return (QUIT);
  if (input.getKey(SDLK_TAB))
    return (MENU);
  return (RATE);
}

void		Score::bestScore(std::vector<AObject*> Elem)
{
  int		i = 0;
  int		j;
  std::vector<int>	stock;
  std::string	test;

  saveScore();
  std::ofstream file("score.txt", std::ios::out | std::ofstream::trunc);
  if (file)
    {
      while (i < Elem.size())
	{
	  if (Elem[i]->getType() == "Character")
	    {
	      while (j < _name.size())
		{
		  if (_name[j] == static_cast<Character*>(Elem[i])->getName())
		    if (_score[j] >= static_cast<Character*>(Elem[i])->getScore())
		      {
			file << static_cast<Character*>(Elem[i])->getName();
			file << "   ";
			file << _score[j];
			file << '\n';
			stock.push_back(j);
			j = _name.size();
		      }
		  j++;
		}
	      if (stock.size() == 0)
		{
		  test = static_cast<Character*>(Elem[i])->getName();
		  file << static_cast<Character*>(Elem[i])->getName();
		  file << "   ";
		  file << static_cast<Character*>(Elem[i])->getScore();
		  file << '\n';
		}
	    }
	  i++;
	}
    }
  bool tmp;
  i = 0;
  while (i < _name.size())
    {
      tmp = true;
      j = 0;
      while (j < stock.size())
	{
	  if (i == stock[j])
	    tmp = false;
	  j++;
	}
      if (tmp == true && test != _name[i])
	{
	  file << _name[i];
	  file << "   ";
	  file << _score[i];
	  file << '\n';
	}
      i++;
    }
}

void		Score::saveScore()
{
  std::fstream	file;
  std::string	line;
  std::size_t	found;
  int		i = 0;

  try
    {
      file.open("score.txt", std::fstream::in);
      while (file.good())
	{
	  std::getline(file, line);
	  found = line.find("   ");
	  if (found != std::string::npos && found != 0)
	    {
	      _name.push_back(line.substr(0, found));
	      std::istringstream buffer(line.substr(found + 3, line.size()));
	      int value;
	      buffer >> value;
	      if (value > 100000 || value < -50)
		{
		  _name.erase(_name.begin() + i);
		  throw "Stop trying to cheat in score";
		}
	      else
		_score.push_back(value);
	      if (_name[i].size() <= 0)
		{
		  _name.erase(_name.begin() + i);
		  _score.erase(_score.begin() + i);
		}
	      i++;
	    }
	  if (_name.size() != _score.size())
	    throw "Bomberman";
	}
      file.close();
    }
  catch (std::ifstream::failure e)
    {
      std::cerr << "Bomberman : Exception " << std::endl;
    }
  catch (const char *str)
    {
      std::cerr << str << std::endl;
    }
}
