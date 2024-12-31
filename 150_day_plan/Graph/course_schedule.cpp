#include "iostream"
#include <vector>
#include <queue>

using namespace std;

bool khansAlgo(int n, vector<int> &indegree, vector<vector<int>> &adj) {
    queue<int> q;
    vector<int> topoOrder; 

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int course = q.front();
        topoOrder.push_back(course);
        q.pop();

        for (int neighbour : adj[course]) {
            indegree[neighbour] -= 1;
            if (indegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    if (topoOrder.size() == n) {
        return true;
    }
    return false;
}

int main() {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{0, 1}, {1, 0}};
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    bool is_graduation_possible = false;

    for (auto course : prerequisites) {
        int course_a = course[0];
        int course_b = course[1];
        adj[course_b].push_back(course_a);
        indegree[course_a] += 1;
    }

    is_graduation_possible = khansAlgo(numCourses, indegree, adj);

    cout << "is_graduation_possible " << is_graduation_possible << endl;

    return 0;
}