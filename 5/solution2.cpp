#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Mapping {
    long src;
    long dest;
    long range;

    bool operator<(const Mapping &other) const
    {
        return src < other.src;
    }
};
typedef vector<Mapping> maps;

struct Range {
    long begin; // inclusive
    long end; // exclusive

    bool operator<(const Range &other) const
    {
        return begin < other.begin;
    }
};

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

unordered_map<int, string> int2string{
    {0, "seed-to-soil"},
    {1, "soil-to-fertilizer"},
    {2, "fertilizer-to-water"},
    {3, "water-to-light"},
    {4, "light-to-temperature"},
    {5, "temperature-to-humidity"},
    {6, "humidity-to-location"},
};

long lowest_by_range(Range r, unordered_map<string, maps> map, int next)
{
    cout << "\nRange: begin=" << r.begin << " end=" << r.end << endl;
    maps mapping = map[int2string[next]];
    vector<Range> new_ranges;

    // generates new ranges
    for (const auto m : mapping)
    {
        cout << "Mapping: src=" << m.src << " dest=" << m.dest << " range=" << m.range << endl;
        cout << "RangeNOW: begin=" << r.begin << " end=" << r.end << endl;
        if (r.begin >= r.end)
            break;

        Range new_r;
        if (m.src + m.range - 1 < r.begin)
        {
            continue;
        }
        else if (m.src <= r.begin)
        {
            cout << "B" << endl;
            new_r.begin = m.dest + (r.begin - m.src);
            new_r.end = m.dest - m.src + (
                min(m.src + m.range, r.end)
            );
            r.begin = min(m.src + m.range, r.end);
        }
        else if (m.src > r.begin && m.src < r.end)
        {
            cout << "C" << endl;
            new_r.begin = r.begin;
            new_r.end = m.src;
            r.begin = m.src;
        }
        else
        {
            cout << "D" << endl;
            new_r.begin = r.begin;
            new_r.end = r.end;
            r.begin = r.end;
        }

        cout << "NRANGE dest begin=" << new_r.begin << " end=" << new_r.end << endl;

        new_ranges.push_back(new_r);
    }
    if (r.begin < r.end)
         new_ranges.push_back(r);

    if (next == 6)
    {
        sort(new_ranges.begin(), new_ranges.end());
        cout << "END ===== =========================" << new_ranges[0].begin << "\n";
        return new_ranges[0].begin;
    }

    vector<long> res;
    for (auto nr : new_ranges)
    {
        if (nr.begin == nr.end)
            continue;
        //cout << nr.begin << " " << nr.end << endl;
        long l = lowest_by_range(nr, map, next + 1);
        res.push_back(l);
    }

    sort(res.begin(), res.end());
    cout << "END ------------------------------------" << res[0] << "\n";
    return res[0];
}

// It thowring a 0 somewhere, find where JOTA i know u can do it

int main()
{
    unordered_map<string, maps> mymap;
    string buff;

    // reads header
    getline(cin, buff);
    vector<string> seeds = split(buff.begin() + 7, buff.end(), " ");
    getline(cin, buff);

    // reads mappings
    bool is_new = true;
    auto curr_maps = mymap.find("");
    while (getline(cin, buff))
    {
        if (buff == "")
        {
            is_new = true;
            continue;
        }

        if (is_new)
        {
            string mappingname = split(buff.begin(), buff.end(), " ")[0]; 
            auto pair = mymap.insert({mappingname, vector<Mapping>{}});
            curr_maps = pair.first;
            is_new = false;
            continue;
        }

        stringstream ss{buff};
        Mapping m{};
        ss >> m.dest >> m.src >> m.range;
        curr_maps->second.push_back(m);
    }
    for (auto &it : mymap)
        sort(it.second.begin(), it.second.end());

    long lowest_location = 0;
    bool first = true;
    for (int i = 0; i < seeds.size(); i += 2)
    {
        Range r;
        r.begin = stol(seeds[i]);
        r.end = r.begin + stol(seeds[i + 1]);
        long low = lowest_by_range(r, mymap, 0);
        if (first || low < lowest_location)
            lowest_location = low;
        first = false;
    }

    /*
    Possible solution:
    Try to search by ranges instead of each seed
    Search how the range works going through the process, then find the lowest
    */

    cout << lowest_location << endl;

    return 0;
}
