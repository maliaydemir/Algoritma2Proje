#include <iostream>
#include <conio.h> 
#include "helpers.h"
#include <locale.h>
using namespace std;
void kitapListele();
vector<Kitap> kitaplar;
int main(){
	//d�zenli bir g�r�n�m verilecek
	setlocale(LC_ALL,"");
	char u[2];
	while(true){
		system("cls");
		kitapListele();
		cout<<endl<<"G�ncellemek ��in Bir Tu�a Bas�n";
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
