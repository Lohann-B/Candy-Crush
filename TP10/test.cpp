#include "test.h"
#include<iostream>
using namespace std;

void testThreeInAColumn(mat & grid, maPosition & pos, unsigned &howMany){
    atLeastThreeInAColumn(grid,pos,howMany);

    cout << pos.abs << " " << pos.ord << "\t" << howMany << endl;
}

void testThreeInARow(mat & grid, maPosition & pos, unsigned &howMany){
    atLeastThreeInARow(grid,pos,howMany);

    cout << "x : " << pos.abs << " y : " << pos.ord << "\t" << howMany << endl;
}

void affichMat(mat &grid){
    for (line &row : grid){
        for (unsigned elem : row){
            cout << elem << "\t";
        }
        cout << endl;
    }
}

void testRemovalColumn(mat &grid, maPosition &pos, const unsigned &howMany){
    affichMat(grid);
    cout << "--------" << endl;

    removalInColumn(grid, pos, howMany);

    affichMat(grid);
}

void testRemovalRow(mat &grid, maPosition &pos, const unsigned &howMany){
    affichMat(grid);
    cout << "--------" << endl;

    removalInRow(grid, pos, howMany);

    affichMat(grid);
}

int main(){
    mat grid2{
             {1,2,2,5,5},
             {1,1,1,6,2},
             {2,1,2,5,2},
             {1,1,3,4,2},
             {4,2,1,1,2},
             };

    mat grid{
             {1,2,5,3,5},
             {1,2,3,6,6},
             {6,1,6,6,6},
             {6,1,3,4,6},
             {4,2,2,5,5},
             };

    maPosition pos;
    unsigned howMany = 0;
    char direction;

    affichMat(grid2);

    atLeastThreeInARow(grid2, pos, howMany);

    testRemovalRow(grid2, pos, howMany);

    return 0;
}
