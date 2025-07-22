

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

struct ball {
    int posX;
    int posY;
    float radius;
    Color color;
};

struct paddle {
        int posX;
        int posY;
        int width;
        int height;
        Color color;
    };
    

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 640;
    const int screenHeight = 480;
    const int half_screenHeight = screenHeight/2;
    const int half_screenWidth = screenWidth/2;
    int speedX = 4;
    int speedY = 4;
    int player1_score = 0;
    int player2_score = 0;

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    
    struct paddle paddle1;
    paddle1.width = 15;
    paddle1.posX = paddle1.width - 5;
    paddle1.height = 70;
    paddle1.posY = half_screenHeight - paddle1.height / 2;
    paddle1.color = WHITE;
    
    struct paddle paddle2;
    paddle2.width = 15;
    paddle2.posX = 635 - paddle2.width;
    paddle2.height = 70;
    paddle2.posY = half_screenHeight - paddle2.height / 2;
    paddle2.color = WHITE;
    
    struct ball pongball;
    pongball.posX = half_screenWidth;
    pongball.posY = half_screenHeight;
    pongball.radius = 15.00;
    pongball.color = WHITE;
    
    
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
       
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_UP)) {
                paddle2.posY -= 5;
            }
        if (IsKeyDown(KEY_DOWN)) {
            paddle2.posY += 5;
        }
        if (IsKeyDown(KEY_W)) {
            paddle1.posY -= 5;
        }
        if (IsKeyDown(KEY_S)) {
           paddle1.posY += 5;
        }
            
        if (paddle1.posY < 0) {
            paddle1.posY = 0;
        }
        if (paddle1.posY > (screenHeight - paddle1.height)) {
            paddle1.posY = (screenHeight - paddle1.height);
        }
        if (paddle2.posY < 0) {
            paddle2.posY = 0;
        }
        if (paddle2.posY > (screenHeight - paddle2.height)) {
            paddle2.posY = (screenHeight - paddle2.height);
        }
            
        pongball.posX += speedX;
        pongball.posY += speedY;
            
        if ((pongball.posX + pongball.radius) >= screenWidth || (pongball.posX - pongball.radius) <= 0) {
            speedX *= -1;
        }
        if ((pongball.posY + pongball.radius) >= screenHeight || (pongball.posY - pongball.radius) <= 0) {
            speedY *= -1;
        }
            
        if (pongball.posX + pongball.radius >= screenWidth) {
            player1_score++;
        }
        if (pongball.posX - pongball.radius <= 0) {
            player2_score++;
        }
            
        if (player1_score >= 10 || player2_score >= 10) {
            const char *winnerText = (player1_score >= 10) ? "Player 1 Wins!" : "Player 2 Wins!";
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
                    player1_score = 0;
                    player2_score = 0;
                    pongball.posX = half_screenWidth;
                    pongball.posY = half_screenHeight;
                    speedX = 5;
                    speedY = 5;

                    paddle1.posY = half_screenHeight - paddle1.height / 2;
                    paddle2.posY = half_screenHeight - paddle2.height / 2;

                    decisionMade = true;
                }

                if (IsKeyPressed(KEY_Q)) {
                    CloseWindow();
                    return 0;
                }
            }
        }

            
        if (CheckCollisionCircleRec((Vector2){pongball.posX, pongball.posY}, pongball.radius, (Rectangle){paddle1.posX, paddle1.posY, paddle1.width, paddle1.height})) {
            speedX *= -1;
        }
        if (CheckCollisionCircleRec((Vector2){pongball.posX, pongball.posY}, pongball.radius, (Rectangle){paddle2.posX, paddle2.posY, paddle2.width, paddle2.height})) {
            speedY *= -1;
        }
          
    

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawLine(half_screenWidth, 0, half_screenWidth, screenHeight, WHITE);
            DrawCircle(pongball.posX, pongball.posY, pongball.radius, pongball.color);
            DrawRectangle(paddle1.posX, paddle1.posY, paddle1.width, paddle1.height, paddle1.color);
            DrawRectangle(paddle2.posX, paddle2.posY, paddle2.width, paddle2.height, paddle2.color);
            DrawText(TextFormat("%d", player1_score), screenWidth/4, 20, 30, WHITE);
            DrawText(TextFormat("%d", player2_score), screenWidth/4 * 3, 20, 30, WHITE);
        
            
       
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}