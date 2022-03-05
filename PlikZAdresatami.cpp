#include "PlikZAdresatami.h"

using namespace std;


bool PlikZAdresatami :: dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = "";
    fstream plik;
    plik.open(pobierzNazwePliku().c_str(), ios::out | ios::app);

    if (plik.good() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty(plik) == true)
        {
            plik << liniaZDanymiAdresata;
        }
        else
        {
            plik << endl << liniaZDanymiAdresata ;
        }
        idOstatniegoAdresata++;
        plik.close();
        return true;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
         plik.close();
        system("pause");
        return false;
    }
}
////////////////////////////////////////////////////////////////////
string PlikZAdresatami :: zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumer() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}
////////////////////////////////////////////////////////////////////
vector <Adresat> PlikZAdresatami :: wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    vector <Adresat> adresaci;
    Adresat adresat;

    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstatniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstatniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
        plikTekstowy.close();
    }
    if (daneOstatniegoAdresataWPliku != "")
    {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstatniegoAdresataWPliku);
    }
    return adresaci;
}

////////////////////////////////////////////////////////////////////////
int PlikZAdresatami :: pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));

    return idUzytkownika;
}

////////////////////////////////////////////////////////////////////////
Adresat PlikZAdresatami :: pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.ustawId(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 2:
                adresat.ustawIdUzytkownika(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 3:
                adresat.ustawImie(pojedynczaDanaAdresata);
                break;
            case 4:
                adresat.ustawNazwisko(pojedynczaDanaAdresata);
                break;
            case 5:
                adresat.ustawNumer(pojedynczaDanaAdresata);
                break;
            case 6:
                adresat.ustawEmail(pojedynczaDanaAdresata);
                break;
            case 7:
                adresat.ustawAdres(pojedynczaDanaAdresata);
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}
/////////////////////////////////////////////////////////////////////
int PlikZAdresatami :: pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}
/////////////////////////////////////////////////////////////////////
int PlikZAdresatami :: pobierzIdOstatniegoAdresata()
{
    fstream plikTekstowy;
    plikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);
    string daneOstatniegoAdresata, daneJednegoAdresata;

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresata))
        {
            daneOstatniegoAdresata = daneJednegoAdresata;
        }
    }
    int idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstatniegoAdresata);
    plikTekstowy.close();
    return idOstatniegoAdresata;
}
//////////////////////////////////////////////////////////////////////
void PlikZAdresatami :: usunWybranaLinieWPliku(int idUsuwanegoAdresata)
{
    fstream odczytywanyPlikTekstowy, tymczasowyPlikTekstowy;
    string wczytanaLinia = "";
    int idAdresataZPliku;

    odczytywanyPlikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);
    tymczasowyPlikTekstowy.open(NAZWA_PLIKU_TYMCZASOWEGO.c_str(), ios::out | ios::app);

    if (odczytywanyPlikTekstowy.good() == true  && tymczasowyPlikTekstowy.good() == true)
    {
        while (getline(odczytywanyPlikTekstowy, wczytanaLinia))
        {
            idAdresataZPliku =  pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(wczytanaLinia);
            if (idAdresataZPliku != idUsuwanegoAdresata)
            {
                if (czyPlikJestPusty(tymczasowyPlikTekstowy) == true)
                    tymczasowyPlikTekstowy << wczytanaLinia;
                else
                    tymczasowyPlikTekstowy << endl << wczytanaLinia;
            }
            else if (idAdresataZPliku == idUsuwanegoAdresata) {}
        }
        odczytywanyPlikTekstowy.close();
        tymczasowyPlikTekstowy.close();

        usunPlik();
        zmienNazwePliku(NAZWA_PLIKU_TYMCZASOWEGO, pobierzNazwePliku());
        podajIdOstatniegoAdresataPoUsunieciuWybranegoAdresata(idUsuwanegoAdresata);
    }
}
//////////////////////////////////////////////////////////////////////////
void PlikZAdresatami :: podajIdOstatniegoAdresataPoUsunieciuWybranegoAdresata(int idUsuwanegoAdresata)
{
    if (idUsuwanegoAdresata == idOstatniegoAdresata)
        idOstatniegoAdresata = pobierzIdOstatniegoAdresata();
}
//////////////////////////////////////////////////////////////////////////
void PlikZAdresatami :: zmienNazwePliku(string staraNazwa, string nowaNazwa)
{
    if (rename(staraNazwa.c_str(), nowaNazwa.c_str()) == 0) {}
    else
        cout << "Nazwa pliku nie zostala zmieniona." << staraNazwa << endl;
}
//////////////////////////////////////////////////////////////////////////
void PlikZAdresatami :: usunPlik()
{
    if (remove(pobierzNazwePliku().c_str()) == 0) {}
    else
        cout << "Nie udalo sie usunac pliku " << pobierzNazwePliku() << endl;
}
///////////////////////////////////////////////////////////////////////////
void PlikZAdresatami :: edytujAdresataWPliku(Adresat adresat)
{
    string liniaZNowymiDanymiAdresata = "";
    liniaZNowymiDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

    int idEdytowanegoAdresata = adresat.pobierzId();
    fstream odczytywanyPlikTekstowy, tymczasowyPlikTekstowy;
    string wczytanaLinia = "";
    int id;
    int numerWczytanejLinii = 1;

    odczytywanyPlikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);
    tymczasowyPlikTekstowy.open(NAZWA_PLIKU_TYMCZASOWEGO.c_str(), ios::out | ios::app);

    if (odczytywanyPlikTekstowy.good() == true && tymczasowyPlikTekstowy.good() == true)
    {
        while (getline(odczytywanyPlikTekstowy, wczytanaLinia))
        {
            id = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(wczytanaLinia);

            if (id != idEdytowanegoAdresata)
            {
                if (numerWczytanejLinii == 1)
                    tymczasowyPlikTekstowy << wczytanaLinia;
                else if (numerWczytanejLinii > 1)
                    tymczasowyPlikTekstowy << endl << wczytanaLinia;
            }
            else if (id == idEdytowanegoAdresata)
            {
                if (numerWczytanejLinii == 1)
                    tymczasowyPlikTekstowy << liniaZNowymiDanymiAdresata;
                else if (numerWczytanejLinii > 1)
                    tymczasowyPlikTekstowy << endl << liniaZNowymiDanymiAdresata;
            }
            numerWczytanejLinii++;
        }
        odczytywanyPlikTekstowy.close();
        tymczasowyPlikTekstowy.close();

        usunPlik();
        zmienNazwePliku(NAZWA_PLIKU_TYMCZASOWEGO, pobierzNazwePliku());
        cout << endl << "Dane zostaly zaktualizowane." << endl << endl;
    }
}

