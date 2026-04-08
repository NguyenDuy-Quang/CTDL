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
struct SLL {
    Node *pHead, *pTail;
};

void initSLL(SLL* list) {
    list->pHead = list->pTail = NULL;
}
void addTail_C2(SLL* list, SinhVien sv) {
    Node* newNode = new Node{sv, NULL};
    if (list->pHead == NULL) {
        list->pHead = list->pTail = newNode;
    } else {
        list->pTail->pNext = newNode;
        list->pTail = newNode;       
    }
}
void printList(Node* pHead) {
    Node* p = pHead;
    while (p != NULL) {
        cout << p->data.hoTen << " | " << p->data.gpa << endl;
        p = p->pNext;
    }
}