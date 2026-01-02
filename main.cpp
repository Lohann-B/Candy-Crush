#include <iostream>
#include <vector>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;
typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

struct maPosition {
    unsigned abs=0;
    unsigned ord=0;
};

maPosition pos;

void clearScreen () {
    cout << "\033[H\033[2J";
}

const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

void initGrid (mat & grid, const size_t & matSize){
    size_t KNbCandies=6;
    for (size_t i=0; i<matSize; ++i){
        for (size_t j=0; j<matSize; ++j){
            grid[i][j]=rand()%KNbCandies+1;
        }
    }
}



void displayGrid(const mat &grid) {
    clearScreen();
    couleur(37);
    couleur(40);
    for (size_t i = 0; i < grid.size(); ++i) {
        couleur(37);
        couleur(40);
        cout << ' ';
        for (size_t j = 0; j < grid.size()*4+1; ++j){
            couleur(37);
            couleur(40);
            if(j%4==0){
                cout << "+";
            } else {
                cout << "-";
            }
            couleur(KReset);
        }
        couleur(37);
        couleur(40);
        cout << ' ';
        couleur(KReset);
        cout << endl;
        couleur(37);
        couleur(40);
        cout << " | ";
        for (size_t j = 0; j < grid.size(); ++j) {
            couleur(KReset);
            couleur(30+grid[i][j]);
            couleur(40);
            if(i==pos.ord && pos.abs==j){
                couleur(KReset);
                couleur(5);
            }
            cout << grid[i][j];
            couleur(KReset);
            couleur(37);
            couleur(40);
            cout << " | ";
            couleur(KReset);
        }
        couleur(KReset);
        cout << endl;
    }
    couleur(37);
    couleur(40);
    cout << ' ';
    couleur(KReset);
    for (size_t j = 0; j < grid.size()*4+1; ++j){
        couleur(37);
        couleur(40);
        if(j%4==0){
            cout << "+";
        } else {
            cout << "-";
        }
        couleur(KReset);
    }
    couleur(37);
    couleur(40);
    cout << ' ';
    couleur(KReset);
    cout << ' ';
    cout << endl;
}

void switchC(mat & grid, const maPosition & pos, const char & direction){
    int tmp = grid[pos.ord][pos.abs];
    int tmp2;
    if (direction=='4' && pos.abs!=0){
        tmp2=grid[pos.ord][pos.abs-1];
        grid[pos.ord][pos.abs-1]=tmp;
        grid[pos.ord][pos.abs]=tmp2;
    }
    if (direction=='2' && pos.ord<grid.size()-1){
        tmp2=grid[pos.ord+1][pos.abs];
        grid[pos.ord+1][pos.abs]=tmp;
            grid[pos.ord][pos.abs]=tmp2;
    }
    if (direction=='6' && pos.abs<grid.size()-1){
        tmp2=grid[pos.ord][pos.abs+1];
        grid[pos.ord][pos.abs+1]=tmp;
        grid[pos.ord][pos.abs]=tmp2;
    }
    if (direction=='8' && pos.ord!=0){
        tmp2=grid[pos.ord-1][pos.abs];
        grid[pos.ord-1][pos.abs]=tmp;
        grid[pos.ord][pos.abs]=tmp2;
    }
}

char input() {
    char c = getchar();
    if (c == '\033') {
        getchar();
        char d = getchar();
        return d;
    }
    return c;
}

void move(mat & grid, maPosition & pos, char direction){
    if (direction=='D' && pos.abs!=0){
        pos.abs -= 1;
    }
    if (direction=='B' && pos.ord<grid.size()-1){
        pos.ord += 1;
    }
    if (direction=='C' && pos.abs<grid.size()-1){
        pos.abs += 1;
    }
    if (direction=='A' && pos.ord!=0){
        pos.ord -= 1;
    }
}

bool atLeastThreeInAColumn (const mat & grid, maPosition & posi, unsigned & howMany){
    howMany=0;
    while (mat[posi.ord][posi.abs+1]==mat[posi.ord][posi.abs]){
        posi.abs+=1;
        howMany+=1;
    }
    if (howMany>2){
        return(true);
    } else {
        return(false);
    }
}

bool atLeastThreeInARow (const mat & grid, maPosition & posi, unsigned & howMany){
    return(1);
    howMany=0;
    while (mat[posi.ord+1][posi.abs]==mat[posi.ord][posi.abs]){
        posi.ord+=1;
        howMany+=1;
    }
    if (howMany>2){
        return(true);
    } else {
        return(false);
    }
}

void removalInColumn (mat & grid, const maPosition & pos, unsigned  howMany){}

void removalInRow (mat & grid, const maPosition & pos, unsigned  howMany){}

void jeu(){
    pos.abs =0;
    pos.ord=0;
    cout << "Taille de la grille : ";
    size_t t;
    cin >> t;
    mat grid(t, line(t));
    initGrid(grid, t);
    int coup=15;
    couleur(KReset);
    while (coup>0) {
        for (int i=0; i<grid.size();++i){
            for (int j=0; j<grid[i].size();++j){
            }
        }
        char d = toupper(input());
        if (d=='D' || d=='B' || d=='C' || d=='A'){move(grid, pos, d);} else {if (isdigit(d)) {switchC(grid, pos,d); coup-=1;}}
        displayGrid(grid);
        couleur(KReset);
        cout << "Coups restants : " << coup << endl;
        couleur(KReset);
    }
    cout << "Game Over" << endl;
    if(false){
        jeu();
    } else {
        cout << "A bientot" << endl;
    }
}
int main(){
    jeu();

    return 0;
}
