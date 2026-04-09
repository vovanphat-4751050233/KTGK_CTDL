#include <iostream>
#include <string>
#include <iomanip> // Thư viện để căn lề bảng cho đẹp

using namespace std;

// --- 1. KHAI BÁO CẤU TRÚC DỮ LIỆU ---
struct SinhVien {
    int mssv;
    string hoTen;
    float diemTB;
};

struct Node {
    SinhVien data;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
};

// Khởi tạo danh sách rỗng
void init(List &l) {
    l.head = l.tail = NULL;
}

// --- 2. CÁC HÀM THÊM (CREATE & ADD) ---
Node* createNode(int ma, string ten, float diem) {
    Node* newNode = new Node;
    newNode->data.mssv = ma;
    newNode->data.hoTen = ten;
    newNode->data.diemTB = diem;
    newNode->next = NULL;
    return newNode;
}

// Thêm vào cuối danh sách
void addLast(List &l, int ma, string ten, float diem) {
    Node* newNode = createNode(ma, ten, diem);
    if (l.head == NULL) {
        l.head = l.tail = newNode;
    } else {
        l.tail->next = newNode;
        l.tail = newNode;
    }
}

// --- 3. HÀM HIỂN THỊ (READ) ---
void printList(List l) {
    if (l.head == NULL) {
        cout << "Danh sach rong!" << endl;
        return;
    }
    cout << setw(10) << left << "MSSV" << " | " 
         << setw(20) << left << "HO TEN" << " | " 
         << setw(7) << left << "DIEM TB" << endl;
    cout << string(45, '-') << endl;
    
    Node* p = l.head;
    while (p != NULL) {
        cout << setw(10) << left << p->data.mssv << " | " 
             << setw(20) << left << p->data.hoTen << " | " 
             << setw(7) << left << p->data.diemTB << endl;
        p = p->next;
    }
}

// --- 4. HÀM SỬA (UPDATE) ---
void updateStudent(List &l, int ma) {
    Node* p = l.head;
    while (p != NULL) {
        if (p->data.mssv == ma) {
            cout << "==> Tim thay SV: " << p->data.hoTen << endl;
            cout << "Nhap diem trung binh moi: ";
            cin >> p->data.diemTB;
            cout << "Cap nhat thanh cong!" << endl;
            return;
        }
        p = p->next;
    }
    cout << "==> Khong tim thay MSSV: " << ma << endl;
}

// --- 5. HÀM XÓA (DELETE) ---
// Xóa sinh viên có điểm TB < 5
void deleteWeakStudents(List &l) {
    Node* curr = l.head;
    Node* prev = NULL;
    bool found = false;

    while (curr != NULL) {
        if (curr->data.diemTB < 5.0) {
            Node* temp = curr;
            if (prev == NULL) { // Truong hop xoa dau danh sach
                l.head = curr->next;
                curr = l.head;
                if (l.head == NULL) l.tail = NULL; // Neu xoa xong danh sach rong
            } else { // Truong hop xoa giua hoac cuoi
                prev->next = curr->next;
                if (curr == l.tail) l.tail = prev; // Neu xoa nut cuoi, cap nhat tail
                curr = prev->next;
            }
            delete temp;
            found = true;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    if (found) cout << "Da xoa cac sinh vien co diem < 5." << endl;
    else cout << "Khong co sinh vien nao diem < 5." << endl;
}

// --- 6. HÀM GIẢI PHÓNG BỘ NHỚ ---
void clearList(List &l) {
    Node* p = l.head;
    while (p != NULL) {
        Node* temp = p;
        p = p->next;
        delete temp;
    }
    l.head = l.tail = NULL;
}

// --- 7. CHƯƠNG TRÌNH CHÍNH ---
int main() {
    List ds;
    init(ds);

    // Thêm 5 sinh viên mẫu
    addLast(ds, 101, "Nguyen Van An", 8.5);
    addLast(ds, 102, "Tran Thi Binh", 4.5); // SV Yeu
    addLast(ds, 103, "Le Cong Vinh", 9.2);
    addLast(ds, 104, "Pham Minh Cuong", 3.8); // SV Yeu
    addLast(ds, 105, "Hoang Lan Anh", 7.0);

    int choice;
    do {
        cout << "\n========= MENU QUAN LY SINH VIEN =========" << endl;
        cout << "1. In danh sach sinh vien" << endl;
        cout << "2. Them sinh vien moi vao cuoi" << endl;
        cout << "3. Sua diem sinh vien theo MSSV" << endl;
        cout << "4. Xoa sinh vien co diem trung binh < 5" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban: "; cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- DANH SACH SINH VIEN ---" << endl;
                printList(ds);
                break;
            case 2: {
                int ma; string ten; float diem;
                cout << "Nhap MSSV: "; cin >> ma;
                cin.ignore(); // Xoa bo nho dem de dung getline
                cout << "Nhap Ho Ten: "; getline(cin, ten);
                cout << "Nhap Diem TB: "; cin >> diem;
                addLast(ds, ma, ten, diem);
                break;
            }
            case 3: {
                int ma;
                cout << "Nhap MSSV can sua: "; cin >> ma;
                updateStudent(ds, ma);
                break;
            }
            case 4:
                deleteWeakStudents(ds);
                break;
            case 0:
                clearList(ds);
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);

    return 0;
}