char board [3][3];
int num_moves;

enum status {
    DRAW = 0,
    PLAYER_WIN = 1,
    COMP_WIN = 2,
    PLAY = 3
};

void init() {
    num_moves = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			board[i][j] = ' ';
		}
	}
}

void print_board(){
	printf("\n");
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
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
	int row = (move-1) / 3;
	int col = (move-1) % 3;
    if (board[row][col] != ' ')
        return -1;
    board[row][col] = token;
    num_moves++;
	return 0;
}

// check for win condition
int check_win() {
    if (num_moves == 9)
        return DRAW;

    



    return PLAY;
}