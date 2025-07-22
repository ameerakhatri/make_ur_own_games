#include "raylib.h"
#include <stdio.h>

struct Boxes {
    Rectangle box;
    Color color;
    int score;
    bool active;
};

struct Ball {
    float radius;
    Vector2 center;
    Color color; 
    int x_speed;
    int y_speed;
};

struct Paddle {
    int posX;
    int posY;
    int width;
    int height;
    Color color;
};
    


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
        
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    int row = 5;
    int column = 10;
    int boxWidth = (int) (screenWidth/column);
    int boxHeight = 20;
    //int ballRadius = 10;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    struct Boxes Enemies[row][column];
    struct Ball ball = {10.0, (Vector2) {screenWidth/2, screenHeight/2},  BLACK, -5, -5}; 
    
    struct Paddle paddle;
    paddle.width = 100;
    paddle.posX = (screenWidth/2) - (paddle.width/2);
    paddle.height = 15;
    paddle.posY = 530 + paddle.height;
    paddle.color = DARKPURPLE;
    
    bool gameState = true;
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            Enemies[r][c].box = (Rectangle){ c * boxWidth, 60 + r * boxHeight, boxWidth - 2, boxHeight - 2 };
            Enemies[r][c].active = true;
            
            if (r == 0) {
                Enemies[r][c].color = RED;
                Enemies[r][c].score = 10;
            }

            if (r == 1) {
                Enemies[r][c].color = ORANGE;
                Enemies[r][c].score = 5;
            }
            
            if (r == 2) {
                Enemies[r][c].color = YELLOW;
                Enemies[r][c].score = 3;
            }
            
            if (r == 3) {
                Enemies[r][c].color = GREEN;
                Enemies[r][c].score = 2;
            }
            
            if (r == 4) {
                Enemies[r][c].color = BLUE;
                Enemies[r][c].score = 1;
            }
        }
    }
    
    
    
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------



        
        // Draw
        //----------------------------------------------------------------------------------
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c++) {
                    
                if (CheckCollisionCircleRec(ball.center, ball.radius, Enemies[r][c].box) == true && Enemies[r][c].active == true) {
                        Enemies[r][c].active = false;
                        ball.y_speed *= -1;
                }
                    
            }
        }
        
        if (ball.center.x - ball.radius < 0 || ball.center.x > screenWidth - ball.radius) {
            ball.x_speed *= -1;
        }
        
        if (ball.center.y - ball.radius < 0) {
            ball.y_speed *= -1;
        }
        
        if (ball.center.y > screenHeight - ball.radius) {
            gameState = false;
        }
        
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                paddle.posX -= 8;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                paddle.posX += 8;
        }
        if (paddle.posX <= 0) {
            paddle.posX = 0;
        }
        if (paddle.posX >= screenWidth - paddle.width) {
            paddle.posX = screenWidth - paddle.width;
        }
        if (CheckCollisionCircleRec((Vector2){ball.center.x, ball.center.y}, ball.radius, (Rectangle){paddle.posX, paddle.posY, paddle.width, paddle.height})) {
             ball.y_speed *= -1;
        }
        
        if (Enemies.score = 210) {
            const char *winnerText = "U WIN!!"
            bool decisionMade = false;
            while (!decisionMade) {
                BeginDrawing();
                ClearBackground(BLACK);

                DrawText(winnerText, 200, 150, 40, RAYWHITE);
                DrawText("Press R to Restart", 200, 250, 20, GRAY);
                DrawText("Press Q to Quit", 200, 280, 20, GRAY);

                EndDrawing();

                if (IsKeyPressed(KEY_R)) {
                // Reset positions and scores
                    
                    ball.center.x = screenWidth/2;
                    ball.center.x = screenHeight/2;
                    speedX = -5;
                    speedY = -5;

                    paddle1.posY = half_screenHeight - paddle1.height / 2;
                    paddle2.posY = half_screenHeight - paddle2.height / 2;

                    decisionMade = true;
                }

                if (IsKeyPressed(KEY_Q)) {
                    CloseWindow();
                    return 0;
                }
            }
        }*/
        
        
        //ball.center.x += ball.x_speed;
        //ball.center.y += ball.y_speed;
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
                for (int r = 0; r < row; r++) {
                    for (int c = 0; c < column; c++) {
                        
                        if (Enemies[r][c].active == true) {
                            DrawRectangleRec(Enemies[r][c].box, Enemies[r][c].color);
                        }
                    }
                }
                
                DrawCircleV(ball.center, ball.radius, ball.color);
                DrawRectangle(paddle.posX, paddle.posY, paddle.width, paddle.height, paddle.color);
                
           
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}