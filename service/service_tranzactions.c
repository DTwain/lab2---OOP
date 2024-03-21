#include "tranzaction.h"
#include "repo_tranzactii.h"
#include <string.h>
#include <stdio.h>
/*
Adaug tranzactia la lista de tranzactii daca este valida
Return values:
return 0  : adaugare cu succes
return -1 : adaugare picata
*/
int add_tranzaction(struct_with_field_tranzactions *struct_obj, int day, int sum, char *type, char *description) {
	int id = struct_obj -> nr_of_tranzactions_added_from_start;
	tranzaction *tranzaction_to_be_added = create_tranzaction(id, day, sum, type, description);
	int tranzaction_validation_result = validate_tranzaction(tranzaction_to_be_added);
	if (tranzaction_validation_result != 0) {
		destroy_tranzaction(tranzaction_to_be_added);
		return -1;
	}
	int rezultat_adaugare = add_tranzaction_repo(struct_obj, tranzaction_to_be_added);
	destroy_tranzaction(tranzaction_to_be_added);
	return rezultat_adaugare;
}

/*
Stergere tranzactie, daca id-ul furnizat corespunde cu un id de tranzactie existent
Return values:
return 0  : stergere reusita
return -1 : stergere esuata , nu exista tranzactia cu id ul dat
*/
struct_with_field_tranzactions* delete_tranzaction(struct_with_field_tranzactions *struct_obj, int tranzaction_ID_to_be_deleted) {
	struct_with_field_tranzactions *result_delete_tranzaction = delete_tranzaction_repo(struct_obj, tranzaction_ID_to_be_deleted);
	if (result_delete_tranzaction != NULL)
		return result_delete_tranzaction;
	return NULL;
}

/*
Modifica tranzactie cu id-ul specificat daca exita 
Return values:
return 0  : modificare reusita
return -1 : modificare esuata , nu exista tranzactia cu id ul dat sau validarea a esuat
*/
int modify_tranzaction(struct_with_field_tranzactions* struct_obj, int id, int day, int sum, char* type, char* description) {
	tranzaction* modified_tranzaction = create_tranzaction(id, day, sum, type, description);
	int tranzaction_validation_result = validate_tranzaction(modified_tranzaction);
	if (tranzaction_validation_result != 0) {
		destroy_tranzaction(modified_tranzaction);
		return -1;
	}
	if (modify_tranzaction_repo(struct_obj, modified_tranzaction) != 0) {
		destroy_tranzaction(modified_tranzaction);
		return -1;
	}
	destroy_tranzaction(modified_tranzaction);
	return 0;
}

struct_with_field_tranzactions *lista_de_tranzactii(struct_with_field_tranzactions *struct_obj) {
	struct_with_field_tranzactions *copie = copie_struct_obj(struct_obj);
	return copie;
}

struct_with_field_tranzactions *filters_on_tranzactions(struct_with_field_tranzactions *struct_obj, char *type_filter, int sum_filter, char mod_h_or_l) {
	struct_with_field_tranzactions *copie = copie_struct_obj(struct_obj);
	if (strcmp(type_filter, "intrare\n") == 0 || strcmp(type_filter, "iesire\n") == 0)
		for(int i = 0; i < copie -> nr_of_tranzactions; ++i)
			if (strcmp(copie -> arr_of_tranzactions[i].type, type_filter) != 0) {
				for (int j = i; j < copie -> nr_of_tranzactions - 1; ++j)
					copie -> arr_of_tranzactions[j] = copie -> arr_of_tranzactions[j + 1];
				copie -> nr_of_tranzactions -= 1;
				i -= 1;
			}
	if (mod_h_or_l == 'H' && sum_filter != -1) {
		for (int i = 0; i < copie -> nr_of_tranzactions; ++i)
			if (copie -> arr_of_tranzactions[i].sum <= sum_filter) {
				for (int j = i; j < copie -> nr_of_tranzactions - 1; ++j)
					copie -> arr_of_tranzactions[j] = copie -> arr_of_tranzactions[j + 1];
				copie -> nr_of_tranzactions -= 1;
				i -= 1;
			}
	}
	else if (mod_h_or_l == 'L' && sum_filter != -1) {
		for (int i = 0; i < copie -> nr_of_tranzactions; ++i)
			if (copie -> arr_of_tranzactions[i].sum >= sum_filter) {
				for (int j = i; j < copie -> nr_of_tranzactions - 1; ++j)
					copie -> arr_of_tranzactions[j] = copie -> arr_of_tranzactions[j + 1];
				copie -> nr_of_tranzactions -= 1;
				i -= 1;
			}
	}
	return copie;		
}

struct_with_field_tranzactions *sorting_based_of_criteria(struct_with_field_tranzactions *struct_obj, char sorting_mode, char *suma_or_zi) {
	struct_with_field_tranzactions *copie = copie_struct_obj(struct_obj);
	if (sorting_mode == 'C') {
		for (int i = 0; i < copie -> nr_of_tranzactions - 1; ++i)
			for (int j = i + 1; j < copie -> nr_of_tranzactions; ++j)
				if (strcmp(suma_or_zi, "suma\n") == 0) {
					if (copie -> arr_of_tranzactions[i].sum > copie -> arr_of_tranzactions[j].sum) {
						tranzaction aux = copie -> arr_of_tranzactions[i];
						copie -> arr_of_tranzactions[i] = copie -> arr_of_tranzactions[j];
						copie -> arr_of_tranzactions[j] = aux;
					}
				}
				else if (strcmp(suma_or_zi, "zi\n") == 0) {
					if (copie -> arr_of_tranzactions[i].day > copie -> arr_of_tranzactions[j].day) {
						tranzaction aux = copie -> arr_of_tranzactions[i];
						copie -> arr_of_tranzactions[i] = copie -> arr_of_tranzactions[j];
						copie -> arr_of_tranzactions[j] = aux;
					}
				}
	}
	else if (sorting_mode == 'D') {
		for (int i = 0; i < copie -> nr_of_tranzactions - 1; ++i)
			for (int j = i + 1; j < copie -> nr_of_tranzactions; ++j)
				if (strcmp(suma_or_zi, "suma\n") == 0) {
					if (copie -> arr_of_tranzactions[i].sum < copie -> arr_of_tranzactions[j].sum) {
						tranzaction aux = copie -> arr_of_tranzactions[i];
						copie -> arr_of_tranzactions[i] = copie -> arr_of_tranzactions[j];
						copie -> arr_of_tranzactions[j] = aux;
					}
				}
				else if (strcmp(suma_or_zi, "zi\n") == 0) {
					if (copie -> arr_of_tranzactions[i].day < copie -> arr_of_tranzactions[j].day) {
						tranzaction aux = copie -> arr_of_tranzactions[i];
						copie -> arr_of_tranzactions[i] = copie -> arr_of_tranzactions[j];
						copie -> arr_of_tranzactions[j] = aux;
					}
				}
	}		
	return copie;
}





