#include "game.h"
#include<iostream>
using namespace std;

void initGrid (mat &grid, const size_t & matSize, const unsigned  &KNbCandies){
    srand(time(0)); //Clé de génération nombre aléatoire

    for (unsigned int i = 0; i < matSize; i++){
        line ligne (matSize);
        for (unsigned int y = 0; y < matSize; y++){
            unsigned int randomNum = rand() % KNbCandies + 1; //Calcul du nombre aléatoire

            ligne[y] = randomNum;
        }
        grid[i] = ligne;
    }
}

void inMakeAMove(maPosition & pos, char & direction){ //Sélectionner la case avec des coordonnées
    cout << "Se positionner sur une colonne : ";
    cin >> pos.abs;
    pos.abs -= 1;

    cout << "Se positionner sur un nombre : ";
    cin >> pos.ord;
    pos.ord -= 1;

    cout << "Dans quel sens voulez-vous l'échanger (AZES): ";
    cin >> direction;

    direction = tolower(direction);
}

void inPosMakeAMove(mat & grid, maPosition & pos, char &c){ // - NON FONCTIONNELLE
    switch(c){

    case 'q':
        if (pos.abs==0){
            cout << "Valeur impossible" << endl;
        }
        else{
            pos.abs -= 1;
            cout << "Valeur possible vers : " << grid[pos.ord][pos.abs] << endl;
        }

        break;

    case 'd':
            if (pos.abs==grid.size()-1){
                cout << "Valeur impossible" << endl;
            }
            else{
                pos.abs += 1;
                cout << "Valeur possible vers : " << grid[pos.ord][pos.abs] << endl;
            }

            break;

        case 'z':
        if (pos.ord==0){
            cout << "Valeur impossible" << endl;
        }
        else{
            pos.ord -= 1;
            cout << "Valeur possible vers : " << grid[pos.ord][pos.abs] << endl;
        }

        break;

    case 's':
        if (pos.ord==grid.size()-1){
            cout << "Valeur impossible" << endl;
        }

        else{
            pos.ord += 1;
            cout << "Valeur possible vers : " << grid[pos.ord][pos.abs] << endl;
        }

        break;
    }
}

void makeAMove (mat & grid, maPosition & pos, const char & direction){
    maPosition target = pos;

    switch(direction){

    case 'q':
        if (pos.abs==0){
            cout << "Valeur impossible" << endl;
        }
        else{
            target.abs -= 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;

    case 'd':
        if (pos.abs==grid.size()-1){
            cout << "Valeur impossible" << endl;
        }
        else{
            target.abs += 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;

    case 'z':
        if (pos.ord==0){
            cout << "Valeur impossible" << endl;
        }
        else{
            target.ord -= 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;

    case 's':
        if (pos.abs==grid.size()-1){
            cout << "Valeur impossible" << endl;
        }

        else{
            target.ord += 1;
            cout << "Valeur possible vers : " << grid[target.ord][target.abs] << endl;
        }

        break;
    }

    // CHANGEMENT DES POSITIONS SANS TEMP
    grid[pos.ord][pos.abs] += grid[target.ord][target.abs];
    grid[target.ord][target.abs] = grid[pos.ord][pos.abs] - grid[target.ord][target.abs];
    grid[pos.ord][pos.abs] -= grid[target.ord][target.abs];

    pos.ord = target.ord;
    pos.abs = target.abs;
}

bool atLeastThreeInAColumn(const mat &grid, maPosition &pos, unsigned &howMany){
    size_t x = 0;
    while (x < grid.size()){
        size_t y = 0;
        howMany = 1;
        while (y < grid.size()-1){
            if (grid[y][x]==grid[y+1][x] && grid[y][x]!=0) ++howMany;
            else howMany=1;

            ++y;
            if (howMany == 3){
                pos.abs=x;
                pos.ord=y-2;
                while (y < grid.size()-1){
                    if (grid[y][x]!=grid[y+1][x]) break;
                    ++howMany;
                    ++y;
                }
                return true;
            }
        }

        ++x;
    }
    cout << "false" << endl;
    return false;
}

bool atLeastThreeInARow(const mat &grid, maPosition &pos, unsigned &howMany){
    size_t y = 0;
    while (y < grid.size()){
        size_t x = 0;
        howMany = 1;
        while (x < grid.size()-1){
            if (grid[y][x]==grid[y][x+1] && grid[y][x] != 0) ++howMany;
            else howMany=1;

            ++x;
            if (howMany == 3){
                pos.abs=x-2;
                pos.ord=y;
                while (x < grid.size()-1){
                    if (grid[y][x]!=grid[y][x+1]) break;
                    ++howMany;
                    ++x;
                }
                return true;
            }
        }
        ++y;
    }
    return false;
}

void removalInColumn (mat &grid, maPosition &pos, const unsigned &howMany){
    for (size_t i = 0; i < howMany; ++i){
        grid[pos.ord+i][pos.abs]=0;
    }

    // -- Méthode double Index

    size_t yNonNul = pos.ord;

    //On remonte
    for (size_t y = pos.ord; y < grid.size(); ++y){
        if (grid[y][pos.abs]!=0){
            grid[yNonNul][pos.abs] = grid[y][pos.abs];

            ++yNonNul;
        }
    }

    // On remplit le bas par des 0
    for (size_t y = yNonNul; y < grid.size(); ++y){
        grid[y][pos.abs] = 0;
    }
}

void removalInRow (mat &grid, maPosition &pos, const unsigned  &howMany){

    for (size_t i = 0; i < howMany; ++i){
        maPosition courant;
        courant.abs = pos.abs + i;
        courant.ord = pos.ord;

        removalInColumn(grid, courant, 1);
    }
}
