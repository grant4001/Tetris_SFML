g++ -g -c main.cpp -o main.o
g++ -g -c TetrisGamePlay.cpp -o TetrisGamePlay.o
g++ -g -c FallingPiece.cpp -o FallingPiece.o
g++ -g -c Field.cpp -o Field.o
g++ main.o TetrisGamePlay.o FallingPiece.o Field.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
gdb ./sfml-app
