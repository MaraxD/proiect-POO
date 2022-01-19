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


//clasa abstracta
class IMagazin {
public:
	virtual string Descriere() = 0;
};

class Book :public IMagazin {
	char* nume;
	int* versiuni; //vector care retine anii in care a fost relansata cartea
	int nrV;
	int nrCarte; //nr cartii dintr o serie
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

		this->versiuni = nullptr;
		this->nrV = 0;
		this->nrCarte = 0;
		this->pret = NULL;
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
	const char* getNume() {
		return nume;
	}

	int* getVersiuni() {
		return versiuni;
	}

	int getNrV() {
		return nrV;
	}

	int getNrCarte() {
		return nrCarte;
	}

	//returneaza o referinta de tip lvalue, ca sa pot sa l fac modificabil
	//rvalue-variab temporara; lvalue nu e, se transmite prin referinta; 
	//const referinta accepta si lvalue si rvalue iar doubla referinta e pt rvalue
	double getPret() {
		return pret;
	}


	//constructor de copiere
	Book(const Book& b) {
		this->nume = new char[strlen(b.nume) + 1];
		strcpy_s(this->nume, strlen(b.nume) + 1, b.nume);

		this->nrV = b.nrV;

		this->versiuni = new int[b.nrV];
		for (int i = 0; i < b.nrV; i++)
			this->versiuni[i] = b.versiuni[i];


		this->nrCarte = b.nrCarte;
		this->pret = b.pret;

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

			this->nrV = b.nrV;

			if (this->versiuni != nullptr) {
				delete[] this->versiuni;
			}

			this->versiuni = new int[b.nrV];
			for (int i = 0; i < b.nrV; i++)
				this->versiuni[i] = b.versiuni[i];


			this->nrCarte = b.nrCarte;
			this->pret = b.pret;

		}
		return *this;
	}

	//implementare functie virtuala
	double SchimbarePret() {
		pret += 0;
		return pret;
	}

	//implementare functie virtuala pura
	string Descriere() {
		return "----detalii despre carte----";
	}

	//supraincarcare tuturor operatoriilor cunoscuti
	//op <<,>>
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

	//<    
	int operator<(const Book& b) {
		if (pret < b.pret)
			return true;
		return false;
	}

};

class Physical :public Book, public IMagazin {
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

	Physical(const Physical& p) :Book(p) {
		this->EsteHardcover = p.EsteHardcover;

	}

	Physical operator=(const Physical& p) {
		if (this != &p) {
			Book::operator=(p);
			this->EsteHardcover = p.EsteHardcover;
		}
		return *this;

	}

	bool getHardcover()
	{
		return EsteHardcover;
	}

	double pret = getPret();

	double SchimbarePret() {
		pret += 20.00;
		return pret;
	}

	string Descriere() {
		return "----detalii despre cartea fizica----";
	}

	//op !() 
	bool operator!() {
		return !EsteHardcover;
	}

	friend ostream& operator<< (ostream& out, const Physical& p) {
		out << (Book)p;
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

class Audiobook : public Book, public IMagazin {
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

	double pret = getPret();

	double SchimbarePret() {
		pret -= 20.00;
		return getPret();
	}

	string Descriere() {
		return "----detalii despre audiobook----";
	}

	friend ostream& operator<< (ostream& out, const Audiobook& a) {
		out << (Book)a;
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

class Ebook : public Book, public IMagazin {
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

	int pret = getPret();

	double SchimbarePret() {
		pret -= 30.00;
		return getPret();
	}

	string Descriere() {
		return "----detalii despre ebook----";
	}

	friend ostream& operator<< (ostream& out, const Ebook& e) {
		out << (Book)e;
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

//clasa compusa
class Cititor {
	string numeC;
	Book* books; //ce carti are clientul, un vector din obiecte de tip Book; cititorul has a book
	int nrCarti;

public:

	Cititor() {

	}

	Cititor(const string& numeC, Book* books, int nrCarti) {
		if (numeC.empty())
			throw new exceptieNume();
		else
			this->numeC = numeC;

		if (nrCarti < 0)
			throw new exception("numarul e invalid");
		else
			this->nrCarti = nrCarti;

		if (books != nullptr) {
			this->books = new Book[nrCarti];
			for (int i = 0; i < nrCarti; i++)
				this->books[i] = books[i]; //se duce in op = din Book
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
				this->books = new Book[c.nrCarti];
				for (int i = 0; i < c.nrCarti; i++)
					this->books[i] = c.books[i];
			}
		}

		return *this;
	}


	friend ostream& operator<<(ostream& out, const Cititor& c) {
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

		fout.write((char*)&books, sizeof(Book));
	}

	void citireDinFisierBinar(ifstream& fin) {
		int dim = 0;
		fin.read((char*)&dim, sizeof(dim));

		char aux[100];
		fin.read(aux, dim);
		numeC = aux;

		fin.read((char*)&this->nrCarti, sizeof(this->nrCarti));

		fin.read((char*)&books, sizeof(Book));
	}

};

//clasa asemanatoare cu cea precedenta
class Scriitor {
	string numeS;
	int nrCarti;
	list<Book*> books; //vector ce contine ce carti a scris; scriitorul has a book

public:

	Scriitor(string numeS, list<Book*> books, int nrCarti) {
		if (numeS.empty())
			throw new exceptieNume();
		else
			this->numeS = numeS;

		if (nrCarti < 0)
			throw new exception("numarul e invalid");
		else
			this->nrCarti = nrCarti;

		//validare?
		this->books = books;
	}

	Scriitor(const Scriitor& s) {
		if (s.numeS.empty())
			throw new exceptieNume();
		else
			this->numeS = s.numeS;

		if (s.nrCarti < 0)
			throw new exception("numarul e invalid");
		else this->nrCarti = s.nrCarti;

		//validare
		this->books = s.books;
	}



	friend ostream& operator<<(ostream& out, const Scriitor& s) {
		out << "numele autorului: " << s.numeS << endl;
		out << "cate carti a scris? " << s.nrCarti; //mrg

		for (Book* b : s.books) {
			out << *b << endl;
		}

		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Scriitor& s) {
		cout << "numele autorului: ";
		in >> s.numeS;
		cout << "cate carti a scris? ";
		in >> s.nrCarti;
		cout << "introdu date despre cartile scrie de autor:";
		for (Book* b : s.books) {
			in >> *b;
		}

		return in;
	}

	//>>,<< in binar
	void scriereInFisierBinar(ofstream& fout) {
		int dim = numeS.size() + 1;

		fout.write((char*)&dim, sizeof(dim));
		fout.write(this->numeS.c_str(), dim);

		fout.write((char*)&this->nrCarti, sizeof(this->nrCarti));

		for (Book* b : books) {
			fout.write((char*)&b, sizeof(Book));
		}
		fout.write((char*)&books, sizeof(Book));
	}

	void citireDinFisierBinar(ifstream& fin) {
		int dim = 0;
		fin.read((char*)&dim, sizeof(dim));

		char aux[100];
		fin.read(aux, dim);
		numeS = aux;

		fin.read((char*)&this->nrCarti, sizeof(this->nrCarti));

		for (Book* b : books) {
			fin.read((char*)&b, sizeof(Book));
		}

	}

	int getNrCarti() {
		return nrCarti;
	}

};


void main() {

	//cerinta 1 - afisare obiecte de tip Book, Physical
	int v[] = { 2009,2010,2015,2020 };
	int v1[] = { 2019,2020,2021 };
	int v2[] = { 1920,1980,2010,2020 };
	int v3[] = { 1937,1999 };
	Book b("Rascoala", v3, 2, 1, 10.99), b1("Ion", v2, 4, 1, 9.99), b2("Gorila", v3, 2, 2, 9.99), b3;
	cout << b1 << endl;
	cout << b.Descriere(); // early-binding
	//cin >> b; cout << endl;
	cout << b << b1 << b2;

	//testare functie virtuala 
	//early - binding 
	if (b.SchimbarePret() < 0)
		cout << "pretul este mult prea mic ca sa se mai modifice";
	else
		cout << endl << b.SchimbarePret() << endl;


	Physical p("Divergent", v, 4, 1, 49.99, 1), p1("Insurgent", v, 4, 2, 49.99, 1), p2("Allegiant", v, 4, 3, 49.99, 1);
	Book carti[] = { p,p1,p2 };
	cout << p.Descriere();
	cout << p << endl << endl;

	cout << p.SchimbarePret() << endl << endl;

	//late-binding
	cout << "--- late binding ---" << endl;
	Book* bp = &p;
	cout << bp->Descriere() << endl;
	cout << bp->SchimbarePret() << endl;//nu schimba pretu??? tot se duce in functia din clasa Book in loc de Physical

	Book* bp1 = &p1;
	cout << bp1->Descriere() << endl;
	cout << bp1->SchimbarePret() << endl;

	Book* bp2 = &p2;
	cout << bp2->Descriere() << endl;
	cout << bp2->SchimbarePret() << endl << endl;

	Book books[] = { b,b1,b2 };

	//testare cerinta 4 - supraincarcarea operatoriilor cunsocuti
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
	cout << b2.getPret() << " " << b.getPret() << endl;
	if (b2 < b)
		cout << "prima carte e mai ieftina decat a doua" << endl << endl;
	else
		cout << "a doua carte e mai ieftina decat prima sau ambele au acelasi pret" << endl << endl;



	//cerinta 7 - salvare in fisier binar
	Cititor c("Mara", books, 3), c1;
	cout << c << endl;
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



	//cerinta 8 - transformare vector dinamic de obiecte in lista
	cout << "--- lista ---" << endl;
	list<Book*> listaCarti;
	list<Book>::iterator itList;
	listaCarti.push_back(&p);
	listaCarti.push_back(&p1);
	listaCarti.push_back(&p2);

	Scriitor s("Veronica Roth", listaCarti, listaCarti.size());
	cout << s;



	//cerinta 10 - conceptul de polimorfism folosind o clasa abstracta
	//trebuie sa transform un obiect p de tip phyisical in book

	//IMagazin** IVector = new IMagazin * [3]{ &b,&b1,&p }; //dimensiunea n ar trebui sa fie introdusa de mine, fa un sizeof()
	//for (int i = 0; i < 3; i++) {
	//	cout << IVector[i]->Descriere() << endl;
	//}


}