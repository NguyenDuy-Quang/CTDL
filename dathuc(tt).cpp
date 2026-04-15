#include <iostream>
#include <cmath>
using namespace std;

struct DaThucMang {
    float heso[100];
    int bac;
    void khoiTao() {
        for(int i = 0; i < 100; i++) heso[i] = 0;
        bac = 0;
    }
    void nhap() {
        cout << "Nhap bac cua da thuc: ";
        cin >> bac;
        for (int i = bac; i >= 0; i--) {
            cout << "He so cua x^" << i << ": ";
            cin >> heso[i];
        }
    }
    void xuat() {
        for (int i = bac; i >= 0; i--) {
            if (heso[i] != 0) {
                cout << heso[i] << "x^" << i;
                if (i > 0 && heso[i-1] >= 0) cout << " + ";
            }
        }
        cout << endl;
    }
};
DaThucMang congMang(DaThucMang dt1, DaThucMang dt2) {
    DaThucMang tong;
    tong.khoiTao();
    
    // Bậc của đa thức tổng sẽ là bậc lớn nhất giữa dt1 và dt2
    tong.bac = (dt1.bac > dt2.bac) ? dt1.bac : dt2.bac;
    
    for (int i = 0; i <= tong.bac; i++) {
        tong.heso[i] = dt1.heso[i] + dt2.heso[i];
    }
    return tong;
}
int main() {
    DaThucMang dt1;
    dt1.khoiTao();
    dt1.nhap();
    dt1.xuat();
    DaThucMang dt2;
    dt2.khoiTao();
    dt2.nhap();
    dt2.xuat();
    cout << "Tong hai da thuc: ";
    congMang(dt1, dt2).xuat();
    return 0;
}