#include <iostream>
#include <list>
#include <queue>

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
Do rozwiązania tego zadania było potrzebne następujące spostrzeżenie:

Jeśli wierzchołek nie jest izolowany i istnieje do niego ścieżka o długości p
to istnieje do niego również ścieżka o długości p+2 (z tego samego wierzchołka).

Wystarczy wziąć ścieżkę o długości p, a następnie z portu p wybrać się do
dowolnego portu sąsiadującego z p, a na koniec wrócić do p.

Zatem do rozwiązania tego zadania wystarczy dla każdej pary wierzchołków znaleźć
najkrótszą ścieżkę o długości parzystej i najkrótszą ścieżkę o długości
nieparzystej. Do tego celu zmodyfikujemy algorytm wyszukiwania wszerz (BFS).
Algorytm ten znajduje najkrótszą ścieżkę w grafie pomiędzy wierzchołkiem
startowym a każdym innym. Algorytm ma zabezpieczenie, dzięki któremu żaden
wierzchołek nie jest odwiedzany więcej niż raz. Zmienimy ten fragment w ten
sposób, aby algorytm odwiedzał każdy wierzchołek był odwiedzany dwa razy. Raz
wchodząc do wierzchołka ścieżką o długości parzystej a raz ścieżką o długości
nieparzystej.

Algorytm BFS musimy uruchomić dla każdego wierzchołka startowego. Musimy jeszcze
rozwiązać jeden problem. Jeśli uruchomimy n razy algorytm BFS, możemy mieć
problemy z limitem pamięci. Istnieją dwa rozwiązania tego problemu. W niniejszym
pliku zdecydowałem się na następujące rozwiązanie tego problemu. Najpierw
wczytujemy wszystkie zapytania. Następnie uruchamiamy jeden algorytm BFS dla
wierzchołka z numerem 1. Odpowiadamy na wszystkie zapytania dotyczące tego
wierzchołka. Powtarzamy ten proces dla każdego wierzchołka.
*/

list<int> graph[5001]; // Graf z treści zadania.
int result[5001][2]; // Wynik działania funkcji bfs.
                     // result[i][0] - najkrótsza parzysta ścieżka z wierzchołka
                     //                startowego do wierzchołka i
                     // result[i][1] - najkrótsza nieparzysta ścieżka
                     //                z wierzchołka startowego do wierzchołka i
                     // wartość zero w tablicy oznacza, że do wierzchołka nie da
                     // się dotrzeć. Najkrótsza ścieżka parzysta od wierzchołka
                     // startowego do niego samego wynosi 2 (0 w przypadku, gdy
                     // wierzchołek jest izolowany).

void bfs(int start_node, int n)
{
    // Zerujemy tablicę wynikową
    for (int i = 1; i <= n; i++)
        result[i][0] = result[i][1] = 0;

    queue<pair<int, int>> Q;

    Q.push(make_pair(start_node, 0));

    while (!Q.empty())
    {
        auto [node, parity] = Q.front(); // node - wierzchołek który obecnie
                                         // obsługujemy,
                                         // parity - parzystość ścieżki (0 / 1)
        Q.pop();

        for (int neighbour: graph[node])
            // Operacja 1 - parity zamienia 0 na 1 oraz 1 na 0:
            // Jeśli parity = 0 wtedy 1 - parity = 1 - 0 = 1
            // Jeśli parity = 1 wtedy 1 - parity = 1 - 1 = 0
            if (result[neighbour][1-parity] == 0)
            {
                result[neighbour][1-parity] = result[node][parity] + 1;
                Q.push(make_pair(neighbour, 1 - parity));
            }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Wczytywanie grafu.
    int n, m, k;

    cin >> n >> m >> k;

    for (int i = 0; i < m; i++)
    {
        int a, b;

        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // Wczytywanie zapytań
    int s[1000000];
    int t[1000000];
    int d[1000000];

    vector<int> indx[5001]; // indx[a] zawiera indeksy zapytań o przygodach
                            // zaczynających się w porcie a

    for (int i = 0; i < k; i++)
    {
        cin >> s[i] >> t[i] >> d[i];
        indx[s[i]].push_back(i);
    }

    bool answers[1000000] = {}; // Wyniki zapytań. {} inicjuje całą tablicę
                                // wartościami false.

    for (int i = 1; i <= n; i++) // Dla każdego portu,
        if (indx[i].size() > 0) // jeśli istniało przynajmniej jedno zapytanie
                                // zaczynające się w tym porcie,
        {
            bfs(i, n); // policz odległości od tego portu do każdego innego

            for (int j : indx[i]) // i dla każdego zapytania zaczynającego się
                                  // w tym porcie
            {
                // odczytaj odpowiedź.
                if (result[t[j]][d[j]%2] != 0 and result[t[j]][d[j]%2] <= d[j])
                    answers[j] = true;
            }
        }

    // Wypisz odpowiedzi na standardowe wyjście.
    for (int i = 0; i < k; i++)
        if (answers[i]) cout << "TAK" << endl;
        else cout << "NIE" << endl;

    return 0;
}
