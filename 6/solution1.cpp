#include <cmath>
#include <iostream>

using namespace std;
#define size 4

int main()
{
    int times[size] = {48, 98, 90, 83};
    int dist[size] = {390, 1103, 1112, 1360};
    int product = 1;
    for (int i = 0; i < size; ++i)
    {
        int t = times[i];
        int s = dist[i];
        double delta = pow(t, 2) - 4 * -1 * -s;
        double x1 = (-t - sqrt(delta)) / -2;
        double x2 = (-t + sqrt(delta)) / -2;

        int start = ceil(min(x1, x2));
        int end = floor(max(x1, x2));
        if (start == min(x1, x2))
            ++start;
        if (end == max(x1, x2))
            --end;
        cout << start << " " << end << endl;
        product *= end - start + 1;
    }

    cout << product << endl;
    return 0;
}
