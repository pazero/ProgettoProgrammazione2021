main: main.o ClasseMap.o ClasseOggetto.o ClasseEroe.o ClasseBigMap.o Comandi.o ClasseBullet.o ClasseMotore.o
	g++ -lncurses -o main main.o ClasseMap.o ClasseOggetto.o ClasseEroe.o ClasseBigMap.o Comandi.o ClasseBullet.o ClasseMotore.o -g

main.o: main.cpp ClasseMap.hpp ClasseOggetto.hpp ClasseEroe.hpp ClasseBigMap.hpp Comandi.hpp ClasseBullet.hpp ClasseMotore.hpp
	g++ -c -lncurses main.cpp -g

ClasseMap.o: ClasseMap.cpp ClasseMap.hpp
	g++ -c -lncurses ClasseMap.cpp -g

ClasseOggetto.o: ClasseOggetto.cpp ClasseOggetto.hpp
	g++ -c -lncurses ClasseOggetto.cpp -g

ClasseEroe.o: ClasseEroe.cpp ClasseEroe.hpp
	g++ -c -lncurses ClasseEroe.cpp -g

ClasseBigMap.o: ClasseBigMap.cpp ClasseBigMap.hpp
	g++ -c -lncurses ClasseBigMap.cpp -g

Comandi.o: Comandi.cpp Comandi.hpp
	g++ -c -lncurses Comandi.cpp -g

ClasseBullet.o: ClasseBullet.cpp ClasseBullet.hpp
	g++ -c -lncurses ClasseBullet.cpp -g

ClasseMotore.o: ClasseMotore.cpp ClasseMotore.hpp
	g++ -c -lncurses ClasseMotore.cpp -g
love:
	./main

clean:
	rm -rf ./*.o

debug:
	gdb ./main