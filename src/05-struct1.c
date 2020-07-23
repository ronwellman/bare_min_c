#include <stdio.h>
#include "05-player.h"

int
main() {

	player_t *player1 = createPlayer();
	
	bool result = addItem(player1);
	if (true == result) {
		printf("Successfully added.\n");
	}

	result = addItem(player1);
	if (true == result) {
		printf("Successfully added.\n");
	}
	
	listItems(player1);
	
	result = destroyPlayer(&player1);
	if ((true == result) && (NULL == player1)) {
		printf("Successfully destroyed.\n");
	}
	return 0;
}

