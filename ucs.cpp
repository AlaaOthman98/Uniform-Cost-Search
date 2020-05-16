#include <bits/stdc++.h>
using namespace std;

bool compare(const pair<int, string> &a, const pair<int, string> &b)
{
    return a.first < b.first;
}

typedef pair<int, string> node;

map<string, vector<node>> graph;
priority_queue<node, vector<node>, greater<node>> frontier, temp;
map<string, string> parent;

int get_cost_from_frontier(string city)
{
    temp = frontier;

    while (!temp.empty())
    {
        auto node = temp.top();
        if (node.second == city)
            return node.first;
        temp.pop();
    }

    return 0;
}

void set_cost_in_frontier(string city, int new_cost)
{
    temp = frontier;
    frontier = priority_queue<node, vector<node>, greater<node>>();

    while (!temp.empty())
    {
        auto node = temp.top();
        if (node.second == city)
            node.first = new_cost;
        temp.pop();
        frontier.push(node);
    }
}

string uniform_cost_search(string source, string goal)
{
    pair<int, string> node;
    map<string, bool> vis;

    node = {0, source};
    frontier.push(node);
    while (1)
    {
        if (frontier.empty())
            return "failure";

        node = frontier.top();
        frontier.pop();
        string current_city = node.second;
        vis[current_city] = 1; // visited

        // cout << current_city << endl;

        if (current_city == goal)
            return "reach goal";

        for (const pair<int, string> neighbour : graph[current_city])
        {
            string city = neighbour.second;
            int cost = neighbour.first;
            if (!(vis[city] || get_cost_from_frontier(city)))
            {
                cost += node.first;
                frontier.push({cost, city});
                parent[city] = current_city;
            }
            else if (get_cost_from_frontier(city) > cost)
            {
                set_cost_in_frontier(city, cost);
            }
        }
    }
}

void get_path(string src, string dest)
{
    vector<string> ans;
    for (string i = dest; i != src; i = parent[i])

        ans.push_back(i);

    for (auto a : ans)

        cout << a << endl;
    cout << src <
}

int main()
{
    freopen("input.txt", "r", stdin);
    // Reading The Map
    int number_of_cities;
    cin >> number_of_cities;

    for (int i = 0; i < number_of_cities; i++)
    {
        string source;
        cin >> source;
        int number_of_neighbours;
        cin >> number_of_neighbours;
        graph[source] = vector<pair<int, string>>(number_of_neighbours);
        for (int j = 0; j < number_of_neighbours; j++)
        {
            int cost;
            string neighbour;
            cin >> cost >> neighbour;
            graph[source][j] = {cost, neighbour};
        }
    }

    cout << uniform_cost_search("Arad",
                                "Bucharest")
         << endl;

    get_path("Arad", "Bucharest");

    return 0;
}