#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

//lettura del chilometraggio totale
int lettura(const int &inizio,const int &blocchi,istream &i){
	int valore=0;
	char lett=0;
	i.seekg(inizio);
	for(int x=0;x<blocchi;x++){
		lett=i.get();
		valore+=lett*pow(10,x);
	}
	return valore;
}

//scrittura del nuovo chilometraggio totale
int scrittura(const int &inizio,const int &blocchi,int km,ostream &o){
	int valore=0;
	o.seekp(inizio);
	for(int x=0;x<blocchi;x++){
		valore=km%10;
		o.put(valore);
		km/=10;
	}
	return 0;
}

//programma per modifica km totali in aprilia caponord e simili
int main(int argc,char **argv){
	
	if(argc!=3){
                cerr<<"Usage: "<<argv[0]<<" file_lettura km_nuovi"<<endl;
                return 1;
        }
	
	const int inizio=0x1C; //indirizzo primo byte odometro totale
	const int blocchi=6; //numero di celle
	int km=atoi(argv[2]); //(atoi converte string in int) il secondo argomento che rappresenta i chilometri da inserire viene convertito in int
	char c;

	ifstream fi(argv[1]); //il primo argomento è il nome del file da modificare
	if(!fi)
		cout<<"Errore apertura file input!!"<<endl;
	ofstream fo("output");
	if(!fo)
		cout<<"Errore apertura file output!!"<<endl;

	for(int i=0;i<0x1c;i++){ //copio il file fino al punto da modificare
		fi.get(c);
		fo<<c;
	}
	
	cout<<"Valore attuale: "<<lettura(inizio,blocchi,fi)<<endl; //leggo il valore originale
	if(scrittura(inizio,blocchi,km,fo)!=0)						//scrivo il valore inserito nel nuovo file
		cout<<"Errore durante la scrittura sul file"<<endl;		//e controllo che l'operazione sia andata a buon fine
	
	fi.seekg(inizio+blocchi); //mi sposto a dopo il chilometraggio
	fo.seekp(inizio+blocchi); //in entrambi i file...
	while(fi.get(c)) //...e copio tutto il resto fino alla fine
		fo<<c;

	fi.close();
	fo.close();
	
	ifstream contr("output"); //apro il file creato in lettura
	if(!contr)				//per controllare che tutto sia andato a buon fine
		cout<<"Errore apertura controllo!!"<<endl;
	cout<<"Lettura nuovo valore: "<<lettura(inizio,blocchi,contr)<<endl;
	contr.close();
	
	cout<<"Programma terminato correttamente"<<endl;
	return 0;
}
