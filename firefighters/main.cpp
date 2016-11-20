#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <queue>

using namespace std;

typedef unsigned int uint;
typedef pair<uint,uint> ii;
typedef vector<ii> vii;

#define INF INT_MAX

const int maxCities = 100000;

void printMap (map<uint, vii> mymap) {
    for (map<uint, vii>::iterator it=mymap.begin(); it!=mymap.end(); ++it) {
        uint u = it->first;
        vii aux = it->second;
        for (uint i = 0; i < aux.size(); ++i) {
            ii p = aux[i];
            uint v = p.first;
            uint d = p.second;
            cout << u << " - " << v << " distance " << d << endl;
        }
    }

}

//Custom Comparator for Determining priority for priority queue (shortest edge comes first)
class prioritize{public: bool operator ()(pair<uint, uint>&p1 ,pair<uint, uint>&p2){return p1.second>p2.second;}};

vector<uint> dijkstra(map<uint, vii> adjacentList, int source) {
    vector<uint> dis(maxCities, INF);
    vector<int> vis(maxCities, false);

    priority_queue<ii, vii, prioritize> pq; //Priority queue to store vertex,weight pairs
    dis[source] = 0;
    pq.push(ii(source, 0)); //Pushing the source with distance from itself as 0
    while (!pq.empty()) {
        pair<int, int> curr = pq.top(); //Current vertex. The shortest distance for this has been found
        pq.pop();
        int currentCity = curr.first;
        int currentDist = curr.second;
        if (vis[currentCity]) continue;
        vis[currentCity] = true;
        for (int i = 0; i < adjacentList[currentCity].size(); i++) {
            ii node = adjacentList[currentCity][i];
            int neighbourCity = node.first;
            uint distCity = node.second;
            int disNode = dis[neighbourCity];
            if (!vis[neighbourCity] && distCity + currentDist < disNode) //If this node is not visited and the current parent node distance+distance from there to this node is shorted than the initial distace set to this node, update it
                pq.push(make_pair(neighbourCity, (dis[neighbourCity] = distCity + currentDist))); //Set the new distance and add to priority queue
        }
    }
    return dis;
}

void getCase () {
    uint n, m;
    //cout << "Insert n and m" << endl;
    cin >> n >> m;

    map<uint, vii> adjacencyMap;
    for (; m > 0; --m) {
        //cout << "Insert u v d" << endl;
        uint u, v, d;
        cin >> u >> v >> d;
        vii aux1 = adjacencyMap[u];
        vii aux2 = adjacencyMap[v];
        aux1.push_back(ii(v,d));
        aux2.push_back(ii(u,d));
        adjacencyMap[u] = aux1;
        adjacencyMap[v] = aux2;
    }

    uint k;
    //cout << "Insert k" << endl;
    cin >> k;
    vector<uint> firefighterBases(k);
    for (uint i = 0; i < k; ++i) {
        //cout << "Insert firefighter base" << endl;
        cin >> firefighterBases[i];
    }

    uint q;
    //cout << "Insert q" << endl;
    cin >> q;
    for (uint i = 0; i < q; ++i) {
        uint query;
        //cout << "Insert query" << endl;
        cin >> query;
        vector<uint> dis = dijkstra(adjacencyMap, query);
        ii min(query, INF);
        for (int i = 0; i < firefighterBases.size(); ++i) {
            uint pos = firefighterBases[i];
            if (dis[pos] > 0) {
                if (dis[pos] == min.second)
                    min.first = (pos < min.first) ? pos : min.first;
                else if (dis[pos] < min.second) {
                    min.first = pos;
                    min.second = dis[pos];
                }
            }
        }
        cout << "To get to " << query << ", distance " << min.second << ", from city " << min.first << "." << endl;
    }
}

int main() {
    uint c;
    cin >> c;

    for (uint i = 0; i < c; ++i) {
        cout << "Case #" << i+1 << endl;
        getCase();
        cout << endl;
    }

    return 0;
}