//
//  main.cpp
//  Reshape the Matrix
//
//  Created by ningya on 14/04/2018.
//  Copyright © 2018 ningya. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> matrixReshape(vector<vector<int>>&, int, int);

void print( const vector<vector<int>>&out ){
    for( vector<int> vs : out){
        for( int i = 0 ; i < vs.size(); i++ ){
            cout<<" "<<vs[i];
        }
        cout<<endl;
    }
}

int main(int argc, const char * argv[]) {
    
    int r, c;
    vector<vector<int>> nums;
//    cout << "pleas key inputs:" << endl;
    cin >> r >> c;
    cout<<c<<" "<<r<<"\n";
    
    int input;
    while( cin >> input && input!=EOF){
        vector<int> row;
        row.push_back(input);
        while( cin >> input && input !='\n') row.push_back(input);
        nums.push_back(row);
    }
//    print(nums);
    
    vector<vector<int>> out = matrixReshape(nums, r, c);
    
    print(out);
    
    return 0;
}

vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
    //check vlide or not first
    if( (nums.size()*nums[0].size()) != (r*c) ) return nums;
    
    
    int count = 0;
    vector<vector<int>> reshaped;
    vector<int> row;
    
    for( vector<int> vec : nums){
        for( int con : vec){
            row.push_back(con);
            count ++ ;
            if(c>0 && count%c == 0){
                reshaped.push_back(row);
                row.clear();
            }
        }
    }
    
    return reshaped;
    
}
