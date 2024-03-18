#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "repo_tranzactii.h"
#include "service_tranzactions.h"

#include "test_headers/test_domain.h"
#include "test_headers/test_repo.h"
#include "test_headers/test_service.h"

void test_all() {
	test_create_tranzaction();
	test_destroy_tranzaction();
	test_validate_tranzaction();
	test_create_list_of_tranzactions();
	test_destroy_struct_with_field_tranzactions();
	test_copie_struct_obj();
	test_add_tranzaction_repo();
	test_delete_tranzaction_repo();
	test_modify_tranzaction_repo();
	test_get_next_tranzaction_id();
	test_add_tranzaction_serv();
	test_delete_tranzaction_serv();
	test_modify_tranzaction_serv();
	test_lista_de_tranzactii_serv();
	test_filters_on_tranzactions_serv();
	test_sorting_based_of_criteria();
}
void menu() {
	printf("Optiuni:\n");
	printf("< 1 > Adaugare tranzactii\n");
	printf("< 2 > Modificare tranzactie existenta\n");
	printf("< 3 > Stergere tranzactie existenta\n");
	printf("< 4 > Vizualizare tranzactii dupa un criteriu\n");
	printf("< 5 > Vizualizare tranzactii ordonat dupa suma sau zi (crescator/descrescator)\n");
}
int read_option() {
	int option = 0;
	printf("Alegeti optiunea: ");
	if (scanf("%d", &option) == 1)
		return option;
	return -1;
}
void verify_option(int option) {
	if (option == -1) {
		fprintf(stderr, "Citirea optiunii a picat\n\n");
		exit(EXIT_FAILURE);
	}
	if (option < 1 || option > 5) 
		printf("\n<< OPTIUNE INVALIDA >>\n\n");

}
void read_data (int *day, int *sum, char type[10], char description[100]) {
	printf("day = ");
	if (scanf("%d", day) != 1) {
		fprintf(stderr, "Citirea zilei a picat\n\n");
		exit(EXIT_FAILURE);
	}
	getchar();

	printf("suma = ");
	if (scanf("%d", sum) != 1) {
		fprintf(stderr, "Citirea sumei a picat\n\n");
		exit(EXIT_FAILURE);
	}
	getchar();

	printf("tip: ");
	fgets(type, 9, stdin);

	printf("description: ");
	fgets(description, 99, stdin);
}
int add(struct_with_field_tranzactions* struct_obj) {
	int day = -1;
	int sum = -1;
	char type[10];
	char description[100];
	read_data(&day, &sum, type, description);

	if (add_tranzaction(struct_obj, day, sum, type, description) != 0)
		return -1;
	return 0;
}
void afisare_tranzactii(struct_with_field_tranzactions* struct_obj) {
	struct_with_field_tranzactions copie = lista_de_tranzactii(struct_obj);
	for (int i = 1; i <= copie.nr_of_tranzactions; ++i) {
		printf("tranzactia: %d\nid: %d\nday: %d\nsum: %d\n", i, copie.arr_of_tranzactions[i].id_tranzaction, copie.arr_of_tranzactions[i].day, copie.arr_of_tranzactions[i].sum);
		puts(copie.arr_of_tranzactions[i].type);
		puts(copie.arr_of_tranzactions[i].description);
		printf("\n\n");
	}
}
int modify(struct_with_field_tranzactions* struct_obj) {
	afisare_tranzactii(struct_obj);
	int id = -1;
	int day = -1;
	int sum = -1;
	char type[10];
	char description[100];
	printf("Alege un id pentru a modifica tranzactia respectiva : ");
	if (scanf("%d", &id) != 1) {
		fprintf(stderr, "Citirea id-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	getchar();
	read_data(&day, &sum, type, description);
	if (modify_tranzaction(struct_obj, id, day, sum, type, description) != 0)
		return -1;
	return 0;
}

int delete(struct_with_field_tranzactions* struct_obj) {
	afisare_tranzactii(struct_obj);
	int id = -1;
	printf("Alege un id pentru a sterge tranzactia respectiva : ");
	if (scanf("%d", &id) != 1) {
		fprintf(stderr, "Citirea id-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	getchar();
	if (delete_tranzaction(struct_obj, id) != 0)
		return -1;
	return 0;
}

int filter(struct_with_field_tranzactions* struct_obj){
	afisare_tranzactii(struct_obj);
	printf("Alege filtrele:\n");

	printf("< 1 > Type filter < intrare / iesire > \n");
	printf("< 2 > Filtru pentru tranzactii cu suma mai mare/mai mica decat o suma data ? < Y / n > \n");
	printf("< 12 > Ambele\n");

	int optiune_filtru = 0;
	printf("Optiune: ");
	if (scanf("%d", &optiune_filtru) != 1) {
		fprintf(stderr, "Citirea optiune_filtru-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	getchar();

	char type_filter[10];
	char mod_filter_2 = "l";
	int suma = -1;
	if (optiune_filtru == 1) {
		printf("Type filter: ");
		fgets(type_filter, 9, stdin);
	}
	else if (optiune_filtru == 2) {
		printf("Da-ti suma: ");
		if (scanf("%d", &suma) != 1) {
			fprintf(stderr, "Citirea sumei-ului a picat\n\n");
			exit(EXIT_FAILURE);
		}
		getchar();

		printf("Afisarea tranzactiilor cu suma mai ... decat %d : < H - mai mare / L - mai mica >", suma);
		if (scanf("%c", &mod_filter_2) != 1) {
			fprintf(stderr, "Citirea mod_filter_2-ului a picat\n\n");
			exit(EXIT_FAILURE);
		}
		getchar();
	}
	else if (optiune_filtru == 12) {
		fgets(type_filter, 9, stdin);
		printf("Da-ti suma: ");
		if (scanf("%d", &suma) != 1) {
			fprintf(stderr, "Citirea sumei a picat\n\n");
			exit(EXIT_FAILURE);
		}
		getchar();

		printf("Afisarea tranzactiilor cu suma mai ... decat %d : < H - mai mare / L - mai mica > ", suma);
		if (scanf("%c", &mod_filter_2) != 1) {
			fprintf(stderr, "Citirea mod_filter_2-ului a picat\n\n");
			exit(EXIT_FAILURE);
		}
		getchar();
	}
	struct_with_field_tranzactions filtred_tranzactions = filters_on_tranzactions(struct_obj, type_filter, suma, (char)toupper(mod_filter_2));
	afisare_tranzactii(&filtred_tranzactions);
	return 0;
}

int sorting(struct_with_field_tranzactions* struct_obj) {
	afisare_tranzactii(struct_obj);
	char mod_sortare = 'C';
	printf("Alege modul de sortare < C - crescator / D - descrescator > ");
	if (scanf(" %c", &mod_sortare) != 1) {
		fprintf(stderr, "Citirea mod_sortare-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	getchar();
	printf("Alege dupa ce se realizeaza sortare: < suma , zi > : ");
	char dupa_ce[10];
	fgets(dupa_ce, 9, stdin);
	if (!(strcmp(dupa_ce, "suma\n") == 0 || strcmp(dupa_ce, "zi\n") == 0))
		printf("<<  Mod sortare incorect  >>");

	struct_with_field_tranzactions sorted_tranzactions = sorting_based_of_criteria(struct_obj, mod_sortare, dupa_ce);
	afisare_tranzactii(&sorted_tranzactions);
	return 0;
}
void run() {
	struct_with_field_tranzactions struct_obj = create_list_of_tranzactions();
	int var_for_continue = 0;
	while (var_for_continue == 0) {
		menu();
		int option = read_option();
		verify_option(option);
		switch (option) {
		case 1:
			if (add(&struct_obj) != 0)
				printf("Ceva a pical la adaugare\n\n");
			else
				printf("OKKK\n\n");
			break;
		case 2:
			if (modify(&struct_obj) != 0)
				printf("Ceva a pical la modificare\n\n");
			else
				printf("OKKK\n\n");
			break;
		case 3:
			if (delete(&struct_obj) != 0)
				printf("Ceva a pical la stergere\n\n");
			else
				printf("OKKK\n\n");
			break;
		case 4:
			if (filter(&struct_obj) != 0)
				printf("Ceva a pical la filtrare\n\n");
			else
				printf("OKKK\n\n");
			break;
		case 5:
			if (sorting(&struct_obj) != 0)
				printf("Ceva a pical la sortare\n\n");
			else
				printf("OKKK\n\n");
			break;
		}
	}
	return 0;
}
int main(int argc, char** argv) {
	test_all();
	run();
	return 0;
}
// ana are mere