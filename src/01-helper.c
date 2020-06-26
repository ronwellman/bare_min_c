#include "01-helper.h"

int
distributeSnacks(MYSTERYMEMBER member) {
	int num = 0;

	switch (member) {
		case SHAGGY:
			num = 20;
			break;
		case SCOOBY:
			num = 40;
			break;
		default:
			num = 0;
	}

	return num;
}
