#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <string>
using namespace std;
#define MAX 100 // Có tối đa 100 phòng

//									Đề tài số 9: Quản lý phòng trọ
//	1. Mỗi nhà trọ các thông tin : mã phòng trọ, họ tên người thuê trọ, số CMND người thuê			Done
//	trọ, ngày tháng năm sinh người thuê trọ, chỉ số điện, chỉ số nước, đơn giá phòng trọ			
//	2. Tạo Queue chứa thông tin Nhà trọ bằng 2 cách : nhập từ bàn phím và đọc / ghi từ file txt.	Done
//	3. Hiển thị tất cả các thông tin của nhà trọ trong Queue.										Done
//	4. Xóa 1 phòng trọ trong Queue.																	Done
//	5. Thêm 1 phòng trọ vào Queue.																	Done
//	6. Tìm phòng trọ có chỉ số điện cao nhất.														Done
//	7. Tìm phòng trọ của người thuê trọ có họ tên “ Tran Van A”.									Done
//	8. Đếm số phòng trọ có đơn giá phòng trọ cao nhất.												Done
//	9. Đếm số phòng trọ có người thuê trọ có năm sinh < 2002.										Done
//	10. Tính tổng chỉ số điện của tất cả các phòng trọ trong nhà trọ.								Done
//	11. Mỗi nhà trọ là một đỉnh trong đồ thị, khoảng cách là trọng số cạnh nối. Tìm đường đi		Done
//	từ nhà trọ này sang nhà trọ khác bằng phương pháp duyệt theo chiều rộng.

struct BirthDay
{
	int day, month, year;
};

int b[MAX][MAX];
string vtex[MAX];
int C[MAX]; // Mảng đỉnh
int D[MAX]; // Mảng trọng số
int bfs[MAX];
int nbfs, ndem, np;


// Thông tin phòng trọ
struct PhongTro
{
	string idRoom, name, idCard;	// Mã phòng chứa, Tên người thuê, Số CMND.
	BirthDay DOB;	// Ngày tháng năm sinh của người thuê trọ
	double water, electric, price;	// Chỉ số điện, nước, đơn giá phòng
};

void init(int& front, int& rear, int n);
void inputList(PhongTro list[], int n);
void outputList(PhongTro list[], int n, int front);
bool inputFile(PhongTro list[], int& n);
void outputFile(PhongTro list[], int front, int rear, int n);
void input1Phong(PhongTro list[], int n, PhongTro& room);
bool push(PhongTro list[], int& bottom, int& top, PhongTro x, int& n);
bool pop(PhongTro list[], int& front, int& rear, int& n);
void pushBFS(int a[], int& front, int& rear, int x);
void popBFS(int a[], int& front, int& rear, int& x);
void ouputPhongDienCaoNhat(PhongTro list[], int front, int rear);
void findRoomByName(PhongTro list[], int front, int rear, string name);
void demSoPhongTroDonGiaMax(PhongTro list[], int front, int rear);
void demSoPhongTroByNamSinh(PhongTro list[], int front, int rear, int namSinh);
double TongChiSoDien(PhongTro list[], int front, int rear);
void BFS(string start, string end, int front, int rear,int n);

void taoVtex(PhongTro list[], int front, int rear);
int vtexIndex(string v, int front, int rear);
void nhap(int a[][MAX], int n, int front, int rear);
void xuat(int a[][MAX], int front, int rear);
void xuatKQ(int a[MAX], int n);
bool checkBirth(PhongTro room);
void capitalize(string& s);
void deleteSpace(string& s);
void trim(string& s);

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
			<< "10/ Dem so phong tro co nguoi thue co nam sinh < X (X >= 1900) \n"
			<< "11/ Tinh tong chi so dien \n"
			<< "12/ BFS nhap tu ban phim \n"
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
			init(front, rear, n);

			inp = true;
			cout << "Nhap du lieu thanh cong! \n";
			break;
		case 2:
			if (inputFile(a, n))
			{
				cout << "Nhap File thanh cong! \n";
				init(front, rear, n);
				inp = true;
			}
			else
				cout << "Thong tin trong File khong hop le hoac File khong ton tai! \n";
			break;
		case 3:
			if (inp)
			{
				cout << "So luong phong tro hien co: " << n << " phong! \n";
				outputList(a, front, rear);
			}
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 4:
			if (inp)
				outputFile(a, front, rear, n);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 5:
		{
			PhongTro x;
			input1Phong(a, n, x);
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
		case 7:
			if (inp)
			{
				cout << " Phong co chi so dien cao nhat \n";
				ouputPhongDienCaoNhat(a, front, rear);
			}
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 8:
			if (inp)
			{
				string ten;
				cin.ignore();
				cout << "Nhap ten can tim: ";
				do
				{
					getline(cin, ten);
					trim(ten);
					if (ten.size() == 0)
						cout << "Khong hop le! Nhap lai: ";
				} while (ten.size() == 0);
				capitalize(ten);
				findRoomByName(a, front, rear, ten);
			}
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 9:
			if (inp)
				demSoPhongTroDonGiaMax(a, front, rear);
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 10:
			if (inp)
			{
				int namSinh;
				cout << "Nhap nam sinh: ";
				do
				{
					cin >> namSinh;
					if (namSinh < 1900)
						cout << "Khong hop le! Nhap lai (nam sinh >= 1900): ";
				} while (namSinh < 1900);
				demSoPhongTroByNamSinh(a, front, rear, namSinh);
			}
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 11:
			if (inp)
				cout << "Tong chi so dien: " << TongChiSoDien(a, front, rear) << endl;
			else
				cout << "Chua nhap du lieu! \n";
			break;
		case 12:
			if (inp)
			{
				char choose;
				string start, end;
				taoVtex(a, front, rear);
				nhap(b, n, front, rear);

				do
				{
					system("cls");
					xuat(b, front, rear);
					cout << "Nhap diem bat dau: ";
					do
					{
						cin >> start;
						trim(start);
						capitalize(start);
						if (vtexIndex(start, front, rear) == -1)
							cout << "Ma phong khong hop le! Nhap lai: ";
					} while (vtexIndex(start, front, rear) == -1);

					cout << "Nhap diem ket thuc: ";
					do
					{
						cin >> end;
						trim(end);
						capitalize(end);
						if (vtexIndex(end, front, rear) == -1)
							cout << "Ma phong khong hop le! Nhap lai: ";
					} while (vtexIndex(end, front, rear) == -1);

					BFS(start, end, front, rear, n);
					cout << "Quang duong BFS: ";
					xuatKQ(bfs, nbfs);

					for (int i = 0; i < nbfs - 1; i++)
						ndem += D[i];

					cout << "Do dai quang duong tu " << start << " toi " << end << " la: " << ndem;
					cout << endl;
					ndem = 0;
					cout<< "An phim bat ky de tiep tuc tim duong di, an phim 0 de dung.\nLua chon: ";
					choose = _getche();
				} while (choose != '0');
			}
			else
				cout << "Chua nhap du lieu! \n";
			break;
		default: exit(0);
		}

		cout << endl;
		cout << "Nhan phim bat ky de quay ve menu! \n";
		_getch();
	} while (key > 0 && key < 13);
}

void init(int& front, int& rear, int n)
{
	rear = n - 1;
	front = 0;
}

// Xóa cách 2 đầu
void trim(string& s)
{
	const char* space = " ";
	s.erase(s.find_last_not_of(space) + 1);
	s.erase(0, s.find_first_not_of(space));
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
			{
				if (room.DOB.day <= 29) return true;
			}
			else if (room.DOB.day < 29) return true;
			break;
		case 4: case 6: case 9: case 11:
			if (room.DOB.day <= 30) return true;
			break;
		default:
			if (room.DOB.day <= 31) return true;
			break;
		}
	}
	return false;
}

// Nhập 1 phòng
void input1Phong(PhongTro list[], int n, PhongTro& room)
{
	cin.ignore();
	cout << "+ Nhap ma phong tro: ";
	do
	{
		getline(cin, room.idRoom);
		trim(room.idRoom);
		if (room.idRoom.size() == 0)
			cout << "Khong hop le! Nhap lai: ";
	} while (room.idRoom.size() == 0);
	deleteSpace(room.idRoom);
	capitalize(room.idRoom);
	room.idRoom = room.idRoom.substr(0, 5);	// Mã phòng tối đa 5 ký tự

	cout << "+ Nhap ho ten nguoi thue tro: ";
	do
	{
		getline(cin, room.name);
		trim(room.name);
		if (room.name.size() == 0)
			cout << "Khong hop le! Nhap lai: ";
	} while (room.name.size() == 0);
	capitalize(room.name);		// Format Họ tên
	room.name = room.name.substr(0, 50);	// Họ tên tối đa 50 ký tự

	cout << "+ Nhap so CMND: ";
	do
	{
		getline(cin, room.idCard);
		trim(room.idCard);
		if (room.idCard.size() == 0)
			cout << "Khong hop le! Nhap lai: ";
	} while (room.idCard.size() == 0);
	deleteSpace(room.idCard);
	room.idCard = room.idCard.substr(0, 12);	// Số CMND tối đa 12 ký tự

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
		input1Phong(list, n, list[i]);
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
	cout << fixed << setprecision(2) << room.electric << endl;
	cout << "+ Chi so nuoc: ";
	cout << fixed << setprecision(2) << room.water << endl;
	cout << "+ Don gia phong: ";
	cout << fixed << setprecision(2) << room.price << endl;
}

// Xuất nhiều phòng
void outputList(PhongTro list[], int front, int rear)
{
	cout << "========================================================== \n";
	if (rear != -1)
		for (int i = front; i <= rear; i++)
		{
			cout << "Thong tin phong tro thu " << i - front + 1 << endl;
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
					if (list[i].idRoom.size() == 0) return false;
					deleteSpace(list[i].idRoom);
					capitalize(list[i].idRoom);
					list[i].idRoom = list[i].idRoom.substr(0, 5);
				}

				break;
				case 1:
				{
					list[i].name = temp;
					trim(list[i].name);
					if (list[i].name.size() == 0) return false;
					capitalize(list[i].name);		// Format Họ tên
					list[i].name = list[i].name.substr(0, 50);	// Họ tên tối đa 50 ký tự
				}
				break;
				case 2:
				{
					list[i].idCard = temp;
					trim(list[i].idCard);
					if (list[i].idCard.size() == 0) return false;
					deleteSpace(list[i].idCard);
					list[i].idCard = list[i].idCard.substr(0, 5);
				}
				break;
				case 3:
				{
					int space = temp.find('/');
					list[i].DOB.day = stoi(temp.substr(0, space));
					list[i].DOB.month = stoi(temp.substr(space + 1, temp.size() - 4 - space));
					list[i].DOB.year = stoi(temp.substr(temp.size() - 4, 4));

					if (!checkBirth(list[i])) return false;
				}
				break;
				case 4:
				{
					list[i].electric = stod(temp);
					if (list[i].electric < 0) return false;
				}
				break;
				case 5:
				{
					list[i].water = stod(temp);
					if (list[i].water < 0) return false;
				}

				break;
				case 6:
				{
					list[i].price = stod(temp);
					if (list[i].price < 0) return false;
				}
				break;
				}
				if (count == 6) break;
				count++;
			}
		}
		return true;
		fi.close();
	}
	else
		return false;
}

// Ghi File
void outputFile(PhongTro list[], int front, int rear, int n)
{
	ofstream fo("database.txt");	// fo = File output

	fo << n << endl;
	if (rear != -1)
		for (int i = front; i <= rear; i++)
		{
			fo << list[i].idRoom << ", "
				<< list[i].name << ", "
				<< list[i].idCard << ", "
				<< list[i].DOB.day << "/" << list[i].DOB.month << "/" << list[i].DOB.year << ", "
				<< fixed << setprecision(2) << list[i].electric << ", "
				<< fixed << setprecision(2) << list[i].water << ", "
				<< fixed << setprecision(2) << list[i].price << ", " << endl;
		}
	cout << "Ghi File thanh cong! \n";
	fo.close();
}

// Push phần tử bằng phương pháp vòng
bool push(PhongTro list[], int& front, int& rear, PhongTro x, int& n)
{
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

void pushBFS(int a[], int& front, int& rear, int x)
{
	if (front == -1)
		front = 0;
	if (rear == MAX - 1)
		rear = -1;
	a[++rear] = x;
}

void popBFS(int a[], int& front, int& rear, int& x)
{
	x = a[front];
	if (front == rear)
		front = rear = -1;
	else
	{
		front++;
		if (front > MAX - 1)
			front = 0;
	}
}

void ouputPhongDienCaoNhat(PhongTro list[], int front, int rear)
{
	PhongTro room[MAX];
	int dau = -1, cuoi = -1, m = 0;
	double maxelectric = -1;

	for (int i = front; i <= rear; i++)
	{
		if (maxelectric < list[i].electric)
			maxelectric = list[i].electric;
	}

	for (int i = front; i <= rear; i++)
	{
		if (maxelectric == list[i].electric)
			push(room, dau, cuoi, list[i], m);
	}
	outputList(room, dau, cuoi);
}

void findRoomByName(PhongTro list[], int front, int rear, string name)
{
	PhongTro room[MAX];
	bool kt = false;
	int dau = -1, cuoi = -1, m = 0;

	for (int i = front; i <= rear; i++)
	{
		if (name.compare(list[i].name) == 0)
		{
			push(room, dau, cuoi, list[i], m);
			kt = true;
		}
	}
	if (kt == true)
		outputList(room, dau, cuoi);
	else
		cout << "khong tim thay \n";
}

void demSoPhongTroDonGiaMax(PhongTro list[], int front, int rear)
{
	int d = 0;
	PhongTro room[MAX];
	int dau = -1, cuoi = -1, m = 0;
	double maxprice = -1;

	for (int i = front; i <= rear; i++)
	{
		if (maxprice < list[i].price)
			maxprice = list[i].price;
	}

	for (int i = front; i <= rear; i++)
	{
		if (maxprice == list[i].price)
		{
			push(room, dau, cuoi, list[i], m);
			d++;
		}
	}

	cout << "Co " << d << " phong tro co don gia phong cao nhat \n";
	if (d != 0)
		outputList(room, dau, cuoi);
}

void demSoPhongTroByNamSinh(PhongTro list[], int front, int rear, int namSinh)
{
	int d = 0;
	PhongTro room[MAX];
	int dau = -1, cuoi = -1, m = 0;

	for (int i = front; i <= rear; i++)
	{
		if (list[i].DOB.year < namSinh)
		{
			push(room, dau, cuoi, list[i], m);
			d++;
		}
	}

	cout << "Co " << d << " phong tro co nguoi thue tro co nam sinh < " << namSinh << endl;
	if (d != 0)
		outputList(room, dau, cuoi);
}

double TongChiSoDien(PhongTro list[], int front, int rear)
{
	double sum = 0;

	for (int i = front; i <= rear; i++)
		sum += list[i].electric;

	return sum;
}

// Tạo dòng tên phòng
void taoVtex(PhongTro list[], int front, int rear)
{
	for (int i = front; i <= rear; i++)
		vtex[i] = list[i].idRoom;
}

// Khởi tạo mảng chứa đỉnh đang xét
void khoiTaoChuaXet(int front, int rear)
{
	for (int i = front; i <= rear; i++)
		C[i] = 1;
}

// Đường đi BFS
void xuatKQ(int b[MAX], int n)
{
	for (int i = 0; i < n; i++)
		cout << vtex[b[i]] << " ";

	cout << endl;
}

// Nhập ma trận kề
void nhap(int b[][MAX], int n, int front, int rear)
{
	cout << "Co " << n << " phong \n";
	for (int i = front; i <= rear; i++)
	{
		cout << "Nhap gia tri ke phong thu " << i - front + 1 << ": ";

		for (int j = front; j <= rear; j++)
			cin >> b[i][j];
	}
}

// Xuất ma trận kề
void xuat(int b[][MAX], int front, int rear)
{
	for (int i = front; i <= rear; i++)
		cout << "\t" << vtex[i];
	cout << endl;

	for (int i = front; i <= rear; i++)
	{
		cout << vtex[i];
		for (int j = front; j <= rear; j++)
			cout << "\t" << b[i][j];

		cout << endl;
	}
}

void BFS(string start, string end, int front, int rear, int n)
{
	int s = vtexIndex(start, front, rear);
	int e = vtexIndex(end, front, rear);
	int a[MAX];
	int dau = -1, cuoi = -1, p, m = 0;

	D[MAX] = bfs[MAX] = 0;
	nbfs = np = 0;
	khoiTaoChuaXet(front, rear);

	pushBFS(a, dau, cuoi, s);
	C[s] = 0;

	while (dau != -1)
	{
		popBFS(a, dau, cuoi, p);
		bfs[nbfs] = p;
		nbfs++;
		if (p == e) return;


		for (int w = front; w <= rear; w++)
		{
			if (C[w] == 1 && b[p][w] != 0)
			{
				pushBFS(a, dau, cuoi, w);
				C[w] = 0;
				D[np] = b[p][w];
				np++;
			}
		}
	}
	cout<<"Khong tim thay duong \n ";
}

int vtexIndex(string v, int front, int rear)
{
	for (int i = front; i <= rear; i++)
	   if (vtex[i].compare(v) == 0) return i;
	return -1;
}

