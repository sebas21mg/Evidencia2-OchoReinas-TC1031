// En este programa la posición en 'x' y en 'y' se calculan a través de números aleatorios

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct queen
{
    int x_pos, y_pos;
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

void printBoard(void)
{
    printf("\n");
    if (noQueens() == 1)
    {
        printf("No existen reinas a mostrar\n");
        return;
    }

    int i, j;
    struct queen *temporary = start;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (temporary->y_pos == i + 1)
            {
                if (temporary->x_pos == j + 1)
                    printf("X  ");
            }
            else
                printf("0  ");
            temporary = temporary->following;
        }
        temporary = start;
        printf("\n");
    }
    printf("\n");
}

int placeQueen(struct queen *checkpoint, int *attempts)
{
    int x_diff, y_diff, cntr = 1;
    float slope;
    struct queen *index = start;
    while (index != checkpoint)
    {
        if (cntr > 128)
            return 1;
        x_diff = index->x_pos - checkpoint->x_pos;
        y_diff = index->y_pos - checkpoint->y_pos;
        slope = (float)y_diff / (float)x_diff;

        if (y_diff == 0 || slope == 1 || slope == -1)
        {
            checkpoint->y_pos = randomNumber(1, 8);
            *attempts = *attempts + 1;
            index = start;
            cntr++;
        }
        else
            index = index->following;
    }
    return 0;
}

void solveBoard(int *attempts)
{
    int i, repeat = 0;
    struct queen *index = start;
    for (i = 0; i < 8; i++)
    {
        repeat = placeQueen(index, attempts);
        if (repeat == 0)
            index = index->following;
        else
        {
            deleteQueens();
            createQueens(8);
            index = start;
            i = -1;
        }
    }
    return;
}

int main(void)
{
    srand(time(NULL));
    int attempts = 1;

    createQueens(8);
    printf("\nReinas iniciales:\n");
    printQueens();
    printBoard();
    solveBoard(&attempts);
    printf("Tablero exitoso con %d intentos:\n", attempts);
    printQueens();
    printBoard();
    deleteQueens();
}