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
Popatrzmy na problem z innej perspektywy. Co jeśli kierowca byłby w stanie
sprzedać paliwo po cenie w jakim zostało ono kupione?

Zwróćmy uwagę, że dodanie takiego założenia nie zmienia sensu zadania, bo
sprzedanie paliwa w cenie w jakim ono zostało kupione jest tożsame z zakupem
mniejszej ilości paliwa na odpowiedniej stacji.

Algorytm teraz może wyglądać następująco:
Dla każdej stacji:
 - Niech c oznacza cenę paliwa na tej stacji
 - Sprzedaj całe paliwo w baku, droższe od c
 - Napełnij bak do pełna paliwem o koszcie c
 - Przejedź do następnej stacji zużywając najtańsze
   paliwo.

Po dojechaniu do ostatniej stacji:
 - Sprzedaj całe paliwo w baku

Przykład z treści zadania nie jest ciekawy.
Weźmy następujący, ciekawszy:
10
4
1 5
3 8
2 5
3 2

Na pierwszej stacji tankujemy do pełna (10 jednostek) bak benzyną o koszcie 1.
Zużywamy 5 jednostek paliwa aby dojechać do stacji drugiej.

Na drugiej stacji tankujemy do pełna (5 jednostek) bak benzyną o koszcie 3.
Zużywamy 5 jednostek paliwa o koszcie 1 i 3 jednostki paliwa o koscie 3.
https://www.youtube.com/watch?v=xu-WuJtOl0c
Na trzeciej stacji sprzedajemy 2 jednostki bezyny o koszcie 3 i tankujemy do
pełna (10 jednostek) paliwo o koszcie 2.
Zużywamy 5 jednostek paliwa aby dojechać do kolejnej stacji.

Na czwartej stacji tankujemy do pełna (5 jednostek) bak benzyną o koszcie 3.
Zużywamy 2 jednostki paliwa o koszcie 2 aby dojechać do stacji docelowej.

Spraedajemy 3 jednostki paliwa o kocie 3 i 5 jednostek paliwa o koszcie 3.

Koszt całej podróży wyniósł 33.
*/

int p; // pojemność baku
int n; // liczba stacji benzynowych
int koszt = 0; // sumaryczny koszt tankowań

// Do reprezentacji zawartości baku użyjemy kolejki w której możemy usuwać
// elementy zarówno z przodu jak i z tyłu.
const int max_n = 1e6; // maksymalna ilość stacji
int cena_paliwa_w_baku[max_n];
int ilosc_paliwa_w_baku[max_n];
int glowa = 0;
int ogon = 0;
int sumaryczna_ilosc_paliwa_w_baku = 0;
// Ponieważ paliwo będziemy dodawać z prawej strony - ceny paliw w kolejce
// będą ustawione w kolejności rosnącej.
// Więcej o tej kolejce można przeczytać na blogu:
//   https://krzysiek.how/pionek-na-planszy/
// W tej notce "bak" został zaimplementowany za pomocą kolejki dwustronnej
// deque.

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> p >> n;

    for (int i = 0; i < n; i++)
    {
        int c; // cena paliwa na stacji

        cin >> c;

        // Sprzedajemy paliwo droższe od c
        while (glowa < ogon and cena_paliwa_w_baku[ogon-1] > c)
        {
            ogon--;
            koszt -= cena_paliwa_w_baku[ogon] * ilosc_paliwa_w_baku[ogon];
            sumaryczna_ilosc_paliwa_w_baku -= ilosc_paliwa_w_baku[ogon];
        }

        // Napełnij bak do pełna
        cena_paliwa_w_baku[ogon] = c;
        ilosc_paliwa_w_baku[ogon] = p - sumaryczna_ilosc_paliwa_w_baku;
        sumaryczna_ilosc_paliwa_w_baku = p;
        koszt += cena_paliwa_w_baku[ogon] * ilosc_paliwa_w_baku[ogon];
        ogon++;

        // Przejedź do następnej stacji zużywając najtańsze paliwo
        int d; // odległość do następnej stacji

        cin >> d;

        sumaryczna_ilosc_paliwa_w_baku -= d;
        while (d > 0)
        {
            if (d >= ilosc_paliwa_w_baku[glowa])
            {
                d -= ilosc_paliwa_w_baku[glowa];
                glowa++;
            }
            else
            {
                ilosc_paliwa_w_baku[glowa] -= d;
                d = 0;
            }
        }
    }
    // Zwróć uwagę, że w każdym przebiegu pętli for dodajemy dokładnie jeden
    // element do naszej kolejki, a obie pętle while usuwają w każdej iteracji
    // jeden element. Ponieważ nie możemy usunąć więcej elementów niż dodaliśmy,
    // mamy tutaj sytuację z kosztem zamortyzowanym. Pętle while nie mogą
    // sumarycznie wykonać się więcej razy niż n (bo n to liczba elementów jaką
    // dodaliśmy na kolejkę). Zatem złożoność algorytmu to O(n).

    // Sprzedaj całe paliwo w baku
    while (glowa < ogon)
    {
        ogon--;
        koszt -= cena_paliwa_w_baku[ogon] * ilosc_paliwa_w_baku[ogon];
    }
    sumaryczna_ilosc_paliwa_w_baku = 0;

    cout << koszt << endl;

    return 0;
}
