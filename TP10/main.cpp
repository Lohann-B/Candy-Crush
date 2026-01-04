#include "game.h"

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

void goTo (unsigned x, unsigned y) {
    cout << "\033[" << y << ";" << x << "H" << flush;
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

// --- DECLARATION ELEMENTS GRAPHIQUES TERMINAL ---
const vector<string> KGrandeCase{
    "   ________________________________________________________________________________________",
    " .                                                                                          .",
    "|                                                                                            |",
    "|                                                                                            |",
    "|                                                                                            |",
    "|                                                                                            |",
    "|                                                                                            |",
    " ' _________________________________________________________________________________________'",
};

const vector<string> KPetiteCase{
    "       ________________________________________________________________________________",
    "     .                                                                                  .",
    "    |                                                                                    |",
    "    |                                                                                    |",
    "    |                                                                                    |",
    "    |                                                                                    |",
    "     ' _________________________________________________________________________________'",
};

const vector<string> KPLAY{
    " _____ __    _____ __ __ ",
    "|  _  |  |  |  _  |  |  |",
    "|   __|  |__|     |_   _|",
    "|__|  |_____|__|__| |_|  ",
};

const vector<string> KDuel{
    " ____          _",
    "|    \\ _ _ ___| |",
    "|  |  | | | -_| |",
    "|____/|___|___|_|",
};

const vector<string> KLeaderboard{
    " __              _         _                 _ ",
    "|  |   ___ ___ _| |___ ___| |_ ___ ___ ___ _| |",
    "|  |__| -_| .'| . | -_|  _| . | . | .'|  _| . |",
    "|_____|___|__,|___|___|_| |___|___|__,|_| |___|",
};


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

void affichVectCoulStr(const vector<string> & v){
    vector<int> colors = {31, 33, 32, 34, 35, 36, 0};

    unsigned i =0;
    for (string elem : v){
        couleur(colors[i % colors.size()]);

        cout << elem << endl;
        usleep(30000);

        i++;
    }
    cout << endl;
}

void popElemDecor(const vector<string> &Element,size_t x,size_t y, size_t Delay = 0){
    for (size_t i = 0; i < Element.size(); ++i){
        goTo(x,y-i);
        cout << Element[Element.size()-1-i] << flush;
        usleep(Delay);
    }
}

void affichElemDecor(const vector<string> &Element,size_t x,size_t y, size_t Delay = 0){
    for (size_t i = 0; i < Element.size(); ++i){
        goTo(x,y+i);
        cout << Element[i] << flush;
        usleep(Delay);
    }
}

void affichDecor(size_t Delay = 0){
    vector <string> Decor1{
        "      _ _ _ _",
        "    .         .",
        "  /             \\",
        " /      --    ---\\",
        "|--   -    ---    |",
        "|  ---            |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
    };

    vector <string> Decor2{
        "  _ _ _",
        ".       .",
        "-  ---   |",
        " --   -  |",
        "       --|",
        "         |",
        "         |",
        "         |",
        "         |",
        "         |",
        "         |",
        "         |",
    };

    const vector <string> Decor3{
        "               .",
        "              /   .",
        "         =  =     . .",
        "      =        = '    .",
        "     =          =  __ .",
        ". __ =          =",
        " .    =        =",
        "  .  ;   =  =",
        "    .   /",
        "       .",
    };

    vector <string> Decor4{
        "   _ _ _",
        " .       .",
        "|--  --   ",
        "|  --  ---",
        "|         ",
        "|         ",
        "|         ",
        "|         ",
        "|         ",
        "|         ",
        "|         ",
        "|         ",
    };

    vector <string> Decor5{
        "      _ _ _ _",
        "    .         .",
        "  /             \\",
        " /            ---\\",
        "|   ----  ---     |",
        "|---    --        |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
        "|                 |",
    };

    vector<int> colors = {31, 33, 32, 34, 35, 36, 0};
    couleur(1);
    for (size_t i = 0; i < Decor3.size(); ++i){
        couleur(colors[i % colors.size()]);
        goTo(68,30+i);
        cout << Decor3[i] << flush;
    }

    couleur(KMAgenta);
    popElemDecor(Decor1,25,42,Delay);
    if (Delay !=0) usleep(300000);

    couleur(KRouge);
    popElemDecor(Decor5,117,42,Delay);
    if (Delay !=0) usleep(300000);

    couleur(KVert);
    popElemDecor(Decor2,44,42,Delay);
    if (Delay !=0) usleep(300000);

    couleur(KCyan);
    popElemDecor(Decor4,107,42,Delay);

    couleur(KReset);
}

// --- INITIALISATION ---
size_t initMatSize(){
    string input;
    size_t size;
    vector <string> sizeRequest {
        "",
        "",
        "                           ________________________________________________________________________________________",
        "                         .                                                                                           .",
        "                        |                                                                                             |",
        "                        |                         Veuillez saisir la taille de la matrice :                           |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                         ' __________________________________________________________________________________________'",
    };

    clearScreen();
    affichVectStr(sizeRequest);

    while (true){
        goTo(93,6);
        input = inputUser(2);

        if (input.empty()) {
            clearScreen();
            affichVectStr(sizeRequest);

            goTo(60,8);
            couleur(KRouge);
            cout <<"Errreur : Saisie vide ! " <<  flush;
            couleur(KReset);
            continue;
        }

        size = stoi(input);

        if (size < 4){
            clearScreen();
            affichVectStr(sizeRequest);

            goTo(51,8);
            couleur(KRouge);
            cout << "Erreur : Veuillez saisir une taille >= 4 !" <<endl;
            couleur(KReset);
        }
        else break;
    }

    return size;

}

unsigned initNbCandies(){
    string input;
    unsigned nb;
    vector <string> nbRequest {
        "",
        "",
        "                           ________________________________________________________________________________________",
        "                         .                                                                                           .",
        "                        |                                                                                             |",
        "                        |                         Veuillez saisir le nombre de bonbons :                              |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                        |                                                                                             |",
        "                         ' __________________________________________________________________________________________'",
    };

    clearScreen();
    affichVectStr(nbRequest);
    while (true){
        goTo(90,6);
        input = inputUser(1);

        if (input.empty()) {
            clearScreen();
            affichVectStr(nbRequest);

            goTo(60,8);
            couleur(KRouge);
            cout <<"Errreur : Saisie vide ! " <<  flush;
            couleur(KReset);
            continue;
        }

        nb = stoi(input);

        if (nb > 7 || nb < 2){
            clearScreen();
            affichVectStr(nbRequest);

            goTo(51,8);
            couleur(KRouge);
            cout << "Erreur : Veuillez saisir un nombre compris entre 2 et 7 ! " <<endl;
            couleur(KReset);
        }
        else break;
    }

    return nb;

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

void displayMenu(const unsigned &select){
    clearScreen();

    if (select==0){
        couleur(1);
        couleur(5);
    }
    couleur(KMAgenta);
    affichElemDecor(KGrandeCase, 35,1);
    affichElemDecor(KPLAY, 70,3);
    couleur(KReset);

    if (select==1){
        couleur(1);
        couleur(5);
    }
    couleur(KCyan);
    affichElemDecor(KPetiteCase, 35,10);
    affichElemDecor(KDuel, 74,11);
    couleur(KReset);

    if (select==2){
        couleur(1);
        couleur(5);
    }
    couleur(KVert);
    affichElemDecor(KPetiteCase, 35,18);
    affichElemDecor(KLeaderboard, 58,19);
    couleur(KReset);

    affichDecor();
}


// --- MAIN ---
void moveMenu (const char &c, unsigned &select){
    if (c=='z'){
        if (select==0) select = 2;
        else -- select;
    }
    else if (c=='s'){
        if (select==2) select = 0;
        else ++ select;
    }
}

unsigned classicMode(mat &grid, size_t &KMatSize, unsigned &KNbCandies, maPosition &pos){
    char c;
    bool gameStarted = false;
    bool caseSelect = false;

    while (cin.get(c) && c!=27){
        if (c==10 && !gameStarted){

            KMatSize = initMatSize();
            usleep(100000);

            KNbCandies = initNbCandies();
            usleep(1000000);

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
                    char direction = c;
                    makeAMove(grid, pos, direction);

                    caseSelect = false;
                    displayGrid(grid,pos);

                    bool Streak = true;
                    maPosition streakPos;
                    unsigned howMany;
                    while (Streak) {
                        Streak = false;

                        if (atLeastThreeInARow(grid, streakPos, howMany)) {
                            removalInRow(grid, streakPos, howMany);
                            displayGrid(grid, pos);
                            usleep(1000000);
                            Streak = true;
                        }

                        if (atLeastThreeInAColumn(grid, streakPos, howMany)) {
                            removalInColumn(grid, streakPos, howMany);
                            displayGrid(grid, pos);
                            usleep(1000000);
                            Streak = true;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void loadingScreen(){
    const vector <string> KCandyCrush{
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

    couleur(KReset);
    affichVectCoulStr(KCandyCrush);

    couleur(KFlash);
    couleur(KJaune);
    affichVectStr(PressEnter);
    couleur(KReset);

    couleur(KCyan);
    affichDecor(15000);
    couleur(KReset);
}

int main(){
    // - Déclaration
    mat grid;
    size_t KMatSize;
    unsigned KNbCandies;

    maPosition pos;

    clearScreen();
    loadingScreen();

    InputManager input;
    input.enableRawMode();

    bool loadingScreen = true;

    unsigned select = 0;

    char c;
    while (cin.get(c) && c!=27){
        if (loadingScreen){
            if (c == 10){
                displayMenu(select);
                loadingScreen = false;
            }
        }
        else{
            if (c==10) break;
            moveMenu(c,select);
            displayMenu(select);
        }
    }
    if (select == 0) classicMode(grid, KMatSize, KNbCandies, pos);

    cout << "Votre choix est " << select << endl;

    input.disableRawMode();
    return 0;
}
