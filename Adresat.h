#ifndef ADRESAT_H
#define ADRESAT_H

#include <iostream>
using namespace std;


class Adresat
{
   int id;
   int idUzytkownika;
   string imie;
   string nazwisko;
   string numer;
   string email;
   string adres;

public:
    void ustawId(int noweId);          //settery
    void ustawIdUzytkownika(int noweIdUzytkownika);
    void ustawImie (string noweImie);
    void ustawNazwisko (string noweNazwisko);
    void ustawNumer (string nowyNumer);
    void ustawEmail (string nowyEmail);
    void ustawAdres (string nowyAdres);

    int pobierzId();          //gettery
    int pobierzIdUzytkownika();
    string pobierzImie();
    string pobierzNazwisko();
    string pobierzNumer();
    string pobierzEmail();
    string pobierzAdres();
};

#endif // ADRESAT

