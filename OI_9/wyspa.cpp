#include <iostream>
#include <vector>

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
W niniejszym pliku wytłumaczę w jaki sposób działa algorytm rozwiązujący zadanie
Wyspa. W jaki sposób można dojść do tego algorytmu oraz dowód jego poprawności
można znaleźć na moim blogu:

  https://krzysiek.how/jak-zmniejszyc-zlozonosc-swojego-algorytmu/

W algorytmie posługujemy się dwoma iteratorami: ogon i głowa, które reprezentują
pewien spójny przedział na naszej wyspie:

  wyspa[ogon], wyspa[ogon+1], ..., wyspa[głowa - 1]

Sumę tych elementów nazywamy umownie odległością zgodną z ruchem wskazówek
zegara pomiędzy miastami ogon i głowa i zapisujemy w zmiennej zgodnie.

  zgodnie = wyspa[ogon] + wyspa[ogon+1] + ... + wyspa[głowa - 1]

Sumę wszystkich pozostałych elementów nazywamy odległością przeciwną do ruchu
wskazówek zegara i pamiętamy ją w zmiennej przeciwnie. W zależności od tego,
która odległość jest większa - zwiększamy odpowiedni iterator. Jeśli zgodnie
jest większe to zwiększamy ogon, jeśli przeciwnie jest większe to zwiększamy
głowę. Po każdym przedunięciu iteratora, aktualizujemy zmienne zgodnie
i przeciwnie, a następnie sprawdzamy czy odległość między miastami (zdefiniowana
w zadaniu jako minimum zmiennych zgodnie i przeciwnie) nie jest większa niż
dotychczas znaleziona. Jeśli tak to aktualizujemy zmienną maksymalna.

Przykład działania algorytmu na przykładowych danych wejściowych:

[] 1 2 3 4 5
zgodnie = 0
przeciwnie = 15
zgodnie < przeciwnie
glowa++

[1] 2 3 4 5
zgodnie = 1
przeciwnie = 14
zgodnie < przeciwnie
glowa++

[1 2] 3 4 5
zgodnie = 3
przeciwnie = 12
zgodnie < przeciwnie
glowa++

[1 2 3] 4 5
zgodnie = 6
przeciwnie = 9
zgodnie < przeciwnie
glowa++

[1 2 3 4] 5
zgodnie = 10
przeciwnie = 5
zgodnie > przeciwnie
ogon++

1 [2 3 4] 5
zgodnie = 9
przeciwnie = 6
zgodnie > przeciwnie
ogon++

1 2 [3 4] 5
zgodnie = 7 [tutaj znajdujemy optymalne rozwiązanie]
przeciwnie = 8
zgodnie < przeciwnie
glowa++

1 2 [3 4 5]
zgodnie = 12
przeciwnie = 3
zgodnie > przeciwnie
ogon++

1 2 3 [4 5]
zgodnie = 9
przeciwnie = 6
zgodnie > przeciwnie
ogon++

1 2 3 4 [5]
zgodnie = 5
przeciwnie = 10
zgodnie < przeciwnie
glowa++
*/
int rozwiazanie(const vector<int>& wyspa)
{
    int suma = 0; // Suma wszystkich elementów w tablicy. Posłuży nam do
                  // zainicjowania zmiennej przeciwnie.

    for (int i = 0; i < wyspa.size(); i++)
        suma += wyspa[i];

    int glowa = 0;
    int ogon = 0;

    int zgodnie = 0;
    int przeciwnie = suma;
    int maksymalna = 0; // Maksymalna znaleziona odległość między miastami.

    while (glowa <= wyspa.size()) // Algorytm kończymy gdy głowa dojdzie do
    {                             // końca tablicy.
        // W zależności od tego, która zmienna (zgodnie / przeciwnie) jest
        // większa, zwiększamy głowę bądź ogon i aktualizujemy zmienne.
        if (zgodnie < przeciwnie)
        {
            zgodnie += wyspa[glowa];
            przeciwnie -= wyspa[glowa];
            glowa++;
        }
        else if (zgodnie > przeciwnie)
        {
            zgodnie -= wyspa[ogon];
            przeciwnie += wyspa[ogon];
            ogon++;
        }
        else // Jeśli zgodnie == przeciwnie to jest to znaleźliśmy największą
             // możliwą odległość między dwoma miastami.
            return zgodnie;

        // Aktualizujemy zmienną maksymalna.
        int odleglosc;

        if (zgodnie < przeciwnie)
            odleglosc = zgodnie;
        else
            odleglosc = przeciwnie;

        if (odleglosc > maksymalna)
            maksymalna = odleglosc;
    }

    return maksymalna;
}
/*
W każdym kroku pętli while zwiększamy jedną ze zmiennych: głowę bądź ogon.
Ponieważ żadna z tych zmiennych nie może przekroczyć wartości wyspa.size(), to
pętla while wykona się co najwyżej 2 * wyspa.size(), a to oznacza, że złożoność
obliczeniowa naszego algorytmu wynosi O(n).
*/

int main()
{
    int n;
    vector<int> wyspa;

    cin >> n;

    wyspa.resize(n);
    for (int i = 0; i < n; i++)
        cin >> wyspa[i];

    cout << rozwiazanie(wyspa) << endl;

    return 0;
}
