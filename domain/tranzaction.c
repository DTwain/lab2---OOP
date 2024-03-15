#include <string.h>
#include "tranzaction.h"

/*
Creare obiect de tip tranzactie
Return type:
	Obiect de tip tranzactie
*/
tranzaction create_tranzaction(int id, int day, int sum, char type[], char description[]) {
	tranzaction tranzaction_to_be_added;

	tranzaction_to_be_added.id_tranzaction = id;
	tranzaction_to_be_added.day = day;
	tranzaction_to_be_added.sum = sum;
	strcpy(tranzaction_to_be_added.type, type);
	strcpy(tranzaction_to_be_added.description, description);
	
	return tranzaction_to_be_added;
}

/*
Distruge tranzactia
*/
void destroy_tranzaction(tranzaction* current_tranzaction) {
	current_tranzaction -> id_tranzaction = 0;
	current_tranzaction -> day = 0;
	current_tranzaction -> sum = 0;
	current_tranzaction -> type[0] = '\0';
	current_tranzaction -> description[0] = '\0';
}
/*
Validare obiect de tip tranzactie
Conditii:
	0 <= id < inf
	0 <= day <= 31
	0 <  sum < inf
	type lengh > 0
	description lengh > 0
Return type:
return 0  : Validare trecuta
return -1 : Validare picata
*/
int validate_tranzaction(tranzaction tranzaction_to_ve_verified) {
	if (tranzaction_to_ve_verified.id_tranzaction < 0)
		return -1;
	if (tranzaction_to_ve_verified.day <= 0 || tranzaction_to_ve_verified.day > 31)
		return -1;
	if (tranzaction_to_ve_verified.sum < 0)
		return -1;
	if (strlen(tranzaction_to_ve_verified.type) == 0 || strlen(tranzaction_to_ve_verified.description) == 0)
		return -1;
	if (strcmp(tranzaction_to_ve_verified.type, "intrare\n") == 0)
		return 0;
	if (strcmp(tranzaction_to_ve_verified.type, "iesire\n") == 0)
		return 0;
	return -1;
}