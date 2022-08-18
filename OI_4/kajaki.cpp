#include <iostream>
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
Zadanie rozwiążemy w sposób zachłanny. W każdym kroku do kajaka wsadzamy
najcięższą osobę. Jeśli do tego kajaka możemy wsadzić jeszcze osobę
o najmniejszej wadze - to to robimy. Całość powtarzamy dopóki są jeszcze osoby,
których nie wsadziliśmy do kajaków.

Aby wykazać, że nasz algorytm działa poprawnie, wystarczy udowodnić poniższy
lemat:

Lemat: Istnieje rozwiązanie optymalne w którym najcięższa osoba jest w tym
samym kajaku co najlżejsza osoba, jeśli się z nią mieści lub sama w przeciwnym
przypadku.
Dowód. Jeśli najcięższa osoba nie mieści się z najlżejszą w jednym kajaku, to
nie mieści się ona również z żadną inną osobą. Ponieważ każda osoba musi się
znaleźć w jakimś kajaku, to osoba najcięższa musi być sama w kajaku.
Załóżmy zatem, że osoba najcięższa (oznaczmy jej wagę przez C) mieści się do
kajaka z osobą najlżejszą (oznaczmy jej wagę przez L). Zachodzi zatem:
  C + L <= w
Weźmy dowolne rozwiązanie optymalne. Jeśli w nim osoba najcięższa znajduje się
w jednym kajaku z osobą najlżejszą to dowód się kończy. Załóżmy zatem, że tak
nie jest. Powinniśmy w tym miejscu rozważyć 4 przypadki. Co jeśli w rozwiązaniu
optymalny osoba najcięższa jest sama, co jeśli jest w kajaku z kimś innym, co
jeśli osoba najlżejsza jest w kajaku sama oraz co jeśli jest w kajaku z kimś
innym. Zamiast tego oznaczmy przez X wagę osoby, która jest w kajaku z osobą
najcięższą i niech X = 0 jeśli osoba najcięższa płynie sama. Analogicznie niech
Y płynie z osobą najlżejszą. Zachodzi zatem:
  C + X <= w
  L + Y <= w
Twierdzę, że możemy przesadzić osoby L oraz Y i uzyskać rozwiązanie optymalne
(bo liczba kajaków się nie zmienia) w której osoba najlżejsza i najcięższa
są w tym samym kajaku. Jedyne co muszę pokazać to to, że X i Y mieszczą się
razem w kajaku. Zachodzi jednak:
  X + Y <= X + C <= w
Pierwsza nierówność zachodzi ponieważ C jest wagą najcięższej osoby - musi zatem
być cięższa niż Y, a druga nierówność wynika z faktu, że X oraz C były w tym
samym kajaku. Co kończy dowód.
*/

int main()
{
    const int max_n = 3e5; // Maksymalna liczba osób.
    int w, n;
    int T[max_n];

    // Wczytujemy dane.
    cin >> w >> n;
    for (int i = 0; i < n; i++)
        cin >> T[i];

    // Sortujemy dane, aby łatwiej było znajdować osoby najcięższe i najlżejsze.
    sort(T, T+n);

    int i = 0; // iterator dla osób najlżejszych
    int j = n-1; // iterator dla osób najcięższych
    int odpowiedz = 0; // liczba kajaków

    while (i <= j) // Dopóki są jeszcze osoby bez kajaka
    {
        odpowiedz++; // Do nowego kajaka wsadź,

        if (T[i] + T[j] <= w) // osobę najlżejszą jeśli się mieści
            i++;
        j--; // i osobę najcieższą niezależnie od warunku.
    }

    // Wypisz odpowiedź.
    cout << odpowiedz << endl;

    return 0;
}
