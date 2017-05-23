CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include -I/usr/include/SDL2 -I./
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = hexnul

all: $(EXE)

$(EXE): main.o hexnul.o render.o state.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.cpp hexnul.h
	$(CXX) $(CXXFLAGS) $< -o $@

hexnul.o: hexnul.cpp hexnul.h render.h
	$(CXX) $(CXXFLAGS) $< -o $@

state.o: state.cpp state.h
	$(CXX) $(CXXFLAGS) $< -o $@

render.o: render.cpp render.h state.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o;rm *.d;rm $(EXE)
