
#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>

struct item {
	char *name;
};

struct inventory {
	size_t max_items;
	size_t total_items;
	struct item *items;
};

typedef struct player {
	struct inventory inv;
	char *name;
} player_t;


player_t *
create_player();

bool
add_item(player_t *);

void
list_items(const player_t *);

bool
destroy_player(player_t *);

#endif
