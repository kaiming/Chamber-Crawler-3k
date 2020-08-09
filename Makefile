CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -MMD # use -MMD to generate dependencies
EXEC = cc3k
MAIN_SOURCES = ${wildcard ./Main/*.cc} # sources in root directory
MAIN_OBJ = ${MAIN_SOURCES:.cc=.o}
BOARD_SOURCES = ${wildcard ./Board/*.cc} # sources in Board subdirectory
BOARD_OBJ = ${BOARD_SOURCES:.cc=.o}
CHARACTER_SOURCES = ${wildcard ./Character/*.cc} # sources in Character subdirectory
CHARACTER_OBJ = ${CHARACTER_SOURCES:.cc=.o}
ENEMY_SOURCES = ${wildcard ./Enemy/*.cc} # sources in Enemy subdirectory
ENEMY_OBJ = ${ENEMY_SOURCES:.cc=.o}
FACTORY_SOURCES = ${wildcard ./Factory/*.cc} # sources in Factory subdirectory
FACTORY_OBJ = ${FACTORY_SOURCES:.cc=.o}
GOLD_SOURCES = ${wildcard ./Gold/*.cc} # sources in Factory subdirectory
GOLD_OBJ = ${GOLD_SOURCES:.cc=.o}
PLAYER_SOURCES = ${wildcard ./Player/*.cc} # sources in Player subdirectory
PLAYER_OBJ = ${PLAYER_SOURCES:.cc=.o}
POTION_SOURCES = ${wildcard ./Potion/*.cc} # sources in Potion subdirectory
POTION_OBJ = ${POTION_SOURCES:.cc=.o}
TD_SOURCES = ${wildcard ./TextDisplay/*.cc} # sources in TextDisplay subdirectory
TD_OBJ = ${TD_SOURCES:.cc=.o}
TILE_SOURCES = ${wildcard ./Tile/*.cc} # sources in Tile subdirectory
TILE_OBJ = ${TILE_SOURCES:.cc=.o}
OBJECTS = ${MAIN_OBJ} ${BOARD_OBJ} ${CHARACTER_OBJ} ${ENEMY_OBJ} ${FACTORY_OBJ} ${GOLD_OBJ} ${PLAYER_OBJ} ${POTION_OBJ} ${TD_OBJ} ${TILE_OBJ}
DEPENDS =  ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm -f ${OBJECTS} ${DEPENDS} ${EXEC}
