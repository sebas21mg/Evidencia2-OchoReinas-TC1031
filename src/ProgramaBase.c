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

        new_queen->x_pos = randomNumber(1, 8);
        new_queen->y_pos = randomNumber(1, 8);
        new_queen->id = queensAmount() + 1;
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

void deleteQueen(int id_in, int eliminar_uno)
{
    if (noQueens() == 1)
    {
        printf("No hay reinas\n");
        return;
    }
    struct queen *index = start;
    do
    {
        if (index->id == id_in)
        {
            // El new_queen a eliminar es el único en la lista
            if (queensAmount() == 1)
            {
                printf("Eliminando a la reina: %d\n", index->id);
                start = NULL;
                free(index);
                return;
            }
            // Hay más de un new_queen en la lista
            else
            {
                printf("Eliminando a la reina: %d\n", index->id);
                index->previous->following = index->following;
                index->following->previous = index->previous;

                if (index == start)
                    start = index->following;

                free(index);
                return;
            }
        }
    } while (index != start);
    printf("La reina %d no se puede eliminar\n", id_in);
}

void printQueens(void)
{
    if (noQueens() == 1)
    {
        printf("\nNo existen reinas a mostrar\n");
        return;
    }
    int i;
    struct queen *temporary;
    printf("Reinas en la lista:\n");

    temporary = start;
    int length = queensAmount();
    for (i = 0; i < length; i++)
    {
        printf("Reina [%d] = %d, %d\n", temporary->id, temporary->x_pos, temporary->y_pos);
        temporary = temporary->following;
    }

    printf("\n");
}

void randomizeQueen (struct queen *index)
{
    index->x_pos = randomNumber(1,8);
    index->y_pos = randomNumber(1,8);
}

int isSolved (int *last_i)
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
                // printf("Entre [%d] y [%d]: %d %d\n", queen_i->id, queen_j->id, x_diff, y_diff);
                if (x_diff == 0 || y_diff == 0){
                    randomizeQueen(queen_j);
                    return 0;
                }

                slope = (float)y_diff / (float)x_diff;
                // printf("Entre [%d] y [%d]: %g\n", queen_i->id, queen_j->id, slope);
                if (slope == 1 || slope == -1)
                {
                    randomizeQueen(queen_j);
                    return 0;
                }
    
            }

            queen_j = queen_j->following;
        }
        if (i > *last_i)
        {
            printf("Ya se ubicaron %d reinas\n", i + 1);
            *last_i = i;
        }
        queen_i = queen_i->following;
    }
    return 1;
}

void testBoard (void)
{
    struct queen *index = start;
    index->x_pos = 1;
    index->y_pos = 6;
    index = index->following;
    
    index->x_pos = 2;
    index->y_pos = 2;
    index = index->following;

    index->x_pos = 3;
    index->y_pos = 7;
    index = index->following;
    
    index->x_pos = 4;
    index->y_pos = 1;
    index = index->following;
    
    index->x_pos = 5;
    index->y_pos = 3;
    index = index->following;
    
    index->x_pos = 6;
    index->y_pos = 5;
    index = index->following;
    
    index->x_pos = 7;
    index->y_pos = 8;
    index = index->following;
    
    index->x_pos = 8;
    index->y_pos = 4;
}

int main(void)
{
    srand(time(NULL));

    createQueens(8);
        
    int solved = 0, last_i = -1;
    while (solved == 0){
        solved = isSolved(&last_i);
    }

    printQueens();
}