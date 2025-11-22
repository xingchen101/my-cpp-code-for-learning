//                                  手搓vector容器
#include<iostream>
using namespace std;
#define type int    //type是vector的类型

class vector{
public:
    type* group;
    int size;
    int capacity;
    vector(){
        group=new type[0];  //group是vector数组
        size=0;
        capacity=0;
    };
    ~vector(){
        delete[] group;
    }
};
void pushback(vector& a,type zhi);  //在数组最后面插入元素,a是目标数组
void insert(vector& a,int place,type zhi);  //在数组某一位置插入元素，place是插入位置的下标
void popback(vector& a);    //删除数组的最后一个元素
void erase(vector& a,int place);    //删除数组的某个下标的元素
void addcapacity(vector& a,int needcapacity);   //增加数组容量
void reserve(vector& a,int needcapacity);    //重新定义数组容量
void resize(vector& a,int needsize,int zhi);    //重新定义数组大小，zhi是初始化数组新添加的元素
void swap(vector&a,vector&b);   //交换a和b数组
bool empty(vector& a); //判断a是否为空

int main(){
    vector a,b;
    pushback(a,1);
    pushback(a,1);
    resize(b,10,6);
    swap(a,b);
    cout << !empty(a);
    return 0;
}

void pushback(vector& a,type zhi){
    if(a.size==a.capacity) addcapacity(a,a.size+1);
    a.group[a.size] =zhi;
    a.size++; 
}
void insert(vector& a,int place,type zhi){
    if(a.size==a.capacity) addcapacity(a,a.size+1);
    for(int i=a.size-1;i>=place;--i){
        a.group[i+1]=a.group[i];
    }
    a.group[place]=zhi;
}
void popback(vector& a){
    a.size--;
    a.group[a.size]=0;
}
void erase(vector& a,int place){
    for(int i=place;i<(a.size-2);++i){
        a.group[i]=a.group[i+1];
    }
    a.size--;
    a.group[a.size]=0;
}
void addcapacity(vector& a,int needcapacity){
    a.capacity*=1.5;
    if(a.capacity<=needcapacity) a.capacity=needcapacity;
    type *group1=new type[a.capacity];
    for(int i=0;i<a.size;i++){
            group1[i]=a.group[i];
    }
    delete[] a.group;
    a.group=group1;
}
void reserve(vector& a,int needcapacity){
    if(needcapacity<=a.capacity) return;
    a.capacity=needcapacity;
    type *group1=new type[a.capacity];
    for(int i=0;i<a.size;i++){
            group1[i]=a.group[i];
    }
    delete[] a.group;
    a.group=group1;
}
void resize(vector& a,int needsize,int zhi){
    int needcapacity=needsize;
    if(needcapacity>=a.capacity) addcapacity(a, needcapacity);
    if(needsize<=a.size){
        for(int i=needsize;i<a.size;i++){
            a.group[i]=0;
        }
        a.size=needsize;
    }
    else{
        for(int i=a.size;i<needsize;i++){
            a.group[i]=zhi;
        }
        a.size=needsize;
    }
}
void swap(vector&a,vector&b){
    type* zhizheng=a.group;
    int size=a.size;
    int capacity=a.capacity;
    a.group=b.group;
    a.size=b.size;
    a.capacity=b.capacity;
    b.group=zhizheng;
    b.size=size;
    b.capacity=capacity;
}
bool empty(vector& a){
    if(a.size!=0) return 0;
    else return 1;
}