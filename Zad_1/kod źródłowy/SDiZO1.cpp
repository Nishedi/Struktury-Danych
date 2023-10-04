#define MAXSIZE 2000001
#include "TableMenu.h"
#include "ListMenu.h"
#include "KopiecMenu.h"
#include "Kopiec.h"
#include "BSTMenu.h"
#include "RBMenu.h"
#include <fstream>
#include <string>
#include <math.h>
#include "TabTest.h"
Timer timer;
int randtab[MAXSIZE];
void ordertable(int randtab[], int number) {
    for (int i = 0; i < number; i++) {
        randtab[i] =i+1;
    }
}

void randomshuttle(int randtab[], int number, int testnumber, int lpoj) {
    if (number == 0)return;
    srand((lpoj * 100 + testnumber) * 845);
   
    for (int i = 0; i < number; i++) {
        
        int randomplace1 = rand() % number;
        randomplace1 = randomplace1 * rand() % number;
        int randomplace2 = rand() % number;
        randomplace2 = randomplace2 * rand() % number;

        int swap = randtab[randomplace1];
        randtab[randomplace1] = randtab[randomplace2];
        randtab[randomplace2] = swap;

    }
}

int randtab2[MAXSIZE];


//Lista i Tblica
uint64_t testTabaddFirst(TabTest* bst, int randtab[], int number, int numbertoadd) {
    uint64_t time = 0;
    time = 1000000000;
    if (numbertoadd == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            bst->addFirst(randtab[i]);
        }
        timer.start();
        for (int i = number; i < number + numbertoadd; i++) {
            bst->addFirst(randtab[i]);
        }
        timer.stop();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        bst->clear();
    }
    time = time * 1000;   
    time = time / numbertoadd;
    return time;
}
uint64_t testTabaddLast(TabTest* bst, int randtab[], int number, int numbertoadd) {
    uint64_t time = 0;
    time = 1000000000;
    if (numbertoadd == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            bst->addFirst(randtab[i]);
        }
        timer.start();
        for (int i = number; i < number + numbertoadd; i++) {
            bst->addLast(randtab[i]);
        }
        timer.stop();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        bst->clear();
    }
    time = time * 1000;
     time = time / numbertoadd;
    return time;
}
uint64_t testTabRandomInsert(TabTest* bst, int randtab[], int number, int numbertoadd) {
    uint64_t time = 0;
    time = 1000000000;
    if (numbertoadd == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            bst->addFirst(randtab[i]);
        }
        timer.start();
        if (bst->counter > 0) {
            for (int i = number; i < number + numbertoadd; i++) {
                int pos = rand() % bst->counter;
                pos = pos * rand() % bst->counter;
                bst->insert(randtab[i],pos);
            }
        }
        timer.stop();if (timer.timeperiod() < time)time = timer.timeperiod();
        bst->clear();
    }
    time = time * 1000;
     time = time / numbertoadd;
    return time;
}
uint64_t testTabremoveFirst(TabTest* bst, int randtab[], int number, int numbertoadd) {
    uint64_t time = 0;
    time = 1000000000;
    if (numbertoadd == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            bst->addFirst(randtab[i]);
        }
        timer.start();
        for (int i = number; i < number + numbertoadd; i++) {
            bst->deleteFirst();
        }
        timer.stop();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        bst->clear();
    }
    time = time * 1000;
   time = time / numbertoadd;
    return time;
}
uint64_t testTabremoveLast(TabTest* bst, int randtab[], int number, int numbertoadd) {
    uint64_t time = 0;
    time = 1000000000;
    if (numbertoadd == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            bst->addFirst(randtab[i]);
        }
        timer.start();
        for (int i = number; i < number + numbertoadd; i++) {
            bst->deleteLast();
        }
        timer.stop();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        bst->clear();
    }
    time = time * 1000;
    time = time / numbertoadd;
    return time;
}
uint64_t testTabRandomRemove(TabTest* kopiec, int randtab[], int number, int randtab2[], int numbertofind) {
    uint64_t time = 1000000000;
    if (numbertofind == 0) return 0;

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            kopiec->addFirst(randtab[i]);
        }
        timer.start();
        for (int i = 0; i < numbertofind; i++) {
            int pos = rand() % kopiec->counter;
            pos = pos * rand() % kopiec->counter;
            kopiec->deleteAt(pos);
        }
        timer.stop();
        //std::cout << timer.timeperiod() << std::endl;
        //time = time + timer.timeperiod();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        kopiec->clear();
    }
    time = time * 1000;
    //time = time / 10;
    time = time / numbertofind;
    return time;
}
uint64_t testTabFind(TabTest* kopiec, int randtab[], int number, int randtab2[], int numbertofind) {
    uint64_t time = 1000000000;
    if (numbertofind == 0) return 0;

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            kopiec->addFirst(randtab[i]);
        }
        timer.start();
        for (int i = 0; i < numbertofind; i++) {
            kopiec->findElem(randtab2[i]);
        }
        timer.stop();
       if (timer.timeperiod() < time)time = timer.timeperiod();
        kopiec->clear();
    }
    time = time * 1000;
    time = time / numbertofind;
    return time;
}
//Koniec tablica

uint64_t testTREEadd(TREE* bst, int randtab[], int number, int numbertoadd) {
    uint64_t time = 0;
    time = 1000000000;
    if (numbertoadd == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            bst->add(randtab[i]);
        }
        timer.start();
        for (int i = number; i < number + numbertoadd; i++) {
            bst->add(randtab[i]);
        }
        timer.stop();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        bst->clear();
    }
    time = time * 1000;   
    time = time / numbertoadd;
    return time;
}
uint64_t testTREE(BST* tree1, RB* tree2, int randtab[], int number, int numbertoremove) {
    numbertoremove = 5;
    uint64_t time = 1000000000;
    if (numbertoremove == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            tree1->add(randtab[i]);
            tree2->add(randtab[i]);
        }
        timer.start();
       
        for (int i = number; i < number + numbertoremove; i++) {
            int val = tree1->head->value;
            tree1->removeFromTree(val);
            tree2->removeFromTree(val);
        }
        if (tree1->counter != tree2->counter)std::cout << "NOK";
        timer.stop();
        //std::cout << timer.timeperiod() << std::endl;

        if (timer.timeperiod() < time)time = timer.timeperiod();
        tree1->clear();
        tree2->clear();
    }
    time = time * 1000;
    time = time / numbertoremove;
    return time;
}
uint64_t testTREEremove(TREE* kopiec, int randtab[], int number, int numbertoremove) {
    uint64_t time = 1000000000;
    if (numbertoremove == 0) return 0;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            kopiec->add(randtab[i]);
        }
        timer.start();
       
        for (int i = number; i < number + numbertoremove; i++) {
            kopiec->deleteRoot();
        }
        timer.stop();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        kopiec->clear();
    }
    time = time * 1000;
    time = time / numbertoremove;
    return time;
}
uint64_t testTREEfind(TREE* kopiec, int randtab[], int number, int randtab2[], int numbertofind) {
    uint64_t time = 1000000000;
    if (numbertofind == 0) return 0;

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < number; i++) {
            kopiec->add(randtab[i]);
        }
        timer.start();
        for (int i = 0; i < numbertofind; i++) {
            kopiec->findvalue(randtab2[i]);
        }
        timer.stop();
        //std::cout << timer.timeperiod() << std::endl;
        //time = time + timer.timeperiod();
        if (timer.timeperiod() < time)time = timer.timeperiod();
        kopiec->clear();
    }
    time = time * 1000;
    time = time / numbertofind;
    return time;
}

int ma333in() {
    Table* tab = new Table();
    LinkedList* list = new LinkedList();
    Kopiec* kopiec = new Kopiec();
    BST* bst = new BST();
    RB* rb = new RB();
    TREE* tree;
    tree = kopiec;
    bst->add(7);
    bst->add(4);
    bst->add(3);
    bst->add(2);
    bst->add(5);
    bst->add(1);
    bst->add(6);
    bst->add(9);
    bst->add(8);
    bst->add(10);
    bst->prepareVisulaisation();
    bst->removeRoot();
    bst->prepareVisulaisation();
    bst->removeRoot();
    bst->prepareVisulaisation();
    bst->removeRoot();
    bst->prepareVisulaisation();
    bst->removeRoot(); bst->prepareVisulaisation();
    bst->removeRoot(); bst->prepareVisulaisation();
    bst->removeRoot(); bst->prepareVisulaisation();
    bst->removeRoot(); bst->prepareVisulaisation();
    bst->removeRoot(); bst->prepareVisulaisation();
    
    /*bst->makestraight(bst->head);
    bst->prepareVisulaisation();
    bst->DSW();*/

   // bst->prepareVisulaisation();

    /*tree->add(1);
    tree->findvalue(1);
    tree->deleteRoot();
    int startnum = 10000;
    int zakres;
    int inkrementacja;
    ordertable(randtab, 100000);
    randomshuttle(randtab, 100000, 0, 0);
    testTREE(bst, rb, randtab,100000,100000);
    //bst->prepareVisulaisation();
    //testRB(rb, randtab, startnum);*/
    return 0;
}

int mai8n() {
    Table* tab = new Table();
    LinkedList* list = new LinkedList();
    Kopiec* kopiec = new Kopiec();
    BST* bst = new BST();
    RB* rb = new RB();
    TREE* tree;
    TabTest* tTab=tab;
    int liczbatestow = 10;
    //std::string filename = "C:\\Users\\KONRAD PEMPERA\\Desktop\\SDiZO1\\SDiZO1\\";
    std::string filename = "C:\\tests\\tests.txt";
    int tabfromfile[1000];
    std::ifstream file(filename);
    if (!file.good()) {
        std::cout << "Blednie podana nazwa pliku\n";
        return -1;
    }
    std::string struktura;
    std::string operacja;
    int startnum;
    int zakres;
    int inkrementacja;

   
    while (file.eof() == false) {
        file >> struktura;
        file >> operacja;
        file >> startnum;
        file >> zakres;
        file >> inkrementacja;
      
        std::ofstream zapis("C:\\tests\\" + struktura + "_" + operacja + ".txt");
        
        int lpoj = 0;
        
        for (int n = startnum; n < zakres; n = n + inkrementacja) {
            lpoj++;
           
            for (int k = 0; k < liczbatestow; k++){
                int n1 = n / 100;
                ordertable(randtab, n+n1);
                zapis << n << " ";

                if (struktura.compare("LinkedList") == 0 || struktura.compare("Tab") == 0) {
                    if (struktura.compare("LinkedList") == 0) {
                        tTab = list;
                    }
                    if (struktura.compare("Tab") == 0) {
                        tTab = tab;
                    }
                    if (operacja.compare("addFirst") == 0) {
                        randomshuttle(randtab, n + n1, k, lpoj);
                        uint64_t time = testTabaddFirst(tTab, randtab, n, n1);
                        zapis << time << std::endl;
                        std::cout << time << " dodawanie na poczatek" << n << std::endl;
                    }
                    if (operacja.compare("addLast") == 0) {
                        randomshuttle(randtab, n + n1, k, lpoj);
                        uint64_t time = testTabaddLast(tTab, randtab, n, n1);
                        zapis << time << std::endl;
                        std::cout << time << " dodawanie na koniec " << n << std::endl;
                    }
                    if (operacja.compare("RandomInsert") == 0) {
                       
                        randomshuttle(randtab, n, k, lpoj);
                        for (int m = 0; m < n; m++) {
                            randtab2[m] = randtab[m];
                        }
                        randomshuttle(randtab2, n, k, lpoj);
                        uint64_t time = testTabRandomInsert(tTab, randtab, n,  n1);
                        zapis << time << std::endl; 
                        std::cout << time << " dodawanie w losowe miejsca " << n << std::endl;
                    }
                    if (operacja.compare("removeFirst") == 0) {
                        randomshuttle(randtab, n + n1, k, lpoj);
                        uint64_t time = testTabremoveFirst(tTab, randtab, n, n1);
                        zapis << time << std::endl;
                        std::cout << time << " usuwanie z poczatku " << n << std::endl;
                    }
                    if (operacja.compare("removeLast") == 0) {
                        randomshuttle(randtab, n + n1, k, lpoj);
                        uint64_t time = testTabremoveLast(tTab, randtab, n, n1);
                        zapis << time << std::endl;
                        std::cout << time << " usuwanie z konca " << n << std::endl;
                    }
                    if (operacja.compare("RandomRemove") == 0) {
                        randomshuttle(randtab, n, k, lpoj);
                        for (int m = 0; m < n; m++) {
                            randtab2[m] = randtab[m];
                        }
                        randomshuttle(randtab2, n, k, lpoj);

                        uint64_t time = testTabRandomRemove(tTab, randtab, n, randtab2,n1);
                        zapis << time << std::endl;
                        std::cout << time << " usuwanie z losowych pozycji " << n << std::endl;
                    }
                    if (operacja.compare("Find") == 0) {
                        randomshuttle(randtab, n, k, lpoj);
                        for (int m = 0; m < n; m++) {
                            randtab2[m] = randtab[m];
                        }
                        randomshuttle(randtab2, n, k, lpoj);
                        uint64_t time = testTabFind(tTab, randtab, n,randtab2, n1);
                        zapis << time << std::endl;
                        std::cout << time << " wyszukiwanie  " << n << std::endl;
                    }
                }



                if (struktura.compare("BST") == 0 || struktura.compare("RB") || struktura.compare("Kopiec")) {
                    tree = kopiec;

                    if (struktura.compare("Kopiec") == 0) {
                        tree = kopiec;
                    }
                    if (struktura.compare("BST") == 0) {
                        tree = bst;
                    }
                    if (struktura.compare("RB") == 0) {
                        tree = rb;
                    }


                    if (operacja.compare("add") == 0) {
                        randomshuttle(randtab, n + n1, k, lpoj);
                        uint64_t time = testTREEadd(tree, randtab, n, n1);
                        zapis << time << std::endl;
                        std::cout << time << " dodawanie " << n << std::endl;
                    }
                    if (operacja.compare("remove") == 0) {
                        randomshuttle(randtab, n, k, lpoj);
                        uint64_t time = testTREEremove(tree, randtab, n, n1);
                        zapis << time << std::endl;
                        std::cout << time << " usuwanie " << n << std::endl;
                    }
                    if (operacja.compare("find") == 0) {
                        randomshuttle(randtab, n, k, lpoj);
                        for (int m = 0; m < n; m++) {
                            randtab2[m] = randtab[m];
                        }
                        randomshuttle(randtab2, n, k, lpoj);
                        uint64_t time = testTREEfind(tree, randtab, n, randtab2, n1);
                        zapis << time << std::endl;
                        std::cout << time << " wyszukiwanie " << n << std::endl;
                    }
                }
        }
        }
        
        zapis.close();

    }
    file.close();
}//testy czasow
//testy czasow



int main(){
   

      int choice = 1;
      while (choice != 0) {
            std::cout << "Aby operowac na tablicy wcisnij ""1""\n";
            std::cout << "Aby operowac na liscie wcisnij ""2""\n";
            std::cout << "Aby operowac na kopcu wcisnij ""3""\n";
            std::cout << "Aby operowac na drzewie wcisnij ""4""\n";
            std::cout << "Aby operowac na drzewie RB wcisnij ""5""\n";
            std::cout << "Aby zakonczyc dzialanie aplikacji ""0""\n";
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
                TableMenu *tablemenu = new TableMenu();
                tablemenu->tabControll(0);
                delete(tablemenu);
                break;
            }
            case 2:
            {
                ListMenu * listMenu = new ListMenu();
                listMenu->listControll(0);
                delete(listMenu); 
                break;
            }
            case 3:
            {
                KopiecMenu *kopiecmenu = new KopiecMenu;
                kopiecmenu->kopiecController(0);
                delete(kopiecmenu);
                break;
            }
            case 4:
            {
                BSTMenu* bstMenu = new BSTMenu();
                bstMenu->bstControllerWithTimer(0);
                delete(bstMenu);
                break;
            }
            case 5:
            {
                RBMenu* rbmenu = new RBMenu();
                rbmenu->rbControllerWithTimer(0);
                delete(rbmenu);
                break;
            }   
            default:
                break;
            }
        }
    
    


    
      return 0;
   
}//testy aplikacji
//testy aplikacji