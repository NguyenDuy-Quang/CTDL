#include <iostream>
using namespace std;

struct Node {
    float heSo;
    int soMu;
    Node* next;
};

struct DaThucLienKet {
    Node* head = nullptr;
    Node* taoNode(float hs, int sm) {
        Node* newNode = new Node;
        newNode->heSo = hs;
        newNode->soMu = sm;
        newNode->next = nullptr;
        return newNode;
    }
    void themSoHang(float hs, int sm) {
        if (hs == 0) return;
        Node* newNode = taoNode(hs, sm);
        if (!head || head->soMu < sm) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next && temp->next->soMu > sm) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    void nhap() {
        int n;
        float hs;
        int sm;
        cout << "Nhap so luong so hang: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Nhap he so va so mu: ";
            cin >> hs >> sm;
            themSoHang(hs, sm);
        }
    }
    void xuat() {
        Node* temp = head;
        while (temp) {
            cout << temp->heSo << "x^" << temp->soMu;
            if (temp->next) cout << " + ";
            temp = temp->next;
        }
        cout << endl;
    }
};
DaThucLienKet congLienKet(DaThucLienKet dt1, DaThucLienKet dt2) {
    DaThucLienKet tong;
    Node* p1 = dt1.head;
    Node* p2 = dt2.head;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->soMu == p2->soMu) {
            float hsTong = p1->heSo + p2->heSo;
            if (hsTong != 0) tong.themSoHang(hsTong, p1->soMu);
            p1 = p1->next;
            p2 = p2->next;
        } 
        else if (p1->soMu > p2->soMu) {
            tong.themSoHang(p1->heSo, p1->soMu);
            p1 = p1->next;
        } 
        else {
            tong.themSoHang(p2->heSo, p2->soMu);
            p2 = p2->next;
        }
    }
    while (p1 != nullptr) {
        tong.themSoHang(p1->heSo, p1->soMu);
        p1 = p1->next;
    }
    while (p2 != nullptr) {
        tong.themSoHang(p2->heSo, p2->soMu);
        p2 = p2->next;
    }
    return tong;
}
int main() {
    DaThucLienKet dt1, dt2;
    
    cout << "Nhap da thuc 1:\n";
    dt1.nhap();
    cout << "Nhap da thuc 2:\n";
    dt2.nhap();
    DaThucLienKet ketQua = congLienKet(dt1, dt2);
    cout << "Da thuc 1: "; dt1.xuat();
    cout << "Da thuc 2: "; dt2.xuat();
    cout << "Ket qua tong: "; ketQua.xuat();
    return 0;
}