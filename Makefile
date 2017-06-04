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
EXE = hexnul

all: $(EXE)

$(EXE): main.o hexnul.o state.o world.o utils.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.cpp hexnul.h
	$(CXX) $(CXXFLAGS) $< -o $@

hexnul.o: hexnul.cpp hexnul.h world.o state.o utils.o
	$(CXX) $(CXXFLAGS) $< -o $@

STATE_DEPS = thing.o thingfactory.h tile.o tilefactory.h utils.o

state.o: state.cpp state.h utils.h $(STATE_DEPS)
	$(CXX) $(CXXFLAGS) $< -o $@

tile.o: tile.h sprite.o
	$(CXX) $(CXXFLAGS) $< -o $@

thing.o: thing.h sprite.o
	$(CXX) $(CXXFLAGS) $< -o $@

sprite.o: sprite.h renderable.o
	$(CXX) $(CXXFLAGS) $< -o $@

world.o: world.cpp world.h state.o utils.o
	$(CXX) $(CXXFLAGS) $< -o $@

utils.o: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) $< -o $@

renderable.o: renderable.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o;rm $(EXE)
