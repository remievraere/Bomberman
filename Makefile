##
## Makefile for Makefile in /home/bulcke_s/rendu/tek2/CPP/bomberman
## 
## Made by Simon Bulcke
## Login   <bulcke_s@epitech.net>
## 
## Started on  Tue May  6 11:54:38 2014 Simon Bulcke
## Last update Sun Jun 15 21:27:02 2014 Simon Bulcke
##

CC		=	g++

RM		=	rm -f

CXXFLAGS	=	-I./LibBomberman_linux_x64/includes

LDFLAGS		=	-lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -ldl -lsfml-audio -L./LibBomberman_linux_x64/libs

NAME		=	bomberman

SRCCPP		=	Bomberman.cpp		\
			AObject.cpp		\
			AMenu.cpp		\
			GameEngine.cpp		\
			Danger.cpp		\
			Map.cpp			\
			Camera.cpp		\
			Anim.cpp		\
			Run.cpp			\
			Interact.cpp		\
			Pause.cpp		\
			./AObject/Cube.cpp	\
			./AObject/Bonus.cpp	\
			./AObject/ECube.cpp	\
			./AObject/Bcube.cpp	\
			./AObject/Character.cpp	\
			./AObject/TexAni.cpp	\
			./AObject/Ground.cpp	\
			./AObject/Ia.cpp	\
			./AObject/Plan.cpp	\
			./AObject/SkyBox.cpp	\
			./AObject/Alpha.cpp	\
			./AObject/Number.cpp	\
			./AObject/Bomb.cpp	\
			./Cfunc/Readdir.cpp	\
			./AMenu/MainMenu.cpp	\
			./AMenu/GameMenu.cpp	\
			./AMenu/NewGame.cpp	\
			./AMenu/FreeMode.cpp	\
			./AMenu/ExtraMenu.cpp	\
			./AMenu/ToolsMenu.cpp	\
			./AMenu/LoadGame.cpp	\
			./AMenu/Score.cpp

OBJP		=	$(SRCCPP:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJP)
			$(CC) $(OBJP) $(LDFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJP)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			all clean fclean re
