#include <iostream>
#include <algorithm>

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
Niech dane będą dwie czynności: (ai, bi) oraz (aj, bj). Powiedzmy, że jesteśmy
w chwili t. Jeśli wykonamy najpierw zadanie (ai, bi) a później zadanie (aj, bj)
to to drugie zadanie skończy się wykonywać w czasie:
t1 = t + ai t + bi + aj (t + ai t + bi) + bj
Jeśli natomiast wykonamy zadania w odwrotnej kolejności to wykonają się one
w chwili:
t2 = t + aj t + bj + ai (t + aj t + bj) + bi
Zastanówmy się kiedy pierwsza z opcji jest korzystniejsza. To znaczy, kiedy
zachodzi t1 <= t2. Po skróceniu wielu wyrazów otrzymamy, że t1 <= t2 wtedy
i tylko wtedy gdy aj bi <= ai bj.

Zwróćmy uwagę na to, że wynik nie zależy od chwili t oraz, że jest to ekwiwalent
bi / ai <= bj / aj jeżeli ai oraz aj nie są zerowe. Oznacza to, że możemy
posortować wszystkie wartości w tablicy rosnąco ze wzglęgu na iloraz b / a
i będzie to optymalna kolejność wykonywania czynności.

Dlaczego? Załóżmy niewprost, że istnieje tańsze rozwiązanie, które nie jest
posortowane według tego kryterium. Musi wtedy istnieć para sąsiednich elementów
dla których bi / ai > bi+1 / ai+1. Ale wtedy możemy je zamienić miejscami
otrzymując rozwiązanie lepsze - sprzeczność.
*/

struct czynnosc
{
    double a;
    double b;
    int indeks;
};

// Operator porównania dwóch czynności - będzie używany w funkcji sortującej
// Nie korzystamy z iloczynu (c1.b / c1.a < c2.b / c2.a) ze względu na to,
// że wartości a mogą być zerowe.
bool operator<(const czynnosc& c1, const czynnosc& c2)
{
    return c2.a * c1.b < c1.a * c2.b;
}

int main()
{
    int n;
    const int max_n = 1e4;
    czynnosc c[max_n];

    // Wczytywanie danych
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> c[i].a >> c[i].b;
        c[i].indeks = i+1;
    }

    // Sortowanie
    sort(c, c+n);

    // Wypisywanie wyniku
    for (int i = 0; i < n; i++)
        cout << c[i].indeks << endl;

    return 0;
}
