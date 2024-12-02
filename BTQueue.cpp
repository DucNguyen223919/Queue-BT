#include <iostream>
#include <string>
using namespace std;

// Cau truc san pham
struct Product {
    string name;
    int quantity;
    double price;
    Product* next;
};

// cau truc node cua hang doi
struct Node {
    Product* cart; // Danh sach san pham trong gio hang
    Node* next;    // Con tro den node tiep theo
};

// Cau truc hang doi
struct Queue {
    Node* front; // Con tro dau hang doi
    Node* rear;  // Con tro cuoi hang doi

    Queue() : front(nullptr), rear(nullptr) {}

    // Thêm gio hang vao hang doi
    void enqueue(Product* cart) {
        Node* newNode = new Node{cart, nullptr};
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
    }

    // Xoa gio hang khoi hang doi
    Product* dequeue() {
        if (!front) return nullptr;
        Node* temp = front;
        Product* cart = front->cart;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return cart;
    }

    // Kiem tra hang doi rong
    bool isEmpty() {
        return front == nullptr;
    }
};

// Tinh tong tien gio hang
double cartTotal(Product* cart) {
    double total = 0;
    while (cart) {
        total += cart->quantity * cart->price;
        cart = cart->next;
    }
    return total;
}

// Dem so luong san pham A trong gio hang
int countProductA(Product* cart, const string& productName) {
    int count = 0;
    while (cart) {
        if (cart->name == productName) {
            count += cart->quantity;
        }
        cart = cart->next;
    }
    return count;
}

int main() {
    Queue checkoutQueue;
    double totalRevenue = 0; // Tong so tien thu duoc
    int productACount = 0;   // So luong san pham A da ban
    string productA = "A";   // Ten san pham A

    // Them du lieu vao hang doi
    for (int i = 1; i <= 3; i++) {
        Product* cart = nullptr;
        Product* last = nullptr;

        for (int j = 1; j <= 2; j++) {
            Product* product = new Product{"A", j, 10.0 * j, nullptr};
            if (!cart) {
                cart = product;
            } else {
                last->next = product;
            }
            last = product;
        }
        checkoutQueue.enqueue(cart);
    }

    // Xu li tung khach hang trong hang doi
    while (!checkoutQueue.isEmpty()) {
        Product* cart = checkoutQueue.dequeue();
        totalRevenue += cartTotal(cart);
        productACount += countProductA(cart, productA);

        // Giai phong bo nho
        while (cart) {
            Product* temp = cart;
            cart = cart->next;
            delete temp;
        }
    }

    cout << "Tong so tien thu duoc: " << totalRevenue << endl;
    cout << "So luong san pham " << productA << " : " << productACount << endl;

    return 0;
}
