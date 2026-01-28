//                            stack_sequence
#include <iostream>
#include <stdexcept>  // 用于 std::runtime_error
using namespace std;
#define eletype int
class stack_s {
private:
    eletype* date;
    int size_;
    int capacity_;
    void addcapacity_();  // 声明

public:
    stack_s();            // 构造函数声明
    ~stack_s();           // 析构函数声明
    void push(eletype element);
    void pop();
    eletype top() const;
    bool empty() const;
    int size() const;
};

// 构造函数
stack_s::stack_s() : capacity_(10), date(new eletype[capacity_]), size_(0) {}

// 析构函数
stack_s::~stack_s() {
    delete[] date;
}

// 扩容函数
void stack_s::addcapacity_() {
    capacity_ *= 2;
    eletype* newdate = new eletype[capacity_];
    for (int i = 0; i < size_; ++i) {
        newdate[i] = date[i];
    }
    delete[] date;
    date = newdate;
}

// push
void stack_s::push(eletype element) {
    if (size_ == capacity_) {
        addcapacity_();
    }
    date[size_] = element;
    size_++;
}

// pop
void stack_s::pop() {
    if (size_ > 0) {
        size_--;
    }
}

// top
eletype stack_s::top() const {
    if (size_ == 0) {
        throw runtime_error("Top of empty stack");
    }
    return date[size_ - 1];
}

// empty
bool stack_s::empty() const {
    return size_ == 0;
}

// size
int stack_s::size() const {
    return size_;
}

// ———————— 主函数 ————————
int main() {
    stack_s a;
    a.push(1);
    a.push(2);
    a.pop();
    cout << a.size() << endl;
    return 0;
}