#include "SubString.cpp"

int main() {
	string Text = "abacdacdacbaa";
	string Sample = "ac";
	vector<int> Stop(Boyer_Moore(Text, Sample));
	for(int i = 0; i < Stop.size(); i++) cout<<Stop[i];
	cout<<endl;
	Stop.clear();
	Stop = Knuth_Morris_Pratt(Text, Sample);
	for(int i = 0; i < Stop.size(); i++) cout<<Stop[i];	
	cout<<endl;
	Stop.clear();
	Stop = Rabin_Karp(Text, Sample);
	for(int i = 0; i < Stop.size(); i++) cout<<Stop[i];	
	cout<<endl;
}