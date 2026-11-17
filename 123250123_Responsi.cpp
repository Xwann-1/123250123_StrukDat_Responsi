// NAMA = Prajawan Ainur Rahmat
// NIM = 123250123

#include <iostream>
using namespace std;

struct nodeQueue
{
    int energi;
    string nama;
    nodeQueue *next;
};

struct nodeStack
{
    int energi;
    string nama;
    nodeStack *next;
};

struct nodeTree
{
    int energi;
    string nama;
    nodeTree *kiri;
    nodeTree *kanan;
};

nodeQueue *front = nullptr;
nodeQueue *last = nullptr;
nodeStack *top = nullptr;
nodeTree *root = nullptr;

void tampilkanMenu()
{
    cout << "=============================" << endl;
    cout << "| Sistem Organ Inti Nirwana |" << endl;
    cout << "=============================" << endl;
    cout << "1. Tambah Energi" << endl;
    cout << "2. Lihat Energi dalam Antrean" << endl;
    cout << "3. Proses Energi" << endl;
    cout << "4. Lihat Energi yang sudah terserap" << endl;
    cout << "5. Hapus Riwayat Energi Teratas" << endl;
    cout << "6. Cari Energi di Organ" << endl;
    cout << "7. Lihat Isi Organ" << endl;
    cout << "8. Gunakan Energi" << endl;
    cout << "9. Keluar" << endl;
    cout << "Masukkan pilihan Anda : ";
}

nodeTree *tambah_tree(nodeTree *akar, int energi, string nama)
{
    if (akar == nullptr)
    {
        return new nodeTree{energi, nama, nullptr, nullptr};
    }

    if (energi < akar->energi)
    {
        akar->kiri = tambah_tree(akar->kiri, energi, nama);
    }
    else
    {
        akar->kanan = tambah_tree(akar->kanan, energi, nama);
    }

    return akar;
}

nodeTree *cari_tree(nodeTree *akar, int energi)
{
    if (akar == nullptr || akar->energi == energi)
    {
        return akar;
    }
    if (energi < akar->energi)
    {
        return cari_tree(akar->kiri, energi);
    }
    return cari_tree(akar->kanan, energi);
}

nodeTree *hapus_tree(nodeTree *akar, int energi)
{
    if (akar == nullptr)
    {
        return nullptr;
    }
    if (energi < akar->energi)
    {
        akar->kiri = hapus_tree(akar->kiri, energi);
    }
    else if (energi > akar->energi)
    {
        akar->kanan = hapus_tree(akar->kanan, energi);
    }
    else if (akar->kiri == nullptr)
    {
        nodeTree *sisa = akar->kanan;
        delete akar;
        return sisa;
    }
    else if (akar->kanan == nullptr)
    {
        nodeTree *sisa = akar->kiri;
        delete akar;
        return sisa;
    }
    else
    {
        nodeTree *pengganti = akar->kanan;
        while (pengganti->kiri != nullptr)
        {
            pengganti = pengganti->kiri;
        }
        akar->energi = pengganti->energi;
        akar->nama = pengganti->nama;
        akar->kanan = hapus_tree(akar->kanan, pengganti->energi);
    }

    return akar;
}

void preorder(nodeTree *akar, int &no)
{
    if (akar == nullptr)
    {
        return;
    }

    cout << no << ". [" << akar->energi << "] " << akar->nama << endl;
    no++;
    preorder(akar->kiri, no);
    preorder(akar->kanan, no);
}

void inorder(nodeTree *akar, int &no)
{
    if (akar == nullptr)
    {
        return;
    }

    inorder(akar->kiri, no);
    cout << no << ". [" << akar->energi << "] " << akar->nama << endl;
    no++;
    inorder(akar->kanan, no);
}

void postorder(nodeTree *akar, int &no)
{
    if (akar == nullptr)
    {
        return;
    }

    postorder(akar->kiri, no);
    postorder(akar->kanan, no);
    cout << no << ". [" << akar->energi << "] " << akar->nama << endl;
    no++;
}

void tambah_energi()
{
    int energi;
    string nama;
    cout << "Masukkan kode energi : ";
    cin >> energi;
    if (cin.fail() || energi <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus berupa angka lebih dari 0!" << endl
             << endl;
        return;
    }

    nodeQueue *q = front;
    while (q != nullptr)
    {
        if (q->energi == energi)
        {
            cout << "Kode energi sudah digunakan!" << endl
                 << endl;
            return;
        }
        q = q->next;
    }

    nodeStack *s = top;
    while (s != nullptr)
    {
        if (s->energi == energi)
        {
            cout << "Kode energi sudah digunakan!" << endl
                 << endl;
            return;
        }
        s = s->next;
    }

    cout << "Masukkan nama energi : ";
    cin.ignore();
    getline(cin, nama);
    if (nama.empty())
    {
        cout << "Nama energi tidak boleh kosong!" << endl
             << endl;
        return;
    }

    nodeQueue *nb = new nodeQueue{energi, nama, nullptr};
    if (front == nullptr)
    {
        front = last = nb;
    }
    else
    {
        last->next = nb;
        last = nb;
    }
    cout << "Berhasil memasukkan energi!" << endl
         << endl;
}

void lihat_antrean()
{
    if (front == nullptr)
    {
        cout << "Energi masih kosong!" << endl
             << endl;
        return;
    }

    cout << "=== Energi Dalam Antrean ===" << endl
         << endl;
    nodeQueue *nb = front;
    int no = 1;

    while (nb != nullptr)
    {
        cout << no << ". [" << nb->energi << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

void proses_energi()
{
    if (front == nullptr)
    {
        cout << "Energi masih kosong!" << endl
             << endl;
        return;
    }

    nodeQueue *hapus = front;
    nodeStack *nb = new nodeStack{hapus->energi, hapus->nama, top};
    top = nb;
    root = tambah_tree(root, hapus->energi, hapus->nama);
    cout << "Berhasil Memproses energi " << hapus->nama << "!" << endl
         << endl;
    front = hapus->next;
    if (front == nullptr)
    {
        last = nullptr;
    }
    delete hapus;
}

void lihat_riwayat()
{
    if (top == nullptr)
    {
        cout << "Belum ada energi yang terserap!" << endl
             << endl;
        return;
    }

    cout << "=== Energi yang sudah terserap ===" << endl
         << endl;
    nodeStack *nb = top;
    int no = 1;
    while (nb != nullptr)
    {
        cout << no << ". [" << nb->energi << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

void cari_energi()
{
    if (root == nullptr)
    {
        cout << "Energi masih kosong!" << endl
             << endl;
        return;
    }
    int energi;
    cout << "Masukkan kode energi: ";
    cin >> energi;
    if (cin.fail() || energi <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus berupa angka lebih dari 0!" << endl
             << endl;
        return;
    }
    nodeTree *hasil = cari_tree(root, energi);
    if (hasil == nullptr)
    {
        cout << "Energi dengan kode " << energi << " tidak ada di daftar!" << endl
             << endl;
        return;
    }
    cout << "Ditemukan: [" << hasil->energi << "] " << hasil->nama << endl
         << endl;
}

void lihat_daftar()
{
    if (root == nullptr)
    {
        cout << "Energi masih kosong!" << endl
             << endl;
        return;
    }
    char pilih;
    int no = 1;
    cout << "=== Daftar Isi Energi ===" << endl
         << endl;
    cout << "1. Pre-order" << endl;
    cout << "2. In-order" << endl;
    cout << "3. Pre-order" << endl
         << endl;
    cout << "Masukkan pilihan Anda: ";
    cin >> pilih;
    cout << endl;
    switch (pilih)
    {
    case '1':
    {
        preorder(root, no);
        break;
    }

    case '2':
    {
        inorder(root, no);
        break;
    }

    case '3':
    {
        postorder(root, no);
        break;
    }

    default:
    {
        cout << "Pilihan yang Anda masukkan tidak valid!" << endl;
        break;
    }
    }
    cout << endl;
}

void ambil_energi()
{
    if (root == nullptr)
    {
        cout << "Energi masih kosong!" << endl
             << endl;
        return;
    }
    int energi;
    cout << "Masukkan kode energi: ";
    cin >> energi;
    if (cin.fail() || energi <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus berupa angka lebih dari 0!" << endl
             << endl;
        return;
    }
    nodeTree *hasil = cari_tree(root, energi);
    if (hasil == nullptr)
    {
        cout << "Energi dengan kode " << energi << " tidak ada di daftar!" << endl
             << endl;
        return;
    }
    cout << "Energi " << hasil->nama << " telah terserap!" << endl
         << endl;
    root = hapus_tree(root, energi);
}

void hapus_riwayat()
{
    if (front == nullptr)
    {
        cout << "Energi masih kosong!" << endl
             << endl;
        return;
    }

    nodeQueue *hapus = front;
    nodeStack *nb = new nodeStack{hapus->energi, hapus->nama, top};
    top = nb;
    root = tambah_tree(root, hapus->energi, hapus->nama);
    cout << "Riwayat energi " << hapus->nama << " teratas telah dihapus!" << endl
         << endl;
    front = hapus->next;
    if (front == nullptr)
    {
        last = nullptr;
    }
    delete hapus;
}

int main()
{
    char pilih = '0';
    while (pilih != 9)
    {
        tampilkanMenu();
        cin >> pilih;
        switch (pilih)
        {
        case '1':
        {
            char pilih_tambah = 'y';
            while (pilih_tambah == 'y' || pilih_tambah == 'Y')
            {
                tambah_energi();
                cout << "Apakah Anda ingin menambahkan energi lagi? (y/n): ";
                cin >> pilih_tambah;
            }
            break;
        }
        case '2':
        {
            lihat_antrean();
            break;
        }
        case '3':
        {
            proses_energi();
            break;
        }
        case '4':
        {
            lihat_riwayat();
            break;
        }
        case '5':
        {
            hapus_riwayat();
            break;
        }
        case '6':
        {
            cari_energi();
            break;
        }
        case '7':
        {
            lihat_daftar();
            break;
        }
        case '8':
        {
            ambil_energi();
            break;
        }
        case '9':
        {
            cout << "[SUKSES] Anda telah keluar program, Terimakasih telah menggunakan layanan kami! ";
            exit(0);
        }
        default:
        {
            cout << "[ERROR] Pilihan yang Anda masukkan tidak valid!" << endl;
            cout << "Silakan coba lagi (Pilih angka 1-8) " << endl
                 << endl;
        }
        }
    }
}