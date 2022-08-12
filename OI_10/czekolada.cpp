#include <iostream>
#include <vector>
#include <algorithm>

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
Intuicyjnie widzimy, że jeśli koszt pewnej linii jest wysoki to lepiej jest
przełamać ją wcześniej, bo w innym wypadku będziemy musieli dzielić wzdłuż tej
linii wielokrotnie. Okazuje się, że podejście zachłanna w którym w każdym kroku
łamiemy najdroższą linię - jest rozwiązaniem poprawnym. Dowód tego faktu jest
dość techniczny i nie będę tu go przedstawiał. Dowód znajduje się między innymi
w niebieskiej książeczce dostępnej na stronie:

  https://www.oi.edu.pl/l/10oi_ksiazeczka/

Aby obliczyć najmniejszy koszt podziału czekolady, tworzymy dwie tablice.
Jedną dla liń pionowych i drugą dla liń poziomych. Do każdej z nich wstawiamy
wartość -1, która będzie służyła jako wartownik. Dla tych osób, które jeszcze
nie wiedzą - wartownicy są to specjalne elementy, które upraszają nam
implementację różnych algorytmów. W naszym przypadku jest to sytuacja w której
jedna z tablic będzie miała jeszcze elementy, a druga już nie. Normalnie
w takiej sytuacji dokłada się dwa kawałki kodu, które obsługują ten przypadek
(jeden kawałek gdy tablica poziome się skończyła i drugi kawałek gdy tablica
pionowe się skończyła). Dzięki zastosowaniu wartowników, tych fragmentów kodu
nie trzeba umieszczać, gdyż gdy jedna z tablic się skończy, to tak na prawdę
się nie kończy, gdyż zostaje właśnie ten jeden element - wartownik. Dzięki niemu
w instrukcji warunkowej w pętli while nie wychodzimy poza tablicję i wynik
porównania jest taki, jaki byśmy chcieli aby był.

W następnym kroku sortujemy elementy w porządku nierosnącym. W kodzie
zrealizowaliśmy to po prostu korzystając z funkcji sort, a następnie odwracając
całą zawartość tablicy. Następnie przechodzimy po obu tablicach korzystając
z dwóch iteratorów (po jednym dla każdej tablicy). Następnie sprawdzamy, który
z elementów tablic jest większy. Przypomina to algorytm scalania dwóch
posortowanych tablic. Ponieważ iteratory liczą również ile dokonaliśmy przełamań
pionowych oraz poziomych, możemy z nich skorzystać do policzenia ile kosztuje
przełamanie całej linii poziomej i pionowej. Mówiąc dokładniej: przełamanie
linii pionowej jest równe kosztowi tej linii przemnożonemu przez ilość łamań
poziomych plus jeden.

Wszystkie te koszty sumujemy do zmiennej wynik i wyświetlamy na ekranie.
*/

int main()
{
    // Wczytywanie danych.
    int n, m;
    vector<int> pionowe;
    vector<int> poziome;

    cin >> n >> m;
    pionowe.resize(n);
    poziome.resize(m);

    for (int i = 0; i < n-1; i++)
        cin >> pionowe[i];

    for (int i = 0; i < m-1; i++)
        cin >> poziome[i];

    // Wstawiamy wartowników.
    pionowe[n-1] = -1;
    poziome[m-1] = -1;

    // Sortujemy nierosnąco obie tablice
    sort(pionowe.begin(), pionowe.end());
    sort(poziome.begin(), poziome.end());

    reverse(pionowe.begin(), pionowe.end());
    reverse(poziome.begin(), poziome.end());

    // Obliczamy koszt optymalnego łamania czekolady.
    int wynik = 0; // Optymalny koszt łamania czekolady.
    int iPion = 0; // Iterator tablicy pionowe i zarazem licznik łamań pionowych
    int iPoziom = 0; // j.w. dla tablicy poziome

    while (iPion < n-1 or iPoziom < m-1)
    {
        if (pionowe[iPion] > poziome[iPoziom]) // Wybieramy droższą linię
        {
            wynik += pionowe[iPion] * (iPoziom + 1);
            iPion++;
        }
        else
        {
            wynik += poziome[iPoziom] * (iPion + 1);
            iPoziom++;
        }
    }

    // Wypisujemy wynik
    cout << wynik << endl;

    return 0;
}
