#pragma once

typedef struct {
	int id_tranzaction;
	int day;
	int sum;
	char *type;
	char *description;
}tranzaction;

tranzaction *create_tranzaction(int id, int day, int sum, char *type, char *description);
int validate_tranzaction(tranzaction *tranzaction_to_ve_verified);
void destroy_tranzaction(tranzaction* current_tranzaction);