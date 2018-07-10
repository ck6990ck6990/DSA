#include <bits/stdc++.h>
using namespace std;

struct data{
	int bidid;
	int clientid;
	int action;
	int price;
	int count;
};
typedef data da;

bool cmpmin(da a, da b){
	return a.price > b.price;
}

bool cmpmax(da a, da b){
	return a.price < b.price;
}

vector<da> a, b;
vector<int> array1;
int array2[100000000];
int n1 = 0, n2 = 0;

void current(){
	printf("n2=%d n1=%d\n",n2,n1);
	puts("sell");
	for(int i = 1 ; i <= n2 ; i++) 
		printf("%d %d %d %d\n",b[i].bidid,b[i].clientid,b[i].price,b[i].count);
	puts("buy");
	for(int i = 1 ; i <= n1 ; i++) 
		printf("%d %d %d %d\n",a[i].bidid,a[i].clientid,a[i].price,a[i].count);
}

void buy(int n)	
{
	a[n] = a[n1];
	n1--;
	a.pop_back();
	int max;	
	while(n*2 <= n1){
		if(n*2+1 <= n1){
			if(a[n*2].price > a[n*2+1].price)
				max = n*2; 
			else if(a[n*2].price < a[n*2+1].price)
				max = n*2+1;
			else if(a[n*2].price == a[n*2+1].price){
				if(a[n*2].bidid < a[n*2+1].bidid)
					max = n*2;
				else
					max = n*2+1;
			}
			if(a[max].price > a[n].price){
				swap(a[max], a[n]);
				n = max;
			}
			else if(a[max].price == a[n].price){
				if(a[max].bidid < a[n].bidid){
					swap(a[max], a[n]);
					n = max;
				}
				else
					break;
			}
			else 
				break;
		}
		else{
			if(a[n*2].price > a[n].price){
				swap(a[n*2], a[n]);
				n *= 2;
			}
			else if(a[n*2].price == a[n].price){
				if(a[n*2].bidid < a[n].bidid){
					swap(a[n*2], a[n]);
					n *= 2;
				}
				else
					break;
			}
			else 
				break;
		}
	}
}

void sell(int n)
{
	b[n] = b[n2];
	n2--;
	b.pop_back();
	int min;
	while(n*2 <= n2){	
		if(n*2+1 <= n2){
			if(b[n*2].price > b[n*2+1].price)
				min = n*2+1;
			else if(b[n*2].price < b[n*2+1].price)
				min = n*2;
			else if(b[n*2].price == b[n*2+1].price){
				if(b[n*2].bidid < b[n*2+1].bidid)
					min = n*2;
				else
					min = n*2+1;
			}
			if(b[min].price < b[n].price){
				swap(b[min], b[n]);
				n = min;
			}
			else if(b[min].price == b[n].price){
				if(b[min].bidid < b[n].bidid){
					swap(b[min], b[n]);
					n = min;
				}
				else
					break;
			}
			else 
				break;
		}
		else{
			if(b[n*2].price < b[n].price){
				swap(b[n*2], b[n]);
				n *= 2;
			}
			else if(b[n*2].price == b[n].price){
				if(b[n*2].bidid < b[n].bidid){
					swap(b[n*2], b[n]);
					n *= 2;
				}
				else
					break;
			}
			else 
				break;
		}
	}
}
void ggggg()
{
	puts("/////");
	current();
	puts("/////");
}

int main()
{
	int bidid, clientid, action, price, count, num, i = 0;
	a.push_back((da){0,0,0,0,0});
	b.push_back((da){0,0,0,0,0});
	while(cin >> bidid >> clientid >> action >> price >> count){
		if(action == 0 || action == 1){
			array2[bidid] = 0;
		}
		if(action == 0){
			int n;
			a.push_back((da){bidid, clientid, action, price, count});    //buy    big top
			n1++;
			n = n1;
			while(n > 1 && a[n/2].price < price){
				swap(a[n/2],a[n]);
				n /= 2;
			}	
			while(n > 1 && a[n/2].price == price && a[n/2].bidid > bidid){
				swap(a[n/2], a[n]);
				n /= 2;
			}
		}
		else if(action == 1){
			int nn;
			b.push_back((da){bidid, clientid, action, price, count});       //sell   small top
			n2++;
			nn = n2;
			while(nn > 1 && b[nn/2].price > price){
				swap(b[nn/2], b[nn]);
				nn /= 2;
			}
			while(nn > 1 && b[nn/2].price == price && b[nn/2].bidid > bidid){
				swap(b[nn/2], b[nn]);
				nn /= 2;
			}
		}
		else if(action == 2){
			array2[price] = 1;
			array2[bidid] = 0;
		}
		while(n1 > 0 && n2 > 0){
			//ggggg();
			if(array2[a[1].bidid] == 1){
				buy(1);
				continue;
			}
			if(array2[b[1].bidid] == 1){
				sell(1);	
				continue;
			}
			if(a[1].price >= b[1].price){
				int trscnt;
				if(a[1].count > b[1].count)
					trscnt = b[1].count;
				else
					trscnt = a[1].count;
				cout << i << "\t" << a[1].clientid << "\t" << b[1].clientid << "\t" << b[1].price << "\t" << trscnt;
				cout << endl;
				i++;
				if(a[1].count == b[1].count){
					buy(1);
					sell(1);
				}
				else if(a[1].count > b[1].count){
					a[1].count -= b[1].count;
					sell(1);
				}
				else if(a[1].count < b[1].count){
					b[1].count -= a[1].count;
					buy(1);
				}
			}
			else
				break;
		}
	}
	return 0;
}
