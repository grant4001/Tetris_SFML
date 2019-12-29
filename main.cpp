#include "include/TetrisGamePlay.h"
#include "include/FallingPiece.h"
#include "include/Field.h"

// MAIN FUNCTION
int main()
{
    // Initialize game object
    TetrisGamePlay Game;

    // Initialize the falling piece
    FallingPiece piece;

    // Initialize the field
    Field field;

    // Start the game window
    Game.StartWindow();

    // Initialize score
    Game.CreateTexts();

    // Load image textures into sprites
    Game.LoadImages(piece.GetNumFigs());

    /////////////////////////////////// MAIN GAME LOOP //////////////////////////////////////
    while (Game.WindowIsOpen())
    {
        // React to some user event.
        Event e; 
        while (Game.WindowPollEvent(&e)) if (piece.UserEventHandler(&e)) Game.WindowClose();
        
        // Increment game timer
        Game.IncrementTimer();

        // Check if we need to drop piece; if so, then do so.
        piece.DropNewPiece();

        // Rotate the piece.
        if (Game.RotateTimeStepHandler()) piece.RotatePiece(field.GetField(), field.GetRightEdgeXVal());

        // Check for horizontal collision with either the field or the frame.
        piece.CheckHorizontalCollision(field.GetField(), field.GetRightEdgeXVal());

        // Move position of the piece left or right (or keep still).
        piece.MoveLeftOrRight();

        // Check bottom collision
        piece.CheckBottomCollision(field.GetField());

        // Set the landing flag
        if (Game.DelayLandingHandler() && piece.PieceIsLanded() && 0==piece.Getdx()) 
            piece.SetLandingFlag();
        
        // If landing flag is set, go into the landing handler  
        if (piece.PieceIsLandedDelayed()) 
        { 
            // these have to be delayed
            piece.PieceLandingHandler(); 
            field.FieldLandingHandler(piece.GetCurrentPieceType(), piece.GetX(), piece.GetY()); 
        }

        // Inch the piece down
        if (Game.MoveDownTimeStepHandler()) piece.MoveDown();

        // Delete full rows and calc score
        Game.CalcScore(field.DeleteFullRows());

        // Reset settings before next frame
        piece.ResetSettings();

        /////////////////////////// DRAWING RELATED /////////////////////////////////

        // Clear window
        Game.ClearWindow();

        // Draw the background
        Game.DrawBackground();

        // Draw the field
        Game.DrawField(field.GetField(), field.GetHeight(), field.GetWidth());
        
        // Draw the falling piece
        Game.DrawFallingPiece(piece.GetCurrentPieceType(), piece.GetX(), piece.GetY(), 4);

        // Draw the frame
        Game.DrawFrame();

        // Draw the frametop
        Game.DrawFrameTop();

        // Draw the score
        Game.DisplayScore();

        // Check if game is lost
        if (field.TopRowFilled()) Game.LossHandler();

        // Display the window
        Game.DisplayWindow();
    }

    return 0;
}