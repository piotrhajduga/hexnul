g++ hexnul.cpp -DPACKAGE_NAME="" -DPACKAGE_TARNAME="" -DPACKAGE_VERSION="" -DPACKAGE_STRING="" -DPACKAGE_BUGREPORT="" -DHAVE_LIBSDL_IMAGE=1  -I. -I.  -g -O2 -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT -MT hexnul.o -MD -MP \
  -c -o hexnul.o;
#if gcc -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DHAVE_LIBSDL_IMAGE=1  -I. -I.     -g -O2 -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -MT hexnul.o -MD -MP -MF ".deps/hexnul.Tpo" \
  #-c -o hexnul.o `test -f 'hexnul.c' || echo './'`hexnul.c; \
#then mv ".deps/hexnul.Tpo" ".deps/hexnul.Po"; \
#else rm -f ".deps/hexnul.Tpo"; exit 1; \
#fi
g++  hexnul.o -g -O2 -I /usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT   -o hexnul -L/usr/lib/x86_64-linux-gnu -lSDL2 -lm
