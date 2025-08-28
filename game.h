#ifndef GAME_H
#define GAME_H

// Player
typedef struct {
    float x,y;
    int velocity;
    int level;
} Player;

void InitPlayer(Player* p);
void UpdatePlayer(Player* p);
void DrawPlayer(Player* p);


// Soup
typedef struct {
    float x,y;
    int speed;
} Soup;

void InitSoup(Soup* s);
void UpdateSoup(Soup* s);
void DrawSoup(Soup* s);
#endif