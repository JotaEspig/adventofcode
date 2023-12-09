#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> saved_cards;

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

int points_in_card(vector<string> lines, int idx)
{
    if (idx >= lines.size())
        return 0;

    auto found = saved_cards.find(idx);
    if (found != saved_cards.end())
        return found->second;

    int points = 1;
    int extra_cards = 0;

    unordered_map<string, int> mymap;
    string curr_s = lines[idx];

    long pos = curr_s.find(":");
    if (pos == string::npos)
    {
        cout << "\":\" not found" << endl;
        return 0;
    }

    vector<string> num_list
        = split(curr_s.begin() + pos + 1, curr_s.end(), "|");

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

        ++extra_cards;
    }

    for (int i = idx + 1; i < idx + extra_cards + 1; ++i)
        points += points_in_card(lines, i);

    saved_cards[idx] = points;
    return points;
}

int main()
{
    int points = 0;
    string buff;
    vector<string> lines;
    while (getline(cin, buff))
        lines.push_back(buff);

    for (int i = 0; i < lines.size(); ++i)
        points += points_in_card(lines, i);

    cout << "Points: " << points << endl;
    return 0;
}
