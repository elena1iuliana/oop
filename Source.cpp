#include "Header.h"

Task::Task(string descriere) {
    this->descriere = descriere;
    this->buget = 0;
    this->termen = "";
    this->areTermenLimita = false;
    this->areBugetLimitat = false;
}

Task::Task(string descriere, string termen, double buget) {
    this->descriere = descriere;
    this->buget = buget;
    this->termen = termen;
    this->areTermenLimita = !termen.empty();
    this->areBugetLimitat = buget > 0;
}

Task::Task(const Task& other) {
    this->descriere = other.descriere;
    this->buget = other.buget;
    this->termen = other.termen;
    this->areTermenLimita = other.areTermenLimita;
    this->areBugetLimitat = other.areBugetLimitat;
}

string Task::getDescriere() const {
    return descriere;
}

void Task::setDescriere(string descriere) {
    this->descriere = descriere;
}

double Task::getBuget() const {
    return buget;
}

void Task::setBuget(double buget) {
    this->buget = buget;
    this->areBugetLimitat = buget > 0;
}

string Task::getTermen() const {
    return termen;
}

void Task::setTermen(string termen) {
    this->termen = termen;
    this->areTermenLimita = !termen.empty();
}

bool Task::getAreTermenLimita() const {
    return areTermenLimita;
}

bool Task::getAreBugetLimitat() const {
    return areBugetLimitat;
}

ostream& operator<<(ostream& out, const Task& t) {
    out << "Task: " << t.descriere;
    if (t.areTermenLimita) {
        out << " (Termen: " << t.termen << ")";
    }
    if (t.areBugetLimitat) {
        out << " (Buget: " << t.buget << ")";
    }
    return out;
}

istream& operator>>(istream& in, Task& t) {
    cout << "Introduceți descrierea task-ului: ";
    getline(in, t.descriere);

    cout << "Introduceți termenul limită (lăsați gol dacă nu există): ";
    getline(in, t.termen);
    t.areTermenLimita = !t.termen.empty();

    cout << "Introduceți bugetul (0 dacă nu există): ";
    in >> t.buget;
    in.ignore();
    t.areBugetLimitat = t.buget > 0;

    return in;
}


Angajat::Angajat(string nume,  double salariu, string functie, string departament) {
    this->nume = nume;
    this->salariu = salariu;
    this->functie = functie;
    this->departament = departament;
}

Angajat::Angajat(const  Angajat& other) {
    this->nume = other.nume;
    this->salariu = other.salariu;
    this->functie = other.functie;
    this->departament = other.departament;

    
    for (int i = 0; i < other.subordonati.getDimensiune(); i++) {
        this->subordonati.adauga(other.subordonati.obtine(i));
    }

    
    for (int i = 0; i < other.taskuri.getDimensiune(); i++) {
        this->taskuri.adauga(other.taskuri.obtine(i));
    }
}

Angajat::~Angajat() {
}

string Angajat::getNume() const {
    return nume;
}

void Angajat::setNume(string nume) {
    this->nume = nume;
}

double Angajat::getSalariu() const {
    return salariu;
}

void Angajat::setSalariu(double salariu) {
    this->salariu = salariu;
}

string Angajat::getFunctie() const {
    return functie;
}

string Angajat::getDepartament() const {
    return departament;
}

void Angajat::adaugaSubordonat(Angajat* subordonat) {
    subordonati.adauga(subordonat);
}

void Angajat::stergeSubordonat(int index) {
    subordonati.sterge(index);
}

void Angajat::adaugaTask(const Task& task) {
    taskuri.adauga(task);
}

void Angajat::stergeTask(int index) {
    taskuri.sterge(index);
}

DoublyLinkedList<Angajat*>& Angajat::getSubordonati() {
    return subordonati;
}

DoublyLinkedList<Task>& Angajat::getTaskuri() {
    return taskuri;
}

ostream& operator<<(ostream& out, const Angajat& a) {
    out << a.functie << ": " << a.nume << " (Departament: " << a.departament << ", Salariu: " << a.salariu << ")";
    return out;
}


Muncitor::Muncitor(string nume, double salariu, string departament) : Angajat(nume, salariu, "Muncitor", departament) {}

Muncitor::Muncitor(const Muncitor& other) : Angajat(other) {}

void Muncitor::afiseazaInfo() {
    cout << "Muncitor: " << nume << "\n";
    cout << "Salariu: " << salariu << "\n";
    cout << "Departament: " << departament << "\n";
    cout << "Taskuri: " << taskuri.getDimensiune() << "\n";

    for (int i = 0; i < taskuri.getDimensiune(); i++) {
        Task task = taskuri.obtine(i);
        cout << "  - " << task.getDescriere();
        if (task.getAreTermenLimita()) {
            cout << " (Termen: " << task.getTermen() << ")";
        }
        if (task.getAreBugetLimitat()) {
            cout << " (Buget: " << task.getBuget() << ")";
        }
        cout << "\n";
    }
    cout << "------------------------\n";
}

ostream& operator<<(ostream& out, const Muncitor& m) {
    out << "Muncitor: " << m.nume << " (Departament: " << m.departament << ", Salariu: " << m.salariu << ")";
    return out;
}


Manager::Manager(string nume, double salariu, string functie, string departament) : Angajat(nume, salariu, functie, departament) {}

Manager::Manager(const Manager& other) : Angajat(other) {}

void Manager::afiseazaInfo() {
    cout << functie << ": " << nume << "\n";
    cout << "Salariu: " << salariu << "\n";
    cout << "Departament: " << departament << "\n";
    cout << "Subordonați: " << subordonati.getDimensiune() << "\n";

    for (int i = 0; i < subordonati.getDimensiune(); i++) {
        Angajat* subordonat = subordonati.obtine(i);
        cout << "  - " << subordonat->getNume() << " (" << subordonat->getFunctie() << ")\n";
    }

    cout << "Taskuri: " << taskuri.getDimensiune() << "\n";
    for (int i = 0; i < taskuri.getDimensiune(); i++) {
        Task task = taskuri.obtine(i);
        cout << "  - " << task.getDescriere();
        if (task.getAreTermenLimita()) {
            cout << " (Termen: " << task.getTermen() << ")";
        }
        if (task.getAreBugetLimitat()) {
            cout << " (Buget: " << task.getBuget() << ")";
        }
        cout << "\n";
    }
    cout << "------------------------\n";
}

ostream& operator<<(ostream& out, const Manager& m) {
    out << m.functie << ": " << m.nume << " (Departament: " << m.departament << ", Salariu: " << m.salariu << ")";
    return out;
}

// Implementarea clasei CEO
CEO::CEO(string nume, double salariu) : Manager(nume, salariu, "CEO", "Conducere") {}

CEO::CEO(const CEO& other) : Manager(other) {}

ostream& operator<<(ostream& out, const CEO& c) {
    out << "CEO: " << c.nume << " (Salariu: " << c.salariu << ")";
    return out;
}


SefDepartament::SefDepartament(string nume, double salariu, string departament) : Manager(nume, salariu, "Șef Departament", departament) {}

SefDepartament::SefDepartament(const SefDepartament& other) : Manager(other) {}

ostream& operator<<(ostream& out, const SefDepartament& sd) {
    out << "Șef Departament: " << sd.nume << " (Departament: " << sd.departament << ", Salariu: " << sd.salariu << ")";
    return out;
}


TeamLeader::TeamLeader(string nume, double salariu, string departament) : Manager(nume, salariu, "Team Leader", departament) {}

TeamLeader::TeamLeader(const TeamLeader& other) : Manager(other) {}

ostream& operator<<(ostream& out, const TeamLeader& tl) {
    out << "Team Leader: " << tl.nume << " (Departament: " << tl.departament << ", Salariu: " << tl.salariu << ")";
    return out;
}


void FileManager::exportAngajati(const string& filename, DoublyLinkedList<Angajat*>& angajati) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw "Nu s-a putut deschide fișierul pentru export";
    }

    file << angajati.getDimensiune() << "\n";
    for (int i = 0; i < angajati.getDimensiune(); i++) {
        Angajat* angajat = angajati.obtine(i);
        file << angajat->getNume() << "," << angajat->getSalariu() << ","
            << angajat->getFunctie() << "," << angajat->getDepartament() << "\n";

        DoublyLinkedList<Task>& taskuri = angajat->getTaskuri();
        file << taskuri.getDimensiune() << "\n";
        for (int j = 0; j < taskuri.getDimensiune(); j++) {
            Task task = taskuri.obtine(j);
            file << task.getDescriere() << "," << task.getTermen() << "," << task.getBuget() << "\n";
        }

      
        DoublyLinkedList<Angajat*>& subordonati = angajat->getSubordonati();
        file << subordonati.getDimensiune() << "\n";
        for (int j = 0; j < subordonati.getDimensiune(); j++) {
           
            file << j << "\n";
        }
    }

    file.close();
}

DoublyLinkedList<Angajat*> FileManager::importAngajati(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw "Nu s-a putut deschide fișierul pentru import";
    }

    DoublyLinkedList<Angajat*> angajati;

    try {
        int numarAngajati;
        file >> numarAngajati;
        file.ignore(); 

        for (int i = 0; i < numarAngajati; i++) {
            string linie;
            getline(file, linie);

            size_t pos = 0;
            string token;
            string nume, functie, departament;
            double salariu;

            pos = linie.find(",");
            nume = linie.substr(0, pos);
            linie.erase(0, pos + 1);

            
            pos = linie.find(",");
            salariu = stod(linie.substr(0, pos));
            linie.erase(0, pos + 1);

           
            pos = linie.find(",");
            functie = linie.substr(0, pos);
            linie.erase(0, pos + 1);

            departament = linie;

            
            Angajat* angajat = nullptr;
            if (functie == "Muncitor") {
                angajat = new Muncitor(nume, salariu, departament);
            }
            else if (functie == "CEO") {
                angajat = new CEO(nume, salariu);
            }
            else if (functie == "Șef Departament") {
                angajat = new SefDepartament(nume, salariu, departament);
            }
            else if (functie == "Team Leader") {
                angajat = new TeamLeader(nume, salariu, departament);
            }
            else {
                throw "Funcție necunoscută: " + functie;
            }

            
            int numarTaskuri;
            file >> numarTaskuri;
            file.ignore(); 

            for (int j = 0; j < numarTaskuri; j++) {
                string linieTask;
                getline(file, linieTask);

                size_t posTask = 0;
                string descriere, termen;
                double buget;

               
                posTask = linieTask.find(",");
                descriere = linieTask.substr(0, posTask);
                linieTask.erase(0, posTask + 1);

                
                posTask = linieTask.find(",");
                termen = linieTask.substr(0, posTask);
                linieTask.erase(0, posTask + 1);

                buget = stod(linieTask);

                Task task(descriere, termen, buget);
                angajat->adaugaTask(task);
            }

            
            int numarSubordonati;
            file >> numarSubordonati;
            file.ignore(); 

            
            for (int j = 0; j < numarSubordonati; j++) {
                string linieSubordonat;
                getline(file, linieSubordonat);
            }

            angajati.adauga(angajat);
        }
    }
    catch (const char* e) {
       
        for (int i = 0; i < angajati.getDimensiune(); i++) {
            delete angajati.obtine(i);
        }
        throw e;
    }

    file.close();
    return angajati;
}

void FileManager::verificaErori(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw "Nu s-a putut deschide fișierul pentru verificare";
    }

    int numarLinie = 0;
    string linie;

    try {
        int numarAngajati;
        file >> numarAngajati;
        file.ignore();
        numarLinie++;

        if (numarAngajati < 0) {
            throw "Număr invalid de angajați la linia " + to_string(numarLinie);
        }

        for (int i = 0; i < numarAngajati; i++) {
            getline(file, linie);
            numarLinie++;

            
            int numarVirghiule = 0;
            for (char c : linie) {
                if (c == ',') numarVirghiule++;
            }

            if (numarVirghiule != 3) {
                throw "Format invalid pentru angajat la linia " + to_string(numarLinie);
            }

            
            size_t pos = linie.find(",");
            pos = linie.find(",", pos + 1);
            size_t endPos = linie.find(",", pos + 1);
            string salariuStr = linie.substr(pos + 1, endPos - pos - 1);

            try {
                double salariu = stod(salariuStr);
                if (salariu < 0) {
                    throw "Salariu invalid la linia " + to_string(numarLinie);
                }
            }
            catch (...) {
                throw "Salariu invalid la linia " + to_string(numarLinie);
            }

           
            int numarTaskuri;
            file >> numarTaskuri;
            numarLinie++;

            if (numarTaskuri < 0) {
                throw "Număr invalid de taskuri la linia " + to_string(numarLinie);
            }

            for (int j = 0; j < numarTaskuri; j++) {
                getline(file, linie);
                numarLinie++;

                
                numarVirghiule = 0;
                for (char c : linie) {
                    if (c == ',') numarVirghiule++;
                }

                if (numarVirghiule != 2) {
                    throw "Format invalid pentru task la linia " + to_string(numarLinie);
                }

               
                pos = linie.find(",");
                pos = linie.find(",", pos + 1);
                string bugetStr = linie.substr(pos + 1);

                try {
                    double buget = stod(bugetStr);
                    if (buget < 0) {
                        throw "Buget invalid la linia " + to_string(numarLinie);
                    }
                }
                catch (...) {
                    throw "Buget invalid la linia " + to_string(numarLinie);
                }
            }

            int numarSubordonati;
            file >> numarSubordonati;
            file.ignore();
            numarLinie++;

            if (numarSubordonati < 0) {
                throw "Număr invalid de subordonați la linia " + to_string(numarLinie);
            }

            for (int j = 0; j < numarSubordonati; j++) {
                getline(file, linie);
                numarLinie++;

                try {
                    int index = stoi(linie);
                    if (index < 0) {
                        throw "Index invalid de subordonat la linia " + to_string(numarLinie);
                    }
                }
                catch (...) {
                    throw "Index invalid de subordonat la linia " + to_string(numarLinie);
                }
            }
        }
    }
    catch (const char* e) {
        throw e;
    }
    catch (const string& e) {
        throw e.c_str();
    }

    file.close();
    cout << "Verificare completă. Fișierul este valid.\n";
}


int main() {
    try {
        
        CEO* ceo = new CEO("Ion Popescu", 15000);

        SefDepartament* sefIT = new SefDepartament("Maria Ionescu", 10000, "IT");
        SefDepartament* sefMarketing = new SefDepartament("George Popa", 9500, "Marketing");

        TeamLeader* teamLeaderDev = new TeamLeader("Ana Dumitrescu", 8000, "IT");
        TeamLeader* teamLeaderTest = new TeamLeader("Mihai Radu", 7800, "IT");
        TeamLeader* teamLeaderSocial = new TeamLeader("Elena Stoica", 7500, "Marketing");

        Muncitor* developer1 = new Muncitor("Andrei Constantin", 6000, "IT");
        Muncitor* developer2 = new Muncitor("Cristina Dinu", 6200, "IT");
        Muncitor* tester1 = new Muncitor("Bogdan Marin", 5800, "IT");
        Muncitor* marketingSpecialist = new Muncitor("Diana Stancu", 5500, "Marketing");

        
        ceo->adaugaSubordonat(sefIT);
        ceo->adaugaSubordonat(sefMarketing);

        sefIT->adaugaSubordonat(teamLeaderDev);
        sefIT->adaugaSubordonat(teamLeaderTest);
        sefMarketing->adaugaSubordonat(teamLeaderSocial);

        teamLeaderDev->adaugaSubordonat(developer1);
        teamLeaderDev->adaugaSubordonat(developer2);
        teamLeaderTest->adaugaSubordonat(tester1);
        teamLeaderSocial->adaugaSubordonat(marketingSpecialist);

        
        Task task1("Dezvoltare frontend", "15.06.2025", 2000);
        Task task2("Testare integrare", "20.06.2025", 1500);
        Task task3("Campanie social media", "10.06.2025", 3000);
        Task task4("Raport trimestrial", "01.07.2025", 0);

        developer1->adaugaTask(task1);
        tester1->adaugaTask(task2);
        marketingSpecialist->adaugaTask(task3);
        ceo->adaugaTask(task4);

        
        cout << "=== Informații despre angajați ===\n";
        ceo->afiseazaInfo();
        sefIT->afiseazaInfo();
        teamLeaderDev->afiseazaInfo();
        developer1->afiseazaInfo();

        
        DoublyLinkedList<Angajat*> angajatiExport;
        angajatiExport.adauga(ceo);
        angajatiExport.adauga(sefIT);
        angajatiExport.adauga(sefMarketing);
        angajatiExport.adauga(teamLeaderDev);
        angajatiExport.adauga(teamLeaderTest);
        angajatiExport.adauga(teamLeaderSocial);
        angajatiExport.adauga(developer1);
        angajatiExport.adauga(developer2);
        angajatiExport.adauga(tester1);
        angajatiExport.adauga(marketingSpecialist);

        
        FileManager::exportAngajati("angajati.csv", angajatiExport);
        cout << "Export realizat cu succes!\n";

        
        try {
            FileManager::verificaErori("angajati.csv");
        }
        catch (const char* mesajEroare) {
            cout << "Eroare la verificarea fișierului: " << mesajEroare << "\n";
        }

       
        try {
            DoublyLinkedList<Angajat*> angajatiImport = FileManager::importAngajati("angajati.csv");
            cout << "Import realizat cu succes! Număr angajați importați: " << angajatiImport.getDimensiune() << "\n";

           
            cout << "Primul angajat importat: " << *(angajatiImport.obtine(0)) << "\n";

            for (int i = 0; i < angajatiImport.getDimensiune(); i++) {
                delete angajatiImport.obtine(i);
            }
        }
        catch (const char* mesajEroare) {
            cout << "Eroare la importul din fișier: " << mesajEroare << "\n";
        }

        delete ceo;
        delete sefIT;
        delete sefMarketing;
        delete teamLeaderDev;
        delete teamLeaderTest;
        delete teamLeaderSocial;
        delete developer1;
        delete developer2;
        delete tester1;
        delete marketingSpecialist;

    }
    catch (const char* mesajEroare) {
        cout << "Eroare: " << mesajEroare << "\n";
    }
    catch (const exception& e) {
        cout << "Excepție standard: " << e.what() << "\n";
    }
    catch (...) {
        cout << "Excepție necunoscută!\n";
    }

    return 0;
}
