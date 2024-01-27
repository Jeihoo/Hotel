#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <stdlib.h>
#include <ranges>
#include <random>
#include <numeric>
#include <ctime>
#include <utility>
#include <set>
#include <conio.h>
using namespace std;

struct Varaaja {
    string nimi, osoite, puhelin;
    int hlo_maara = 0;
    int yo_maara = 0;
    double summa = 0;
    int huonenumero = 0;
    bool varaustilanne = false;

};

const int HUONEMAARA = 200;

vector<Varaaja> Varaus_1hh(vector<Varaaja> V_vec2, int yo_maara, string nimi, string osoite, string puhelin, int hlo_maara, double summa, int huonenumero, int UI_huone);
vector<Varaaja> Varaus_2hh(vector<Varaaja> V_vec3, int yo_maara, string nimi, string osoite, string puhelin, int hlo_maara, double summa, int* huonenumero, int UI_huone);

int main()
{
    
    vector<Varaaja> V_vec2;
    vector<Varaaja> V_vec3;
    vector<Varaaja> H_vec1;
    vector<Varaaja> H_vec2;
   
    Varaaja varaus[HUONEMAARA];
    Varaaja v;
    int valinta;
    char valinta2;
    bool tarkistus = true;

    do {
        cout << "\n\t\t\t\t HOTELLIN VARAUS JUHO TIAINEN ";             //Hotellin varausohjelman nimi
        cout << "\n\t\t\t\t        * PAA MENU *" << endl << endl;

        cout << "\n\t\t\t\t 1. Varaa huone 1hh, 100e/hlo" << endl;
        cout << "\n\t\t\t\t 2. Varaa huone 2hh, 150e/hlo" << endl;
        cout << "\n\t\t\t\t 3. Tarkista Varauksesi" << endl;
        cout << "\n\t\t\t\t 4. Lopeta varauksesi" << endl;

        cout << "Valitse Toiminto (1-4): ";
        cin >> valinta;
        while (valinta < 1 || valinta > 4)
        {
            cout << "Valintasi ei ole mahdollinen, syota uusi toiminto (1-4)";
            while (!(cin >> valinta))
            {
                cout << "Syotteesi ei ole numero, syota uusi luku: ";
                cin.clear();
                cin.ignore(123, '\n');
                cout << endl;
            }
        }
        


        switch (valinta)
        {
        case 1:

            do
            {
                cout << "Haluatko valita huonenumeron itse vai annatko koneen valita sen?\n" << "1. Tietokone valitsee\n2. Itse\n";
                cin >> valinta2;

                tarkistus = isdigit(valinta2);
                while (tarkistus == 0)
                {
                    cout << "Virheellinen syote, valitse 1 tai 2 ja paina enter.\n";
                    cin.clear();
                    cin.ignore(80, '\n');
                    cin >> valinta2;
                    tarkistus = isdigit(valinta2);
                }
                if (valinta2 == '1')
                {
                    do
                    { 
                        srand(time(0));
                        v.huonenumero = 1 + (rand() % 99);

                    } while (varaus[v.huonenumero].varaustilanne == true);

                    cout << "Huonenumerosi on: " << v.huonenumero;
                    cout << endl;
                    break;
                }
                else if (valinta2 == '2')
                {

                    cout << "Valitse huonenumero (1-100): ";             
                    while (!(cin >> v.huonenumero))
                    {
                        cout << "Syotteesi ei ole numero, syota uusi huonenumero (1-100): ";
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout << endl;
                    }

                    while (v.huonenumero > 100 || v.huonenumero <= 0) 
                    {
                        cout << "1hh hotellihuoneita on vain numerot 1-100, syota uusi huonenumero: ";
                        while (!(cin >> v.huonenumero))
                        {
                            cout << "Syotteesi ei ole numero, syota uusi huonenumero (1-100): ";
                            cin.clear();
                            cin.ignore(123, '\n');
                            cout << endl;
                        }
                    }
                    while (varaus[v.huonenumero].varaustilanne == true)
                    {
                        cout << "Valitettavasti huone ei ole vapaana, valitse toinen huone\n";
                        cout << "Valitse huonenumero (1-100): ";
                        while (!(cin >> v.huonenumero))
                        {
                            cout << "Syotteesi ei ole numero, syota uusi huonenumero (1-100): ";
                            cin.clear();
                            cin.ignore(123, '\n');
                            cout << endl;
                        }

                        while (v.huonenumero > 100 || v.huonenumero <= 0)
                        {
                            cout << "1hh hotellihuoneita on vain numerot 1-100, syota uusi huonenumero: ";
                            while (!(cin >> v.huonenumero))
                            {
                                cout << "Syotteesi ei ole numero, syota uusi huonenumero (1-100): ";
                                cin.clear();
                                cin.ignore(123, '\n');
                                cout << endl;
                            }
                        }
                    }

                    break;
                }


            } while (true);

            varaus[v.huonenumero].varaustilanne = true;
            H_vec1.push_back(v);  

           
            V_vec2 = Varaus_1hh(V_vec2, 0, "", "", "", 0, 0, 0, 0);


            break;

        case 2:



            do
            {
                cout << "Haluatko valita huonenumeron itse vai annatko koneen valita sen?\n" << "1. Tietokone valitsee\n2. Itse\n";
                cin >> valinta2;

                tarkistus = isdigit(valinta2);
                while (tarkistus == 0)
                {
                    cout << "Virheellinen syote, valitse 1 tai 2 ja paina enter.\n";
                    cin.clear();
                    cin.ignore(80, '\n');
                    cin >> valinta2;
                    tarkistus = isdigit(valinta2);
                }
                if (valinta2 == '1')
                {
                    do
                    { //Satunnaisgeneroi huonenumeron ja tarkistaa onko talle tietylle numerolle jo varattu huone. Yrittaa niin kauan kunnes vapaa huone loytyy
                        srand(time(0));
                        v.huonenumero = 101 + (rand() % 99);

                    } while (varaus[v.huonenumero].varaustilanne == true);

                    cout << "Huonenumerosi on: " << v.huonenumero;
                    cout << endl;
                    break;
                }
                else if (valinta2 == '2')
                {

                    cout << "Valitse huonenumero (101-200): ";
                    while (!(cin >> v.huonenumero))
                    {
                        cout << "Syotteesi ei ole numero, syota uusi huonenumero (101-200): ";
                        cin.clear();
                        cin.ignore(123, '\n');
                        cout << endl;
                    }

                    while (v.huonenumero > 200 || v.huonenumero <= 100) {
                        cout << "2hh hotellihuoneita on vain numerot 101-200, syota uusi huonenumero: ";
                        while (!(cin >> v.huonenumero))
                        {
                            cout << "Syotteesi ei ole numero, syota uusi huonenumero (1-100): ";
                            cin.clear();
                            cin.ignore(123, '\n');
                            cout << endl;
                        }
                    }
                    while (varaus[v.huonenumero].varaustilanne == true)
                    {
                        cout << "Valitettavasti huone ei ole vapaana, valitse toinen huone\n";
                        cout << "Valitse huonenumero (101-200): ";
                        while (!(cin >> v.huonenumero))
                        {
                            cout << "Syotteesi ei ole numero, syota uusi huonenumero (101-200): ";
                            cin.clear();
                            cin.ignore(123, '\n');
                            cout << endl;
                        }

                        while (v.huonenumero > 200 || v.huonenumero <= 100) 
                        {
                            cout << "2hh hotellihuoneita on vain numerot 101-200, syota uusi huonenumero: ";
                            while (!(cin >> v.huonenumero))
                            {
                                cout << "Syotteesi ei ole numero, syota uusi huonenumero (101-200): ";
                                cin.clear();
                                cin.ignore(123, '\n');
                                cout << endl;
                            }
                        }
                    }

                    break;
                }


            } while (true);

            varaus[v.huonenumero].varaustilanne = true;
            H_vec2.push_back(v);
           
            V_vec3 = Varaus_2hh(V_vec3, 0, "", "", "", 0, 0, 0, 0);

            break;

        case 3:

            cout << endl;
            cout << "\t\t\t\t--------Varaustietosi-------- " << endl << endl << endl;




            for (int i = 0; i < V_vec2.size(); i++)
            {
                

                cout << "\t\t\t\t   VARAUSKEN " << i + 1 << " TIEDOT" << endl << endl;
                cout << "\t\t\t\t-------------1hh-------------" << endl << endl;
                cout << "\t\t\t\tVaraajan nimi:\t\t" << V_vec2[i].nimi << endl;
                cout << "\t\t\t\tVaraajan osoite:\t" << V_vec2[i].osoite << endl;
                cout << "\t\t\t\tVaraajan puhelinnumero:\t" << V_vec2[i].puhelin << endl;
                cout << "\t\t\t\tVaraajan henkilomaara:\t" << V_vec2[i].hlo_maara << endl;
                cout << "\t\t\t\tVaraajan yo maara:\t" << V_vec2[i].yo_maara << endl << endl;
                cout << "\t\t\t\tVaraajan huone:\t\t" << H_vec1[i].huonenumero << endl;
                cout << "\t\t\t\tVarauksesi hinta:\t" << V_vec2[i].summa << endl << endl << endl;


            }







            for (int i = 0; i < V_vec3.size(); i++)
            {


                cout << "\t\t\t\t  VARAUKSEN " << i + 1 << " TIEDOT" << endl << endl;
                cout << "\t\t\t\t-------------2hh-------------" << endl << endl;
                cout << "\t\t\t\tVaraajan nimi:\t\t" << V_vec3[i].nimi << endl;
                cout << "\t\t\t\tVaraajan osoite:\t" << V_vec3[i].osoite << endl;
                cout << "\t\t\t\tVaraajan puhelinnumero:\t" << V_vec3[i].puhelin << endl;
                cout << "\t\t\t\tVaraajan henkilomaara:\t" << V_vec3[i].hlo_maara << endl;
                cout << "\t\t\t\tVaraajan yo maara:\t" << V_vec3[i].yo_maara << endl << endl;
                cout << "\t\t\t\tVaraajan huone:\t\t" << H_vec2[i].huonenumero << endl;
                cout << "\t\t\t\tVarauksesi hinta:\t" << V_vec3[i].summa << endl << endl << endl;

            }



            break;

        case 4:
            cout << endl << endl << "Kiitos varauksestasi! Nahdaan pian!" << endl << endl;
        }
    } while (valinta != 4);

    return 0;

}


vector<Varaaja> Varaus_1hh(vector<Varaaja> V_vec2, int yo_maara, string nimi, string osoite, string puhelin, int hlo_maara, double summa, int huonenumero, int UI_huone)
{
    Varaaja v;
 

  

    cout << "\n\nKuinka monta yota viivyt hotellilla: ";
    while (!(cin >> v.yo_maara))
    {
        cout << "Syotteesi ei ole numero, syota uusi maara: ";
        cin.clear();
        cin.ignore(123, '\n');
        cout << endl;
    }
    cout << "Etunimi Sukunimi: ";
    cin.ignore();
    getline(cin, v.nimi);
    cout << "Osoite: ";
    getline(cin, v.osoite);
    cout << "Puhelinnumero: ";
    getline(cin, v.puhelin);
    cout << "Henkilo maara, max 1 henkiloa: ";
    while (!(cin >> v.hlo_maara))
    {
        cout << "Syotteesi ei ole numero, syota uusi henkilomaara: ";
        cin.clear();
        cin.ignore(123, '\n');
        cout << endl;
    }

    while (v.hlo_maara > 1 || v.hlo_maara <= 0) {
        cout << "Huoneen maksimikapasitetti on 1 henkiloa, laita uusi henkilomaara: ";
        while (!(cin >> v.hlo_maara))
        {
            cout << "Syotteesi ei ole numero, syota uusi henkilomaara: ";
            cin.clear();
            cin.ignore(123, '\n');
            cout << endl;
        }
    }

    v.summa = v.hlo_maara * 100 * v.yo_maara;
    cout << "Huoneesi hinta on " << v.summa << endl;

    V_vec2.push_back(v);

    return V_vec2;

}

vector<Varaaja> Varaus_2hh(vector<Varaaja> V_vec3, int yo_maara, string nimi, string osoite, string puhelin, int hlo_maara, double summa, int* huonenumero, int UI_huone)
{
    Varaaja v;

    cout << "\n\nKuinka monta yota viivyt hotellilla: ";
    while (!(cin >> v.yo_maara))
    {
        cout << "Syotteesi ei ole numero, syota uusi maara: ";
        cin.clear();
        cin.ignore(123, '\n');
        cout << endl;
    }
    cout << "Etunimi Sukunimi: ";
    cin.ignore();
    getline(cin, v.nimi);                                                //asiakas tayttaa 'nimen'
    cout << "Osoite: ";
    getline(cin, v.osoite);                                             // 'osoitteen'
    cout << "Puhelinnumero: ";
    getline(cin, v.puhelin);                                             // 'puhelinumeron'
    cout << "Henkilo maara, max 2 henkiloa: ";
    while (!(cin >> v.hlo_maara))
    {
        cout << "Syotteesi ei ole numero, syota uusi henkilomaara: ";
        cin.clear();
        cin.ignore(123, '\n');
        cout << endl;
    }

    while (v.hlo_maara > 2 || v.hlo_maara <= 0) {
        cout << "Huoneen maksimikapasitetti on 1 henkiloa, laita uusi henkilomaara: ";
        while (!(cin >> v.hlo_maara))
        {
            cout << "Syotteesi ei ole numero, syota uusi henkilomaara: ";
            cin.clear();
            cin.ignore(123, '\n');
            cout << endl;
        }
    }

    v.summa = v.hlo_maara * 150 * v.yo_maara;
    cout << "Huoneesi hinta on " << v.summa << endl;
    V_vec3.push_back(v);

    return V_vec3;
}
