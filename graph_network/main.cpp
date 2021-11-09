#include <cstdio>
#include <cstdlib>
#include <list>
using namespace std;
struct edge {
    int start;
    int end;
    int dist;
} graph[300000];
int n, m;
int cmp(const void *a, const void *b){
    edge *p = (edge *) a;
    edge *q = (edge *) b;
    return p->dist - q->dist;
}
int main()
{
    while(scanf("%d %d",&m ,&n) != EOF){
        int total = 0;
        for (int i = 0; i < n; i++){
            scanf ("%d %d %d", &graph[i].start, &graph[i].end, &graph[i].dist);
        }
        qsort(graph, n, sizeof(graph[0]), cmp); //sort edges by its cost

        list<int> mylist[m];
        for(int i=0; i<n; i++){
            mylist[graph[i].start].push_back(graph[i].end);
            mylist[graph[i].end].push_back(graph[i].start);
            total = total+graph[i].dist;

            bool done = false;
            for(int j=1; j<m; j++){

            }
        }


        printf ("%d\n", total);
    }
    return 0;
}
