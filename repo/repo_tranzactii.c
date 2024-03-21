#include <stdlib.h>
#include <string.h>
#include "repo_tranzactii.h"
#include "tranzaction.h"
/*
Creare obiect de tip struct_with_field_tranzactions
Return value: obiect de tip struct_with_field_tranzactions
*/
struct_with_field_tranzactions *create_list_of_tranzactions() {
	struct_with_field_tranzactions* struct_obj = (struct_with_field_tranzactions*) malloc(sizeof(struct_with_field_tranzactions));
	if (struct_obj == NULL)
		exit(EXIT_FAILURE);

	struct_obj -> arr_of_tranzactions = (tranzaction*)malloc(20 * sizeof(tranzaction));
	struct_obj -> capacity = 20;

	struct_obj -> nr_of_tranzactions = 0;
	struct_obj -> nr_of_tranzactions_added_from_start = 0;
	return struct_obj;
}

/*
Redimensionare array dinamic 
Dublez capacitatea initiala
Aloc dinamic un array nou de capacitate updatata
Mut elementele din primul array in cel nou creat
Dealoc vechiul array
Si modific adresa vechiului array cu cea a noului
*/
void resize(struct_with_field_tranzactions* struct_obj) {
	struct_obj -> capacity *= 2;
	tranzaction* local_array_tranzaction = (tranzaction*)malloc(struct_obj->capacity * sizeof(tranzaction));
	if (local_array_tranzaction == NULL)
		exit(EXIT_FAILURE);

	for (int i = 0; i < struct_obj -> nr_of_tranzactions; ++i)
		local_array_tranzaction[i] = struct_obj->arr_of_tranzactions[i];
	free(struct_obj -> arr_of_tranzactions);
	struct_obj -> arr_of_tranzactions = local_array_tranzaction;
}
/*
Readucerea la 0 a numarului de tranzactii, "stergerea lor"
*/
void destroy_struct_with_field_tranzactions(struct_with_field_tranzactions *struct_obj) {
	for (int i = 0; i < struct_obj -> nr_of_tranzactions; ++i) {
			free(struct_obj -> arr_of_tranzactions[i].type);
			free(struct_obj -> arr_of_tranzactions[i].description);
	}
	free(struct_obj -> arr_of_tranzactions);
	free(struct_obj);
	struct_obj = NULL;
}

/*
Crearea unei copii a tranzactiilor
return value:
	 copie a obiectului de tip struct_with_field_tranzactions, care contine tranzactiile
*/
struct_with_field_tranzactions *copie_struct_obj(struct_with_field_tranzactions *struct_obj) {
	struct_with_field_tranzactions* copie = (struct_with_field_tranzactions*)malloc(sizeof(struct_with_field_tranzactions));
	if (copie == NULL) 
		exit(EXIT_FAILURE);
	
	copie -> capacity = struct_obj -> capacity;
	copie -> arr_of_tranzactions = (tranzaction*)malloc(copie -> capacity * sizeof(tranzaction));
	if (copie -> arr_of_tranzactions == NULL)
		exit(EXIT_FAILURE);

	copie -> nr_of_tranzactions = struct_obj -> nr_of_tranzactions;
	copie -> nr_of_tranzactions_added_from_start = struct_obj -> nr_of_tranzactions_added_from_start;

	for (int i = 0; i < struct_obj -> nr_of_tranzactions; ++i) {
		copie -> arr_of_tranzactions[i].day = struct_obj -> arr_of_tranzactions[i].day;
		copie -> arr_of_tranzactions[i].id_tranzaction = struct_obj -> arr_of_tranzactions[i].id_tranzaction;
		copie -> arr_of_tranzactions[i].sum = struct_obj -> arr_of_tranzactions[i].sum;

		copie -> arr_of_tranzactions[i].type = (char*)malloc(strlen(struct_obj -> arr_of_tranzactions[i].type) + 1);
		if (copie -> arr_of_tranzactions[i].type == NULL)
			exit(EXIT_FAILURE);
		strcpy(copie -> arr_of_tranzactions[i].type, struct_obj -> arr_of_tranzactions[i].type);

		copie -> arr_of_tranzactions[i].description = (char*)malloc(strlen(struct_obj -> arr_of_tranzactions[i].description) + 1);
		if (copie -> arr_of_tranzactions[i].description == NULL)
			exit(EXIT_FAILURE);
		strcpy(copie -> arr_of_tranzactions[i].description, struct_obj -> arr_of_tranzactions[i].description);
	}
	return copie;
}

/*
Adauga obiectul de tip tranzactie la lista de tranzactii
return 0 : Adaugarea s - a realizat cu succes
*/
int add_tranzaction_repo(struct_with_field_tranzactions *struct_obj, tranzaction *curr_tranzaction) {
	if (struct_obj -> capacity == struct_obj -> nr_of_tranzactions)
		resize(struct_obj);

	struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].day = curr_tranzaction -> day;
	struct_obj->arr_of_tranzactions[struct_obj -> nr_of_tranzactions].id_tranzaction = struct_obj -> nr_of_tranzactions_added_from_start;
	struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].sum = curr_tranzaction -> sum;

	struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].type = (char*)malloc(strlen(curr_tranzaction -> type) + 1);
	if (struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].type == NULL)
		exit(EXIT_FAILURE);
	strcpy(struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].type, curr_tranzaction -> type);

	struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].description = (char*)malloc(strlen(curr_tranzaction -> description) + 1);
	if (struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].description == NULL)
		exit(EXIT_FAILURE);
	strcpy(struct_obj -> arr_of_tranzactions[struct_obj -> nr_of_tranzactions].description, curr_tranzaction -> description);

	struct_obj -> nr_of_tranzactions += 1;
	struct_obj->nr_of_tranzactions_added_from_start += 1;
	return 0;
}

/*
Sterge tranzactia cu id-ul egal cu tranzaction_id_to_be_removed, daca exista
Return values:
return 0  : Stergere realizata
return -1 : Stergere NEREALIZATA, tranzaction_id_to_be_removed nu s-a gasit prin id-ul tranzactiilor existente 
*/
struct_with_field_tranzactions* delete_tranzaction_repo(struct_with_field_tranzactions* struct_obj, int tranzaction_id_to_be_removed) {
	int poz_tranzaction_with_id = -1;
	for (int i = 0; i < struct_obj -> nr_of_tranzactions; ++i)
		if (struct_obj -> arr_of_tranzactions[i].id_tranzaction == tranzaction_id_to_be_removed) {
			poz_tranzaction_with_id = i;
			break;
		}
	if (poz_tranzaction_with_id == -1)
		return NULL;

	struct_with_field_tranzactions* struct_obj_without_tranzaction_found = (struct_with_field_tranzactions*)malloc(sizeof(struct_with_field_tranzactions));
	if (struct_obj_without_tranzaction_found == NULL)
		exit(EXIT_FAILURE);

	struct_obj_without_tranzaction_found -> capacity = struct_obj -> capacity;
	struct_obj_without_tranzaction_found -> nr_of_tranzactions = struct_obj -> nr_of_tranzactions - 1;
	struct_obj_without_tranzaction_found -> nr_of_tranzactions_added_from_start = struct_obj -> nr_of_tranzactions_added_from_start;
	struct_obj_without_tranzaction_found -> arr_of_tranzactions = (tranzaction*)malloc(struct_obj_without_tranzaction_found -> capacity * sizeof(tranzaction));
	if (struct_obj_without_tranzaction_found->arr_of_tranzactions == NULL)
		exit(EXIT_FAILURE);

	int cnt_obj_added = 0;
	for (int i = 0; i < struct_obj->nr_of_tranzactions; ++i) {
		if (struct_obj->arr_of_tranzactions[i].id_tranzaction != poz_tranzaction_with_id) {
			struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].id_tranzaction = struct_obj->arr_of_tranzactions[i].id_tranzaction;
			struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].day = struct_obj->arr_of_tranzactions[i].day;
			struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].sum = struct_obj->arr_of_tranzactions[i].sum;
			struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].type = (char*)malloc(strlen(struct_obj->arr_of_tranzactions[i].type) + 1);
			if (struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].type == NULL)
				exit(EXIT_FAILURE);
			strcpy(struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].type, struct_obj->arr_of_tranzactions[i].type);

			struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].description = (char*)malloc(strlen(struct_obj->arr_of_tranzactions[i].description) + 1);
			if (struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].description == NULL)
				exit(EXIT_FAILURE);
			strcpy(struct_obj_without_tranzaction_found->arr_of_tranzactions[cnt_obj_added].description, struct_obj->arr_of_tranzactions[i].description);
			
			cnt_obj_added += 1;
		}
	}
	destroy_struct_with_field_tranzactions(struct_obj);
	struct_obj_without_tranzaction_found;
	return struct_obj_without_tranzaction_found;
}

/*
Modifica tranzactia cu id-ul egal cu id-ul tranzactiei modificate cu tranzactia modificata
Return values:
return 0  : Modificare realizata cu succes
return -1 : Modificare NEREALIZATA, implica inexistenta unei tranzactii cu id-ul egal cu id-ul noii tranzactii
*/
int modify_tranzaction_repo(struct_with_field_tranzactions* struct_obj, tranzaction *modified_tranzaction) {
	for (int i = 0; i < struct_obj -> nr_of_tranzactions; ++i)
		if (struct_obj -> arr_of_tranzactions[i].id_tranzaction == modified_tranzaction -> id_tranzaction) {
			int lungime_type_for_old_tranzaction = strlen(struct_obj -> arr_of_tranzactions[i].type);
			int lungime_type_for_new_tranzaction = strlen(modified_tranzaction -> type);
			if (lungime_type_for_new_tranzaction > lungime_type_for_old_tranzaction) {
				char* new_arr_for_type = (char*)malloc(lungime_type_for_new_tranzaction + 1);
				if (new_arr_for_type == NULL)
					exit(EXIT_FAILURE);

				strcpy(new_arr_for_type, modified_tranzaction -> type);
				free(struct_obj -> arr_of_tranzactions[i].type);
				struct_obj -> arr_of_tranzactions[i].type = new_arr_for_type;
			}
			else {
				strcpy(struct_obj -> arr_of_tranzactions[i].type, modified_tranzaction -> type);
			}
			int lungime_description_for_old_tranzaction = strlen(struct_obj -> arr_of_tranzactions[i].description);
			int lungime_description_for_new_tranzaction = strlen(modified_tranzaction -> description);
			if (lungime_description_for_new_tranzaction > lungime_description_for_old_tranzaction) {
				char* new_arr_for_description = (char*)malloc(lungime_description_for_new_tranzaction + 1);
				if (new_arr_for_description == NULL)
					exit(EXIT_FAILURE);

				strcpy(new_arr_for_description, modified_tranzaction -> description);
				free(struct_obj -> arr_of_tranzactions[i].description);
				struct_obj->arr_of_tranzactions[i].description = new_arr_for_description;
			}
			else {
				strcpy(struct_obj -> arr_of_tranzactions[i].description, modified_tranzaction -> description);
			}
			struct_obj -> arr_of_tranzactions[i].day = modified_tranzaction -> day;
			struct_obj -> arr_of_tranzactions[i].sum = modified_tranzaction -> sum;
			return 0;
		}
	return -1;
}

/*
return : Numarul de tranzactii adaugate va reprezenta id-ul posibilei urmatoare tranzactii
*/
int get_next_tranzaction_id(struct_with_field_tranzactions *struct_obj) {
	return struct_obj -> nr_of_tranzactions_added_from_start;
}




