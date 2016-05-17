#include <QCoreApplication>

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int f(int node/*srvice variables:*/,int endNode, vector<vector<pair<int,int> > >& g, vector<int>& minLen, vector<int>& child,vector<bool>& memory,int inf,int iteration);

int main()
{
    //variables
    const int inf = INT_MAX / 2;
    vector<int> minLen;
    vector<int> child;
    vector<bool> memory;
    vector<vector<pair<int,int> > > g;
    int endNode;
    int startNode;
    int numOfScript;
    int numOfNodes;
    //end

    //fstream
    ifstream input;
    input.open("input.txt");
    //end

    //input
    input>>numOfScript>>numOfNodes>>startNode>>endNode;
    g.resize(numOfNodes);
    int left,right,cost;
    for(int i=0;i<numOfScript;i++){
        input>>left>>right>>cost;
        g[left].push_back(make_pair(right,cost));
    }
    minLen.resize(numOfNodes,inf);
    child.resize(numOfNodes,-1);
    memory.resize(numOfNodes,false);
    //end

    //output
    cout<<f(startNode,endNode,g,minLen,child,memory,inf,0)<<endl;//начало алгоритма  вывод результата
    int current=startNode;
    while(current!=endNode){
        cout<<current<<"->";
        current=child[current];
    }
    cout<<current;
    //end output


    return 0;
}

int f(int node/*srvice variables:*/,int endNode, vector<vector<pair<int,int> > >& g, vector<int>& minLen, vector<int>& child,vector<bool>& memory,int inf,int iteration){

    if(memory[node]) return minLen[node];

    memory[node]=true;

    if(node==endNode) return 0; //вернуть 0 если нашли конечный узел

    if(minLen[node]!=inf) return minLen[node];//возвращаем значение которе запомнили, если уже расчитали

    int m = inf;

    for(size_t i=0; i<g[node].size(); i++){

        int oldm = m;
        m = min<int>(m, f(g[node][i].first,endNode,g,minLen,child,memory,inf,iteration+1)+g[node][i].second);
        if(m<oldm) child[node]=g[node][i].first;

    }

    minLen[node]=m;
    return m;

}
