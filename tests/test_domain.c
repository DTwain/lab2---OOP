#include "assert.h"
#include "tranzaction.h"
#include <string.h>
void test_create_tranzaction() {
	tranzaction *temp = create_tranzaction(1, 12, 300, "intrare", "datoria pe mai");
	assert(temp -> day == 12);
	assert(temp -> id_tranzaction == 1);
	assert(temp -> sum == 300);
	assert(strcmp(temp -> type, "intrare") == 0);
	assert(strcmp(temp -> description, "datoria pe mai") == 0);
	destroy_tranzaction(temp);
}
void test_destroy_tranzaction() {
	tranzaction *temp = create_tranzaction(1, 12, 300, "intrare", "datoria pe mai");
	destroy_tranzaction(temp);
}

void test_validate_tranzaction() {
	tranzaction *temp = create_tranzaction(8, 12, 300, "intrare\n", "datoria pe mai\n");
	tranzaction *temp2 = create_tranzaction(-1, 12, 300, "iesire\n", "datoria pe mai\n");
	tranzaction *temp3 = create_tranzaction(1, 32, -3, "intrare\n", "datoria pe mai\n");
	tranzaction *temp4 = create_tranzaction(1, 12, -300, "intrare\n", "datoria pe mai\n");
	tranzaction *temp5 = create_tranzaction(16, 100, 3300, "intraree\n", "datoria pe mai\n");
	tranzaction *temp6 = create_tranzaction(29, 100, 300, "\n", "\n");

	assert(validate_tranzaction(temp) == 0);
	assert(validate_tranzaction(temp2) == -1);
	assert(validate_tranzaction(temp3) == -1);
	assert(validate_tranzaction(temp4) == -1);
	assert(validate_tranzaction(temp5) == -1);
	assert(validate_tranzaction(temp6) == -1);
	
	destroy_tranzaction(temp2);
	destroy_tranzaction(temp);
	destroy_tranzaction(temp3);
	destroy_tranzaction(temp4);
	destroy_tranzaction(temp5);
	destroy_tranzaction(temp6);
}