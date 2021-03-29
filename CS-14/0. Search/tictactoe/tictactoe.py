"""
Tic Tac Toe Player
"""

import math

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    count_X, count_O = 0, 0

    for row in board:
        for value in row:
            if value == X:
                count_X += 1
            if value == O:
                count_O += 1
    return X if count_X < count_O else O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    possible_actions = set()

    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                possible_actions.add( (i,j) )

    return possible_actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    # get row & col
    row = action[0]
    col = action[1]

    # validate move
    if board[row][col] != EMPTY:
        raise Exception('Not a valid action for the board')

    # perform deep copy
    new_board = initial_state()
    for i in range(3):
        for j in range(3):
            new_board[i][j] = board[i][j]

    # perform action on new_board
    new_board[row][col] = player(new_board)

    return new_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for x in range(3):
        # row win check
        if board[x][0]==X and board[x][1]==X and board[x][2]==X:
            return X
        elif board[x][0]==O and board[x][1]==O and board[x][2]==O:
            return O
        # col win check
        elif board[0][x]==X and board[1][x]==X and board[2][x]==X:
            return X
        elif board[0][x]==O and board[1][x]==O and board[2][x]==O:
            return O

    # diagnol win check
    if board[0][0]==X and board[1][1]==X and board[2][2]==X:
        return X
    elif board[0][2]==X and board[1][1]==X and board[2][0]==X:
        return X
    elif board[0][0]==O and board[1][1]==O and board[2][2]==O:
        return O
    elif board[0][2]==O and board[1][1]==O and board[2][0]==O:
        return O

    # return None if no winner
    return None

def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    return not (winner(board) == None) or len(actions(board)) == 0


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    utilities = { X : 1, O : -1, None : 0 }
    return utilities[winner(board)]


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    s = actions(board).copy().pop()
    #print('board action:', s)
    #print(min_value(board))
    #print('max_value():', max_value(board, s), ', min_value():', min_value(board, s))

    #p = [(action, max_value(result(board, action))) for action in actions(board)]
    #print(p)

    a = (-1,-1)

    if player(board) == X:
        possible_actions = []

        for action in actions(board):
            v = min_value(result(board, action))
            if v == 1:
                return action
            possible_actions.append((action, v))

        best_action = possible_actions[0]

        for (action, v) in possible_actions:
            if v > best_action[1]:
                best_action = (action, v)
        return best_action[0]
    else:

        possible_actions = []

        for action in actions(board):
            v = max_value(result(board, action))
            if v == -1:
                return action
            possible_actions.append((action, v))

        best_action = possible_actions[0]

        for (action, v) in possible_actions:
            if v < best_action[1]:
                best_action = (action, v)
        # print('actions:', possible_actions)
        return best_action[0]

    return s

def max_value(board):
    if terminal(board):
        return utility(board)

    # v = -infinity
    v = -100

    for action in actions(board):
        v = max(v, min_value(result(board, action)))

    return v


def min_value(board):
    if terminal(board):
        return utility(board)

    # v = infinity
    v = 100

    for action in actions(board):
        v = min(v, max_value(result(board, action)))

    return v
