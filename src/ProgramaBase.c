/*En este programa la posición en 'x' y en 'y' se calculan a través de números aleatorios*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct queen
{
    int x_pos, y_pos, id;
    struct queen *following;
    struct queen *previous;
};

struct queen *start = NULL;

int randomNumber(int start, int end)
{
    return rand() % (end - start + 1) + start;
}

int noQueens(void)
{
    if (start == NULL)
        return 1;
    else
        return 0;
}

int queensAmount(void)
{
    if (noQueens() == 1)
        return 0;

    struct queen *temporary;
    int length = 0;
    temporary = start;
    do
    {
        length++;
        temporary = temporary->following;
    } while (temporary != start);
    return length;
}

void createQueens(int queens_amount)
{
    int i;
    for (i = 0; i < queens_amount; i++)
    {
        struct queen *new_queen = malloc(sizeof(struct queen));
        if (new_queen == NULL)
        {
            printf("No se puede crear una nueva reina");
            return;
        }

        new_queen->x_pos = i + 1;
        new_queen->y_pos = randomNumber(1, 8);

        if (noQueens() == 1)
        {
            new_queen->previous = new_queen;
            new_queen->following = new_queen;
            start = new_queen;
        }
        else
        {
            new_queen->previous = start->previous;
            new_queen->following = start;
            start->previous->following = new_queen;
            start->previous = new_queen;
        }
    }
}

void deleteQueens()
{
    if (noQueens() == 1)
    {
        printf("La lista está vacía\n");
        return;
    }
    struct queen *index = start->previous;
    while (start != NULL)
    {
        if (index == start)
        {
            // printf("Eliminando a la reina %d\n", index->x_pos);
            start = NULL;
            free(index);
            return;
        }
        else
        {
            // printf("Eliminando a la reina %d\n", index->x_pos);
            index->previous->following = index->following;
            index->following->previous = index->previous;

            struct queen *temporary = index;
            index = index->previous;
            free(temporary);
        }
    }
}

void printQueens(void)
{
    printf("\n");
    if (noQueens() == 1)
    {
        printf("No existen reinas a mostrar\n");
        return;
    }
    int i;
    struct queen *temporary;

    temporary = start;
    int length = queensAmount();
    for (i = 0; i < length; i++)
    {
        printf("Reina [%d] = (%d, %d)\n", temporary->x_pos, temporary->x_pos, temporary->y_pos);
        temporary = temporary->following;
    }

    printf("\n");
}

void randomizeQueen (struct queen *index)
{
    index->x_pos = randomNumber(1,8);
    index->y_pos = randomNumber(1,8);
}

int isSolved ()
{
    int x_diff, y_diff;
    float slope;
    struct queen *queen_i = start;
    for (int i = 0; i < 8; i++)
    {
        struct queen *queen_j = queen_i->following;
        while (queen_j != start)
        {
            if (queen_i != queen_j){

                x_diff = queen_j->x_pos - queen_i->x_pos;
                y_diff = queen_j->y_pos - queen_i->y_pos;
                if (x_diff == 0 || y_diff == 0){
                    randomizeQueen(queen_j);
                    return 0;
                }

                slope = (float)y_diff / (float)x_diff;
                if (slope == 1 || slope == -1)
                {
                    randomizeQueen(queen_j);
                    return 0;
                }
    
            }

            queen_j = queen_j->following;
        }
        queen_i = queen_i->following;
    }
    return 1;
}

int main(void)
{
    srand(time(NULL));

    createQueens(8);
        
    int solved = 0;
    while (solved == 0){
        solved = isSolved();
    }

    printQueens();
}