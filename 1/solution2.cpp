#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> mymap{
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};

string get_num_by_letters(string::iterator begin, string::iterator end)
{
    string result = "";
    unsigned long len = end - begin;
    string check = "";
    for (auto it = begin; it < min(end, begin + 5); ++it)
    {
        if (result.size() == 1)
            break;
        check += *it;
        result = mymap[check];
    }
    return result;
}

int get_value_in_line(string buff)
{
    string value_str = "";
    // find first
    for (auto it = buff.begin(); it < buff.end(); ++it)
    {
        if (isdigit(*it))
            value_str += *it;
        else
            value_str += get_num_by_letters(it, buff.end());

        if (value_str.size() == 1)
            break;
    }
    // find last
    for (auto it = buff.end() - 1; it >= buff.begin(); --it)
    {
        if (isdigit(*it))
            value_str += *it;
        else
            value_str += get_num_by_letters(it, buff.end());

        if (value_str.size() == 2)
            break;
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
        cout << buff << endl
             << a << endl;
        sum += a;
    }
    cout << sum << endl;
    return 0;
}
