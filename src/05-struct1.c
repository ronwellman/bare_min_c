#include <stdio.h>
#include "05-player.h"

int
main() {

	player_t *player1 = create_player();
	list_items(player1);
	bool result = add_item(player1);
	if (true == result) {
		printf("Successfully added.\n");
	}
	result = add_item(player1);
	if (true == result) {
		printf("Successfully added.\n");
	}
	
	list_items(player1);
	destroy_player(player1);
	return 0;
}

