#define SIZE 3

char board [SIZE][SIZE];
int num_moves;

enum status {
    DRAW = 0,
    PLAYER_WIN = 1,
    COMP_WIN = 2,
    PLAY = 3
};

/**
    MINIMAX TREE
    for a given board state if move is player
    then succ is all the possible comp moves that can come after
    and vice versa
*/
typedef struct state_t {
    char board[SIZE][SIZE];
    int move;   // 0 -> player move | 1 -> comp ove
    int heur;   // how favorable is this position for comp? more +ve is better
                // probably number of comp wins/ player wins from a state
    int wins;   // num of comp wins down this path
    int non_wins;
    int losses;
    struct state_t *succ; // array of state_t 
} state_t;

void init() {
    num_moves = 0;
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = ' ';
		}
	}
}

// malloc and create deep copy of board
void copy(char dest[SIZE][SIZE], char src[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            dest[i][j] = src[i][j];
            
        }
    }
}

void print_board(){
	printf("\n");
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++) {
			printf("[%c] ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// return -1 if failed
int make_move(int move, char token){
	//	1 2 3
	//	4 5 6
	//	7 8 9
    if (move < 1 || move > 9)
        return -1;
	int row = (move-1) / SIZE;
	int col = (move-1) % SIZE;
    if (board[row][col] != ' ')
        return -1;
    board[row][col] = token;
    num_moves++;
	return 0;
}

// TODO::: only works for SIZE 3
// check for win condition
int check_win(char curr_board[SIZE][SIZE]) {
    if (num_moves == 9)
        return DRAW;
    int status;

    for (int row = 0; row < SIZE; row++) {
        if (curr_board[row][0] != ' ')
            if ((curr_board[row][0] == curr_board[row][1]) && (curr_board[row][1] == curr_board[row][2])) {
                status = (curr_board[row][0] == 'x') ? PLAYER_WIN : COMP_WIN;
                return status;
            }
    }
    // check vertical wins
    for (int col = 0; col < SIZE; col++) {
        if (curr_board[0][col] != ' ')
            if ((curr_board[0][col] == curr_board[1][col]) && (curr_board[1][col] == curr_board[2][col])){
                status = (curr_board[0][col] == 'x') ? PLAYER_WIN : COMP_WIN;
                return status;
            }
                
    }
    // check /
    if (curr_board[2][0] != ' '){
        if ((curr_board[2][0] == curr_board[1][1] && curr_board[1][1] == curr_board[0][2])){
            status = (curr_board[2][0] == 'x') ? PLAYER_WIN : COMP_WIN;
            return status;
        }
    }
    // check backslash
    if (curr_board[0][0] != ' '){
        if ((curr_board[0][0] == curr_board[1][1] && curr_board[1][1] == curr_board[2][2])){
            status = (curr_board[0][0] == 'x') ? PLAYER_WIN : COMP_WIN;
            return status;
        }
    }


    return PLAY;
}