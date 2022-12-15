#include <bits/stdc++.h>
// Tymon Tumialis
using namespace std;
typedef long long ll;
constexpr int MAX_VAl = 200000;

struct best_choices
{
    ll cost = 0;
    int benefit = 0;
};

ll cost_of_move[MAX_VAl];
ll Height_of_element[MAX_VAl];
ll Right_dominos_which_falls[MAX_VAl];
ll Left_dominos_which_falls[MAX_VAl];
inline bool sort_vector(best_choices &lhs, best_choices &rhs)
{
    if (lhs.benefit > rhs.benefit)
        return true;
    if (lhs.benefit == rhs.benefit && lhs.cost < rhs.cost)
        return true;

    return false;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, h, h1, h2, ben = 1, res_to_left = 0, res_to_right = 0;
    best_choices b_ch;
    ll x, n1, n2, prev = 0, left_range = 0, index_left = 0, right_range = 0, right_index = 0, total_of_new_domins = 0;
    vector<best_choices> TO_add_left;
    vector<best_choices> To_add_right;
    cin >> n;
    vector<ll> Pref_sum_right(n);
    vector<ll> Pref_sum_left(n);
    // reading date
    for (int i = 0; i < MAX_VAl; i++)
    {
        Right_dominos_which_falls[i] = numeric_limits<ll>::max();
        Left_dominos_which_falls[i] = numeric_limits<ll>::max();
    }
    for (int i = 0; i < n; i++)
    {
        cin >> x >> h;

        Height_of_element[i] = h;
        Pref_sum_right[i] = x;
        if (i != 0)
            cost_of_move[i - 1] = x - prev;
        prev = x;
    }
    cin >> n1 >> h1 >> n2 >> h2;
    total_of_new_domins = n1 + n2;
    // Calculating Pref_sum
    for (int i = n - 2; i >= 0; i--)
        Pref_sum_left[i] = Pref_sum_left[i + 1] + cost_of_move[i];

    for (int i = 1; i < n; i++)
    {
        left_range = Pref_sum_left[i] + Height_of_element[i];
        auto itr = lower_bound(Pref_sum_left.begin(), Pref_sum_left.end(), left_range, greater<int>());
        itr--;
        index_left = itr - Pref_sum_left.begin();
        for (auto j = index_left; j < i; j++)
        {
            if (Left_dominos_which_falls[j] == 0)
                break;
            if (Pref_sum_left[j] - left_range > 0)
                Left_dominos_which_falls[j] = min(Pref_sum_left[j] - left_range, Left_dominos_which_falls[j]);
            else
                Left_dominos_which_falls[j] = 0;
        }
    }
    for (int i = n - 2; i >= 0; i--)
    {
        right_range = Pref_sum_right[i] + Height_of_element[i];
        auto itr = lower_bound(Pref_sum_right.begin(), Pref_sum_right.end(), right_range);
        right_index = itr - Pref_sum_right.begin();
        for (int j = right_index; j > i; j--)
        {
            if (Right_dominos_which_falls[j] == 0)
                break;
            if (Pref_sum_right[j] - right_range > 0)
                Right_dominos_which_falls[j] = min(Pref_sum_right[j] - right_range, Right_dominos_which_falls[j]);
            else
                Right_dominos_which_falls[j] = 0;
        }
    }
    // indexy są pokazują ile potrzeba żeby dany element się przewrócił !!!!
    ll cost = 0;
    for (int i = 1; i < n; i++)
    {
        if (Right_dominos_which_falls[i] != 0)
        {
            if (res_to_right == 0)
            {
                res_to_right = ben;
                cost = Right_dominos_which_falls[i];
            }
            else
            {
                b_ch.benefit = ben;
                b_ch.cost = cost;
                To_add_right.push_back(b_ch);
                cost = Right_dominos_which_falls[i];
            }

            ben = 0;
        }
        ben++;
    }
    ben = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        if (Left_dominos_which_falls[i] != 0)
        {
            if (res_to_left == 0)
            {
                res_to_left = ben;
                cost = Left_dominos_which_falls[i];
            }
            else
            {
                b_ch.benefit = ben;
                b_ch.cost = cost;
                cost = Left_dominos_which_falls[i];
                TO_add_left.push_back(b_ch);
            }
            ben = 0;
        }
        ben++;
    }
    // sortowanie które elementy które najlepiej wybrać
    sort(To_add_right.begin(), To_add_right.end(), sort_vector);
    sort(TO_add_left.begin(), TO_add_left.end(), sort_vector);
    ll mod = 0;
    for (int i = 0; i < To_add_right.size(); i++)
    {
        if (To_add_right[i].cost <= total_of_new_domins * h1)
        {
            res_to_right += To_add_right[i].benefit;
            mod = To_add_right[i].cost % h1;
            res_to_right += To_add_right[i].cost / h1;
            if (mod != 0)
            {
                res_to_right += 1;
                total_of_new_domins -= 1;
            }
            total_of_new_domins -= To_add_right[i].cost / h1;
        }
        if (total_of_new_domins == 0)
            break;
    }
    if (total_of_new_domins != 0)
        res_to_right += total_of_new_domins;
    total_of_new_domins = n1 + n2;
    for (int i = 0; i < TO_add_left.size(); i++)
    {
        if (TO_add_left[i].cost <= total_of_new_domins * h1)
        {
            res_to_left += To_add_right[i].benefit;
            mod = TO_add_left[i].cost % h1;
            res_to_left += TO_add_left[i].cost / h1;
            if (mod != 0)
            {
                res_to_left += 1;
                total_of_new_domins -= 1;
            }
            total_of_new_domins -= TO_add_left[i].cost / h1;
        }
        if (total_of_new_domins == 0)
            break;
    }
    if (total_of_new_domins != 0)
        res_to_left += total_of_new_domins;
    if (n == 1)
        res_to_left++;
    cout << max(res_to_left, res_to_right);
    return 0;
}