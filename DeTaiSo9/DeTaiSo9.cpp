#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
#define MAX 100 // Có tối đa 100 phòng
//	Đề tài số 9: Quản lý phòng trọ
//	1. Mỗi nhà trọ các thông tin : mã phòng trọ, họ tên người thuê trọ, số CMND người thuê			Thanh	Done
//	trọ, ngày tháng năm sinh người thuê trọ, chỉ số điện, chỉ số nước, đơn giá phòng trọ			
//	2. Tạo Queue chứa thông tin Nhà trọ bằng 2 cách : nhập từ bàn phím và đọc / ghi từ file txt.	Thanh	Done
//	3. Hiển thị tất cả các thông tin của nhà trọ trong Queue.										Thanh	Done
//	4. Xóa 1 phòng trọ trong Queue.																	Thanh	Done
//	5. Thêm 1 phòng trọ vào Queue.																	Thanh	Done
//										Anh chị test lại giúp em nha, xem còn sai sót gì ko <3
// ==================================================================================================================================
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

void inputList(PhongTro list[], int n);
void outputList(PhongTro list[], int n);
bool inputFile(PhongTro list[], int& n);
void outputFile(PhongTro list[], int n);
void input1Phong(PhongTro& room);
bool push(PhongTro list[], int& bottom, int& top, PhongTro x, int& n);
bool pop(PhongTro list[], int& front, int& rear, int& n);
void ouputPhongCoDonGiaCaoNhat(PhongTro list[], int &n);
void findRoomByName(PhongTro list[],int &n,string name);
string toLowerCase(string &s1);
int main()
{
	PhongTro a[MAX];
	int rear, front, key, n = 0;	// Key là user chọn
	bool inp = false; // Kiểm tra nhập dữ liệu chưa
	rear = front = -1;	// Khởi tạo Queue rỗng

	do
	{
		system("cls");
		cout << "1/ Nhap du lieu tu ban phim \n"
			<< "2/ Nhap du lieu tu File \n"
			<< "3/ Hien thi thong tin tat ca phong tro (Console) \n"
			<< "4/ Hien thi thong tin tat ca phong tro (File) \n"
			<< "5/ Them 1 phong tro \n"
			<< "6/ Xoa  1 phong tro \n"
			<< "7/ Phong tro co chi so dien cao nhat \n"
			<< "8/ Tim nguoi trong phong tro \n"
			<< "9/ Dem so phong tro co don gia phong cao nhat \n"
			<< "10/ Dem so phong tro co nguoi thue co nam sinh < 2002 \n"
			<< "11/ Tinh tong chi so dien \n"
			<< "12/ BFS \n"
			<< "13/ Thoat \n"
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
			inputList(a, n);

			inp = true;
			cout << "Nhap du lieu thanh cong! \n";
			break;
		case 2:
			if (inputFile(a, n))
			{
				cout << "Nhap File thanh cong! \n";
				inp = true;
			}
			else
				cout << "Thong tin trong File khong hop le hoac File khong ton tai! \n";
			break;
		case 3:
			if (inp)
				outputList(a, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 4:
			if (inp)
				outputFile(a, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 5:
			{
				PhongTro x;
				input1Phong(x);
				if (push(a, front, rear, x, n))
					cout << "Them thanh cong! \n";
				else
					cout << "Them that bai! \n";
				inp = true;
			}		
			break;
		case 6:
			if (inp)
			{
				if (pop(a, front, rear, n))
					cout << "Xoa thanh cong! \n";
				else
					cout << "Xoa that bai! \n";
			}
			else
				cout << "Chua nhap du lieu! \n";
			break;
//===============================================================
		case 7:
			if (inp)
				ouputPhongCoDonGiaCaoNhat(a,n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 8:
			if (inp)
				{
					string ten;
					cin.ignore();
				cout<<"Nhap ten can tim: ";
				getline(cin, ten);
				findRoomByName(a,n,ten);
				}
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 9:
			if (inp)
				outputFile(a, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 10:
			if (inp)
				outputFile(a, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 11:
			if (inp)
				outputFile(a, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 12:
			if (inp)
				outputFile(a, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		default: exit(0);
		}
		cout << endl;
		cout << "Nhan phim bat ky de quay ve menu! \n";
		_getch();
	} while (key > 0 && key < 13);
	system("pause");
	return 0;
}

// Xóa cách 2 đầu
void trim(string& s)
{
	int left = 0, right = s.size() - 1; // Đầu chuỗi và cuối chuỗi
	while (s[left] == ' ' || (s[right] == ' '))
	{
		if (s[left] == ' ') left++;
		if (s[right] == ' ') right--;
	}

	s.erase(right + 1, s.size() - 1);
	s.erase(0, left);
}

// Xóa cách ở giữa
void deleteSpace(string& s)
{
	int i = 0;

	while (i != s.size())
	{
		if (s[i] == ' ')
			s.erase(i, 1);
		else i++;
	}
}

// In hoa chữ đầu
void capitalize(string& s)
{
	int i = 1;
	s[0] = toupper(s[0]);
	while (i != s.size())
	{
		if ((s[i] != ' ') && s[i - 1] == ' ')
			s[i] = toupper(s[i]);
		else
			if (s[i] == ' ' && s[i + 1] == ' ')
			{
				s.erase(i, 1);
				i--;
			}
			else s[i] = tolower(s[i]);
		i++;
	}
}

// Kiểm tra ngày sinh hợp lệ
bool checkBirth(PhongTro room)
{
	if (room.DOB.month >= 1 && room.DOB.month <= 12 && room.DOB.year >= 1900 && room.DOB.day >= 1)	// Giới hạn ngày sinh hợp lệ
	{
		switch (room.DOB.month)
		{
		case 2:
			if (room.DOB.year % 400 == 0 || room.DOB.year % 4 == 0 && room.DOB.year % 100 != 0)	// Kiểm tra năm nhuận
				if (room.DOB.day <= 29) return 1;
			break;
		case 4: case 6: case 9: case 11:
			if (room.DOB.day <= 30) return 1;
			break;
		default:
			if (room.DOB.day <= 31) return 1;
			break;
		}
	}
	return 0;
}

// Nhập 1 phòng
void input1Phong(PhongTro& room)
{
	cin.ignore();
	cout << "+ Nhap ma phong tro: ";
	getline(cin, room.idRoom);
	trim(room.idRoom);
	deleteSpace(room.idRoom);
	room.idRoom.substr(0, 5);	// Mã phòng tối đa 5 ký tự

	cout << "+ Nhap ho ten nguoi thue tro: ";
	getline(cin, room.name);
	trim(room.name);
	capitalize(room.name);		// Format Họ tên
	room.name.substr(0, 50);	// Họ tên tối đa 50 ký tự

	cout << "+ Nhap so CMND: ";
	getline(cin, room.idCard);
	trim(room.idCard);
	deleteSpace(room.idCard);
	room.idCard.substr(0, 12);	// Số CMND tối đa 12 ký tự

	cout << "+ Nhap ngay sinh: ";
	do
	{
		cin >> room.DOB.day >> room.DOB.month >> room.DOB.year;
		if (!checkBirth(room))
			cout << "Ngay sinh khong hop le! Nhap lai: ";
	} while (!checkBirth(room));

	cout << "+ Nhap chi so dien: ";
	do
	{
		cin >> room.electric;
		if (room.electric < 0)
			cout << "Chi so dien khong hop le! Nhap lai: ";
	} while (room.electric < 0);

	cout << "+ Nhap chi so nuoc: ";
	do
	{
		cin >> room.water;
		if (room.water < 0)
			cout << "Chi so nuoc khong hop le! Nhap lai: ";
	} while (room.water < 0);

	cout << "+ Nhap don gia phong: ";
	do
	{
		cin >> room.price;
		if (room.price < 0)
			cout << "Don gia phong khong hop le! Nhap lai: ";
	} while (room.price < 0);
}

// Nhập nhiều phòng
void inputList(PhongTro list[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap thong tin phong tro thu " << i + 1 << endl;
		input1Phong(list[i]);
		cout << "========================================================== \n";
	}
}

// Xuất 1 phòng
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

// Xuất nhiều phòng
void outputList(PhongTro list[], int n)
{
	cout << "So luong phong tro hien co: " << n << " phong ! \n";
	cout << "========================================================== \n";
	for (int i = 0; i < n; i++)
	{
		cout << "Thong tin phong tro thu " << i + 1 << endl;
		output1Phong(list[i]);
		cout << "========================================================== \n";
	}
}

// Đọc File
bool inputFile(PhongTro list[], int& n)
{
	string fileName;
	cout << "Nhap ten file: ";
	cin >> fileName;
	fileName += ".txt";

	ifstream fi;	// fi = File input
	string temp;

	fi.open(fileName);
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
				{
					trim(temp);
					list[i].idRoom = temp.erase(0, 1);
					deleteSpace(list[i].idRoom);
					list[i].idRoom.substr(0, 5);
				}

				break;
				case 1:
				{
					list[i].name = temp;
					trim(list[i].name);
					capitalize(list[i].name);		// Format Họ tên
					list[i].name.substr(0, 50);	// Họ tên tối đa 50 ký tự
				}
				break;
				case 2:
				{
					list[i].idCard = temp;
					trim(list[i].idCard);
					deleteSpace(list[i].idCard);
					list[i].idCard.substr(0, 5);
				}
				break;
				case 3:
				{
					int space = temp.find('/');
					list[i].DOB.day = stoi(temp.substr(0, space));
					list[i].DOB.month = stoi(temp.substr(space + 1, temp.size() - 4 - space));
					list[i].DOB.year = stoi(temp.substr(temp.size() - 4, 4));

					if (!checkBirth(list[i])) return 0;
				}
				break;
				case 4:
				{
					list[i].electric = stod(temp);
					if (list[i].electric < 0) return 0;
				}
				break;
				case 5:
				{
					list[i].water = stod(temp);
					if (list[i].water < 0) return 0;
				}

				break;
				case 6:
				{
					list[i].price = stod(temp);
					if (list[i].price < 0) return 0;
				}
				break;
				}
				if (count == 6) break;
				count++;
			}
		}

		return 1;
		fi.close();
	}
	else
		return 0;
}

// Ghi File
void outputFile(PhongTro list[], int n)
{
	ofstream fo("database.txt");	// fo = File output

	fo << n << endl;
	for (int i = 0; i < n; i++)
	{
		fo << list[i].idRoom << ", "
			<< list[i].name << ", "
			<< list[i].idCard << ", "
			<< list[i].DOB.day << "/" << list[i].DOB.month << "/" << list[i].DOB.year << ", "
			<< list[i].electric << ", "
			<< list[i].water << ", "
			<< list[i].price << ", " << endl;
	}
	cout << "Ghi File thanh cong! \n";
	fo.close();
}

// Push phần tử bằng phương pháp vòng
bool push(PhongTro list[], int& front, int& rear, PhongTro x, int& n)
{
	if (n != 0)		// Nếu đã input sẽ cập nhật lại front và rear
	{
		rear = n - 1;
		front = 0;
	}
		
	if (rear - front <= MAX - 1 && rear - front != -1) // Khi Queue chưa đầy
	{
		if (front == -1)	// Xét Queue rỗng
			front = 0;
		if (rear == MAX - 1)	// Xét Queue tràn
			rear = -1;
		list[++rear] = x;
		n++;
		return 1;
	}
	return 0;
}

// Pop phần tử bằng phương pháp vòng
bool pop(PhongTro list[], int& front, int& rear, int& n)
{
	if (n != 0)		// Nếu đã input sẽ cập nhật lại front và rear
	{
		rear = n - 1;
		front = 0;
	}

	if (front != -1)
	{
		if (front == rear) 
			front = rear = -1;
		else
		{
			front++;
			if (front > MAX - 1)
				front = 0;
		}
		n--;
		return 1;
	}
	return 0;
}
void ouputPhongCoDonGiaCaoNhat(PhongTro list[], int &n)
{
	PhongTro room[MAX];
	int front=-1,rear=-1,m=0;
	double maxElectric=0;
	int kt=0;
	for(int i=0; i<n ; i++) 
	{
          if(maxElectric<list[i].electric)
		   {
			   maxElectric=list[i].electric;
			   kt=1;
		   }		
	}
	if(kt==1)
	for(int i=0; i<n ; i++) 
	{
          if(maxElectric==list[i].electric)
		 push(room,front,rear,list[i],m);
	}
	outputList(room,m);
}
void findRoomByName(PhongTro list[],int &n,string name)
{
	PhongTro room[MAX];
	int kt=0;
	int front=-1,rear=-1,m=0;
	for(int i=0; i<n; i++)
	{
		if(toLowerCase(name).compare(toLowerCase(list[i].name))==0)
		{
			push(room,front,rear,list[i],m);
			kt=1;
		}
	}
	if(kt==1) 
	outputList(room,m);
	else
	cout<<"Khong tim thay \n";
}
string toLowerCase(string &s1)
{
	string m=s1;
	int i=0;
	while(i<m.size())
	{
		m[i]=tolower(m[i]);
		i++;
	}
	return m;
}
