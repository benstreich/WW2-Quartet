#include <stdio.h>              
#include <conio.h>
#include <stdlib.h>
#include <string.h>         //Diese Bibliothek wird für strcpy verwendet
#include <conio.h>
#include <dos.h>
#include <time.h>           //Diese Bibliothek wird vorallem für die Random funktion verwendet (rand)
#include <Windows.h>        //Diese Bibliothek wird verwendet für die Sleep funktion (z.b. Sleep(500);)



typedef struct Cards {      //Typedef Struktur für das Quiz
    int Number;             //Werte der Funktion Cards
    char Flugzeuge[50];
    int kmh;
    int Gipfelhoehe;
    double Ps;
    struct Cards* pNext;    //pointer auf pNext (Zeiger auf Nächste Karte)
}struCards;


struCards* func_cardwon(struCards* pListWon, struCards* pListLost);                                  //Diese Funktion ist für den Gewinner einer Karte zuständig (Won). Diese Funktion benutzt ebenfalls die Funktion func_Counting_List
int Func_Counting_List(struCards* pListe);                                                          //Diese Funktion ist für die Zählung der Aktuellen Liste 
struCards* func_cardlost(struCards* pListLost);                                                      //Diese Funktion ist für den Verlierer der Karte zuständig (Lost)

int Func_Cards_Comparing(int Type, struCards* pCards_Player, struCards* pCards_Computer);            //Diese Funktion ist zuständig für das Vergleichen der Karten (Wer gewinnt der Zwei Karten (Player vs Computer))
struCards* Func_CreatingList(struCards* pList, struCards* pCard);                                    //Diese Funktion ist zuständig für das Erstellen von Listen (Create)
struCards* Func_removingList(struCards* pList, struCards* pCard);                                    //Diese Funktion ist zuständig für das Löschen von einzelnen Karten
struCards* Func_Card(double plane, const char* pDesignation, int kmh, int summit_heigt, double Ps);  //Hier werden die Werte in der Struktur (typedef struct Cards) in die Karte gefüllt
int Func_system_Output(struCards* pCards_Player, struCards* pCards_Computer);                        //Diese funktion sieht der Spieler, hier kann er sich entscheiden zwischen Verschiedenen Werten seiner Karte
void Func_GameWon();                                                                                 //Grafik mit "You Won" diese wird natürlich nur ausgeführt wenn der Spieler gewonnen hat, Diese wird ausgeführt in der Funktion func_system_Output gleich nachdem Vergleich der Zwei Werten
void Func_GameLost();                                                                                //Grafik mit "You Lost" diese wird natürlich nur ausgeführt wenn der Spieler Verloren hat, Diese wird ausgeführt in der Funktion func_system_Output gleich nachdem Vergleich der Zwei Werten
int Func_Starting_Quartet();
void func_CardComputer(struCards* pCards_Computer, struCards* pCards_Player, int Quantity);
void Func_Main_Menu();


int main() {
    //Main Methode Leitet weiter and Func_Main_Menu von dort aus weiter ins Spielen

    Func_Main_Menu();   //Func_Main_Menu ist die Funktion für Das Hauptmenu (Erste Interaktion mit Spieler)                            
    return 0;
}

int Func_system_Output(struCards* pCards_Player, struCards* pCards_Computer) {
    //Geschrieben von *Ben*
    //Diese funktion sieht der Spieler, hier kann er sich entscheiden zwischen Verschiedenen Werten seiner Karte
    //Parameter pCards_Player, pCards_Computer 
    //Aufgerufen in Func_Starting_Quartett 
    //Funktion für das eigentliche Spielen des Quartettes
    //Keinen Returnwert (return 0;)
    char X;

    char k;

    bool NextCard = false;
    int Card_Mod = 0;                                                                                    //0 = Nichts (Default), 1 = Won, 2 = Lost, 3 = Tie
    bool BackinMenu = false;

    while (!BackinMenu) {
        NextCard = false;

        int QuantityofPlayers;                                                                           //Anzahl Karten Spieler (Variablerstellung)
        int QuantityofComputer;                                                                          //Anzahl Karten Computer (Variablerstellung)


        QuantityofPlayers = Func_Counting_List(pCards_Player);                                          //Karten im Stapel (Player) (Instanziierung mit der Funktion: Func_counting_List)
        QuantityofComputer = Func_Counting_List(pCards_Computer);                                       //Karten im Stapel (Computer) (Instanziierung mit der Funktion: Func_counting_List)


       // Kartenausgabe-Schleife
        while (!NextCard && !BackinMenu && QuantityofPlayers > 0 && QuantityofComputer > 0) {           //while schleife für deb Eigentlichen "Spielstart"
            system("cls");
            printf(" ___________________________________________                ___________________________________________\n");
            printf("|                                           |              |                                           |\n");
            printf("|                 Computer                  |              |               Deine Karte                 |\n");
            printf("|                                           |              |                                           |\n");
            printf("|                                           |              |  Bezeichnung:    %-25s|\n", pCards_Player->Flugzeuge);
            printf("|                   ?????                   |              |  Nummer:        %2i                        |\n", pCards_Player->Number);
            printf("|                  ?     ?                  |              |                                           |\n");
            printf("|                         ?                 |              |                                           |\n");
            printf("|                         ?                 |              |  kmh:            %6i                   |\n", pCards_Player->kmh);
            printf("|                         ?                 |              |  Gipfelh\x94he:  %9i                   |\n", pCards_Player->Gipfelhoehe);
            printf("|                     ?????                 |              |  PS:           %8.1lf                   |\n", pCards_Player->Ps);
            printf("|                     ?                     |              |                                           |\n");
            printf("|                     ?                     |              |                                           |\n");
            printf("|                     ?                     |              |                                           |\n");
            printf("|                                           |              |                                           |\n");
            printf("|                     ?                     |              |                                           |\n");
            printf("|                                           |              |                                           |\n");
            printf("|___________________________________________|              |___________________________________________|\n\n");

            printf(" ___________________________________________\n");
            printf("|                                           |\n");
            printf("|     Wert w\x84\hlen:                          |\n");
            printf("|                                           |\n");
            printf("|     Km/h          (1)                     |\n");
            printf("|     Gipfelh\x94he    (2)                     |\n");
            printf("|     PS            (3)                     |\n");
            printf("|___________________________________________|\n");
            printf("|                                           |\n");
            printf("|     Verfgbare Karten:                     |\n");
            printf("|                                           |\n");
            printf("|     Eigene Karten: %i                      |\n", QuantityofPlayers);        //Gemessen mit der Anzahl der Karten(Durch Func_counting_list)
            printf("|     Gegner Karten: %i                      |\n", QuantityofComputer);
            printf("|___________________________________________|\n");
            printf("|                                           |\n");
            printf("|    Funktion w\x84\hlen:                       |\n");
            printf("|                                           |\n");
            printf("|    Neustart      (4)                      |\n");
            printf("|    Menu          (5)                      |\n");
            printf("|    Beenden       (6)                      |\n");
            printf("|___________________________________________|\n\n");






            X = _getch();


            if (X == '1') {                                                                                //Der Spieler wählt 1, 2, 3 für die Verschiedenen Werten                    
                Card_Mod = Func_Cards_Comparing(1, pCards_Player, pCards_Computer);                        //Es wird verglichen mit der Funktion func_Cards_Comparing
                NextCard = true;                                                                           //NextCard (bool) wird true, 
            }
            else if (X == '2') {
                Card_Mod = Func_Cards_Comparing(2, pCards_Player, pCards_Computer);
                NextCard = true;
            }

            else if (X == '3') {
                Card_Mod = Func_Cards_Comparing(3, pCards_Player, pCards_Computer);
                NextCard = true;
            }
            else if (X == '4') {

                Func_Starting_Quartet();
            }
            else if (X == '5') {
                Func_Main_Menu();
            }
            else if (X == '6') {
                exit(1);
            }




        }



        if (Card_Mod == 1)                                                                               // 1 = Won
        {

            pCards_Player = func_cardwon(pCards_Player, pCards_Computer);
            pCards_Computer = func_cardlost(pCards_Computer);
            Func_GameWon();                                                                                           //Ausgabe (Karte gewonnen)
            func_CardComputer(pCards_Computer, pCards_Player, QuantityofPlayers);

        }
        else if (Card_Mod == 2)                                                                         //2 = Lost
        {
            pCards_Computer = func_cardwon(pCards_Computer, pCards_Player);
            pCards_Player = func_cardlost(pCards_Player);
            Func_GameLost();                                                                            //Ausgabe (Karte verloren)
        }





        while (QuantityofPlayers == 0 && QuantityofComputer == 10 && !BackinMenu)                     //while Schleife für das Verlieren des Spielers
        {
            system("cls");

            printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
            printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
            printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
            printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
            printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
            printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");



            printf("\t\t\t\t\t\t _____   \n");
            Sleep(200);
            printf("\t\t\t\t\t\t|____ |   \n");
            Sleep(200);
            printf("\t\t\t\t\t\t    / /   \n");
            Sleep(200);
            printf("\t\t\t\t\t\t    \x5c \x5c \n");
            Sleep(200);
            printf("\t\t\t\t\t\t.___/ / \n");
            Sleep(200);
            printf("\t\t\t\t\t\t\x5c____/ \n");
            Sleep(200);
            system("cls");

            printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
            printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
            printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
            printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
            printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
            printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");

            printf("\t\t\t\t\t\t _____  \n");
            Sleep(200);
            printf("\t\t\t\t\t\t/ __  \x5c \n");
            Sleep(200);
            printf("\t\t\t\t\t\t`' / /' \n");
            Sleep(200);
            printf("\t\t\t\t\t\t  / /   \n");
            Sleep(200);
            printf("\t\t\t\t\t\t./ /___ \n");
            Sleep(200);
            printf("\t\t\t\t\t\t\x5c_____/ \n");
            Sleep(200);
            system("cls");

            printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
            printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
            printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
            printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
            printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
            printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");

            printf("\t\t\t\t\t\t __   \n");
            Sleep(200);
            printf("\t\t\t\t\t\t/  |  \n");
            Sleep(200);
            printf("\t\t\t\t\t\t`| |  \n");
            Sleep(200);
            printf("\t\t\t\t\t\t | |  \n");
            Sleep(200);
            printf("\t\t\t\t\t\t_| |_ \n");
            Sleep(200);
            printf("\t\t\t\t\t\t\x5c___/ \n");
            Sleep(200);
            system("cls");

            printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
            printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
            printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
            printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
            printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
            printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");


            printf("\t\t*******************************************************************\n");
            printf("\t\t*                                                                 *\n");
            printf("\t\t*     _____  _____ ___  _________  _   _  _____  _____ ______     *       \n");
            printf("\t\t*    /  __ \x5c|  _  ||  \x5c/  || ___ \x5c| | | ||_   _||  ___|| ___ \x5c    *\n");
            printf("\t\t*    | /  \x5c/| | | || .  . || |_/ /| | | |  | |  | |__  | |_/ /    *   \n");
            printf("\t\t*    | |    | | | || |\x5c/| ||  __/ | | | |  | |  |  __| |    /     *\n");
            printf("\t\t*    | \x5c__/\x5c\x5c \x5c_/ /| |  | || |    | |_| |  | |  | |___ | |\x5c \x5c     *\n");
            printf("\t\t*     \x5c____/ \x5c___/ \x5c_|  |_/\x5c_|     \x5c___/   \x5c_/  \x5c____/ \x5c_| \x5c_|    *\n");
            printf("\t\t*                                                                 *\n");
            printf("\t\t*                                                                 *\n");
            printf("\t\t*******************************************************************\n\n");


            printf("\n Dr\x81\cken sie die (1) um zur\x81\ck ins Menu zu kehren, (2) f\x81r beenden\n");
            k = _getch();

            if (k == '1')
            {
                BackinMenu = true;
                while (BackinMenu = true) { system("cls"); Func_Main_Menu(); }


            }
            else if (k == '2') { exit; }
            else exit;
            system("cls");
        }



    }

    return 0;
}

int Func_Starting_Quartet() {
    system("cls");
    //Geschrieben von *Rakul*
    //Keine Parameter
    //Keinen Returnwert (return 0;)


    struCards* pStart = NULL;
    struCards* pCards_Player = NULL;                       //Erstellung der Liste von Player
    struCards* pCards_Computer = NULL;                     //Erstellung der Liste von Computer

    // Einfüllen der Startliste mit Karten
    pStart = Func_CreatingList(pStart, Func_Card(1, "Messerschmitt Bf 109 G-1", 650, 12200, 1475));         //Abfüllung der Parameter (mehr Erklärung bei Func_Card (unten))
    pStart = Func_CreatingList(pStart, Func_Card(2, "Spitfire Mk.XIV", 714, 13570, 2050));
    pStart = Func_CreatingList(pStart, Func_Card(3, "J-16 (Rata)", 525, 9000, 1000));
    pStart = Func_CreatingList(pStart, Func_Card(4, "P-51 D Mustang", 699, 12800, 1695));
    pStart = Func_CreatingList(pStart, Func_Card(5, "Messerschmitt Me 210 A-1", 560, 8900, 2700));
    pStart = Func_CreatingList(pStart, Func_Card(6, "Westland Welkin Mk.I", 619, 13420, 2500));
    pStart = Func_CreatingList(pStart, Func_Card(7, "P-38 L-5 Lightning", 667, 13200, 2950));
    pStart = Func_CreatingList(pStart, Func_Card(8, "Grumman F7F-3 Tigercat", 696, 12400, 4200));
    pStart = Func_CreatingList(pStart, Func_Card(9, "Bristol Beaufighter Mk.X", 533, 8080, 3340));
    pStart = Func_CreatingList(pStart, Func_Card(10, "P-61 Black Widow", 585, 10060, 4500));



    double RoundCount;

    for (RoundCount = 1; RoundCount <= 5; RoundCount++)                             //Forschleife für Spieler (1-5)
    {
        int Quantity = Func_Counting_List(pStart);                                  // Es werden alle Elemente der Liste pStart gezählt.

        srand(time(NULL));
        int Random = rand() % Quantity;                                             //Random variable wird wird begrenzt durch die Anzahl Karten des Spielers

        struCards* pRandCard = pStart;                                               //pRandCard = Zufällige Karte aus der Liste

        for (int X = 1; X <= Random; X++)
        {
            pRandCard = pRandCard->pNext;
        }

        pStart = Func_removingList(pStart, pRandCard);
        pCards_Player = Func_CreatingList(pCards_Player, pRandCard);
    }

    for (RoundCount = 5; RoundCount < 10; RoundCount++)        //Forschleife für Computer (6-10)
    {
        int Quantity = Func_Counting_List(pStart);             //Es werden alle Elemente der Liste pStart gezählt (Func_Counting_List)
        srand(time(NULL));
        int Random = rand() % Quantity;                         //Random variable wird wird begrenzt durch die Anzahl Karten des Computers

        struCards* pRandCard = pStart;                         //pRandCard = Zufällige Karte aus der Liste

        for (int X = 1; X <= Random; X++)
        {
            pRandCard = pRandCard->pNext;
        }




        pStart = Func_removingList(pStart, pRandCard);
        pCards_Computer = Func_CreatingList(pCards_Computer, pRandCard);
    }


    Func_system_Output(pCards_Player, pCards_Computer);
    return 0;
}

struCards* func_cardwon(struCards* pListWon, struCards* pListLost) {
    //Geschrieben von *Rakul*
    //Parameter pListWon, pListlost
    //Zeigt wer gewonnen hat Computer oder Spieler 
    //Wird jedes mal ausgeführt jedes mal 1 Verlierer und 1 Gewinner nach jedem Vergleich
    //Retourniert wird pListwon

    struCards* pLast;
    struCards* pTmp;

    if (Func_Counting_List(pListWon) == 1)
    {
        pLast = pListWon;
        struCards* pCard = pListLost;
        pLast->pNext = pCard;
    }

    else if (Func_Counting_List(pListWon) > 1)
    {
        pTmp = pListWon;
        pListWon = pListWon->pNext;
        pTmp->pNext = NULL;
        pLast = pListWon;

        while (pLast->pNext != NULL)
        {
            pLast = pLast->pNext;
        }
        pLast->pNext = pTmp;

        struCards* pCard = pListLost;
        pTmp->pNext = pCard;
    }

    return pListWon;
}

int Func_Counting_List(struCards* pListe)                    //In dieser Funktion werden alle Karten gezählt und zurückgegeben
{
    //Geschrieben von *Rakul*
    //Parameter pListe
    //Stapel wird gezählt
    //Wichtig für die Anzeige von Karten (Computer und Spieler) (QuantityPlayer u QuantityComputer)
    //Ebenfalls Wichtig für die Auslösung des Endgewinners (Spieler oder Computer hat: 10 Karten)
    //Retourniert Quantity (Anzahl Karten)
    int Quantity = 0;
    struCards* pTmp = pListe;
    for (pTmp; pTmp != NULL; pTmp = pTmp->pNext)
    {
        Quantity++;
    }
    return Quantity;
}

struCards* func_cardlost(struCards* pListLost) {         //Diese Funktion ist für den Verlierer der Karte zuständig (Lost)

    //Geschrieben von *Ben*
    //Parameter pListLost
    //Zeigt wer gewonnen hat Computer oder Spieler 
    //Wird jedes mal ausgeführt jedes mal 1 Verlierer und 1 Gewinner nach jedem Vergleich
    //Retourniert pListlost 

    struCards* pTmp = pListLost;

    if (Func_Counting_List(pListLost) == 1) {
        pListLost = NULL;
    }

    else if (Func_Counting_List(pListLost) > 1) {
        pListLost = pListLost->pNext;
        pTmp->pNext = NULL;
    }



    return pListLost;
}

int Func_Cards_Comparing(int Type, struCards* pCards_Player, struCards* pCards_Computer) //Diese Funktion ist zuständig für die Vergleichung von Karten
{
    //Geschrieben von *Ben*
    //Parameter: int Type, struCards* pCards_Player, struCards* pCards_Computer
    //Parameter werden aufgerufen in Func_system_Output
    //Für den Vergleich zwischen pCard vom Spieler und pCard vom Computer
    //Retourniert wird 1,2,3 für die 3 verscheidenen Werte

    //Type (Eingegeben des Benutzers (Wert des Flugzeugs (z.b. kmh)))

    int Cards_Mod = 0; //0 = Nichts (Default), 1 = Won, 2 = Lost

    if (Type == 1) {
        if (pCards_Player->kmh > pCards_Computer->kmh)
        {
            Cards_Mod = 1;  //Won (pCards_Player (kmh) > pCards_Computer (kmh))
        }
        else if (pCards_Player->kmh < pCards_Computer->kmh)
        {
            Cards_Mod = 2; //Lost (pCards_Player (kmh) < pCards_Computer (kmh))
        }

    }
    else if (Type == 2) {
        if (pCards_Player->Gipfelhoehe > pCards_Computer->Gipfelhoehe)
        {
            Cards_Mod = 1;     //Won (pCards_Player (Gipfelhoehe) > pCards_Computer (Gipfelhoehe)) 
        }
        else if (pCards_Player->Gipfelhoehe < pCards_Computer->Gipfelhoehe)
        {
            Cards_Mod = 2;     //Lost (pCards_Player (Gifpelhoehe) < pCards_Computer (Gifpelhoehe))
        }

    }
    else if (Type == 3) {
        if (pCards_Player->Ps > pCards_Computer->Ps)
        {
            Cards_Mod = 1;  //Won (pCards_Player (Ps) > pCards_Computer (Ps)) 
        }
        else if (pCards_Player->Ps < pCards_Computer->Ps)
        {
            Cards_Mod = 2; //Lost (pCards_Player (Ps) < pCards_Computer (Ps))
        }

    }
    return Cards_Mod;   //Gibt 1, 2, 3 zurück für den Vergleich der Karten (Wer gewonnen hat oder Unentschieden)
}

struCards* Func_CreatingList(struCards* pList, struCards* pCard)                  //Diese Funktion ist zuständig für das Erstellen von Listen (Create)

{       //Geschrieben von *Rakul*
        //Parameter pList, pCard (gleich wie func_removingList)
        //Zusammen mit Func_Card wird mit Func_CreatingList die Karten des Quartettes erstellt 
        //Wobei der Parameter pCard als Funktion verwendet wird (func_Card)
        //Retourniert wird plist
    if (pList == NULL) {

        pList = pCard;
        pCard->pNext = NULL;
    }
    else {
        struCards* pLast = pList;
        while (pLast->pNext != NULL)                                              //While-Schleife ist zuständig für die Suche nach der Letzten Karte (pLast)
            pLast = pLast->pNext;

        pLast->pNext = pCard;

    }
    return pList;                                                                 //Ganze Liste Wird zurückgegeben
}

struCards* Func_removingList(struCards* pList, struCards* pCard)    //Diese Funktion ist zuständig für das Löschen der Karte(eigenen oder des des Gegners)
                                                                    //Kommt auf das Resultat von Func_Cards_Comparing drauf an (1 = Won, 2 = Lost(REMOVING))
{
    //Geschrieben von *Rakul*
    //Parameter pList, pCard 
    //Funktion wird verwendet in der Funktion func_Starting_Quartett
    //Für das Löschen von Karten entweder des Computers oder des Spielers
    //Retourniert wird der Parameter pList

    if (pList == pCard) {
        pList = pList->pNext;
        pCard->pNext = NULL;
    }
    else {
        struCards* pTmp = pList;
        while (pTmp->pNext != pCard) pTmp = pTmp->pNext;
        pTmp->pNext = pCard->pNext;
        pCard->pNext = NULL;
    }
    return pList;

}

struCards* Func_Card(double plane, const char* pDesignation, int kmh, int summit_height, double Ps)              //Hier werden die Werte in der Struktur (typedef struct Cards) in die Karte gefüllt
{
    //Geschrieben von *Ben*
    //Parameter: double plane, const char* pDesignation, int kmh, int summit_height, double ps
    //Die Parameter werden übergeben an in der Funktion func_Starting_Quartett für die Erstellung der Karten
    //Die Werte der Parameter werden dort abgefüllt
    //Retourniert wird der Pointer der Struktur der auf die Werte zeigt

    struCards* pTmp = (struCards*)malloc(sizeof(struCards));                                                     //Hier wird Speicherplatz reserviert für pTmp mit malloc           

    pTmp->Number = plane;                           //Abfüllung von Werten in die Karten (Number in Struktur = parameter)

    strcpy_s(pTmp->Flugzeuge, pDesignation);        //String abfüllung mit Parameter
    pTmp->kmh = kmh;                                //Kmh abfüllung mit Parameter
    pTmp->Gipfelhoehe = summit_height;              //Gipfelhöhe Abfüllung mit Parameter
    pTmp->Ps = Ps;                                  //Ps Abfüllung mit Parameter
    pTmp->pNext = NULL;                             //pNext = NULL

    return pTmp;



}

void Func_GameWon() {
    //Geschrieben von *Ben und Rakul*
    //Keine Parameter
    //Kein Returnwert, ausser Grafische Darstellung 
    system("cls");
    printf("Karten werden verglichen.\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen..\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen...\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen.\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen..\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen...\n");
    Sleep(150);
    system("cls");

    printf("\t\t\t __  __ ____   __  __   _       __ ____   _   __\n");
    printf("\t\t\t \x5c \x5c/ // __ \x5c / / / /  | |     / // __ \x5c / | / / \n");
    printf("\t\t\t  \x5c  // / / // / / /   | | /| / // / / //  |/ / \n");
    printf("\t\t\t  / // /_/ // /_/ /    | |/ |/ // /_/ // /|  /     \n");
    printf("\t\t\t /_/ \x5c____/ \x5c____/     |__/|__/ \x5c____//_/ |_/   \n");
    Sleep(1000);
}

void Func_GameLost() {
    //Geschrieben von *Ben und Rakul*
    //Keine Parameter
    //Kein Returnwert, ausser Grafische Darstellung
    system("cls");
    printf("Karten werden verglichen.\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen..\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen...\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen.\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen..\n");
    Sleep(150);
    system("cls");
    printf("Karten werden verglichen...\n");
    Sleep(150);
    system("cls");

    printf("\t\t\t __  __ ____   __  __   __    ____  _____ ______ \n");
    printf("\t\t\t \x5c \x5c/ // __ \x5c / / / /  / /   / __ \x5c/ ___//_  __/ \n");
    printf("\t\t\t  \x5c  // / / // / / /  / /   / / / /\x5c__ \x5c  / /   \n");
    printf("\t\t\t  / // /_/ // /_/ /  / /___/ /_/ /___/ / / /    \n");
    printf("\t\t\t /_/ \x5c____/ \x5c____/  /_____/\x5c____//____/ /_/     \n");
    Sleep(600);
}

void Func_Main_Menu() {
    //Geschrieben von *Ben und Rakul*
    //Keine Parameter
    //Kein Returnwert, ausser Grafische Darstellung


    bool back = false;
    char back1;
    char starten;

    system("mode con cols=120 lines=170");
    system("cls");
    printf("\t ______ _                                   ___     __          __  _ _   _         _           \n");
    printf("\t|  ____| |                                 |__ \x5C    \x5C \x5C        / / | | | | |       (_)            \n");
    printf("\t| |__  | |_   _  __ _ _______ _   _  __ _     ) |    \x5C \x5C  /\x5C  / /__| | |_| | ___ __ _  ___  __ _ \n");
    printf("\t|  __| | | | | |/ _` |_  / _ \x5C | | |/ _` |   / /      \x5C \x5C/  \x5C/ / _ \x5C | __| |/ / '__| |/ _ \x5C/ _` |\n");
    printf("\t| |    | | |_| | (_| |/ /  __/ |_| | (_| |  / /_ _     \x5C  /\x5C  /  __/ | |_|   <| |  | |  __/ (_| |\n");
    printf("\t|_|    |_|\x5C__,_|\x5C__, /___\x5C___|\x5C__,_|\x5C__, | |____(_)     \x5C/  \x5C/ \x5C___|_|\x5C__|_|\x5C_\x5C_|  |_|\x5C___|\x5C__, |\n");
    printf("\t                 __/ |               __/ |                                                  __/ |\n");
    printf("\t                |___/               |___/                                                  |___/ \n\n\n");



    printf("\t\t\t\t ________________________________________ \n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|           Spielen      (1)             |\n");
    printf("\t\t\t\t|           Spielregeln  (2)             |\n");
    printf("\t\t\t\t|           Beenden      (3)             |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|                                        |\n");
    printf("\t\t\t\t|________________________________________|\n");
    starten = _getch();
    system("cls");




    if (starten == '1') {
        Func_Starting_Quartet();
    }

    else if (starten == '2') {

        printf("\t\t\t\t __________________________________________ \n");
        Sleep(150);
        printf("\t\t\t\t|                                          |\n");
        Sleep(150);
        printf("\t\t\t\t| 1. Quartett wird meist zu zweit gespielt.|\n");
        Sleep(150);
        printf("\t\t\t\t|                                          |\n");
        Sleep(150);
        printf("\t\t\t\t| 2. Im Spiel gilt es, möglichst viele     |\n");
        Sleep(150);
        printf("\t\t\t\t|    Quartette zu sammeln. Wer am Ende     |\n");
        Sleep(150);
        printf("\t\t\t\t|    die meisten Quartette vorleht, hat    |\n");
        Sleep(150);
        printf("\t\t\t\t|    gewonnen                              |\n");
        Sleep(150);
        printf("\t\t\t\t|                                          |\n");
        Sleep(150);
        printf("\t\t\t\t| 3. Das Spiel endet, wenn ein Spieler     |\n");
        Sleep(150);
        printf("\t\t\t\t|    keine Karten mehr hat.                |\n");
        Sleep(150);
        printf("\t\t\t\t|                                          |\n");
        Sleep(150);
        printf("\t\t\t\t| 4. Wer die meisten Karten gesammelt      |\n");
        Sleep(150);
        printf("\t\t\t\t|    hat, hat gewonnen                     |\n");
        Sleep(150);
        printf("\t\t\t\t|_________________________________________ |\n");

        printf("Wollen sie zur\x81\ck (1) oder beenden (2)\n");
        back1 = _getch();

        if (back1 == '1')
        {
            back = true;
            while (back = true) { system("cls"); Func_Main_Menu(); }


        }
        else if (back1 == '2') { exit(1); }
        system("cls");
    }

    else if (starten == '3') exit(1);
    else exit(1);





}

void func_CardComputer(struCards* pCards_Computer, struCards* pCards_Player, int Quantity) {
    //Geschrieben von *Ben und Rakul*
    //Parameter pCards_Computer, pCards_Player, Quantity
    //Diese Parameter werden übergeben um die Karten des Computers darzustellen die der Spieler gewonnen hat
    //Keinen Returnwert, ausser Grafische Darstellung

    char X;
    char k;
    bool BackinMenu = false;
    if (Quantity < 9) {


        printf("\t\t\t __________________________________________\n");
        printf("\t\t\t|                                          |\n");
        printf("\t\t\t|                                          |\n");
        printf("\t\t\t|                  Computer                |\n");
        printf("\t\t\t|                                          |\n");
        printf("\t\t\t|                    ?????                 |\n");
        printf("\t\t\t|                   ?     ?                |\n");
        printf("\t\t\t|                          ?               |\n");
        printf("\t\t\t|                          ?               |\n");
        printf("\t\t\t|                      ?????               |\n");
        printf("\t\t\t|                      ?                   |\n");
        printf("\t\t\t|                      ?                   |\n");
        printf("\t\t\t|                      ?                   |\n");
        printf("\t\t\t|                                          |\n");
        printf("\t\t\t|                      ?                   |\n");
        printf("\t\t\t|                                          |\n");
        printf("\t\t\t|                                          |\n");
        printf("\t\t\t|__________________________________________|\n\n");
        Sleep(1000);
        printf("\t\t\tSie haben diese Karte gewonnen vom Computer\n\n");
        printf("\t\t\t                       |\n");
        printf("\t\t\t                       |\n");
        printf("\t\t\t                       |\n");
        printf("\t\t\t                       |\n");
        printf("\t\t\t                       V\n");
        printf("\n");


        printf("\t\t\t ___________________________________________\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|  Computers Karte                          |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|  Bezeichnung:    % -25s| \n", pCards_Computer->Flugzeuge);
        Sleep(50);
        printf("\t\t\t|  Nummer:        %2i                        |\n", pCards_Computer->Number);
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|  kmh:            %6i                   |\n", pCards_Computer->kmh);
        Sleep(50);
        printf("\t\t\t|  Gipfelh\x94he:  %9i                   |\n", pCards_Computer->Gipfelhoehe);
        Sleep(50);
        printf("\t\t\t|  PS:           %8.1lf                   |\n", pCards_Computer->Ps);
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|                                           |\n");
        Sleep(50);
        printf("\t\t\t|___________________________________________|\n\n");
        Sleep(50);



        printf("\t\t\t Dr\x81\cken sie irgendeine taste...");

        X = _getch();
        system("cls");
    }

    else if (Quantity == 10)
    {
        system("cls");

        printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
        printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
        printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
        printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
        printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
        printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");



        printf("\t\t\t\t\t\t _____   \n");
        Sleep(200);
        printf("\t\t\t\t\t\t|____ |   \n");
        Sleep(200);
        printf("\t\t\t\t\t\t    / /   \n");
        Sleep(200);
        printf("\t\t\t\t\t\t    \x5c \x5c \n");
        Sleep(200);
        printf("\t\t\t\t\t\t.___/ / \n");
        Sleep(200);
        printf("\t\t\t\t\t\t\x5c____/ \n");
        Sleep(200);
        system("cls");

        printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
        printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
        printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
        printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
        printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
        printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");

        printf("\t\t\t\t\t\t _____  \n");
        Sleep(200);
        printf("\t\t\t\t\t\t/ __  \x5c \n");
        Sleep(200);
        printf("\t\t\t\t\t\t`' / /' \n");
        Sleep(200);
        printf("\t\t\t\t\t\t  / /   \n");
        Sleep(200);
        printf("\t\t\t\t\t\t./ /___ \n");
        Sleep(200);
        printf("\t\t\t\t\t\t\x5c_____/ \n");
        Sleep(200);
        system("cls");

        printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
        printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
        printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
        printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
        printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
        printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");

        printf("\t\t\t\t\t\t __   \n");
        Sleep(200);
        printf("\t\t\t\t\t\t/  |  \n");
        Sleep(200);
        printf("\t\t\t\t\t\t`| |  \n");
        Sleep(200);
        printf("\t\t\t\t\t\t | |  \n");
        Sleep(200);
        printf("\t\t\t\t\t\t_| |_ \n");
        Sleep(200);
        printf("\t\t\t\t\t\t\x5c___/ \n");
        Sleep(200);
        system("cls");

        printf("\t\t\t _    _  _   _  _____   _    _  _____  _   _  ___       \n");
        printf("\t\t\t| |  | || | | ||  _  | | |  | ||  _  || \x5c | ||__ \x5c      \n");
        printf("\t\t\t| |  | || |_| || | | | | |  | || | | ||  \x5c| |   ) |     \n");
        printf("\t\t\t| |/\x5c| ||  _  || | | | | |/\x5c| || | | || . ` |  / /      \n");
        printf("\t\t\t\x5c  /\x5c  /| | | |\x5c \x5c_/ / \x5c  /\x5c  /\x5c \x5c_/ /| |\x5c  | |_|       \n");
        printf("\t\t\t \x5c/  \x5c/ \x5c_| |_/ \x5c___/   \x5c/  \x5c/  \x5c___/ \x5c_| \x5c_/ (_)      \n\n");

        printf("\t\t*******************************************************************\n");
        printf("\t\t*                                                                 *\n");
        printf("\t\t*                                                                 *\n");
        printf("\t\t*                  __   __ _____  _   _                           *\n");
        printf("\t\t*                  \x5c \x5c / /|  _  || | | |                          *\n");
        printf("\t\t*                   \x5c V / | | | || | | |                          *\n");
        printf("\t\t*                    \x5c /  | | | || | | |                          *\n");
        printf("\t\t*                    | |  \x5c \x5c_/ /| |_| |                          *\n");
        printf("\t\t*                    \x5c_/   \x5c___/  \x5c___/                           *\n");
        printf("\t\t*                                                                 *\n");
        printf("\t\t*                                                                 *\n");
        printf("\t\t*******************************************************************\n\n");

        printf("Dr\x81\cken sie die (1) um ins Menu zur\x81\ckzukehren, (2) f\x81r beenden\n ");
        k = _getch();

        if (k == '1')
        {
            BackinMenu = true;
            while (BackinMenu = true) { system("cls"); Func_Main_Menu(); }

        }
        else if (k == '2') { exit; }
        else exit;
        system("cls");
    }




}

