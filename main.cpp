#include <iostream>
#include <vector>
#include <map>
#include <queue>
#define ll long long
#define ve vector
#define mp make_pair
using namespace std;

int main() {
    ll n, m;
    cin >> n >> m;
    ve<map<ll, ll>> adjacencies(n, map<ll, ll>());
    ll s, t;
    cin >> s >> t;
    for(int i = 0; i<m; i++){
        ll a, b, d;
        cin >> a >> b >> d;
        if(!adjacencies[b].count(a)){
            adjacencies[a][b] = 0;
        }
        adjacencies[a][b] += d;
        if(!adjacencies[b].count(a)){
            adjacencies[b][a] = 0;
        }
    }

    ll returnVal = 0;
    bool repeat = 1;
    while(repeat){
        repeat = 0;
        ve<pair<ll, ll>> previous(n, {-1, -1});
        ve<bool> visited(n, 0);
        queue<pair<pair<ll, ll>,ll>> q;
        q.push(mp(mp(-1, -1), s));
        while(q.size()>0){
            ll last = q.front().first.first;
            ll size = q.front().first.second;
            ll current = q.front().second;
            q.pop();
            if(visited[current] == 0){
                visited[current] = 1;
                previous[current] = mp(last, size);
                if(current == t){
                    break;
                }
                for(auto it = adjacencies[current].begin(); it!=adjacencies[current].end(); it++){
                    if(it->second!=0){
                        q.push(mp(mp(current, it->second), it->first));
                    }
                }
            }

        }
        if(previous[t].first != -1){
            repeat = 1;
            ll minAdjust = previous[t].second;
            ll nextNode = previous[t].first;
            ll current = t;
            while (nextNode!= -1){
                minAdjust = min(minAdjust, previous[current].second);
                current = nextNode;
                nextNode = previous[current].first;
            }
            returnVal+= minAdjust;
            nextNode = previous[t].first;
            current = t;
            while (nextNode!= -1){
                adjacencies[nextNode][current]-=minAdjust;
                adjacencies[current][nextNode]+=minAdjust;

                current = nextNode;
                nextNode = previous[current].first;
            }
        }
    }
    cout << returnVal;


    return 0;
}
