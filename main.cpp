#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include "helpers.h"
#include <cmath>
#include <locale.h>
#include <typeinfo>
using namespace std;

//UYE SÝLÝNÝRKEN SAHÝP OLDUÐU KÝTAPLARI VARSA EKSTRA KONTROL EDÝP BÝLGÝLENDÝRME YAPILACAK
//UYE SÝLÝNÝRSE KÝTAPLARIN DURUMU 0 YAPILACAK 

//yýkýcý fonksiyonu wait() fonksiyonuyla braber kullan

vector<Kitap> kitaplar;
vector<Uye> uyeler;
void kitapTeslim();

//kitap ve uye iþlem classlarý
class kitapEkleAraListele{
	public: 
	void ekle(){
		string stat="";
	do{		
		Kitap k;
		cout<<"Kitap Adý: ";
		k.setName(input());
		cout<<"Kitap Yazarýnýn Adý Soyadý: ";
		k.setWriter(input());
		kitaplar.push_back(k);
		//kitap id oluþturulamýyor
		//kitaplar.at(kitaplar.size()-1).setId(kitaplar.size());
		if(kitaplar.size()==1){
			kitaplar.at(kitaplar.size()-1).setId(1);
		}else{
			kitaplar.at(kitaplar.size()-1).setId(kitaplar.at(kitaplar.size()-2).getId()+1);
		}
		kitaplar.at(kitaplar.size()-1).add();
		//cout<<kitaplar.at(kitaplar.size()-1).getName()<<"-*-"<<endl;
		
		cout<<"Eklemeye Devam Etmek Ýçin (E): ";
		stat=input();		
		}while(stat=="E"||stat=="e");
	
	}
	void listele(){
	kitaplar.clear();
	getKitaplar(&kitaplar);
	for(int i=0;i<kitaplar.size();i++){
		//cout<<kitaplar.at(i).getFull()<<endl;
		Goruntule(kitaplar.at(i));
		if((i+1)!=kitaplar.size()){
		cout<<"-----------------------------------------------------"<<endl;
		}
	}
	wait();
	}
	void ara(){
		string key;
		cout<<"ARA: ";
		key=input();
		if(key.length()!=0){
		
		cout<<"----Bulunan Kitaplar----"<<endl;
		for(int i=0;i<kitaplar.size();i++){
		string name=toLower(kitaplar.at(i).getName());
		key=toLower(key);
	
		bool stat=false;
		for(int j=0;j<name.length();j++){
			if((name.substr(j,key.length()))==key&&!kitaplar.at(i).getDeleted()){
				Goruntule(kitaplar.at(i));
				cout<<"----------------------------------"<<endl;
				stat=true;
				break;
			}
		}
		if(!stat){
			name=kitaplar.at(i).getWriter();
			for(int j=0;j<name.length();j++){
			if((name.substr(j,key.length()))==key){
				Goruntule(kitaplar.at(i));
				cout<<"----------------------------------"<<endl;
				break;
			}
			}
		}
		
	}

	}else{
		cout<<"Yanlýþ Giriþ Yaptýnýz.."<<endl;
	}
	wait();
	}
};
class kitapSilGuncelle{
	public:
	void sil(){
		srand (time(NULL));
	int id,i;
	bool stat=false;
	cout<<"Silmek Ýstediðiniz Kitap Kodu: ";
	cin>>id;
	cin.ignore();
	for(i=0;i<kitaplar.size();i++){
		if(kitaplar.at(i).getId()==id){
			stat=true;
			break;
		}
	}
	if(stat){
		if(kitaplar.at(i).getConstant()){
			cout<<"BU KÝTAP DEMÝRBAÞ LÝSTESÝNDEDÝR ENVANTERDEN ÇIKARILAMAZ"<<endl;
		}
		else{
			cout<<"Bu Kitapý Envanterden Silmek Ýstediðinize Emin Misiniz?"<<endl;
			int gkod=rand() % 8999 + 1000;
			cout<<"DOÐRULAMA ÝÇÝN GÜVENLÝK KODUNU GÝRÝNÝZ ("<<gkod<<"): ";
			int kod;
			cin>>kod;
			cin.ignore();
			if(gkod==kod){
				//silme iþlemini yap
				kitaplar.at(i).setDeleted(true);
				Yaz(&kitaplar);
				getKitaplar(&kitaplar);
				cout<<"Silme Ýþlemi Tamamlandý"<<endl;
			}
		}
	}else{
		cout<<"Bu Koda Ait Kitap Bulunamadý"<<endl;
	}
	wait();
	
	
	}
	void guncelle(){
		int id,indis=-1;
	cout<<"Güncellemek Ýstediðiniz Kitap Kodu: ";
	cin>>id;
	cin.ignore();
/*
	for(int i=0;i<kitaplar.size();i++){
		if(kitaplar.at(i).getId()==id){
			indis=i;
		}
	}
*/
	indis=getKitap(&kitaplar,id);
	
	if(indis!=-1){
		Goruntule(kitaplar.at(indis));
		string tmp;
		int tmp1;
		cout<<"**GÜNCELLENMEYECEK OLAN DEÐERLERÝ BOÞ GÝRÝNÝZ ***"<<endl;
		cout<<"Yeni Kitap Adý:";
		tmp=input();
		if(tmp!=""){
			kitaplar.at(indis).setName(tmp);
		}
		cout<<"Yeni Kitap Yazarý:";
		tmp="";
		tmp=input();
		if(tmp!=""){
			kitaplar.at(indis).setWriter(tmp);
		}
		cout<<"Kitabýn Demirbaþ Durumu(1/0):";
		tmp="";
		tmp=input();
		if(tmp!=""){
			if(tmp=="1"){
			kitaplar.at(indis).setConstant(true);
			}
			else if(tmp=="0"){
			kitaplar.at(indis).setConstant(false);
			}
		}
		
		Yaz(&kitaplar);
		
	}else{
		cout<<"Bu Koda Ait Kitap Bulunamadý.";
	}
	wait();
	
	}
};
class islemKitap:public kitapEkleAraListele,public kitapSilGuncelle{
	public:
	islemKitap(){
		//iþlem menüsü	
		cout<<"***Kategori Deðiþtirmek Ýçin Ýþlem Seçiminde (x) Giriþi Yapýn***"<<endl;
		cout<<"-----------------------"<<endl;
		cout<<"|"<<"    Kitap Ekleme: "<<" E"<<" |"<<endl;
		cout<<"|"<<"Kitap Güncelleme: "<<" G"<<" |"<<endl;
		cout<<"|"<<" Kitap Listeleme: "<<" L"<<" |"<<endl;
		cout<<"|"<<"     Kitap Arama: "<<" A"<<" |"<<endl;
		cout<<"|"<<"     Kitap Silme: "<<" S"<<" |"<<endl;
		cout<<"|"<<"    Kitap Teslim: "<<" T"<<" |"<<endl;
		cout<<"-----------------------"<<endl;
	}
	~islemKitap(){
		system("cls");
	}	
	
	void kitapTeslim(){
	
	string tmp;
	cout<<"Kitap Kodu: ";
	tmp=input();
	
	int kitapId=getKitap(&kitaplar,toInteger(tmp));
		//cout<<kitaplar.size()<<endl;
	if(kitapId!=-1&&(!kitaplar.at(kitapId).getConstant())&&kitaplar.at(kitapId).getOwner()==0){

		cout<<"Teslim Alacak Üye Kodu: ";
		tmp=input();
		
		int uyeId=getUye(&uyeler,toInteger(tmp));
		if(uyeId!=-1){
			srand (time(NULL));
			int gkod=rand() % 8999 + 1000;
			cout<<"Teslim Ýþlemini Onaylayýn..Güvenlik Kodunu Giriniz: ("<<gkod<<"): ";
			
			tmp=input();
			if(gkod==toInteger(tmp)){
				//teslim iþlemini yap
				kitaplar.at(kitapId).setOwner(uyeler.at(uyeId).getId());
				Yaz(&kitaplar);
				cout<<"Kitap Teslimi Onaylandý.."<<endl;
				
			}else{
				cout<<"Güvenlik Kodunu Yanlýþ Girdiniz.."<<endl;
			}
		}else{
			cout<<"Bu Koda Ait Üye Bulunamadý.."<<endl;
		}
	}else if(kitapId!=-1&&kitaplar.at(kitapId).getOwner()!=0){
		//kitabý uyeden geri alma iþlemi
		int uyeId=getUye(&uyeler,kitaplar.at(kitapId).getOwner());
		cout<<kitaplar.at(kitapId).getName()<<" kitabýný "<<uyeler.at(uyeId).getName()<<" adlý üyeden saðlam þekilde geri alýndýðýný onaylayýnýz.."<<endl;
		int gkod=rand()%8999+1000;
		cout<<"GÜVENLÝK KODUNU GÝRÝNÝZ ("<<gkod<<"): ";
		tmp=input();
		if(gkod==toInteger(tmp)){
			kitaplar.at(kitapId).setOwner(0);
			Yaz(&kitaplar);
			cout<<"Kitap Teslimi Onaylandý..";
		}else{
			cout<<"GÜVENLÝK KODUNU YANLIÞ GÝRDÝNÝZ..";
		}
	}
	else{
		cout<<"Bu Koda Ait Kitap Bulunamadý veya Bu Kitap Teslim Edilemez.."<<endl;
	}
	wait();
}
};

class uyeEkleAraListele{
	public:
	void ekle(){
		string stat="";
	do{		
		Uye u;
		cout<<"Üye Adý: ";
		stat=input();
		cout<<"Üye Soyadý: ";
		u.setName(stat,input());
		do{
		cout<<"Uye Telefonu (05XX XXX XX XX): ";
		u.setPhone(input());
		//phoneCheck fonksiyonu oluþtur
		if(u.getPhone().length()<11){
			cout<<"11 haneli telefon numarasý giriniz"<<endl;
		}
		}while(u.getPhone().length()<11);
		uyeler.push_back(u);
		//kitap id oluþturulamýyor
		//kitaplar.at(kitaplar.size()-1).setId(kitaplar.size());
		if(uyeler.size()==1){
			uyeler.at(uyeler.size()-1).setId(1);
		}else{
			uyeler.at(uyeler.size()-1).setId(uyeler.at(uyeler.size()-2).getId()+1);
		}
			uyeler.at(uyeler.size()-1).add();
		//cout<<kitaplar.at(kitaplar.size()-1).getName()<<"-*-"<<endl;
		
		cout<<"Eklemey Devam Etmek Ýçin (E): ";
		stat=input();		
	}while(stat=="E"||stat=="e");
	
	//uyeYaz(&uyeler);
	}
	void listele(){
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
	wait();
	}
	void ara(){
		string key;
	cout<<"ARA: ";
	key=input();
	if(key.length()!=0){
	cout<<"----Bulunan Uyeler----"<<endl;
	for(int i=0;i<uyeler.size();i++){
		string name=toLower(uyeler.at(i).getName());
		key=toLower(key);
		bool stat=false;
		for(int j=0;j<name.length();j++){
			if((name.substr(j,key.length()))==key&&!uyeler.at(i).getDeleted()){
				Goruntule(uyeler.at(i));
				cout<<"---------------------------------------"<<endl;
				break;
			}
		}
	}
	}else{
		cout<<"Yanlýþ Giriþ Yaptýnýz.."<<endl;
	}
	wait();
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
};
class uyeSilGuncelle{
	public:
	void sil(){
		srand (time(NULL));
	int id,i;
	bool stat=false;
	cout<<"Silmek Ýstediðiniz Üye Kodu: ";
	cin>>id;
	cin.ignore();
	i=getUye(&uyeler,id);
	if(i!=-1){
		cout<<"Bu Üyeyi Silmek Ýstediðinize Emin Misiniz?"<<endl;
		int gkod=rand() % 8999 + 1000;
		cout<<"DOÐRULAMA ÝÇÝN GÜVENLÝK KODUNU GÝRÝNÝZ ("<<gkod<<"): ";
		int kod;
		cin>>kod;
		cin.ignore();
		if(gkod==kod){
			//Sahip Olduðu kitaplarýn durumuna bak
			vector<int> uKitaplar=getUyeKitap(&kitaplar,id);
			if(uKitaplar.size()>0){
				cout<<"Silmek istediðiniz üyenin teslim etmesi gereken kitaplarý teslim aldýðýnýzý onaylamak için bir tuþa basýnýz.."<<endl;
				getche();
				for(int j=0;j<uKitaplar.size();j++){
					kitaplar.at(uKitaplar.at(j)).setOwner(0);
				}
				Yaz(&kitaplar);
				getKitaplar(&kitaplar);
			}
						
			//silme iþlemini yap
			uyeler.at(i).setDeleted(true);
			Yaz(&uyeler);
			getUyeler(&uyeler);//tedbir ve döngülerin eksiksiz dönmesi için tekrar resetledim dizileri
			cout<<"Silme Ýþlemi Tamamlandý.."<<endl;
			
		}	
	}else{
		cout<<"Bu Koda Ait Üye Bulunamadý"<<endl;
	}
	wait();
	}
	void guncelle(){
		int id,indis=-1;
	cout<<"Güncellemek Ýstediðiniz Uye Kodu: ";
	cin>>id;
	cin.ignore();

	indis=getUye(&uyeler,id);
	
	if(indis!=-1){
		Goruntule(uyeler.at(indis));
		string tmp;
		int tmp1;
		cout<<"**GÜNCELLENMEYECEK OLAN DEÐERLERÝ BOÞ GÝRÝNÝZ ***"<<endl;
		cout<<"Yeni Uye Adý Soyadý:";
		tmp=input();
		if(tmp!=""){
			uyeler.at(indis).setName(tmp,"");
		}
		cout<<"Yeni Uye Telefonu:";
		tmp="";
		tmp=input();
		if(tmp!=""){
			uyeler.at(indis).setPhone(tmp);
		}
		Yaz(&uyeler);
		
	}else{
		cout<<"Bu Koda Ait Uye Bulunamadý.";
	}	
	wait();
	
	}
};
class islemUye:public uyeEkleAraListele, public uyeSilGuncelle{
	public:
	islemUye(){
	cout<<"***Kategori Deðiþtirmek Ýçin Ýþlem Seçiminde (x) Giriþi Yapýn***"<<endl;
	cout<<"-----------------------"<<endl;
	cout<<"|"<<"    Uye Ekleme: "<<" E"<<" |"<<endl;
	cout<<"|"<<"Uye Güncelleme: "<<" G"<<" |"<<endl;
	cout<<"|"<<" Uye Listeleme: "<<" L"<<" |"<<endl;
	cout<<"|"<<"     Uye Arama: "<<" A"<<" |"<<endl;
	cout<<"|"<<"     Uye Silme: "<<" S"<<" |"<<endl;
	cout<<"-----------------------"<<endl;
	}
	~islemUye(){
		system("cls");
	}
};


int main(){
	//üye kitap teslimi tamam geri teslim alme ve uye listesinde listeleme yapýlacak	
	
	getKitaplar(&kitaplar);
	getUyeler(&uyeler);
	
	
	/* deðiþken tipi bulma
	Kitap aa;
	cout<<typeid(aa).name();
	return 0;
	*/
	
	char menu[10];
	char t,m;
	while(true){
		setlocale(LC_ALL, "Turkish"); 
		cout<<"Ýþlem Kategorisi Seçin (Ü/K): ";
		cin>>t;
		cin.ignore();
		if(t==-102||t==-127||t=='u'||t=='U'){
			t='ü';
		}else if(t=='k'||t=='K'){
			t='k';
		}		
	
	
	while(t=='ü'){
		islemUye iu;
		cout<<"Ýþlem Seçin:  ";
		gets(menu);
		strlwr(menu);
		if(strlen(menu)==1){
			m=menu[0];
		}else{
			m='.';
		}
		switch(m){
			case 'e':
				iu.ekle();
				break;
			case 's':
				iu.sil();
				break;
			case 'l':
				iu.listele();
				break;
			case 'g':
				iu.guncelle();
				break;
			case 'a':
				iu.ara();
				break;
			case 'x':
				system("cls");
				t='.';
				break;
			default:
			cout<<"Yanlýþ Giriþ Yaptýnýz."<<endl;
			wait();
			break;
		}		
	}
	while(t=='k'){
		islemKitap ik;
		cout<<"Ýþlem Seçin: ";
		gets(menu);
		strlwr(menu);
		if(strlen(menu)==1){
			m=menu[0];
		}else{
			m='.';
		}
	switch(m){
		case 'e':
			ik.ekle();
			//cout<<kitaplar.at(kitaplar.size()-1).getFull()<<endl;
			break;
		case 's':
			ik.sil();
			break;
		case 'l':
			ik.listele();
			break;
		case 'g':
			ik.guncelle();
			break;
		case 'a':
			ik.ara();
			break;
		case 't':
			ik.kitapTeslim();//islemKitap classýndaki kitapTeslim fonksiyonunu dýþarý alýp dene hata verirse
			break;
			
		case 'x':
			system("cls");
			t='.';
			break;
		default:
			cout<<"Yanlýþ Giriþ Yaptýnýz."<<endl;
			wait();
			break;
	}
	getKitaplar(&kitaplar);
	
  }
	}
	cout<<"döngüden çýktýnýz";
	return 0;
}




