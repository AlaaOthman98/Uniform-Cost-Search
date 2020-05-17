#include <bits/stdc++.h>
using namespace std;

typedef pair<int, string> node;

map<string, vector<node>> graph;
priority_queue<node, vector<node>, greater<node>> frontier, temp;
map<string, string> parent;

// to search frontier if a ciy is already exist and return the current cost to compare it.
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

// if we found a city with a cost smaller than its cost in the frontier, so we replace it using this function.
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

// Uniforn Cost Search Implementation.
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

        if (current_city == goal)
            return "reach goal";

        for (const pair<int, string> neighbour : graph[current_city])
        {
            string city = neighbour.second;
            int cost = neighbour.first + node.first;
            if (!(vis[city] || get_cost_from_frontier(city)))
            {
                frontier.push({cost, city});
                parent[city] = current_city;
            }
            else if (get_cost_from_frontier(city) > cost)
            {
                set_cost_in_frontier(city, cost);
                parent[city] = current_city;
            }
        }
    }
}

// get the optimal path after running UCS algorithm
void get_path(string src, string dest)
{
    vector<string> ans;
    for (string i = dest; i != src; i = parent[i])
    {
        ans.push_back(i);
    }
    ans.push_back(src);
    reverse(ans.begin(), ans.end());
    for (auto a : ans)
        cout << a << ", ";
    cout << endl;
}

int main()
{
    // Reading The Map From map.txt File
    freopen("map.txt", "r", stdin);

    /*
        * first it reads number of cities on the map
        * then iterate over this number and accept the name of each city and the number of its neighbours
        * then iterate over the number of neighbours and input the cost and the name of the neighbour city
        * last thing is to enter source and destionation cities to get the route between.
    */

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

    // entering source and destination cities
    string source, destination;
    cin >> source >> destination;

    // executes the algorithm and return the state of it
    string state = uniform_cost_search(source, destination);

    if (state == "reach goal")
    {
        cout << "Congratulations! We find the optimal path! Here it is: " << endl
             << endl;
        // print the path.
        get_path(source, destination);
    }
    else
    {
        // failure state
        cout << "Unfortunatly, We are very sorry, there is no solution for this problem right now." << endl;
    }

    return 0;
}