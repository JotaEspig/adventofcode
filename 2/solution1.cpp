#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define MAX_R 12
#define MAX_G 13
#define MAX_B 14

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
    int count = 0;
    string buff = "";
    int id = 1;
    while (getline(cin, buff))
    {
        bool possible = true;
        string a = split(buff.begin(), buff.end(), ":")[1];
        vector<string> sets = split(a.begin(), a.end(), ";");
        for (string s : sets)
        {
            int r = 0, g = 0, b = 0;
            vector<string> colors = split(s.begin(), s.end(), ",");
            for (string c : colors)
            {
                stringstream ss{c};
                int num;
                string colorname;
                ss >> num;
                ss >> colorname;
                if (colorname == "red")
                    r = num;
                else if (colorname == "green")
                    g = num;
                else if (colorname == "blue")
                    b = num;
            }

            if (r > MAX_R || g > MAX_G || b > MAX_B)
            {
                possible = false;
                break;
            }
        }
        cout << a << " === " << possible << endl;
        count += possible * id;
        ++id;
    }
    cout << "Possíveis: " << count << endl;
    return 0;
}
