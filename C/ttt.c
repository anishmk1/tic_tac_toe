#include <stdio.h>
#include <stdlib.h>

#include "ttt_helpers.c"


// ALL THE AI
int ai() {
	int comp_move;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				printf("i: %d j: %d\n", i, j);
				comp_move = 3*i + j + 1;
				printf("comp move %d\n", comp_move);
				return comp_move;
			}
		}
	}
	// pseudo random response
	return -1;
}

int main(){

	printf("<<<<<<<< TTT >>>>>>>>\n");
	// char ch;
	int input;

	init();
	print_board();
	// int turn = 0;		// 0 --> player / 1 --< comp
	int status = PLAY;
	while (status == PLAY) {
		do {
			printf("type from 1 to 9: ");
			input = getchar() - 48;
			getchar();
		} while (make_move(input, 'x') < 0);
		print_board();
		status = check_win();
		if (status != PLAY)
			break;

		printf("::::::: COMP TURN :::::\n\n");
		int comp_move = ai();
		make_move(comp_move, 'o');
		print_board();

		status = check_win();
	}

	switch (status) {
		case DRAW:
			printf("Draw game\n");
			break;
		
		case PLAYER_WIN:
			printf("Player win\n");
			break;

		case COMP_WIN:
			printf("Comp win\n");
			break;

		default:
			printf("default\n");
			break;
	}


	printf("GAME OVER\n");
}


/// Em Sandeham Ledu