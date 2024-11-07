#include<iostream>
#include<list>
#include<string>
#include<algorithm>
//Quản lí điểm
class Quan_li{
    private:
        int MSV;
        double point;
        std::string name;
        int date, month ,year;
    public:
         Quan_li(int MSV = 0, double point = 0.0, std::string name = "", int date = 0, int month = 0, int year= 0): MSV(MSV), point(point), name(name), date(date), month(month), year(year){}
         
         friend std::istream& operator>>(std::istream &is, Quan_li &ql){
            std::cout << "-Nhap ma sinh vien: ";
            is >> ql.MSV;
            std::cout << "-Ho va ten:";
            is.ignore();
            is >> ql.name;
            std::cout << "-Nhap ngay thang nam sinh date/month/year: ";
            std::cout << "  *Ngay:"; is >> ql.date;
            std::cout << "  *Thang:"; is >> ql.month;
            std::cout << "  *Nam: ";is >> ql.year;
            std::cout << "-Diem: ";
            is >> ql.point;
            return is;
         }
         friend std::ostream& operator<<(std::ostream &os, const Quan_li &ql){
            os << "MSV: " << ql.MSV << " " << ql.name << " " << ql.date << "/" << ql.month << "/" << ql.year;
            os << ql.point;
            return os;
            }
        
        Quan_li displaY() const{
            std::cout << "MSV:" << MSV << "-" << "Ten:" <<  name << "-" << "Ngay sinh:" << date << "/" << month << "/" << year << "-" << "Diem:" << point << std::endl;
            return *this;
          }

        double getPoint() const {
             return point;
             }
        int getMSV() const {
            return MSV;
            }

        bool operator<(const Quan_li &other) const {
            return point < other.point; 
            }
};

class Danh_sach{
    private:
        std::list<Quan_li> ds;
    public:
        void addSV(Quan_li &ql){
            ds.push_back(ql);
        }
        void outAll() const {
        for (const auto &ql : ds) {
            ql.displaY();
        }
        }
        void sx(){
            ds.sort();
        }

        Quan_li look_max() const{
            if (ds.empty()) return Quan_li();
            return *std::max_element(ds.begin(), ds.end());
        }
        Quan_li look_min() const{
            if (ds.empty()) return Quan_li();
            return *std::min_element(ds.begin(), ds.end());
        } 
        void xoaSV(int ma) {
        ds.remove_if([ma](const Quan_li &ql) { return ql.getMSV() == ma; });
    }
};



class App {
private:
    Danh_sach danhSach;

public:
    void menu() {
        int choice;
        do {
            std::cout << "\n\nQUAN LY DANH SACH SINH VIEN\n";
            std::cout << "1. Them sinh vien\n";
            std::cout << "2. Xuat danh sach\n";
            std::cout << "3. Sap xep danh sach theo diem\n";
            std::cout << "4. Tim sinh vien diem cao nhat\n";
            std::cout << "5. Tim sinh vien diem thap nhat\n";
            std::cout << "6. Xoa sinh vien theo ma\n";
            std::cout << "0. Thoat\n";
            std::cout << "Nhap lua chon: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    themSinhVien();
                    break;
                case 2:
                    xuatDanhSach();
                    break;
                case 3:
                    sapXepDanhSach();
                    break;
                case 4:
                    timSinhVienDiemCaoNhat();
                    break;
                case 5:
                    timSinhVienDiemThapNhat();
                    break;
                case 6:
                    xoaSinhVienTheoMa();
                    break;
                case 0:
                    std::cout << "Thoat chuong trinh.\n";
                    break;
                default:
                    std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
            }
        } while (choice != 0);
    }

   void themSinhVien() {
    int ma, ngay, thang ,nam;
    float diem;
    std::string ten;

    std::cout << "Nhap ma: ";
    std::cin >> ma;
    std::cout << "Nhap ten: ";
    std::cin.ignore();
    std::getline(std::cin, ten);
    std::cout << "Nhap ngay sinh: \n";
    std::cout << "Ngay: ";
    std::cin >> ngay;
    std::cout << "Thang: ";
    std::cin >> thang;
    std::cout << "Nam: ";
    std::cin >> nam;
    std::cout << "Nhap diem: ";
    std::cin >> diem;

    // Khởi tạo đối tượng Quan_li với giá trị mặc định cho ngày/tháng/năm
     Quan_li sv(ma, diem, ten, ngay, thang, nam);
    danhSach.addSV(sv);
    std::cout << "Da them sinh vien thanh cong!\n";
}

    void xuatDanhSach() const {
        std::cout << "Danh sach sinh vien:\n";
        danhSach.outAll();
    }

    void sapXepDanhSach() {
        danhSach.sx();
        std::cout << "Danh sach da sap xep theo diem!\n";
    }

    void timSinhVienDiemCaoNhat() const {
        std::cout << "Sinh vien co diem cao nhat: " << danhSach.look_max() << std::endl;
    }

    void timSinhVienDiemThapNhat() const {
        std::cout << "Sinh vien co diem thap nhat: " << danhSach.look_min() << std::endl;
    }

    void xoaSinhVienTheoMa() {
        int ma;
        std::cout << "Nhap ma sinh vien can xoa: ";
        std::cin >> ma;
        danhSach.xoaSV(ma);
        std::cout << "Da xoa sinh vien co ma " << ma << "!\n";
    }
};
int main(){
    App app;
    app.menu();
    return 0;
}


