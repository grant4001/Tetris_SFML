#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

class Field
{
    public:
        Field();
        int GetHeight();
        int GetWidth();
        int GetRightEdgeXVal();
        int (*GetField())[10];
        void FieldLandingHandler(int piece_type, int* x, int* y);
        int DetectFullRow();
        int DeleteFullRows();
        int field[20][10] = {0};
        bool TopRowFilled();

    private:
        const int FIELD_HEIGHT = 20;
        const int FIELD_WIDTH = 10;
        const int X_MAX = 9;
                
};

#endif