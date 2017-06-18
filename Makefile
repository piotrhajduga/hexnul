OUT_DIR = bin
OBJ_DIR = obj
EXE = $(OUT_DIR)/hexnul
INC_DIR = inc
SRC_DIR = src

CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include -I/usr/include/SDL2 -I$(INC_DIR)
CXXFLAGS = -Wall -c -std=c++11 -g $(SDL_INCLUDE)
LDFLAGS = $(DEBUGFLAGS) $(SDL_LIB)

all: $(OUT_DIR) $(OBJ_DIR) $(EXE)

rebuild: clean all

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(EXE): $(addprefix $(OBJ_DIR)/,main.o utils.o agent.o game.o maploader.o state.o toolbar.o sprite.o tile.o thing.o world.o building.o road.o thing.o)
	$(CXX) $^ $(LDFLAGS) -o $@

MAIN_INC = $(addprefix $(INC_DIR)/,game.h road.h thing.h utils.h)
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

GAME_INC = $(addprefix $(INC_DIR)/,game.h world.h state.h thing.h utils.h)
$(OBJ_DIR)/game.o: $(SRC_DIR)/game.cpp $(GAME_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

STATE_INC = $(addprefix $(INC_DIR)/,state.h utils.h direction.h tile.h)
$(OBJ_DIR)/state.o: $(SRC_DIR)/state.cpp $(STATE_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

TILE_INC = $(addprefix $(INC_DIR)/,tile.h sprite.h constants.h pathnode.h)
$(OBJ_DIR)/tile.o: $(SRC_DIR)/tile.cpp $(TILE_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

THING_INC = $(addprefix $(INC_DIR)/,thing.h thingtype.h renderable.h pathnode.h)
$(OBJ_DIR)/thing.o: $(SRC_DIR)/thing.cpp $(THING_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/sprite.o: $(SRC_DIR)/sprite.cpp $(INC_DIR)/sprite.h $(INC_DIR)/renderable.h
	$(CXX) $(CXXFLAGS) $< -o $@

WORLD_INC = $(addprefix $(INC_DIR)/,world.h maploader.h toolbar.h agent.h building.h road.h direction.h tile.h state.h utils.h sprite.h pathnode.h)
$(OBJ_DIR)/world.o: $(SRC_DIR)/world.cpp $(WORLD_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

MAPLOADER_INC = $(addprefix $(INC_DIR)/,maploader.h utils.h state.h tile.h)
$(OBJ_DIR)/maploader.o: $(SRC_DIR)/maploader.cpp $(MAPLOADER_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/utils.o: $(SRC_DIR)/utils.cpp $(INC_DIR)/utils.h $(INC_DIR)/constants.h
	$(CXX) $(CXXFLAGS) $< -o $@

ROAD_INC = $(addprefix $(INC_DIR)/,road.h direction.h thing.h thingtype.h sprite.h pathnode.h)
$(OBJ_DIR)/road.o: $(SRC_DIR)/road.cpp $(ROAD_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

BUILDING_INC = $(addprefix $(INC_DIR)/,building.h utils.h constants.h thing.h thingtype.h pathnode.h)
$(OBJ_DIR)/building.o: $(SRC_DIR)/building.cpp $(BUILDING_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

TOOLBAR_INC = $(addprefix $(INC_DIR)/,toolbar.h renderable.h sprite.h world.h state.h utils.h)
$(OBJ_DIR)/toolbar.o: $(SRC_DIR)/toolbar.cpp $(TOOLBAR_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

AGENT_INC = $(addprefix $(INC_DIR)/,agent.h sprite.h renderable.h state.h utils.h direction.h pathnode.h)
$(OBJ_DIR)/agent.o: $(SRC_DIR)/agent.cpp $(AGENT_INC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean-objects:
	rm -f *.o
	rm -rf $(OBJ_DIR)/
	
clean: clean-objects
	rm -f $(EXE)
