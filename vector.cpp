#include <iostream>
using namespace std;

#define type int

class vector {
private:
    type* data;
    int size;
    int capacity;
    void addcapacity(int needcapacity);

public:
    vector();
    vector(int needcapacity);
    vector(int needcapacity, int zhi);        // 指定容量并用 zhi 初始化所有元素
    ~vector();                                // 析构函数：释放动态内存
    void push_back(type zhi);                 // 在末尾添加一个元素（可能触发扩容）
    void pop_back();                          // 删除最后一个元素（不释放内存）
    void insert(int place, type zhi);         // 在下标 place 处插入元素
    void erase(int place);                    // 删除下标 place 处的元素
    void resize(int needsize, int zhi);       // 调整容器大小（变大用 zhi 填充，变小截断）
    void reserve(int needcapacity);           // 预先分配至少 needcapacity 的容量
    void clear();                             // 清空所有元素（size = 0，不释放内存）
    void swap(vector& other);                 // 与另一个 vector 交换内容（O(1) 时间）
    bool empty() const;                       // 判断容器是否为空
    int get_size() const { return size; }     // 返回当前元素个数
    int get_capacity() const { return capacity; } // 返回当前分配的容量
    type& operator[](int index);              // 非 const 下标访问（可修改）
    const type& operator[](int index) const;  // const 对象的只读下标访问
};

vector::vector() : data(nullptr), size(0), capacity(0) {
}

// 构造函数：指定初始容量（不初始化元素值）
vector::vector(int needcapacity) : size(0), capacity(needcapacity) {
    if (needcapacity <= 0) {
        // 若请求容量无效，则视为创建空容器
        data = nullptr;
        capacity = 0;
    } else {
        // 分配指定大小的内存，但不初始化元素（size=0）
        data = new type[needcapacity];
    }
}

// 构造函数：指定容量并用 zhi 初始化所有元素
vector::vector(int needcapacity, int zhi) : size(needcapacity), capacity(needcapacity) {
    if (needcapacity <= 0) {
        data = nullptr;
        size = 0;
        capacity = 0;
    } else {
        data = new type[needcapacity];
        // 将所有元素初始化为 zhi
        for (int i = 0; i < needcapacity; ++i) {
            data[i] = zhi;
        }
    }
}

// 析构函数：安全释放动态分配的内存
vector::~vector() {
    delete[] data;  // delete[] nullptr 是合法且安全的操作
}

// 在容器末尾添加一个元素
void vector::push_back(type zhi) {
    // 如果当前容量已满，需要扩容
    if (size == capacity) {
        addcapacity(size + 1);  // 至少需要 size+1 的容量
    }
    data[size] = zhi;  // 将新元素放到末尾
    size++;            // 更新元素个数
}

// 删除最后一个元素（不释放内存，仅减小 size）
void vector::pop_back() {
    if (size > 0) {
        size--;  // 逻辑上移除最后一个元素
    }
}

// 在指定位置插入一个元素（place 必须在 [0, size] 范围内）
void vector::insert(int place, type zhi) {
    // 越界检查：插入位置不能小于 0 或大于当前 size
    if (place < 0 || place > size) return;

    // 容量不足则扩容
    if (size == capacity) {
        addcapacity(size + 1);
    }

    // 从后往前移动元素，为新元素腾出空间
    for (int i = size - 1; i >= place; --i) {
        data[i + 1] = data[i];
    }

    data[place] = zhi;  // 插入新元素
    size++;             // 元素个数加一
}

// 删除指定位置的元素
void vector::erase(int place) {
    if (place < 0 || place >= size) return;  // 越界保护

    // 将后面的元素向前移动，覆盖被删除的元素
    for (int i = place; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;  // 元素个数减一
}

void vector::addcapacity(int needcapacity) {
    // 若当前容量为 0，先设为 1（避免后续计算出错）
    if (capacity == 0) {
        capacity = 1;
    }

    // 计算 1.5 倍新容量（使用整数运算：capacity + capacity/2）
    int new_capacity = capacity + capacity / 2;

    // 如果 1.5 倍仍小于所需容量，则直接使用 needcapacity
    // 这样在需要大量空间时能一步到位，避免多次小步扩容
    if (new_capacity < needcapacity) {
        new_capacity = needcapacity;
    }

    // 分配新的更大内存块
    type* newData = new type[new_capacity];

    // 将旧数据逐个拷贝到新内存
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }

    // 释放旧内存
    delete[] data;

    // 更新指针和容量
    data = newData;
    capacity = new_capacity;
}

// 显式预留容量（用户调用，仅当 needcapacity > 当前 capacity 时才扩）
void vector::reserve(int needcapacity) {
    if (needcapacity <= capacity) return;  // 已足够，无需操作
    addcapacity(needcapacity);             // 委托给内部扩容函数
}

// 调整容器大小
void vector::resize(int needsize, int zhi) {
    if (needsize < 0) needsize = 0;  // 防止负数

    // 如果新大小超过当前容量，先扩容
    if (needsize > capacity) {
        reserve(needsize);
    }

    if (needsize <= size) {
        // 缩小：只需更新 size，不释放内存
        size = needsize;
    } else {
        // 扩大：用 zhi 填充新增的位置
        for (int i = size; i < needsize; ++i) {
            data[i] = zhi;
        }
        size = needsize;
    }
}

// 与另一个 vector 交换内容（高效 O(1) 操作）
void vector::swap(vector& other) {
    type* tmp_ptr = this->data;
    int tmp_size = this->size;
    int tmp_cap = this->capacity;

    this->data = other.data;
    this->size = other.size;
    this->capacity = other.capacity;

    other.data = tmp_ptr;
    other.size = tmp_size;
    other.capacity = tmp_cap;
}

// 判断容器是否为空
bool vector::empty() const {
    return size == 0;
}

// 非 const 下标访问（允许修改元素）
type& vector::operator[](int index) {
    return data[index];
}

// const 对象的只读下标访问
const type& vector::operator[](int index) const {
    return data[index];
}

int main(){
    return 0;
}
