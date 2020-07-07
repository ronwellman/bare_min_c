#include <stdio.h>

int
main() {
	short int si;
	int i;
	long int li;
	long long int lli;

	printf("Number of Bytes:\nshort int: %ld\nint: %ld\n",
			sizeof(si), sizeof(i));
	printf("long int: %ld\nlong long int: %ld\n",
			sizeof(li), sizeof(lli));

	return 0;
}
