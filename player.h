#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

int score = 0;
int highscore = 0;
int level = 0;
int mouseX;
int mouseY;

bool isInMenu = true;
bool isInHelp = false;
bool isPause = false;
bool isPlaySound = true;

Mix_Music *currentMusic = nullptr;


#endif // PLAYER_H_INCLUDED
