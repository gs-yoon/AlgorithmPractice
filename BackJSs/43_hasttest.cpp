#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

int main()
{
	unordered_map<string,vector<string>> hashmap;
	hashmap["SF"].push_back("inception");
	hashmap["SF"].push_back("interstella");

	for (auto title : hashmap["SF"])
	{
		cout << "titil = " << title << endl;
	}

	auto ret = hashmap.find("REAL");
	if (ret == hashmap.end())
		{
		cout << "no\n";
	}

	auto ret2 = hashmap.find("SF");
	if (ret2 != hashmap.end())
	{
		cout << "yes\n";
		cout << ret2->first << endl;
		cout << ret2->second[0]<< endl;
	}
}