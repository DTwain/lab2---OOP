#include "repo_tranzactii.h"

/*
Creare obiect de tip struct_with_field_tranzactions
Return value: obiect de tip struct_with_field_tranzactions
*/
struct_with_field_tranzactions create_list_of_tranzactions() {
	struct_with_field_tranzactions struct_obj;
	struct_obj.nr_of_tranzactions = 0;
	struct_obj.nr_of_tranzactions_added_from_start = 0;
	return struct_obj;
}

/*
Readucerea la 0 a numarului de tranzactii, "stergerea lor"
*/
void destroy_struct_with_field_tranzactions(struct_with_field_tranzactions *struct_obj) {
	struct_obj -> nr_of_tranzactions = 0;
	struct_obj -> nr_of_tranzactions_added_from_start = 0;
}

/*
Crearea unei copii a tranzactiilor
return value:
	 copie a obiectului de tip struct_with_field_tranzactions, care contine tranzactiile
*/
struct_with_field_tranzactions copie_struct_obj(struct_with_field_tranzactions *struct_obj) {
	struct_with_field_tranzactions copie = create_list_of_tranzactions();
	for (int i = 1; i <= struct_obj -> nr_of_tranzactions; ++i) {
		copie.nr_of_tranzactions += 1;
		copie.nr_of_tranzactions_added_from_start += 1;
		copie.arr_of_tranzactions[i] = struct_obj -> arr_of_tranzactions[i];
	}
	return copie;
}

/*
Adauga obiectul de tip tranzactie la lista de tranzactii
return 0 : Adaugarea s - a realizat cu succes
*/
int add_tranzaction_repo(struct_with_field_tranzactions *struct_obj, tranzaction curr_tranzaction) {
	struct_obj -> nr_of_tranzactions += 1;
	struct_obj -> nr_of_tranzactions_added_from_start += 1;
	struct_obj -> arr_of_tranzactions[struct_obj->nr_of_tranzactions] = curr_tranzaction;
	return 0;
}

/*
Sterge tranzactia cu id-ul egal cu tranzaction_id_to_be_removed, daca exista
Return values:
return 0  : Stergere realizata
return -1 : Stergere NEREALIZATA, tranzaction_id_to_be_removed nu s-a gasit prin id-ul tranzactiilor existente 
*/
int delete_tranzaction_repo(struct_with_field_tranzactions* struct_obj, int tranzaction_id_to_be_removed) {
	int poz_tranzaction_with_id = 0;
	for (int i = 1; i <= struct_obj -> nr_of_tranzactions; ++i)
		if (struct_obj -> arr_of_tranzactions[i].id_tranzaction == tranzaction_id_to_be_removed) {
			poz_tranzaction_with_id = i;
			break;
		}
	if (poz_tranzaction_with_id == 0)
		return -1;

	for (int i = poz_tranzaction_with_id; i < struct_obj -> nr_of_tranzactions; ++i)
		struct_obj -> arr_of_tranzactions[i] = struct_obj -> arr_of_tranzactions[i + 1];
	struct_obj -> nr_of_tranzactions -= 1;
	return 0;
}

/*
Modifica tranzactia cu id-ul egal cu id-ul tranzactiei modificate cu tranzactia modificata
Return values:
return 0  : Modificare realizata cu succes
return -1 : Modificare NEREALIZATA, implica inexistenta unei tranzactii cu id-ul egal cu id-ul noii tranzactii
*/
int modify_tranzaction_repo(struct_with_field_tranzactions* struct_obj,const tranzaction modified_tranzaction) {
	for (int i = 1; i <= struct_obj -> nr_of_tranzactions; ++i)
		if (struct_obj -> arr_of_tranzactions[i].id_tranzaction == modified_tranzaction.id_tranzaction) {
			struct_obj -> arr_of_tranzactions[i] = modified_tranzaction;
			return 0;
		}
	return -1;
}

/*
return : Numarul de tranzactii adaugate va reprezenta id-ul posibilei urmatoare tranzactii
*/
int get_next_tranzaction_id(struct_with_field_tranzactions struct_obj) {
	return struct_obj.nr_of_tranzactions_added_from_start;
}




