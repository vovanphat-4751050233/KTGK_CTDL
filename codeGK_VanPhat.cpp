#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Word {
    string english;
    string vietnamese;
};

struct Node {
    Word data;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
};

void init(List &l) {
    l.head = l.tail = NULL;
}Node* createNode(string eng, string vie) {
    Node* newNode = new Node;
    newNode->data.english = eng;
    newNode->data.vietnamese = vie;
    newNode->next = NULL;
    return newNode;
}

void addLast(List &l, string eng, string vie) {
    Node* newNode = createNode(eng, vie);
    if (l.head == NULL) {
        l.head = l.tail = newNode;
    } else {
        l.tail->next = newNode;
        l.tail = newNode;
    }
}// Câu 3: In toàn bộ
void printList(List l) {
    Node* p = l.head;
    while (p != NULL) {
        cout << p->data.english << ": " << p->data.vietnamese << endl;
        p = p->next;
    }
}

// Câu 5: In từ đầu đến "hello"
void printUntilHello(List l) {
    Node* p = l.head;
    bool found = false;
    while (p != NULL) {
        cout << p->data.english << ": " << p->data.vietnamese << endl;
        if (p->data.english == "hello") {
            found = true;
            break;
        }
        p = p->next;
    }
    if (!found) cout << "(Khong tim thay tu 'hello' trong danh sach)" << endl;
}
int findWord(List l, string x) {
    Node* p = l.head;
    while (p != NULL) {
        if (p->data.english == x) return 1; // Trả về 1 nếu thấy
        p = p->next;
    }
    return 0; // Trả về 0 nếu không thấy
}
void deleteStartWithC(List &l) {
    Node* curr = l.head;
    Node* prev = NULL;

    while (curr != NULL) {
        // Kiểm tra chữ cái đầu tiên (chuyển về chữ thường để so sánh)
        if (!curr->data.english.empty() && tolower(curr->data.english[0]) == 'c') {
            Node* temp = curr;
            if (prev == NULL) { // Xóa đầu
                l.head = curr->next;
                curr = l.head;
            } else {
                prev->next = curr->next;
                curr = prev->next;
            }
            if (temp == l.tail) l.tail = prev;
            delete temp;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}
void sortDictionary(List &l) {
    for (Node* p = l.head; p != NULL && p->next != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if (p->data.english > q->data.english) {
                swap(p->data, q->data);
            }
        }
    }
}
int main() {
    List dict;
    init(dict);

    // 8a. Tạo danh sách 10 từ
    addLast(dict, "apple", "qua tao");
    addLast(dict, "cat", "con meo");
    addLast(dict, "banana", "qua chuoi");
    addLast(dict, "hello", "xin chao");
    addLast(dict, "car", "xe hoi");
    addLast(dict, "dog", "con cho");
    addLast(dict, "computer", "may tinh");
    addLast(dict, "egg", "qua trung");
    addLast(dict, "candy", "keo");
    addLast(dict, "fan", "cai quat");

    // 8b. In từ điển
    cout << "--- Tu dien ban dau: ---" << endl;
    printList(dict);

    // 8c. Tìm 1 từ bất kỳ
    string x;
    cout << "\nNhap tu tieng Anh can tim: ";
    cin >> x;
    if (findWord(dict, x)) 
        cout << "=> Tim thay tu '" << x << "' trong tu dien." << endl;
    else 
        cout << "=> Khong tim thay." << endl;

    // 8d. Hiển thị đến từ "hello"
    cout << "\n--- Tu dau den 'hello': ---" << endl;
    printUntilHello(dict);

    // 8e. Xóa các từ bắt đầu bằng 'c'
    deleteStartWithC(dict);
    cout << "\n--- Sau khi xoa cac tu bat dau bang 'c': ---" << endl;
    printList(dict);

    // 8f. Sắp xếp và in lại
    sortDictionary(dict);
    cout << "\n--- Tu dien sau khi sap xep tang dan: ---" << endl;
    printList(dict);

    return 0;
}
//da test