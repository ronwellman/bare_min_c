#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "05-player.h"

player_t *
create_player() {
	player_t *player = calloc(1, sizeof(*player));

	printf("Enter a name for the player: ");
	size_t len = 0;
	size_t nameLen = getline(&(player->name), &len, stdin);
	if ('\n' == player->name[nameLen - 1]) {
		player->name[nameLen - 1] = '\0';
	}

	player->inv.max_items = 5;
	player->inv.items = calloc(player->inv.max_items, sizeof(*(player->inv.items)));

	return player;
}

bool
add_item(player_t *player) {
	if (NULL == player->inv.items) {
		perror("Player items is NULL.\n");
		return false;
	}

	printf("Enter an item name: ");
	char *name = NULL;
	size_t len = 0;
	size_t nameLen = getline(&name, &len, stdin);
	if ('\n' == name[nameLen - 1]) {
		name[nameLen - 1] = '\0';
	}

	if (strlen(name) > 0) {
		player->inv.items[player->inv.total_items].name = name;
		player->inv.total_items += 1;
	}

	return true;	
}

void
list_items(const player_t *player) {
	if (NULL == player || NULL == player->name) {
		perror("Can't list NULL player.\n");
		return;
	}

	printf("Player: %s\n", player->name);
	if (0 == player->inv.total_items || NULL == player->inv.items) {
		printf("\t0 items\n");
		return;
	}

	for (size_t num = 0; num < player->inv.total_items; num++) {
		printf("\tItem %ld: %s\n", num + 1, player->inv.items[num].name);	
	}
}

bool
destroy_player(player_t *player) {
	if (NULL == player) {
		return true;		
	}
	
	if (NULL != player->inv.items) {
		for (size_t num = 0; num < player->inv.total_items; num++) {
			free(player->inv.items[num].name);
			player->inv.items[num].name = NULL;
		}
		free(player->inv.items);
		player->inv.items = NULL;
	}
	free(player->name);
	player->name = NULL;
	free(player);
	player = NULL;

	return true;
}
