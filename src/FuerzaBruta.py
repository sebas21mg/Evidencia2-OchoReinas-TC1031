import random

board = [[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0]]

def print_b(board):
    for i in range(8):
        for j in range(8):
            print(board[i][j], end=" ")
        print()

def check_attack(i, j):
    for k in range(8):
        if board[i][k] == 1 or board[k][j] == 1:
            return True
    for k in range(8):
        for l in range(8):
            if (k + l == i + j) or (k - l == i - j):
                if board[k][l] == 1:
                    return True

counter = 0
counter_try = 1
total_try = 1

while True:
    i = random.randint(0, 7)
    j = random.randint(0, 7)

    if not check_attack(i, j):
        board[i][j] = 1
        counter += 1
        print("counter:", counter)
        print_b(board)

    counter_try += 1
    if counter_try > 1000000:
        counter = 0
        counter_try = 1
        board = [[0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0]]

    total_try += 1

    if counter == 8:
        print("Solution found in", total_try, "attempts")
        print_b(board)
        break
    
    
board_test = [[0,0,0,1,0,0,0,0],
[0,0,0,0,0,0,1,0],
[0,0,1,0,0,0,0,0],
[0,0,0,0,0,0,0,1],
[0,1,0,0,0,0,0,0],
[0,0,0,0,1,0,0,0],
[1,0,0,0,0,0,0,0],
[0,0,0,0,0,1,0,0]]


def print_b(board_test):
    for i in range(8):
        for j in range(8):
            print(board_test[i][j], end=" ")
        print()

def check_attack(i, j):
    for k in range(8):
        if board_test[i][k] == 1 or board_test[k][j] == 1:
            return True
    for k in range(8):
        for l in range(8):
            if (k + l == i + j) or (k - l == i - j):
                if board_test[k][l] == 1:
                    return True
                
while True:
    i = random.randint(0, 7)
    j = random.randint(0, 7)

    if not check_attack(i, j):
        board_test[i][j] = 1
        counter += 1
        print("counter:", counter)
        print_b(board_test)

    counter_try += 1
    if counter_try > 1000000:
        counter = 0
        counter_try = 1
        board_test = [[0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0]]

    total_try += 1

    if counter == 8:
        print("Solution found in", total_try, "attempts")
        print_b(board_test)
        break