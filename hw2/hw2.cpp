#include <bits/stdc++.h>
using namespace std;

struct ya{
	int u, i, r, t;
	bool operator !=(const struct ya &a) const{
		if(u == a.u && i == a.i && r == a.r && t == a.t) 
			return false;
		return true;
	}
};
typedef struct ya yo;
vector<yo> aa, ba;

bool operator < (const yo &a, const yo &b){
	if(a.u == -100 || b.u == -100){            //in function "users"
		if(a.i != b.i)
			return a.i < b.i;        //i>u>t>r
		if(a.u != b.u)
			return a.u < b.u;
		if(a.t != b.t)
			return a.t < b.t;
		return a.r < b.r;
	}
    if(a.u != b.u)                 //u>i>r>t
    	return a.u < b.u;
	if(a.i != b.i) 
		return a.i < b.i;
	if(a.t != b.t) 
		return a.t < b.t;
	return a.r < b.r;
}

int compareuser (yo a, yo b){
	if(a.u != b.u) 
		return a.u < b.u;
	if(a.i != b.i) 
		return a.i < b.i;
	if(a.t != b.t) 
		return a.t < b.t;
    return a.r < b.r;
}

int compareitem (yo a, yo b){
	if(a.i != b.i) 
		return a.i < b.i;
	if(a.u != b.u) 
		return a.u < b.u;
	if(a.t != b.t) 
		return a.t < b.t;
    return a.r < b.r;
}

int comparetime(yo a, yo b){
	return a.t < b.t;
}

int compare(int a, int b){
	return a < b;
}

FILE *fku = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "r");

void accept(int u, int i, int t){
	yo yeah = {u, i, -100, t};
	vector<yo>::iterator iter = lower_bound(aa.begin(), aa.end(), yeah);
	if((iter != aa.end())&&(iter->u == u)&&(iter->i == i)&&(iter->t == t))
		cout << iter->r << endl;
	else 
		cout << '0' << endl;	
}

void items(int u1, int u2){
	int last = -1;
	vector<int> array;
	yo yeah1 = {u1, -100, -100, -100};
	yo yeah2 = {u2, -100, -100, -100};
	vector<yo>::iterator iter1 = lower_bound(aa.begin(), aa.end(), yeah1);
	vector<yo>::iterator iter2 = lower_bound(aa.begin(), aa.end(), yeah2);
	while(iter1->u == u1 && iter2->u == u2){
		if(iter1->i == iter2->i && iter1->i != last){
			array.push_back(iter1->i);
			last = iter1->i;
			iter1++;
			iter2++;
		}
		else if(iter1->i > iter2->i)
			iter2++;
		else
			iter1++;
	}
	sort(array.begin(), array.end(), compare);
	vector<int>::iterator i;
	if(array.size() != 0)
		for(i = array.begin(); i != array.end(); i++)
			cout << *i << endl;
	else
		cout << "EMPTY" << endl;
}

void users(int i1, int i2, int t1, int t2){
	vector<int> array;
	int last = -1;
	yo yeah1 = {-100, i1, -100, -100};
	yo yeah2 = {-100, i2, -100, -100};
	vector<yo>::iterator iter1 = lower_bound(ba.begin(), ba.end(), yeah1);
	vector<yo>::iterator iter2 = lower_bound(ba.begin(), ba.end(), yeah2);
	while(iter1->i == i1 && iter2->i == i2){
		if(iter1->u == iter2->u && iter1->u != last){
			if(iter1->t < t1 || iter1->t > t2){
				iter1++;
				continue;
			}
			if(iter2->t < t1 || iter2->t > t2){
				iter2++;
				continue;
			}
			if(iter1->t >= t1 && iter1->t <= t2 && iter2->t >= t1 && iter2->t <= t2)
				array.push_back(iter1->u);
			last = iter1->u;
			iter1++;
			iter2++;
		}
		else if(iter1->u > iter2->u)
			iter2++;
		else
			iter1++;
	}
	sort(array.begin(), array.end(), compare);
	vector<int>::iterator i;
	if(array.size() != 0)
		for(i = array.begin(); i != array.end(); i++)
			cout << *i << endl;
	else
		cout << "EMPTY" << endl;
}

void ratio(int i, int th)
{
	int acnum = 0, totnum = 0, tmpnum = 0;
	vector<vector<yo>::iterator> array;
	int x = aa.begin()->u;
	yo tmp = *(aa.begin()+1);
	for(vector<yo>::iterator j = aa.begin(); j != aa.end(); j++){
		if(j->u == x){
			if(tmp != *j) 
				tmpnum++;
			tmp = *j;
			continue;
		}
		if(tmpnum > th){
			array.push_back(j-1);
			totnum++;
		}
		tmpnum = 1;
		x = j->u;
		tmp = *j;
	}
	if(tmpnum > th)
	{
		totnum++;
		array.push_back(aa.end()-1);
	}
	vector<yo>::iterator iter;
	for(int k = 0; k < array.size(); k++){
		iter = array[k];
		int uu = array[k]->u;
		while(iter->u == uu){
			if(iter->i == i && iter->r == 1){
				acnum++;
				break;
			}
			iter--;
		}
	}
	cout << acnum << "/" << totnum << endl;
}

void findtime(int i, vector<int> use)
{
	yo yeah = {-100, i, -100, -100};
	vector<yo>::iterator j;
	vector<yo>::iterator k;
	vector<yo> array;
	vector<int> array2;
	vector<yo>::iterator it = lower_bound(ba.begin(), ba.end(), yeah, compareitem);
	while(it->i == i){
		for(int k = 0; k < use.size(); k++){
			if(use[k] == it->u){
				array.push_back(*it);
			}
		}
		it++;
	}
	sort(array.begin(), array.end(), comparetime);
	for(j = array.begin(); j != array.end(); j++){
		if(j->t != (j+1)->t){
			array2.push_back(j->t);
		}
	}
	if(array2.size() == 0)
		cout << "EMPTY" << endl;
	else
		for(int l = 0; l < array2.size(); l++)
			cout << array2[l] << endl;
}

int main(void){
	assert(fku != NULL);
	int u, i, t, r, n;
	char s[32];
	while(fscanf(fku,"%d%d%d%d", &u, &i, &r, &t) != EOF){
		aa.push_back((yo){u, i, r, t});
		ba.push_back((yo){u, i, r, t});
	}
	fclose(fku);
	sort(aa.begin(), aa.end(), compareuser);
	sort(ba.begin(), ba.end(), compareitem);
	scanf("%d", &n);
	bool f = true;
	for(int i = 0; i < n; i++){
		if(f == true) 
			cin >> s;
		if(s[0] == 'a'){
			int u1, i1, t1;
			cin >> u1 >> i1 >> t1;
			accept(u1, i1, t1);
			f = true;
		}
		else if(s[0] == 'i'){
			int u1, u2;
			cin >> u1 >> u2;
			items(u1, u2);
			f = true;
		}
		else if(s[0] == 'u'){
			int i1, i2, t1, t2;
			cin >> i1 >> i2 >> t1 >> t2;
			users(i1, i2, t1, t2);
			f = true;
		}
		else if(s[0] == 'r'){
			int i1, th;
			cin >> i1 >> th;
			ratio(i1, th);
			f = true;
		}
		else if(s[0] == 'f'){
			f = false;
			vector<int> use;
			int tmp;
			int i1;
			cin >> i1;
			while(~ scanf("%s", s) && isdigit(s[0])){
				sscanf(s, "%d", &tmp);
				use.push_back(tmp);
			}
			sort(use.begin(), use.end());
			findtime(i1, use);
			//cout << "fku" << endl;
		}
	}
	return 0;
}
