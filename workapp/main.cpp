#include <bits/stdc++.h>
#include <vector>
#include <stdlib.h>

using namespace std;

const int maxn = 150000;

int n;

int compare(const void* a, const void* b){
    pair<int, int> A = *(pair<int, int>*)a;
    pair<int, int> B = *(pair<int, int>*)b;

    return A.second - B.second;
}

int inline solve(vector< pair<int, int> > ary) {
    int table[n][n];
    qsort(&ary[0], (unsigned int)n, sizeof(pair<int, int>),compare);
    for(auto t : ary) cout<<t.first<<" "<<t.second<<endl;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){

        }
    }

}

int main() {

	scanf("%d",&n);

	vector< pair<int,int> > ary(n);

	for(int i = 0; i < n; i++) scanf("%d%d",&ary[i].first, &ary[i].second);

	printf("%d\n",solve(ary));
	return 0;
}
