#include <iostream>
#include <string>
using namespace std;

struct SinhVien {
    string hoTen;
    string ngaySinh;
    string lop;
    float gpa;
};
struct Node {
    SinhVien data;
    Node* pNext;
};
struct List {
    Node* pHead;
};
void List_Init(List* list) {
    list->pHead = NULL;
}
void addTail_C1(List* list, SinhVien sv) {
    Node* newNode = new Node{sv, NULL};
    if (list->pHead == NULL) {
        list->pHead = newNode;
    } else {
        Node* p = list->pHead;
        while (p->pNext != NULL) { 
            p = p->pNext;
        }
        p->pNext = newNode;
    }
}
void printList(Node* pHead) {
    Node* p = pHead;
    while (p != NULL) {
        cout << p->data.hoTen << " | " << p->data.gpa << endl;
        p = p->pNext;
    }
}