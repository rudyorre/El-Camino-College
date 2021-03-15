#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

vector<string> read_entry(const string entry)
{
	vector<string> tokens;

	size_t prev = 0, pos = 0;
	do
	{
		pos = entry.find("|", prev);
		if (pos == string::npos) pos = entry.length();
		string token = entry.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + 1;
	} while (pos < entry.length() && prev < entry.length());

	return tokens;
}

vector<string> findPotentialBadTraders(vector<string> inputVec)
{
	vector<string> suspicious_traders;
	vector<string> first_occurrences;
	int last_stock_price = stoi(read_entry(inputVec[0])[1]);

	for (auto entry : inputVec) // go through the input entries
	{
		vector<string> split_entry = read_entry(entry); //split the string to a vector of strings

		if (split_entry.size() == 2) // if the size is 2, then it is a stock price change
		{
			// go back 3 days and check each individual trade
			// not finished
			int day = stoi(split_entry[0]);
			int current_stock_price = stoi(split_entry[1]);
			int price_change = current_stock_price - last_stock_price;

			// Filter (by copying) inputVec by 4 conditions:
			// 1. If trade occurred 3 days prior to the price change
			// 2. If the trade type (BUY/SELL) matches (ex. if price increases, only buyers would benefit)
			// 3. If the profit/loss prevented is above the threshold of $500,000
			// 4. If the name of the trader isn't on the first_occurrences vector (so no duplicates occur)
			copy_if(cbegin(inputVec), cend(inputVec), back_inserter(suspicious_traders),
				[&day, &price_change, &suspicious_traders, &first_occurrences](string s)
				{
					vector<string> split = read_entry(s);
					if (split.size() == 2) return false;
					int entry_day = stoi(split[0]); // get the day of that entry and convert to int

					bool is_prior = entry_day >= day - 3 && entry_day < day; // whether entry is within window or not
					bool is_trade_type = (price_change > 0 ? "BUY" : "SELL") == split[2]; // whether the entry matches the BUY or SELL we're looking for
					bool is_over_threshold = abs(stoi(split[3]) * price_change) >= 500000;
					bool is_first = (find(begin(first_occurrences), end(first_occurrences), split[1]) == end(first_occurrences)) ? true : false;

					if (is_prior && is_trade_type && is_over_threshold && is_first)
					{
						first_occurrences.push_back(split[1]);
						return true;
					}
					return false;
				});

			// Transform suspicious_traders from <DAY>|<TRADER>|<TRADE_TYPE>|<AMOUNT> format to just <DAY>|<TRADER>
			transform(cbegin(suspicious_traders), cend(suspicious_traders), begin(suspicious_traders), 
				[](string s)
				{
					vector<string> split = read_entry(s);
					return split[0] + "|" + split[1];
				});

			last_stock_price = current_stock_price; // the current becomes the last stock price
		}
	}

	return suspicious_traders;
}


int main()
{
	ifstream in("input_1.txt");
	string str;

	if (!in)
	{
		cerr << "No input file" << endl;
		exit(0);
	}

	vector<string> inputVec;

	while (getline(in, str))
	{
		inputVec.push_back(str);
	}

	cout << "Input Entries:" << endl;
	for (auto it : inputVec)
	{
		cout << it << endl;
	}

	vector<string> resV = findPotentialBadTraders(inputVec);

	cout << endl << "Suspicious Traders:" << endl;
	for (const string& r : resV)
	{
		cout << r << endl;
	}

	return 0;
}