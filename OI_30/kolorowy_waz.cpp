#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int m, p, n;
    int mapa[2001][2001];
    string polecenie;

    cin >> m >> p >> n;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            mapa[i][j] = -1;

    for (int i = 0; i < p; i++)
    {
        int w, k, c;

        cin >> w >> k >> c;
        mapa[w][k] = c;
    }

    int pozycja_głowy[2001][2001];

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            pozycja_głowy[i][j] = -1;
    pozycja_głowy[1][1] = 0;

    int wąż_w = 1;
    int wąż_k = 1;
    int czas = 0;
    vector<int> wąż = {0};

    for (int i = 0; i < n; i++)
    {
        cin >> polecenie;

        if (polecenie == "Z")
        {
            int w, k;

            cin >> w >> k;

            int segment = czas - pozycja_głowy[w][k];

            if (segment < wąż.size())
                cout << wąż[wąż.size() - 1 - segment] << endl;
            else
                cout << -1 << endl;
        }
        else
        {
            if (polecenie == "G") wąż_w--;
            if (polecenie == "D") wąż_w++;
            if (polecenie == "L") wąż_k--;
            if (polecenie == "P") wąż_k++;

            if (mapa[wąż_w][wąż_k] != -1)
            {
                wąż.push_back(mapa[wąż_w][wąż_k]);
                mapa[wąż_w][wąż_k] = -1;
            }

            czas++;
            pozycja_głowy[wąż_w][wąż_k] = czas;
        }
    }


    return 0;
}
