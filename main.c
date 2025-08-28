#include "raylib.h"
#include "game.h"

int main(int argc, char* argv[]) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Gra o marcelu");
    SetTargetFPS(120);

    int fontSize = 35;

    bool hasTurbo = false; 

    InitAudioDevice();
    Sound loseSound = LoadSound("assets/lose.mp3");
    Sound turboSound = LoadSound("assets/turbo.mp3");

    Player skunks;
    InitPlayer(&skunks);

    char levelText[50];

    Soup soups[10];
    int soupCount = 0;
    int createdSoups = 0;

    float timer = 0.0f;
    float turboTimer = 0.0f;

    int oldSpeed;
    bool c = false;

    // Load textures
    Texture2D skunksTexture = LoadTexture("assets/skunks.png");
    Texture2D soupTexture = LoadTexture("assets/soup.jpg");

    // Turbo Button
    Rectangle button = { 100, 25, 200, 60 };
    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        bool mouseOver = CheckCollisionPointRec(mousePoint, button);
        bool clicked = false;

        if (mouseOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clicked = true;
        }

        sprintf(levelText, "Level %d", skunks.level);
        BeginDrawing();
        if (!hasTurbo) {
            ClearBackground(RAYWHITE);
        }
        else {
            ClearBackground(DARKGREEN);
        }

        float delta = GetFrameTime();
        // Turbo Button
        turboTimer += delta;
        if (mouseOver)
            DrawRectangleRec(button, LIGHTGRAY);
        else
            DrawRectangleRec(button, GRAY);

        DrawText("Turbo (cost 10 lvl)", button.x + 20, button.y + 23, 17, BLACK);

        if (clicked) {
            if (!hasTurbo && skunks.level > 10) {
                hasTurbo = true;
                turboTimer = 0;
                skunks.level -= 10;
                skunks.velocity += 30;

                for (int i = 0; i < soupCount; i++) {
                    if (!c) { oldSpeed = soups[i].speed; c = true; }
                    soups[i].speed = 1;
                }

                PlaySound(turboSound);
            }
            else if (turboTimer >= 11 && hasTurbo) {
                hasTurbo = false;
                turboTimer = 0;
                skunks.velocity += 10;

                for (int i = 0; i < soupCount; i++) {
                    soups[i].speed = 1;
                }
            }
        }

        // Level Text
        int textWidth = MeasureText(levelText, fontSize);
        int x = (screenWidth - textWidth) / 2;

        DrawText(levelText, x, 20, fontSize, BLACK);

        // Player
        UpdatePlayer(&skunks);
        DrawPlayer(&skunks, skunksTexture);

        if (createdSoups >= skunks.level + 3) {
            createdSoups = 0;
            skunks.level++;
        }

        // Soup
        timer += delta;

        if (timer >= 5.f / skunks.level) {
            Soup soup;
            soup.x = 0;
            soup.y = GetScreenHeight() / 2;
            soup.speed = skunks.level;

            soups[soupCount] = soup;
            soupCount++;
            createdSoups++;
            timer = 0.f;
        }

        // Manage Soups + Check collisions
        for (int i = 0; i < soupCount; i++) {
            UpdateSoup(&soups[i]);
            if (soups[i].x > GetScreenWidth()) {
                for (int j = i; j < soupCount - 1; j++) {
                    soups[j] = soups[j + 1];
                }
                soupCount--;
                i--;
                continue;
            }

            float scale = .05f;

            Rectangle skunkRec = {
                skunks.x,
                skunks.y,
                skunksTexture.width * scale,
                skunksTexture.height * scale
            };

            Rectangle soupRec = {
                soups[i].x,
                soups[i].y,
                soupTexture.width * scale,
                soupTexture.height * scale
            };

            if (CheckCollisionRecs(skunkRec, soupRec)) {
                if (skunks.level > 1) {
                    skunks.level--;
                }
                if (!IsSoundPlaying(loseSound)) PlaySound(loseSound);
                soups[i].x = -100;
            }
            DrawSoup(&soups[i], soupTexture);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
