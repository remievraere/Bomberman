// Started by Simon Bulcke
// Last update by Remi Evraere
//

#ifndef			MAP_HH_
# define		MAP_HH_

# include		<cstdlib>
# include		<ctime>

# include		"Bomberman.hh"
# include		"AObject.hh"
# include		"GameEngine.hh"

# include		"./AObject/Objects.hh"

class			GameEngine;

class			Danger;

class			Interact;

class			Map
{
private:

  Danger		*_danger;
  Interact		*_interact;
  std::vector<AObject*> _Elem;
  int			_nbElem;
  int			_id;
  int			_x;
  int			_y;
  std::vector<char>	_AllowedChar;
  int			_idDraw;
  AObject		*_skybox;
  glm::vec3		_posDraw;
  std::string           _fpname;
  std::string           _spname;
  std::string		_pathground;
  GameMode		_mode;

public:

  Map(int, int, int, int, int, int, std::string, std::string,
      std::string, std::string, std::string, std::string);
  Map(std::string, int, int, std::string, std::string,
      std::string, std::string, std::string, std::string);
  Map(std::string);
  ~Map();
  void			Print();
  bool			isEmpty();
  bool			checkMap(std::string map);
  void			update(gdl::Clock clock, gdl::Input input);
  void			draw(gdl::BasicShader shader, gdl::Clock clock);
  void			drawDualScreen(gdl::BasicShader shader,
				       gdl::Clock clock);
  void			drawEdit(gdl::BasicShader shader,
				 gdl::Clock clock);
  glm::vec3		getCharPos(int id);
  int			getElemSize()const;
  AObject*		getElem(int i)const;
  AObject*		getElem(int x, int y)const;
  bool			addPlayer(int nb);
  bool			addIa(int nb);
  void			initAllowedCharInMap();
  bool			checkChar(char c)const;
  int			getCharId(int)const;
  Character*		getCharObj(int nb)const;
  Ia*			getIaObj(int nb)const;
  int			getIaSize()const;
  Direction		offense_mode(Ia*);
  Direction		defense_mode(Ia*);
  Direction		setIaMove(Ia*);
  void			setIdDraw(int id);
  bool			setCollision(glm::vec3 pos, int id, Direction d);
  void			setPosDraw(glm::vec3 pos);
  void			parsBomb();
  void			save(std::vector<AObject*>, std::string);
  void			findBomb(Bomb*);
  std::string		isAnObjects(std::vector<AObject*> Objects, int i,
				    int j)const;
  void			putBomb(Character*);
  void			putBomb(Ia*);
  bool			isId(int, AObject*);
  void			addExplosion(Bomb*);
  bool			stopExplosion(float x, float z);
  void			pickBonus(Character *);
  void			eraseOnBonus();
  void			moveBonus();
  void			saveMap(std::string path);
  float			distance(glm::vec3, glm::vec3)const;
  glm::vec3		getClosest(glm::vec3, int)const;
  int			checkDeath(Character *);
  int			checkIaDeath();
  void			stayIn();
  int			getNbPlayer()const;
  bool			parseECube(std::string line);
  bool			parseBomb(std::string line);
  bool			parseCharacter(std::string line);
  bool			parseBonus(std::string line);
  bool			parseIa(std::string line);
  void			eraseChar(Character *);
  void			setNewWave(int);
  bool			ifBomb();
  bool			ifExplosion();
  int			findPlayer(int id)const;
  Character*		getChar(int id)const;
  Ia*			getIa(int id)const;
  bool			fillBombToPlayers();
  bool			addPlayers(int nb_player, int nb_ia);
  void			setMode(GameMode);
  bool			checkSaveId(int);
  void			callScore();
};

#endif		/* MAP_HH_ */
