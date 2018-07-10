#include <bits/stdc++.h>
using namespace std;
unsigned long long t = 0;
bool solve = false;
vector< vector<int> > rowarray;
vector< vector<int> > colarray;
int checkrowsum[100] = {0}, checkcolsum[100] = {0};
int rowsum[100] = {0}, colsum[100] = {0};
int array[100][100] = {{0}}, row, col;
void result(){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(array[i][j] == 1) 
				printf("#");
			else
				printf(".");
		}
		puts("");
	}
	puts("");
}

bool checkrow(int a, int b){
	if(b == 0)
		return true;
	if(checkrowsum[a] > rowsum[a])
		return false;
	if(b-checkrowsum[a]+1 > col-rowsum[a])
		return false;
	int cnt = 0, i, k = 0;
	int size = rowarray[a].size();
	for(int i = 0; i <= b; i++){
		if(array[a][i] == 1){
			cnt++;
			if(cnt > rowarray[a][k])
				return false;
		}
		else if(array[a][i] != 1 && cnt != 0){
			if(cnt != rowarray[a][k]){
				return false;
			}
			cnt = 0;
			k++;
		}
	}
	if(cnt != 0)
		if(cnt > rowarray[a][k])
			return false;
	if(b > col-1 || k > size)
		return false;
	if(b == col-1 && array[a][b] == 1){
		if(k != size-1)
			return false;
		if(cnt != rowarray[a][k]){
			return false;
		}
	}
	return true;
}
bool checkcol(int a, int b)
{
	if(a == 0)
		return true;
	if(checkcolsum[b] > colsum[b])
		return false;
	if(a-checkcolsum[b]+1 > row-colsum[b])
		return false;
	int cnt = 0, i, k = 0;
	int size = colarray[b].size();
	for(int i = 0; i <= a; i++){
		if(array[i][b] == 1){
			cnt++;
			if(cnt > colarray[b][k])
				return false;
		}
		else if(array[i][b] != 1 && cnt != 0){
			if(cnt != colarray[b][k]){
				return false;
			}
			cnt = 0;
			k++;
		}
	}
	if(cnt != 0)
		if(cnt > colarray[b][k])
			return false;
	if(a > row-1 || k > size)
		return false;
	if(a == row-1 && array[a][b] == 1){
		if(k != size-1)
			return false;
		if(cnt != colarray[b][k]){
			return false;
		}
	}
	return true;
}
bool check(int a, int b)
{
	if(checkrow(a,b) && checkcol(a,b))
		return true;
	else
		return false;
}
void r(int a, int b)
{
	if(a == row && b == 0){
		result();
		solve = true;
		return;
	}
	array[a][b] = 1;
	checkcolsum[b]++;
	checkrowsum[a]++;
	if(check(a,b)){
		if(b == col - 1)
			r(a+1,0);
		else{
			if(checkrowsum[a] == rowsum[a]){
				int i;
				for(i = b+1; i < col; i++){
					array[a][i] = -1;
					if(!checkcol(a,i))
						break;
				}
				if(i == col)
					r(a+1,0);
				for(int j = b+1 ; j < col ; j++)
					array[a][j] = 0;
			}
			else
				r(a,b+1);
		}
		if(solve == true)
			return;
	}
	checkrowsum[a]--;
	checkcolsum[b]--;
	array[a][b] = -1;
	if(check(a,b)){
		if(b == col - 1)
			r(a+1, 0);
		else
			r(a, b+1);
	}
	array[a][b] = 0;
	return;
}

int main(){
	int a;
	char s[100];
	scanf("%d%d\n",&row,&col);
	for(int i = 0; i < row; i++){
		vector<int> tmp;
		stringstream ss;
		fgets(s, 100, stdin);
		ss << s;
		while(ss >> a){
			tmp.push_back(a);
			rowsum[i] += a;
		}
		rowarray.push_back(tmp);
	}
	for(int j = 0; j < col; j++){
		vector<int> tmp;
		stringstream ss;
		fgets(s, 100, stdin);
		ss << s;
		while(ss >> a){
			tmp.push_back(a);
			colsum[j] += a;
		}
		colarray.push_back(tmp);
	}
	r(0,0);
	return 0;
}
