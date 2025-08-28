#include "game.h"
#include <stdio.h>
#include "raylib.h"

// Player

void InitPlayer(Player* p) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;
    p->x = centerX;
    p->y = centerY;
    p->velocity = (-2) - p->level;
    p->level = 1;
}

void UpdatePlayer(Player* p) {
    if (IsKeyDown(KEY_W)) p->velocity = (-2) - p->level;
    if (IsKeyDown(KEY_S)) p->velocity = 2 + p->level;

    p->y += p->velocity;
}



void DrawPlayer(Player* p, Texture2D texture) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerX = (screenWidth / 2)-10;
    int centerY = screenHeight / 2;

    // Draw player
    Vector2 position = {centerX, p->y};
    DrawTextureEx(texture, position, 0.0f, 0.1f, WHITE);

    // Map limit
    if (p->y < 70) {
        p->y = 70;
        p->velocity = 2 + p->level;
    }
    if (p->y > 500) {
        p->y = 500;
        p->velocity = (-2) - p->level;
    }
}

// Soup

void InitSoup(Soup* s) {
    Texture2D soupTexture = LoadTexture("assets/soup.jpg");

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;
    s->x = 0;
    s->y = centerY;
    s->speed = 2;
}

void UpdateSoup(Soup* s) {
    s->x += s->speed;
}

void DrawSoup(Soup* s, Texture2D texture) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerX = (screenWidth / 2) - 10;
    int centerY = screenHeight / 2;

    // Draw Soup
    Vector2 position = { s->x, centerY };
    DrawTextureEx(texture, position, 0.0f, 0.1f, WHITE);
}