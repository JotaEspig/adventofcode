#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, pair<string, string>> map;

int solve(map mymap, string key, string instructions, int idx = 0)
{
    if (idx == instructions.length())
        idx = 0;
    char instr = instructions[idx];

    pair<string, string> found_pair = mymap[key];
    string found;
    if (instr == 'L')
        found = found_pair.first;
    else
        found = found_pair.second;

    if (found == "ZZZ")
        return 1;
    return 1 + solve(mymap, found, instructions, idx + 1);
}

int main()
{
    map mymap;
    string instructions, buff;

    getline(cin, instructions);

    getline(cin, buff);
    while (getline(cin, buff))
    {
        string key{buff.begin(), buff.begin() + 3};
        string first{buff.begin() + 7, buff.begin() + 10};
        string second{buff.begin() + 12, buff.begin() + 15};
        mymap[key] = {first, second};
    }

    cout << solve(mymap, "AAA", instructions) << endl;

    return 0;
}
