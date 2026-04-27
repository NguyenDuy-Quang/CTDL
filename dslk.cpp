#include <iostream>
#include <string.h>

using namespace std;

// 1. Khai báo cấu trúc dữ liệu
struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh; // 0: Nam, 1: Nu
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

// Khởi tạo danh sách rỗng
void Init(List &l) {
    l.first = l.last = NULL;
}

// Tạo node mới
Node* CreateNode(SinhVien x) {
    Node *p = new Node;
    if (p == NULL) return NULL;
    p->data = x;
    p->link = NULL;
    return p;
}

// So sánh ngày sinh
bool TrungNgaySinh(Ngay n1, Ngay n2) {
    return (n1.ngay == n2.ngay && n1.thang == n2.thang && n1.nam == n2.nam);
}

// 2. Thêm sinh viên vào danh sách đã sắp xếp theo mã SV (Ascending)
void InsertOrder(List &l, SinhVien x) {
    Node *p = CreateNode(x);
    if (l.first == NULL) {
        l.first = l.last = p;
        return;
    }

    // Thêm vào đầu nếu mã SV nhỏ hơn node đầu
    if (strcmp(p->data.maSV, l.first->data.maSV) < 0) {
        p->link = l.first;
        l.first = p;
        return;
    }

    // Tìm vị trí chèn
    Node *prev = l.first;
    Node *curr = l.first->link;
    while (curr != NULL && strcmp(curr->data.maSV, p->data.maSV) < 0) {
        prev = curr;
        curr = curr->link;
    }
    
    p->link = curr;
    prev->link = p;
    if (curr == NULL) l.last = p;
}

// 3. In các sinh viên có cùng ngày sinh
void InSinhVienTrungNgaySinh(List l) {
    bool found = false;
    for (Node *p = l.first; p != NULL; p = p->link) {
        bool hasMatch = false;
        for (Node *q = l.first; q != NULL; q = q->link) {
            if (p != q && TrungNgaySinh(p->data.ngaySinh, q->data.ngaySinh)) {
                hasMatch = true;
                break;
            }
        }
        if (hasMatch) {
            cout << "MSSV: " << p->data.maSV << " - Ho Ten: " << p->data.hoTen 
                 << " - Ngay sinh: " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << endl;
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
}

// 4. Loại bỏ các sinh viên có cùng ngày sinh
void XoaSinhVienTrungNgaySinh(List &l) {
    if (l.first == NULL) return;

    // Đánh dấu các node cần xóa
    Node *p = l.first;
    while (p != NULL) {
        bool checkMatch = false;
        Node *q = l.first;
        while (q != NULL) {
            if (p != q && TrungNgaySinh(p->data.ngaySinh, q->data.ngaySinh)) {
                checkMatch = true;
                break;
            }
            q = q->link;
        }

        if (checkMatch) {
            // Xử lý xóa node p
            Node *temp = p;
            if (p == l.first) {
                l.first = l.first->link;
                p = l.first;
            } else {
                Node *prev = l.first;
                while (prev->link != p) prev = prev->link;
                prev->link = p->link;
                if (p == l.last) l.last = prev;
                p = p->link;
            }
            delete temp;
        } else {
            p = p->link;
        }
    }
}

void InDanhSach(List l) {
    Node *p = l.first;
    while (p != NULL) {
        cout << "[" << p->data.maSV << "] " << p->data.hoTen << endl;
        p = p->link;
    }
}

// Test Case mẫu
int main() {
    List listSV;
    Init(listSV);

    // Dữ liệu giả lập để test
    SinhVien sv1 = {"202201", "Nguyen Van A", 0, {10, 5, 2004}, "HN", "IT1", "SET"};
    SinhVien sv2 = {"202203", "Tran Thi B", 1, {10, 5, 2004}, "HP", "IT2", "SET"}; // Trùng ngày sv1
    SinhVien sv3 = {"202202", "Le Van C", 0, {15, 8, 2004}, "DN", "IT1", "SET"};

    InsertOrder(listSV, sv1);
    InsertOrder(listSV, sv2);
    InsertOrder(listSV, sv3);

    cout << "--- Danh sach sau khi nhap (da sap xep ma SV) ---" << endl;
    InDanhSach(listSV);

    cout << "\n--- Sinh vien co cung ngay sinh ---" << endl;
    InSinhVienTrungNgaySinh(listSV);

    cout << "\n--- Danh sach sau khi loai bo sinh vien trung ngay sinh ---" << endl;
    XoaSinhVienTrungNgaySinh(listSV);
    InDanhSach(listSV);

    return 0;
}