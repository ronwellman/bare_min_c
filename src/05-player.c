#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "05-player.h"

#define INV_SIZE 5

player_t *
createPlayer() {
	// allocate for new player
	player_t *player = calloc(1, sizeof(*player));
	if (NULL == player) {
		perror("Unable to allocate for new player.\n");
		return NULL;
	}

	// get player's name
	printf("Enter a name for the player: ");
	size_t len = 0;
	size_t nameLen = getline(&(player->name), &len, stdin);
	if ('\n' == player->name[nameLen - 1]) {
		player->name[nameLen - 1] = '\0';
	}

	// allocate for items
	player->inv.maxItems = INV_SIZE;
	player->inv.items = calloc(player->inv.maxItems,
			sizeof(*(player->inv.items)));

	return player;
}

bool
addItem(player_t *player) {
	if (NULL == player->inv.items) {
		perror("Player items is NULL.\n");
		return false;
	}

	// is inventory full
	if (player->inv.maxItems == player->inv.totalItems) {
		return false;
	}

	// get new item
	printf("Enter an item name: ");
	char *name = NULL;
	size_t len = 0;
	size_t nameLen = getline(&name, &len, stdin);
	if ('\n' == name[nameLen - 1]) {
		name[nameLen - 1] = '\0';
	}

	// store new item
	if (strlen(name) > 0) {
		player->inv.items[player->inv.totalItems].name = name;
		player->inv.totalItems += 1;
	} else {
		free(name);
		return false;
	}

	return true;	
}

void
listItems(const player_t *player) {
	if (NULL == player || NULL == player->name) {
		perror("Can't list NULL player.\n");
		return;
	}

	printf("Player: %s\n", player->name);
	
	// empty inventory
	if (0 == player->inv.totalItems || NULL == player->inv.items) {
		printf("\tempty inventory\n");
		return;
	}

	// loop through items
	for (size_t num = 0; num < player->inv.totalItems; num++) {
		printf("\tItem %ld: %s\n", num + 1, player->inv.items[num].name);	
	}
}

bool
destroyPlayer(player_t *player) {
	if (NULL == player) {
		return true;	
	}
	
	if (NULL != player->inv.items) {
		for (size_t num = 0; num < player->inv.totalItems; num++) {
			// free individual items
			free(player->inv.items[num].name);
			player->inv.items[num].name = NULL;
		}
		// free array of pointers to items
		free(player->inv.items);
		player->inv.items = NULL;
		player->inv.totalItems = 0;
	}

	// free player
	free(player->name);
	player->name = NULL;
	free(player);
	player = NULL;

	return true;
}
