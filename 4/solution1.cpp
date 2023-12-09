#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool starts_with(string::iterator begin, string::iterator end, string word)
{
    for (auto it = word.begin(); it < word.end(); ++it)
        if (*it != *(begin + (it - word.begin())))
            return false;

    return true;
}

vector<string>
split(string::iterator begin, string::iterator end, string separator)
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
    int points = 0;
    string buff;
    while (getline(cin, buff))
    {
        unordered_map<string, int> mymap;
        int exp = -1;
        int before = points;
        long pos = buff.find(":");
        if (pos == string::npos)
        {
            cout << "\":\" not found" << endl;
            break;
        }

        vector<string> num_list
            = split(buff.begin() + pos + 1, buff.end(), "|");

        vector<string> winning_nums
            = split(num_list[0].begin(), num_list[0].end(), " ");
        for (auto s : winning_nums)
        {
            if (s.length() == 0 || !isdigit(s[0]))
                continue;

            mymap[s] = 0;
        }

        vector<string> got_nums
            = split(num_list[1].begin(), num_list[1].end(), " ");
        for (auto s : got_nums)
        {
            if (s.length() == 0 || !isdigit(s[0]))
                continue;

            unordered_map<string, int>::iterator found = mymap.find(s);
            if (found == mymap.end())
                continue;

            ++exp;
        }

        points += (exp > -1) * pow(2, exp);

        cout << "Diff: " << points - before << endl;
    }

    cout << "Points: " << points << endl;
    return 0;
}
