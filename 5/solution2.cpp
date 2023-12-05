#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Mapping {
    long src = 0;
    long dest = 0;
    long range = 0;
};
typedef vector<Mapping> maps;

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

long dest(long src, maps mappings)
{
    long pos = src;
    for (auto m : mappings)
    {
        if (src < m.src || src > m.src + m.range - 1)
            continue;

        pos = m.dest + (src - m.src);
        break;
    }

    return pos;
}

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

    unordered_map<long, long> seed_to_dest;
    long lowest_location = 0;
    bool first = true;
    for (int i = 0; i < seeds.size(); i += 2)
    {
        cout << i << endl;
        long seed = stol(seeds[i]);
        long range = stol(seeds[i+1]);
        for (int j = 0; j < range; ++j)
        {
            ++seed;
            auto found = seed_to_dest.find(seed);
            if (found != seed_to_dest.end())
            {
                if (first || found->second < lowest_location)
                    lowest_location = found->second;
                //cout << "MAP seed: " << found->first << " loc: " << found->second << endl;
                continue;
            }

            long soil_pos = dest(seed, mymap["seed-to-soil"]);
            long fertilizer_pos = dest(soil_pos, mymap["soil-to-fertilizer"]);
            long water_pos = dest(fertilizer_pos, mymap["fertilizer-to-water"]);
            long light_pos = dest(water_pos, mymap["water-to-light"]);
            long temperature_pos = dest(light_pos, mymap["light-to-temperature"]);
            long humidity_pos = dest(temperature_pos, mymap["temperature-to-humidity"]);
            long location_pos = dest(humidity_pos, mymap["humidity-to-location"]);
            if (first || location_pos < lowest_location)
                lowest_location = location_pos;

            first = false;
            seed_to_dest[seed] = location_pos;
            //cout << "seed: " << seed << " loc: " << location_pos << endl;
        }
    }

    cout << lowest_location << endl;

    return 0;
}
