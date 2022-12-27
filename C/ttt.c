#include <stdio.h>
#include <stdlib.h>

#include "ttt_helpers.c"

/**
	try implemeting minimax?
	heuristic --- how many of the outcome states do i win in?
	at a depth of d (start with 2 moves)
	use an array of states.
*/

// }
// gets st having just made a comp move
// keep track of depth
// when 
int get_heur(state_t *st, int depth) {
	st->wins = 0;
	st->non_wins = 0;
	if (depth == 9) {
		// for (int i = 0; i < 9; i++){
		// 	printf("[%c] ",st->board[i/3][i%3]);
		// }
		// printf("\n");
		if (check_win(st->board) == PLAYER_WIN) {
			st->wins = 1;
		} else {
			st->non_wins = 1;
		}
		return st->wins;
	}
	// loop through sst->board
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (st->board[i][j] == ' ') {
				// possible player move
				// add x here
				state_t player_st;
				copy(player_st.board, st->board);
				player_st.board[i][j] = 'x';
				if (check_win(player_st.board) == COMP_WIN) {
					st->losses = 1;
					return 0;
				}

				// AGAIN LOOP THROUGH ADDING 'o' WHEREVER POSSIBLE
				// RECURSIVELY RETURN NUMBER OF WINS/NON_WINS
				for (int k = 0; k < SIZE; k++) {
					for (int l = 0; l < SIZE; l++) {
						if (player_st.board[k][l] == ' ') {
							// place a 'o' here and get_heur
							state_t comp_st;
							comp_st.wins = 0;
							comp_st.non_wins = 0;
							copy(comp_st.board, player_st.board);
							comp_st.board[k][l] = 'o';
							get_heur(&comp_st, depth + 1);

							// propagate wins
							st->wins += comp_st.wins;
							st->non_wins += comp_st.non_wins;
						}
					}
				}
			}
		}
	}

	// for each possible player move --> new player state
	// get number of comp wins for this state


	return st->wins/ st->non_wins;
}







// ALL THE AI
int ai() {
	int comp_move;
	int max_heur = 0;
	// for each possible comp move, get its heuristic value
	// return the move with the highest heuristic value
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == ' ') {
				// printf("i: %d j: %d\n", i, j);
				// comp_move = 3*i + j + 1;
				// printf("comp move %d\n", comp_move);
				state_t st;
				copy(st.board, board);
				st.board[i][j] = 'o';	// make new what if state
				// for (int i = 0; i < 9; i++)
				// 	printf("[%c] ", st.board[i/3][i%3]);
				// printf("\n");
				get_heur(&st, num_moves);		// should fill in heur field
				if (st.losses == 1) {
					printf("losing??\n");
					continue;
				}
				int heur = st.wins / st.non_wins;
				if (heur >= max_heur) {
					max_heur = heur;
					comp_move = 3*i + j + 1;
				}
				printf("[%d][%d] -- st wins: %d, st non_wins: %d, st losses: %d\n", i, j, st.wins, st.non_wins, st.losses);
			}
		}
	}
	// pseudo random response
	printf("comp move: %d\n", comp_move);
	return comp_move;
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
		status = check_win(board);
		if (status != PLAY)
			break;

		printf("::::::: COMP TURN :::::\n\n");
		int comp_move = ai();
		make_move(comp_move, 'o');
		print_board();

		status = check_win(board);
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