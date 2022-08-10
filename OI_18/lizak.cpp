#include <iostream>
#include <string>
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
Istnieje powszechnie znany algorytm rozwiązujący ogólniejszy problem. Mając daną
tablicę liczb naturalnych oraz pewną wartość, należy znaleźć taką spójną
podtablicę, której suma jest równa tej wartości.

Algorytm jest stosunkowo prosty. Będziemy rozważać przedział [l; r) który będzie
oznaczał podtablicę tab[l], tab[l+1], ..., tab[r-1]. Jeśli suma tej podtablicy
jest mniejsza od wartości to dokładamy element tab[r] (inkrementujemy zmienną
r - czyli przechodzimy do przedziału [l; r+1)). Jeśli suma jest mniejsza to
usuwamy tab[l] (inkrementujemy zmienną l - przechodzimy do przedziału [l+1; r)).
Ponieważ obie zmienne jedynie zwiększamy oraz obie zmienne nie mogą być większe
od n, to złożoność całego algorytmu wynosi O(n).

Uruchamiając ten algorytm m krotnie dla każdego zapytania, otrzymujemy algorytm
o złożoności O(nm), który to otrzymałby na olimpiadzie 16-24 pkt.
*/
pair<int, int> znajdz_przedzial(const vector<int>& tablica, int k)
{
    int l = 0, r = 0;
    // By nie liczyć za każdym razem sumy przedziału [l; r), trzymamy ją
    // w poniższej zmiennej
    int suma_przedzialu = 0;

    while (suma_przedzialu != k)
    {
        if (suma_przedzialu < k)
        {
            // Jeśli zmienna r wyszła poza zakres - oznacza to, że nie udało nam
            // się znaleźć żądanego przedziału. Zwracamy (-1, -1) na znak, że
            // szukanego przedziału nie ma.
            if (r == tablica.size())
                return make_pair(-1, -1);

            suma_przedzialu += tablica[r];
            r++;
        }
        else
        {
            suma_przedzialu -= tablica[l];
            l++;
        }
    }

    // Ponieważ inaczej reprezentujemy przedział niż w treści zadania - na
    // koniec musimy do l dodać 1.
    return make_pair(l + 1, r);
}

/*
Jednak nasze zadanie jest nieco prostsze. Segmenty lizaka mają wartość 1 albo 2.
Okazuje się, że upraszcza to znacznie nasz problem.

Zobaczmy jak powyższy algorytm zachowałby się, gdyby został on uruchomiony na
tablicy złożonej jedynie z jedynek i dwójek.

W pierwszym kroku algorytm zwiększa jedynie zmienną r. Czyni to dopóki wartość
zmiennej suma_przedzialu nie jest równa k albo k+1. Jeśli jest równa k to
znaleźliśmy przedział. Jeśli nie to przechodzimy do drugiego kroku.

W drugim kroku algorytm widzi, że suma przedziału jest zbyt duża, więc usuwa
jeden segment lizaka, przesuwając zmienną l w prawo. Jeśli usunięty segment
lizaka był waniliowy to suma przedziału równa się k i kończymy. Jeśli nie to
suma przedziału jest teraz równa k-1 i algorytm bierze następny segment lizaka
z prawej. Jeśli segment ten jest waniliowy - to suma przedziału jest równa k
i znaleźliśmy przedział. Jeśli nie to suma przedziału jest teraz równa k+1
i powtarzamy krok drugi.

Zauważmy, że oba kroki możemy zrobić w czasie stałym przy odpowiedniem
preprocessingu.

Jest jedynie liniowa ilość przedziałów [0; r) i każdy z nich może mieć sumę
nie większą od 2 milionów. Możemy przejrzeć je wszystkie i dla każdej
znalezionej sumy zapamiętać ile wynosiła wartość r.

Aby móc wykonać krok drugi w czasie stałym to dla każdego segmentu musimy
zapisać gdzie znajduje się najbliższy na prawo od niego segment waniliowy.
Na potrzeby zadania, każdy segment waniliowy będzie miał ustawioną wartość 1.
Każdy segment truskawkowy, który za prawego sąsiada ma segment waniliowy, będzie
miała wartość 2 i tak dalej.
*/

// Wartość k może maksymalnie mieć wartość 2 miliony (2e6), ale nam zdarzy się
// zapytać tablicę o wartość k+1. Stąd jej rozmiar musi wynosić 2e6 + 2.
// Wypełniamy ją na początku wartościami -1, które będą oznaczać, że nie
// istnieje przedział [0; r) o takiej sumie.
vector<int> indeks_prefiksu_o_zadanej_sumie(2e6 + 2, -1);
vector<int> gdzie_na_prawo_wanilia(1e6 + 1);

void preprocessing(const string& lizak)
{
    // Liczymy tablicę dla pierwszego kroku.
    int suma = 0;

    for (int i = 0; i < lizak.size(); i++)
    {
        if (lizak[i] == 'T') suma += 2;
        else suma++;

        // Policzona suma dotyczy przedziału [0; i]. Skoro chcemy mieć przedział
        // postaci [0; r) musimy dodać jeden.
        indeks_prefiksu_o_zadanej_sumie[suma] = i + 1;
    }

    // Liczymy tablicę dla drugiego kroku
    int val = 1e6; // Jakaś duża wartość, która będzie oznaczać, że na prawo nie
                   // ma segmentu waniliowego.

    gdzie_na_prawo_wanilia[lizak.size()] = val;
    for (int i = lizak.size()-1; i >= 0; i--)
    {
        val++;
        if (lizak[i] == 'W')
            val = 1;
        gdzie_na_prawo_wanilia[i] = val;
    }
}

// Łączymy wszystko, tworząc zapytanie w czasie stałym.
pair<int, int> znajdz_przedzial(int k, int rozmiar_lizaka)
{
        if (indeks_prefiksu_o_zadanej_sumie[k] != -1)
            // Istnieje przedział [0; r) o zadanej sumie.
            return make_pair(1, indeks_prefiksu_o_zadanej_sumie[k]);
        else if (indeks_prefiksu_o_zadanej_sumie[k+1] == -1)
            // Sytuacja w której żądana wartość jest większa od całego lizaka.
            return make_pair(-1, -1);
        else
        {
            // Sytuacja w której musimy wykonać oba kroki.
            int left = 0;
            int right = indeks_prefiksu_o_zadanej_sumie[k+1];

            int wanilia_od_lewego_konca = gdzie_na_prawo_wanilia[left];
            int wanilia_od_prawego_konca = gdzie_na_prawo_wanilia[right];

            // Sprawdzamy czy lewy koniec czy prawy koniec szybciej trafi na
            // segment waniliowy.
            if (wanilia_od_lewego_konca <= wanilia_od_prawego_konca)
            {
                left += wanilia_od_lewego_konca;
                right += wanilia_od_lewego_konca-1;
            }
            else
            {
                left += wanilia_od_prawego_konca;
                right += wanilia_od_prawego_konca;
            }

            // Na końcu sprawdzamy czy otrzymany wynik nie wykroczył poza
            // tablicę.
            if (right > rozmiar_lizaka)
                return make_pair(-1, -1);
            else
                // Tak samo jak w pierwszym algorytmie. Ponieważ w treści
                // zadania inaczej zażyczono sobie format przedziału - musimy
                // dodać 1 do lewego końca.
                return make_pair(left + 1, right);
        }
}

// W książce "Przygody Bajtazara. 25 lat olimpiady informatycznej" przedstawione
// zostało inne, prostsze rozwiązanie tego zadania; jednakże moim zdaniem
// trudniejsze do wymyślenia. Moje rozwiązanie wymaga przyjrzenia się w jaki
// sposób działa znane rozwiązanie i przepisanie go aby działało w czasie
// stałym. Tym niemniej polecam zapoznanie się z rozwiązaniem opisanym
// w książce.

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Wczytywanie danych
    int n, m;
    string lizak;
    vector<int> zapytania;

    cin >> n >> m >> lizak;

    zapytania.resize(m);

    for (int i = 0; i < m; i++)
        cin >> zapytania[i];

    // Obliczenia
    preprocessing(lizak);

    for (int i = 0; i < m; i++)
    {
        pair <int, int> wynik;

        wynik = znajdz_przedzial(zapytania[i], n);

        if (wynik.first == -1)
            cout << "NIE" << endl;
        else
            cout << wynik.first << " " << wynik.second << endl;
    }

    // Poniżej zostawiam kod, jeśli ktoś chciałby uruchomić algorytm O(n * m)
    /*
    vector<int> cena_segmentow_lizaka;

    cena_segmentow_lizaka.resize(lizak.size(), 1);

    for (int i = 0; i < lizak.size(); i++)
        if (lizak[i] == 'T')
            cena_segmentow_lizaka[i] = 2;

    for (int i = 0; i < m; i++)
    {
        pair<int, int> wynik;

        wynik = znajdz_przedzial(cena_segmentow_lizaka, zapytania[i]);

        if (wynik.first == -1)
            cout << "NIE" << endl;
        else
            cout << wynik.first << " " << wynik.second << endl;
    }
    */

    return 0;
}
