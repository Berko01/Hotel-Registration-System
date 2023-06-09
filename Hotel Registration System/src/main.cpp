#include <iostream>
using namespace std;
#include <fstream>
#include <vector>

#define roomCount 5

class Hotel
{
private:
	string name;
	string telephone;
	int roomNo;
	int day;
	float price;

public:
	void hotelRecord(string name, string telephone, int roomNo, int day, float price);
	void customerInfo(int);
	void emptyRooms();
	int roomControl(int);
	void updateRecord(int);
	void deleteRecord(int);
	int ısRoomEmpty(int);
	friend ostream &operator<<(ostream &, Hotel &);
};

ostream &operator<<(ostream &cikti, Hotel &obj1)
{
	cikti << obj1.roomNo << " " << obj1.name << " " << obj1.telephone << " " << obj1.day << " " << obj1.price << endl;
	return cikti;
}

int Hotel::ısRoomEmpty(int roomNum)
{
	fstream recordBook;
	recordBook.open("recordBook.txt", ios::in);
	while (recordBook >> roomNo)
	{
		if (roomNo == roomNum)
		{
			recordBook.close();
			return -1;
		}
		else
		{
			recordBook >> name >> telephone >> day >> price;
		}
	}
	recordBook.close();
	return 1;
}

void Hotel::emptyRooms()
{
	fstream recordBook;
	recordBook.open("recordBook.txt", ios::in);
	int roomStates[roomCount];
	for (int i = 0; i < roomCount; i++)
	{
		roomStates[i] = -1;
	}
	while (recordBook >> roomNo)
	{
		roomStates[roomNo] = 1;
		recordBook >> name >> telephone >> day >> price;
	}
	for (int i = 0; i < roomCount; i++)
	{
		// Boş olan odalar -1den farklı olduğu için onları yazdırıyor
		if (roomStates[i] == -1)
		{
			cout << i << endl;
		}
	}
	recordBook.close();
}

void Hotel::hotelRecord(string name, string telephone, int roomNo, int day, float price)
{
	this->name = name;
	this->telephone = telephone;
	this->roomNo = roomNo;
	this->day = day;
	this->price = price;
	fstream recordBook;
	recordBook.open("recordBook.txt", ios::out);
	recordBook << *this;
}

void Hotel::deleteRecord(int roomNum)
{
	fstream recordBook, copyRecordBook;
	recordBook.open("recordBook.txt", ios::in);
	copyRecordBook.open("recordBook2.txt", ios::out);
	while (recordBook >> roomNo)
	{
		if (roomNum != roomNo)
		{
			recordBook >> name >> telephone >> day >> price;
			copyRecordBook << *this;
		}
		else
			recordBook >> name >> telephone >> day >> price;
	}
	recordBook.close();
	copyRecordBook.close();
	remove("recordBook.txt.");
	rename("recordBook2.txt.", "recordBook.txt"); // eskiDosyaAdı-yeniDosyaAdı
	cout << "Kayit silindi." << endl;
}

void Hotel::updateRecord(int roomNum)
{
	fstream recordBook, copyRecordBook;
	recordBook.open("recordBook.txt", ios::in);
	copyRecordBook.open("recordBook2.txt", ios::out);
	while (recordBook >> roomNo)
	{
		if (roomNum != roomNo)
		{
			recordBook >> name >> telephone >> day >> price;
			copyRecordBook << *this;
		}
		else
		{
			cout << "Oda numarasi giriniz: " << endl;
			cin >> roomNo;
			while (this->ısRoomEmpty(roomNo) == -1)
			{
				cout << "Oda dolu yeni oda numarasi giriniz: " << endl;
				cin >> roomNo;
			}
			cout << "Isim,telefon,gun giriniz:" << endl;
			cin >> name >> telephone >> day;
			price = day * 100;
			copyRecordBook<<*this;
		}
	}
	recordBook.close();
	copyRecordBook.close();
	remove("recordBook.txt.");
	rename("recordBook2.txt.", "recordBook.txt"); // eskiDosyaAdı-yeniDosyaAdı
	cout << "Kayit guncellendi." << endl;
}

void Hotel::customerInfo(int roomNum)
{

	fstream recordBook;
	recordBook.open("recordBook.txt", ios::in);
	while (recordBook >> roomNo)
	{
		if (roomNo == roomNum)
		{
			recordBook >> name >> telephone >> day >> price;
			cout << "Room num: " << roomNo << endl;
			cout << "Name: " << name << endl;
			cout << "Telephone: " << telephone << endl;
			cout << "Day: " << day << endl;
			cout << "Price: " << price << endl;
			recordBook.close();
			return;
		}
		else
		{
			recordBook >> name >> telephone >> day >> price;
		}
	}
}

int main()
{

	vector<Hotel> vector1;
	string name;
	char telephone[10];
	int day;
	int price,hotelNum;
	Hotel hotel1;
	vector1.push_back(hotel1);
	cout << "Otel Kayit Sistemine Hos Geldiniz.." << endl;
	cout<<	"Islem yapilmak istenen otelin numarasini giriniz."<<endl;
	cin>>hotelNum;
	cout << "Otel kayit icin 1 tuslayiniz" << endl;
	cout << "Musteri Bilgileri icin 2 tuslayiniz" << endl;
	cout << "Bos odalarimizi gostermek icin 3 tuslayiniz" << endl;
	cout << "Kayit guncelleme icin 4 tuslayiniz" << endl;
	cout << " Kayit silmek icin 5 tuslayiniz" << endl;
	cout << " Cikis icin 6 tuslayiniz" << endl;
	int process = 0;
	cin >> process;

	if (process == 1)
	{
		cout << "Bos odalar:" << endl;
		vector1[hotelNum].emptyRooms();
		cout << "Lutfen bos bir oda seciniz." << endl;
		int roomChoice;
		cin >> roomChoice;
		if (vector1[hotelNum].ısRoomEmpty(roomChoice) == 1)
		{
			fstream kayitYaz;
			kayitYaz.open("altunogluOtel.txt", ios::out | ios::app);
			cout << " musteri isim: ";
			cin >> name;
			cout << " tlf No: ";
			cin >> telephone;
			cout << " gun : ";
			cin >> day;
			price = day * 100;
			vector1[hotelNum].hotelRecord(name, telephone, roomChoice, day, price);
		}
		else
		{
			cout << "Bu oda doludur." << endl;
			return 0;
		}
	}
	else if (process == 2)
	{
		cout << "Gosterilecek kayidin oda numarasini giriniz." << endl;
		int roomChoice;
		cin >> roomChoice;
		vector1[hotelNum].customerInfo(roomChoice);
	}
	else if (process == 3)
	{
		cout << "Bos odalar: " << endl;
		vector1[hotelNum].emptyRooms();
	}
	else if (process == 4)
	{
		cout << "Guncellenecek kayidin oda numarasini giriniz." << endl;
		int roomChoice;
		cin >> roomChoice;
		vector1[hotelNum].updateRecord(roomChoice);
	}
	else if (process == 5)
	{
		cout << "Silinecek kayidin oda numarasini giriniz." << endl;
		int roomChoice;
		cin >> roomChoice;
		vector1[hotelNum].deleteRecord(roomChoice);
	}
	else if (process == 6)
	{
		cout << "Hoscakalin." << endl;
		return 0;
	}

	

	system("pause");
	return 0;
}