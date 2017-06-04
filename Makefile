CXX = g++
DEBUGFLAGS = -g
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include -I/usr/include/SDL2 -I./
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(DEBUGFLAGS) $(SDL_INCLUDE)
LDFLAGS = $(DEBUGFLAGS) $(SDL_LIB)
OBJ_DIR = obj
EXE = hexnul

all: $(EXE)

$(EXE): main.o hexnul.o state.o world.o utils.o
	$(CXX) $^ $(LDFLAGS) -o $@

objdir:
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/main.o: main.cpp hexnul.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/hexnul.o: hexnul.cpp hexnul.h world.o state.o utils.o
	$(CXX) $(CXXFLAGS) $< -o $@

STATE_DEPS = thingfactory.h tilefactory.h $(OBJ_DIR)/utils.o

$(OBJ_DIR)/state.o: state.cpp state.h utils.h $(STATE_DEPS)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/tile.o: tile.h $(OBJ_DIR)/sprite.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/thing.o: thing.h $(OBJ_DIR)/sprite.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/sprite.o: sprite.h $(OBJ_DIR)/renderable.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/world.o: world.cpp world.h $(OBJ_DIR)/state.o $(OBJ_DIR)/utils.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/utils.o: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/renderable.o: renderable.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o;rm $(EXE)
