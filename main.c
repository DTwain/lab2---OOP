#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <crtdbg.h>
#include "repo_tranzactii.h"
#include "service_tranzactions.h"

#include "test_headers/test_domain.h"
#include "test_headers/test_repo.h"
#include "test_headers/test_service.h"

#define _CRTDBG_MAP_ALLOC

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
	test_resize();
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
	if (scanf_s("%d", &option) == 1)
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
void read_data (int *day, int *sum, char type[], char description[]) {
	printf("day = ");
	if (scanf_s("%d", day) != 1) {
		fprintf(stderr, "Citirea zilei a picat\n\n");
		exit(EXIT_FAILURE);
	}
	if (getchar() == EOF)
		exit(EXIT_FAILURE);

	printf("suma = ");
	if (scanf_s("%d", sum) != 1) {
		fprintf(stderr, "Citirea sumei a picat\n\n");
		exit(EXIT_FAILURE);
	}
	if (getchar() == EOF)
		exit(EXIT_FAILURE);

	printf("tip: ");
	fgets(type, 60, stdin);

	printf("description: ");
	fgets(description, 300, stdin);

}
int add(struct_with_field_tranzactions* struct_obj) {
	int day = -1;
	int sum = -1;
	char type[60];
	char description[300];
	read_data(&day, &sum, type, description);

	size_t lengh_type = strlen(type);
	char* type_dinamic = (char*)malloc(lengh_type + 1);
	if (type_dinamic == NULL)
		exit(EXIT_FAILURE);
	strcpy_s(type_dinamic, lengh_type + 1, type);

	size_t lengh_description = strlen(description);
	char* description_dinamic = (char*)malloc(lengh_description + 1);
	if (description_dinamic == NULL)
		exit(EXIT_FAILURE);
	strcpy_s(description_dinamic, lengh_description + 1, description);

	if (add_tranzaction(struct_obj, day, sum, type, description) != 0) {
		free(type_dinamic);
		free(description_dinamic);
		return -1;
	}
	free(type_dinamic);
	free(description_dinamic);
	return 0;
}
void afisare_tranzactii(struct_with_field_tranzactions* struct_obj) {
	for (int i = 0; i < struct_obj-> nr_of_tranzactions; ++i) {
		printf("tranzactia: %d\nid: %d\nday: %d\nsum: %d\n", i, struct_obj-> arr_of_tranzactions[i].id_tranzaction, struct_obj-> arr_of_tranzactions[i].day, struct_obj-> arr_of_tranzactions[i].sum);
		puts(struct_obj-> arr_of_tranzactions[i].type);
		puts(struct_obj-> arr_of_tranzactions[i].description);
		printf("\n\n");
	}
}
int modify(struct_with_field_tranzactions* struct_obj) {
	afisare_tranzactii(struct_obj);

	int id = -1;
	int day = -1;
	int sum = -1;
	char type[60];
	char description[300];

	printf("Alege un id pentru a modifica tranzactia respectiva : ");
	if (scanf_s("%d", &id) != 1) {
		fprintf(stderr, "Citirea id-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	if (getchar() == EOF)
		exit(EXIT_FAILURE);
	read_data(&day, &sum, type, description);

	size_t lengh_type = strlen(type);
	char* type_dinamic = (char*)malloc(lengh_type + 1);
	if (type_dinamic == NULL)
		exit(EXIT_FAILURE);
	strcpy_s(type_dinamic, lengh_type + 1, type);

	size_t lengh_description = strlen(description);
	char* description_dinamic = (char*)malloc(lengh_description + 1);
	if (description_dinamic == NULL)
		exit(EXIT_FAILURE);
	strcpy_s(description_dinamic, lengh_description + 1, description);

	if (modify_tranzaction(struct_obj, id, day, sum, type_dinamic, description_dinamic) != 0) {
		free(type_dinamic);
		free(description_dinamic);
		return -1;
	}
	free(type_dinamic);
	free(description_dinamic);
	return 0;
}

struct_with_field_tranzactions* delete(struct_with_field_tranzactions* struct_obj) {
	afisare_tranzactii(struct_obj);
	int id = -1;
	printf("Alege un id pentru a sterge tranzactia respectiva : ");
	if (scanf_s("%d", &id) != 1) {
		fprintf(stderr, "Citirea id-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	if (getchar() == EOF)
		exit(EXIT_FAILURE);
	struct_with_field_tranzactions* rezultat = delete_tranzaction(struct_obj, id);
	return rezultat;
}

int filter(struct_with_field_tranzactions* struct_obj){
	afisare_tranzactii(struct_obj);
	printf("Alege filtrele:\n");

	printf("< 1 > Type filter < intrare / iesire > \n");
	printf("< 2 > Filtru pentru tranzactii cu suma mai mare/mai mica decat o suma data ? < Y / n > \n");
	printf("< 12 > Ambele\n");

	int optiune_filtru = 0;
	printf("Optiune: ");
	if (scanf_s("%d", &optiune_filtru) != 1) {
		fprintf(stderr, "Citirea optiune_filtru-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	if (getchar() == EOF)
		exit(EXIT_FAILURE);

	char type_filter[50];
	type_filter[0] = '\0';
	char mod_filter_2 = 'L';
	int suma = -1;

	if (optiune_filtru == 1) {
		printf("Type filter: ");
		fgets(type_filter, 50, stdin);
	}
	else if (optiune_filtru == 2) {
		printf("Da-ti suma: ");
		if (scanf_s("%d", &suma) != 1) {
			fprintf(stderr, "Citirea sumei-ului a picat\n\n");
			exit(EXIT_FAILURE);
		}
		if (getchar() == EOF)
			exit(EXIT_FAILURE);

		printf("Afisarea tranzactiilor cu suma mai ... decat %d : < H - mai mare / L - mai mica >", suma);
		if (scanf_s("%c", &mod_filter_2, 1) != 1) {
			fprintf(stderr, "Citirea mod_filter_2-ului a picat\n\n");
			exit(EXIT_FAILURE);
		}
		if (getchar() == EOF)
			exit(EXIT_FAILURE);
	}
	else if (optiune_filtru == 12) {
		printf("Type filter: ");
		fgets(type_filter, 50, stdin);
		printf("Da-ti suma: ");
		if (scanf_s("%d", &suma) != 1) {
			fprintf(stderr, "Citirea sumei a picat\n\n");
			exit(EXIT_FAILURE);
		}
		if (getchar() == EOF)
			exit(EXIT_FAILURE);

		printf("Afisarea tranzactiilor cu suma mai ... decat %d : < H - mai mare / L - mai mica > ", suma);
		if (scanf_s("%c", &mod_filter_2, 1) != 1) {
			fprintf(stderr, "Citirea mod_filter_2-ului a picat\n\n");
			exit(EXIT_FAILURE);
		}
		if (getchar() == EOF)
			exit(EXIT_FAILURE);
	}
	size_t lengh_type_filter = strlen(type_filter);
	char* type_filter_dinamic = (char*)malloc(lengh_type_filter + 1);
	if (type_filter_dinamic == NULL)
		exit(EXIT_FAILURE);
	strcpy_s(type_filter_dinamic, lengh_type_filter + 1, type_filter);

	struct_with_field_tranzactions *filtred_tranzactions = filters_on_tranzactions(struct_obj, type_filter_dinamic, suma, (char)toupper(mod_filter_2));
	
	afisare_tranzactii(filtred_tranzactions);

	free(type_filter_dinamic);
	destroy_struct_with_field_tranzactions(filtred_tranzactions);
	return 0;
}

int sorting(struct_with_field_tranzactions* struct_obj) {
	afisare_tranzactii(struct_obj);
	char mod_sortare = 'C';
	printf("Alege modul de sortare < C - crescator / D - descrescator > ");
	if (scanf_s(" %c", &mod_sortare, 1) != 1) {
		fprintf(stderr, "Citirea mod_sortare-ului a picat\n\n");
		exit(EXIT_FAILURE);
	}
	if (getchar() == EOF)
		exit(EXIT_FAILURE);
	
	printf("Alege dupa ce se realizeaza sortare: < suma , zi > : ");
	char dupa_ce[50];
	fgets(dupa_ce, 50, stdin);
	if (!(strcmp(dupa_ce, "suma\n") == 0 || strcmp(dupa_ce, "zi\n") == 0))
		printf("<<  Mod sortare incorect  >>");

	size_t lengh_dupa_ce = strlen(dupa_ce);
	char* dupa_ce_dinamic = (char*)malloc(lengh_dupa_ce + 1);
	if (dupa_ce_dinamic == NULL)
		exit(EXIT_FAILURE);
	strcpy_s(dupa_ce_dinamic, lengh_dupa_ce + 1, dupa_ce);

	struct_with_field_tranzactions *sorted_tranzactions = sorting_based_of_criteria(struct_obj, mod_sortare, dupa_ce_dinamic);
	afisare_tranzactii(sorted_tranzactions);

	free(dupa_ce_dinamic);
	destroy_struct_with_field_tranzactions(sorted_tranzactions);
	return 0;
}
void run() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	int var_for_continue = 0;
	while (var_for_continue == 0) {
		menu();
		int option = read_option();
		verify_option(option);
		switch (option) {
		case 1:
			if (add(struct_obj) != 0)
				printf("Ceva a pical la adaugare\n\n");
			else
				printf("OKKK\n\n");
			break;
		case 2:
			if (modify(struct_obj) != 0)
				printf("Ceva a pical la modificare\n\n");
			else
				printf("OKKK\n\n");
			break;
		case 3: {
			struct_with_field_tranzactions* rezultat = delete(struct_obj);
			if (rezultat == NULL)
				printf("Ceva a pical la stergere\n\n");
			else {
				struct_obj = rezultat;
				printf("OKKK\n\n");
			}
			break;
		}
		case 4:
			if (filter(struct_obj) != 0)
				printf("Ceva a pical la filtrare\n\n");
			else
				printf("OKKK\n\n");
			break;
		case 5:
			if (sorting(struct_obj) != 0)
				printf("Ceva a pical la sortare\n\n");
			else
				printf("OKKK\n\n");
			break;
		}
	}
	destroy_struct_with_field_tranzactions(struct_obj);
}
int main() {
	test_all();
	//run();
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}
// ana are mere