#ifndef TEST_H
#define TEST_H
#include "game.h"

void testThreeInARow(mat & grid, maPosition & pos, unsigned &howMany);
void testThreeInAColumn(mat & grid, maPosition & pos, unsigned &howMany);

void affichMat(mat &grid);

void testRemovalColumn(mat &grid, maPosition &pos, const unsigned &howMany);

void testRemovalRow(mat &grid, maPosition &pos, const unsigned &howMany);

#endif // TEST_H
