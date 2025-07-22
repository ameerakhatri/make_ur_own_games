
#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

struct player {
        int posX;
        int posY;
        int width;
        int height;
        Color color;
    };
 
 struct Cheese {
     int posX;
     int posY;
     float radius;
     float speed;
     Color color;
 };
 
 struct Bomb {
     int posX;
     int posY;
     float radius;
     float speed;
     Color color;
 };
 
 
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    struct player rat;
    rat.width = 100;
    rat.posX = 0;
    rat.height = 20;
    rat.posY = 600 - rat.height;
    rat.color = BLUE;
    
    
    //cheese 1
    struct Cheese cheese1;
    cheese1.posX = 40;
    cheese1.posY = 30;
    cheese1.radius = 20.00;
    cheese1.speed = GetRandomValue(2, 5);
    cheese1.color = GOLD;
    
    //cheese 2
    struct Cheese cheese2;
    cheese2.posX = 460;
    cheese2.posY = 30;
    cheese2.radius = 20.00;
    cheese2.speed = GetRandomValue(2, 5);
    cheese2.color = GOLD;
    
    
    struct Bomb bomb1;
    bomb1.posX = 356;
    bomb1.posY = 30;
    bomb1.radius = 22.00;
    bomb1.speed = GetRandomValue(2, 5);
    bomb1.color = BLACK;
        
    
    int score;
    score = 0;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
            
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                rat.posX -= 15;
            }
        if (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)) {
                rat.posX += 15;
        }
        if (rat.posX < 0) {
                rat.posX = 0;
        }
        if (rat.posX > (screenWidth - rat.width)) {
                rat.posX = (screenWidth - rat.width);
        }
        
        Vector2 CenterOfCheese1 = {(float)cheese1.posX, (float)cheese1.posY};
        Vector2 CenterOfCheese2 = {(float)cheese2.posX, (float)cheese2.posY};
        Rectangle ratRec = {(float)rat.posX, (float)rat.posY, (float)rat.width, (float)rat.height};
        
         
        if (CheckCollisionCircleRec(CenterOfCheese1, cheese1.radius, ratRec)) {
            score = score + 1;
            cheese1.posY = 0;
            cheese1.posX = GetRandomValue(0,800);
        }
        if (CheckCollisionCircleRec(CenterOfCheese2, cheese2.radius, ratRec)) {
            score = score + 1;
            cheese2.posY = 0;
            cheese2.posX = GetRandomValue(0,800);
        }

        // Checking if coin is going off of screen 
        if (cheese1.posY > screenHeight + (int)cheese1.radius) {
            cheese1.posY = 0;
            cheese1.posX = GetRandomValue(0,800);
        }
        
        if (cheese2.posY > screenHeight + (int)cheese2.radius) {
            cheese2.posY = 0;
            cheese2.posX = GetRandomValue(0,800);
        }


        cheese1.posY += cheese1.speed;
        cheese2.posY += cheese2.speed;
        bomb1.posY += bomb1.speed;
        
        Vector2 CenterOfBomb1 = {(float)bomb1.posX, (float)bomb1.posY};
        if (CheckCollisionCircleRec(CenterOfBomb1, bomb1.radius, ratRec)) {
            const char *losertext = "You lost :(";
            bool decision = false;
            while (!decision) {
                BeginDrawing();
                ClearBackground(BLACK);

                DrawText(losertext, 200, 150, 40, RAYWHITE);
                DrawText("Press R to Restart", 200, 250, 20, GRAY);
                DrawText("Press Q to Quit", 200, 280, 20, GRAY);
                EndDrawing();

                if (IsKeyPressed(KEY_R)) {
                // Reset positions and scores
                    score = 0;
                    rat.posX = 0;
                    rat.posY = 600 - 20;
                    bomb1.posX = GetRandomValue(0,800);
                    bomb1.posY = 30;
                    bomb1.speed = GetRandomValue(2, 5);
                    cheese1.posX = GetRandomValue(0,800);
                    cheese1.posY = 30;
                    cheese1.speed = GetRandomValue(2, 5);
                    cheese2.posX = GetRandomValue(0,800);
                    cheese2.posY = 30;
                    cheese2.speed = GetRandomValue(2, 5);

                    decision = true;
                }

                if (IsKeyPressed(KEY_Q)) {
                    CloseWindow();
                    return 0;
                }
            }
        }     
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangle(rat.posX, rat.posY, rat.width, rat.height, rat.color);
            DrawCircle(cheese1.posX, cheese1.posY, cheese1.radius, cheese1.color);
            DrawCircle(cheese2.posX, cheese2.posY, cheese2.radius, cheese2.color);
            DrawCircle(bomb1.posX, bomb1.posY, bomb1.radius, bomb1.color);
            DrawText(TextFormat("Score %d", score), 20, 20, 20, BLACK);

            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}