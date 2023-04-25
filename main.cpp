#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Adresat
{
    string imie, nazwisko, nrTel, email, adres;
    int idAdresata;
};
string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

void dodajOsobeDoKsiazki (vector <Adresat> &adresaci)
{

    Adresat pomoc;

    string imie = " ", nazwisko = " ", nrTel = " ", email = " ", adres = " ";
    //int idAdresata;


    cout << "Podaj imie: ";
    imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();
    cout << "Podaj nr telefonu: ";
    nrTel = wczytajLinie();
    cout << "Podaj email: ";
    email = wczytajLinie();
    cout << "Podaj swoj adres: ";
    adres = wczytajLinie();

    pomoc.idAdresata = adresaci.empty() ? 1 : adresaci.back().idAdresata +1;
    pomoc.imie = imie;
    pomoc.nazwisko = nazwisko;
    pomoc.nrTel = nrTel;
    pomoc.email = email;
    pomoc.adres = adres;

    adresaci.push_back(pomoc);

    fstream plikDoZapisu;
    plikDoZapisu.open("ksiazkaZAdresami.txt", ios::out | ios::app);

    if (plikDoZapisu.good() == true)
    {
        plikDoZapisu << pomoc.idAdresata << "|" << pomoc.imie << "|" << pomoc.nazwisko << "|" << pomoc.nrTel << "|" << pomoc.email << "|" << pomoc.adres << "|" << endl;
        plikDoZapisu.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku";
        system("pause");
    }
    cout << "Osoba zostala dodana do ksiazki adresowej" << endl;
    system("pause");
}

vector <Adresat> rozdzielDaneAdresatowNaPojedynczeDane (vector <Adresat> &adresaci, string liniaDoOdczytania, char znakPionowejKreski)
{
    Adresat adresat;
    int nrLinii = 1;
    stringstream ss(liniaDoOdczytania);
    string pojedynczaDana = " ";

    while (getline(ss, pojedynczaDana, znakPionowejKreski))
    {
        switch (nrLinii)
        {
        case 1:
            adresat.idAdresata = (atoi(pojedynczaDana.c_str()));
            break;
        case 2:
            adresat.imie = pojedynczaDana;
            break;
        case 3:
            adresat.nazwisko = pojedynczaDana;
            break;
        case 4:
            adresat.nrTel = pojedynczaDana;
            break;
        case 5:
            adresat.email = pojedynczaDana;
            break;
        case 6:
            adresat.adres = pojedynczaDana;
            break;

        }
        nrLinii++;
    }
    adresaci.push_back(adresat);

    return adresaci;
}

void wczytajPlikZDanymiAdresatow (vector <Adresat> &adresaci)
{
    string liniaTekstu;
    fstream plik;

    plik.open("ksiazkaZAdresami.txt", ios::app);
    plik.close();

    plik.open("ksiazkaZAdresami.txt", ios::in);

    if (plik.good())
    {
        while (getline(plik, liniaTekstu))
        {
            adresaci = rozdzielDaneAdresatowNaPojedynczeDane(adresaci, liniaTekstu, '|');
        }
    }
    plik.close();
}

void zapiszPoModyfikacji (vector <Adresat> &adresaci)
{
    fstream plikPoUsunieciuOsoby;
    plikPoUsunieciuOsoby.open("KsiazkaZAdresami.txt", ios::out | ios::trunc);
    if (plikPoUsunieciuOsoby.good())
    {
        for ( vector <Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr )
        {
            plikPoUsunieciuOsoby << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;

        }
    }
    plikPoUsunieciuOsoby.close();
}

void usunAdresata (vector <Adresat> &adresaci)
{
    int idUsuwanejOsoby;
    char potwierdzenieWyboru;

    cout << "Podaj id adresata, ktorego chcesz usunac: ";
    cin >> idUsuwanejOsoby;
    for (vector <Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr-> idAdresata == idUsuwanejOsoby)
        {
            cout << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;
            Sleep(1000);
            cout << "Czy na pewno chcesz usunac tego adresata? Kliknij t: " << endl;
            cin >> potwierdzenieWyboru;
            if (potwierdzenieWyboru == 't')
            {
                adresaci.erase(itr);
                cout << "Kontakt zostal usuniety";
                Sleep(1500);

                zapiszPoModyfikacji(adresaci);
            }
            else if (potwierdzenieWyboru != 't')
            {
                cout << "Blad! Wcisnales zly klawisz!";
            }
            break;
        }
    }
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    string noweImie, noweNazwisko, nowyNumerTelefonu, nowyEmail, nowyAdres;
    char wybranyElementMenu;
    int idSzukanejOsoby;
    bool zmienna1 = true;

    cout << "Wyszukanie znajomego. Podaj numer ID znajomego: ";
    cin >> idSzukanejOsoby;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> idAdresata == idSzukanejOsoby)
        {
            cout << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;
            Sleep(1000);
            while(zmienna1)
            {
                system("cls");
                cout << "1.Edytuj imie." << endl;
                cout << "2.Edytuj nazwisko." << endl;
                cout << "3.Edytuj numer telefonu." << endl;
                cout << "4.Edytuj adres mailowy." << endl;
                cout << "5.Edytuj adres kontaktowy." << endl;
                cout << "6.Edytuj wszystkie informacje." << endl;
                cout << "9.Zakoncz edycje." << endl<<endl;
                cin >> wybranyElementMenu;

                switch(wybranyElementMenu)
                {
                case '1':
                    cout << "Podaj nowe imie: ";
                    itr-> imie = wczytajLinie();
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    itr-> nazwisko = wczytajLinie();
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    itr-> nrTel = wczytajLinie();
                    break;
                case '4':
                    cout << "Podaj nowy adres email: ";
                    itr-> email = wczytajLinie();
                    break;
                case '5':
                    cout << "Podaj nowy adres zamieszkania: ";
                    itr-> adres = wczytajLinie();
                    break;
                case '6':
                    cout << "Podaj nowe imie: ";
                    itr-> imie = wczytajLinie();
                    cout << "Podaj nowe nazwisko: ";
                    itr-> nazwisko = wczytajLinie();
                    cout << "Podaj nowy numer telefonu: ";
                    itr-> nrTel = wczytajLinie();
                    cout << "Podaj nowy adres mailowy: ";
                    itr-> email = wczytajLinie();
                    cout << "Podaj nowy adres zamieszkania: ";
                    itr-> adres = wczytajLinie();
                    break;
                case '9':
                    zmienna1 = false;

                }
            }
        }
    }
    zapiszPoModyfikacji(adresaci);
}
void wyszukajPoImieniu(vector <Adresat> &adresaci)
{
    string imieSzukane;

    cout << "Wyszukaj po imieniu. Podaj imie :";
    cin >> imieSzukane;
    vector <Adresat> ::iterator koniec = adresaci.end();
    for (vector<Adresat>::iterator itr = adresaci.begin(); itr != koniec; ++itr)
    {
        if(itr->imie == imieSzukane )
        {
            cout << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;
        }
    }
    cout << "Nie ma osoby o podanym nazwisku w ksiazce adresowej " << endl;
    Sleep(3000);
}

void wyszukajPoNazwisku(vector <Adresat> &adresaci)
{
    string nazwiskoSzukane;

    cout << "Wyszukaj po nazwisku. Podaj nazwisko :";
    cin >> nazwiskoSzukane;
    vector <Adresat> ::iterator koniec = adresaci.end();
    for (vector<Adresat>::iterator itr = adresaci.begin(); itr != koniec; ++itr)
    {
        if(itr->nazwisko == nazwiskoSzukane )
        {
            cout << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;
        }
    }
    cout << "Nie ma osoby o podanym nazwisku w ksiazce adresowej " << endl;
    Sleep(3000);
}
void wyswietlWszystkieOsoby(vector <Adresat> &adresaci)
{
    vector <Adresat> ::iterator koniec = adresaci.end();
    for (vector<Adresat>::iterator itr = adresaci.begin(); itr != koniec; ++itr)
    {
        cout << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;
    }
    system("pause");
}
int main()
{
    char wyborWMenu;
    vector <Adresat> adresaci;

    wczytajPlikZDanymiAdresatow (adresaci);

    while (true)
    {
        system("cls");
        cout << "Witaj w ksiazce adresowej!" << endl;
        cout << "Wybierz opcje: " << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyswietl wszystkie po imieniu" << endl;
        cout << "3. Wyswietl wszystkie po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Wyjscie z programu" << endl;
        cin>>wyborWMenu;
        switch (wyborWMenu)
        {

        case '1':
            dodajOsobeDoKsiazki(adresaci);
            break;
        case '2':
            wyszukajPoImieniu(adresaci);
            break;
        case '3':
            wyszukajPoNazwisku(adresaci);
            break;
        case '4':
            wyswietlWszystkieOsoby(adresaci);
            break;
        case '5':
            usunAdresata(adresaci);
            break;
        case '6':
            edytujAdresata(adresaci);
            break;
        case '7':
            exit(0);
            break;
        }
    }
    return 0;
}
