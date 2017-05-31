CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include -I/usr/include/SDL2 -I./
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = hexnul

all: $(EXE)

$(EXE): main.o hexnul.o state.o world.o thing.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.cpp hexnul.h
	$(CXX) $(CXXFLAGS) $< -o $@

hexnul.o: hexnul.cpp hexnul.h world.h
	$(CXX) $(CXXFLAGS) $< -o $@

state.o: state.cpp state.h thing.h
	$(CXX) $(CXXFLAGS) $< -o $@

world.o: world.cpp world.h
	$(CXX) $(CXXFLAGS) $< -o $@

thing.o: thing.cpp thing.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o;rm $(EXE)
