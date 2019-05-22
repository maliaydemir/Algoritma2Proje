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
	
	//d�zenli bir g�r�n�m verilecek
	setlocale(LC_ALL,"");
	char u[2];
	while(true){
		system("cls");
		uyeListele();
		cout<<endl<<"G�ncellemek ��in Bir Tu�a Bas�n";
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
	//gelen uye idsine g�re kitaplar listesinden o uyeye ait kitaplar� yazd�r
	//2 3 tab bo�luklu
	for(int i=0;i<kitaplar.size();i++){
		if(kitaplar.at(i).getOwner()==id){
			cout<<"      >>> "<<kitaplar.at(i)._getId()<<"-"<<kitaplar.at(i).getName()<<endl;
		}
	}
}
