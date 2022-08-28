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
Sekretem do rozwiązania tego zadania, jest zliczenie trójkątów wielobarwnych,
wielobarwnych, aby otrzymać liczbę trójkątów jednobarwnych.

Liczbę trójkątów wielobarwnych możemy policzyć następująco. Jeśli z pewnego
wierzchołka wychodzi a krawędzi czerwonych i b krawędzi czarnych to biorąc
dowolną czerwoną krawędź i dowolną czarną krawędź, znaleźliśmy trójkąt
wielobarwny (niezależnie od tego jakiego koloru jest trzecia krawędź). Zatem
w tym wierzchołku znaleźliśmy przynajmniej a razy b różnych trójkątów
wielobarwnych. Robimy to dla każdego wierzchołka a następnie sumujemy trójkąty.

Każdy trójkąt wielobarwny zliczyliśmy dokładnie dwukrotnie. Weźmy dowolny
trójkąt wielobarwny i oznaczmy jego wierzchołki jako a, b i c. Bez straty
ogólności załóżmy, że krawędź a-b jest czerwona, a krawędzie a-c i b-c są
czarne. Wtedy ten trójkąt zliczyliśmy gdy zliczaliśmy trójkąty z wierzchołka a
i trójkąty z wierzchołka b.

Wszystkich trójkątów jest "n po 3" (z n wierzchołków wybieramy trzy) czyli
inaczej n * (n-1) * (n-2) / 6.
*/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    int czerwone[1001] = {}; // czerwone[i] - liczba czerwonych krawędzi
                             // wychodząca z wierzchołka i
    
    cin >> n >> m;
    
    for (int i = 0; i < m; i++)
    {
        int p, k;
        
        cin >> p >> k;
        czerwone[p]++;
        czerwone[k]++;
    }
    
    int wielobarwne = 0;
    
    for (int i = 1; i <= n; i++)
        // Liczba czarnych wierzchołków jest równa (n - 1 - czerwone[i]).
        wielobarwne += (czerwone[i] * (n - 1 - czerwone[i]));
    
    wielobarwne /= 2;
    
    cout << n * (n-1) * (n-2) / 6 - wielobarwne << endl;
    
    return 0;
}
