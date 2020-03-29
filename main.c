// Nome: João Paulo Mendes Rodrigues | Número: 21260309

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "vars.h"
#include "menus.h"
#include "memLoadSave.h"
#include "funcAreas.h"
#include "funcAnimais.h"
#include "listAnimais.h"
#include "funcExtra.h"

int main(int argc, char** argv) {
	int total_areas, menuPri, menuSec, menuTerc, extra;
	char listAnim[TAM_STRING];
	
	char *file_areas = FILE_AREAS, *file_animais = FILE_ANIMAIS, *file_especies = FILE_ESPECIES;
	parea areas = NULL;
	pespecie especies = NULL;
	
	extra = MenuExtra();

	total_areas = 0;
	areas = loadAreas(areas, &total_areas, file_areas);
	
	if (areas != NULL) {
		if(extra)
			especies = readEspecies(especies, file_especies);
		
		readAnimais(areas, total_areas, file_animais, especies, extra);
		
		do {
			menuPri = Menu();
			switch (menuPri) {
				case 1:
					do {
						menuSec = MenuAreas();
						switch (menuSec) {
							case 1:
								showAreas(areas, total_areas, extra);
								break;
							case 2:
								areas = addAreas(areas, &total_areas);
								break;
							case 3:
								areas = delAreas(areas, &total_areas);
								break;
							case 5:
								menuPri = 3; // opcao = terminar ==> o menu principal assume a opcao terminar
								break;
						}
					} while (menuSec != 4 && menuSec != 5); // opcao != voltar e terminar
					break;
					
				case 2:
					do {
						menuSec = MenuAnimais();
						switch (menuSec) {
							case 1:
								do{
									menuTerc=MenuAnimaisListagem();
									switch (menuTerc) {
										case 1:
											showAnimaisTodos(areas, total_areas);
											break;
										case 2:
											printf("Area dos Animais? "); scanf(" %s", listAnim);
											showAnimaisLoc(areas, total_areas, listAnim);
											break;
										case 3:
											printf("Especie dos Animais? "); scanf(" %s", listAnim);
											showAnimaisEsp(areas, total_areas, listAnim);
											break;
										case 4:
											printf("ID do Animal? "); scanf(" %s", listAnim);
											showAnimaisInfo(areas, total_areas, listAnim, especies, extra);
											break;
										case 6:
											menuSec=7;// opcao = terminar ==> o menu secundario assume a opcao terminar
											menuPri=3;// opcao = terminar ==> o menu principal assume a opcao terminar
											break;
									}
								}while(menuTerc != 5 && menuTerc != 6);// opcao != voltar e terminar
								break;
							case 2:
								verificaTransferAnimais(areas, total_areas, extra);
								break;
							case 3:
								verificaDelAnimal(areas, total_areas, especies, extra);
								break;
							case 4:
								verificaNascerAnimal(areas, total_areas, extra);
								break;
							case 5:
								especies = addAnimalFich(areas, total_areas, especies, extra);
								break;
							case 7:
								menuPri = 3; // opcao = terminar ==> o menu principal assume a opcao terminar
								break;
						}
					} while (menuSec != 6 && menuSec != 7); // opcao != voltar e terminar
					break;
			}
		} while (menuPri != 3); // opcao != terminar
		if(menuPri == 3)
			saveZoo(areas, total_areas, especies, extra);
	}
	return (EXIT_SUCCESS);
}

