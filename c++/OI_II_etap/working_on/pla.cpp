#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
struct distances_between
{
    ull licz = 0;
    int mian = 0;
    ull left_licznik = 0;
    int left_mian = 0;
    ull right_licznik = 0;
    int right_mian = 0;
};
void lower(pair<ull, int> &el)
{
    while (el.first % 2 == 0 && el.second != 1)
    {
        el.first /= 2;
        el.second /= 2;
    }
}
inline ull NWW(ull a, ull b) { return a * b / min(a, b); }
template <class distances_between>
struct myComp
{
    ull nww_d, nww_l, l_m, r_m, l_l, r_l;
    bool operator()(distances_between &lhs, distances_between &rhs)
    {
        nww_d = NWW(lhs.mian, rhs.mian);
        nww_l = NWW(lhs.left_mian, rhs.left_mian);
        l_m = nww_d / lhs.mian;
        r_m = nww_d / rhs.mian;
        l_l = nww_l / lhs.left_mian;
        r_l = nww_l / rhs.left_mian;
        if (lhs.licz * l_m < rhs.licz * r_m)
            return true;
        else if (lhs.licz * l_m == rhs.licz * r_m && lhs.left_licznik * l_l > rhs.left_licznik * r_l)
            return true;
        return false;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, X, z, k, N = 0, prev = 0, current = 0;
    cin >> n >> X >> z;
    //  wczytanie danych
    distances_between ds_b;
    distances_between ds_left;
    distances_between ds_right;
    pair<ull, int> res; // first licznik second mianownik
    ull nww_b_l, nww_b_r, l_m, b_m_1, r_m, b_m_2;
    priority_queue<distances_between, vector<distances_between>, myComp<distances_between>> pq;
    for (int i = 0; i < n; i++)
    {
        cin >> current;
        if (i != 0)
        {
            ds_b.licz = current - prev;
            ds_b.mian = 2;
            ds_b.left_licznik = prev;
            ds_b.left_mian = 1;
            ds_b.right_licznik = current;
            ds_b.right_mian = 1;
            pq.push(ds_b);
        }
        prev = current;
    }
    if (current != X)
    {
        ds_b.licz = X - current;
        ds_b.mian = 2;
        ds_b.left_licznik = current;
        ds_b.left_mian = 1;
        ds_b.right_licznik = 0;
        ds_b.right_mian = 1;
        pq.push(ds_b);
    }

    for (int i = 0; i < z; i++)
    {
        cin >> k;
        for (int j = 0; j < k - N; j++)
        {
            ds_b = pq.top();
            if (ds_b.right_licznik == 0)
            {
                res.first = X;
                res.second = 1;
                ds_right.left_licznik = ds_b.left_licznik;
                ds_right.left_mian = ds_b.left_mian;
                ds_right.right_licznik = X;
                ds_right.right_mian = 1;
                ds_right.licz = ds_b.licz;
                ds_right.mian = 2 * ds_b.mian;
                pq.push(ds_right);
            }
            else
            {
                ds_left.left_licznik = ds_b.left_licznik;
                ds_left.left_mian = ds_b.left_mian;
                ds_right.right_licznik = ds_b.right_licznik;
                ds_right.right_mian = ds_b.right_mian;
                nww_b_l = NWW(ds_left.left_mian, ds_b.mian); // wspólny mianownik punktów
                nww_b_r = NWW(ds_right.right_mian, ds_b.mian);
                // sprawdzenie ile razy trzeba pomnożyć licznik
                l_m = nww_b_l / ds_left.left_mian; // lewy
                b_m_1 = nww_b_l / ds_b.mian;
                //------------------------------//
                r_m = nww_b_r / ds_right.right_mian; // prawy
                b_m_2 = nww_b_r / ds_b.mian;
                //------------------------------// lewy
                ds_left.right_licznik = ds_left.left_licznik * l_m + ds_b.licz * b_m_1;
                ds_left.right_mian = ds_b.mian;
                ds_left.licz = ds_b.licz;
                ds_left.mian = ds_b.mian * 2;
                //--------------------------// prawy
                ds_right.left_licznik = ds_right.right_licznik * r_m - ds_b.licz * b_m_2;
                ds_right.left_mian = ds_b.mian;
                ds_right.licz = ds_b.licz;
                ds_right.mian = ds_b.mian * 2;
                //------------------------//
                pq.push(ds_left);
                pq.push(ds_right);
                res.first = ds_right.left_licznik;
                res.second = ds_right.left_mian;
            }
            pq.pop();
        }
        lower(res);
        cout << res.first << "/" << res.second << "\n";
        N = k;
    }
    return 0;
}