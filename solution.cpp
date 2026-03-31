#include <iostream>
#include <vector>

using namespace std;

int D;
long long n;
vector<int> leaf_states;

// Process all leaves in the subtree and record their states
// node: current node index (1-indexed binary tree)
// balls: number of balls passing through this node
// Returns which leaf the last ball lands in
int solve(int node, long long balls) {
    // Check if this is a leaf node
    // Leaves are at depth D, which are nodes from 2^(D-1) to 2^D - 1
    int first_leaf = 1 << (D - 1);
    int last_leaf = (1 << D) - 1;

    if (node >= first_leaf && node <= last_leaf) {
        // This is a leaf - store its state
        leaf_states[node - first_leaf] = (balls % 2);
        return node;
    }

    // Internal node
    // With k balls:
    // - Balls 1, 3, 5, ... (odd positions) go left -> ceiling(k/2) balls go left
    // - Balls 2, 4, 6, ... (even positions) go right -> floor(k/2) balls go right

    long long left_balls = (balls + 1) / 2;
    long long right_balls = balls / 2;

    int last_pos;
    if (balls % 2 == 1) {
        // Odd number of balls, last one goes left
        last_pos = solve(2 * node, left_balls);
        // Still need to process right subtree for complete leaf states
        solve(2 * node + 1, right_balls);
    } else {
        // Even number of balls, last one goes right
        // Process left subtree first, then right
        solve(2 * node, left_balls);
        last_pos = solve(2 * node + 1, right_balls);
    }

    return last_pos;
}

int main() {
    cin >> D >> n;

    int num_leaves = 1 << (D - 1);
    leaf_states.resize(num_leaves, 0);

    int last_position = solve(1, n);

    cout << last_position << endl;

    for (int i = 0; i < num_leaves; i++) {
        cout << leaf_states[i];
        if (i < num_leaves - 1) cout << " ";
    }
    cout << endl;

    return 0;
}

