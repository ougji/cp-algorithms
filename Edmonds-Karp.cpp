#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define all(v) v.begin(), v.end()

using namespace std;

int n, m;
vector<int> g[105];
ll cap[105][105];
ll flow[105][105];

ll bfs(int s, int t, vector<int> &pr)
{
    vector<ll> d(n + 5, 0);
    fill(all(pr), -1);

    d[s] = 1e18;
    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (auto to : g[v])
        {
            // d[v]
            ll cur_flow = cap[v][to] - flow[v][to];
            if (d[to] < min(d[v], cur_flow))
            {
                d[to] = min(d[v], cur_flow);
                pr[to] = v;
                q.push(to);
            }
        }
    }

    return d[t];
}

ll max_flow(int s, int t)
{
    ll ans = 0;
    ll cur_flow;
    vector<int> pr(n + 5);

    while (cur_flow = bfs(s, t, pr))
    {
        ans += cur_flow;
        // cout << cur_flow << ": ";

        int cur = t;
        while (cur != s)
        {
            int prev = pr[cur];
            flow[prev][cur] += cur_flow;
            flow[cur][prev] -= cur_flow;
            cur = prev;
            // cout << cur << " ";
        }
        // cout << "\n";
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        g[u].pb(v);
        g[v].pb(u);

        cap[u][v] = c;
    }

    cout << max_flow(1, n);
}
