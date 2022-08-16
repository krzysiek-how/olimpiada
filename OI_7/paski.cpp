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
Autorzy rozwiązania tego zadania w niebieskiej książeczce nazwali to zadanie
"prawdopodobnie jednym z najtrudniejszych zadań w historii Olimpiady". W tym
pliku pokaże w jaki sposób można łatwo rozwiązać to zadanie korzystając
z liczb Sprague'a-Grandy'ego. Nie będę tutaj przedstawiał całego wykładu na
temat tych liczb (to jest materiał na bloga), ale szybko przypomnę najważniejsze
informacje na temat tych liczb.

Liczby Sprague'a-Grandy'ego dotyczą gier, które spełniają następujące własności:
 - w każdej chwilii gracze mogą wykonać dokładnie te same ruchy
 - przegrywa gracz, który nie może wykonać ruchu
 - w każdej pozycji można wykonać jedynie skończenie wiele ruchów

Każdej pozycji w grze przypisujemy następującą liczbę naturalną  (zwaną liczbą
Sprague'a-Grundy'ego):
 - jeśli z tej pozycji nie można wykonać żadnego ruchu to przypisujemy jej
   wartość 0,
 - w przeciwnym przypadku niech V będzie zbiorem liczb Sprague'a-Grundy'ego
   wszystkich pozycji do których można dojść po wykonaniu jednego ruchu z tej
   pozycji; nadejemy jej wartość mex(V).

Funkcja mex (od ang. minimum excluded) oznacza najmniejszą liczbę naturalną nie
występującą w V. Dla przykładu:
  mex({1, 2, 5}) = 0
  mex({0, 1, 4, 5}) = 2
  mex({0, 1, 2, 3}) = 4

Do rozwiązania naszego zadania potrzebujemy jeszcze lematu i twierdzenia:

Lemat (łatwiejszy): Dla danej pozycji w grze, gracz pierwszy ma strategię
wygrywającą wtedy i tylko wtedy gdy jej liczba Sprague'a-Grundy'ego jest różna
od zera.

Weźmy dowolne dwie gry spełniające własności powyżej. Utwórzmy nową grę
w następujący sposób. Gracze będą grać w obie gry równocześnie. W każdym kroku
gracz może wybrać w której grze chce wykonać ruch i wykonuje go w tej grze, po
czym tura przechodzi na drugiego gracza.

Twierdzenie (trudniejsze): W tak utworzonej grze, liczba Sprague'a-Grundy'ego
jest równa xorowi liczb Sprague'a-Grundy'ego obu pozycji dla odpowiednich gier.
Twierdzenie to uogólnia się na dowolną, skończoną liczbę gier.

W grze w paski. Jeśli mamy pasek o długości 30 i przykryjemy go paskiem
o długości 5, możemy otrzymać dwa paski o długości 12 i 13. Wtedy gracze grają
w grę w której do wyboru mają dwa paski i tylko na jednym z nich mogą wykonać
ruch. Jest to gra z naszego lematu! Zatem aby policzyć liczbę Sprague'a-
-Grundy'ego dla takiej gry wystarczą nam liczby dla gry z paskiem 12 i z paskiem
13.

Pomysł na to zadanie jest następujące. Dla każdej liczby od 0 do 1000 liczymy
liczbę Sprague'a-Grundy'ego dla paska o takiej długości. Dla paska o długości i
patrzymy na wszystkie możliwe pozycje do jakich można przejść i sprawdzamy ich
liczby. Jeśli w wyniku takiego ruchu, pasek podzieliliśmy na dwie części,
korzystamy z twierdzenia i xorujemy liczby dla powstałych pasków.

Dla danej długości paska odpowiadamy czy gracz pierwszy ma strategię wygrywającą
zgodnie z powyższym lematem.
*/

// Funkcja liczącą mex (minimum excluded) dla wartości z wektora.
int mex(vector<int> values)
{
    int answer = 0;
    int iterator = 0;

    // sortujemy wartości w wektorze
    sort(values.begin(), values.end());

    // jeśli w wektorze znajduje się wartość answer
    while (iterator < values.size() and values[iterator] == answer)
    {
        // przechodzimy iteratorem za wszystkie elementy równe answer
        while (iterator < values.size() and values[iterator] == answer)
            iterator++;
        // zwiększamy answer o 1
        answer++;
    }

    return answer;
}

int main()
{
    int l[3]; // długości kolorowych pasków

    cin >> l[0] >> l[1] >> l[2];

    int SG[1001]; // SG[i] - liczba Sprague'a-Grundy'ego dla paska o długości i

    SG[0] = 0;

    for (int i = 1; i <= 1000; i++)
    {
        vector<int> moves; // liczby Sprague'a-Grundy'ego dla pozycji powstałych
                           // po pojedynczym ruchu z paska o długości i

        for (int j = 0; j < 3; j++) // używamy paska o kolorze j
            for (int k = 0; i - k - l[j] >= 0; k++)
                // Podzieliliśmy pasek na paski o długości k oraz i - k - l[j].
                // Być może jeden z tych pasków jest o długości zero.
                // Zgodnie z twierdzeniem, xorujemy liczby dla tych pasków.
                moves.push_back(SG[k] ^ SG[i - k - l[j]]);

        // Liczba Sprague'a-Grundy'ego to mex policzonych wartości
        SG[i] = mex(moves);
    }

    int m, p;

    cin >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> p;

        // Dla każdego zapytania p, odpowiadamy zgodnie z lematem.
        if (SG[p] == 0) cout << 2 << endl;
        else cout << 1 << endl;
    }

    return 0;
}
