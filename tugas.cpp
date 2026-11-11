#include<iostream>
#include<vector>
#include<string>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
    private:
        vector <pair<int, string>> table;
        vector <int> status; // 0: EMPTY, 1: FILLED, 2: DELETED

        int hash1 (int key) {
            return key % TABLE_SIZE;
        }
        
        // bilangan prima terdekat (lebih kecil) dari ukuran table
        int hash2 (int key) {
            return 7 - (key % 7);
        }

    public:
        HashTable() {
            table.resize(TABLE_SIZE);
            status.resize(TABLE_SIZE, 0);
        }

        void insert (int key, string value) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            int deletedIndex = -1;

            while (true) {
                if (status[index] == 1 && table[index].first == key) {
                    table[index].second = value;
                    return;
                }

                if (status[index] == 2 && deletedIndex == -1) {
                    deletedIndex = index;
                }

                if (status[index] == 0) {
                    if (deletedIndex != -1) {
                        index = deletedIndex;
                    }

                    table[index] = make_pair(key, value);
                    status[index] = 1;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            if (deletedIndex != -1) {
                table[deletedIndex] = make_pair(key, value);
                status[deletedIndex] = 1;
            } else {
                cout << "Table penuh" << endl;
            }
        }

        void search(int key) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            while (status[index] != 0) {
                if (status[index] == 1 && table[index].first == key) {
                    cout << "Data ditemukan : NIM " << table[index].first << " - " << table[index].second << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Data dengan NIM " << key << " tidak ditemukan" << endl;
        }

        void remove (int key) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            while (status[index] != 0) {
                if (status[index] == 1 && table[index].first == key) {
                    status[index] = 2;
                    cout << "Data dengan NIM " << key << " berhasil dihapus" << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Data dengan NIM " << key << " tidak ditemukan" << endl;
        }

        void display() {
            for (int i = 0; i < TABLE_SIZE; i++) {
                cout << i << " : ";
            
                if (status[i] == 1) {
                    cout << table[i].first << " - " << table[i].second;
                } else if (status[i] == 2) {
                    cout << "DELETED";
                } else {
                    cout << "EMPTY";
                }

                cout << endl;
            }
        }
};

int main() {
    HashTable ht;

    // Memasukkan data mahasiswa (NIM sebagai key, Nama sebagai value)
    ht.insert(101, "Andi");
    ht.insert(205, "Budi");
    ht.insert(311, "Citra");
    ht.insert(415, "Dewi");

    cout << "Isi Hash Table awal : " << endl;
    ht.display();
    cout << endl;

    cout << "Mencari data mahasiswa NIM 205 : " << endl;
    ht.search(205);
    cout << endl;

    cout << "Menghapus data mahasiswa NIM 205 : " << endl;
    ht.remove(205);
    cout << endl;

    cout << "Hash Table setelah penghapusan : " << endl;
    ht.display();

    return 0;
}