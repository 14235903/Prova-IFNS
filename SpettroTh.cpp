#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iomanip>
#include <TFitResultPtr.h>
#include <TFitResult.h>
#include <TMath.h>
#include <TGraph.h>
#include <TMultiGraph.h>

using namespace std;

// commento prova da VS code Pietro


//-----------------------------------------------------------Struttura programma-------------------------------------------------------------//
/*
				- Acquisizione dati
				- Calcolo i valori di energia dei picchi
				- Test di compatibilità con i valori teorici
*/
//-------------------------------------------------------------------------------------------------------------------------------------------//


void SpettroTh(){

//-------------------------------------------------------------Acquisizione dati-------------------------------------------------------------//

	int a = 0;
	const int nmisure = 7;		//ho messo 7 perché i valori teorici attesi sono 7, ma ce ne potrebbe essere un ottavo da considerare (quello Th->Ra con la probabilità del 28%)
	//da riempire con dati sperimentali
	double CHN[] = {785, 1075, 1128, 1200, 1247, 1347, 1743};
	double FWHM[] = {40, 20, 15, 25, 6, 15, 50};
	double err_CHN[nmisure];
	for (int i = 0; i < nmisure; ++i){
		err_CHN[i] = FWHM[i] / (2 * sqrt(2 * 0.69));
	}

//-------------------------------------------------------------------------------------------------------------------------------------------//




//--------------------------------------------------Calcolo i valori di energia dei picchi---------------------------------------------------//

	//ricavo le energie dei picchi utilizzando la calibrazione
	//ricopio i parametri che mi servono
	double a = 0.00497654;
	double err_a = 4.29854*pow(10,-5);
	double b = 5.48321;
	double err_b = 0.0032384;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Stampo i parametri della calibrazione: " << "a = ( " << a << " +-" << err_a << " ) MeV/conteggi ; b = ( " << b << " +-" << err_b << " ) MeV " << endl;
  	cout << "--------------------------------------------------------------------------------" << endl;


  	//faccio i conti
  	double energie[nmisure];
	double errore_E[nmisure];

	//Scrivo quali decadimenti corrispondono alle varie energie
	cout << "\t\t\tLegenda: " << endl;
	cout << "\t\t232Th -> 228Ra: misura 0\n" << "\t\t228Th -> 224Ra: misura 1\n" << "\t\t224Ra -> 220Rn: misura 2\n" << "\t\t212Bi -> 208Tl: misura 3\n" << "\t\t220Rn -> 216Po: misura 4\n" << "\t\t216Po -> 212Pb: misura 5\n" << "\t\t212Po -> 208Pb: misura 6" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	//calcolo i valori di energia corrispondenti ai picchi
	cout << "Stampo le energie misurate (calcolate con la calibrazione): " << endl;
	for(int k = 0; k < nmisure; k++){
		energie[k]=(CHN[k]-1090)*a+b;
		errore_E[k] = sqrt( pow( (CHN[k]-1090)*err_a,2) + pow(err_b,2) + pow(a *err_CHN[k], 2));
		cout << "misura n°:" << k << " : " << " ( " << energie[k] << " +- " << errore_E[k] << " ) MeV " << endl;
	}

//-------------------------------------------------------------------------------------------------------------------------------------------//




//-------------------------------------------------Test di compatibilità con i valori teorici------------------------------------------------//

	//valori attesi
	// in ordine in accordo con i canali: 232Th->228Ra ; 228Th->224Ra (quella con prob del 72%) ; 224Ra->220Rn ; 212Bi->208Tl ; 220Rn->216Po ; 216Po->212Pb ;  212Po->208Pb
	double En_teoriche[] = {4.01, 5.42, 5.68, 6.08, 6.28, 6.78, 8.78};


	//faccio il test di Gauss tra il p0 trovato dal fit e la fL ricavata con R e C al 0.5%
	cout << "--------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < nmisure; ++i)
	{
		cout << "Misura " << i  << ": ";
		double z_oss = ( pow( pow( energie[i]-En_teoriche[i] ,2) ,0.5) )/(errore_E[i]);
		if(z_oss<1.96)
		  cout << "Il valore dell'energia trovato misurato risulta compatibile con il valore atteso." << endl;
		else
		  cout << "Il valore dell'energia trovato misurato non risulta compatibile con il valore atteso." << endl;
	}
	cout << "--------------------------------------------------------------------------------" << endl;
//-------------------------------------------------------------------------------------------------------------------------------------------//


}