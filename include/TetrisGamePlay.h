#ifndef TETRISGAMEPLAY_H
#define TETRISGAMEPLAY_H

#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using std::string;

class TetrisGamePlay 
{
    public:
        TetrisGamePlay();
        void StartWindow();
        void LoadImages(int numFigs);
        bool WindowIsOpen();
        void IncrementTimer();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        bool WindowPollEvent(Event* e);
        void WindowClose();
        void DrawBackground();
        void DrawFallingPiece(int piece_type, int *x, int *y, int SIZE);
        void DrawField(int (*field)[10], int fieldHeight, int fieldWidth);
        void DrawFrame();
        void DrawFrameTop();
        bool MoveDownTimeStepHandler();
        bool RotateTimeStepHandler();
        bool DelayLandingHandler();
        void ClearWindow();
        void DisplayWindow();

    private:
        const string WINDOW_TITLE = "Tetris!";
        const int WINDOW_HEIGHT = 480;  
        const int WINDOW_WIDTH = 320;
        const int UNIT = 18;
        const float FALL_DELAY = 0.3;
        const float ROTATE_DELAY = 0.1;
        const float LANDING_DELAY = 0.7;
        const int DRAW_X_OFFSET = 28;
        const int DRAW_Y_OFFSET = 31;
        Clock clock;
        float falling_timer;
        float rotate_timer;
        float landing_timer;
        RenderWindow window;
        Texture tiles, background, frame, frametop;
        Sprite tiles_s, background_s, frame_s, frametop_s;
        Sprite field_s[7];
};

#endif
