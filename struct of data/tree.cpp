#include <iostream>
using namespace std;

template <typename T>
struct listnode{
    T data;
    listnode<T>* next;
    listnode(T d) : data(d), next(NULL) {}
};

template <typename T>
struct treenode{
    T data;
    listnode<treenode<T>*>* childhead;
    treenode() : data(T()), childhead(NULL) {}
    ~treenode(){
        while(childhead){
            listnode<treenode<T>*>* tmp=childhead;
            childhead=tmp->next;
            delete tmp;
        }
    }
    void addchild(treenode<T>* node){
        listnode<treenode<T>*>* childnode=new listnode<treenode<T>*>(node);
        if(childhead==NULL) childhead=childnode;
        else{
            childnode->next=childhead;
            childhead=childnode;
        }
    }
};

template <typename T>
class tree{
private:
    treenode<T>* nodes;
    treenode<T>* root;
public:
    tree();
    tree(int maxnodes);
    ~tree();
    treenode<T>* gettreenode(int id);
    void setroot(int rootid);
    void addchild(int parentid, int sonid);
    void assigndata(int nodeid, T data);
    void print(treenode<T>* node = NULL);
};

template <typename T>
tree<T>::tree(){
    nodes=new treenode<T>[100001];
    root=NULL;
}

template <typename T>
tree<T>::tree(int maxnodes){
    nodes=new treenode<T>[maxnodes];
    root=NULL;
}

template <typename T>
tree<T>::~tree(){
    delete[] nodes;
}

template <typename T>
treenode<T>* tree<T>::gettreenode(int id){
    return &nodes[id];
}

template <typename T>
void tree<T>::setroot(int rootid){
    if(rootid<0) return;
    root=gettreenode(rootid);
    return;
}

template <typename T>
void tree<T>::addchild(int parentid, int sonid){
    nodes[parentid].addchild(&nodes[sonid]);
    return;
}

template <typename T>
void tree<T>::assigndata(int nodeid, T data){
    nodes[nodeid].data=data;
    return;
}

template <typename T>
void tree<T>::print(treenode<T>* node){
    if(node==NULL) node=root;
    if(node) cout << node->data << ' ';
    listnode<treenode<T>*>* tmp=node->childhead;
    while(tmp){
        print(tmp->data);
        tmp=tmp->next;
    }
}

int main(){
    tree<int> a;
    a.assigndata(0,0);
    a.assigndata(1,1);
    a.assigndata(2,2);
    a.setroot(0);
    a.addchild(0,1);
    a.addchild(1,2);
    a.print();
    return 0;
}