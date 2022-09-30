#include <iostream>
#include <vector>

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
Zadanie składało się z dwóch części. W pierwszej należało zauważyć, że za każdym
razem gdy startował strajk w którymś mieście to sieć komunikacyjna kraju rozpada
się o dodatkowe v - 1 części, gdzie v to liczba sąsiadów tego miasta, w których
nie odbywają się strajki. Druga część zadania polega na sprytnym liczeniu tej
wartości.

Zacznijmy od rozwiązań nieoptymalnych.

Rozwiązanie nieoptymalne 1.

Każdy wierzchołek zapamiętuje ile ma sąsiadów, którzy niestrajkują. W takim
rozwiązaniu szybko jesteśmy w stanie obliczyć ilość części na które rozpada się
sięć komunikacyjna. Jednak potrzebujemy następnie wszystkim naszym sąsiadom
zmniejszyć licznik. Zatem potrzebujemy czasu liniowego na aktualizację tych
wartości. Otrzymujemy zatem algorytm o następującym czasie:

O(1) - obliczenie zapytania
O(n) - aktualizacja wartości

Daje nam to rozwiązanie działające w najgorszym razie w czasie O(nm).

Rozwiązanie nieoptymalne 2.

Zapamiętujemy jedynie informację o tym które wierzchołki strajkują a które nie
(na przykład w tablicy boolowskiej). Aby dla danego wierzchołka policzyć ile ma
sąsiadów, którzy nie strajkują, wystarczy przejrzeć sąsiadów i odczytać
z tablicy czy strajkują czy nie. Potrzebujemy zatem do tego czasu liniowego.
Jednakże aktualizacja samej tablicy odbywa się w czasie stałym

O(n) - obliczanie zapytania
O(1) - aktualizacja wartości

Daje nam to rozwiązanie działające w najgorszym razie w czasie O(nm).

Jeśli mamy do czynienia z sytuacją w której łatwo wpaść na dwa rozwiązania
z których jedna jest dobra w jednym aspekcie, a zła w drugiej a druga na odwrót,
to jest duża szansa na to, aby otrzymać rozwiązanie, które działa rozsądnie
w obu aspektach.

Widzimy, że w obu rozwiązaniach nieoptymalnych problemem są wierzchołki, które
mają wielu sąsiadów. Prawdą jest jednak, że takich wierzchołków jest niewiele.
Ustalmy sobie wartość K. Pomalujmy kolorem czerwonym wszystkie wierczhołki,
które mają co najmniej K sąsiadów. Są to owe wierzchołki problematyczne.
Będziemy te wierzchołki traktować w inny sposób niż wszystkie pozostałe.
Wierzchołków czerwonych nie może być więcej niż O(n / K).

Rozwiązanie 1.

Dla każdego wierzchołka czerwonego pamiętamy ile posiada on sąsiadów, którzy
niestrajkują. Każdy wierzchołek ponadto pamięta czy strajkuje czy nie. W jaki
sposób odpowiadamy na zapytania? Jeśli jesteśmy wierzchołkiem czerwonym to
dokładnie wiemy ile mamy sąsiadów, którzy nie strajkują. Jeśli nie jesteśmy to
musimy to policzyć, ale ponieważ nie jesteśmy to mamy mniej niż K sąsiadów.
Zatem operacja tą jesteśmy w stanie wykonać w czasie O(K). Niezależnie od tego
czy jesteśmy czerwoni czy nie, musimy przejść po wszystkich naszych czerwonych
sąsiadach i zaktualizować im liczbę niestrajkujących sąsiadów. Nie zajmie nam
to więcej czasu niż O(n / K) (bo tyle co najwyżej jest wszystkich czerwonych
wierzchołków.

O(K) - obliczanie zapytania
O(n / K) - aktualizacja wartości

To rozwiązanie zostało zaimplementowane w niniejszym pliku. Nie omieszkam jednak
skorzystać z okazji i przedstawić rozwiązanie alternatywne:

Rozwiązanie 2.

Każdy wierzchołek pamieta ile posiada nieczerwonych sąsiadów którzy
niestrajkują. Dodatkowo każdy czerwony wierzchołek pamięta czy strajkuje czy
nie. Aby odpowiedzieć na zapytanie, musimy przejść po wszystkich naszych
czerwonych sąsiadach i zobaczyć który z nich strajkuje czy nie. Dodając liczbę
strajkujących czerwonych sąsiadów do wcześniej spamiętanej ilości nieczerwonych
strajkujących sąsiadów - możemy odpowiedzieć na zapytanie. Jeśli chodzi o
aktualizację. Czerwone wierzchołki wystarczą, że zapamiętają czy strajkują czy
nie. Natomiast czarne muszą zaktualizować wartość wszystkich swoich sąsiadom.
Na szczęście jest ich nie więcej niż K.

O(n / K) - obliczanie zapytania
O(K) - aktualizacja wartości

Ostatecznie w rozwiązaniu 1 i 2 otrzymujemy złożoność O(m (n / K + K)).
Można udowodnić że najlepszą złożoność otrzymamy dla K = sqrt(n) (pierwiastek
z n). Wtedy nasza złożoność wynosi O(m sqrt(n)).

*/

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b, m, z, liczba_spojnych;

    const int K = 700; // ~ pierwiastek z 500 000
    vector<vector<int>> graf;
    vector<int> liczba_sasiadow;
    vector<bool> jest_czerwony;
    vector<bool> strajkuje;
    vector<vector<int>> czerwoni_sasiedzi;

    /* Wczytywanie grafu */
    cin >> n;

    graf.resize(n+1);

    for (int i = 0; i < n-1; i++)
    {
        cin >> a >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }

    /* Każdy wierzchołek zapamiętuje ile ma sąsiadów, którzy niestrajkują */
    liczba_sasiadow.resize(n+1);
    for (int i = 1; i <= n; i++)
        liczba_sasiadow[i] = graf[i].size();

    /* Zapisujemy, które wierzchołki są czerwone */
    jest_czerwony.resize(n+1);
    for (int i = 1; i <= n; i++)
        jest_czerwony[i] = (liczba_sasiadow[i] >= K);

    /* Tworzymy listę czerwonych sąsiadów */
    czerwoni_sasiedzi.resize(n+1);
    for (int i = 1; i <= n; i++)
        for (int j : graf[i])
            if (jest_czerwony[j])
                czerwoni_sasiedzi[i].push_back(j);

    /* Zapamiętujemy czy wierzchołek strajkuje czy nie */
    strajkuje.resize(n+1, false);

    /* Na początku mamy jedną spójną część */
    liczba_spojnych = 1;

    cin >> m;
    while (m--)
    {
        cin >> z; // Wczytujemy zapytanie

        if (z > 0) // Rozpoczyna się strajk
        {
            strajkuje[z] = true; // z rozpoczyna strajk

            // jeśli wierzchołek jest czerwony to mamy liczbę sąsiadów policzoną
            if (jest_czerwony[z]) //
                liczba_spojnych += liczba_sasiadow[z] - 1;
            // w przeciwnym razie musimy sprawdzić wszystkich naszych sąsiadów
            else
            {
                for (int j : graf[z])
                    if (not strajkuje[j])
                        liczba_spojnych++;
                liczba_spojnych--;
            }

            // aktualizujemy liczbę sąsiadów dla czerwonych wierzchołków
            for (int j : czerwoni_sasiedzi[z])
                liczba_sasiadow[j]--;
        }
        else // Kończy się strajk (analogicznie jak przypadek wyżej)
        {
            z = -z;

            strajkuje[z] = false;

            if (jest_czerwony[z])
                liczba_spojnych -= liczba_sasiadow[z] - 1;
            else
            {
                for (int j : graf[z])
                    if (not strajkuje[j])
                        liczba_spojnych--;
                liczba_spojnych++;
            }

            for (int j : czerwoni_sasiedzi[z])
                liczba_sasiadow[j]++;
        }

        // wypisujemy liczbę spójnych części na ekranie
        cout << liczba_spojnych << endl;
    }

    return 0;
}
