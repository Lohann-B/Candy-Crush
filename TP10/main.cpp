#include "game.h"
#include "test.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

string inputUser(unsigned sizeMax){
    string input = "";
    char c;

    while (cin.get(c) && c!=10) {
        if (isdigit(c) && input.size()<sizeMax){
            input += c;
            cout << c << flush;
        }
        else if ( c == 127 && !input.empty()) {
            input.pop_back();
            cout << "\b \b" << flush;
        }
    }
    cout << endl;
    return input;
}

// --- INITIALISATION ---
size_t initMatSize(){
    string input;
    size_t size;

    while (true){
        cout << "Taille de la matrice : " << flush;
        input = inputUser(2);

        if (input.empty()) {
            cout << endl << "Errreur : Saisie vide ! " << endl;
            continue;
        }

        size = stoi(input);

        if (size < 4) cout << endl << "Veuillez saisir une taille >= 4"<<endl;
        else break;
    }

    return size;

}

unsigned initNbCandies(){
    string input;
    unsigned nb;

    while (true){
        cout << "Combien de type de bonbon ? (MAX 7) : " << flush;
        input = inputUser(1);

        if (input.empty()) {
            cout << endl << "Errreur : Saisie vide ! " << endl;
            continue;
        }

        nb = stoi(input);

        if (nb > 7 || nb < 2) cout << endl << "Erreur : Veuillez saisir un nombre compris entre 2 et 7"<<endl;
        else break;
    }

    return nb;

}


// --- DECLARATION COULEURS TERMINAL ---
const unsigned KReset   (0);
const unsigned KFlash   (5);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

// --- STRUCTURE ---

class InputManager {
public:
    void enableRawMode() {
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        _oldTerm = term;

        term.c_lflag &= ~(ICANON | ECHO); // Désactive Entrée et l'affichage
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }

    // Restore les paramètres d'origine
    void disableRawMode() {
        tcsetattr(STDIN_FILENO, TCSANOW, &_oldTerm);
    }

private:
    termios _oldTerm;
};

// --- AFFICHAGE ---

void clearScreen () {
    cout << "\033[H\033[2J";
}

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

void fond (const unsigned & coul) {
    cout << "\033[" << coul+10 <<"m";
}

void affichVectUInt(line v){
    for (unsigned int elem : v){
        cout << elem << "\t";
    }
    cout << endl;
}

void affichVectStr(vector<string> & v){
    for (string &elem : v){
        cout << elem << endl;
        usleep(30000);
    }
    cout << endl;
}

void affichVectCoulStr(vector<string> & v){
    vector<int> colors = {31, 33, 32, 34, 35, 36, 0};

    unsigned i =0;
    for (string &elem : v){
        couleur(colors[i % colors.size()]);

        cout << elem << endl;
        usleep(30000);

        i++;
    }
    cout << endl;
}

// --- MATRICE ---

void affichVectLine(const line &v, const unsigned int &numLigne, const maPosition &pos){
    cout << numLigne+1;
    if (numLigne < 9){ //arrangement nombre à deux chiffres
        cout << " ";
    }
    cout <<" - | "; //affiche numéro ligne

    for (unsigned int numCol = 0; numCol < v.size(); numCol++){
        unsigned int elem = v[numCol];

        if (numLigne == pos.ord && numCol == pos.abs){
            cout << "\033[5;7;1m";
        }
        if (elem == 0){
            if (numLigne == pos.ord && numCol == pos.abs){
                cout << "\033[5;7;1m";
            }
            else{
                couleur(0);
            }
            cout << " ";
        }
        else{
            couleur(elem + 29);
            cout << elem;
        }

        couleur(0);
        cout << " | ";
    }
    cout << endl;
}

void affichBarre(mat & grid, char carac){
    string barre = "      ";
    for (unsigned int i = 0; i < 4*grid.size()-1; i++){
        barre += carac;
    }

    cout << barre << endl;
}

void affichAbs(mat & grid){
    unsigned int taille = 9; //ne peut pas affciher à 3 chiffres

    if (grid.size()<9){
        taille = grid.size();
    }

    cout << "       ";
    for (unsigned int i = 1; i < taille+1; i++){
        cout << i << "   ";
    }

    if (grid.size()>9){
        for (unsigned int i = 10; i < grid.size()+1; i++){
            cout << i << "  ";
        }
    }

    cout << endl;
}

void displayGrid(mat & grid, maPosition &pos){
    clearScreen();
    couleur(KReset);

    affichAbs(grid);
    affichBarre(grid,'_');

    for (unsigned int numLigne = 0; numLigne < grid.size(); numLigne++){
        affichVectLine(grid[numLigne],numLigne, pos);
    }

    affichBarre(grid,'-');
}

// --- MAIN ---

void game(){
    //INITIALISATION VARIABLES
    const size_t matSize = initMatSize();
    const unsigned KNbCandies = initNbCandies();
    mat grid (matSize);

    maPosition pos;
    char direction;

    //INITIALISATION MATRICE
    initGrid(grid, matSize,KNbCandies);
    displayGrid(grid, pos);

    //DÉROULEMENT DU JEU
    cout << grid.size() << endl;

    for (unsigned int i = 0; i < 5; i++){
        inMakeAMove(pos,direction);
        makeAMove(grid,pos,direction);
        displayGrid(grid, pos);
        cout << "Votre choix est " << grid[pos.ord][pos.abs] << " à échanger vers la direction de " << direction << endl;
    }
}

void loadingScreen(){
    vector <string> candyCrush{
        "||       _____          ____  _____   ______        _____    _____      _____             _____        _____    ____   ____          ______   ____   ____ ",
        "||   ___|\\    \\    ____|\\   \\|\\    \\ |\\     \\   ___|\\    \\  |\\    \\    /    /|        ___|\\    \\   ___|\\    \\  |    | |    |     ___|\\     \\ |    | |    |",
        "||  /    /\\    \\  /    /\\    \\\\\\    \\| \\     \\ |    |\\    \\ | \\    \\  /    / |       /    /\\    \\ |    |\\    \\ |    | |    |    |    |\\     \\|    | |    |",
        "|| |    |  |    ||    |  |    |\\|    \\  \\     ||    | |    ||  \\____\\/    /  /      |    |  |    ||    | |    ||    | |    |    |    |/____/||    |_|    |",
        "|| |    |  |____||    |__|    | |     \\  |    ||    | |    | \\ |    /    /  /       |    |  |____||    |/____/ |    | |    | ___|    \\|   | ||    .-.    |",
        "|| |    |   ____ |    .--.    | |      \\ |    ||    | |    |  \\|___/    /  /        |    |   ____ |    |\\    \\ |    | |    ||    \\    \\___|/ |    | |    |",
        "|| |    |  |    ||    |  |    | |    |\\ \\|    ||    | |    |      /    /  /         |    |  |    ||    | |    ||    | |    ||    |\\     \\    |    | |    |",
        "|| |\\ ___\\/    /||____|  |____| |____||\\_____/||____|/____/|     /____/  /          |\\ ___\\/    /||____| |____||\\___\\_|____||\\ ___\\|_____|   |____| |____|",
        "|| | |   /____/ ||    |  |    | |    |/ \\|   |||    /    | |    |`    | /           | |   /____/ ||    | |    || |    |    || |    |     |   |    | |    |",
        "||  \\|___|    | /|____|  |____| |____|   |___|/|____|____|/     |_____|/             \\|___|    | /|____| |____| \\|____|____| \\|____|_____|   |____| |____|",
        "||    \\( |____|/   \\(      )/     \\(       )/    \\(    )/          )/                  \\( |____|/   \\(     )/      \\(   )/      \\(    )/       \\(     )/  ",
        "||     '   )/       '      '       '       '      '    '           '                    '   )/       '     '        '   '        '    '         '     '   ",
        "||         '                                                                                '                                                             ",
        };

    vector <string> PressEnter{
        "                                                        _____                    _____     _           ",
        "                                                       |  _  |___ ___ ___ ___   |   __|___| |_ ___ ___ ",
        "                                                       |   __|  _| -_|_ -|_ -|  |   __|   |  _| -_|  _|",
        "                                                       |__|  |_| |___|___|___|  |_____|_|_|_| |___|_|  "
    };

    vector <string> Decor{
        "                                  _ _ _ _                                                                                    _ _ _ _",
        "                                .         .                                                                                .         .",
        "                              /             \\	                                                                        /             \\",
        "                             /      --    ---\\                                                                          /            ---\\",
        "                            |--   -    ---   |  _ _ _                                                           _ _ _  |   ----  ---    |",
        "                            |  ---           |.       .                                                       .       .|---    --       |",
        "                            |                |-  ---   |                              .                      |--  --   |                |",
        "                            |                | --   -  |                             /   .                   |  --  ---|                |",
        "                            |                |       --|                        =  =     . .                 |         |                |",
        "                            |                |         |                     =        = '    .               |         |                |",
        "                            |                |         |                    =          =  __ .               |         |                |",
        "                            |                |         |               . __ =          =                     |         |                |",
        "                            |                |         |                .    =        =                      |         |                |",
        "                            |                |         |                 .  ;   =  =                         |         |                |",
        "                            |                |         |                   .   /                             |         |                |",
        "                            |                |         |                      .                              |         |                |",
    };

    couleur(KReset);
    affichVectCoulStr(candyCrush);

    couleur(KFlash);
    couleur(KRouge);
    affichVectStr(PressEnter);
    couleur(KReset);

    affichVectStr(Decor);
    couleur(KReset);
}

int main(){
    // - Déclaration
    mat grid;
    size_t KMatSize;
    unsigned KNbCandies;

    bool gameStarted = false;
    bool caseSelect = false;

    maPosition pos;
    char direction;
    unsigned howMany;

    clearScreen();
    loadingScreen();

    InputManager input;
    input.enableRawMode();

    char c;
    while (cin.get(c) && c!=27){
        if (c==10 && !gameStarted){

            KMatSize = initMatSize();
            cout << "Votre choix : " << KMatSize << "\r\n\n";

            KNbCandies = initNbCandies();
            cout << "Votre choix : " << KNbCandies << "\r\n\n";

            grid.resize(KMatSize);
            initGrid(grid, KMatSize, KNbCandies);

            displayGrid(grid, pos); // affichage 1

            usleep(1000000);

            gameStarted = true;
            continue;
        }
        if (gameStarted){

            if (!caseSelect){
                if (c==10) caseSelect = true;
                else{
                    inPosMakeAMove(grid, pos, c);
                    displayGrid(grid,pos);
                }
            } else {
                if ((c=='z' && pos.ord!=0) || (c=='s' && pos.ord!=KMatSize-1) || (c=='q' && pos.abs!=0) || (c=='d' && pos.abs!=KMatSize-1)){
                    direction = c;
                    makeAMove(grid, pos, direction);

                    caseSelect = false;
                    displayGrid(grid,pos);

                    bool Streak = true;
                    while (Streak) {
                        Streak = false;

                        if (atLeastThreeInARow(grid, pos, howMany)) {
                            removalInRow(grid, pos, howMany);
                            displayGrid(grid, pos);
                            usleep(1000000);
                            Streak = true;
                        }

                        if (atLeastThreeInAColumn(grid, pos, howMany)) {
                            removalInColumn(grid, pos, howMany);
                            displayGrid(grid, pos);
                            usleep(1000000);
                            Streak = true;
                        }
                    }
                }
            }
        }
    }
    input.disableRawMode();
    return 0;
}
