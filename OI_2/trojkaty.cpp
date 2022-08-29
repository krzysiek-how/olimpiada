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
W dowolnym 45 elementowym multizbiorze liczb z przedziału [1; 1 000 000 000]
istnieje trójka z której można zbudować trójkąt. Multizbiór n kolejnych liczb
fibonacciego tworzy n elementowy multi zbiór w którym nie da się zbudować
trójkąta o minimalnym możliwym największym elemencie:
Zacznijmy od multizbioru {1, 1}. Nie możemy dodać do multizbioru liczby 1,
bo (1, 1, 1) tworzy trójkąt. Możemy dodać 2: {1, 1, 2}. Teraz nie możemy do
multi zbioru dodać 2, gdyż (1, 2, 2) tworzy trójkąt. Możemy za to dodać 3:
{1, 1, 2, 3}. Teraz do multizbioru nie możemy dodać ani 3 ani 4, gdyż (2, 3, 3)
oraz (2, 3, 4) tworzą trójkąt. Ogólnie - w każdym kroku nie możemy dodać do
multizbioru liczby mniejszej niż dwa największe elementy tego multizbioru.
45-tą liczbą Fibonacciego jest 1 134 903 170. Zatem dowolna liczba mniejsza
od miliarda sprawi, że w naszym multizbiorze utworzy się trójkąt.

Wiedząc, że wśród 45 elementów można znaleźć trójkąt - możemy wczytać jedynie
pierwsze 45 liczb ze standardowego wejścia i szukać wśród nich trójkąta.
Ponieważ elementów jest tak mało - możemy nawet sprawdzić wszystkie możliwe
trójki w czasie O(n^3).
*/

// Sprawdzamy czy trójka a, b, c tworzy trójkąt.
bool czy_trojkat(int a, int b, int c)
{
    if (a + b <= c) return false;
    if (a + c <= b) return false;
    if (b + c <= a) return false;
    return true;
}

int main()
{
    vector<int> v;

    // Wczytujemy liczby z wejścia aż znajdziemy zero lub aż wczytamy 45 liczb
    do
    {
        int n;

        cin >> n;

        v.push_back(n);
    } while(v.back() != 0 and v.size() < 45);

    // Usuwamy 0 z naszego wektora
    if (v.back() == 0) v.pop_back();

    // Brutalnie sprawdzamy wszystkie trójki i sprawdzamy czy tworzą one trójkąt
    for (int i = 0; i < v.size(); i++)
        for (int j = i + 1; j < v.size(); j++)
            for (int k = j + 1; k < v.size(); k++)
                if (czy_trojkat(v[i], v[j], v[k]))
                {
                    cout << v[i] << " " << v[j] << " " << v[k] << endl;
                    return 0; // Kończy program
                }

    // Jeśli nie znaleźliśmy takiej trójki - wypisujemy "NIE".
    cout << "NIE" << endl;

    return 0;
}
