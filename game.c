//Name: Shane Bowen
//ID: R00149085
//Class: SD2-A

//------------------------------------
//	Include Libraries
//------------------------------------

#include "game.h"
#define SIZE 3 // Grid Size

//---------------------------------------------
//	01. FUNCTION create_new_game (IMPLEMENTED)
//---------------------------------------------
game* create_new_game(char* p1, char* p2, int im) {
	//1. We declare the variable to be returned
	game* res = NULL;

	//2. We create memory space for it with malloc.
	res = (game*)malloc(1 * sizeof(game));

	//3. We use the names passed as arguments to initialise p1 and p2.
	(*res).p1 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*res).p1, p1);

	(*res).p2 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*res).p2, p2);

	//4. We set the mode based on the names of the players.
	// Human vs. Human --> mode = 0
	// Human vs. Computer --> mode = 1
	// Computer vs. Human --> mode = 2
	// Computer vs. Computer --> mode = 3
	int mode = 0;
	if (strcmp(p1, "Computer") == 0)
		mode += 2;
	if (strcmp(p2, "Computer") == 0)
		mode += 1;
	(*res).mode = mode;

	//5. We set the status to be 1; (i.e., player1 moves first)
	(*res).status = 1;

	//6. We initialise the board so that all its positions are empty
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			(*res).board[i][j] = ' ';

	//7. We use the im passed as arguments to initialise intelligent_machine.
	if (im == 0)
		(*res).intelligent_machine = False;
	else
		(*res).intelligent_machine = True;

	//8. ---Computer Intelligent Movement Only --- We initialise the avenues
	//avenue 0 --> [0,1,2]
	//avenue 1 --> [3,4,5]
	//avenue 2 --> [6,7,8]
	//avenue 3 --> [0,3,6]
	//avenue 4 --> [1,4,7]
	//avenue 5 --> [2,5,8]   
	//avenue 6 --> [0,4,8]
	//avenue 7 --> [2,4,6]   

	(*res).avenue_positions[0][0] = 0;
	(*res).avenue_positions[0][1] = 1;
	(*res).avenue_positions[0][2] = 2;

	(*res).avenue_positions[1][0] = 3;
	(*res).avenue_positions[1][1] = 4;
	(*res).avenue_positions[1][2] = 5;

	(*res).avenue_positions[2][0] = 6;
	(*res).avenue_positions[2][1] = 7;
	(*res).avenue_positions[2][2] = 8;   

	(*res).avenue_positions[3][0] = 0;
	(*res).avenue_positions[3][1] = 3;
	(*res).avenue_positions[3][2] = 6;

	(*res).avenue_positions[4][0] = 1;
	(*res).avenue_positions[4][1] = 4;
	(*res).avenue_positions[4][2] = 7;

	(*res).avenue_positions[5][0] = 2;
	(*res).avenue_positions[5][1] = 5;
	(*res).avenue_positions[5][2] = 8;    

	(*res).avenue_positions[6][0] = 0;
	(*res).avenue_positions[6][1] = 4;
	(*res).avenue_positions[6][2] = 8;

	(*res).avenue_positions[7][0] = 2;
	(*res).avenue_positions[7][1] = 4;
	(*res).avenue_positions[7][2] = 6;    

	//9. ---Computer Intelligent Movement Only --- We initialise all avenues to state2
	int size = 2 * SIZE + 2;
	for (int i = 0; i < size; i++)
		(*res).avenue_states[i] = 2;

	//10. We return res
	return res;
}

//-------------------------------------
//	02. FUNCTION display_board_content
//-------------------------------------
void display_board_content(game* g) {
	// We print the header of the board status
	printf("\n\t-------------\n");
	printf("\tBOARD STATUS \n");
	printf("\t-------------\n");

	// We print the Board Content
	int i, j, k;

	// For each row
	for (i = 0; i < SIZE; i++) {
		printf("\n\t|---|---|---|\t|---|---|---|\n");
		printf("\t|");

		// For each column
		for (j = 0; j < SIZE; j++) {
			printf(" %c |", (*g).board[i][j]); //Display Content inside box
		}
		printf("\t|");

		// For player hints
		k = j;
		for (j = 0; j < SIZE; j++) {
			printf(" %d |", k*i + j);
		}
	}
	printf("\n\t|---|---|---|\t|---|---|---|\n");
}

//------------------------------------
//	03. FUNCTION display_game_status
//------------------------------------
void display_game_status(game* g) {
	//1. We clean the screen by printing 50 empty lines
	int i;
	for (i = 0; i < 50; i++) {
		printf("\n");
	}
	//2. We call to display_board_content to print both (1) Indicative Indexes and (2) Actual Board Content
	display_board_content(g);

	//3. We print the header of game status
	printf("\n\t-------------\n");
	printf("\tGAME STATUS \n");
	printf("\t-------------\n");

	//4. We display the status
	// status = 1 --> Game is on. Player P1_name moves next.
	// status = 2 --> Game is on. Player P2_name moves next.
	// status = 3 --> Game is over. Player P1_name has won.
	// status = 4 --> Game is over. Player P2_name has won.
	// status = 5 --> Game is over. Draw.
	switch ((*g).status) {
	case 1:
		printf("\tGame is on. Player %s moves next\n\n", (*g).p1);
		break;  // P1 moves next
	case 2:
		printf("\tGame is on. Player %s moves next\n\n", (*g).p2);
		break;  // P2 moves next
	case 3:
		printf("\tGame is over. Player %s has won\n\n", (*g).p1);
		break;  // P1 has won
	case 4:
		printf("\tGame is over. Player %s has won\n\n", (*g).p2);
		break;  // P2 has won
	default:
		printf("\tGame is over. Game finished with a draw\n\n");
		break; // Draw
	}
}

//--------------------------------------------------
// 04. gen_num (IMPLEMENTED)
//--------------------------------------------------
int gen_num(int lb, int ub) {
	//1. We create the output variable with an initial value.
	int res = 0;

	//2. We assign num to a random value in the desired range
	res = (rand() % (ub - lb)) + lb;

	//3. We return the output variable
	return res;
}

//--------------------------------------------------
// 05. FUNCTION my_getchar (IMPLEMENTED)
//--------------------------------------------------
char my_get_char() {
	//1. We create the variable to be returned
	char res = ' ';

	//2. We create an extra variable to consume any other characters entered until a return is pressed
	boolean line_consumed = False;
	char dummy_char = ' ';

	//3. We consume the first char entered, i.e., the one we are interested at
	res = getchar();

	//4. While still there are remaining characters
	while (line_consumed == False) {
		//4.1. We consume the next character
		dummy_char = getchar();

		//4.2. If the new character is the end of line one, we can ensure we have consumed the entire line.
		if (dummy_char == '\n')
			line_consumed = True;
	}

	//5. We return res
	return res;
}

//------------------------------------
//	06. FUNCTION is_position_empty
//------------------------------------
boolean is_position_empty(game* g, int pos) {
	//1. We create the variable to be returned
	boolean res = False;

	//2. We check if the index is a valid one and if the board is empty at that index.
	int size = 8;
	if (pos >= 0 && pos <= size) {
		//If it is valid and free, we return True.
		if (((*g).board[pos / SIZE][pos % SIZE]) == ' ') {
			res = True;
		}

		//Otherwise, we return False and write a warning message.
		else {
			if ((*g).status == 1 && ((*g).mode == 0 || (*g).mode == 1)) {
				printf("\tThe position is already busy. Try again!\n");
			}
			else if ((*g).status == 2 && ((*g).mode == 0 || (*g).mode == 2)) {
				printf("\tThe position is already busy. Try again!\n");
			}
		}
	}

	//3. We return res
	return res;
}

//---------------------------------------
//	07. FUNCTION user_get_movement_index
//---------------------------------------
int user_get_movement_index(game* g) {

	//1. We create the variable to be returned
	int res = -1;

	//2. We create a boolean variable to control that we have received a valid movement index.
	boolean valid = False;

	//3. We create a char variable to control the index we are receiving by keyboard.
	char charValue = ' ';

	//4. While we have not received a valid movement index.
	while (!valid) {
		//We print a message asking for a new movement.
		printf("\tEnter a position from 0 to %d : ", 8);
		//We call to my_get_char to get the index and we convert it to an integer.
		charValue = my_get_char();
		if (charValue >= '0' && charValue <= '8') {
			//We call to is_position_empty to check that the index is a valid one.
			res = atoi(&charValue); //Convert String to Integer
			if (is_position_empty(g, res)) {
				valid = True;
			}
		}
		else {
			printf("\tInvalid position. Try again!\n");
		}
	}

	//5. We return res
	return res;
}

//-------------------------------------------
//	08. FUNCTION computer_get_movement_index
//-------------------------------------------
int computer_get_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We create a boolean variable to control that we have received a valid movement index.
	boolean valid = False;

	//3. While we have not received a valid movement index.
	while (!valid) {
		//If the machine is not intelligent we generate a random index to move for.
		if (!(*g).intelligent_machine) {
			res = gen_num(0, 9);
		}
		//Otherwise we call to the function intelligent_selection to pick the best index to move for.
		else {
			res = intelligent_selection(g);
		}

		//In both cases we call to is_position_empty to double check that the selected index is a valid one.
		if (is_position_empty(g, res)) {
			valid = True;
		}
	}

	//4. We display a message of pressing a key to continue
	printf("\tPress any key to continue...\n");

	//5. We call to my_get_char() to wait for the user to press a key before continuing.
	my_get_char();

	//6. We return res
	return res;
}

//---------------------------------------
//	09. FUNCTION get_next_movement_index
//---------------------------------------
int get_next_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We ask for the next valid movement to be selected.
	//Depending on the game status and the players name we call to the function
	//user_get_movement_index or computer_get_movement_index

	if ((*g).status == 1) {
		if ((*g).mode == 0 || (*g).mode == 1){
			res = user_get_movement_index(g);
		}
		else{
			res = computer_get_movement_index(g);
		}
	}
	else if ((*g).status == 2) {
		if ((*g).mode == 0 || (*g).mode == 2){
			res = user_get_movement_index(g);
		}
		else{
			res = computer_get_movement_index(g);
		}
	}

	//3. We return res
	return res;
}

//------------------------------------
//	10. FUNCTION is_there_a_winner
//------------------------------------
int is_there_a_winner(game* g) {
	//1. We create the variable to be returned
	int res = 0;

	//2. We check the 8 possible ways (avenues) of winning the game,
	//to see if either player P1 or player P2 have won in any of them.

	int i, j;
	int size = 8;
	char currentBox;
	char nextBox;
	boolean checkedAvenue;
	int *avenue = NULL;

	for (i = 0; i < size; i++) {
		
		// check if avenue can have winner
		checkedAvenue = True;

		// Current avenue
		avenue = (*g).avenue_positions[i];

		for (j = 0; j < SIZE - 1; j++) {

			currentBox = (*g).board[*(avenue + j) / SIZE][*(avenue + j) % SIZE];
			nextBox = (*g).board[*(avenue + j + 1) / SIZE][*(avenue + j + 1) % SIZE];

			// avenue can't have a winner
			if (currentBox != nextBox || currentBox == ' '){
				checkedAvenue = False;
			}

			printf("INVALID : %d\n", checkedAvenue);
		}

		// If the Avenue is true
		if (checkedAvenue == True) {
			char playerChar = (*g).board[*(avenue) / SIZE][*(avenue) % SIZE];

			if (playerChar == 'X'){
				res = 1;
			}
			else{
				res = 2;
			}

			// You have won
			break;
		}
	}

	//3. We return res
	return res;
}

//------------------------------------
//	11. FUNCTION is_board_full
//------------------------------------
boolean is_board_full(game* g) {
	//1. We create the variable to be returned
	boolean full = True;

	//2. We check if the 9 positions of the board are busy.
	//If all positions are busy, we return True.
	//If at least one position is empty, we return False.
	int i;
	int size = 9;
	for (i = 0; i <= size && full; i++) {
		if ((*g).board[i / SIZE][i % SIZE] == ' ') {
			full = False;
		}
	}

	//3. We return res
	return full;
}

//------------------------------------
//	12. FUNCTION process_movement
//------------------------------------
void process_movement(game* g, int pos) {
	// 1. We update board with the new movement at index 'pos'.
	// This requires checking the current status to know if the movement is an 'X' or a 'O'.
	switch ((*g).status) {
	case 1: (*g).board[pos / SIZE][pos % SIZE] = 'X'; break; // Player 1
	case 2: (*g).board[pos / SIZE][pos % SIZE] = 'O'; break; // Player 2
	}

	//2. ---Computer Intelligent Movement Only ---
	//We traverse each avenue: If pos belongs to it, we call to update_avenue_states to update its state.
	if ((*g).intelligent_machine) {
		int i, j;
		int size = 8;
		for (i = 0; i < size; i++) {
			for (j = 0; j < SIZE; j++) {
				if (pos == (*g).avenue_positions[i][j]) {
					update_avenue_states(g, i);
					break;
				}
			}
		}
	}

	//3. We create a variable winner and call to the function is_there_a_winner
	//to see if this movement has lead to a winner.
	int winner = is_there_a_winner(g);

	//4. We create a variable full and call to the function is_board_full to see if the board is full.
	boolean full = is_board_full(g);

	//5. We update the status accordingly.
	// (Case 1) winner == 1 --> Game Status = 3.
	// (Case 2) winner == 2 --> Game Status = 4.
	// (Case 3) winner == 0 and full == True --> Game Status = 5.
	// (Case 4) winner == 0 and full == False --> Depending on current Game Status.
	//											  If Game Status == 1 --> Game Status = 2.
	//											  If Game Status == 2 --> Game Status = 1.
	switch (winner) {
	case 1: (*g).status = 3; break;
	case 2: (*g).status = 4; break;
	case 0:
		if (full){		
			(*g).status = 5;
		}
		else {
			if ((*g).status == 1){
				(*g).status = 2;
			}
			else if ((*g).status == 2){
				(*g).status = 1;
			}
		}
		break;
	}
}

//------------------------------------
//	13. FUNCTION play_game
//------------------------------------
void play_game(char* p1, char* p2, int im) {
	//1. We create a variable pointer game* g and call to the function
	//create_new_game so as to initialise it.
	game* g = create_new_game(p1, p2, im);
	int nextMovementIndex;

	//2. Game loop: While the game is on (i.e., Game Status = 1 or Game Status = 2)
	while ((*g).status == 1 || (*g).status == 2) {
		//2.1. We call to display_game_status to print the board content and the next player to move.
		display_game_status(g);
		//2.2. We call to get_next_movement_index to force the human player or the computer
		//to select a valid index to move for.
		nextMovementIndex = get_next_movement_index(g);
		//2.3. We call to process_movement to update the board content and the Game Status.
		process_movement(g, nextMovementIndex);
	}

	//3. Once the game is over we call to display_game_status to print the last Game Status of the game.
	display_game_status(g);
}

//------------------------------------
//	14. FUNCTION update_avenue_states
//------------------------------------
void update_avenue_states(game* g, int avenue) {
	// 1. We update the state
	switch ((*g).avenue_states[avenue]) {

		// CASE State 1 --> We keep still at State 1.

		// CASE State 2 --> If Player1 is moving --> State 3.
		//					If Player2 is moving --> State 4.
	case 2:
		if ((*g).status == 1){
			(*g).avenue_states[avenue] = 3;
		}
		else if ((*g).status == 2){
			(*g).avenue_states[avenue] = 4;
		}
		break;
		// CASE State 3 --> If Player1 is moving --> State 5.
		//					If Player2 is moving --> State 1.
	case 3:
		if ((*g).status == 1){
			(*g).avenue_states[avenue] = 5;
		}
		else if ((*g).status == 2){
			(*g).avenue_states[avenue] = 1;
		}
		break;
		// CASE State 4 --> If Player1 is moving --> State 1.
		//					If Player2 is moving --> State 6.
	case 4:
		if ((*g).status == 1){
			(*g).avenue_states[avenue] = 1;
		}
		else if ((*g).status == 2){
			(*g).avenue_states[avenue] = 6;
		}
		break;
		// CASE State 5 --> If Player1 is moving --> State 7.
		//					If Player2 is moving --> State 1.
	case 5:
		if ((*g).status == 1){
			(*g).avenue_states[avenue] = 7;
		}
		else if ((*g).status == 2){
			(*g).avenue_states[avenue] = 1;
		}
		break;
		// CASE State 6 --> If Player1 is moving --> State 1.
		//					If Player2 is moving --> State 8.
	case 6:
		if ((*g).status == 1){
			(*g).avenue_states[avenue] = 1;
		}
		else if ((*g).status == 2){
			(*g).avenue_states[avenue] = 8;
		}
		break;
	}
	// CASE State 7 --> This case does not make sense, as the game is over.
	// CASE State 8 --> This case does not make sense, as the game is over.
}

//----------------------------------------
//	15. FUNCTION get_position_points
//----------------------------------------
int get_position_points(game* g, int pos) {
	//1. We create the variable to be returned
	int res = 0;

	//2. We traverse the 8 avenues, to see if pos in on it.
	//Remember that each pos will belong to multiple avenues:
	//pos = 1; pos = 3; pos = 5; pos = 7 belong to 2 avenues.
	//pos = 0; pos = 2; pos = 6; pos = 8 belong to 3 avenues.
	//pos = 4 belongs to 4 avenues.
	int i, j;
	int size = 8;
	for (i = 0; i < size; i++) {
		for (j = 0; j < SIZE; j++) {
			if (pos == (*g).avenue_positions[i][j]) {
				//For each avenue pos belongs to, it gets points from it.
				//How many points? It depends of the state of the avenue.
				// CASE State 1 --> 0 points.
				switch ((*g).avenue_states[i]) {
					// CASE State 2 --> 1 point.
				case 2: res += 1; break;
					// CASE State 3 --> If Player1 is moving --> 4 points.
					//					If Player2 is moving --> 2 points.
				case 3:
					if ((*g).status == 1){
						res += 4;
					}
					else{
						res += 2;
					}
					break;
					// CASE State 4 --> If Player1 is moving --> 2 points.
					//					If Player2 is moving --> 4 points.
				case 4:
					if ((*g).status == 1){
						res += 2;
					}
					else{
						res += 4;
					}
					break;
					// CASE State 5 --> If Player1 is moving --> 16 points.
					//					If Player2 is moving --> 8 points.
				case 5:
					if ((*g).status == 1){
						res += 16;
					}
					else{
						res += 8;
					}
					break;
					// CASE State 6 --> If Player1 is moving --> 8 points.
					//					If Player2 is moving --> 16 points.
				case 6:
					if ((*g).status == 1){
						res += 8;
					}
					else{
						res += 16;
					}
					break;
					// CASE State 7 --> This case does not make sense, as the game is over.
					// CASE State 8 --> This case does not make sense, as the game is over.
				}
			}
		}
	}

	//3. We return the accumulated amount of points of pos
	return res;
}

//----------------------------------------
//	16. FUNCTION intelligent_selection
//----------------------------------------
int intelligent_selection(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We create an auxiliary variable max_points to compute the maximum amount of points we have found so far.
	int max_points = -1;

	//3. We traverse all the positions of boards to pick the one leading to maximum points.
	int selected_position, points;
	int size = 8;

	for (selected_position = 0; selected_position <= size; selected_position++) {
		//If a position is empty, then we call to get_position_points to get its points.
		if (is_position_empty(g, selected_position)) {
			points = get_position_points(g, selected_position);

			//We compare the result with max_points.
			//If the new position gets more points than max_points, then we update:
			//(1) The selected position and (2) The proper variable max_points with the new points computed.
			if (points > max_points) {
				max_points = points;
				res = selected_position;
			}
		}//If a position is not empty then we do not consider it.
	}

	//4. We return res
	return res;
}