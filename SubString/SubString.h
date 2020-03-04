#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> GetStopTable(string);
vector<int> prefix_func(string);
vector<int> suffix_func(string);
vector<int> Boyer_Moore(string, string);
vector<int> Rabin_Karp(string, string);
vector<int> Knuth_Morris_Pratt(string, string);
