#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int eraseOverlapIntervals(vector<vector<int> >& intervals) {
     vector<vector<int> > map;
    vector<int> overlap, count;
    bool isClear = true;
    int remove = 0;

    for( vector<int> interval : intervals ){
        vector<int> row(interval[1], 0);
        if(interval[1]>overlap.size())
            overlap.resize(interval[1]);
        count.push_back(0);
        
        for( int i=interval.at(0); i<interval.at(1); i++ ){
            row[i] = 1;
            overlap[i] ++;
            if(overlap[i]>1){
                count[count.size()-1] ++;
                isClear = false;
                
                if(overlap[i]==2){
                    for(int j=0; j<map.size(); j++){
                        if(map[j].size()>i && map[j][i]==1){
                            count[j] ++;
                            break;
                        }
                    }
                }
            }
        }
        map.push_back(row);
    }

    while(!isClear){
        int max=0, idx=0;
        for(int i=0; i<count.size(); i++){
            if(count[i]>max){
                max = count[i];
                idx = i;
            }
        }

        for(int i=1; i<map[idx].size(); i++){
            if(map[idx][i]==0) continue;
            
            overlap[i] --;
            if(overlap[i]==1){
                for(int j=0; j<map.size(); j++){
                    if(j!=idx && map[j].size()>i && map[j][i]==1){
                        count[j] --;
                        break;
                    }
                }
            }
        }

        map[idx].clear();
        count[idx] = 0;
        remove ++;

        isClear = true;
        for(int i : overlap) if(i>1) {isClear=false; break;}
    }

    return remove;
}


int main(void){
    vector<vector<int> > input;

    while(true){
        int a, b;
        cin>>a>>b;
        if(a<0 || b<=a) break;
        vector<int> row;
        row.push_back(a);
        row.push_back(b);
        input.push_back(row);
    }


    int output;
    output = eraseOverlapIntervals(input);
    cout<<output<<endl;

    return 0;
}
