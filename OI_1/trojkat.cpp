#include <iostream>

using namespace std;

/*
Udzielę korepetycji!

Cześć! Mam na imię Krzysztof i w 2011 roku reprezentowałem nasz kraj na finale
mistrzostw świata w programowaniu w Orlando na Florydzie. Mimo licznych sukcesów
w zawodach programistycznych uważam, że moją najsilniejszą stroną jest
umiejętność dzielenia się swoją wiedzą z innymi. Pracowałem między innymi
w III LO we Wrocławiu, XIV LO we Wrocławiu, Gimnazjum nr 13
oraz Gimnazjum nr 49. Jedna z moich uczennic wygrała ogólnopolską olimpiadę
przedmiotową, obecnie spełnia się w projektach naukowych w Stanach
Zjednoczonych. W latach 2014-2020 byłem doktorantem na Uniwersytecie
Wrocławskim, gdzie prowadziłem zajęcia dla studentów. Uczniowie bardzo cenili
sobie zajęcia ze mną i niezależnie od przedmiotu, moi studenci dobrze wypadali
na tle swoich rówieśników. Po skończeniu doktoratu pracowałem w firmie Google,
gdzie udało mi się zaimplementować algorytm euklidesa w pliku konfiguracyjnym
oraz regresję liniową w SQLu. Udało mi się również usunąć kilka tysięcy plików
konfiguracyjnych i zastąpić je 200 linijkowym skryptem (który robił właściwie to
samo). Jestem również autorem kilkunastu artykułów w prasie popularnonaukowej
i prowadzę swojego bloga naukowego.

Rzuciłem prace w Google aby zająć się profesjonalnym udzielaniem korepetycji.
Z sukcesami prowadzę zajęcia dla uczniów, którzy chcieliby spróbować swoich
szans na olimpiadzie informatycznej. Nie zależnie od tego czy startowałeś
w Olimpiadzie w poprzednich latach, czy dopiero zaczynasz swoją przygodę, mogę
pomóc Ci rozwinąć skrzydła i odblokować cały potencjał w Tobie drzemiący.
Jeśli chcesz się zapisać na moje zajęcia, napisz maila na adres:

  korepetycje@krzysiek.how

Więcej informacji znajdziesz na:

  https://krzysiek.how/korepetycje/

Moi studenci napisali o mnie:

  https://krzysiek.how/opinie-studentow/

Moi klienci napisali o mnie:

  https://www.e-korepetycje.net/kpiecuch
*/

/*
UWAGA!

Program nie był napisany aby zoptymalizować liczbę operacji ani prędkość
działania. Autorowi przyświecała idea napisania jak najprostszego algorytmu, aby
był on zrozumiały dla jak największej liczby odbiorców.
*/

/*
Niech a <= b <= c będą długościami odcinków. Można z nich utworzyć trójkąt
wtedy i tylko wtedy gdy c < a + b. Aby sprawdzić czy spośród odcinków
a1 <= a2 <= ... <= an każde trzy tworzą trójkąt, wystarczy sprawdzić czy odcinki
a1, a2 i an tworzą trójkąt. Wystarczy zatem spośród odcinków na wejściu znaleźć
dwa najmniejsze i największy a następnie podstawić do nierówności.

Zadanie wymaga od nas dodatkowo obsługi ułamków. Na szczeście jest to proste.
*/

// Definicja ułamka.
struct ulamek
{
    long long licznik;
    long long mianownik;
};

// Porównanie dwóch ułamków.
bool operator<(const ulamek& u1, const ulamek& u2)
{
    return u1.licznik * u2.mianownik < u2.licznik * u1.mianownik;
}

// Dodawanie dwóch ułamków do siebie.
ulamek operator+(const ulamek& u1, const ulamek& u2)
{
    ulamek suma;

    suma.licznik = u1.licznik * u2.mianownik + u2.licznik * u1.mianownik;
    suma.mianownik = u1.mianownik * u2.mianownik;

    return suma;
}

int main()
{
    int n;
    char ukosnik;

    cin >> n;

    ulamek min1, min2, max;

    min1.licznik = min2.licznik = 1e4;
    max.licznik = 0;
    min1.mianownik = min2.mianownik = max.mianownik = 1;

    for (int i = 0; i < n; i++)
    {
        ulamek u;

        cin >> u.licznik >> ukosnik >> u.mianownik;

        if (u < min1)
        {
            min2 = min1;
            min1 = u;
        }
        else if (u < min2)
        {
            min2 = u;
        }
        if (max < u)
        {
            max = u;
        }
    }

    if (max < min1 + min2)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;

    return 0;
}
