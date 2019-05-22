#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include "helpers.h"
#include <cmath>
#include <locale.h>
#include <typeinfo>
using namespace std;

//UYE S�L�N�RKEN SAH�P OLDU�U K�TAPLARI VARSA EKSTRA KONTROL ED�P B�LG�LEND�RME YAPILACAK
//UYE S�L�N�RSE K�TAPLARIN DURUMU 0 YAPILACAK 

//y�k�c� fonksiyonu wait() fonksiyonuyla braber kullan

vector<Kitap> kitaplar;
vector<Uye> uyeler;
void kitapTeslim();

//kitap ve uye i�lem classlar�
class kitapEkleAraListele{
	public: 
	void ekle(){
		string stat="";
	do{		
		Kitap k;
		cout<<"Kitap Ad�: ";
		k.setName(input());
		cout<<"Kitap Yazar�n�n Ad� Soyad�: ";
		k.setWriter(input());
		kitaplar.push_back(k);
		//kitap id olu�turulam�yor
		//kitaplar.at(kitaplar.size()-1).setId(kitaplar.size());
		if(kitaplar.size()==1){
			kitaplar.at(kitaplar.size()-1).setId(1);
		}else{
			kitaplar.at(kitaplar.size()-1).setId(kitaplar.at(kitaplar.size()-2).getId()+1);
		}
		kitaplar.at(kitaplar.size()-1).add();
		//cout<<kitaplar.at(kitaplar.size()-1).getName()<<"-*-"<<endl;
		
		cout<<"Eklemeye Devam Etmek ��in (E): ";
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
		cout<<"Yanl�� Giri� Yapt�n�z.."<<endl;
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
	cout<<"Silmek �stedi�iniz Kitap Kodu: ";
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
			cout<<"BU K�TAP DEM�RBA� L�STES�NDED�R ENVANTERDEN �IKARILAMAZ"<<endl;
		}
		else{
			cout<<"Bu Kitap� Envanterden Silmek �stedi�inize Emin Misiniz?"<<endl;
			int gkod=rand() % 8999 + 1000;
			cout<<"DO�RULAMA ���N G�VENL�K KODUNU G�R�N�Z ("<<gkod<<"): ";
			int kod;
			cin>>kod;
			cin.ignore();
			if(gkod==kod){
				//silme i�lemini yap
				kitaplar.at(i).setDeleted(true);
				Yaz(&kitaplar);
				getKitaplar(&kitaplar);
				cout<<"Silme ��lemi Tamamland�"<<endl;
			}
		}
	}else{
		cout<<"Bu Koda Ait Kitap Bulunamad�"<<endl;
	}
	wait();
	
	
	}
	void guncelle(){
		int id,indis=-1;
	cout<<"G�ncellemek �stedi�iniz Kitap Kodu: ";
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
		cout<<"**G�NCELLENMEYECEK OLAN DE�ERLER� BO� G�R�N�Z ***"<<endl;
		cout<<"Yeni Kitap Ad�:";
		tmp=input();
		if(tmp!=""){
			kitaplar.at(indis).setName(tmp);
		}
		cout<<"Yeni Kitap Yazar�:";
		tmp="";
		tmp=input();
		if(tmp!=""){
			kitaplar.at(indis).setWriter(tmp);
		}
		cout<<"Kitab�n Demirba� Durumu(1/0):";
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
		cout<<"Bu Koda Ait Kitap Bulunamad�.";
	}
	wait();
	
	}
};
class islemKitap:public kitapEkleAraListele,public kitapSilGuncelle{
	public:
	islemKitap(){
		//i�lem men�s�	
		cout<<"***Kategori De�i�tirmek ��in ��lem Se�iminde (x) Giri�i Yap�n***"<<endl;
		cout<<"-----------------------"<<endl;
		cout<<"|"<<"    Kitap Ekleme: "<<" E"<<" |"<<endl;
		cout<<"|"<<"Kitap G�ncelleme: "<<" G"<<" |"<<endl;
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

		cout<<"Teslim Alacak �ye Kodu: ";
		tmp=input();
		
		int uyeId=getUye(&uyeler,toInteger(tmp));
		if(uyeId!=-1){
			srand (time(NULL));
			int gkod=rand() % 8999 + 1000;
			cout<<"Teslim ��lemini Onaylay�n..G�venlik Kodunu Giriniz: ("<<gkod<<"): ";
			
			tmp=input();
			if(gkod==toInteger(tmp)){
				//teslim i�lemini yap
				kitaplar.at(kitapId).setOwner(uyeler.at(uyeId).getId());
				Yaz(&kitaplar);
				cout<<"Kitap Teslimi Onayland�.."<<endl;
				
			}else{
				cout<<"G�venlik Kodunu Yanl�� Girdiniz.."<<endl;
			}
		}else{
			cout<<"Bu Koda Ait �ye Bulunamad�.."<<endl;
		}
	}else if(kitapId!=-1&&kitaplar.at(kitapId).getOwner()!=0){
		//kitab� uyeden geri alma i�lemi
		int uyeId=getUye(&uyeler,kitaplar.at(kitapId).getOwner());
		cout<<kitaplar.at(kitapId).getName()<<" kitab�n� "<<uyeler.at(uyeId).getName()<<" adl� �yeden sa�lam �ekilde geri al�nd���n� onaylay�n�z.."<<endl;
		int gkod=rand()%8999+1000;
		cout<<"G�VENL�K KODUNU G�R�N�Z ("<<gkod<<"): ";
		tmp=input();
		if(gkod==toInteger(tmp)){
			kitaplar.at(kitapId).setOwner(0);
			Yaz(&kitaplar);
			cout<<"Kitap Teslimi Onayland�..";
		}else{
			cout<<"G�VENL�K KODUNU YANLI� G�RD�N�Z..";
		}
	}
	else{
		cout<<"Bu Koda Ait Kitap Bulunamad� veya Bu Kitap Teslim Edilemez.."<<endl;
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
		cout<<"�ye Ad�: ";
		stat=input();
		cout<<"�ye Soyad�: ";
		u.setName(stat,input());
		do{
		cout<<"Uye Telefonu (05XX XXX XX XX): ";
		u.setPhone(input());
		//phoneCheck fonksiyonu olu�tur
		if(u.getPhone().length()<11){
			cout<<"11 haneli telefon numaras� giriniz"<<endl;
		}
		}while(u.getPhone().length()<11);
		uyeler.push_back(u);
		//kitap id olu�turulam�yor
		//kitaplar.at(kitaplar.size()-1).setId(kitaplar.size());
		if(uyeler.size()==1){
			uyeler.at(uyeler.size()-1).setId(1);
		}else{
			uyeler.at(uyeler.size()-1).setId(uyeler.at(uyeler.size()-2).getId()+1);
		}
			uyeler.at(uyeler.size()-1).add();
		//cout<<kitaplar.at(kitaplar.size()-1).getName()<<"-*-"<<endl;
		
		cout<<"Eklemey Devam Etmek ��in (E): ";
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
		cout<<"Yanl�� Giri� Yapt�n�z.."<<endl;
	}
	wait();
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
};
class uyeSilGuncelle{
	public:
	void sil(){
		srand (time(NULL));
	int id,i;
	bool stat=false;
	cout<<"Silmek �stedi�iniz �ye Kodu: ";
	cin>>id;
	cin.ignore();
	i=getUye(&uyeler,id);
	if(i!=-1){
		cout<<"Bu �yeyi Silmek �stedi�inize Emin Misiniz?"<<endl;
		int gkod=rand() % 8999 + 1000;
		cout<<"DO�RULAMA ���N G�VENL�K KODUNU G�R�N�Z ("<<gkod<<"): ";
		int kod;
		cin>>kod;
		cin.ignore();
		if(gkod==kod){
			//Sahip Oldu�u kitaplar�n durumuna bak
			vector<int> uKitaplar=getUyeKitap(&kitaplar,id);
			if(uKitaplar.size()>0){
				cout<<"Silmek istedi�iniz �yenin teslim etmesi gereken kitaplar� teslim ald���n�z� onaylamak i�in bir tu�a bas�n�z.."<<endl;
				getche();
				for(int j=0;j<uKitaplar.size();j++){
					kitaplar.at(uKitaplar.at(j)).setOwner(0);
				}
				Yaz(&kitaplar);
				getKitaplar(&kitaplar);
			}
						
			//silme i�lemini yap
			uyeler.at(i).setDeleted(true);
			Yaz(&uyeler);
			getUyeler(&uyeler);//tedbir ve d�ng�lerin eksiksiz d�nmesi i�in tekrar resetledim dizileri
			cout<<"Silme ��lemi Tamamland�.."<<endl;
			
		}	
	}else{
		cout<<"Bu Koda Ait �ye Bulunamad�"<<endl;
	}
	wait();
	}
	void guncelle(){
		int id,indis=-1;
	cout<<"G�ncellemek �stedi�iniz Uye Kodu: ";
	cin>>id;
	cin.ignore();

	indis=getUye(&uyeler,id);
	
	if(indis!=-1){
		Goruntule(uyeler.at(indis));
		string tmp;
		int tmp1;
		cout<<"**G�NCELLENMEYECEK OLAN DE�ERLER� BO� G�R�N�Z ***"<<endl;
		cout<<"Yeni Uye Ad� Soyad�:";
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
		cout<<"Bu Koda Ait Uye Bulunamad�.";
	}	
	wait();
	
	}
};
class islemUye:public uyeEkleAraListele, public uyeSilGuncelle{
	public:
	islemUye(){
	cout<<"***Kategori De�i�tirmek ��in ��lem Se�iminde (x) Giri�i Yap�n***"<<endl;
	cout<<"-----------------------"<<endl;
	cout<<"|"<<"    Uye Ekleme: "<<" E"<<" |"<<endl;
	cout<<"|"<<"Uye G�ncelleme: "<<" G"<<" |"<<endl;
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
	//�ye kitap teslimi tamam geri teslim alme ve uye listesinde listeleme yap�lacak	
	
	getKitaplar(&kitaplar);
	getUyeler(&uyeler);
	
	
	/* de�i�ken tipi bulma
	Kitap aa;
	cout<<typeid(aa).name();
	return 0;
	*/
	
	char menu[10];
	char t,m;
	while(true){
		setlocale(LC_ALL, "Turkish"); 
		cout<<"��lem Kategorisi Se�in (�/K): ";
		cin>>t;
		cin.ignore();
		if(t==-102||t==-127||t=='u'||t=='U'){
			t='�';
		}else if(t=='k'||t=='K'){
			t='k';
		}		
	
	
	while(t=='�'){
		islemUye iu;
		cout<<"��lem Se�in:  ";
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
			cout<<"Yanl�� Giri� Yapt�n�z."<<endl;
			wait();
			break;
		}		
	}
	while(t=='k'){
		islemKitap ik;
		cout<<"��lem Se�in: ";
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
			ik.kitapTeslim();//islemKitap class�ndaki kitapTeslim fonksiyonunu d��ar� al�p dene hata verirse
			break;
			
		case 'x':
			system("cls");
			t='.';
			break;
		default:
			cout<<"Yanl�� Giri� Yapt�n�z."<<endl;
			wait();
			break;
	}
	getKitaplar(&kitaplar);
	
  }
	}
	cout<<"d�ng�den ��kt�n�z";
	return 0;
}




