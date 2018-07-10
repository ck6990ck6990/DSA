#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cmath>

using namespace std;

int main()
{
	double max = -1;
	double a[300][500] = {{0}};
	double b[300][300];
  	int n, i, j, k, x = 0, y = 0;
	cin >> n;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++){
			cin >> a[i][j];
			b[i][j] = a[i][j];
		}

	for(i = 0; i < n; i++)
		for(j = n; j < n+n; j++){
			if(i + n == j)
				a[i][j] = 1;
		}    

    // left down triangle = 0
	for(i = 0; i < n; i++){
		int c = 0;
		for(j = 0; j < i+1; j++){
			if(i == j && a[i][j] != 0) 
				continue;
			else if(a[i][j] != 0){
				double  r = a[i][j] / a[j][j];
				for(k = 0; k < n+n; k++)
					a[i][k] -= a[j][k] * r;
			}
			else if(a[i][j] == 0 && i == j){
				for(int f = i+1+c; f < n; f++){
					c++;
					if(a[f][j] == 0)
						continue;
					for(int u = 0; u < n+n; u++)
						a[i][u] += a[f][u];
					break;
				}
				j=-1;
			}
		}
	}

	// let all pivots = 1
	for(i = 0, j = 0; i < n; i++, j++)
		if(a[i][j] != 0 && a[i][j] != 1){
			double r = a[i][j];
			for(k = 0; k < n*2; k++)
				a[i][k] /= r;              
		}

	// eliminate from down to top
	for(i = n-1; i >= 0; i--)
		for(j = n-1; j > i; j--){
			if(a[i][j] != 0){
				double r = a[i][j];
				for(k = 0; k < n+n; k++)
					a[i][k] -= r * a[j][k];
			}
		}

	//output
 	double sum = 0, t, aa;
 	for(i = 0; i < n; i++)
 		for(j = 0; j < n; j++){
   			for(k = 0; k < n; k++)
   				sum += b[i][k] * a[k][j+n];
   			if(i == j)
   				if(abs(sum-1.0) >= 0)
   					max = abs(sum-1);
   			else 
   				if(abs(sum) >= 0)
   					max = abs(sum);

    		sum = 0;
    	}
    cout << max << endl;

	for(i = 0; i < n; i++)
		for(j = n; j < n+n; j++){
			cout << a[i][j] << " ";
			if(j == n*2 - 1)
				cout << endl;
		}
    return 0;
}
