template<typename Typ>
class rolka
{
private:
	class Iterator;
	
	class czastka //Klasa cząstka
	{
	private:
		Typ dane;
		czastka* nastepny;
	public:
		czastka(const Typ& wartosc, czastka* kolejny = 0) : dane(wartosc), nastepny(kolejny) {}; //Konstruktor parametryczny
		friend class rolka; //Przyjaźń z klasą rolka, aby ta mogła wykorzystywać elementy prywatne klasy czastka
		friend class Iterator; //Przyjaźń z klasą iterator, aby ta mogła wykorzystywać elementy prywatne klasy czastka
	};
	class Iterator //Klasa Iterator
	{
	private: czastka * obecny;
			 friend class rolka; //Przyjaźń z klasą rolka, aby ta mogła wykorzystywać elementy prywatne klasy Iterator
	public: Iterator(czastka* gdzie) : obecny(gdzie) {}; //Konstruktor parametryczny
														  //Deklaracje standardowych typów, które dostarczane są przez iteratory w STL
			typedef forward_iterator_tag kategoria_iteratora;
			typedef Typ rodzaj_wartosci;
			typedef ptrdiff_t typy_roznicowe;
			typedef Typ* wskaznik;
			typedef Typ& referencja;
			//Miast powyższych linijek kodu można wydziedziczyć typy z klasy forward_iterator<T>

			Iterator() : obecny(0) {}; //Rozpoczynamy od zerowego element

									   //Kompilator sam wygenruje konstruktor Iterator oraz operator =

			Typ& operator*() //Przeciążanie operatora *
			{
				return obecny->dane;
			}
			Typ* operator->() //Przeciążanie operatora ->
			{
				return &(obecny->dane);
			}
			Iterator operator++(int) //Przeciążanie operatora postinkrementacji
			{
				Iterator tymczasowy = *this; //Wskaźnik do samej siebie
				obecny = obecny->nastepny;
				return tymczasowy;
			}
			Iterator& operator++() // //Przeciążanie operatora preinkrementacja
			{
				obecny = obecny->nastepny;
				return *this;
			}
			bool operator==(const Iterator drugi) //Przeciążanie operatora ==
			{
				return obecny == drugi.obecny;
			}
			bool operator!=(const Iterator drugi)
			{
				return obecny != drugi.obecny;
			}
	};

	//Element kontenera
	czastka* cialo;
public:
	//Definiowanie podstawowych typów dostarczanych przez STl
	typedef Typ rodzaj_typu;
	typedef Iterator iterator;
	rolka() : cialo(0) {}; //Inicjowanie pustego kontenera rolka
	~rolka(); //Destruktor kontenera
	void push_front(const Typ&);//Deklaracja funkcji push_front dla kontenera
	iterator begin() //Funkcja zwracajaca iterator na poczatek kontenera
	{
		return iterator(cialo);
	}
	iterator end() //Funkcja zwracajaca iterator na koniec kontenera
	{
		return iterator(0);
	}
};
template<typename Typ>
rolka<Typ> ::~rolka() 
{
	czastka* nic;
	while(cialo)//Usuwanie calego kontenera
	{
		nic = cialo;
		cialo = cialo->nastepny;
		delete nic;
	}
}
template<typename Typ>
void rolka<Typ> ::push_front(const Typ& wpisowe)
{
	czastka* cos = new czastka(wpisowe, cialo);
	cialo = cos;
}
