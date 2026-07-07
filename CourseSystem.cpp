#include <iostream>
#include <string>

using namespace std;

/*
 * Author: Ege Kilic
 * Date: July 2026
 * Description: A Custom Course System Automation with Generic Dynamic List Implementation.
 */

namespace CourseSystem{

class Student{
private:
string studentID;
string name;
string department;
int year;
double gpa;

public:
Student(){
studentID;
name;
department;
year = 1;
gpa = 0.0;
}

Student(string id, string n, string dept, int y, double g){
studentID=id;
name=n;
department=dept;
year=y;
gpa=g;
}

string getID() const{
return studentID;
}
string getName() const{
return name;
}
string getDept() const{
return department;
}
int getYear() const{
return year;
}
double getGPA() const{
return gpa;
}

void yazdir() const{
cout<<studentID<<"\t| "<<name<<"\t| "<<department<<"\t| "<<year<<"\t| "<<gpa<<endl;
}
};

template <typename T>
class DynamicList{
private:
T* dizi;
int kapasite;
int elemanSayisi;

void kapasiteArttir(){
kapasite=kapasite*2;
T* yeniDizi=new T[kapasite];

for(int i=0;i<elemanSayisi;i++){
yeniDizi[i]=dizi[i];
}

delete[] dizi;
dizi=yeniDizi;

cout<<"\n[SISTEM]: Kapasite doldu, yeni kapasite: "<<kapasite<<" oldu.\n";
}

public:
DynamicList(){
kapasite=5;
elemanSayisi=0;
dizi = new T[kapasite];
}

~DynamicList() {
delete[] dizi;
}

void ekle(const T& eleman){
if(elemanSayisi==kapasite){
kapasiteArttir();
}
dizi[elemanSayisi]=eleman;
elemanSayisi++;
}

T getEleman(int index)const{
if(index>=0 && index<elemanSayisi){
return dizi[index];
}
return T();
}

int getElemanSayisi() const{
return elemanSayisi;
}
};
}

using namespace CourseSystem;

void ogrenciEkleMenu(DynamicList<Student>& liste) {
string id, isim, bolum;
int sinif;
double gpa;

cin.ignore();
cout<<"\n--- Ogrenci Kayit Paneli ---\n";
cout<<"ID: ";
getline(cin, id);
cout<<"Ad Soyad: ";
getline(cin, isim);
cout<<"Bolum: ";
getline(cin, bolum);
cout<<"Sinif (1-4): ";
cin>>sinif;

while(true){
cout<<"GPA (0.0 - 4.0): ";
cin>>gpa;
if(gpa>=0.0 && gpa<=4.0){
break;
}
cout<<"Gecersiz GPA! Tekrar dene.\n";
}

Student yeniOgr(id, isim, bolum, sinif, gpa);
liste.ekle(yeniOgr);
cout<<"Ogrenci sisteme eklendi!\n";
}

void tumOgrencileriGoster(const DynamicList<Student>& liste){
if (liste.getElemanSayisi()==0){
cout<<"\nSistemde kayitli ogrenci bulunmamaktadir.\n";
return;
}

cout << "\n------------ OGRENCI LISTESI ------------\n";
cout << "ID\t| Isim\t| Bolum\t| Sinif\t| GPA\n";
cout << "--------------------------------------------\n";

for(int i=0; i<liste.getElemanSayisi();i++){
liste.getEleman(i).yazdir();
}
cout << "--------------------------------------------\n";
}

void ogrenciAra(const DynamicList<Student>& liste){
if(liste.getElemanSayisi()==0){
cout<<"\nSistemde ogrenci yok.\n";
return;
}

string arananID;
cin.ignore();
cout<<"\nAramak istediginiz Ogrenci ID'sini giriniz: ";
getline(cin, arananID);

bool bulundu=false;
for(int i=0;i<liste.getElemanSayisi();i++) {
if(liste.getEleman(i).getID()==arananID){
cout<<"\n[Ogrenci Bulundu]:\n";
cout<<"---------------------------------------------------\n";
liste.getEleman(i).yazdir();
cout<<"---------------------------------------------------\n";
bulundu=true;
break;
}
}

if(!bulundu){
cout<<"\nGirilen ID'ye ait bir ogrenci bulunamadi.\n";
}
}

void gosterKursIstatistikleri(const DynamicList<Student>& liste){
int toplamOgr=liste.getElemanSayisi();
if(toplamOgr == 0){
cout<<"\nIstatistik hesaplamak icin kayitli ogrenci yok.\n";
return;
}

double toplamGpa=0.0;
Student enYuksek=liste.getEleman(0);
Student enDusuk=liste.getEleman(0);

for(int i=0;i<toplamOgr;i++){
Student anlikOgr=liste.getEleman(i);
toplamGpa+=anlikOgr.getGPA();

if(anlikOgr.getGPA() > enYuksek.getGPA()){
enYuksek = anlikOgr;
}
if(anlikOgr.getGPA() < enDusuk.getGPA()){
enDusuk = anlikOgr;
}
}

double ortalama = toplamGpa / toplamOgr;

cout<<"\n----------- ISTATISTIKLER -----------\n";
cout<<"Kayitli Toplam Ogrenci Sayisi : "<<toplamOgr<<"\n";
cout<<"Sinifin GPA Ortalamasi : "<<ortalama<<"\n";
cout<<"-----------------------------------------------\n";
cout<<"En Yuksek GPA'li Ogrenci : "<<enYuksek.getName()<<" ("<<enYuksek.getGPA()<<")\n";
cout<<"En Dusuk GPA'li Ogrenci : "<<enDusuk.getName()<<" ("<<enDusuk.getGPA()<<")\n";
cout<<"-----------------------------------------------\n";
}

int main() {
DynamicList<Student> otomasyon;
int secim;

do{
cout << "\n--- OGRENCI KAYIT SISTEMI MENUSU ---\n";
cout << "1. Ogrenci Ekle\n";
cout << "2. Tum Ogrencileri Goster\n";
cout << "3. Ogrenci Ara\n";
cout << "4. Kurs Istatistiklerini Goster\n";
cout << "5. Cikis\n";
cout << "Seciminiz (1-5): ";
cin >> secim;

switch(secim){
case 1:
ogrenciEkleMenu(otomasyon);
break;
case 2:
tumOgrencileriGoster(otomasyon);
break;
case 3:
ogrenciAra(otomasyon);
break;
case 4:
gosterKursIstatistikleri(otomasyon);
break;
case 5:
cout<<"\nProgram kapatiliyor...\n";
break;
default:
cout<<"\nHatali secim! Lutfen tekrar deneyin.\n";
}
} while(secim != 5);

return 0;
}
