#include <iostream>
#include <vector>
template<typename T>
struct HardData{
    T data;
};
template<typename T>
std::ostream &operator<<(std::ostream &out, const HardData<T> &data) {
    out << data.data<<" ";
    return out;
}
template<typename T>
bool operator!=(const HardData<T> data1, const HardData<T> data2) {
    return data1.data != data2.data;
}
template<typename T, size_t size>
struct List {
    T mas[size];
    size_t length = 0;
};

template<typename T, size_t size>
List<T, size> &constructor(List<T, size> &is) {//1
    for (int i=0;i<size;i++){
        is.mas[i]=T();
    }
}

template<typename T, size_t size>
List<T, size> &destructor(List<T, size> &is) {//2
    for (int i=0;i<size;i++){
        is.mas[i]=T();
    }
}
template<typename T, size_t size>
size_t realsize(List<T, size> &is) {//3
    return is.length;
}

template<typename T, size_t size>
List<T, size> pushback(List<T, size> &is, T data) {//4
    if (realsize(is) == size) {
        std::cout << "List is full" << std::endl;
    } else {
        is.mas[realsize(is)] = data;
        is.length++;
    }
    return is;
}

template<typename T, size_t size>
List<T, size> pushindex(List<T, size> &is, unsigned int index, T data) {//5

    if (realsize(is) == size) {
        std::cout << "List is full" << std::endl;
    } else if (index < realsize(is)) {
        for (int i = realsize(is); is.mas[index] != T(); i--) {
            std::swap(is.mas[i - 1], is.mas[i]);
        }
        is.mas[index] = data;
        is.length++;

    } else {
        std::cout << "List have empty index before this" << std::endl;
    }
    return is;
}

template<typename T, size_t size>
T pophead(List<T, size> &is) {//6
    if (realsize(is) == 0) {
        std::cout << "List is empty" << std::endl;
    } else {
        T data = is.mas[0];
        is.mas[0] = T();

        for (int i =0; is.mas[realsize(is)-1] != T(); i++) {
            std::swap(is.mas[i], is.mas[i + 1]);
        }
        is.length--;
        return data;
    }
}

template<typename T, size_t size>
T poptail(List<T, size> &is) //7
{
    if (realsize(is) == 0) {
        std::cout << "list is empty" << std::endl;
        return T();
    } else {
        T data = is.mas[realsize(is) - 1];
        is.mas[realsize(is) - 1] = T();
        is.length--;
        return data;
    }
}

template<typename T, size_t size>
T popindex(List<T, size> &is, unsigned int index) {//8

    if (realsize(is) == 0) {
        std::cout << "List is empty" << std::endl;
        return T();
    } else {
        T data = is.mas[index];
        is.mas[index] = T();
        for (unsigned int i = index; is.mas[realsize(is)-1] != T(); i++) {
            std::swap(is.mas[i], is.mas[i + 1]);
        }
        is.length--;
        return data;
    }
}

template<typename T, size_t size>
T show(List<T, size> &is, unsigned int index) {// 9
    if (index == realsize(is)) {
        std::cout << "Element dont found" << std::endl;
        return T();
    } else {
        return is.mas[index];
    }
}

template<typename T, size_t size>
 int firstelem(List<T, size> &is, T data) {//10
    int i = 0;
    while (is.mas[i] != data && i < realsize(is)) {
        i++;
    }
    if (i == size) {
        std::cout << "Element not found" << std::endl;
        return -1;
    } else {
        return i;
    }
}

template<typename T, size_t size>
void print(List<T, size> &is) {//11
    for (int i = 0; i < realsize(is); i++) {
        std::cout << is.mas[i] << " ";
    }
    std::cout << std::endl;
}


int main() {
//    List<int,6> p;
//    constructor(p);
//    pushback(p,1);
//    pushback(p,2);
//    pushback(p,3);
//    pushindex(p,0,10);
//    pushindex(p,2,15);
//    pophead(p);
//    poptail(p);
//    popindex(p,0);
//    show(p,7);
//    firstelem(p,6);
//    print(p);
//    destructor(p);
    //
    std::vector<HardData<int>> dat(6);
    srand(time(nullptr));
    for (HardData<int>& da:dat){
        da.data=rand()%11;
    }
    List<HardData<int>,6> p1;
    constructor(p1);
    pushback(p1,dat[0]);
    pushback(p1,dat[1]);
    pushback(p1,dat[2]);
    pushindex(p1,0,dat[3]);
    pushindex(p1,2,dat[4]);
    print(p1);
    pophead(p1);
    poptail(p1);
    popindex(p1,0);
    show(p1,7);
    std::cout<<firstelem(p1,dat[1])<<std::endl;
    print(p1);
    destructor(p1);
    return 0;
}
