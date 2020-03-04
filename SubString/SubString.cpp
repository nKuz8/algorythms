#include "SubString.h"
#define D 26
#define Q 174281




vector<int> GetStopTable(string Text){
	vector<int> StopTable(26, -1);
	for(int i = Text.size() - 2; i >= 0; i--) {
		if(StopTable[Text[i] - 96] == -1) StopTable[Text[i] - 96] = i;
	}
	return StopTable;
}

vector<int> prefix_func(string Text) {
	vector<int> Pi(Text.size(), 0);
	int k = 0;
	Pi[0] = 0;
	for(int i = 1; i < Text.size(); i++) {
		while(k > 0 && Text[k] != Text[i]) k = Pi[k - 1];
		if(Text[k] == Text[i]) k++;
		Pi[i] = k;
	}
	return Pi;
}

vector<int> suffix_func(string Text) {
	size_t m = Text.size();
	vector<int> P = prefix_func(Text);
	reverse(Text.begin(), Text.end());
	vector<int> P1 = prefix_func(Text);
	vector<int> Table(m + 1);
	for(int i = 0; i < m + 1; i++) Table[i] = m - P[m - 1];
	for(int i = 0; i < m; i ++) {
		int ind = m - P1[i];
		int shift = i - P1[i] + 1;
		if(Table[ind] > shift) Table[ind] = shift;
	}
	return Table;	
}

vector<int> Boyer_Moore(string Text, string Sample) {
	vector<int> suff = suffix_func(Sample);
	vector<int> stop = GetStopTable(Sample);
	vector<int> result;
	for(int i = 0; i < Text.size() - Sample.size() + 1; ) {
		int j = Sample.size() - 1;
		while(j >= 0 && Sample[j] == Text[i + j]) j--;
		int delta_stop;
		if(j == -1) {
			result.push_back(i);
			delta_stop = 1;
		}
		else {
			delta_stop = j - stop[Text[i + j] - 96];
		}

		int delta_suff = suff[j + 1];

		i += max(delta_stop, delta_suff);
	}

	return result;
}

vector<int> Knuth_Morris_Pratt(string Text, string Sample) {
	vector<int> Pi = prefix_func(Sample);
	vector<int> result;
	int k = 0;
	for(int i = 0; i < Text.size(); i ++) {
		while (k > 0 && Sample[k] != Text[i]) k = Pi[k - 1];
		if (Sample[k] == Text[i]) k++;
		if (k == Sample.size()) {
			result.push_back(i - Sample.size() + 1);
			k = Pi[k - 1];
		}
	}
	return result;
}

vector<int> Rabin_Karp(string Text, string Sample) {
	size_t n = Text.length();
	size_t m = Sample.length();
	vector<int> result;
	int d_m = (int)pow(D, m - 1) % Q;
	int h = 0, h1 = 0;
	for(int i = 0; i < m; i++) {
		h = (int)(D * h + Sample[i]) % Q;
		h1 = (int)(D * h1 + Text[i]) % Q;
	}
	for(int s = 0; s < n - m + 1; s++) {
		if(h == h1) {
			if(Sample == Text.substr(s, m)) result.push_back(s);
		}
		if(s < n-m) h1 = (D*(h1 - d_m*(Text[s])) + Text[s + m]) % Q;
	}
	return result;
}