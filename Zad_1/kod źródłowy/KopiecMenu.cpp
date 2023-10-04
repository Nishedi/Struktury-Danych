#include "KopiecMenu.h"
#include <fstream>
void KopiecMenu::kopiecController(int x) {
	int value=-1;
	int choice;
	do {
		std::cout << "1. Wyswietl\n";
		std::cout << "2. Dodaj \n";
		std::cout << "3. Usun \n";
		std::cout << "4. Znajdz \n";
		std::cout << "5. Wyczysc \n";
		if (x == 0) {
			std::cout << "6. Testuj\n";
			std::cout << "7. Wczytaj z pliku\n";
		}
		std::cout << "0. Powrot do wyboru struktury\n";
		std::cin >> choice;
		int rand;
		switch (choice) {
		case 1:
			kopiec->prepareVisulaisation();
			break;
		case 2:
			std::cout << "Jaka wartosc dodac?\n";
			std::cin >> value;
			if (x == 0) {
				kopiec->add(value);
			}
			if (x == 1) {
				timer.start();
				kopiec->add(value);
				timer.stop();
				std::cout << "Czas dodania wybranego elementu do struktury trwal " << timer.timeperiod() << " nanosekund\n";
			}
			kopiec->prepareVisulaisation();
			break;
		case 3:
			std::cout << "Usuwanie korzenia\n";
			if (x == 0) {
				kopiec->deleteRoot();
			}
			if (x == 1) {
				timer.start();
				kopiec->deleteRoot();
				timer.stop();
				std::cout << "Czas usunieca korzenia ze struktury trwal " << timer.timeperiod() << " nanosekund\n";
			}
			kopiec->prepareVisulaisation();
			break;
		case 4:
		{
			std::cout << "Jaka liczbe wyszukac?\n";
			std::cin >> value;
			int result = -1;
			if (x == 0) {
				result = kopiec->findvalue(value);
			}
			if (x == 1) {
				timer.start();
				result = kopiec->findvalue(value);
				timer.stop();
				std::cout << "Czas wyszukania wybranego elementu ze struktury trwal " << timer.timeperiod() << " nanosekund\n";
			}
			if (result == -1) {
				std::cout << "Wartosc nie zostala znaleziona\n";
			}
			else {
				std::cout << "Wartosc " << result << " zostala znaleziona\n";
			}
			break;
		}
		case 5:
			while (kopiec->counter != 0)
				kopiec->deleteRoot();
			break;
		case 6:
		{
			kopiecController(1);
			break;
		}
		case 7: 
		{
			while (kopiec->counter != 0)
				kopiec->deleteRoot();
			std::string filename = "kopiec.txt";
			int tabfromfile[1000];
			std::cout << "Podaj nazwe pliku z ktorego maja byc wczytane dane: \n";
			std::ifstream file(filename);
			if (!file.good()) {
				std::cout << "Blednie podana nazwa pliku\n";
				return;
			}
			int l;
			int i = 0;
			int it = 0;
			int number;
			file >> number;

			while (it < number) {
				file >> l;
				tabfromfile[i] = l;
				i++;
				it++;
			}
			file.close();
			kopiec->create(tabfromfile, i);
			kopiec->prepareVisulaisation();
			kopiec->show();
			break;
		}
		}
		

	} while (choice != 0);
}