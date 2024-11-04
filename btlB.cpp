#include<iostream>
#include<memory>
#include<cmath>

class Node{
    public:
    int he_so;
    int b_ac;
    std::shared_ptr<Node> next;

    Node(int heso, int bac): he_so(heso), b_ac(bac), next(nullptr) {}
};

class Da_thuc{
    private:
    std::shared_ptr<Node> head;

    public:
    Da_thuc(): head(nullptr){}

    void input(int heso, int bac) {
        if (heso == 0) return;

        auto newNode = std::make_shared<Node>(heso, bac);

        if (!head || head->b_ac < bac) {
            newNode->next = head;
            head = newNode;
            return;
        }

   
        auto current = head;
        while (current->next && current->next->b_ac > bac) {
            current = current->next;
        }

     
        if (current->b_ac == bac) {
            current->he_so += heso;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    } 
    //Phương thức nhập, xuất  hệ số, bậc
    friend std::istream& operator>>(std::istream& in, Da_thuc& dt){
    while (true) {
        int heso, bac;
        std::cout << "Nhap he so (0 de dung): ";
        in >> heso;
        if (heso == 0) break;
        std::cout << "Nhap bac: ";
        in >> bac;
        dt.input(heso, bac);
        char choice;
        std::cout << "Nhap tiep (1) hoac dung (0): ";
        in >> choice;
        if (choice == '0') break;
    }
    return in;
    }

    
    friend std::ostream& operator<<(std::ostream& os, Da_thuc& dt){
       auto temp = dt.head;
       if(!temp){
        os << "0";
        return os;
       }
        while(temp){
            if (temp != dt.head) {
                os << (temp->he_so > 0 ? "+" : "");
            }
            os << temp->he_so << "x^" << temp->b_ac;
               temp = temp -> next;
        }
        return os;
    }

    //Tính biểu thức tại một điểm
    double evulation(int x){
        double result = 0;
        auto current = head;
        while(current) {
            result += current -> he_so* std::pow(x, current -> b_ac);
            current = current -> next;
        }
        return result;
    }
    //+ đa thức
    Da_thuc operator+(Da_thuc& other){
        Da_thuc result;
        auto t1 = head;
        auto t2 = other.head;
        while(t1 || t2){
            if(t1 && (!t2 || t1 -> b_ac > t2->b_ac)){
                result.input(t1 ->he_so, t1 ->b_ac);
                t1 = t1 ->next;
            }else if(t2 && (!t1 || t2 ->b_ac > t1 ->b_ac)){
                result.input(t2 ->he_so, t2 ->b_ac);
                t2 = t2 ->next;
            }else{
                result.input(t1 ->he_so + t2->b_ac, t1 ->b_ac);
                t1 = t1 ->next;
                t2 = t2 ->next;
            }
        }
        return result;
    }
    //-  Đa thức
     Da_thuc operator-(Da_thuc& other){
        Da_thuc result;
        auto t1 = head;
        auto t2 = other.head;
        while(t1 || t2){
            if(t1 && (!t2 || t1 -> b_ac > t2->b_ac)){
                result.input(t1 ->he_so, t1 ->b_ac);
                t1 = t1 ->next;
            }else if(t2 && (!t1 || t2 ->b_ac > t1 ->b_ac)){
                result.input(t2 ->he_so, t2 ->b_ac);
                t2 = t2 ->next;
            }else{
                result.input(t1 ->he_so - t2->b_ac, t1 ->b_ac);
                t1 = t1 ->next;
                t2 = t2 ->next;
            }
        }
        return result;
    }
    //* Đa thức
     Da_thuc operator*(Da_thuc& other){
        Da_thuc result;
        for(auto t1 = head; t1; t1 = t1 ->next){
            for(auto t2 = other.head; t2; t2= t2 ->next){
                result.input(t1 ->he_so* t2 ->he_so, t1 ->b_ac + t2 ->b_ac);
            }
        }
        return result;
     }
     // / Đa thức

};
int main()
{
    Da_thuc dt1,dt2;
    std::cout << "Nhap da thuc 1: " << std::endl;
    std::cin >> dt1;
    std::cout << "Nhap da thuc 2: " << std::endl;
    std::cin >> dt2;

    Da_thuc tong = dt1 + dt2;
    Da_thuc hieu = dt1 - dt2;
    Da_thuc tich = dt1 * dt2;

    std::cout << "Tong hai da thuc la: " << tong << std::endl;
    std::cout << "Hieu hai da thuc la: " << hieu << std::endl;
    std::cout << "Tich hai da thuc la: " << tich << std::endl;

    int x;
    std::cout << "Nhap x cua da thuc 1: ";
    std::cin >> x;
    std:: cout << "Gia tri cua da thuc 1 tai " << x <<" la: " <<dt1.evulation(x) << std::endl;
    std::cout << "Nhap x cua da thuc 2: ";
    std::cin >> x;
    std:: cout << "Gia tri cua da thuc 2 tai " << x <<" la: " <<dt2.evulation(x) << std::endl;

    std::cout << "Tong hai da thuc la: " << tong.evulation(x) << std::endl;
    std::cout << "Hieu hai da thuc la: " << hieu.evulation(x) << std::endl;
    std::cout << "Tich hai da thuc la: " << tich.evulation(x) << std::endl;
}