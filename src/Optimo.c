/*En este programa la posición en 'x' y en 'y' se calculan a través de números aleatorios*/

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
            printf("Eliminando a la reina %d\n", index->x_pos);
            start = NULL;
            free(index);
            return;
        }
        else
        {
            printf("Eliminando a la reina %d\n", index->x_pos);
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
        printf("Reina [%d] = %d, %d\n", temporary->x_pos, temporary->x_pos, temporary->y_pos);
        temporary = temporary->following;
    }

    printf("\n");
}

void randomizeQueen(struct queen *changed_queen, struct queen *checkpoint)
{
    struct queen *index = start;
    changed_queen->y_pos = randomNumber(1, 8);
    while (index != checkpoint->following)
    {
        if (index->y_pos == changed_queen->y_pos)
        {
            changed_queen->y_pos = randomNumber(1, 8);
            index = start;
        }
        else
            index = index->following;
    }
}

int placeQueen (struct queen *checkpoint)
{
    int x_diff, y_diff, flag = 0, cntr = 1;
    float slope;
    struct queen *index = start;
    while (index != checkpoint)
    {
        if (cntr > 64)
            return 1;
        x_diff = index->x_pos - checkpoint->x_pos;
        y_diff = index->y_pos - checkpoint->y_pos;
        slope = (float)y_diff / (float)x_diff;
        printf("%d. Entre (%d, %d) y (%d, %d): x_diff = %d, y_diff = %d, slope = %f\n", cntr, checkpoint->x_pos, checkpoint->y_pos, index->x_pos, index->y_pos, x_diff, y_diff, slope);

        if (y_diff == 0 || slope == 1 || slope == -1)
        {
            // if (checkpoint->x_pos == 8 && flag == 1)
            //     return 1;
            flag = 1;
            checkpoint->y_pos = randomNumber(1, 8);
            // randomizeQueen(checkpoint, index);
            // checkpoint = index;
            index = start;
            printf("Repetir\n\n");
            cntr ++;
        }
        else
        {
            flag = 0;
            // if (index->following == start)
            //     index = checkpoint->following;
            // else
            index = index->following;
        }
    }
    return 0;
}

// void remakeQueens (void)
// {
//     struct queen *index = start;
//     for (int i = 0; i < 8; i ++)
//     {
//         index->y_pos = randomNumber(1,8);
//         index = index->following;
//     }
// }

void solveBoard(void)
{
    int i, repeat = 0;
    struct queen *index = start;
    for (i = 0; i < 8; i++)
    {
        repeat = placeQueen(index);
        printf("\n%d\n", repeat);
        if (repeat == 0)
            index = index->following;
        else
        {
            printf("Entra aquí\n");
            deleteQueens();
            createQueens(8);
            // remakeQueens();
            index = start;
            i = -1;
        }
        printQueens();
        printf("\n");
    }
    printf("Salió\n");
    return;

    // if (queen1->following == start)
    // {
    //     printf("\n\n\n");
    //     solveBoard(queen1->following);
    //     return 1;
    // }
}

void correctBoard(void)
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

void boardForTest(void)
{
    struct queen *index = start;
    index->x_pos = 1;
    index->y_pos = 5;
    index = index->following;

    index->x_pos = 2;
    index->y_pos = 7;
    index = index->following;

    index->x_pos = 3;
    index->y_pos = 4;
    index = index->following;

    index->x_pos = 4;
    index->y_pos = 1;
    index = index->following;

    index->x_pos = 5;
    index->y_pos = 3;
    index = index->following;

    index->x_pos = 6;
    index->y_pos = 8;
    index = index->following;

    index->x_pos = 7;
    index->y_pos = 6;
    index = index->following;

    index->x_pos = 8;
    index->y_pos = 2;
}

int testBoard (void)
{
    struct queen *queen1 = start, *queen2;
    int x_diff, y_diff;
    float slope;
    for (int i = 0; i < 7; i++)
    {
        queen2 = queen1->following;
        while (queen2 != start)
        {
            x_diff = queen2->x_pos - queen1->x_pos;
            y_diff = queen2->y_pos - queen1->y_pos;
            slope = (float)y_diff / (float)x_diff;

            if (y_diff == 0 || slope == 1 || slope == -1)
            {
                printf("Hubo problemas entre el %d y %d\n", queen1->x_pos, queen2->x_pos);
                printf("Entre (%d, %d) y (%d, %d): x_diff = %d, y_diff = %d, slope = %f\n", queen1->x_pos, queen1->y_pos, queen2->x_pos, queen2->y_pos, x_diff, y_diff, slope);
                return 0;
            }

            queen2 = queen2->following;
        }
    }
    return 1;
}

int main(void)
{
    srand(time(NULL));

    createQueens(8);
    printQueens();

    // testBoard();
    // solveBoard(&num_queens_done, index);

    // while (solved == 0){
    solveBoard();
    // }

    int test_board = testBoard();

    if (test_board == 1)
        printf("\nSIUUUUU\n");
    else
        printf("\nDOOOOO\n");

    // printQueens();
    deleteQueens();
    printQueens();



    // Para hacer pruebas 
    // createQueens(8);
    // boardForTest();
    // int test_board = testBoard();

    // if (test_board == 1)
    //     printf("\nSIUUUUU\n");
    // else
    //     printf("\nDOOOOO\n");

    // printQueens();
    // deleteQueens();
    // printQueens();
}