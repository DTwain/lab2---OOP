#include <string.h>
#include "assert.h"
#include "service_tranzactions.h"
#include "repo_tranzactii.h"
#include "tranzaction.h"

void test_add_tranzaction_serv() {
	struct_with_field_tranzactions struct_obj = create_list_of_tranzactions();
	assert(add_tranzaction(&struct_obj, 12, 40, "iesire\n", "cumparaturi\n") == 0);

	assert(add_tranzaction(&struct_obj, 5, 500, "intrar\n", "imprumut\n") == -1);

	assert(struct_obj.nr_of_tranzactions == 1);
}

void test_delete_tranzaction_serv() {
	struct_with_field_tranzactions struct_obj = create_list_of_tranzactions();
	assert(add_tranzaction(&struct_obj, 12, 40, "iesire\n", "cumparaturi\n") == 0);
	assert(add_tranzaction(&struct_obj, 5, 500, "intrare\n", "imprumut\n") == 0);

	assert(delete_tranzaction(&struct_obj, 1) == 0);
	assert(delete_tranzaction(&struct_obj, 1) == -1);

	assert(struct_obj.nr_of_tranzactions == 1);
	assert(struct_obj.nr_of_tranzactions_added_from_start == 2);
}

void test_modify_tranzaction_serv() {
	struct_with_field_tranzactions struct_obj = create_list_of_tranzactions();
	assert(add_tranzaction(&struct_obj, 12, 40, "iesire\n", "cumparaturi\n") == 0);
	assert(add_tranzaction(&struct_obj, 5, 500, "intrare\n", "imprumut\n") == 0);

	assert(modify_tranzaction(&struct_obj, 0, 9, 100, "intrare\n", "cumparaturi + altele\n") == 0);
	assert(struct_obj.arr_of_tranzactions[1].day == 9);
	assert(struct_obj.arr_of_tranzactions[1].sum == 100);
	assert(strcmp(struct_obj.arr_of_tranzactions[1].type, "intrare\n") == 0);
	assert(strcmp(struct_obj.arr_of_tranzactions[1].description, "cumparaturi + altele\n") == 0);

	assert(modify_tranzaction(&struct_obj, 1, 9, 100, "intrare\n", "\0") == -1);
	assert(modify_tranzaction(&struct_obj, 4, 17, 1500, "iesire\n", "cumparaturi + altele\n") == -1);

}

void test_lista_de_tranzactii_serv() {
	struct_with_field_tranzactions struct_obj = create_list_of_tranzactions();
	assert(add_tranzaction(&struct_obj, 12, 40, "iesire\n", "cumparaturi\n") == 0);
	assert(add_tranzaction(&struct_obj, 5, 500, "intrare\n", "imprumut\n") == 0);

	struct_with_field_tranzactions copie = lista_de_tranzactii(&struct_obj);
	assert(copie.nr_of_tranzactions == 2);
	assert(copie.nr_of_tranzactions_added_from_start == 2);

	assert(copie.arr_of_tranzactions[1].id_tranzaction == 0);
	assert(copie.arr_of_tranzactions[1].day == 12);
	assert(copie.arr_of_tranzactions[1].sum == 40);
	assert(strcmp(copie.arr_of_tranzactions[1].type, "iesire\n") == 0);
	assert(strcmp(copie.arr_of_tranzactions[1].description, "cumparaturi\n") == 0);

	assert(copie.arr_of_tranzactions[2].id_tranzaction == 1);
	assert(copie.arr_of_tranzactions[2].day == 5);
	assert(copie.arr_of_tranzactions[2].sum == 500);
	assert(strcmp(copie.arr_of_tranzactions[2].type, "intrare\n") == 0);
	assert(strcmp(copie.arr_of_tranzactions[2].description, "imprumut\n") == 0);
}

void test_filters_on_tranzactions_serv() {
	struct_with_field_tranzactions struct_obj = create_list_of_tranzactions();
	assert(add_tranzaction(&struct_obj, 5, 500, "intrare\n", "imprumut\n") == 0);
	assert(add_tranzaction(&struct_obj, 12, 40, "iesire\n", "cumparaturi\n") == 0);
	assert(add_tranzaction(&struct_obj, 8, 300, "iesire\n", "plata ceva\n") == 0);
	assert(add_tranzaction(&struct_obj, 19, 1000, "intrare\n", "club\n") == 0);
	assert(add_tranzaction(&struct_obj, 24, 2000, "intrare\n", "televizor\n") == 0);

	struct_with_field_tranzactions copie = lista_de_tranzactii(&struct_obj);
	
	struct_with_field_tranzactions copie2 = filters_on_tranzactions(&struct_obj, "intrare\n", 400, 'H');
	assert(copie2.nr_of_tranzactions == 3);
	assert(copie2.arr_of_tranzactions[1].day == 5);
	assert(copie2.arr_of_tranzactions[1].sum == 500);
	assert(strcmp(copie2.arr_of_tranzactions[1].type, "intrare\n") == 0);
	assert(strcmp(copie2.arr_of_tranzactions[1].description, "imprumut\n") == 0);

	assert(copie2.arr_of_tranzactions[2].day == 19);
	assert(copie2.arr_of_tranzactions[2].sum == 1000);
	assert(strcmp(copie2.arr_of_tranzactions[2].type, "intrare\n") == 0);
	assert(strcmp(copie2.arr_of_tranzactions[2].description, "club\n") == 0);

	struct_with_field_tranzactions copie4 = filters_on_tranzactions(&struct_obj, "intrrrare\n", 400, 'H');
	assert(copie4.nr_of_tranzactions == 3);
	assert(copie4.arr_of_tranzactions[1].day == 5);
	assert(copie4.arr_of_tranzactions[1].sum == 500);
	assert(strcmp(copie4.arr_of_tranzactions[1].type, "intrare\n") == 0);
	assert(strcmp(copie4.arr_of_tranzactions[1].description, "imprumut\n") == 0);

	struct_with_field_tranzactions copie3 = filters_on_tranzactions(&struct_obj, "intraree\n", 400, 'L');
	assert(copie3.nr_of_tranzactions == 2);
	assert(copie3.arr_of_tranzactions[1].day == 12);
	assert(copie3.arr_of_tranzactions[1].sum == 40);
	assert(strcmp(copie3.arr_of_tranzactions[1].type, "iesire\n") == 0);
	assert(strcmp(copie3.arr_of_tranzactions[1].description, "cumparaturi\n") == 0);

}

void test_sorting_based_of_criteria() {
	struct_with_field_tranzactions struct_obj = create_list_of_tranzactions();
	assert(add_tranzaction(&struct_obj, 12, 1212, "intrare\n", "chirie\n") == 0);
	assert(add_tranzaction(&struct_obj, 4, 300, "iesire\n", "host\n") == 0);
	assert(add_tranzaction(&struct_obj, 30, 1222, "iesire\n", "jucarii\n") == 0);
	assert(add_tranzaction(&struct_obj, 7, 900, "intrare\n", "chirie\n") == 0);
	assert(add_tranzaction(&struct_obj, 22, 30, "iesire\n", "hugo\n") == 0);

	struct_with_field_tranzactions rezultat = sorting_based_of_criteria(&struct_obj, 'C', "suma\n");

	assert(rezultat.arr_of_tranzactions[1].id_tranzaction == 4);
	assert(rezultat.arr_of_tranzactions[2].id_tranzaction == 1);
	assert(rezultat.arr_of_tranzactions[3].id_tranzaction == 3);
	assert(rezultat.arr_of_tranzactions[4].id_tranzaction == 0);
	assert(rezultat.arr_of_tranzactions[5].id_tranzaction == 2);

	struct_with_field_tranzactions rezultat2 = sorting_based_of_criteria(&struct_obj, 'C', "zi\n");

	assert(rezultat2.arr_of_tranzactions[1].id_tranzaction == 1);
	assert(rezultat2.arr_of_tranzactions[2].id_tranzaction == 3);
	assert(rezultat2.arr_of_tranzactions[3].id_tranzaction == 0);
	assert(rezultat2.arr_of_tranzactions[4].id_tranzaction == 4);
	assert(rezultat2.arr_of_tranzactions[5].id_tranzaction == 2);

	struct_with_field_tranzactions rezultat3 = sorting_based_of_criteria(&struct_obj, 'D', "suma\n");

	assert(rezultat3.arr_of_tranzactions[1].id_tranzaction == 2);
	assert(rezultat3.arr_of_tranzactions[2].id_tranzaction == 0);
	assert(rezultat3.arr_of_tranzactions[3].id_tranzaction == 3);
	assert(rezultat3.arr_of_tranzactions[4].id_tranzaction == 1);
	assert(rezultat3.arr_of_tranzactions[5].id_tranzaction == 4);

	struct_with_field_tranzactions rezultat4 = sorting_based_of_criteria(&struct_obj, 'D', "zi\n");

	assert(rezultat4.arr_of_tranzactions[1].id_tranzaction == 2);
	assert(rezultat4.arr_of_tranzactions[2].id_tranzaction == 4);
	assert(rezultat4.arr_of_tranzactions[3].id_tranzaction == 0);
	assert(rezultat4.arr_of_tranzactions[4].id_tranzaction == 3);
	assert(rezultat4.arr_of_tranzactions[5].id_tranzaction == 1);




}