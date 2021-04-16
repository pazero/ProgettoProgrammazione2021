CC = g++ -lncurses -g
CFLAGS = -c -Wall
SRC_DIR = ./src
BIN := main.o Map.o Oggetto.o Eroe.o WorldGen.o Comandi.o Bullet.o Motore.o

main: $(BIN)
	$(CC) -o main $(BIN)

main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/*.hpp
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp

Map.o: $(SRC_DIR)/Map.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/Map.cpp 

Oggetto.o: $(SRC_DIR)/Oggetto.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/Oggetto.cpp

Eroe.o: $(SRC_DIR)/Eroe.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/Eroe.cpp

WorldGen.o: $(SRC_DIR)/WorldGen.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/WorldGen.cpp

Comandi.o: $(SRC_DIR)/Comandi.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/Comandi.cpp

Bullet.o: $(SRC_DIR)/Bullet.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/Bullet.cpp

Motore.o: $(SRC_DIR)/Motore.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/Motore.cpp
	

love:
	./main

clean:
	rm -rf ./*.o

debug:
	gdb ./main