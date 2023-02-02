#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "windows.h"
#include <iomanip>
#include <stdlib.h>
#include <ctime>
using namespace std;

char crta[]="=============================================\n";

enum tipRacuna{
	tekuciRacun=1,
	devizniRacun,
	stedniRacun,
};

struct Admin{
	char user[10];
	char pass[10];
}admin;

struct Racun{
	int stanjeRacuna = 0;
	long long int brKartice;
	int pin;	
};

struct iznos{
	int iznos=0;
};

struct zaIspisIzDatoteke{
	string ibIspis;
	string imeIspis;
	string prezimeIspis;
	string racunIspis;
	string brKarticeIspis;
	string pinIspis;
	int stanjeRacunaIspis;
};

struct Korisnik{
	int ib;
	char ime[30];
	char prezime[30];
	tipRacuna racun;
	Racun racunKorisnik;
	Korisnik unosKorisnika(){
		int izbor,temp=0;
		srand(time(NULL));
		rand();
		temp = rand()%999+1;
		this->ib=temp;
		string provjera;
		fstream file("korisnici.txt", ios::in);
		while(!file.eof()){
			file>>provjera;
			if(provjera=="IB:"){
				file>>provjera;
				if(ib==temp){
					temp = rand()%999+1;
					this->ib=temp;
				}else{
					this->ib=temp;
				}
			}
		}
		file.close();
		cin.ignore();
		cout<<"Unesite ime korisnika: ";
		cin.getline(this->ime,sizeof this->ime);
		cout<<"Unesite prezime korisnika: ";
		cin.getline(this->prezime, sizeof this->prezime);
		cout<<"Unesite vrstu racuna: ";
		cout<<"\n\t1.Tekuci racun";
		cout<<"\n\t2.Devizni racun";
		cout<<"\n\t3.Stedni racun";
		cout<<"\nOdabir: ";
		cin>>izbor;
		this->racun = (tipRacuna)izbor;
	}
};

void unosKarInfo(Korisnik &k){
	string provjera;
	long long int kart;
	int pin;
	srand(time(NULL));
	rand();
	kart = rand()%8888888888888889+1111111111111111;
	k.racunKorisnik.brKartice = kart;
	pin = rand()%8889+1111;
	k.racunKorisnik.pin = pin;
	fstream dat("korisnici.txt", ios::in);
	while(!dat.eof()){
		dat>>provjera;
		if(provjera=="Brojkartice:"){
			dat>>provjera;
			if(k.racunKorisnik.brKartice==kart){
				kart = rand()%8888888888888889+1111111111111111;
				k.racunKorisnik.brKartice = kart;
			}else{
				k.racunKorisnik.brKartice=kart;
			}
		}
		dat>>provjera;
		if(provjera=="PIN:"){
			dat>>provjera;
			if(k.racunKorisnik.pin==pin){
				pin=rand()%8889+1111;
				k.racunKorisnik.pin = pin;
			}else{
				k.racunKorisnik.pin=pin;
			}
		}
	}
	dat.close();
}

int n = 0;
int *korPtr = &n;

void prebrojKorisnike(int &ptr){
	ptr=0;
	string provjera;
	fstream file("korisnici.txt", ios::in);
	if(file.is_open()){
		while(!file.eof()){
			file>>provjera;
			if(provjera=="IB:"){
				ptr++;
			}
		}
	}
}

//=========================GLAVNI MENI=========================//

int meni(){
	cout<<"\n\t\t::MENI::\n\n";
	cout<<crta<<"\n";
	cout<<"\t\t1.Admin\n";
	cout<<"\t\t2.Korisnik\n";
	cout<<"\t\t0.Izlaz\n\n";
	cout<<crta;
}

//===================ZA ADMINA======================//

bool adminLogin(Admin a){
	int pokusaj=0;
	do{
		cout<<"Username: ";
		cin.getline(a.user,10);
		cout<<"Password: ";
		cin.getline(a.pass,10);
		cout<<"\n";
		pokusaj++;
		if(pokusaj==3){
			cout<<"Unijeli ste pogresne podatke 3 puta, zatvaramo program\n";
			Sleep(1000);
			return false;
		}
	}while(strcmp(a.user,"admin") || strcmp(a.pass,"admin"));
	return true;
}

void adminFunk(){
	cout<<crta<<"\n";
	cout<<"\t1.Unesite novog korisnika\n";
	cout<<"\t2.Pretrazite korinika (IB/Ime)\n";
	cout<<"\t3.Pregledaj sve korisnike\n";
	cout<<"\t0.Izlaz\n\n";
	cout<<crta;
}

bool pretraziKorisnika(int *ptr){
	char ime[20];
	string ib;
	bool isIme = false;
	bool isIB = false;
	string provjera;
	if(*ptr==0){
		cout<<"\n---------------------------------------\n";
		cout<<"\tNema unesenih korisnika\n";
		cout<<"---------------------------------------\n\n";
	}else{
		cin.ignore();
		cout<<"\nUnesite ime i prezime za trazenje korisnika\n";
		cout<<"-------------------------------------------\n";
		cout<<"IB: ";
		cin>>ib;
		cin.ignore();
		cout<<"Ime: ";
		cin.getline(ime,20);
		string provjera;
		fstream file("korisnici.txt", ios::in);
		if(file.is_open()){
			while(true){
				if(file.eof()){
					break;
				}
				file>>provjera;
				if(provjera=="IB:"){
					file>>provjera;
					if(ib==provjera){
						isIB=true;
					}
				}
				file>>provjera;
				if(provjera=="Ime:"){
					file>>provjera;
					if(ime==provjera){
						isIme=true;
					}
				}
			}
			if(isIB && isIme){
				cout<<left<<setw(11)<<"\nIB"<<setw(13)<<"Ime"<<setw(15)<<"Prezime"<<setw(12)<<"Racun"<<setw(22)<<"Broj kartice"<<setw(10)<<"PIN"<<"Stanje:"<<"\n\n";
				string novaProvjera;
				fstream dat("korisnici.txt", ios::in);
				if(dat.is_open()){
					while(true){
					if(dat.eof()){
						break;
					}
					dat>>provjera;
					if(provjera=="IB:"){
						dat>>provjera;
						if(provjera==ib){
							cout<<left<<setw(10)<<provjera;
							dat>>provjera;
							if(provjera=="Ime:"){
								dat>>provjera;
								cout<<left<<setw(13)<<provjera;
							}
							dat>>provjera;
							if(provjera=="Prezime:"){
								dat>>provjera;
								cout<<left<<setw(17)<<provjera;
							}
							dat>>provjera;
							if(provjera=="Racun:"){
								dat>>provjera;
								cout<<left<<setw(10)<<provjera;
							}
							dat>>provjera;
							if(provjera=="Brojkartice:"){
								dat>>provjera;
								cout<<left<<setw(22)<<provjera;
							}
							dat>>provjera;
							if(provjera=="PIN:"){
								dat>>provjera;
								cout<<setw(10)<<left<<provjera;
							}
							dat>>provjera;
							if(provjera=="Stanje:"){
								dat>>provjera;
								cout<<left<<provjera<<" KM"<<endl;
							}
						}
					}
				}
					dat.close();
				}
				cout<<"\n";
			}else{
				cout<<"Korisnik ne postoji\n";
				return false;
			}
			file.close();
		}
	}
}

void citanjeIzDatoteke(int *ptr){
	string provjera;
	if(*ptr==0){
		cout<<"\n---------------------------------------\n";
		cout<<"\tNema unesenih korisnika\n";
		cout<<"---------------------------------------\n\n";
	}else{
		cout<<left<<setw(11)<<"\nIB"<<setw(13)<<"Ime"<<setw(15)<<"Prezime"<<setw(12)<<"Racun"<<setw(22)<<"Broj kartice"<<setw(10)<<"PIN"<<"Stanje"<<"\n\n";
		fstream korisnici("korisnici.txt", ios::in);
		if(korisnici.is_open()){
			while(true){
				if(korisnici.eof()){
					break;
				}
				korisnici>>provjera;
				if(provjera=="IB:"){
					korisnici>>provjera;
					cout<<left<<setw(10)<<provjera;
				}
				korisnici>>provjera;
				if(provjera=="Ime:"){
					korisnici>>provjera;
					cout<<left<<setw(13)<<provjera;
				}
				korisnici>>provjera;
				if(provjera=="Prezime:"){
					korisnici>>provjera;
					cout<<left<<setw(17)<<provjera;
				}
				korisnici>>provjera;
				if(provjera=="Racun:"){
					korisnici>>provjera;
					cout<<left<<setw(10)<<provjera;
				}
				korisnici>>provjera;
				if(provjera=="Brojkartice:"){
					korisnici>>provjera;
					cout<<left<<setw(22)<<provjera;
				}
				korisnici>>provjera;
				if(provjera=="PIN:"){
					korisnici>>provjera;
					cout<<left<<setw(10)<<provjera;
				}
				korisnici>>provjera;
				if(provjera=="Stanje:"){
					korisnici>>provjera;
					cout<<left<<provjera<<" KM"<<endl;
				}
			}
			korisnici.close();
		}
	}
	cout<<"\n";
}

void unosUDatoteku(Korisnik &korisnik, int &ptr){
	fstream korisnici("korisnici.txt", ios::app);
	if(korisnici.is_open()){
		korisnik.unosKorisnika();
		korisnici<<"IB: "<<korisnik.ib<<endl;
		korisnici<<"Ime: "<<korisnik.ime<<endl;
		korisnici<<"Prezime: "<<korisnik.prezime<<endl;
		korisnici<<"Racun: "<<korisnik.racun<<endl;
		unosKarInfo(korisnik);
		korisnici<<"Brojkartice: "<<korisnik.racunKorisnik.brKartice<<endl;
		korisnici<<"PIN: "<<korisnik.racunKorisnik.pin<<endl;
		korisnici<<"Stanje: "<<to_string(korisnik.racunKorisnik.stanjeRacuna)<<endl;
		ptr++;
		korisnici.close();
		cout<<"----------------------------------------\n";
		cout<<"\tUspjesno unesen korisnik\n";
		cout<<"----------------------------------------\n";
	}
}

void adminOdabir(int odabir, Korisnik &korisnik);

//-------------------------------------ZA KORISNIKA-------------------------------------//
void korisnikMeni(){
	cout<<crta;
	cout<<"\t1.Uplata\n";
	cout<<"\t2.Isplata\n";
	cout<<"\t3.Stanje racuna\n";
	cout<<"\t0.Izlaz\n";
	cout<<crta;	
}

int brojac = 0;
int *brojacPtr = &brojac;

bool korisnikLogin(Korisnik k,int &brojacPtr){
	string provjera;
	string provjeraKar;
	string provjeraPin;
	bool isBr,isPin;
	int br=0,brKartLen,pinLen,pin;
	long long int brKart;
	do{
		brojacPtr=0;
		isBr=false;
		isPin=false;
		cout<<"Broj kartice: ";
		cin>>brKart;
		brKartLen = to_string(brKart).length();
		cout<<"PIN: ";
		cin>>pin;
		pinLen = to_string(pin).length();
		fstream file("korisnici.txt", ios::in);
		if(file.is_open()){
			while(isBr==false && isPin==false){
				if(file.eof()){
					break;
				}
				file>>provjera;
				if(provjera=="Brojkartice:"){
					file>>provjera;
					brojacPtr++;
					if(provjera==to_string(brKart)){
						isBr = true;
					}
					file>>provjera;
					if(provjera=="PIN:"){
						file>>provjera;
						if(provjera==to_string(pin)){
							isPin = true;
						}
					}
				}
			}
		}
		br++;
		if(br>3){
			cout<<"------------------------------------\n";
			cout<<"Unijeli ste pogresne podatke vise puta!\n";
			cout<<"Zatvaramo program\n";
			cout<<"------------------------------------\n";
			Sleep(3000);
			return false;
		}
		file.close();
	}while(brKartLen!=16 || pinLen!=4 || isBr==false || isPin==false);
	if(isBr && isPin){
		cout<<"Molimo pricekajte.\n";
		Sleep(3000);
		return true;
	}else{
		return false;
	}
}

int y=0;
int *uiPtr = &y;

void uplata(iznos &iznosU, int *uiPtr){
	iznosU.iznos=0;
	int iznos;
	cout<<"Unesite iznos koji zelite uplatiti: ";
	cin>>iznos;
	iznosU.iznos+=iznos;
	*uiPtr = 1;
}

void isplata(iznos &iznosU, int *uiPtr){
	iznosU.iznos=0;
	int iznos,temp;
	cout<<"Unesite iznos koji zelite isplatiti: ";
	cin>>iznos;
	iznosU.iznos-=iznos;
	*uiPtr = 2;
}

void ispisFileUpisStruct(int *ptr, Racun racun, iznos iznosU, int *brojacPtr, zaIspisIzDatoteke *ispisDat){
	int temp = *ptr;
	string provjera;
	int indeks;
	int br=0;
	ifstream file("korisnici.txt");
	file>>provjera;
	if(file.is_open()){
		for (int i=0;i<temp;i++){
			if(provjera=="IB:"){
				file>>provjera;
				ispisDat[i].ibIspis = provjera;
			}
			file>>provjera;
			if(provjera=="Ime:"){
				file>>provjera;
				ispisDat[i].imeIspis = provjera;
			}
			file>>provjera;
			if(provjera=="Prezime:"){
				file>>provjera;
				ispisDat[i].prezimeIspis = provjera;
			}
			file>>provjera;
			if(provjera=="Racun:"){
				file>>provjera;
				ispisDat[i].racunIspis = provjera;
			}
			file>>provjera;
			if(provjera=="Brojkartice:"){
				file>>provjera;
				ispisDat[i].brKarticeIspis = provjera;
			}
			file>>provjera;
			if(provjera=="PIN:"){
				file>>provjera;
				ispisDat[i].pinIspis = provjera;
			}
			file>>provjera;
			if(provjera=="Stanje:"){
				file>>provjera;
				if(*brojacPtr-1 == i){
					if(*uiPtr == 1){
						ispisDat[i].stanjeRacunaIspis = stoi(provjera)+iznosU.iznos;
					}else if(*uiPtr == 2){
						if(stoi(provjera)>(iznosU.iznos*(-1))-1){
							ispisDat[i].stanjeRacunaIspis = stoi(provjera)+iznosU.iznos;
						}else{
							cout<<"Nemate dovoljno sredstava\n";
						}
					}else if(*uiPtr == 3){
						ispisDat[i].stanjeRacunaIspis = stoi(provjera);
					}
				}else{
					ispisDat[i].stanjeRacunaIspis = stoi(provjera);
				}
			}
			file>>provjera;
		}
		file.close();
	}
	fstream datKor("korisnici.txt", ios::out);
	if(datKor.is_open()){
		for(int i=0;i<temp;i++){
			datKor<<"IB: "<<ispisDat[i].ibIspis<<endl;
			datKor<<"Ime: "<<ispisDat[i].imeIspis<<endl;
			datKor<<"Prezime: "<<ispisDat[i].prezimeIspis<<endl;
			datKor<<"Racun: "<<ispisDat[i].racunIspis<<endl;
			datKor<<"Brojkartice: "<<ispisDat[i].brKarticeIspis<<endl;
			datKor<<"PIN: "<<ispisDat[i].pinIspis<<endl;
			datKor<<"Stanje: "<<ispisDat[i].stanjeRacunaIspis<<endl;
		}
		datKor.close();
	}
}

void stanjeRacuna(zaIspisIzDatoteke *zaIspis, int *brojacPtr, int *uiPtr){
	int br=0;
	string provjera;
	ifstream file("korisnici.txt");
	if(file.is_open()){
		while(true){
			if(file.eof()){
				break;
			}
			file>>provjera;
			if(provjera=="Stanje:"){
				file>>provjera;
				br++;
				if(br==*brojacPtr){
					zaIspis[*brojacPtr-1].stanjeRacunaIspis = stoi(provjera);
				}
			}
		}
		file.close();
	}
	cout<<"Stanje racuna iznosi "<<zaIspis[*brojacPtr-1].stanjeRacunaIspis<<" KM\n";
	*uiPtr = 3;
}

int main(){
	fstream kreirajKor("korisnici.txt", ios::app);
	kreirajKor.close();
	prebrojKorisnike(*korPtr);
	Korisnik korisnik;
	iznos iznosU;
	zaIspisIzDatoteke *ispisDat = new zaIspisIzDatoteke[*korPtr];
	int izborKoristenja;
	meni();
	do{
	cout<<"Odaberite nacin koristenja: ";
	cin>>izborKoristenja;
	cin.ignore();
	}while(izborKoristenja<0 || izborKoristenja>2);
	system("cls");
	if(izborKoristenja == 1){
		bool isTrue = adminLogin(admin);
		if(isTrue){
			cout<<"Uspjesno ste se prijavili.\n";
			Sleep(1000);
			system("cls");
			adminFunk();
			int izbor;
			do{
				cout<<"Odaberite za nastavak: ";
				cin>>izbor;
			}while(izbor<0 || izbor>3);
			adminOdabir(izbor,korisnik);
			while(izbor!=0){
				cout<<"Odaberite za nastavak: ";
				cin>>izbor;
				adminOdabir(izbor,korisnik);
			}
		}else{
			cout<<"Prijava nije uspjela\n";
		}
	}else if(izborKoristenja==2){
		system("cls");
		bool isKorLog = korisnikLogin(korisnik,*brojacPtr);
		if(isKorLog){
			system("cls");
			korisnikMeni();
			int izborKorisnik;
			do{
				cout<<"Odaberite za nastavak: ";
				cin>>izborKorisnik;
				if(izborKorisnik==1){
					uplata(iznosU,uiPtr);
				}else if(izborKorisnik==2){
					isplata(iznosU,uiPtr);
				}else if(izborKorisnik==3){
					stanjeRacuna(ispisDat,brojacPtr,uiPtr);
				}else if(izborKorisnik==0){
					system("cls");
					main();
				}else{
					cout<<"Pogresan odabir\n";
				}
			}while(izborKorisnik<0 || izborKorisnik>3);
			ispisFileUpisStruct(korPtr, korisnik.racunKorisnik, iznosU, brojacPtr, ispisDat);
			while(izborKorisnik!=0){
				do{
				cout<<"Odaberite za nastavak: ";
				cin>>izborKorisnik;
				if(izborKorisnik==1){
					uplata(iznosU,uiPtr);
				}else if(izborKorisnik==2){
					isplata(iznosU, uiPtr);
				}else if(izborKorisnik==3){
					stanjeRacuna(ispisDat,brojacPtr, uiPtr);
				}else if(izborKorisnik==0){
					system("cls");
					main();
				}else{
					cout<<"Pogresan odabir\n";
				}
			}while(izborKorisnik<0 || izborKorisnik>3);
				ispisFileUpisStruct(korPtr, korisnik.racunKorisnik, iznosU, brojacPtr, ispisDat);
			}
		}else{
			system("cls");
			main();
		}
	}else{
		cout<<crta;
		cout<<"\n\t\tProgram zatvoren\n\n";
		cout<<crta;
	}
	cout<<endl;
	delete[] ispisDat;
	return 0;
}

void adminOdabir(int odabir, Korisnik &korisnik){
	switch(odabir){
		case 1:
			unosUDatoteku(korisnik, *korPtr);
			break;
		case 2:
			pretraziKorisnika(korPtr);
			break;	
		case 3:
			citanjeIzDatoteke(korPtr);
			break;	
		case 0:
			system("cls");
			main();	
	}
}

