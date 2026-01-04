#ifndef GAME_H
#define GAME_H
// --- INCLUSION ---
#include<string>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

// --- ALIAS ---
typedef std::vector<unsigned> line;
typedef std::vector<line> mat;

// --- STRUCTURES ---
struct maPosition{
    size_t abs = 0;
    size_t ord = 0;
};

struct Joueur {
    string nom;
    size_t score;
};

//--- FONCTIONS ---
void initGrid (mat & grid, const size_t & matSize, const unsigned &KNbCandies);

void inMakeAMove(maPosition & pos, char & direction);
void inPosMakeAMove(mat & grid, maPosition & pos, char &c);
void makeAMove (mat & grid, maPosition & pos, const char & direction);

bool atLeastThreeInAColumn(const mat & grid, maPosition & pos, unsigned & howMany);
bool atLeastThreeInARow(const mat &grid, maPosition &pos, unsigned &howMany);

void removalInColumn (mat &grid, maPosition &pos, const unsigned  &howMany);
void removalInRow (mat &grid, maPosition &pos, const unsigned  &howMany);

vector<Joueur> lire_score(string mode);
void ajouter_score(string mode, string nom, size_t score);
void tri_score(vector<Joueur>& s);

#endif
