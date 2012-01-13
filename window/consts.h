#ifndef CONSTS_H
#define CONSTS_H

const int SCREENWIDTH=640;
const int SCREENHEIGHT=480;
const int BPP=32;

const char GAMENAME[]="Platformer v4";
const int FPSDELAY=1000/50;

const float DEGTORAD=3.141592653589793f/180.0f;
const float RADTODEG=180.0f/3.141592653589793f;

// Resfile
const char RESLIST[]="data/";

// Sprite
const char IMGEXT[]=".png";		// Rozszezenie obrazka
const char MDLEXT[]=".obj";		// Rozszezenie modelu 3d
const char ANIMEXT[]=".txt";	// Rozszezenie pliku z animacjami

// Poziom
//const int FRAMEWIDTH=640;
//const int FRAMEHEIGHT=480;

// Npc
const char NPCPATH[]="npc/";
const char NPCLIST[]="npc/list.ini";
const char LUAPATH[]="lua/";
const char LUALIST[]="lua/list.ini";
const char MUSICPATH[]="music/";
const char MUSICLIST[]="music/list.ini";
const char SOUNDPATH[]="sound/";

#endif // CONST_H
