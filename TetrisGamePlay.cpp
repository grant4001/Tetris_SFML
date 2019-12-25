#include "include/TetrisGamePlay.h"

// Empty constructor
TetrisGamePlay::TetrisGamePlay() {}

// Start the game window
void TetrisGamePlay::StartWindow() 
{
    window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
}

// Load images
void TetrisGamePlay::LoadImages(int numFigs)
{
    // Load textures
    tiles.loadFromFile("images/tiles.png");
    background.loadFromFile("images/background.png");
    frame.loadFromFile("images/frame.png");
    frametop.loadFromFile("images/frametop.png");

    // Load textures into sprites
    tiles_s.setTexture(tiles);
    background_s.setTexture(background);
    frame_s.setTexture(frame);
    frametop_s.setTexture(frametop);
    
    for (int i = 0; i < numFigs; i++) 
    {
        field_s[i].setTexture(tiles);
        field_s[i].setTextureRect(IntRect(i * UNIT, 0, UNIT, UNIT));
    }
}

bool TetrisGamePlay::WindowIsOpen()
{
    return window.isOpen();
}

void TetrisGamePlay::IncrementTimer()
{   
    float elapse = clock.getElapsedTime().asSeconds();
    falling_timer += elapse;
    landing_timer += elapse;
    rotate_timer += elapse;
    clock.restart();
}

bool TetrisGamePlay::WindowPollEvent(Event* e)
{
    return window.pollEvent(*e);
}

void TetrisGamePlay::WindowClose()
{
    window.close();
}

void TetrisGamePlay::DrawBackground()
{
    window.draw(background_s);
}

void TetrisGamePlay::DrawFallingPiece(int piece_type, int *x, int *y, int SIZE)
{
    tiles_s.setTextureRect(IntRect(piece_type * UNIT, 0, UNIT, UNIT));
    for (int i = 0; i < SIZE; i++)
    {
        tiles_s.setPosition(x[i] * UNIT + DRAW_X_OFFSET, y[i] * UNIT + DRAW_Y_OFFSET);
        window.draw(tiles_s);
    }
}

void TetrisGamePlay::DrawField(int (*field)[10], int fieldHeight, int fieldWidth)
{
    for (int i = 0; i < fieldHeight; i++)
        for (int j = 0; j < fieldWidth; j++) 
            if ((*(field + i))[j] != 0)
            {
                field_s[(*(field + i))[j] - 1].setPosition(j * UNIT + DRAW_X_OFFSET, i * UNIT + DRAW_Y_OFFSET);
                window.draw(field_s[(*(field + i))[j] - 1]);
            }
}

void TetrisGamePlay::DrawFrame()
{
    window.draw(frame_s);
}

void TetrisGamePlay::DrawFrameTop()
{
    window.draw(frametop_s);
}

bool TetrisGamePlay::MoveDownTimeStepHandler()
{ 
    if (falling_timer > FALL_DELAY)
    {
        falling_timer = 0;
        return true;
    } else return false;
}

bool TetrisGamePlay::RotateTimeStepHandler()
{
    if (rotate_timer > ROTATE_DELAY)
    {
        rotate_timer = 0;
        return true;
    } else return false;
}

bool TetrisGamePlay::DelayLandingHandler()
{
    if (landing_timer > LANDING_DELAY)
    {
        landing_timer = 0;
        return true;
    } else return false;
}

void TetrisGamePlay::ClearWindow()
{
    window.clear(Color::White);
}

void TetrisGamePlay::DisplayWindow()
{
    window.display();
}