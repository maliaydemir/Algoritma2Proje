#include<cstring>
#include<fstream>
#include<iostream>
#include <vector>
#include <cmath>
#include <locale.h>
#include <conio.h> 
using namespace std;

//int ve string d�n���n fonksiyonlar�
string toString(int id){
		string _id="";
		int r;
		if(id<0){
			return "-1";
		}else if(id==0){
			return "0";
		}
		for(int i=1;i<=id;i+=0){
			i*=10;
			r=(id/(i/10))%10;
			_id=(char)(r+48)+_id;
		}		
		return _id;
}
int toInteger(string _id){
	int tmp=0;
		for(int i=0;i<_id.length();i++){
			if(_id[i]>=48||_id[i]<=57){
			tmp=tmp+(((int)_id[i])-48)*pow(10,_id.length()-1-i);
			}else{
				return -1;
			}
		}
		return tmp;
}
 
string trim(string str, const string chars = "\t\n\v\f\r "){
	//stringlerin ba��ndaki ve sonundaki bo�luklar� siler
	// " test " --> "test"
	str.erase(0, str.find_first_not_of(chars));
	str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
string toLower(string str){
	string tmp="";
	for(int i=0;i<str.length();i++){
		tmp+=tolower(str[i]);
	}
	return tmp;
	
	
}


//g�ncelleme ve silme i�in olu�turulacak class� fonksiyonlar gibi yapabilirsin yap�c� fonksiyonda ayarlars�n
//ekleme i�in de o fonksiyonu kullanmak yerine �zerine ekleyerek yazd�r
class Delete{
	//Uye ve Kitap 
	protected:
	bool isDeleted;
	public:
		void setDeleted(bool status){
		isDeleted = status;
	}
		bool getDeleted(){
		return isDeleted;
	}
};

class Kitap:public Delete{
	int id;
	string name;
	string writer;
	int owner;
	bool constant=false;
	public:
		
		Kitap(){
			isDeleted=false;
			owner=0;
		}
	//SET
	void setId(int _id){
		id=_id;
	}
	void setId(string _id){
		id=toInteger(_id);
	}
	void setName(string _name){
		name=_name;
	}
	void setWriter(string _writer){
		writer=_writer;
	}
	void setConstant(bool status){
		constant=status;
	}
	void setOwner(int _owner){
		owner=_owner;
	}
	void setOwner(string _owner){
		owner=toInteger(_owner);
	}
	//GET
	int getId(){
		return id;
	}
	string _getId(){
		//int id verisi string olarak d�nd�r�lecek
		return toString(id);
		
	}
	string getName(){
		return trim(name);
	}
	string getWriter(){
		return trim(writer);
	}
	bool getConstant(){
		return constant;
	}
	int getOwner(){
		return owner;
	}
		
	string getFull(){
		if(constant){
		return _getId()+"-"+getName()+"-"+getWriter()+"-1-"+toString(owner);
		}else{
		return _getId()+"-"+getName()+"-"+getWriter()+"-0-"+toString(owner);
		}
	}
	void add(){
		//addProcess(getFull()+"\n");
			ofstream dosya("db/kitap.txt",ios::app);
			dosya<<getFull()<<endl;
			dosya.close();
	}	
};

class Uye:public Delete{
	int id;
	string name;
	string phone;
	public:
		Uye(){
			isDeleted=false;
		}
	//SET
	void setId(int _id){
		id=_id;
	}
	void setId(string _id){
		id=toInteger(_id);
	}	
	void setName(string _name,string _surname){
		name=_name+" "+_surname;
	}
	void setPhone(string _phone){
		phone=_phone;
	}
	//GET
	int getId(){
		return id;
	}
	string _getId(){
		//int id verisi string olarak d�nd�r�lecek
		return toString(id);
		
	}
	string getName(){
		return name;
	}
	string getPhone(){
		return phone;
	}

	string getFull(){
		return _getId()+"-"+getName()+"-"+getPhone();
		
	}
	void add(){
		//addProcess(getFull()+"\n");
			ofstream dosya("db/uye.txt",ios::app);
			dosya<<getFull()<<endl;
			dosya.close();
	}
};




//bekleme ve string veri giri� fonksiyonlar�
void wait(){
	cout<<endl<<"Devam Etmek ��in Bir Tu�a Bas�n�z";
	getche();
	cout<<endl;
}
string input(){

	char tmp[50];
	gets(tmp);
	for(int i=0;i<strlen(tmp);i++){
			if(tmp[i]=='*'||tmp[i]=='/'||tmp[i]=='-'||tmp[i]=='\\'){
				tmp[i]=' ';
			}
	}
	string tmp2=tmp;
	//cout<<tmp;
	return trim(tmp2);
}

//kitap fonksiyonlar�
void Yaz(vector<Kitap>* kitaplar){

	ofstream dosya("db/kitap.txt");
	for(int i=0;i<kitaplar->size();i++){
		Kitap k=kitaplar->at(i);	
		if(!k.getDeleted()){
		dosya<<k.getFull()<<endl;
		}	
	}
	dosya.close();	
}
void getKitaplar(vector<Kitap>* kitaplar){
	//kitap.txt dosyas�ndaki verileri (global)kitaplar vector �ne at�lacak
	kitaplar->clear();
	ifstream dosya;
	dosya.open("db/kitap.txt", ios::in);
	string line;
	string tmp="";
	int count=0;
	Kitap k;
	while(!dosya.eof()){
		getline(dosya,line);
			
		if(line.length()<2){
			break;
		}
		for(int i=0;i<=line.length();i++){
			if((line[i]!='-'||i==(line.length()-1))&&i!=line.length()){
				tmp+=line[i];
			}
			else{
				count++;
				if(count==1){
					//id elde edildi
					k.setId(tmp);
				}else if(count==2){
					//kitap ad� edle edildi
					k.setName(tmp);
				}else if(count==3){
					//yazar elde edildi
					k.setWriter(tmp);
				}
				else if(count==4){
					//yazar elde edildi
					//cout<<tmp;
					if(tmp=="1"){
					k.setConstant(true);
					}
					else if(tmp=="0"){
					k.setConstant(false);
					}
				}
				else if(count==5){
					k.setOwner(tmp);
				}
				tmp="";				
			}
		}
		//cout<<endl;
		count=0;
		
		kitaplar->push_back(k);	
	}	
	/*
	for(int i=0;i<kitaplar->size();i++){
		cout<<kitaplar->at(i).getFull()<<endl;
	}*/
}
int getKitap(vector<Kitap>* kitaplar,int id){
	//kitap kodunu verip dizideki indisini d�nd�r�r
	int i;
	for(i=0;i<kitaplar->size();i++){
		if(kitaplar->at(i).getId()==id){
			return i;
		}
	}
	return -1;
}
void Goruntule(Kitap k){
		cout<<"       Kitap Kodu: "<<k.getId()<<endl;
		cout<<"        Kitap Ad�: "<<k.getName()<<endl;
		cout<<"     Kitap Yazar�: "<<k.getWriter()<<endl;
		cout<<"  Demirba� Durumu: ";
		if(k.getConstant()){
			cout<<"Evet"<<endl;
		}else{
			cout<<"Hay�r"<<endl;
		}
		cout<<"Kitab� Emanet�isi: ";
		if(k.getOwner()==0){
			cout<<"YOK"<<endl;
		}else{
			cout<<k.getOwner()<<endl;
		}
}

//�ye fonksiyonlar�
void Goruntule(Uye u){
	cout<<"    �ye Kodu: "<<u._getId()<<endl;
	cout<<"     �ye Ad�: "<<u.getName()<<endl;
	cout<<"�ye Telefonu: "<<u.getPhone()<<endl;
}
void Yaz(vector<Uye>* uyeler){

	ofstream dosya("db/uye.txt",ios::trunc);
	for(int i=0;i<uyeler->size();i++){
		Uye u=uyeler->at(i);
		if(!u.getDeleted()){
		dosya<<u.getFull()<<endl;
		}
		//cout<<k.getFull()<<endl;
	}
	dosya.close();
			
}
void getUyeler(vector<Uye>* uyeler){
	//kitap.txt dosyas�ndaki verileri (global)kitaplar vector �ne at�lacak
	uyeler->clear();
	ifstream dosya;
	dosya.open("db/uye.txt", ios::in);
	string line;
	string tmp="";
	int count=0;
	Uye u;
	while(!dosya.eof()){
		getline(dosya,line);
		if(line.length()<2){
			break;
		}
		if(line.length()<2){
			break;
		}
	
		for(int i=0;i<=line.length();i++){
			if((line[i]!='-'||i==(line.length()-1))&&i!=line.length()){
				tmp+=line[i];				
			}
			else{
				//cout<<tmp<<endl;
				count++;
				if(count==1){
					//id elde edildi
					u.setId(tmp);
				}else if(count==2){
					//kitap ad� edle edildi
					u.setName(tmp,"");
				}else if(count==3){
					//yazar elde edildi
					u.setPhone(tmp);
				}		
				tmp="";				
		}
		//cout<<endl;		
	}
		count=0;
		uyeler->push_back(u);	
	/*
	for(int i=0;i<kitaplar->size();i++){
		cout<<kitaplar->at(i).getFull()<<endl;
	}*/
}
}
int getUye(vector<Uye>* uyeler,int id){
	//�ye kodunu verip dizideki indisini d�nd�r�r
	int i;
	for(i=0;i<uyeler->size();i++){
		if(uyeler->at(i).getId()==id){
			return i;
		}
	}
	return -1;
}

vector<int> getUyeKitap(vector<Kitap>* kitaplar, int id){
	//verilen uyenin(id) �d�n� ald��� kitaplar�n indisini vector olarak d�nd�r�r
	vector<int> tmp;
	for(int i=0;i<kitaplar->size();i++){
		if(kitaplar->at(i).getOwner()==id){
			tmp.push_back(i);
		}
	}
	return tmp;
	
}


