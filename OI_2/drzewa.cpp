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
Cały pomysł na rozwiązanie tego zadania opiera się na spostrzeżeniu, że
w algorytmie przeszukiwania w głąb odwiedzamy liście w kolejności od lewej do
prawej - czyli w takiej samej kolejności w jakiej podane są głębokości tych
liści w danych wejściowych.

Do rozwiązania tego zadania wystarczy jedno przejście dfs całego drzewa. My
jednak dokonamy trzech, aby lepiej przedstawić jaka idea przyświeca każdemu
z nich (w ten sposób rozwiązanie całego zadania będzie łatwiejsze do
zrozumienia). Czytelnik może spróbować przepisać rozwiązanie tak aby korzystało
tylko z jednego przejścia dfs.

Zacznijmy od sprawdzenia czy dane wejściowe w ogóle przedstawiają poprawne
drzewo binarne. Każde wywołanie dfs będzie pamiętało wysokość na którym się
znajduje. Jeśli wysokość ta odpowiada temu z wejścia, oznacza to, że trafiliśmy
do liścia. Kończymy zatem to wywołanie rekurencyjne dfs i wracamy do ojca. Jeśli
nasza wysokość jest mniejsza od tego z wejścia, wykonujemy dwa wywołania
rekurencyjne - dla naszego lewego i prawego syna. Jeśli wysokość jest większa od
wysokości z wejścia - oznacza to sytuację niemożliwą, zatem zwracamy w tym
miejscu -1. Musimy jeszcze sprawdzić czy w żadnym momencie nie brakło nam liczb
z wejścia i czy na końcu zużyliśmy wszystkie liczby. Aby sprawdzić to drugie,
nasza funkcja zwróci ile elementów wykorzystała z wejścia. W funkcji main
sprawdzimy czy były to wszystkie liczby.

Do napisania funkcji użyjemy zmiennej statycznej it - iteratora po wejściu.
Zmienna statyczna charakteryzuje się tym, że jest tylko jedna dla całej funkcji
i jej wartość nie zmienia się po zakończeniu funkcji. Działa zatem podobnie jak
zmienna globalna (z wyjątkiem, że nie jest widoczna dla innych funkcji). Nie
chciałem używać zmiennej globalnej w tym przypadku bo każda z trzech funkcji
dfs będzie miała swój własny iterator.
*/

int czy_poprawny(const vector<int>& wejscie, int glebokosc = 0)
{
    static int it = 0;

    // Jeśli skończyły się nam liczby z wejścia, lub wejście mówi że następny
    // liść powinien być na wyższej wysokości niż obecnie jesteśmy - zgłoś błąd.
    if (it == wejscie.size() or wejscie[it] < glebokosc)
        return -1;

    // Jeśli jesteśmy na tej samej głebokości co wartość z wejścia to zwiększ
    // wartość iteratora i zwróć jego wartość,
    if (wejscie[it] == glebokosc)
    {
        it++;
        return it;
    }

    // W przeciwnym przypadku jesteśmy na wyższej wysokości niż następny liść.
    // Wywołujemy zatem się dwukrotnie (dla lewego i prawego syna). Jeśli
    // którykolwiek z nich zwrócił błąd - propagujemy błąd wyżej. W przeciwnym
    // przypadku zwracamy wartość iteratora.
    if (czy_poprawny(wejscie, glebokosc+1) == -1 or
        czy_poprawny(wejscie, glebokosc+1) == -1)
        return -1;
    return it;
}

/*
Do policzenia zapisu genealogicznego, potrzebujemy zapamiętać numer wierzchołka
w którym się znajdujemy, oraz numer naszego ojca. Odpowiednie wartości wrzucamy
do wektora.

Przejście dfsem wygląda analogicznie jak w powyższym algorytmie z tą różnicą, że
teraz nie sprawdzamy już czy wejście jest poprawne.
*/

void zapis_genealogiczny(const vector<int>& wejscie,
                         vector<int>& wyjscie,
                         int glebokosc = 0,
                         int ojciec = 0)
{
    static int it = 0;
    static int numer_wierzcholka = 1;

    // Potrzebujemy zapamiętać numer wierzchołka, którym jesteśmy, gdyż zmienna
    // numer_wierzcholka ulegnie modyfikacji przy wywołaniu rekurencyjnym.
    int moj_numer = numer_wierzcholka;
    numer_wierzcholka++;

    // Zapamiętujemy, kto był naszym ojcem.
    wyjscie.push_back(ojciec);

    // Jeśli jesteśmy liściem to zwiększamy iterator i kończymy.
    if (wejscie[it] == glebokosc)
    {
        it++;
        return;
    }

    // W przeciwnym przypadku wywołujemy się rekurencyjnie dla lewego i prawego
    // syna.
    zapis_genealogiczny(wejscie, wyjscie, glebokosc+1, moj_numer);
    zapis_genealogiczny(wejscie, wyjscie, glebokosc+1, moj_numer);
}

/*
Zapis nawiasowy jest jeszcze prostszy. Gdy jesteśmy liściem, dodajemy do stringa
"()". Gdy nie jesteśmy liściem to dodajemy "(", wywołujemy się rekurencyjnie
i na końcu dodajemy ")".
*/

void zapis_nawiasowy(const vector<int>& wejscie,
                     string& wyjscie,
                     int glebokosc = 0)
{
    static int it = 0;

    if (wejscie[it] == glebokosc)
    {
        wyjscie.push_back('(');
        wyjscie.push_back(')');

        it++;

        return;
    }

    wyjscie.push_back('(');
    zapis_nawiasowy(wejscie, wyjscie, glebokosc+1);
    zapis_nawiasowy(wejscie, wyjscie, glebokosc+1);
    wyjscie.push_back(')');
}

int main()
{
    // Wczytywanie danych wejściowych.
    int N;
    vector<int> poziomowy;

    cin >> N;

    poziomowy.resize(N);
    for (int i = 0; i < N; i++)
        cin >> poziomowy[i];

    // Sprawdzamy czy zapis jest poprawny.
    if (czy_poprawny(poziomowy) != N)
    {
        cout << "NIE" << endl;
        return 0;
    }

    // Liczymy i wyświetlamy zapis genealogiczny.
    vector<int> genealogiczny;

    zapis_genealogiczny(poziomowy, genealogiczny);

    for (auto el: genealogiczny)
        cout << el << " ";
    cout << endl;

    // Liczymy i wyświetlamy zapis nawiasowy.
    string nawiasowy;

    zapis_nawiasowy(poziomowy, nawiasowy);

    cout << nawiasowy << endl;

    return 0;
}
