// 202802042 Data Structures �dev.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Dugum {
    int veri; //d���m�n say�sal de�eri
    Dugum* sonraki;//sonraki d���me i�aret�i
};
struct Kuyruk {
    Dugum* bas; //kuyru�unba��ndaki eleman�nadresini tutar
    Dugum* son;//kuyru�un sonundaki eleman�n adresini tutar
    void olustur(); //ba�lang�� i�in gereken tan�mlar� i�erir
    void kapat(); //program bitimindebellek iadesi yapar
    void ekle(int); //kuyru�a yeni veri ekler
    int cikar();//kuyruktan s�radaki eleman� ��kar�r
    bool bosMu();//kuyruk bo� mu kontrol eder
    int eleman;
    int elemanSayi();// kuyru�un eleman say�s�n� d�nd�r�r
};
void Kuyruk::olustur() {
    bas = NULL;
    son = NULL;
    eleman = 0;
}
void Kuyruk::kapat() {
    Dugum* ptr;
    while (bas) {
        ptr = bas;
        bas = bas->sonraki;
        eleman--;
        delete ptr;
    }
}
void Kuyruk::ekle(int deger) {
    Dugum* yeni = new Dugum;
    yeni->veri = deger;
    yeni->sonraki = NULL;
    if (bas == NULL) {
        bas = yeni;
        son = bas;
        eleman++;
    }
    else {
        son->sonraki = yeni;
        son = yeni;
        eleman++;
    }
}
int Kuyruk::cikar() {
    if (bas == NULL) {
        return -1;
    }
    else {
        Dugum* ust = bas;
        int temp = bas->veri;
        bas = bas->sonraki;
        delete ust;
        eleman--;
        return temp;
    }
}
bool Kuyruk::bosMu() {
    if (bas == NULL) {
        return true;
    }
    else
        return false;
}
int Kuyruk::elemanSayi() {
    return eleman;
}
struct Yigin {
    Kuyruk k1, k2;//y���n i�in kullan�lacak kuyruk de�i�kenleri
    void olustur(); //ba�lang�� i�in gereken tan�mlar� i�erir
    void kapat(); //program bitimindebellek iadesi yapar
    void ekle(int); //kuyru�a yeni veri ekler
    int cikar();//kuyruktan s�radaki eleman� ��kar�r
    bool bosMu();//kuyruk bo� mu kontrol eder
    int tepe();      //y���n�n tepesindeki eleman� okur
    void yazdir();  //y���nelemanlar�n� s�raylaekrana yazar
    int eleman;
    int elemanSayi();// y���n�n eleman say�s�n� d�nd�r�r.
};
void Yigin::olustur() {
    k1.olustur();
    k2.olustur();
}
void Yigin::kapat() {
    k1.kapat();
    k2.kapat();
    eleman = 0;
}
void Yigin::ekle(int deger) {
    while (!k1.bosMu()) {
        k2.ekle(k1.bas->veri);
        k1.cikar();
    }
    k1.ekle(deger);
    eleman++;
    while (!k2.bosMu()) {
        k1.ekle(k2.bas->veri);
        k2.cikar();
    }
}
int Yigin::cikar() {
    eleman--;
    return k1.cikar();
}
int Yigin::tepe() {
    if (k1.bosMu()) {
        return -1;
    }
    else {
        return k1.bas->veri;
    }
}
int Yigin::elemanSayi() {
    return eleman;
}
void Yigin::yazdir() {
    Kuyruk temp;
    temp = k1;
    while (!temp.bosMu()) {
        std::cout << temp.cikar() << " ";
    }
    std::cout << "\n";
}
bool Yigin::bosMu() {
    if (k1.bas == NULL) {
        return true;
    }
    else {
        return false;
    }
}
void yiginCikar(Yigin* s) {
    if (!s->bosMu()) {
        s->cikar();
        yiginCikar(s);
    }
    else {
        std::cout << "Yigin bos.";
        return;
    }
}
void siraliEkle(Yigin* s, int x) {
    if (s->bosMu() || x > s->tepe()) {
        s->ekle(x);
        return;
    }

    int temp = s->cikar();
    siraliEkle(s, x);

    s->ekle(temp);
}
int main()
{
    Yigin stack;
    stack.olustur();

    stack.ekle(3);
    stack.ekle(1);
    stack.ekle(7);
    stack.ekle(4);
    stack.ekle(8);
    std::cout << "Orijinal Yigin:\n";
    //stack.yazdir();

    std::cout << "\n---yiginCikar fonksiyon cagrisi\n";
    yiginCikar(&stack);

    siraliEkle(&stack, 3);
    siraliEkle(&stack, 1);
    siraliEkle(&stack, 7);
    siraliEkle(&stack, 4);
    siraliEkle(&stack, 8);
    std::cout << "\nSirali Yigin:\n";
    stack.yazdir();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
