#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

int loadDictionary(istream& dictfile, vector<string>& dict)
{
	if (!dictfile)
	{
		cerr << "No input file" << endl;
		exit(0);
		return 0;
	}

	string str;
	int count = 0;

	while (getline(dictfile, str))
	{
		dict.push_back(str);
		count++;
	}

	return count;
}

int permute(string word, vector<string>& dict, vector<string>& results)
{
	int count = 0;
	// find all permutations of word
	sort(begin(word), end(word));
	do
	{
		// if it exists in the dictionary, and doesn't exist in the results vector, append it to results
		if (find(begin(dict), end(dict), word) != end(dict) && find(begin(results), end(results), word) == end(results))
		{
			results.push_back(word);
			count++;
		}
	}
	while (next_permutation(begin(word), end(word)));

	return count++;
}

void print(const vector<string>& results)
{
	if (results.size() == 0)
	{
		cout << "No matching words :(" << endl;
		return;
	}

	for (auto result : results)
	{
		cout << "Matching word " << result << endl;
	}
}

int permuterecurHelper(string s, int i, string permutations[], int& pi);

void Loop(string s, int i, int j, string permutations[], int& pi)
{
	if (j >= s.size())
	{
		return;
	}

	// statement
	swap(s[i], s[j]);
	permuterecurHelper(s, i + 1, permutations, pi);
	swap(s[i], s[j]);

	Loop(s, i, j + 1, permutations, pi);
}

bool Find(int i, string s, const string dict[], int size)
{
	if (i == size)
	{
		return false;
	}
	if (s == dict[i])
	{
		return true;
	}

	return Find(i + 1, s, dict, size);
}

int permuterecurHelper(string s, int i, string permutations[], int& pi)
{
	if (i == s.size())
	{
		permutations[pi] = s;
		pi++;
	}

	int j = i;
	Loop(s, i, j, permutations, pi);

	return 0;
}

void Filter(int i, int max, string permutations[], int& ri, const string dict[], string result[])
{
	if (i >= max)
	{
		return;
	}

	if (Find(0, permutations[i], dict, 2))
	{
		result[ri] = permutations[i];
		ri++;
	}

	Filter(i + 1, max, permutations, ri, dict, result);
}

int permuterecur(string word, const string dict[], int size, string result[])
{
	const int max_permutations = 6; // this should be factorial(word.size)
	string permutations[max_permutations];
	int pi = 0;
	int ri = 0;

	permuterecurHelper(word, 0, permutations, pi);

	Filter(0, max_permutations, permutations, ri, dict, result);

	return 0;
}

int main()
{
	string dict[2] = { "top", "pot" };
	string results[20]; // or whaetver max_results is
	
	permuterecur("top", dict, 2, results);

	cout << results[0] << endl;
	cout << results[1] << endl;

	//ifstream dictfile("words.txt");

	//vector<string> dict;
	//loadDictionary(dictfile, dict);

	//while (true)
	//{
	//	// Input
	//	string input;
	//	cout << "Please enter a string for an anagram: ";
	//	cin >> input;

	//	// Permute Input Word and Print
	//	vector<string> results;
	//	permute(input, dict, results);
	//	print(results);

	//	cout << "Another anagram? (y/n): ";
	//	cin >> input;
	//	cout << endl;
	//	if (input != "y" && input != "Y") break;
	//}

}