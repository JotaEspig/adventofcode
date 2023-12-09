#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const int HIGH_CARD = 0b0000001;
const int PAIR = 0b0000010;
const int TWOPAIR = 0b0000100;
const int THREE = 0b0001000;
const int FULLHOUSE = 0b0010000;
const int FOUR = 0b0100000;
const int FIVE = 0b1000000;

unordered_map<char, int> card_values
    = {{'A', 13}, {'K', 12}, {'Q', 11}, {'J', 0}, {'T', 9}, {'9', 8}, {'8', 7},
       {'7', 6},  {'6', 5},  {'5', 4},  {'4', 3}, {'3', 2}, {'2', 1}};

struct Hand
{
    string cards;
    int type;
    int bid;

    void generate_type();
    bool dedraw(const Hand &other) const;
    bool operator<(const Hand &other) const;
};

void Hand::generate_type()
{
    unordered_map<char, int> counter;

    type = HIGH_CARD;
    for (auto c : cards)
        counter[c] = counter[c] + 1;

    auto found = counter.find('J');
    if (found != counter.end())
    {
        char highest = '?';
        for (auto c : cards)
            if (c != 'J' && counter[c] > counter[highest])
                highest = c;
        if (highest != '?')
        {
            counter[highest] = counter[highest] + found->second;
            counter[found->first] = 0;
        }
    }

    bool already_pair = false;
    bool already_three = false;
    for (auto p : counter)
    {
        if (p.second == 2)
        {
            if (already_pair)
            {
                type = TWOPAIR;
                return;
            }
            else if (already_three)
            {
                type = FULLHOUSE;
                return;
            }
            else
            {
                already_pair = true;
                type = PAIR;
            }
        }
        else if (p.second == 3)
        {
            if (already_pair)
            {
                type = FULLHOUSE;
                return;
            }
            else
            {
                type = THREE;
                already_three = true;
            }
        }
        else if (p.second == 4)
        {
            type = FOUR;
            return;
        }
        else if (p.second == 5)
        {
            type = FIVE;
            return;
        }
    }
}

bool Hand::dedraw(const Hand &other) const
{
    int i = -1;
    for (auto c : cards)
    {
        ++i;
        char oc = other.cards[i];
        if (c == oc)
            continue;
        else if (card_values[c] < card_values[oc])
            return true;
        else
            return false;
    }

    return false;
}

bool Hand::operator<(const Hand &other) const
{
    return (type < other.type) || (type == other.type && dedraw(other));
}

int main()
{
    string buff;
    vector<Hand> hands;
    while (getline(cin, buff))
    {
        string s{buff.begin(), buff.begin() + 5};
        string bid_str{buff.begin() + 6, buff.end()};
        stringstream ss{bid_str};
        Hand h;
        h.cards = s;
        ss >> h.bid;
        h.generate_type();
        hands.push_back(h);
    }

    sort(hands.begin(), hands.end());
    long total = 0;
    int i = 1;
    for (auto h : hands)
    {
        total += i * h.bid;
        cout << h.cards << " " << h.type << endl
             << "RANK: " << i << " - Bid: " << h.bid << " = " << i * h.bid
             << endl;
        ++i;
    }
    cout << total << endl;
    return 0;
}
