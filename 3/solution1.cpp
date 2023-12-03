#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <cctype>

using namespace std;

int num_at(vector<string> lines, pair<int, int> idx)
{
    string temp{lines[idx.first]};
    string s{temp.begin() + idx.second, temp.end()};

    stringstream ss{s};
    int num;
    ss >> num;
    return num;
}

vector<pair<int, int>> find_by_symbol(vector<string> lines, pair<int, int> idx)
{
    vector<pair<int, int>> idxs;
    pair<int, int> possibles[8] = {
        {idx.first - 1, idx.second - 1},
        {idx.first - 1, idx.second},
        {idx.first - 1, idx.second + 1},
        {idx.first, idx.second - 1},
        {idx.first, idx.second + 1},
        {idx.first + 1, idx.second - 1},
        {idx.first + 1, idx.second},
        {idx.first + 1, idx.second + 1}
    };

    int num_lines = lines.size();
    int num_chars = lines[0].size();
    for (auto p : possibles)
    {
        if ((p.first < 0 || p.first >= num_lines) &&
            (p.second < 0 || p.second >= num_chars))
            continue;
        if (!isdigit(lines[p.first][p.second]))
            continue;

        auto it = lines[p.first].begin() + p.second;
        while (isdigit(*(--it)));
        ++it;
        idxs.push_back({p.first, it - lines[p.first].begin()});
    }

    return idxs;
}

int main()
{
    vector<string> lines;
    string buff;
    // read all lines
    while (getline(cin, buff))
    {
        lines.push_back(buff);
        buff = "";
    }

    int num_lines = lines.size();
    int num_chars = lines[0].size();
    unordered_set<int> idxs{};
    for (auto l_it = lines.begin(); l_it < lines.end(); ++l_it)
    {
        string curr_s = *l_it;
        for (auto c_it = curr_s.begin(); c_it < curr_s.end(); ++c_it)
        {
            if (!isdigit(*c_it) && *c_it != '.')
            {
                vector<pair<int, int>> tmp = find_by_symbol(
                    lines,
                    {l_it - lines.begin(), c_it - curr_s.begin()}
                );
                for (auto e : tmp)
                    idxs.insert(e.first * num_lines + e.second);
            }
        }
    }

    int sum = 0;
    for (auto e : idxs)
    {
        int line_idx = e / num_lines;
        int char_idx = e % num_lines;
        int num = num_at(lines, {line_idx, char_idx});
        sum += num;
    }

    cout << sum << endl;

    return 0;
}
