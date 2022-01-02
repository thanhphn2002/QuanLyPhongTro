#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
#define MAX 100 // Có tối đa 100 phòng

//	Đề tài số 9: Quản lý phòng trọ
//	1. Mỗi nhà trọ các thông tin : mã phòng trọ, họ tên người thuê trọ, số CMND người thuê			Thanh
//	trọ, ngày tháng năm sinh người thuê trọ, chỉ số điện, chỉ số nước, đơn giá phòng trọ			
//	2. Tạo Queue chứa thông tin Nhà trọ bằng 2 cách : nhập từ bàn phím và đọc / ghi từ file txt.	Thanh
//	3. Hiển thị tất cả các thông tin của nhà trọ trong Queue.										Thanh	
//  PS:	Phần nhập liệu của em mới xong 50% thôi, em còn kiểm tra ngày sinh hợp lệ, số CMND không được trùng vs fomat họ tên nữa 
//	4. Xóa 1 phòng trọ trong Queue.																	Nhi
//	5. Thêm 1 phòng trọ vào Queue.																	Nhi
//	6. Tìm phòng trọ có chỉ số điện cao nhất.														Nhi
//	7. Tìm phòng trọ của người thuê trọ có họ tên “ Tran Van A”.									Thiên
//	8. Đếm số phòng trọ có đơn giá phòng trọ cao nhất.												Thiên
//	9. Đếm số phòng trọ có người thuê trọ có năm sinh < 2002.										Thiên
//	10. Tính tổng chỉ số điện của tất cả các phòng trọ trong nhà trọ.								My
//	11. Mỗi nhà trọ là một đỉnh trong đồ thị, khoảng cách là trọng số cạnh nối.Tìm đường đi			My
//	từ nhà trọ này sang nhà trọ khác bằng phương pháp duyệt theo chiều rộng.

struct BirthDay	
{
	int day, month, year;
};

// Thông tin phòng trọ
struct PhongTro
{
	string idRoom, name, idCard;	// Mã phòng chứa, Tên người thuê, Số CMND.
	BirthDay DOB;	// Ngày tháng năm sinh của người thuê trọ
	double water, electric, price;	// Chỉ số điện, nước, đơn giá phòng
};

void init(int& bottom, int& top);
void inputList(PhongTro list[], int n);
void outputList(PhongTro list[], int n);
void inputFile(PhongTro list[], int& n);
bool push();
bool pop();

void main()
{
	PhongTro a[MAX];
	int top, bottom, key, n;	// Key là user chọn
	bool inp = false; // Kiểm tra nhập dữ liệu chưa

	do
	{
		system("cls");
		cout <<"1/ Nhap du lieu tu ban phim \n"
			<< "2/ Nhap du lieu tu File \n"
			<< "3/ Hien thi thong tin tat ca phong tro \n"
			<< "4/ Them 1 phong tro \n"
			<< "5/ Xoa  1 phong tro \n"
			<< "6/ Phong tro co chi so dien cao nhat \n"
			<< "7/ Tim nguoi trong phong tro \n"
			<< "8/ Dem so phong tro co don gia phong cao nhat \n"
			<< "9/ Dem so phong tro co nguoi thue co nam sinh < 2002 \n"
			<< "10/ Tinh tong chi so dien \n"
			<< "11/ BFS \n"
			<< "12/ Thoat \n"
			<< "==> Lua chon cua ban: ";
		cin >> key;

		system("cls");
		switch (key)
		{
		case 1:
			cout << "Nhap so luong phong tro: ";
			do
			{
				cin >> n;
				if (n <= 0 || n > 100)
					cout << "Nhap sai! Nhap lai (0 < n <= 100): ";
			} while (n <= 0 || n > 100);
			init(top, bottom);
			inputList(a, n);

			inp = true;
			cout << "Nhap du lieu thanh cong! \n";
			break;
		case 2:
			inputFile(a, n);
			inp = true;
			break;
		case 3:
			if (inp)
				outputList(a, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		default: exit(0);
		}
		_getch();
	} while (key > 0 & key < 12);
}

void init(int& bottom, int& top)
{
	top = bottom = -1;	// Đỉnh và đáy của Queue
}

void input1Phong(PhongTro& room)
{
	cin.ignore();
	cout << "+ Nhap ma phong tro: ";
	getline(cin, room.idRoom);
	room.idRoom = room.idRoom.substr(0, 5);	// Mã phòng tối đa 5 ký tự
	cout << "+ Nhap ho ten nguoi thue tro: ";
	getline(cin, room.name);
	room.name = room.name.substr(0, 50);	// Họ tên tối đa 50 ký tự
	cout << "+ Nhap so CMND: ";
	getline(cin, room.idCard);
	room.idCard = room.idCard.substr(0, 12);	// Số CMND tối đa 12 ký tự
	cout << "+ Nhap ngay sinh: ";
	cin >> room.DOB.day >> room.DOB.month >> room.DOB.year;
	cout << "+ Nhap chi so dien: ";
	cin >> room.electric;
	cout << "+ Nhap chi so nuoc: ";
	cin >> room.water;
	cout << "+ Nhap don gia phong: ";
	cin >> room.price;
}

void inputList(PhongTro list[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap thong tin phong tro thu " << i + 1 << endl;
		input1Phong(list[i]);
		cout << "========================================================== \n";
	}
}

void output1Phong(PhongTro room)
{
	cout << "+ Ma phong tro: ";
	cout << room.idRoom << endl;
	cout << "+ Ho ten nguoi thue tro: ";
	cout << room.name << endl;
	cout << "+ So CMND: ";
	cout << room.idCard << endl;
	cout << "+ Ngay sinh: ";
	cout << room.DOB.day << "/" << room.DOB.month << "/" << room.DOB.year << endl;
	cout << "+ Chi so dien: ";
	cout << room.electric << endl;
	cout << "+ Chi so nuoc: ";
	cout << room.water << endl;
	cout << "+ Don gia phong: ";
	cout << room.price << endl;
}

void outputList(PhongTro list[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Thong tin phong tro thu " << i + 1 << endl;
		output1Phong(list[i]);
		cout << "========================================================== \n";
	}
}

void inputFile(PhongTro list[], int& n)
{
	ifstream fi;	// fi = File input
	string temp;
	fi.open("data.txt");
	if (fi.is_open())
	{
		fi >> n;
		for (int i = 0; i < n; i++)
		{
			int count = 0;
			while (getline(fi, temp, ',') || !fi.eof())
			{
				switch (count)
				{
				case 0: 
					list[i].idRoom = temp.erase(0, 1);
					break;
				case 1:
					list[i].name = temp;
					break;
				case 2:
					list[i].idCard = temp;
					break;
				case 3:
					{
						int space = temp.find('/');
						list[i].DOB.day = stoi(temp.substr(0, space));
						list[i].DOB.month = stoi(temp.substr(space + 1, temp.size() - 4 - space));
						list[i].DOB.year = stoi(temp.substr(temp.size() - 4, 4));
					}
					break;
				case 4:
					list[i].electric = stod(temp);
					break;
				case 5:
					list[i].water = stod(temp);
					break;
				case 6:
					list[i].price = stod(temp);
					break;
				}
				if (count == 6) break;
				count++;
			}
		}
			
		cout << "Nhap File thanh cong! \n";
		fi.close();
	}
	else
		cout << "Khong the mo File! \n";
}

bool push()
{
	return 0;
}

bool pop()
{
	return 0;
}