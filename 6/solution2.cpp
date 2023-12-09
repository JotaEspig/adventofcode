#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    long t = 48989083;
    long s = 390110311121360;
    double delta = pow(t, 2) - 4 * -1 * -s;
    double x1 = (-t - sqrt(delta)) / -2;
    double x2 = (-t + sqrt(delta)) / -2;

    long start = ceil(min(x1, x2));
    long end = floor(max(x1, x2));
    if (start == min(x1, x2))
        ++start;
    if (end == max(x1, x2))
        --end;

    cout << start << " " << end << endl;

    long product = end - start + 1;

    cout << product << endl;
    return 0;
}
