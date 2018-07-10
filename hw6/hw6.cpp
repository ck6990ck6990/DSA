#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

unordered_set<string> dictionary; 
vector<string> arr2, arr3;
FILE *fku = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b", "r");

inline int readfp(){
	const int N = 524288;
	static char buf[N];
	static char *p = buf, *end = buf;
	if(p == end) {
		if((end = buf + fread(buf, 1, N, fku)) == buf) return EOF;
		p = buf;
	}
	return *p++;
}
inline void ins(vector<string> arr){
	char ch = 97;
	string tmp;
	for(int i = 0; i < arr.size(); i++)
		for(int j = 0; j < arr[i].size()+1; j++){
			while(ch < 97+26){
				if(arr[i][j] != ch){
					tmp = arr[i];
					tmp.insert(j, &ch, 1);
					arr2.push_back(tmp);
				}
				ch++;
			}
			ch = 97;
		}
}
inline void del(vector<string> arr){
	string tmp;
	for(int i = 0; i < arr.size(); i++)
		for(int j = 0; j < arr[i].size(); j++){
			tmp = arr[i];
			tmp.erase(j, 1);
			arr2.push_back(tmp);
		}
}
inline void subs(vector<string> arr){
	string tmp;
	char ch = 97;
	for(int i = 0; i < arr.size(); i++)
		for(int j = 0; j < arr[i].size(); j++){
			while(ch < 97 + 26){
				if(arr[i][j] != ch){
					tmp = arr[i];
					tmp[j] = ch;
					arr2.push_back(tmp);
				}
				ch++;
			}
			ch = 97;
		}
}
inline void trans(vector<string> arr){
	string tmp;
	for(int i = 0; i < arr.size(); i++)
		for(int j = 0; j < arr[i].size()-1; j++){
			if(arr[i] != arr[i+1]){
				tmp = arr[i];
				swap(tmp[j], tmp[j+1]);
				arr2.push_back(tmp);
			}
		}
}
inline void ed(vector<string> arr){
	ins(arr);
	del(arr);
	subs(arr);
	trans(arr);
}
bool cmp(string a, string b){
	return a < b;
}
int main(){
	vector<string> arr;
	dictionary.reserve(1000000);
	arr2.reserve(3600000);
	char s[200], str[200], aa[200], c, vol[50];
	int aaa, aaaa, n1, n2, n0;
	string abc;
	assert(fku != NULL);
	while( (c = readfp() ) != EOF){									
		while(c != ' ' && c != '\n'){					
			abc += tolower(c);
			c = readfp();
		}
		dictionary.insert(abc);
		abc.clear();
		if(c != '\n')
			while((c=readfp()) != '\n');
	}
	fclose(fku);
	while(fgets(aa, 200, stdin) != NULL){
		sscanf(aa, "%s", vol);
		for(int i = 0; i < strlen(vol); i++){
			printf("%c", vol[i]);
		}
		arr.push_back(vol);
		printf(" ==> ");
		if(dictionary.find(vol) != dictionary.end())
			printf("OK");
		else{
			ed(arr);
			ed(arr2);
			for(int i = 0; i < arr2.size(); i++){
				if(dictionary.find(arr2[i]) != dictionary.end())
					arr3.push_back(arr2[i]);
			}
			sort(arr3.begin(), arr3.end(), cmp);
			if(arr3.size() != 0){
				arr3.push_back("0");
				for(int i = 0; i < arr3.size()-1; i++){
					if(i+1 <= arr3.size())
						if(arr3[i] == arr3[i+1])
							continue;
					printf("%s ", arr3[i].c_str());
				}
			}
			else
				printf("NONE");
		}
		printf("\n");
		n0 = arr.size();
		n1 = arr2.size();
		n2 = arr3.size();
		for(int i = 0; i < n0; i++)
			arr.pop_back();
		for(int i = 0; i < n1; i++)
			arr2.pop_back();
		for(int i = 0; i < n2; i++)
			arr3.pop_back();
	}
	return 0;
}
