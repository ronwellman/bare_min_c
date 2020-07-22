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
	
	destroyPlayer(player1);
	return 0;
}

