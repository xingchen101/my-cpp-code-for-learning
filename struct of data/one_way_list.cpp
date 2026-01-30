#include<iostream>
using namespace std;
#define eletype int
    
struct listnode{
    int val;
    listnode* next;
    listnode(eletype x) : val(x),next(NULL){}
};
class list{
private:
    listnode* head;
    int size;
public:
    list() : head(NULL),size(0){}
    void print();
    void insert(int index,eletype value);
    void erase(int index);
    void push_back(eletype value);
    void push_front(eletype value);
    void pop_back();
    void pop_front();
    void clear();
    ~list() {clear();}
};

int main(){
    cout << 1;
    return 0;

}

void list::print(){
    listnode* cur=head;
    for(int i=0;i<size;++i){
        cout<<cur->val << ' ';
        cur=cur->next;
    }
    cout << endl;
    return;
}
void list::insert(int index,eletype value){
    if(index<0||index>size) return;
    listnode* cur=head;
    listnode* newnode=new listnode(value);
    if(index==0){
        newnode->next=cur;
        head=newnode;
    }
    else{
        for(int i=0;i<index-1;++i){
            cur = cur->next;
        }
        newnode->next=cur->next;
        cur->next=newnode;
    }
    size++;
    return;
}
void list::erase(int index){
    if(index<0||index>=size) return;
    listnode* cur=head;
    if(index==0){
        head=cur->next;
        delete cur;
    }
    else{
        for(int i=0;i<index-1;++i){
            cur=cur->next;
        }
        listnode* del=cur->next;
        cur->next=del->next;
        delete del;
    }
    size--;
    return;
}
void list::push_back(eletype value){
    insert(size,value);
    return;
}
void list::push_front(eletype value){
    insert(0,value);
    return;
}
void list::pop_back(){
    erase(size-1);
}
void list::pop_front(){
    erase(0);
}
void list::clear(){
    while(head!=NULL){
        listnode* cur=head;
        head=head->next;
        delete cur;
    }
    size=0;
    return;
}