#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, H;
    string nawiasowanie;

    cin >> n >> H >> nawiasowanie;

    int glebokosc = 0;
    int liczba_zmian = 0;

    for (int i = 0; i < n; i++)
    {
        if (nawiasowanie[i] == '(' and glebokosc == H)
        {
            nawiasowanie[i] = ')';
            liczba_zmian++;
        }
        else if (nawiasowanie[i] == ')' and glebokosc == 0)
        {
            nawiasowanie[i] = '(';
            liczba_zmian++;
        }

        if (nawiasowanie[i] == '(')
            glebokosc++;
        else
            glebokosc--;
    }

    cout << liczba_zmian << endl;

    return 0;
}
