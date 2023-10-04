#include "BSTMenu.h"
void BSTMenu::deletetree() {
	if(rb->head!=NULL)
		rb->removeFromTree(rb->head->value);
}

int BSTMenu::checker(int tab[], int size, int value) {
	for (int j = 0; j < size; j++) {
		if (tab[j] == value) {
			return 1;
		}
	}
	return 0;
}

void BSTMenu::preparetable(int n, int tab[]) {
	int random;
	int i = 0;

	while (i < n) {
		srand(time(NULL));
		random = (std::rand() % 99) + 1;
		if (checker(tab, n, random) == 0) {
			tab[i] = random;
			i++;

		}
	}
}

void BSTMenu::bstControllerWithTimer(int x) {
	system("cls");
	Timer timer;

	int choice = 100;
	int random;
	while (choice!=0) {
		std::cout << "1. Wyswietl\n";
		std::cout << "2. Dodaj \n";
		std::cout << "3. Usun \n";
		std::cout << "4. Znajdz \n";
		std::cout << "5. Wyczysc \n";
		if (x == 0) {
			std::cout << "6. Testuj\n";
			
		}
		else {
			std::cout << "6. Powrot do normalnego trybu\n";
		}
		std::cout << "7. Wczytaj z pliku\n";
		std::cout << "0. Powrot do wyboru struktury\n";
		std::cin >> choice;
		switch (choice) {
		case 1:
		{
			rb->showinorder(rb->head);
			std::cout << "\n";
			rb->preparevisulaisation();
			break;
		}
		case 2:
		{
			std::cout << "Jaka liczbe dodac\n";
			std::cin >> random;

			if (x == 0) {
				rb->addToTree(random);
				break;
			}
			if (x == 1) {
				timer.start();
				rb->addToTree(random);
				timer.stop();
				std::cout << "Operacja dodania do drzewa trwala " << timer.timeperiod() << " mikrosekund\n";
			}
			break;
		}
		case 3:
		{
			std::cout << "Jaka liczbe usunac \n";
			std::cin >> random;
			int result;
			if (x == 0) {
				result=rb->removeFromTree(random);
			}
			if (x == 1) {
				timer.start();
				result = rb->removeFromTree(random);
				timer.stop();
				std::cout << "Operacja usuniecia z drzewa trwala " << timer.timeperiod() << " microsekund\n";
			}
			if (result == -1) std::cout << "Podana liczba nie znajduje sie w drzewie \n";
			break;
		}
		case 4:
		{

			std::cout << "Jaka liczbe wyszukac?\n";
			std::cin >> random;
			Element* el=NULL;
			if (x == 0) {
				el = rb->findInTree(rb->head, random);
			}
			if (x == 1) {
				timer.start();
				el=rb->findInTree(rb->head,random);
				timer.stop();
				std::cout << "Operacja wyszukania w drzewie trwala " << timer.timeperiod() << " microsekund\n";
			}
			if (el == NULL) {
				std::cout << "Nie znaleziono podanej wartosci w drzewie\n";
			}
			else {
				std::cout << "Znaleziono podana wartosc w drzewie\n";
			}
			break;
		}
		case 5:
		{
			deletetree();
			break;
		}
		case 6:
			if(x==0)
				bstControllerWithTimer(1);
			if (x == 1)
				bstControllerWithTimer(0);
		case 7: {
			deletetree();
			std::string filename = "kopiec.txt";
			int tabfromfile[1000];
			std::cout << "Podaj nazwe pliku z ktorego maja byc wczytane dane: \n";
			std::cin >> filename;
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
			for (int i = 0; i < number;i++) {
				rb->addToTree(tabfromfile[i]);
			}
			rb->preparevisulaisation();
			rb->showinorder(rb->head);
			break;
		}
		default: std::cout << "Bledny wybor dzialania\n";
		}
	}
}