// Started by Simon Bulcke
// Last update by Remi Evraere
//


#include	"AObject.hh"
#include	"GameEngine.hh"
#include	"Bomberman.hh"
#include	"Map.hh"
#include	"./AObject/Objects.hh"

int		main(int ac, char **av, char **env)
{
  GameEngine	engine;
  Module	main;

  if (engine.initialize() == false)
    {
      std::cout << "Bomberman : Init fail\n" << std::endl;
      exit(EXIT_FAILURE);
    }
  main = ANIM;//MENU;
  while (1)
    {
      switch (main)
	{
	case ANIM :
	  {
	    while ((main = engine.runGame(ANIM)) == ANIM);
	    break;
	  }
	case MENU :
	  {
	    while ((main = engine.runGame(MENU)) == MENU);
	    break;
	  }
	case QUIT :
	  exit(EXIT_SUCCESS);
	case ERROR :
	  exit(EXIT_FAILURE);
	case GAME :
	  {
	    while ((main = engine.runGame(GAME)) == GAME);
	    break;
	  }
	case LOAD_MAP :
	  {
	    while ((main = engine.runGame(LOAD_MAP)) == LOAD_MAP);
	    break;
	  }
	case DUAL_GAME :
	  {
	    while ((main = engine.runGame(DUAL_GAME)) == DUAL_GAME);
	    break;
	  }
	case EDIT_MAP :
	  {
	    while ((main = engine.runGame(EDIT_MAP)) == EDIT_MAP);
	    break;
	  }
	case RATE :
	  {
	    while ((main = engine.runGame(RATE)) == RATE);
	    break;
	  }
	case NEW_GAME :
	  {
	    while ((main = engine.runGame(NEW_GAME)) == EDIT_MAP);
	    break;
	  }
	case FREE_MODE :
	  {
	    while ((main = engine.runGame(FREE_MODE)) == FREE_MODE);
	    break;
	  }
	case ARCADE :
	  {
	    while ((main = engine.runGame(ARCADE)) == ARCADE);
	    break;
	  }
	case EXTRA :
	  {
	    while ((main = engine.runGame(EXTRA)) == EXTRA);
	    break;
	  }
	case SURVIVAL :
	  {
	    while ((main = engine.runGame(SURVIVAL)) == SURVIVAL);
	    break;
	  }
	case TOOLS :
	  {
	    while ((main = engine.runGame(TOOLS)) == TOOLS);
	    break;
	  }
	case LOAD_GAME :
	  {
	    while ((main = engine.runGame(LOAD_GAME)) == LOAD_GAME);
	    break;
	  }
	case READ_SAVE :
	  {
	    while ((main = engine.runGame(READ_SAVE)) == READ_SAVE);
	    break;
	  }
	default :
	  {
	    main = MENU;
	    std::cout << "NOT IMPLEMENTED" << std::endl;
	  }
	}
    }
}
