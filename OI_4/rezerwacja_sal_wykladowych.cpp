#include <iostream>
#include <vector>
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
To zadanie spróbujemy rozwiązać za pomocą programowania dynamicznego. Utworzymy
tablicę dp i w jej i-tym elemencie (dp[i]) będziemy trzymać maksymalny czas
wykorzystania sali wykładowej jeśli ostatni wykład skończyłby się przed czasem
i.

W książce "Przygody Bajtazara" (którą gorąco polecam), autorzy zasugerowali
sortowanie wykładów i użycie wyszukiwania binarnego. My uprościmy to rozwiązanie
i wykorzystamy fakt, że wartości p oraz k są ograniczone z góry przez 30 000.
Zaczniemy od umieszczenia wszystkich przedziałów w tablicy wektorów. Wektor
poczatki[i] będzie zawierał początki wszystkich przedziałów, które kończą się
w chwili i. Jest to ekwiwalent sortowania (zwany sortowaniem przez zliczanie).

Powiedzmy, że chcemy teraz policzyć dp[i]. Mamy dwie możliwości. Albo w chwili
i będzie kończył się jakiś wykład, albo... nie... Jeśli nie to dp[i] = dp[i-1].
Jeśli kończy się wykład, który się zaczął w chwili j to dp[i] = dp[j] + i - j.
Z tych dwóch wartości wystarczy wziąć maksimum. Jeśli istnieje więcej wykładów
kończących się w chwili i to musimy maksimum wziąć z nich wszystkich.

Złożoność całego algorytmu to O(n + limit).
*/

const int limit = 3e4; // Maksymalna wartość zmiennych p oraz k.

int main()
{
    int n, p, k;
    int dp[limit + 1];
    vector<int> poczatki[limit + 1];

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> p >> k;
        poczatki[k].push_back(p);
    }

    dp[0] = 0;

    for (int i = 1; i <= limit; i++)
    {
        dp[i] = dp[i-1];

        for (int j : poczatki[i])
            dp[i] = max(dp[i], dp[j] + i - j);
    }

    cout << dp[limit] << endl;

    return 0;
}
