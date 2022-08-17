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
Rozwiązanie zadania zacznijmy od zwykłego zliczania kontenerów. Dla każdej
operacji wykonanej przez dźwig, patrzymy na których pozycjach zostaną
umieszczone kontenery i dla tych miejsc zwiększamy licznik o jeden. To proste
rozwiązanie pozwalało uzyskać 21 punktów na olimpiadzie.
*/

const int max_size = 1e5;
int kontenery[max_size + 1];

void pojedynczo(int a, int l, int d)
{
    for (int i = 0; i < l; i++)
        kontenery[a + i * d]++;
}

/*
Powyższa funkcja działa w czasie O(l), albo inaczej - działa ona w najgorszym
przypadku w czasie O(n / d) gdyż n to liczba pozycji na rampie, a d oznacza
wielkość "skoku" pomiędzy kolejnymi kontenerami. Ponieważ d może być małą liczbą
naturalną, a funkcję należy wykonać m razy, otrzymaliśmy w ten sposób algorytm
działający w czasie O(n * m).
*/

/*
Spróbujmy teraz rozwiązać problem w którym wszystkie operacje mają tę samą
wartość "skoku" d. Jeśli d = 1 to każda operacja zostawia kontenery na pewnym
przedziale. Możemy przejść po wszystkich pozycjach na rampie i pamiętać ile
w tej chwili jest otwartych przedziałów. W tym celu musimy wcześniej dla każdej
pozycji na rampie zliczyć ile w danej pozycji zaczyna się i ile kończy
przedziałów. Wtedy algorytm może po prostu przejść po wszystkich pozycjach i dla
pozycji i:
 - dodać do zmienej licznikowej liczbę przedziałów, które otwierają się
   w pozycji i
 - zapisać, że w pozycji i będzie się znajdowało tyle kontenerów ile jest
   otwartych przedziałów
 - odjąć od zmiennej licznikowej liczbę przedziałów które zamykają się
   w pozycji i
Co jednak jeśli d jest większe niż 1? Dla d = 2 musimy wykonać algorytm
dwukrotnie: dla pozycji parzystych i pozycji nieparzystych. Z kolei dla d = 3
musimy wykonać algorytm trzykrotnie: dla pozycji postaci 3k, pozycji 3k+1 oraz
pozycji 3k+2. Ogólnie. Dla pozycji d, musimy algorytm wykonać d-krotnie.
*/

void zbiorowo(const vector<int>& a, const vector<int>& l, int d, int n)
{
    int poczatki[max_size + 1] = {};
    int konce[max_size + 1] = {};

    for (int i = 0; i < a.size(); i++)
    {
        poczatki[a[i]]++;
        konce[a[i] + (l[i] - 1) * d]++;
    }

    for (int mod = 0; mod < d; mod++)
    {
        int licz = 0;

        for (int i = mod; i <= n; i += d)
        {
            licz += poczatki[i];
            kontenery[i] += licz;
            licz -= konce[i];
        }
    }
}

/*
Algorytm możemy wykonać dla wszystkich wartości skoku d na wejściu. Takie
rozwiązanie dawało 54 punkty na olimpiadzie. Pojedyncze uruchomienie funkcji
działa w czasie O(m + n). Ponieważ funkcję musimy uruchomić dla każdej
wartości d - końcowa złożoność to O(m * n).
*/

/*
Rozwiązanie, które tutaj chciałbym przedstawić, polega na połączeniu tych dwóch
algorytmów. Operacje, które mają wartość d większą od pewnej stałej T,
obsługujemy za pomocą pierwszego algorytmu - algorytm ten działa dobrze dla
dużych wartości d. Operacje, które mają mają wartość d mniejszą od stałej T,
grupujemy i obsługujemy za pomocą drugiego algorytmu - algorytm ten działa
dobrze jeśli nie jest uruchumiony zbyt wiele razy.

Pierwszy algorytm zadziała w czasie O(m * n / T). Z kolei drugi algorytm
zadziała w czasie O(T * n). Zatem całość działa w czasie O(m * n / T + T * n).
Można policzyć, że najlepiej za T wziąć wartość równą pierwiastkowi z n. Wtedy
nasz algorytm będzie działał w złożoności O(sqrt(n) * (m + n)), co gwarantuje
nam 100 punktów na olimpiadzie.

Poniżej znajduje się implementacja algorytmu. Zamiast liczyć pierwiastka z n,
przyjąłem T = sqrt(100 000) ~= 316.
*/

const int T = 316;

int main()
{
    int n, k;
    int a;
    int l;
    int d;

    // Zgrupowane wartości a oraz l dla tej samej wartości d. Wektory te zostaną
    // później przekazane drugiemu algorytmowi.
    vector<int> a_d[T + 1];
    vector<int> l_d[T + 1];

    cin >> n >> k;

    for (int i = 0; i < k; i++)
    {
        cin >> a >> l >> d;

        if (d <= T)
        {
            // Zbieramy dane dla drugiego algorytmu...
            a_d[d].push_back(a);
            l_d[d].push_back(l);
        }
        // albo uruchamiamy pierwszy algorytm.
        else pojedynczo(a, l, d);
    }

    // Uruchamiamy drugi algorytm dla każdego d, ...
    for (int d = 1; d <= T; d++)
        // który miał choć jedno zapytanie na wejściu.
        if (a_d[d].size() > 0)
            zbiorowo(a_d[d], l_d[d], d, n);

    // Wypisujemy wynik
    for (int i = 1; i <= n; i++)
        cout << kontenery[i] << " ";
    cout << endl;

    return 0;
}
