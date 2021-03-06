CC = g++ -lncurses -g
CFLAGS = -c -Wall
SRC_DIR = ./src
BIN := main.o ClasseMap.o ClasseOggetto.o ClasseEroe.o ClasseBigMap.o Comandi.o ClasseBullet.o ClasseMotore.o ClasseBonus.o ClasseEnemy.o

ProgettoProgrammazione2021: $(BIN)
	$(CC) -o ProgettoProgrammazione2021 $(BIN)

main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/*.hpp
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp

ClasseMap.o: $(SRC_DIR)/ClasseMap.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseMap.cpp 

ClasseOggetto.o: $(SRC_DIR)/ClasseOggetto.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseOggetto.cpp

ClasseEroe.o: $(SRC_DIR)/ClasseEroe.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseEroe.cpp

ClasseBigMap.o: $(SRC_DIR)/ClasseBigMap.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseBigMap.cpp

Comandi.o: $(SRC_DIR)/Comandi.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/Comandi.cpp

ClasseBullet.o: $(SRC_DIR)/ClasseBullet.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseBullet.cpp

ClasseMotore.o: $(SRC_DIR)/ClasseMotore.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseMotore.cpp

ClasseBonus.o: $(SRC_DIR)/ClasseBonus.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseBonus.cpp

ClasseEnemy.o: $(SRC_DIR)/ClasseEnemy.?pp
	$(CC) $(CFLAGS) $(SRC_DIR)/ClasseEnemy.cpp
love:
	./ProgettoProgrammazione2021

clean:
	rm -rf ./*.o

debug:
	gdb ./ProgettoProgrammazione2021