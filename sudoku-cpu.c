#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

long backtracking = 0;

// Fonction d'affichage
void affichage (int grille[9][9])
{
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            printf( ((j+1)%3) ? "%d " : "%d|", grille[i][j]);
        }
        putchar('\n');
        if (!((i+1)%3))
            puts("------------------");
    }
    puts("\n\n");
}

bool absentSurLigne (int k, int grille[9][9], int i)
{
    for (int j=0; j < 9; j++)
        if (grille[i][j] == k)
            return false;
    return true;
}

bool absentSurColonne (int k, int grille[9][9], int j)
{
    for (int i=0; i < 9; i++)
        if (grille[i][j] == k)
            return false;
    return true;
}

bool absentSurBloc (int k, int grille[9][9], int i, int j)
{
    int _i = i-(i%3), _j = j-(j%3);  // ou encore : _i = 3*(i/3), _j = 3*(j/3);
    for (i=_i; i < _i+3; i++)
        for (j=_j; j < _j+3; j++)
            if (grille[i][j] == k)
                return false;
    return true;
}

bool estValide (int grille[9][9], int position)
{
    if (position == 9*9)
        return true;

    int i = position/9, j = position%9;    /* i: row, j: column */

    if (grille[i][j] != 0)
        return estValide(grille, position+1);

    for (int k=1; k <= 9; k++)
    {
        if (absentSurLigne(k,grille,i) && absentSurColonne(k,grille,j) && absentSurBloc(k,grille,i,j))
        {
            grille[i][j] = k;
            backtracking++;

            if ( estValide (grille, position+1) )
                return true;
        }
    }
    grille[i][j] = 0;

    return false;
}

int main (void)
{
    clock_t begin = clock();
    int grilleFacile[9][9] ={
        {0,9,3,0,5,0,0,0,4},
        {0,0,7,0,0,0,0,8,0},
        {5,6,0,9,0,0,0,0,7},
        {0,8,0,0,3,9,4,2,0},
        {0,4,0,8,2,7,0,3,0},
        {0,3,5,6,1,0,0,9,0},
        {9,0,0,0,0,5,0,4,2},
        {0,7,0,0,0,0,1,0,0},
        {3,0,0,0,4,0,8,7,0}
    };

    int grilleDifficile[9][9] ={
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,3,0,8,5},
        {0,0,1,0,2,0,0,0,0},
        {0,0,0,5,0,7,0,0,0},
        {0,0,4,0,0,0,1,0,0},
        {0,9,0,0,0,0,0,0,0},
        {5,0,0,0,0,0,0,7,3},
        {0,0,2,0,1,0,0,0,0},
        {0,0,0,0,4,0,0,0,9}
    };

    printf("Grille avant\n");
    affichage(grilleDifficile);

    estValide(grilleDifficile,0);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f\nbacktracking=%ld\nGrille apres\n", backtracking, time_spent);
    affichage(grilleDifficile);
}

