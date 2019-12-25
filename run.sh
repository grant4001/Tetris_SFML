g++ -c main.cpp -o main.o
g++ -c TetrisGamePlay.cpp -o TetrisGamePlay.o
g++ -c FallingPiece.cpp -o FallingPiece.o
g++ -c Field.cpp -o Field.o
g++ main.o TetrisGamePlay.o FallingPiece.o Field.o -o TetrisApp -lsfml-graphics -lsfml-window -lsfml-system
./TetrisApp
