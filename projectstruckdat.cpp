#include <iostream>
#include <string.h>
#include <malloc.h>
#include <fstream>
#define max 150

using namespace std;

typedef struct typenode *typeptr;
typedef struct typestack *typeptr1;
struct isi_data
{
    char nama[50], alamat[40];
    int no, umur, gaji;
};

struct typenode
{
    isi_data info;
    typeptr next;
};
struct typestack
{
    isi_data info1;
    typeptr1 next1;
};
typeptr awal, akhir, qdepan, qbelakang;
typeptr1 stack, stackawal;

void buatlistbaru();
int listkosong();
void sisipnode(isi_data IB);
void bacamaju();
void buatqueue();
int queuekosong();
void enqueue(isi_data IB);
void dequeue();
void cetakqueue();
void buatstack();
void push(isi_data IB);
void pop();
void karyawan();
void cetakstack();
string ulang, namafile, ambil_file;
isi_data data[max];
main()
{
    int menu, i;
    
    i = 1;
    buatlistbaru();
    buatstack();
    buatqueue();
    do
    {
        system("CLS");
        cout << "1. Input data/ tambah data";
        cout << "\n2. Simpan file";
        cout << "\n3. Ambil file";
        cout << "\n4. Data Karyawan yang pernah mendaftar";
        cout << "\n5. Gaji";
        cout << "\n6. Pemberian Gaji";
        cout << "\n7. Pengurangan karyawan";
        cout << "\n8. Data Karyawan";
        cout << "\n9. Exit";
        cout << "\nPilih : ";
        cin >> menu;
        switch (menu)
        {
        case 1:
            do
            {
                cout << "ID 	 : ";
                cin >> data[i].no;
                cout << "Nama 	 : ";
                cin.ignore();
                cin.getline(data[i].nama, 50);
                cout << "Alamat   : ";
                cin.getline(data[i].alamat, 40);
                cout << "Umur	 : ";
                cin >> data[i].umur;
                cout << "Gaji     : ";
                cin >> data[i].gaji;
                sisipnode(data[i]);
                enqueue(data[i]);
                push(data[i]);
                i++;
                do
                {
                    cout << "\nTambah data?y/n : ";
                    cin >> ulang;
                } while ((ulang != "y" && ulang != "Y") && (ulang != "n" && ulang != "N"));
            } while (ulang == "y" || ulang == "Y");
            break;

        case 2:
        {
            cout << "Masukkan nama file : ";
            cin >> namafile;
            ofstream karyawan(namafile.c_str(), ios::out);
            for (int b = 1; b < i; b++)
            {
                karyawan << data[b].no << endl
                         << data[b].nama << endl
                         << data[b].alamat << endl
                         << data[b].umur << endl
                         << data[b].gaji << endl;
            }
            break;
        }
        case 3:
        {

            cout << "Masukkan nama file yang akan diambil : ";
            cin >> ambil_file;
            ifstream karyawan(ambil_file.c_str(), ifstream::out);
            while (!karyawan.eof())
            {
                karyawan >> data[i].no;
                karyawan.ignore();
                karyawan.getline(data[i].nama, 50);
                karyawan.getline(data[i].alamat, 40);
                karyawan >> data[i].umur;
                karyawan >> data[i].gaji;
                sisipnode(data[i]);
                enqueue(data[i]);
                push(data[i]);
                i++;
            }
            karyawan.close();
            cout<<"\nBerhasil";
            break;
        }

        case 4:
            bacamaju();
            break;

        case 5:
            cetakqueue();
            break;

        case 6:
            dequeue();
            break;

        case 7:
        
			pop();
            break;
        case 8:
			karyawan();
            break;
        case 9:
            exit(0);
            break;
        }
        do
        {
            cout << "\nIngin kembali ke menu?y/n : ";
            cin >> ulang;
        } while ((ulang != "y" && ulang != "Y") && (ulang != "n" && ulang != "N"));
    } while (ulang == "y" || ulang == "Y");
}

void buatlistbaru()
{
    typeptr list;
    list = NULL;
    awal = list;
    akhir = list;
}

int listkosong()
{
    if (awal == NULL)
        return 1;
    else
        return 0;
}

void sisipnode(isi_data IB)
{
    typeptr NB, bantu;
    NB = (typenode *)malloc(sizeof(typenode));
    NB->info = IB;
    NB->next = NULL;
    if (listkosong())
    {
        awal = NB;
        akhir = NB;
    }
    else if (IB.no <= awal->info.no)
    {
        NB->next = awal;
        awal = NB;
    }
    else
    {
        bantu = awal;
        while (bantu->next != NULL && (IB.no > bantu->next->info.no))
            bantu = bantu->next;
        NB->next = bantu->next;
        bantu->next = NB;
        if (IB.no > akhir->info.no)
            akhir = NB;
    }
}

void bacamaju()
{
    typeptr bantu;
    bantu = awal;

    while (bantu != NULL)
    {
		if (bantu->info.no!=0)
		{
			cout << "ID       : " << bantu->info.no << endl;
        cout << "Nama     : " << bantu->info.nama << endl;
        cout << "Alamat   : " << bantu->info.alamat << endl;
        cout << "Umur     : " << bantu->info.umur << endl;
        cout << "Gaji     : " << bantu->info.gaji << endl;

        cout << endl;
		}
		        bantu = bantu->next;
        
    }
}

//Queue
void buatqueue()
{
    qdepan = (typenode *)malloc(sizeof(typenode));
    qdepan = NULL;
    qbelakang = qdepan;
}

int queuekosong()
{
    if (qdepan == NULL)
        return 1;
    else
        return 0;
}

void enqueue(isi_data IB)
{
    typeptr NB;
    NB = (typenode *)malloc(sizeof(typenode));
    NB->info = IB;
    if (qdepan == NULL)
        qdepan = NB;
    else
        qbelakang->next = NB;
    qbelakang = NB;
    qbelakang->next = NULL;
}

void dequeue()
{
    typeptr hapus;
    if (queuekosong())
    {
        cout << "Queue masih kosong !";
    }
    else
    {
        hapus = qdepan;
        qdepan = hapus->next;
        free(hapus);
    }
    cout << "Gaji sudah diberikan";
}

void cetakqueue()
{
    typeptr bantu;
    bantu = qdepan;
    cout<<"Antrian Gaji Keluar\n";
    do
    {
		if (bantu->info.no!=0)
		{
			 cout << "Gaji  ID "<<bantu->info.no<<" : " << bantu->info.gaji << endl;
        cout << endl;
		}
       
        bantu = bantu->next;
    } while (bantu != NULL);
}

//stack
void buatstack()
{
    typeptr1 NS;
    NS = (typestack *)malloc(sizeof(typestack));
    NS = NULL;
    stackawal = NS;
}
void push(isi_data IB)
{

    typeptr1 NS;
    NS = (typestack *)malloc(sizeof(typestack));
    NS->info1 = IB;
    if (stackawal == NULL)
        stackawal = NS;
    else
        stack->next1 = NS;
    stack = NS;
    stack->next1 = NULL;
}
void cetakstack()
{
    typeptr1 bantu;
    bantu = stackawal;
    cout << "Urutan Senioritas\n";
    while (bantu != NULL)
    {
		if (bantu->info1.no!=0)
		{
		 cout << "ID       : " << bantu->info1.no << endl;
        cout << "Nama     : " << bantu->info1.nama << endl;
        cout << "Alamat   : " << bantu->info1.alamat << endl;
        cout << "Umur     : " << bantu->info1.umur << endl;
        cout << "Gaji     : " << bantu->info1.gaji << endl;
        cout << endl;
		}
       
        bantu = bantu->next1;
    }
}
void pop()
{	
	
    typeptr1 hapus, bantu;
    bantu = stackawal;
    hapus = stack;
    if (hapus == stackawal)
    {
        stackawal = NULL;
    }
    else
    {
        while (bantu->next1->next1 != NULL)
            bantu = bantu->next1;
        stack = bantu;
        stack->next1 = NULL;
    };
    free(hapus);
    cout<<"Satu kontrak habis";
}
void karyawan(){
	int i=1;
	ifstream karyawan(ambil_file.c_str(), ifstream::out);
            while (!karyawan.eof())
            {
                karyawan >> data[i].no;
                karyawan.ignore();
                karyawan.getline(data[i].nama, 50);
                karyawan.getline(data[i].alamat, 40);
                karyawan >> data[i].umur;
                karyawan >> data[i].gaji;
            if (data[i].no!=0)
			{
				  cout << "ID       : " << data[i].no << endl;
        cout << "Nama     : " << data[i].nama << endl;
        cout << "Alamat   : " << data[i].alamat << endl;
        cout << "Umur     : " << data[i].umur << endl;
        cout << "Gaji     : " <<data[i].gaji << endl;
        cout << endl;
			}
              
            i++;
            }
            
            karyawan.close();
	
}

