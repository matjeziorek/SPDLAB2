#include <vector>       
#include <fstream>      
#include <iostream>
#include <queue>        
#include <string>

using namespace std;
class Zadanie {
public:
	int terminDostepnosci;      //r
	int czasWykonania;		    //p
	int czasDostarczenia;       //q
};

struct PorownajCzasDostarczenia {
	bool operator ()(const Zadanie & zadanie1, const Zadanie & zadanie2) {
		//kolejnosc - malejaco
		return zadanie1.czasDostarczenia < zadanie2.czasDostarczenia ? true : false;
	}
};

struct PorownajTerminDostepnosci {
	bool operator ()(const Zadanie & zadanie1, const Zadanie & zadanie2) {
		//kolejnosc - malejaco
		return zadanie1.terminDostepnosci > zadanie2.terminDostepnosci ? true : false;
	}
};

int main() {

	vector<Zadanie> dane;  //wektor danych z pliku
	fstream plik;

	//tworzymy kolejke
	priority_queue < Zadanie, vector < Zadanie >, PorownajTerminDostepnosci > zbiorN; //kolejka R
	priority_queue < Zadanie, vector < Zadanie >, PorownajCzasDostarczenia > zbiorG;  //kolejka Q

	string nazwaPliku;
	nazwaPliku = "dane.txt";
	plik.open(nazwaPliku, ios::in);

	unsigned int liczbaZadan;	//format pliku: n, r p q, r p q, ...
	if (plik.good() == true) {//sprawdzamy czy plik otworzyl sie poprawnie

							  //pracujemy z plikiem
		Zadanie tmp;
		plik >> liczbaZadan;

		for (int i = 0; i<liczbaZadan; i++) {
			plik >> tmp.terminDostepnosci;    //wczytujemy r
			plik >> tmp.czasWykonania;        //wczytujemy p
			plik >> tmp.czasDostarczenia;     //wczytujemy q

			dane.push_back(tmp);			    //wrzucenie calego obiektu na koniec
		}

		for (int i = 0; i < liczbaZadan; i++)
		{
			zbiorN.push(dane[i]); //wrzucenie do kolejki
		}

		plik.close();

	}
	else {
		cout << "Nie mozna wczytac pliku" << endl;
	}

	//Schrage Algorithm
	//1 krok inicjalizacja wszystkich zmiennych
	int t = 0;      //chwila czasowa
	int k = 0;      //pozycja w permutacji
	int cMax = 0;   //maksymalny z terminow dostarczenia zadan
					//wykonuj dopoki zbior g lub n jest p nie jest pusty
	while (!(zbiorG.empty()) || !(zbiorN.empty())) {
		//ze zbioru zadan jeszcze nieuszeregowanych usuwane sa i umieszczane w zbiorze G 
		//zadania gotowe do realizacji w chwili t, tj zadania ktorych termin dostepnosci r 
		//jest mniejszy lub rowny chwili t
		while (!(zbiorN.empty()) && (zbiorN.top().terminDostepnosci <= t)) {
			zbiorG.push(zbiorN.top());      //wrzucenie do kolejki cale zadanie
			zbiorN.pop();                   //wyrzucamy element ze zbioru N
		}
		//sprawdzamy czy  zbior zadan gotowych w chwili t nie jest pusty
		//jezeli jest to chwila czasowa t przesuwana jest do momentu dostepnosci 
		//najwczesniejszego zadania ze zbioru N i aktualizujemy zbior zadan gotowych
		if (zbiorG.empty()) {
			t = zbiorN.top().terminDostepnosci;
			continue;
		}
		//zwiekszamy indeks k okreslajacy pozycje w permutacji pi 
		k++;
		// ze zboru zadañ gotowych wyznaczane jest zadanie o najwiêkszym q
		//zadanie to usuwane jest ze zbioru g
		t = t + zbiorG.top().czasWykonania;
		cMax = max(cMax, t + zbiorG.top().czasDostarczenia);
		zbiorG.pop();
	}

	cout << "C Max: " << cMax;
	getchar();
}