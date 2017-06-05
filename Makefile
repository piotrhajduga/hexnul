OUT_DIR = bin
OBJ_DIR = obj
EXE = $(OUT_DIR)/hexnul
INCLUDE_DIR = include
SOURCE_DIR = src

CXX = g++
DEBUGFLAGS = -g
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include -I/usr/include/SDL2 -I./$(INCLUDE_DIR)
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(DEBUGFLAGS) $(SDL_INCLUDE)
LDFLAGS = $(DEBUGFLAGS) $(SDL_LIB)

all: $(OUT_DIR) $(OBJ_DIR) $(EXE)

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(EXE): $(addprefix $(OBJ_DIR)/, main.o hexnul.o state.o world.o utils.o)
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/main.o: $(SOURCE_DIR)/main.cpp $(INCLUDE_DIR)/hexnul.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/hexnul.o: $(SOURCE_DIR)/hexnul.cpp $(INCLUDE_DIR)/hexnul.h $(OBJ_DIR)/world.o $(OBJ_DIR)/state.o $(OBJ_DIR)/utils.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/state.o: $(SOURCE_DIR)/state.cpp $(INCLUDE_DIR)/state.h $(addprefix $(OBJ_DIR)/, utils.o tile.o thing.o)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/tile.o: $(INCLUDE_DIR)/tile.h $(OBJ_DIR)/sprite.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/thing.o: $(addprefix $(INCLUDE_DIR)/,thing.h base_thing.h building.h thingstack.h road.h) $(OBJ_DIR)/sprite.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/sprite.o: $(INCLUDE_DIR)/sprite.h $(INCLUDE_DIR)/renderable.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/world.o: $(SOURCE_DIR)/world.cpp $(INCLUDE_DIR)/world.h $(OBJ_DIR)/state.o $(OBJ_DIR)/utils.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/utils.o: $(SOURCE_DIR)/utils.cpp $(INCLUDE_DIR)/utils.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean-objects:
	rm -f *.o
	rm -rf $(OBJ_DIR)
	
clean: clean-objects
	rm -f $(EXE)
