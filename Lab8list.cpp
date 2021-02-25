#include <iostream>
#include <vector>

template<typename T>
struct harddata {
    T data;
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const harddata<T> &data) {
    out << data.data << std::endl;
    return out;
}

template<typename T>
bool operator!=(const harddata<T> data1, const harddata<T> data2) {
    return data1.data != data2.data;
}

template<typename T>
struct Node {
    Node *pNext = nullptr;
    Node *pPrev = nullptr;
    T data = T();
};
template<typename T>
struct List {
    Node<T> *top;
    Node<T> *tail;
};

template<typename T>
List<T> &constructor(List<T> &is) //1
{
    is.top = nullptr;
    is.tail = nullptr;
    return is;
}

template<typename T>
List<T> &pushtop(List<T> &is, T data) //4
{
    Node<T> *point = new Node<T>;
    point->data = data;
    if (is.top == nullptr) {
        is.tail = point;
    } else {
        is.top->pPrev = point;
        point->pNext = is.top;
    }
    point->pPrev = is.tail;
    is.top = point;
    is.tail->pNext = is.top;
    return is;
}

template<typename T>
List<T> &pushtail(List<T> &is, T data) //5
{
    Node<T> *point = new Node<T>;
    point->data = data;
    if (is.tail == nullptr) {
        is.top = point;
    } else {
        is.tail->pNext = point;
        point->pPrev = is.tail;
    }
    point->pNext = is.top;
    is.tail = point;
    is.top->pPrev = is.tail;
    return is;
}

template<typename T>
List<T> &pushindex(List<T> &is, unsigned int index, T data) //6
{
    if (index == 0) {
        pushtop(is, data);
    } else if (index == size(is)) {
        pushtail(is, data);
    } else if (index < size(is)) {
        Node<T> *iter = is.top->pNext;
        for (int i = 1; i < index; i++) {
            iter = iter->pNext;
        }
        Node<T> *point = new Node<T>;
        point->data = data;
        point->pPrev = iter->pPrev;
        iter->pPrev->pNext = point;
        iter->pPrev = point;
        point->pNext = iter;
    }
    return is;
}

template<typename T>
List<T> &pushukaz(List<T> &is, Node<T> *ukaz, T data) {
    if (ukaz == is.tail) {
        pushtail(is, data);
    } else {
        Node<T> *point = new Node<T>;
        ukaz->pNext->pPrev = point;
        point->pNext = ukaz->pNext;
        ukaz->pNext = point;
        point->pPrev = ukaz;
    }

    return is;
}

template<typename T>
unsigned int size(const List<T> &is) //3
{
    int i = 0;
    if (is.top != nullptr) {
        for (Node<T> *iter = is.top; iter != is.tail; iter = iter->pNext) {
            i++;
        }
        i++;
    }
    return i;
}

template<typename T>
T poptop(List<T> &is) //8
{
    T data;
    if (is.top == nullptr) {
        std::cout << "List is empty" << std::endl;
        return T();
    } else if (is.top == is.tail) {
        data = is.top->data;
        Node<T> *point = is.top;
        is.top = nullptr;
        is.tail = nullptr;
        delete point;
    } else {
        data = is.top->data;
        Node<T> *point = is.top;
        is.top = is.top->pNext;
        is.tail->pNext = is.top;
        is.top->pPrev = is.tail;
        delete point;
    }
    return data;
}

template<typename T>
T poptail(List<T> &is) //9
{
    T data;
    if (is.tail == nullptr) {
        std::cout << "List is empty" << std::endl;
        return T();
    } else if (is.top == is.tail) {
        data = is.tail->data;
        Node<T> *point = is.tail;
        is.top = nullptr;
        is.tail = nullptr;
        delete point;
    } else {
        data = is.tail->data;
        Node<T> *point = is.tail;
        is.tail = is.tail->pPrev;
        is.top->pPrev = is.tail;
        is.tail->pNext = is.top;
        delete point;
    }
    return data;
}

template<typename T>
T popindex(List<T> &is, unsigned int index) // 10
{
    if (index < size(is)) {
        Node<T> *iter = is.top;
        for (int i = 0; i < index; i++) {
            iter = iter->pNext;
        }
        T data = iter->data;
        if (iter == is.top) {
            poptop(is);
        } else if (iter == is.tail) {
            poptail(is);
        } else {
            iter->pPrev->pNext = iter->pNext;
            iter->pNext->pPrev = iter->pPrev;
            delete iter;
        }
        return data;
    } else { return T(); }
}

template<typename T>
T popukaz(List<T> &is, Node<T>(*ukaz)) // 11
{
    if (is.top == nullptr) {
        std::cout << "list dont have element" << std::endl;
        return T();
    } else {
        T data = ukaz->data;
        if (ukaz == is.top) {
            poptop(is);
        } else if (ukaz == is.tail) {
            poptail(is);
        } else {
            ukaz->pPrev->pNext = ukaz->pNext;
            ukaz->pNext->pPrev = ukaz->pPrev;
            delete ukaz;
        }
        return data;
    }
}

template<typename T>
T show(const List<T> &is, unsigned int index) //12
{
    if (index < size(is)) {
        Node<T> *iter = is.top;
        for (int i = 0; i < index; i++) {
            iter = iter->pNext;
        }
        std::cout << iter->data << std::endl;
        return iter->data;
    } else {
        std::cout << "the index is clear" << std::endl;
        return T();
    }
}

template<typename T>
int search(const List<T> &is, T data) //13
{
    unsigned int i = 0;
    // Node<T> *iter = is.top;
    for (Node<T> *iter = is.top; iter->data != data && i <= size(is); iter = iter->pNext, i++) {}
    if (i < size(is)) {
        std::cout << i << std::endl;
        return i;
    } else {
        std::cout << "list dont have this data" << std::endl;
        return -1;
    }
}

template<typename T>
void print(const List<T> &is) //14
{
    if (is.top == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else {
        Node<T> *iter = is.top;
        do {
            std::cout << iter->data << " ";
            iter = iter->pNext;
        } while (iter != is.top);
        std::cout << std::endl;
    }
}

template<typename T>
List<T> &distructor(List<T> &is) //2
{
    if (is.top == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else {
        while (is.tail != nullptr) {
            is.top = is.top->pNext;
            delete is.top->pPrev;
            is.top = nullptr;
            is.tail = nullptr;
        }
    }
    return is;
}


int main() {
    List<int> p;
    constructor(p);
    pushtail(p, 13);
    print(p);
    pushtail(p, 60);
    print(p);
    pushtail(p, 90);
    print(p);
    pushtop(p, 9);
    print(p);
    pushindex(p, 0, 20);
    search(p, 50);
    print(p);
    poptop(p);
    print(p);
    poptail(p);
    print(p);
    popindex(p, 2);
    print(p);
    size(p);
    show(p, 0);
    distructor(p);
    /////
    std::vector<harddata<int>> dat(6);
    srand(time(nullptr));
    for (harddata<int> &da:dat) {
        da.data = rand() % 11;
    }
    List<harddata<int>> p1;
    constructor(p1);
    pushtail(p1, dat[0]);
    pushtail(p1, dat[1]);
    pushtail(p1, dat[2]);
    pushindex(p1, 0, dat[3]);
    pushindex(p1, 2, dat[4]);
    print(p1);
    poptop(p1);
    poptail(p1);
    popindex(p1, 0);
    show(p1, 7);
    print(p1);
    distructor(p1);
    return 0;


    return 0;
}