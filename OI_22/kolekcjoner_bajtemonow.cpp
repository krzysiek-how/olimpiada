#include "ckollib.h"

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
Główną ideą rozwiązania jest policzenie, ile kart każdego Bajtemona miał
Bajtazar (zanim podkradziono mu karty). Następnie sprawdzamy numer katalogowy
każdego z Bajtemonów i przedstawiamy go w systemie binarnym. Dla każdej pozycji
w systemie binarnym zliczamy ile kart miało jedynkę na tej pozycji. Jeśli liczba
ta jest podzielna przez liczbę kart (którą policzyliśmy na początku) to bit ten
nie wystąpił w liczbie katalogowej Bajtemona który został podkradziony. Jeśli
nie jest - to bit ten występuje w tej liczbie katalogowej.

Dla przykładu. Bajtazar ma 3 Bajtemony o numerach katalogowych: 10, 5 i 6.
Podkradziono mu 1 kartę o indeksie 5. Zapisujemy numery katalogowe w systemie
binarnym:
1 0 1 0
1 0 1 0
1 0 1 0
0 1 0 1
0 1 0 1
0 1 1 0
0 1 1 0
0 1 1 0
Liczymy ile każdy z bitów wystąpił:
3 5 6 2
Bity które nie są podzielne przez 3 to drugi i czwarty. Zatem numer katalogowy
skradzionego Bajtemona to 0 1 0 1 (czyli 5).

Pozostaje nam rozwiązać w jaki sposób policzyć ile kart każdego rodzaju
Bajtemona miał Bajtazar (przed podkradzeniem). W tym celu wybieramy dwa pierwsze
Bajtemony i zliczamy ich wystąpienia w całym ciągu. Mamy kilka sytuacji do
rozpatrzenia:
- Jeśli był tylko jeden Bajtemon to jest to Bajtemon podkradziony
- Jeśli jeden z tych dwóch Bajtemonów wystąpił rzadziej, to jest on podkradziony
- Jeśli oba Bajtemony wystąpiły tą samą liczbę razy - to jest to szukana wartość
Poniższy kod implementuje powyższe rozwiązanie.
*/

int main()
{
    int numer_karty = karta();

    // Wybieramy dwie pierwsze karty
    // i brutalnie spamiętujemy ich liczbę wystąpień
    int index_pierwszy = -1;
    int liczba_pierwszy = 0;
    int index_drugi = -1;
    int liczba_drugi = 0;

    // Spamiętujemy ile razy wystąpił każdy bit w numerach kart
    int bity[31] = {};

    while (numer_karty != 0)
    {
        // Jeśli jeszcze nie wybraliśmy karty do spamiętywania
        if (index_pierwszy == -1)
            index_pierwszy = numer_karty;
        else if (index_drugi == -1 and index_pierwszy != numer_karty)
            index_drugi = numer_karty;

        // Jeśli wczytana karta to ta, którą spamiętujemy
        if (numer_karty == index_pierwszy)
            liczba_pierwszy++;
        if (numer_karty == index_drugi)
            liczba_drugi++;

        // Spamiętujemy ile razy wystąpił każdy bit
        for (int i = 0; i < 31; i++)
        {
            if (numer_karty % 2 == 1)
                bity[i]++;
            numer_karty /= 2;
        }

        // Wczytujemy nową kartę
        numer_karty = karta();
    }

    // Sprawdzamy czy szczęśliwie nie zdarzyło się, że spamiętaliśmy
    // skradzioną kartę
    if (liczba_pierwszy < liczba_drugi or index_drugi == -1)
        odpowiedz(index_pierwszy);
    else if (liczba_pierwszy > liczba_drugi)
        odpowiedz(index_drugi);
    else
    {
        // Odczytujemy z tablicy bitów skradzioną liczbę
        int skradziona_karta = 0;
        int potega = 1;
        for (int i = 0; i < 31; i++)
        {
            if (bity[i] % liczba_pierwszy != 0)
                skradziona_karta += potega;
            potega *= 2;
        }

        odpowiedz(skradziona_karta);
    }

    return 0;
}
