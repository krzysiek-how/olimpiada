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
Zaczynamy od stworzeniu grafu, gdzie wierzchołkami jest wzrost żołnierzy,
a krawędź między dwoma wzrostami jest wtedy, gdy istnieje dwóch żołnierzy na tej
samej pozycji o tych wzrostach.

Zauważmy, że w tak stworzonym grafie, każdy wierzchołek jest stopnia co najwyżej
drugiego. Oznacza to, że graf składa się z rozłącznych cykli oraz ścieżek.

Wierzchołek będziemy nazywać zdublowanym jeśli dwóch żołnierzy o tym wzroście
stoi w tym samym szeregu.

Wierzchołek będizemy nazywać singletonem jeśli istnieje tylko jeden żołnierz
(licząc oba szeregi) o danym wzroście. Inaczej mówiąc - stopień singletona jest
równy jeden i singletony są końcami ścieżek w grafie.

W końcu zauważmy, że zarówno dla ścieżek jak i dla cykli, istnieją zawsze dwie
(sensowne) metody pozbycia się zdublowanych wierzchołków.
Rozważmy następującą ścieżkę:

O - O - X - O - X - O - O - O - X - O - O

Za pomocą X oznaczyliśmy wierzchołki zdublowane, natomiast za pomocą
O wierzhochłki pozostałe. Znak "-" oznacza krawędź pomiędzy wierzchołkami.
Mamy następujące dwie możliwości pozbycia się zdublowanych wierzchołków z grafu:

O - O - X = O = X - O - O - O - X = O = O
O = O = X - O - X = O = O = O = X - O - O

Za pomocą znaku "=" oznaczyłem krawędzie (a zatem pozycje żołnierzy), które
należy zamienić, aby na ścieżce przestały być zdublowane wierzchołki. To znaczy,
że jeśli cały graf składałby się tylko z tej ścieżki, to po zamianie żołnierzy
na tych pozycjach, uzyskalibyśmy ustawienie poprawne.

Krawędzie które należy zamienić, tworzą ścieżki łączące ze sobą dwa wierzchołki
zdublowane, bądź wierzchołek zdublowany z singletonem. Łatwo można wyznaczyć te
krawędzie, a następnie sprawdzić która z tych metod daje mniejszą liczbę
przestawień. Dla naszego przykładu, druga metoda wymaga przestawienia
6 żołnierzy (posiada 6 krawędzi), a metoda pierwsza tylko 4.

Obie te liczby możemy policzyć na przykład uruchamiając algorytm DFS na tej
ścieżce. Z obu możliwości, wybieramy tę, która wymaga mniejszej liczby
przestawień. Uruchamiamy DFS dla każdej ścieżki i każdego cyklu w grafie
i sumujemy wszystkie liczby ze sobą.
*/

const int max_wzrost = 1e5;
vector<int> graf[max_wzrost+1]; // lista krawędzi
int zdublowane[max_wzrost+1];   // liczba wystąpień w pierwszym szeregu
                                // pomniejszona o liczbę wystąpień w drugim
bool odwiedzone[max_wzrost+1];  // tablica odwiedzone dla algorytmu DFS

// Funkcja sprawdzająca, czy wierzchołek jest zdublowany
bool jest_zdublowany(int i)
{
    return (zdublowane[i] == 2 or zdublowane[i] == -2);
}

// Funkcja sprawdzająca, czy wierzchołek jest singletonem
bool jest_singletonem(int i)
{
    return (zdublowane[i] == 1 or zdublowane[i] == -1);
}

// Algorytm DFS.
// W zmiennej v1 zapiszemy liczbę krawędzi w pierwszej możliwości, a w zmiennej
// v2 liczbę krawędzi w drugiej możliwości (porównaj z przykładem powyżej).
void dfs(int start, int& v1, int& v2)
{
    // Dla każdego sąsiada wierzchołka start
    for (int sasiad : graf[start])
        // Jeśli wierzchołek nie był odwiedzony
        if (!odwiedzone[sasiad])
        {
            // Oznacz wierzchołek jako odwiedzony
            odwiedzone[sasiad] = true;
            if (zdublowane[start])
            {
                // Jeśli wierzchołek jest zdublowany - zwiększ v2 i zamień
                // miejscami v1 z v2
                v2++;
                dfs(sasiad, v2, v1);
            }
            else
            {
                // Jeśli wierzchołek nie jest zdublowany - zwiększ v1
                v1++;
                dfs(sasiad, v1, v2);
            }
        }
}

// Algorytm zwracający rozwiązanie dla naszego zadania
int rozwiazanie()
{
    int odpowiedz = 0;

    for (int i = 1; i <= max_wzrost; i++)
    {
        int v1 = 0;
        int v2 = 0;

        // Uruchom algorytm DFS dla każdego początku ścieżki
        if (!odwiedzone[i] and jest_singletonem(i))
        {
            odwiedzone[i] = true;
            dfs(i, v1, v2);
            odpowiedz += min(v1, v2); // wybierz lepsze rozwiązanie
        }
    }

    // Uruchom algorytm DFS dla ścieżek
    for (int i = 1; i <= max_wzrost; i++)
    {
        int v1 = 0;
        int v2 = 0;

        if (!odwiedzone[i])
        {
            dfs(i, v1, v2);
            odpowiedz += min(v1, v2); // wybierz lepsze rozwiązanie
        }
    }

    return odpowiedz; // zwróć wynik
}

int main()
{
    // Wczytanie danych
    int n;
    vector<int> x;
    vector<int> y;

    cin >> n;

    x.resize(n);
    y.resize(n);

    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 0; i < n; i++)
        cin >> y[i];

    // Zbudowanie grafu
    for (int i = 0; i < n; i++)
    {
        zdublowane[x[i]]++;
        zdublowane[y[i]]--;

        graf[x[i]].push_back(y[i]);
        graf[y[i]].push_back(x[i]);
    }

    // Wypisanie rozwiązania
    cout << rozwiazanie() << endl;

    return 0;
}
