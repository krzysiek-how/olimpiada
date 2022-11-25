#include <iostream>

using namespace std;

const int MAX = 3e5;

int main()
{
    int n, m, k;
    int ciag[MAX];
    int podciag[MAX];

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> ciag[i];
        ciag[i]--;
    }

    for (int i = 0; i < m; i++)
    {
        cin >> podciag[i];
        podciag[i]--;
    }

    int it = 0;
    int lastcolor[MAX];
    int prefix[MAX];

    for (int i = 0; i < k; i++)
        lastcolor[i] = -2;

    for (int i = 0; i < n; i++)
    {
        if (it < m and ciag[i] == podciag[it])
        {
            lastcolor[podciag[it]] = it;
            it++;
        }
        prefix[i] = lastcolor[ciag[i]];
    }

    int sufix[MAX+1];

    sufix[n] = 0;
    for (int i = n-1; i >= 0; i--)
    {
        sufix[i] = sufix[i+1];
        if (sufix[i] < m and ciag[i] == podciag[m-1-sufix[i]])
            sufix[i]++;
    }

    for (int i = 0; i < n; i++)
        if (prefix[i] + sufix[i+1] >= m-1)
            cout << "1 ";
        else
            cout << "0 ";
    cout << endl;

    return 0;
}
