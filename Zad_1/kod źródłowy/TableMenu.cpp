#include "TableMenu.h"
#include <fstream>

void TableMenu::clear(Table *table) {
    int j = table->counter;
    for (int i = 0; i < j; i++) {
        table->deleteLast();
    }
}

void TableMenu::tabControll(int x) {
    system("cls");


    int choice = 0;
    do {
        std::cout << "1. Wyswietl \n";
        std::cout << "2. Dodaj \n";
        std::cout << "3. Usun \n";
        std::cout << "4. Wyszukaj \n";
        std::cout << "5. Wyczysc tablice\n";
        if (x == 0) {
            std::cout << "6. Testuj czas \n";
            std::cout << "7. Wczytaj z pliku\n";
        }
        std::cout << "Aby wrocic do wyboru struktury wcisnij ""0"" \n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "Wyswietlanie od przodu: \n";
            table->showTab();
            std::cout << "Wyswietlanie od tylu: \n";
            table->showTabReversed();
            break;
        case 2:
        {
            std::cout << "Podaj indeks, na ktory chcesz wpisac nowa wartosc\n";
            int choice2;
            std::cin >> choice2;
            if (choice2 >= table->counter) {
                std::cout << "Pozycja poza zakresem\n";
                break;
            }
            std::cout << "Wpisz jaka wartosc dodac do tablicy\n";
            int value;
            std::cin >> value;
            if (x == 0) {
                if (choice2 == 0)
                    table->addFirst(value);
                if (choice2 == table->counter-1&&choice2!=0)
                    table->addLast(value);
                if(choice2!= 0 && choice2!=table->counter-1)
                    table->insert(value, choice2);
            }
            if (x == 1) {
                timer.start();
                if (choice2 == 0)
                    table->addFirst(value);
                if (choice2 == table->counter-1&&choice2!=0)
                    table->addLast(value);
                if (choice2 != 0 && choice2 != table->counter-1)
                    table->insert(value, choice2);
                timer.stop();
                std::cout << "Czas dodania wartosci na wskazana pozycje trwal " << timer.timeperiod() << " nanosekund\n";
            }
            table->showTab();
            break;
        }
        case 3:
        {
            std::cout << "Z jakiej pozycji usunac wartosc?\n";
            int position = -1;
            std::cin >> position;
            if (position >= table->counter) {
                std::cout << "Pozycja poza zakresem\n";
                break;
            }

            if (x == 0) {
                if (position == 0)
                    table->deleteFirst();
                if (position == table->counter - 1 && position != 0)
                    table->deleteLast();
                if (position != 0 && position != table->counter - 1)
                    table->deleteAt(position);
            }
            if (x == 1) {
                timer.start();
                if (position == 0)
                    table->deleteFirst();
                if (position == table->counter - 1 && position != 0)
                    table->deleteLast();
                if (position != 0 && position != table->counter - 1)
                    table->deleteAt(position);
                timer.stop();
                std::cout << "Czas trwania usuwania elementu z wybranej pozycji wynosi " << timer.timeperiod() << " nanosekund\n";
            }
            

            table->showTab();
            table->showTabReversed();
            break;
        }
        case 4:
        {
            int result=-1;
            int random = std::rand() % 100;
            std::cin >> random;
            if (x == 0)
                result = table->findElem(random);

            if (x == 1) {
                timer.start();
                result = table->findElem(random);
                timer.stop();
                std::cout << "Operacja wyszukania elementu trwala " << timer.timeperiod() << " nanoseuknd";
            }

            if (result != -1)std::cout << "Liczba zostala znaleziona\n";
            else std::cout << "Liczba nie zostala znaleziona\n";
            break;
        }
        case 5:
        {
            clear(table);
        }
        case 6:
            if (x == 1)break;
            tabControll(1);
            break;
        case 7:
            {
                clear(table);
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
                int it = 0;
                int number;
                file >> number;

                while (it<number) {
                    file >> l;
                    tabfromfile[i] = l;
                    i++;
                    it++;
                }
                file.close();
                for (int j = 0; j < i; j++) {
                    table->addLast(tabfromfile[j]);
                }
                table->showTab();
                break;
            }
        
        }



    } while (choice != 0);
}