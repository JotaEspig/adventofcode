#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool starts_with(string::iterator begin, string::iterator end, string word)
{
    for (auto it = word.begin(); it < word.end(); ++it)
        if (*it != *(begin + (it - word.begin())))
            return false;

    return true;
}

vector<string> split(string::iterator begin, string::iterator end, string separator)
{
    vector<string> v;
    long sep_len = separator.length();
    string buff = "";
    for (auto it = begin; it < end; ++it)
    {
        if (!starts_with(it, end, separator))
        {
            buff += *it;
            continue;
        }

        it += sep_len - 1;
        v.push_back(buff);
        buff = "";
    }
    v.push_back(buff);

    return v;
}

int main()
{
    int sum = 0;
    string buff = "";
    while (getline(cin, buff))
    {
        int r = 0, g = 0, b = 0;
        string a = split(buff.begin(), buff.end(), ":")[1];
        vector<string> sets = split(a.begin(), a.end(), ";");
        for (string s : sets)
        {
            vector<string> colors = split(s.begin(), s.end(), ",");
            for (string c : colors)
            {
                stringstream ss{c};
                int num;
                string colorname;
                ss >> num;
                ss >> colorname;
                if (colorname == "red" && num > r)
                    r = num;
                else if (colorname == "green" && num > g)
                    g = num;
                else if (colorname == "blue" && num > b)
                    b = num;
            }
        }

        cout << r * g * b << endl;
        sum += r * g * b;
    }
    cout << "Sum: " << sum << endl;
    return 0;
}
