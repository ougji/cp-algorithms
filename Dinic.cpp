#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define all(v) v.begin(), v.end()

using namespace std;

int n, m;
vector<int> g[105];
ll cap[105][105];
ll flow[105][105];

void bfs(int s, int t, vector<int> &level)
{
    fill(all(level), 1e9);
    level[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (auto to : g[v])
        {
            if (cap[v][to] != flow[v][to] && level[to] > level[v] + 1)
            {
                level[to] = level[v] + 1;
                q.push(to);
            }
        }
    }
}

ll dfs(int v, int t, vector<int> &level, vector<int> &ptr, ll f)
{
    if (v == t)
        return f;
    if (!f)
        return 0;

    for (int &i = ptr[v]; i < g[v].size(); ++i)
    {
        int to = g[v][i];
        if (level[v] + 1 == level[to])
        {
            ll cur_flow = dfs(to, t, level, ptr, min(f, cap[v][to] - flow[v][to]));
            if (!cur_flow)
                continue;

            flow[v][to] += cur_flow;
            flow[to][v] -= cur_flow;
            return cur_flow;
        }
    }

    return 0;
}

ll max_flow(int s, int t)
{
    ll ans = 0;
    vector<int> level(n + 5);

    while (true)
    {
        bfs(s, t, level);
        if (level[t] == 1e9)
            break;

        ll cur_flow;
        vector<int> ptr(n + 5, 0);
        while (cur_flow = dfs(s, t, level, ptr, 1e18))
        {
            ans += cur_flow;
        }
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
