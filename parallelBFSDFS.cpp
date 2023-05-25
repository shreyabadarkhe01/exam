#include <bits/stdc++.h>

#include <omp.h>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

node* buildTree(node* root) {
    int data;
    cout << "enter data: " << endl;
    cin >> data;
    root = new node(data);

    if (data == -1) {
        return NULL;
    }

    cout << "Enter data to insert to the left of " << data << endl;
    root->left = buildTree(root->left);

    cout << "Enter data to insert to the right of " << data << endl;
    root->right = buildTree(root->right);

    return root;
}

void parallelBFS(node* root) {
    if (root == NULL)
        return;

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        #pragma omp parallel for
        for (int i = 0; i < q.size(); i++) {
            node* currNode;
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
            }

            cout << currNode->data << " ";

            if (currNode->left)
                #pragma omp critical
                q.push(currNode->left);

            if (currNode->right)
                #pragma omp critical
                q.push(currNode->right);
        }
    }
}


int main() {
    node* root = NULL;
    root = buildTree(root);
    cout<<"Bfs-->";
    parallelBFS(root);
   
    return 0;
}
