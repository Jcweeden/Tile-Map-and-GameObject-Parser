#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Game.cpp RenderManager.cpp GameObject.cpp GameObjectFactory.cpp InputHandler.cpp CollisionManager.cpp Level.cpp TileMapParser.cpp Camera.cpp level01/PlayerLevel01.cpp level01/EnemyLevel01.cpp level01/CoinLevel01.cpp

#CC specifies which compiler we're using
CC = g++ -std=c++11

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -ltinyxml

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = TileMapParser

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
