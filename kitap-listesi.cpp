#include <iostream>
#include <conio.h> 
#include "helpers.h"
#include <locale.h>
using namespace std;
void kitapListele();
vector<Kitap> kitaplar;
int main(){
	//düzenli bir görünüm verilecek
	setlocale(LC_ALL,"");
	char u[2];
	while(true){
		system("cls");
		kitapListele();
		cout<<endl<<"Güncellemek Ýçin Bir Tuþa Basýn";
		getche();
	}
}	

void kitapListele(){
	kitaplar.clear();
	getKitaplar(&kitaplar);
	for(int i=0;i<kitaplar.size();i++){
		//cout<<kitaplar.at(i).getFull()<<endl;
		Goruntule(kitaplar.at(i));
		if((i+1)!=kitaplar.size()){
		cout<<"-----------------------------------------------------"<<endl;
		}
	}
}
