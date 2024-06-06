#include <iostream>
#include <string>
using namespace std;

class lexicon {
public:
    lexicon() {
        root = NULL;
    }

    ~lexicon() {};

    void insert(const string &s) {
        root = InsertNode(root, s);
    }

    int lookup(const string &s) const {
        node *p = SearchNode(root, s);
        if (p != NULL) {
            return p->count;
        }
        else {
            return 0;
        }
    }

    int depth(const string &s) {
        int num = lookup(s);
        if (num > 0) {
            int d = NodeDepth(root, s);
            return d;
        }
        else {
            return -1;
        }
    }

    void replace(const string &s1, const string &s2) {
        if (lookup(s1) > 0) {
            int count1 = 0;
            node *r1 = SearchNode(root, s1);
            count1 = r1->count;
            r1->count = 0;
            root = DeleteNode(root, s1);
            if (lookup(s2) == 0) {
                insert(s2);
                node *r2 = SearchNode(root, s2);
                r2->count = count1;
            }
            else {
                node *r2 = SearchNode(root, s2);
                r2->count += count1;
            }
        }
    }

    friend ostream & operator << (ostream &out, const lexicon &l) {
        l.inOrder(l.root);
        return out;
    }
private:
    struct node {
        string data;
        node *left, *right;
        int count;
        node (const string &s): data(s), left(NULL), right(NULL), count(1){}
    };

    node *root;

    static node* InsertNode (node* r, const string &s) {
        if (r == NULL) {
            return new node(s);
        }
        if (s == r->data) {
            ++(r->count);
            r->data = s;
        }
        else if (s < r->data) {
            r->left = InsertNode(r->left, s);
        }
        else {
            r->right = InsertNode(r->right, s);
        }
        return r;
    }

    static node* SearchNode (node *r, const string &s) {
        if (r == NULL) {
            return NULL;
        }
        if (r->data == s) {
            return r;
        }
        if (s < r->data) {
            return SearchNode(r->left, s);
        }
        else {
            return SearchNode(r->right, s);
        }
    }

    static int NodeDepth (node *r, const string &s) {
        if (r == NULL) {
            return 0;
        }
        if (r->data > s) {
            return 1 + NodeDepth(r->left, s);
        }
        else if (r->data < s) {
            return 1 + NodeDepth(r->right, s);
        }
        else {
            return 0;
        }
    }

    static node* minValueNode(node *r) {
        node *current = r;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    static node* DeleteNode (node *r, const string &s) {
        if (r == NULL) {
            return r;
        }
        if (s < r->data) {
            r->left = DeleteNode(r->left, s);
        }
        else if (s > r->data) {
            r->right = DeleteNode(r->right, s);
        }
        else {
            if ((r->left == NULL) && (r->right == NULL)) {
                return NULL;
            }
            else if (r->left == NULL) {
                node *temp = r->right;
                delete r;
                return temp;
            }
            else if (r->right == NULL) {
                node *temp = r->left;
                delete r;
                return temp;
            }
            node *temp = minValueNode(r->left);
            r->data = temp->data;
            r->count = temp->count;
            r->left = DeleteNode(r->left, r->data);
        }
        return r;
    }

    static void inOrder(const node *r) {
        if (r == NULL) return;
        inOrder(r->left);
        cout << r->data << " " << r->count << endl;
        inOrder(r->right);
    }
};