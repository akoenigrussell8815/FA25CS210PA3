//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Directions for DFS (students must use these)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// ----------------------------------------------------------
// DO NOT MODIFY: Maze generation
// ----------------------------------------------------------
void generateMaze(vector<vector<int>>& maze, int N, int M) {
    srand(time(0));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int roll = rand() % 100;
            maze[r][c] = (roll < 70) ? 0 : 1;   // 0 = open, 1 = wall
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Choose a random boundary cell that is open
// ----------------------------------------------------------
pair<int,int> chooseBoundaryCell(const vector<vector<int>>& maze) {
    int N = maze.size();
    int M = maze[0].size();

    while (true) {
        int side = rand() % 4;
        int r, c;

        if (side == 0) {          // top row
            r = 0;
            c = rand() % M;
        } else if (side == 1) {   // bottom row
            r = N - 1;
            c = rand() % M;
        } else if (side == 2) {   // left column
            r = rand() % N;
            c = 0;
        } else {                  // right column
            r = rand() % N;
            c = M - 1;
        }

        if (maze[r][c] == 0) {
            return {r, c};
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the maze with S and E markers
// ----------------------------------------------------------
void printMaze(const vector<vector<int>>& maze,
               int ent_r, int ent_c,
               int exit_r, int exit_c)
{
    int N = maze.size();
    int M = maze[0].size();

    cout << "\nMaze:\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (r == ent_r && c == ent_c) {
                cout << "S ";
            } else if (r == exit_r && c == exit_c) {
                cout << "E ";
            } else {
                cout << maze[r][c] << " ";
            }
        }
        cout << "\n";
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the reconstructed path
// Students must fill parent[][] correctly during DFS
// ----------------------------------------------------------
void printPath(pair<int,int> exitcell,
               const vector<vector<int>>& parent_r,
               const vector<vector<int>>& parent_c,
               int ent_r, int ent_c)
{
    int r = exitcell.first;
    int c = exitcell.second;

    vector<pair<int,int>> path;

    // Walk backward from exit to entrance
    while (!(r == ent_r && c == ent_c)) {
        path.push_back({r, c});
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        r = pr;
        c = pc;
    }
    path.push_back({ent_r, ent_c});

    cout << "\nPath from entrance to exit:\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << "(" << path[i].first << ", " << path[i].second << ")\n";
    }
}

// ----------------------------------------------------------
// STUDENTS IMPLEMENT DFS HERE
// Add arguments, return type, and logic
// ----------------------------------------------------------

//I used the parent row and column vectors as my stack and used recursion to traverse the graph.

bool dfs(int r, int c, //point of entry
        const vector<vector<int>>& maze,
        vector<vector<bool>>& visited,
        vector<vector<int>>& parent_r,
        vector<vector<int>>& parent_c,
        int exit_r, int exit_c) {

    for (int i = 0; i < 4; i++) { // this for loop just goes through the direction of each node as my recursion follows.
        if (r+dr[i] < maze.size() && r+dr[i] >= 0 && c+dc[i] < maze[0].size() && c+dc[i] >= 0) {
            if ((r+dr[i] == exit_r && c+dc[i] == exit_c)) { //this is my first base case, so if it reaches the end then it returns true all the way back to the original. Other base case is at the bottom.
                parent_c[r+dr[i]][c+dc[i]] = c;
                parent_r[r+dr[i]][c+dc[i]] = r;
                return true;
            }
            if (maze[r+dr[i]][c+dc[i]] == 0) { //checks if it's open
                if (visited[r+dr[i]][c+dc[i]] == false) { //checks if it's been visited :: if it is open and hasn't been visited then the code saves it's current spot and goes on to recur the code on the next node.
                    parent_c[r+dr[i]][c+dc[i]] = c;
                    parent_r[r+dr[i]][c+dc[i]] = r;
                    visited[r+dr[i]][c+dc[i]] = true;
                    c = c+dc[i];
                    r = r+dr[i];
                    if (dfs(r, c, maze, visited, parent_r, parent_c, exit_r, exit_c)) {
                        return true;
                    }
                    int temp_c = parent_c[r][c]; //If the node that was recurred is false or doesn't have a path to exit then it goes pac to the saved parent.
                    r = parent_r[r][c];
                    c = temp_c;
                }
            }
        }
    }

    return false;// Other Base case: If the code goes through every possible path and finds no exit, then it returns false and there is no path.

}


// ----------------------------------------------------------
// MAIN PROGRAM (students add DFS calls and logic)
// ----------------------------------------------------------
int main() {
    int N, M;

    cout << "Enter maze dimensions N M: ";
    cin >> N >> M;

    vector<vector<int>> maze(N, vector<int>(M));
    generateMaze(maze, N, M);

    // Pick entrance and exit
    pair<int,int> entrance = chooseBoundaryCell(maze);
    pair<int,int> exitcell = chooseBoundaryCell(maze);

    while (exitcell == entrance) {
        exitcell = chooseBoundaryCell(maze);
    }

    int ent_r = entrance.first;
    int ent_c = entrance.second;
    int exit_r = exitcell.first;
    int exit_c = exitcell.second;

    // Display the maze
    printMaze(maze, ent_r, ent_c, exit_r, exit_c);

    // Students must use these
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> parent_r(N, vector<int>(M, -1));
    vector<vector<int>> parent_c(N, vector<int>(M, -1));

    // ------------------------------------------------------
    // STUDENT WORK:
    // Call your DFS, track visited, and fill parent_r and parent_c
    // ------------------------------------------------------
    bool found = dfs(ent_r, ent_c, maze, visited, parent_r, parent_c, exit_r, exit_c);

    // ------------------------------------------------------
    // STUDENT WORK:
    // If found, print the path
    // ------------------------------------------------------
    if (found) {
        printPath(exitcell, parent_r, parent_c, ent_r, ent_c);
    } else {
        cout << "\nNo path exists.\n";
    }

    return 0;
}