#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int get_value_in_line(string buff)
{
    string value_str = "";
    // find first
    for (auto c : buff)
    {
        if (isdigit(c))
        {
            value_str += c;
            break;
        }
    }
    for (auto it = buff.end() - 1; it >= buff.begin(); --it)
    {
        if (isdigit(*it))
        {
            value_str += *it;
            break;
        }
    }

    return stoi(value_str);
}

int main()
{
    long sum = 0;
    string buff;

    while (getline(cin, buff))
    {
        int a = get_value_in_line(buff);
        cout << buff << endl << a << endl;
        sum += a;
    }
    cout << sum << endl;
    return 0;
}
