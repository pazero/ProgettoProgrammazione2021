main: main.o ClasseMap.o ClasseOggetto.o ClasseEroe.o ClasseBigMap.o Comandi.o ClasseBullet.o
	g++ -lncurses -o main main.o ClasseMap.o ClasseOggetto.o ClasseEroe.o ClasseBigMap.o Comandi.o ClasseBullet.o

main.o: main.cpp ClasseMap.hpp ClasseOggetto.hpp ClasseEroe.hpp ClasseBigMap.hpp Comandi.hpp ClasseBullet.hpp
	g++ -c -lncurses main.cpp

ClasseMap.o: ClasseMap.cpp ClasseMap.hpp
	g++ -c -lncurses ClasseMap.cpp

ClasseOggetto.o: ClasseOggetto.cpp ClasseOggetto.hpp
	g++ -c -lncurses ClasseOggetto.cpp

ClasseEroe.o: ClasseEroe.cpp ClasseEroe.hpp
	g++ -c -lncurses ClasseEroe.cpp

ClasseBigMap.o: ClasseBigMap.cpp ClasseBigMap.hpp
	g++ -c -lncurses ClasseBigMap.cpp

Comandi.o: Comandi.cpp Comandi.hpp
	g++ -c -lncurses Comandi.cpp

ClasseBullet.o: ClasseBullet.cpp ClasseBullet.hpp
	g++ -c -lncurses ClasseBullet.cpp

love:
	./main