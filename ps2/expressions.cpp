#include<iostream>
#include<stack>
#include<queue>
#include<string>

using namespace std;

struct node {
    char data;
    struct node* left;
    struct node* right;
};
node* root;
string s;

void reverseLevelOrder() {
    stack <node*> S;
    queue <node*> Q;
    Q.push(root);

    while (Q.empty() == false)
    {
        root = Q.front();
        Q.pop();
        S.push(root);

        if (root->right)
            Q.push(root->right);

        if (root->left)
            Q.push(root->left);
    }

    while (S.empty() == false)
    {
        root = S.top();
        cout << root->data;
        S.pop();
    }
}
node* newNode(char data) {
    node* temp = new node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return (temp);
}
node* make_tree() {
    stack<node *> S;
    int len = s.size();
    for(int i = 0; i < len; ++i) {
        node *fresh_node = newNode(s[i]);
        if (isupper(s[i])) {
            node *right = S.top();
            S.pop();
            node *left = S.top();
            S.pop();
            fresh_node->right = left;
            fresh_node->left = right;
        }
        S.push(fresh_node);
    }
    return S.top();
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        root = make_tree();
        reverseLevelOrder();
        cout << "\n";
    }
    return 0;
}
