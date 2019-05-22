#include <iostream>
#include <conio.h> 
#include "helpers.h"
#include <locale.h>
using namespace std;
void uyeListele();
void yazUyeKitap(int id);
vector<Uye> uyeler;
vector<Kitap> kitaplar;
int main(){
	
	//düzenli bir görünüm verilecek
	setlocale(LC_ALL,"");
	char u[2];
	while(true){
		system("cls");
		uyeListele();
		cout<<endl<<"Güncellemek Ýçin Bir Tuþa Basýn";
		getche();
	}
}	

void uyeListele(){
	uyeler.clear();
	getUyeler(&uyeler);
	getKitaplar(&kitaplar);
	for(int i=0;i<uyeler.size();i++){
		//cout<<uyeler.at(i).getFull()<<endl;		
		Goruntule(uyeler.at(i));
		yazUyeKitap(uyeler.at(i).getId());
		if(i<uyeler.size()-1){
			cout<<"----------------------------------------"<<endl;
		}
	}
}
void yazUyeKitap(int id){
	//gelen uye idsine göre kitaplar listesinden o uyeye ait kitaplarý yazdýr
	//2 3 tab boþluklu
	for(int i=0;i<kitaplar.size();i++){
		if(kitaplar.at(i).getOwner()==id){
			cout<<"      >>> "<<kitaplar.at(i)._getId()<<"-"<<kitaplar.at(i).getName()<<endl;
		}
	}
}
