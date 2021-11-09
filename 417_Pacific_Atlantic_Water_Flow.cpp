using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
      int m = matrix.size();
      if( m<=0 ) return vector<vector<int>>();

      int n = matrix[0].size();
      if( n<=0 ) return vector<vector<int>>();

      vector<vector<int>> map;
      map.push_back( vector<int>(n, 1) );
      for(int i=1; i<m; i++){
          vector<int> row(n, 0);
          row[0] += 1;
          row[n-1] += 2;
          map.push_back(row);
      }
      for(int i=0; i<n; i++) if( map[m-1][i]<2 ) map[m-1][i] += 2;
      map[m-1][0] = 3;
      map[0][n-1] = 3;

      for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
          if(map[i][j]>=3) continue;

          queue< pair<int, int>> cords;
          cords.push( make_pair(i,j) );
          while( !cords.empty() ){
            pair<int, int> cord = cords.front();
            cords.pop();
            int x = cord.first;
            int y = cord.second;
            if(map[x][y]>=3) continue;
            
            //update out
            int old = map[x][y];
            int u=0, r=0, l=0, d=0;
            if(x>0 && matrix[x][y] >= matrix[x-1][y]) u = map[x-1][y];
            if(x<m-1 && matrix[x][y] >= matrix[x+1][y]) d = map[x+1][y];
            if(y>0 && matrix[x][y] >= matrix[x][y-1]) l = map[x][y-1];
            if(y<n-1 && matrix[x][y] >= matrix[x][y+1]) r = map[x][y+1];

            if( u==3 || d==3 || l==3 || r==3 ) { 
              map[x][y] = 3;
            } else{
              if( map[x][y]!=1 && (u==1 || d==1 || l==1 || r==1) ) map[x][y] += 1;
              if( map[x][y]<2 && (u==2 || d==2 || l==2 || r==2) ) map[x][y] += 2;
            }
            if(old == map[x][y]) continue;

            //update in
            if(x>0 && matrix[x][y]<=matrix[x-1][y] && map[x][y]!=map[x-1][y]) cords.push( make_pair(x-1,y) );
            if(x<m-1 && matrix[x][y]<=matrix[x+1][y] && map[x][y]!=map[x+1][y])  cords.push( make_pair(x+1,y) );
            if(y>0 && matrix[x][y]<=matrix[x][y-1] && map[x][y]!=map[x][y-1])  cords.push( make_pair(x,y-1) );
            if(y<n-1 && matrix[x][y]<=matrix[x][y+1] && map[x][y]!=map[x][y+1])  cords.push( make_pair(x,y+1) );
          }
          
        }
      }

      vector<vector<int>> result;
      for(int i=0; i<m; i++){
          for(int j=0; j<n; j++){
            if(map[i][j]>=3) result.push_back( vector<int>({i,j}) );
          }
      }
     
      return result;
    }
};