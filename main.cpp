#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Osoba {
    int id;
    int AktualnieZalogowaneId;
    string imie, nazwisko, numerTelefonu, email, adres;
};

struct Uzytkownik {
    int IdZalogowanegoUzytkownika;
    string login, haslo;
};

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        } else {
            cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
        }
    }
    return znak;
}

string ZamianaIntNaString(int liczba) {

    ostringstream ss;
    ss << liczba;
    string wyraz = ss.str();
    return wyraz;
}

void zapisNowegoUzytkownika(vector<Uzytkownik> &BazaDanych) {
    string login, haslo;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik Dane;

    cout << "Podaj login " << endl;
    cin >> Dane.login;
    cout << "Podaj haslo " << endl;
    cin >> Dane.haslo;

    if (BazaDanych.empty() == true) {
        Dane.IdZalogowanegoUzytkownika = 1;
    } else {
        Dane.IdZalogowanegoUzytkownika = BazaDanych.back().IdZalogowanegoUzytkownika + 1;
    }

    BazaDanych.push_back(Dane);

    fstream plik;

    plik.open("BazaUzytkownikow.txt", ios::out);

    if(plik.good() == true) {
        for(vector<Uzytkownik>::iterator itr=BazaDanych.begin(); itr!=BazaDanych.end(); itr++) {
            liniaZDanymiUzytkownika += ZamianaIntNaString(itr->IdZalogowanegoUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr->login + '|';
            liniaZDanymiUzytkownika += itr->haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";

        }
        plik.close();
        cout << "Dane nowego uzytkownika zostaly zapisane " << endl;
    } else {
        cout << "Nie udalo sie otworzyc pliku! " << endl;
    }
}

void WczytajBazeUzytkownikow(vector<Uzytkownik> &BazaDanych) {
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int iloscZnajomych = 0;
    fstream plik;
    Uzytkownik Dane;

    BazaDanych.clear();
    plik.open("BazaUzytkownikow.txt",ios::in); // aby otworzyc plik do odczytu
    if (plik.good() == true) {

        while (getline(plik,linia)) {
            BazaDanych.push_back(Dane);
            iloscZnajomych++;
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++) {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|') {
                    iloscPionowychKresek++;
                    wyraz = linia.substr (poczatek,ileZnakowWyjac);
                    switch (iloscPionowychKresek) {
                    case 1:
                        BazaDanych[iloscZnajomych - 1].IdZalogowanegoUzytkownika = atoi(wyraz.c_str());
                        break;
                    case 2:
                        BazaDanych[iloscZnajomych - 1].login = wyraz;
                        break;
                    case 3:
                        BazaDanych[iloscZnajomych - 1].haslo = wyraz;
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }

            }
        }
        plik.close();
    }

}

int LogowanieUzytkownika(vector<Uzytkownik> &BazaDanych) {

    string login, haslo;
    int idZalogowanegoUzytkownika = 0;
    bool ZnalezionyUzytkownik = 0;
    int iloscProb = 3;




        cout << "Podaj login uzytkownika " << endl;

        cin >> login;

        for(vector<Uzytkownik>::iterator itr=BazaDanych.begin(); itr!=BazaDanych.end(); itr++) {
            if(itr->login == login) {
                ZnalezionyUzytkownik = 1;
                cout << "Podaj haslo uzytkownika " << endl;
                cin >> haslo;
                if(itr->haslo == haslo) {
                    cout << "Pomyslnie zalogowano uzytkownika " << endl;
                    cout << itr->login << endl;
                    cout << itr->haslo << endl;
                    cout << itr->IdZalogowanegoUzytkownika << endl;
                    idZalogowanegoUzytkownika = itr->IdZalogowanegoUzytkownika;
                    break;
                }else{
                    cout << "Haslo nieprawidlowe, trwa zamykanie programu " << endl;
                exit(0);
                }


                }
            }

    if(!ZnalezionyUzytkownik) {
        system("cls");
        for(int i=3; i>0; i--) {
            cout << "Nie znaleziono uzytkownika lub haslo nieprawidlowe " << endl;
            cout << "Program zostanie zamkniety za " << i << endl;
            Sleep(1000);
            system("cls");
        }
        exit(0);
    }




    return idZalogowanegoUzytkownika;

}

void zmianaHasloUzytkownika(vector<Uzytkownik> &BazaDanych, int AktualneId) {

    string NoweHaslo;

    cout << "Jestes w panelu zmiany haslo uzytkownika " << endl;
    cout << "Podaj aktualne haslo " << endl;


    for(vector<Uzytkownik>::iterator itr=BazaDanych.begin(); itr!=BazaDanych.end(); itr++) {
        if(AktualneId == itr->IdZalogowanegoUzytkownika) {
            cin >> NoweHaslo;
            itr->haslo = NoweHaslo;
            break;
        }
    }





}

void WyswietlWszystkichUzytkownik(vector<Uzytkownik> &BazaDanych) {

    for(vector<Uzytkownik>::iterator itr=BazaDanych.begin(); itr!=BazaDanych.end(); itr++) {
        cout << itr->IdZalogowanegoUzytkownika << endl;
        cout << itr->login << endl;
        cout << itr->haslo << endl;

        cout << endl;
        system("pause");
    }
}



void zapiszNowegoZnajomego(vector <Osoba> &adresaci, int ZalogowaneId) {
    string imie, nazwisko, adres, numerTelefonu, email;
    string liniaZDanymiZnajomego = "";
    Osoba kontakt;

    cout << "zalogowaneId to: " << ZalogowaneId << endl;

    cout << endl << "Zapisywanie nowego znajomego." << endl << endl;
    cout << "Podaj imie: ";
    cin >> kontakt.imie;
    cout << "Podaj nazwisko: ";
    cin >> kontakt.nazwisko;
    cout << "Podaj numer telefonu: ";
    cin >> kontakt.numerTelefonu;
    cout << "Podaj mail: ";
    cin >> kontakt.email;
    cout << "Podaj adres: ";
    cin >> kontakt.adres;


    if (adresaci.empty() == true) {
        kontakt.id = 1;
    } else {
        kontakt.id = adresaci.back().id + 1;
    }

    kontakt.AktualnieZalogowaneId = ZalogowaneId;


    cout << kontakt.AktualnieZalogowaneId << endl;
    system("pause");
    adresaci.push_back(kontakt);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out);

    if (plik.good() == true) {
        for (vector <Osoba>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            liniaZDanymiZnajomego += ZamianaIntNaString(itr -> id) + '|';
            liniaZDanymiZnajomego +=ZamianaIntNaString(itr->AktualnieZalogowaneId) + '|';
            liniaZDanymiZnajomego += itr -> imie + '|';
            liniaZDanymiZnajomego += itr -> nazwisko + '|';
            liniaZDanymiZnajomego += itr -> numerTelefonu + '|';
            liniaZDanymiZnajomego += itr -> email + '|';
            liniaZDanymiZnajomego += itr -> adres + '|';

            plik << liniaZDanymiZnajomego << endl;
            liniaZDanymiZnajomego = "";
        }
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");

    }
    plik.close();
}

void zapiszZnajomychUzytkownikaDoWektora (vector <Osoba> &adresaci, string linia, int iloscZnajomych) {
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    Osoba pusty;

    adresaci.push_back(pusty);

    ileZnakowWyjac = 0;
    poczatek = 0;
    iloscPionowychKresek = 0;

    for (int i = 0; i < linia.size(); i++) {
        ileZnakowWyjac = i - poczatek;
        if (linia[i] == '|') {
            iloscPionowychKresek++;
            wyraz = linia.substr (poczatek,ileZnakowWyjac);
            switch (iloscPionowychKresek) {
            case 1:
                adresaci[iloscZnajomych - 1].id = atoi(wyraz.c_str());
                break;
            case 2:
                adresaci[iloscZnajomych - 1].AktualnieZalogowaneId = atoi(wyraz.c_str());
                break;
            case 3:
                adresaci[iloscZnajomych - 1].imie = wyraz;
                break;
            case 4:
                adresaci[iloscZnajomych - 1].nazwisko = wyraz;
                break;
            case 5:
                adresaci[iloscZnajomych - 1].numerTelefonu = wyraz;
                break;
            case 6:
                adresaci[iloscZnajomych - 1].email = wyraz;
                break;
            case 7:
                adresaci[iloscZnajomych - 1].adres = wyraz;
                break;
            }
            poczatek = poczatek + ileZnakowWyjac + 1;
        }
    }
}


void UsuwanieWybrnajeLiniiZPliku(int AktualnieZalogowaneId) {
    vector<string> liniaDoUsuniecia;
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnajokWyjac = 0;
    int poczatek = 0;
    int idUzytkownikaZPliku = 0;
    bool znalezionaLinia;
    fstream staryPlik;
    ofstream NowyPlik;
    liniaDoUsuniecia.clear();
    staryPlik.open("KsiazkaAdresowa.txt", ios::in);
    if(staryPlik.good() == true) {
        while(getline(staryPlik,linia)) {
            ileZnajokWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;
            for(int i=0; i<linia.size(); i++) {
                ileZnajokWyjac = i - poczatek;
                if(linia[i] == '|') {
                    iloscPionowychKresek++;
                    wyraz = linia.substr(poczatek,ileZnajokWyjac);
                    idUzytkownikaZPliku = atoi(wyraz.c_str());
                    if(iloscPionowychKresek == 2 && AktualnieZalogowaneId == idUzytkownikaZPliku) {
                        liniaDoUsuniecia.push_back(linia);
                        break;
                    }
                    poczatek = poczatek + ileZnajokWyjac +1;
                }
            }
        }
        staryPlik.close();
    }
    NowyPlik.open("KontaktyTymczasowe.txt");
    staryPlik.open("KsiazkaAdresowa.txt", ios::in);
    while(getline(staryPlik, linia)) {
        znalezionaLinia = 0;
        for(int i=0; i<liniaDoUsuniecia.size(); i++) {
            if(linia == liniaDoUsuniecia[i]) {
                znalezionaLinia = 1;
            }
        }
        if(znalezionaLinia == 0) {
            NowyPlik << linia <<endl;
        }
    }
    NowyPlik.close();
    staryPlik.close();
    remove("KsiazkaAdresowa.txt");
    rename("KontaktyTymczasowe.txt", "KsiazkaAdresowa.txt");
}

void wczytajZnajomychZPliku(vector <Osoba> &adresaci, int idZalogowanegoUzytkownika) {

    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku = 0;
    int iloscZnajomych = 0;
    fstream plik;

    adresaci.clear();
    plik.open("KsiazkaAdresowa.txt",ios::in);
    if (plik.good() == true) {
        while (getline(plik,linia)) {
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++) {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|') {
                    iloscPionowychKresek++;
                    wyraz = linia.substr (poczatek, ileZnakowWyjac);
                    idUzytkownikaZPliku = atoi(wyraz.c_str());
                    //if ( iloscPionowychKresek == 2 && idZalogowanegoUzytkownika == idUzytkownikaZPliku) {
                    iloscZnajomych++;
                    zapiszZnajomychUzytkownikaDoWektora(adresaci, linia, iloscZnajomych);
                    break;
                    // }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }
}
void wczytajZanjomychZgodniezZalogowanymId(vector <Osoba> &adresaci, int idZalogowanegoUzytkownika) {

    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku = 0;
    int iloscZnajomych = 0;
    fstream plik;

    adresaci.clear();
    plik.open("KsiazkaAdresowa.txt",ios::in);
    if (plik.good() == true) {
        while (getline(plik,linia)) {
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++) {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|') {
                    iloscPionowychKresek++;
                    wyraz = linia.substr (poczatek, ileZnakowWyjac);
                    idUzytkownikaZPliku = atoi(wyraz.c_str());
                    if(iloscPionowychKresek == 2 && idZalogowanegoUzytkownika == idUzytkownikaZPliku) {
                        iloscZnajomych++;
                        zapiszZnajomychUzytkownikaDoWektora(adresaci, linia, iloscZnajomych);
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }
}


void WyszukajPoNazwisku(vector<Osoba> &adresaci) {

    string PoszukiwaneNazwisko;
    cout << "Podaj nazwisko ktore chcesz wyszukac " << endl;
    cin >> PoszukiwaneNazwisko;

    for(vector<Osoba>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++) {
        if(PoszukiwaneNazwisko == itr->nazwisko) {
            cout << itr->id << endl;
            cout << itr->imie << endl;
            cout << itr->nazwisko << endl;
            cout << itr->numerTelefonu << endl;
            cout << itr-> email << endl;
            cout << itr->adres << endl;
            cout << endl;
            system("pause");

        }

    }
}

void WyszukajPoImieniu(vector<Osoba> &adresaci) {
    string PoszukiwaneImie;
    cout << "Podaj nazwisko ktore chcesz wyszukac " << endl;
    cin >> PoszukiwaneImie;

    for(vector<Osoba>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++) {
        if(PoszukiwaneImie == itr->imie) {
            cout << itr->id << endl;
            cout << itr->imie << endl;
            cout << itr->nazwisko << endl;
            cout << itr->numerTelefonu << endl;
            cout << itr-> email << endl;
            cout << itr->adres << endl;
            cout << endl;
            system("pause");
        }
    }
}

void WyswietlWszystkieOsoby(vector<Osoba> &adresaci) {

    for(vector<Osoba>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++) {
        cout << itr->id << endl;
        cout << itr->AktualnieZalogowaneId << endl;
        cout << itr->imie << endl;
        cout << itr->nazwisko << endl;
        cout << itr->numerTelefonu << endl;
        cout << itr-> email << endl;
        cout << itr->adres << endl;
        cout << endl;
        system("pause");
    }
}



void UsunUzytkownika(vector<Osoba> &adresaci) {

    int idUzytkownikaKtoregoChcemyUsunac;
    char znakDoOdczytu;

    cout << "Podaj id uzytkownika ktorego chcesz usunac z ksiazki adresowej" << endl;
    cout << endl;
    cin >> idUzytkownikaKtoregoChcemyUsunac;
    system("cls");

    for(vector<Osoba>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++) {
        if(idUzytkownikaKtoregoChcemyUsunac == itr->id) {
            cout << "Jesli chcesz usunac kontakt nacisnij t" << endl;
            cin >> znakDoOdczytu;
            if(znakDoOdczytu == 't') {
                itr = adresaci.erase(itr);
                cout << "Kontakt zostal usuniety" << endl;
                system("pause");
                break;
            }
        }
    }
}

void EdytujIstniejacyKontakt(vector<Osoba> &adresaci) {

    char ZnakSpecjalny;
    int idKontaktuDoEdycji;
    string noweImie, noweNazwisko, NowyNumerTelefonu, NowyEmail, NowyAdresZamieszkania;



    cout << "Podaj id ktore chcesz edytowac! " << endl;
    cin >> idKontaktuDoEdycji;
    for(vector<Osoba>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++) {

        if(idKontaktuDoEdycji == itr->id) {
            cout << "Wybierz sposob edycji " << endl;
            cout << "1. Edytuj imie " << endl;
            cout << "2. Edytuj nazwisko " << endl;
            cout << "3. Edytuj numer telefonu " << endl;
            cout << "4. Edytuj email " << endl;
            cout << "5. Edytuj adres zamieszkania " << endl;
            cout << "6. Wroc do menu glownego " << endl;
            cin >> ZnakSpecjalny;
            system("cls");

            cout << "Probujesz zmodyfikowac kontakt ponizej " << endl;
            cout << itr->id << endl;
            cout << itr->imie << endl;
            cout << itr->nazwisko << endl;
            cout << itr->numerTelefonu << endl;
            cout << itr-> email << endl;
            cout << itr->adres << endl;
            cout << endl;
            system("pause");

            switch(ZnakSpecjalny) {
            case '1':
                cout << "Podaj nowe imie " << endl;
                cin >> noweImie;
                itr->imie = noweImie;
                break;
            case '2':
                cout << "Podaj nowe nazwisko " << endl;
                cin >> noweNazwisko;
                itr->nazwisko = noweNazwisko;
                break;
            case '3':
                cout << "Podaj nowy numer telefonu " << endl;
                cin >> NowyNumerTelefonu;
                itr->numerTelefonu = NowyNumerTelefonu;
                break;
            case '4':
                cout << "Podaj nowy adres email " << endl;
                cin >> NowyEmail;
                itr->email = NowyEmail;
                break;
            case '5':
                cout << "Podaj nowy adres zamieszkania " << endl;
                cin >> NowyAdresZamieszkania;
                itr->adres = NowyAdresZamieszkania;
                break;
            case '6':
                system("cls");
                exit(0);
                break;
            }

            cout << "Oto zmodyfikowany kontakt: " << endl;
            cout << itr->id << endl;
            cout << itr->imie << endl;
            cout << itr->nazwisko << endl;
            cout << itr->numerTelefonu << endl;
            cout << itr-> email << endl;
            cout << itr->adres << endl;
            system("pause");
            system("cls");

        }
    }
}




void ZapisZmianyWKsiazceAdresowej(vector<Osoba> &adresaci, int AktualnieZalogowaneID) {
    fstream plik;

    string liniaZDanymiZnajomego = "";
    UsuwanieWybrnajeLiniiZPliku(AktualnieZalogowaneID);

    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good() == true) {
        for (vector <Osoba>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            liniaZDanymiZnajomego += ZamianaIntNaString(itr -> id) + '|';
            liniaZDanymiZnajomego += ZamianaIntNaString(itr->AktualnieZalogowaneId) + '|';
            liniaZDanymiZnajomego += itr -> imie + '|';
            liniaZDanymiZnajomego += itr -> nazwisko + '|';
            liniaZDanymiZnajomego += itr -> numerTelefonu + '|';
            liniaZDanymiZnajomego += itr -> email + '|';
            liniaZDanymiZnajomego += itr -> adres + '|';
            plik << liniaZDanymiZnajomego << endl;
            liniaZDanymiZnajomego = "";
        }
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void ZapiszZmianeHaslaWBazieDanych(vector<Uzytkownik> &BazaDanych) {
    fstream plik;
    string liniaZDanymiUzytkownika = "";

    plik.open("BazaUzytkownikow.txt", ios::out);
    if(plik.good() == true) {
        for(vector<Uzytkownik>::iterator itr=BazaDanych.begin(); itr!=BazaDanych.end(); itr++) {

            liniaZDanymiUzytkownika += ZamianaIntNaString(itr->IdZalogowanegoUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr->login + '|';
            liniaZDanymiUzytkownika += itr->haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
    }
    plik.close();
}

void MenuGlowne(int AktualnieZalogowaneId) {

    vector<Uzytkownik> BazaDanych;
    vector<Osoba> adresaci;
    char wybor;



}


int main() {
    vector<Osoba> adresaci;
    vector<Uzytkownik> BazaDanych;

    char wybor;
    int AktualnieZalogowaneId = 0;


    WczytajBazeUzytkownikow(BazaDanych);



    while (true) {


        cout << "1. Logowanie " << endl;
        cout << "2. Rejestracja " << endl;
        cout << "3. Wyswietl uzytkownik " << endl;
        cout << "4. Wyjdz z programu " << endl;


        wybor = wczytajZnak();

        if (wybor == '1') {
            AktualnieZalogowaneId = LogowanieUzytkownika(BazaDanych);
            wczytajZanjomychZgodniezZalogowanymId(adresaci,AktualnieZalogowaneId);



            while(true) {
                system("cls");
                cout << "1. Dodaj osobe" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkie osoby" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmien haslo " << endl;
                cout << "8. Wyloguj sie " << endl;
                cout << "9. Zakoncz program" << endl;
                cout << "Numer aktualnie zalogowane uzytkownika to: " << AktualnieZalogowaneId << endl;

                wybor = wczytajZnak();

                if (wybor == '1') {
                    wczytajZnajomychZPliku(adresaci,AktualnieZalogowaneId);
                    zapiszNowegoZnajomego(adresaci, AktualnieZalogowaneId);
                } else if (wybor == '2') {
                    WyszukajPoImieniu(adresaci);
                } else if (wybor == '3') {
                    WyszukajPoNazwisku(adresaci);
                } else if (wybor == '4') {
                    WyswietlWszystkieOsoby(adresaci);
                } else if (wybor == '5') {
                    UsunUzytkownika(adresaci);
                    ZapisZmianyWKsiazceAdresowej(adresaci,AktualnieZalogowaneId);
                } else if (wybor == '6') {
                    EdytujIstniejacyKontakt(adresaci);
                    ZapisZmianyWKsiazceAdresowej(adresaci,AktualnieZalogowaneId);
                } else if(wybor == '7') {
                    WczytajBazeUzytkownikow(BazaDanych);
                    zmianaHasloUzytkownika(BazaDanych,AktualnieZalogowaneId);
                    ZapiszZmianeHaslaWBazieDanych(BazaDanych);

                } else if(wybor == '8') {
                    system("cls");
                    main();

                } else if (wybor == '9') {
                    exit(0);
                }

            }

        } else if (wybor == '2') {
            zapisNowegoUzytkownika(BazaDanych);
        } else if (wybor == '3') {
            WyswietlWszystkichUzytkownik(BazaDanych);
        } else if (wybor == '4') {
            exit(0);
        }



    }
    return 0;
}
