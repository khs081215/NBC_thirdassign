#include <iostream>
#include <algorithm>

using namespace std;

//주어진 문제에는 없지만 임의로 Item 클래스를 만들었다.
class Item {
private:
    string name_;
    int price_;
public:
    Item(string name = "knife", int price = 50000) {
        name_ = name;
        price_ = price;
    }
    void PrintInfo() const {
        cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
    }
    int GetPrice() const {
        return price_;
    }
};

bool compareItemsByPrice(const Item& a, const Item& b) {
    return a.GetPrice() < b.GetPrice();
}

template<typename T>
class Inventory {
private:
    T* pItems_;
    int capacity_;
    int size_;



public:
    Inventory(int capacity=10) {
        if (capacity <= 0) {
            capacity = 1;
        }
        size_ = 0;
        capacity_ = capacity;
        pItems_ = new T[capacity_];
    }

    Inventory(const Inventory<T>& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            pItems_[i] = other.pItems_[i];
        }
        cout << "인벤토리 복사 완료" << endl;
    }

    void Assign(const Inventory<T>& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        delete[] pItems_;
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            pItems_[i] = other.pItems_[i];
        }
        cout << "이미 존재하는 인벤토리에 복사 완료" << endl;
    }

    void SortItems() {
        sort(&pItems_[0], &pItems_[size_], compareItemsByPrice);
    }

    ~Inventory() {
        delete[] pItems_;
        pItems_ = nullptr;
    }
    void AddItem(const T& item) {
        if (size_ < capacity_) {
            pItems_[size_] = item;
            size_ += 1;
        }
        else {
            Resize(capacity_ * 2);
            AddItem(item);
            // cout << "인벤토리가 꽉 찼습니다!" << endl;
        }
    }
    void Resize(int newCapacity) {
        if (newCapacity > capacity_) {
            T* pItembuffer = new T[newCapacity];
            for (int i = 0; i < size_; ++i) {
                pItembuffer[i] = pItems_[i];
            }
            delete[] pItems_;
            pItems_ = pItembuffer;
            capacity_ = newCapacity;
        }
        else if(newCapacity<capacity_){

        }
    }
    void RemoveLastItem() {
        if (size_ == 0) {
            cout << "인벤토리가 비어있습니다." << endl;
        }
        else {
            size_ -= 1;
        }
    }
    int GetSize() const {
        return size_;
    }
    int GetCapacity() const {
        return capacity_;
    }
    void PrintAllItems() const {
        if (size_ == 0) {
            cout << "(비어있음)" << endl;
        }
        else {
            cout << capacity_ << " 용량  " << size_ << " 사이즈" << endl;
            for (int i = 0; i < size_;i++) {
                pItems_[i].PrintInfo();
            }
        }
    }
};





int main() 
{
    Item i1;
    Item i2("Axe", 9000);
    Item i3("Wand", 100000);
    cout << "Int형 인벤토리 출력\n";
    Inventory<int> intInventory(20);
    intInventory.AddItem(5);
    intInventory.AddItem(3);
    cout << "Int인벤토리에 5, 3 정수 추가\n";
    cout << "Int인벤토리 "<<intInventory.GetCapacity() << " 용량  " << intInventory.GetSize() << " 사이즈\n" << endl;


    cout << "빈 인벤토리 출력\n";
    Inventory<Item> myInventory;
    myInventory.PrintAllItems();
    cout << "\n";
    cout << "아이템 1번 추가\n";
    myInventory.AddItem(i1);
    myInventory.PrintAllItems();
    cout << "\n";
    cout << "아이템 2,3번 추가\n";
    myInventory.AddItem(i2);
    myInventory.AddItem(i3);
    myInventory.PrintAllItems();
    cout << "\n";
    cout << "아이템 제거\n";
    myInventory.RemoveLastItem();
    myInventory.PrintAllItems();
    cout << "\n";
    cout << "인벤토리 깊은 복사(생성자)\n";
    Inventory<Item> friendInventory(myInventory);
    friendInventory.PrintAllItems();
    cout << "\n";
    cout << "인벤토리 새로 생성\n";
    Inventory<Item> bestfriendInventory;
    bestfriendInventory.PrintAllItems();
    cout << "\n";
    cout << "인벤토리 깊은 복사(Assign 메서드)\n";
    bestfriendInventory.Assign(myInventory);
    bestfriendInventory.PrintAllItems();
    cout << "\n";
    cout << "용량이 1인 인벤토리 생성\n";
    Inventory<Item> littleInventory(0);
    littleInventory.PrintAllItems();
    cout << "\n";
    cout << "아이템 2개 추가\n";
    littleInventory.AddItem(i1);
    littleInventory.AddItem(i2);
    littleInventory.PrintAllItems();
    cout << "\n";
    cout << "아이템 3개 추가\n";
    littleInventory.AddItem(i1);
    littleInventory.AddItem(i3);
    littleInventory.AddItem(i2);
    littleInventory.PrintAllItems();
    cout << "\n";
    cout << "아이템 정렬\n";
    littleInventory.SortItems();
    littleInventory.PrintAllItems();

    return 0;
}