#include "function.h"

set<State> SwapSort::extend(State s)
{
    set<State> newstate;
    State tmp ;
    int t = s[0];

    tmp = s;
    tmp[0] = tmp[tmp.size()-1];
    tmp[tmp.size()-1] = t;
    newstate.insert(tmp);


    tmp = s;
    tmp[0] = tmp[1];
    tmp[1] = t;
    newstate.insert(tmp);


    return newstate;
}

void SwapSort::solve(int steps)
{
    State goal;

    auto tmp = *(_paths.begin());
    goal = tmp.front();
    std::sort(goal.begin(),goal.end());


    while(steps>0){
        set<list<State>> oldp, newp;

        for(auto p : _paths){
            set<State> newset;

            newset = extend(p.back());
            _explored.insert(p.back());

            oldp.insert(p);

            for(auto s : newset){
                if(s == goal){
                    auto t = p;
                    t.push_back(s);
                    _solutions.insert(t);
                }else{
                    auto forfind = _explored.find(s);
                    if(forfind==_explored.end()){
                        auto t = p;
                        t.push_back(s);
                        newp.insert(t);
                    }
                }
            }
        }
        for( auto o : oldp){
                _paths.erase(o);
            }
        for(auto v : newp){
                _paths.insert(v);
        }
        steps--;
    }

}
