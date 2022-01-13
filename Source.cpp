#include<iostream>
#include<string>
#include<fstream>
#include<list>

using namespace std;

//2 exceptii custom
class exceptieNume : public exception {
public:
	const char* what() const throw() {
		return "trebuie sa aiba un nume";
	}
};

class exceptieVersiune : public exception {
public:
	const char* what() const throw() {
		return "trebuie sa aiba un an introdus macar pt ca altfel nu ar mai exista cartea pe piata";
	}
};


//interfata
class IMagazin {
public:
	virtual string Descriere() = 0;
};//trebuie si mostenirea lui sa fie privata???

//informatia pe care o gasesti pe google de ex, sau pe site ul carturesti
class Book :public IMagazin { //practic ca exista o carte cu numele etc.. pe piata, somewhere intr un magazin
	char* nume;
	int* versiuni; //vector care retine anii in care a fost relansata cartea
	int nrV;
	int nrCarte; //dintr o serie
	double pret;

public:

	//constructorul cu toti parametrii
	Book(const char* nume, int* versiuni, int nrV, int nrCarte, double pret) {
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);

		}
		else
			throw exceptieNume();

		if (versiuni != nullptr) {
			this->versiuni = new int[nrV];
			for (int i = 0; i < nrV; i++)
				this->versiuni[i] = versiuni[i];
		}
		else
			throw new exception("vectorul e invalid");

		if (nrV < 1)
			throw exceptieVersiune();
		else
			this->nrV = nrV;

		if (nrCarte < 0)
			throw new exception("nr cartii este invalid");
		else
			this->nrCarte = nrCarte;

		if (pret < 5.00)
			throw new exception("pretul nu poate sa fie atat de mic");
		else
			this->pret = pret;

	}

	//constructorul default
	Book() {
		this->nume = new char[strlen("Unknown") + 1];
		strcpy_s(this->nume, strlen("Unknown") + 1, "Unknown");
	}

	//constructorul fara variabila char*
	Book(int* versiuni, int nrV, int nrCarte, double pret) {
		if (versiuni != nullptr) {
			this->versiuni = new int[nrV];
			for (int i = 0; i < nrV; i++)
				this->versiuni[i] = versiuni[i];
		}
		else
			throw new exception("vectorul e invalid");

		if (nrV < 1)
			throw exceptieVersiune();
		else
			this->nrV = nrV;

		if (nrCarte < 0)
			throw new exception("nr cartii este invalid");
		else
			this->nrCarte = nrCarte;

		if (pret < 5.00)
			throw new exception("pretul nu poate sa fie atat de mic");
		else
			this->pret = pret;
	}

	//getteri
	const char* getNume() const {
		return nume;
	}

	int* getVersiuni() const {
		return versiuni;
	}

	int getNrV() const {
		return nrV;
	}

	int getNrCarte() const {
		return nrCarte;
	}

	//returneaza o referinta de tip lvalue, ca sa pot sa l fac modificabil
	//rvalue-variab temporara; lvalue nu e, se transmite prin referinta; 
	//const referinta accepta si lvalue si rvalue iar doubla referinta e pt rvalue
	double& getPret() const {
		static double Pret = pret;
		return Pret;
	}


	//constructor de copiere
	Book(const Book& b) {
		this->nume = new char[strlen(b.nume) + 1];
		strcpy_s(this->nume, strlen(b.nume) + 1, b.nume);

		this->versiuni = new int[b.nrV];
		for (int i = 0; i < b.nrV; i++)
			this->versiuni[i] = b.versiuni[i];

		this->nrV = nrV;
		this->nrCarte = nrCarte;
		this->pret = pret;

	}


	//destructor
	~Book() {
		if (this->nume != nullptr)
			delete[] this->nume;

		if (this->versiuni != nullptr)
			delete[] this->versiuni;
	}


	//op egal
	Book& operator=(const Book& b) {
		if (this != &b) {
			if (this->nume != nullptr) {
				delete[] this->nume;
			}
			this->nume = new char[strlen(b.nume) + 1];
			strcpy_s(this->nume, strlen(b.nume) + 1, b.nume);

			if (this->versiuni != nullptr)
				delete[] this->versiuni;
			this->versiuni = new int[b.nrV];
			for (int i = 0; i < b.nrV; i++)
				this->versiuni[i] = b.versiuni[i];

			this->nrV = b.nrV;
			this->nrCarte = b.nrCarte;
			this->pret = b.pret;

		}
		return *this;
	}

	//implementare functie virtuala
	double SchimbarePret() {
		this->pret += 0;
		return this->pret;
	}

	//implementare functie virtuala pura
	string Descriere() {
		return "----detalii despre carte----";
	}

	//supraincarcare tuturor operatoriilor cunoscuti
	friend ostream& operator<< (ostream& out, const Book& b) {
		out << endl << "numele cartii: " << b.nume << endl << "la ce versiune e? " << b.nrV;
		out << " (";
		for (int i = 0; i < b.nrV; i++) {
			out << b.versiuni[i] << ", ";
		}out << ")" << endl;

		out << "pretul cartii: " << b.pret << endl << "nr cartii in serie: " << b.nrCarte << endl;

		return out;
	}

	friend istream& operator>> (istream& in, Book& b) {
		cout << "cum se numeste cartea? ";
		char aux[100];
		in >> aux;

		if (b.nume != nullptr)
			delete[] b.nume;
		b.nume = new char[strlen(aux) + 1];
		strcpy_s(b.nume, strlen(aux) + 1, aux);

		cout << "la ce versiune e? ";
		in >> b.nrV;

		cout << "anii fiecarei versiuni: ";
		if (b.versiuni != nullptr)
			delete[] b.versiuni;
		b.versiuni = new int[b.nrV];
		for (int i = 0; i < b.nrV; i++)
			in >> b.versiuni[i];

		cout << "cat costa? ";
		in >> b.pret;

		cout << "nr cartii din serie: ";
		in >> b.nrCarte;

		return in;
	}


	//op ++ post incrementare
	friend const Book operator++(Book& b, int) {
		Book aux = b;
		b.nrCarte++;
		return aux;
	}

	//op ==
	bool operator==(Book& b) {
		if (this == &b)
			return true;

		bool normalFields = strcmp(this->nume, b.nume) == 0 &&
			this->nrV == b.nrV &&
			this->nrCarte == b.nrCarte &&
			this->pret == b.pret;

		if (normalFields == true) {
			for (int i = 0; i < nrV; i++) {
				if (this->versiuni[i] != b.versiuni[i])
					return false;
			}
			return true;
		}
		else
			return false;
	}

	//op functie ()
	void operator()(int numar) {
		if (numar > 0) {
			for (int i = 0; i < nrV; i++)
				if (this->versiuni[i] + numar <= 10)//sa vad ce face dupa il modific
					this->versiuni[i] += numar;
		}
		else
			throw exceptieVersiune();

	}

	//op [] 
	int& operator[](int index) {
		if (index >= 0 && index < nrV)
			return versiuni[index];
		else
			throw new exception("indexul se afla in exteriorul intervalul specificat");

	}

	//operator cast
	operator double() {
		return pret;
	}

	//<    ??e bine??
	int operator<(const Book& b) {
		if (pret < b.pret)
			return true;
		return false;
	}



};

//clasa compusa
class Cititor {
	string numeC;
	Book* books; //ce carti are clientul, un vector din obiecte de tip Book; cititorul has a book
	int nrCarti;

public:

	Cititor() {

	}

	Cititor(string numeC, Book* books, int nrCarti) {
		if (numeC.empty())
			throw new exceptieNume();
		else
			this->numeC = numeC;

		if (nrCarti < 0)
			throw new exception("numarul e invalid");
		else this->nrCarti = nrCarti;

		if (books != nullptr) {
			this->books = new Book[nrCarti];
			for (int i = 0; i < nrCarti; i++)
				this->books = books;
		}
		else
			throw new exception("vectorul este invalid");

	}

	Cititor(const Cititor& c) {
		this->numeC = c.numeC;
		this->nrCarti = c.nrCarti;

		this->books = new Book[c.nrCarti];
		for (int i = 0; i < c.nrCarti; i++)
			this->books[i] = c.books[i];

	}

	~Cititor() {
		if (this->books != nullptr) {
			delete[] this->books;
		}
	}


	Cititor operator=(const Cititor& c) {
		if (this != &c) {
			this->numeC = c.numeC;
			this->nrCarti = c.nrCarti;

			if (this->books != c.books) {
				delete[] this->books;
				this->books = new Book[nrCarti];
				for (int i = 0; i < c.nrCarti; i++)
					this->books[i] = c.books[i];
			}
		}

		return *this;
	}


	friend ostream& operator<<(ostream& out, Cititor& c) {
		out << "numele cititorului: " << c.numeC << endl;
		out << "cate carti detine? " << c.nrCarti;

		if (c.books != nullptr) {
			for (int i = 0; i < c.nrCarti; i++)
				out << c.books[i] << " ";
		}

		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Cititor& c) {
		in >> c.numeC;
		in >> c.nrCarti;
		Book* books = new Book[c.nrCarti];
		for (int i = 0; i < c.nrCarti; i++) {
			in >> c.books[i];
			cout << " ";
		}

		return in;
	}

	//>>,<< in binar
	void scriereInFisierBinar(ofstream& fout) {
		int dim = numeC.size() + 1;

		fout.write((char*)&dim, sizeof(dim));
		fout.write(this->numeC.c_str(), dim);

		fout.write((char*)&this->nrCarti, sizeof(this->nrCarti));

		for (int i = 0; i < nrCarti; i++) {
			fout.write((char*)&books[i], sizeof(Book));
		}
	}

	void citireDinFisierBinar(ifstream& fin) {
		int dim = 0;
		fin.read((char*)&dim, sizeof(dim));

		char aux[100];
		fin.read(aux, dim);
		numeC = aux;

		fin.read((char*)&this->nrCarti, sizeof(this->nrCarti));

		for (int i = 0; i < nrCarti; i++) {
			fin.read((char*)&books[i], sizeof(Book)); //asa se face???
		}


	}

};

//clasa asemanatoare cu cea precedenta
class Scriitor {
	string numeS;
	int nrCarti;
	Book* books; //vector ce contine ce carti a scris; scriitorul has a book

public:

	Scriitor(string n = "Anonim") {

	}

	Scriitor(string numeS, Book* books, int nrCarti) {
		if (numeS.empty())
			throw new exceptieNume();
		else
			this->numeS = numeS;

		if (nrCarti < 0)
			throw new exception("numarul e invalid");
		else this->nrCarti = nrCarti;

		if (books != nullptr) {
			this->books = books;
		}
		else
			throw new exception("vectorul este invalid");
	}

	Scriitor(const Scriitor& s) {
		if (s.numeS.empty())
			throw new exceptieNume();
		else
			this->numeS = s.numeS;

		if (s.nrCarti < 0)
			throw new exception("numarul e invalid");
		else this->nrCarti = s.nrCarti;

		if (s.books != nullptr) {
			this->books = new Book[s.nrCarti];
			for (int i = 0; i < s.nrCarti; i++)
				this->books[i] = s.books[i];
		}
		else
			throw new exception("vectorul este invalid");
	}



	friend ostream& operator<<(ostream& out, const Scriitor& s) {
		out << "numele autorului: " << s.numeS;
		out << "cate carti a scris? " << s.nrCarti; //mrg

		if (s.books != nullptr) {
			for (int i = 0; i < s.nrCarti; i++)
				out << s.books[i] << " ";
		}

		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Scriitor& s) {
		in >> s.numeS;
		in >> s.nrCarti;
		Book* books = new Book[s.nrCarti];
		for (int i = 0; i < s.nrCarti; i++) {
			in >> s.books[i];
			cout << " ";
		}

		return in;
	}

	//>>,<< in binar
	void scriereInFisierBinar(ofstream& fout) {
		int dim = numeS.size() + 1;

		fout.write((char*)&dim, sizeof(dim));
		fout.write(this->numeS.c_str(), dim);

		fout.write((char*)&this->nrCarti, sizeof(this->nrCarti));

		fout.write((char*)&books, sizeof(Book));
	}

	void citireDinFisierBinar(ifstream& fin) {
		int dim = 0;
		fin.read((char*)&dim, sizeof(dim));

		char aux[100];
		fin.read(aux, dim);
		numeS = aux;

		fin.read((char*)&this->nrCarti, sizeof(this->nrCarti));

		for (int i = 0; i < nrCarti; i++) {
			fin.read((char*)&books[i], sizeof(Book)); //asa se face???
		}

	}

};

class Physical :private Book, public IMagazin {
	bool EsteHardcover; //1-da, 0-nu, este paperback

public:

	Physical(const char* nume,
		int* versiuni,
		int nrV,
		int nrCarte,
		double pret, bool EsteHardcover) :Book(nume, versiuni, nrV, nrCarte, pret) {

		this->EsteHardcover = EsteHardcover;
	}

	Physical() :Book() {
		this->EsteHardcover = true;
	}

	~Physical() {

	}

	bool getHardcover()
	{
		return EsteHardcover;
	}


	double SchimbarePret() {
		getPret() += 20.00;
		return getPret();
	}

	string Descriere() {
		return "----detalii despre cartea fizica----";
	}

	//op !() 
	bool operator!() {
		return !EsteHardcover;
	}

	friend ostream& operator<< (ostream& out, const ::Physical& p) {
		out << Book(p.getNume(), p.getVersiuni(), p.getNrV(), p.getNrCarte(), p.getPret());
		out << "este hardcover cartea? " << p.EsteHardcover;
		return out;
	}

	friend istream& operator>> (istream& in, Physical& p) {
		in >> (Book&)p;
		cout << "cartea este de tip hardcover? ";
		in >> p.EsteHardcover;
		return in;
	}



};

class Audiobook : private Book, public IMagazin {
	double durata;

public:
	//+validare
	Audiobook(const char* nume,
		int* versiuni,
		int nrV,
		int nrCarte,
		double pret,
		double durata) :Book(nume, versiuni, nrV, nrCarte, pret) {
		this->durata = durata;
	}

	Audiobook() :Book() {

	}

	~Audiobook() {

	}

	double SchimbarePret() {
		getPret() -= 20.00;
		return getPret();
	}

	string Descriere() {
		return "----detalii despre audiobook----";
	}

	friend ostream& operator<< (ostream& out, const Audiobook& a) {
		out << endl << Book(a.getNume(), a.getVersiuni(), a.getNrV(), a.getNrCarte(), a.getPret());
		out << "cat dureaza sa asculti tot audiobook-ul? " << a.durata;
		return out;
	}

	friend istream& operator>> (istream& in, Audiobook& a) {
		in >> (Book&)a;
		cout << "cat dureaza sa asculti tot audiobook-ul? ";
		in >> a.durata;
		return in;
	}
};

class Ebook : private Book, public IMagazin {
	string compatibilitate; //cu ce aplicatii este compatibila citire acestei carti (kindle, google books, apple books etc)
	bool AreNarator; //daca are optiune de narator pentru persoanele cu dificultati de vaz

public:
	Ebook(const char* nume,
		int* versiuni,
		int nrV,
		int nrCarte,
		double pret,
		string compatibilitate,
		bool AreNarator) :Book(nume, versiuni, nrV, nrCarte, pret) {
		if (compatibilitate.empty())
			throw new exception("invalid");
		else
			this->compatibilitate = compatibilitate;

		this->AreNarator = AreNarator;
	}

	Ebook() :Book() {

	}

	~Ebook() {

	}



	Ebook operator+(Ebook& e) {
		Ebook aux(*this);

		aux.compatibilitate = aux.compatibilitate + " " + e.compatibilitate; //down casting: ex: compatibilitate: google books

		return aux;
	}

	double SchimbarePret() {
		getPret() -= 30.00;
		return getPret();
	}

	string Descriere() {
		return "----detalii despre ebook----";
	}

	friend ostream& operator<< (ostream& out, const Ebook& e) {
		out << endl << Book(e.getNume(), e.getVersiuni(), e.getNrV(), e.getNrCarte(), e.getPret());
		out << "cu ce aplicatii este compatibila aceasta carte? " << e.compatibilitate << endl << "are optiune de narator? " << e.AreNarator;
		return out;
	}

	friend istream& operator>> (istream& in, Ebook& e) {
		in >> (Book&)e;
		cout << "cu ce aplicatii este compatibila aceasta carte? ";
		in >> e.compatibilitate;

		cout << "are optiune de narator? ";
		in >> e.AreNarator;

		return in;
	}

};

void main() {
	int v[] = { 2009,2010,2015,2020 };
	int v1[] = { 2019,2020,2021 };
	int v2[] = { 1920,1980,2010,2020 };
	int v3[] = { 1937,1999 };
	Book b("Rascoala", v3, sizeof(v3) / sizeof(v3[0]), 1, 10.99),
		b1("Ion", v2, sizeof(v2) / sizeof(v2[0]), 1, 9.99),
		b2("Gorila", v3, sizeof(v3) / sizeof(v3[0]), 2, 9.99);
	cout << b.Descriere();
	//cin >> b; cout << endl;
	cout << b << endl << b1 << endl << b2;

	if (b.SchimbarePret() < 0)
		cout << "pretul este mult prea mic ca sa se mai modifice";
	else
		cout << b.SchimbarePret() << endl;


	Physical p("divergent", v, 4, 1, 49.99, 1);
	cout << p.Descriere();
	cout << p << endl << endl;

	cout << p.SchimbarePret() << endl << endl;

	Book* books[] = { &b,&b1,&b2 };
	for (int i = 0; i < 3; i++)
		cout << *books[i];

	//testare cerinta 4
	cout << "--- schimbare nr volum ---" << endl;
	cout << "inainte de schimbare:" << b << endl;
	operator++(b, 1);
	cout << b << endl << endl;

	cout << "--- exista doua carti identice? lets find out ---" << endl;
	if (b1 == b2)
		cout << "cele doua obiecte sunt egale" << endl << endl;
	else
		cout << "sunt diferite intre ele" << endl << endl;

	//ce face asta????
	b(2);
	cout << b << endl << endl;

	cout << "--- afisarea anului in care a fost lansata a doua versiune a cartii ---" << endl;
	cout << b[1] << endl << endl;

	cout << "--- rotunjirea pretului (in jos) ---" << endl;
	cout << (int)b1 << endl << endl;

	cout << "--- care carte e cea mai ieftina? lets find out ---" << endl;
	if (b < b1)
		cout << "prima carte e mai ieftina decat a doua" << endl << endl;
	else
		cout << "a doua carte e mai ieftina decat prima" << endl << endl;



	//salvare in fisier binar
	Cititor c("Mara", *books, 3), c1;
	cout << c;
	ofstream fout("cititor.bin", ios::out | ios::binary | ios::app);
	if (fout.is_open()) {
		c.scriereInFisierBinar(fout);
		fout.close();
	}
	else
		cout << "nu se poate scrie in fisierul binar";

	ifstream fin("cititor.bin", ios::out | ios::binary);
	if (fin.is_open()) {
		c1.citireDinFisierBinar(fin);
		cout << "--- asta se afla in fisierul binar ---" << endl << c1 << endl;
		fin.close();
	}
	else
		cout << " nu se poate deschide fisierul binar pentru citire";



	//cerinta 8
/*cout << "--- lista ---";

Scriitor s("liviu rebreanu", *books, 3); cout << endl;
Scriitor s1("liviu rebreanu", *books, 3); cout << endl;
Scriitor s2("liviu rebreanu", *books, 3); cout << endl;

list<Book> listaScriitori;
list<Book>::iterator itList;

listaScriitori.push_back(b);
listaScriitori.push_back(b1);
listaScriitori.push_front(b2);
for (itList = listaScriitori.begin(); itList != listaScriitori.end(); itList++)
	cout << *itList;*/




	IMagazin** IVector = new IMagazin * [3]{ &b,&b1,&p }; //dimensiunea n ar trebui sa fie introdusa de mine, fa un sizeof()
	for (int i = 0; i < 3; i++) {
		cout << IVector[i]->Descriere() << endl;
	}

}