// Started by CLovis Masson
// Last update by Simon Bulcke
//


#ifndef			RUN_HH_
# define		RUN_HH_

# include		"GameEngine.hh"

class GameEngine;

class Camera;

class Map;

class Pause;

class Run
{
private:

  GameEngine		*_g;
  Map			*_map;
  AMenu			*_menu;
  Camera		*_cam;
  std::string		_mapPath;
  std::string		_fpname;
  std::string		_spname;
  int			_iaNb;
  int			_mapX;
  int			_mapY;
  int			_BDensity;
  int			_CDensity;
  int			_soundVol;

public:

  Run(GameEngine*, Map*, Camera*);
  ~Run();
  Module		runMenu();
  Module		runArcade();
  Module		runGameMenu();
  Module		runLoadMap();
  Module		runDualGame();
  Module		runEditMap();
  Module		runSurvival();
  Module		runNewGame();
  Module		runFreeMode();
  Module		runExtra();
  Module		runTools();
  Module		runScore();
  Module		runLoadGame();
  Module		runReadSave();
  Module		startSoloGame();
  Module		startDualGame();
  bool			isFree(float, float, std::vector <AObject *>);
  std::vector<AObject*>	deleteCube(float, float, std::vector <AObject *>);
  std::vector<AObject*>	deleteAtPos(float, float, std::vector <AObject *>);
  std::string		nameSave();
  void			setMapPath(std::string path);
  void			setFpname(std::string);
  void			setSpname(std::string);
  void			setNbIa(int);
  void			setMapX(int);
  void			setMapY(int);
  void			setBDensity(int);
  void			setCDensity(int);
  void			setSoundVol(int);
  int			getSoundVol()const;
  bool			setScreen(std::string);
  bool			showInfoPlan(std::string path, int timeout);
};

#endif /*RUN_HH_*/
