#include "ListMenu.h"
#include <fstream>


void ListMenu::listControll(int x) {
    system("cls");


    int choice = 0;
    do {
        std::cout << "1. Wyswietl \n";
        std::cout << "2. Dodaj \n";
        std::cout << "3. Usun\n";
        std::cout << "4. Znajdz \n";
        std::cout << "5. wyczysc liste\n";
        if (x == 0) {
            std::cout << "6. Testuj \n";
            std::cout << "7. Wczytaj z pliku\n";
        }
            
        std::cout << "Aby wrocic do wyboru struktury wcisnij ""0"" \n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            list->showList();
            list->showListReversed();
            break;
        case 2:
            std::cout << "Na jaka pozycje wstawic nowy element? \n";
            int choice2;
            std::cin >> choice2;
            if (choice2 >= list->counter) {
                std::cout << "Pozycja spoza zakresu\n";
            }
            std::cout << "Podaj jaka wartosc chcesz dodac\n";
            int value;
            std::cin >> value;
            
            if (x == 0) {
                if (choice2 == 0) {
                    list->addFirst(value);
                }
                if (choice2 == list->counter-1&&choice2!=0) {
                    list->addLast(value);
                }
                if (value != 0 && value != list->counter-1) {
                    list->insert(value, choice2);
                }
            }
            if (x == 1) {
                timer.start();
                if (choice2 == 0) {
                    list->addFirst(value);
                }
                if (choice2 == list->counter - 1 && choice2 != 0) {
                    list->addLast(value);
                }
                if (value != 0 && value != list->counter - 1) {
                    list->insert(value, choice2);
                }
                std::cout << "Operacja dodania elementu na wskazana pozycje trwala " << timer.timeperiod() << " nanosekund\n";
            }
            list->showList();
            list->showListReversed();
            break;
        case 3:
        {
            int todelete;
            std::cout << "Podaj wartosc do usuniecia\n";
            std::cin >> todelete;
            if(x==0)
                list->deleteValue(todelete);
            if (x == 1) {
                timer.start();
                list->deleteValue(value);
                timer.stop();
                std::cout << "Operacja usuniecia zadanej wartosci trwala " << timer.timeperiod() << " nanosekund\n";
            }
            list->showList();
            list->showListReversed();
            break;
        }
        case 4:
        {
            int value = std::rand() % 16;
            std::cout << "Jaka liczbe wyszukac?\n";
            std::cin >> value;
            ElemList* number = NULL;
            if (x == 0) {
                number = list->findElement(value);
            }
            if (x == 1) {
                timer.start();
                number = list->findElement(value);
                timer.stop();
                std::cout << "Operacja wyszukania wartosci w liscie trwala " << timer.timeperiod() << " nanosekund\n";
            }

            if (number == NULL) {
                std::cout << "W strukturze nie ma takiej liczby\n";
            }
            else {
                std::cout << "Znaleziono element " << number->value << std::endl;
            }
            break;
        }
        case 5:
        {
            for (int i = 0; i < list->counter; i++) {
                list->deleteFirst();
            }
        }
        case 6:
        {
            if (x == 0)break;
            listControll(1);
            break;
        }
        case 7:
        {
            std::string filename = " ";
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
            int number;
            int it = 0;

            file >> number;

            while (it < number) {
                file >> l;
                tabfromfile[i] = l;
                i++;
                it++;
            }
            file.close();

            for (int j = 0; j < i; j++) {
                list->addFirst(tabfromfile[j]);
            }
            list->showList();
            list->showListReversed();
            break;
        }
        
        }

    } while (choice != 0);
}