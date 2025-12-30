# ✈️ AirBooking - Airline Management System
Sistem complet de management pentru companii aeriene dezvoltat în C++, care simulează operațiunile zilnice ale unei companii aeriene moderne (ex: Wizz Air). Aplicația oferă gestionare avansată a zborurilor, pasagerilor, biletelor și serviciilor auxiliare, cu date pre-configurate și funcționalitate de salvare automată.

## 1. Date și Utilizare:

### Date Inițiale:
La pornire, aplicația încarcă automat date din `date.txt`:
- 3+ zboruri pre-configurate
- Pasageri înregistrați cu bilete
- Diverse clase și configurații
### Date finale:
- Salvare automată la ieșire în `date2.txt`
- Format text structurat pentru editare manuală
- Încărcare rapidă la pornire
  
## 2. Validări Complete:
- Format loc: `[1-99][A-Z]` (ex: 12A, 5B)
- Format poartă: `[A-Z][1-99]` (ex: A12, B5)
- Discount: 0-80%
- Capacitate zbor > 0
  
## 3. Funcționalități
### 🛫 Gestiunea Zborurilor
- **Adăugare zbor** - Înregistrare zboruri noi (număr, destinație, poartă, capacitate)
- **Căutare zbor** - Vizualizare detalii complete inclusiv lista pasagerilor
- **Modificare poartă** - Actualizare poartă de îmbarcare
- **Sortare zboruri** - După încasări, ocupare sau destinație
- **Filtrare zboruri** - Zboruri pline, goale sau după destinație

### 👥 Gestiunea Pasagerilor
- **Adăugare pasager** - Înregistrare pasageri noi cu alocare bilet
- **Căutare pasager** - Găsire rapidă după nume
- **Modificare loc** - Schimbare loc cu validare disponibilitate
- **Check-in online** - Sistem de check-in cu gestionare bagaje
- **Upgrade bilet** - Promovare între clase (Economic → Premium → Business → First Class)
  
### 📊 Rapoarte și Analiză
- **Calcul încasări** - Venit total pe zbor (bilete + bagaje)
- **Verificare capacitate** - Status locuri disponibile
- **Statistici ocupare** - Rata de umplere a zborurilor
- **Afișare optimizată** - Cu/fără detalii pasageri

## 4. Caracteristici:
### 🧳 Sistemul de Bagaje

Gestionare completă bagaje cu calcul automat taxe:

| Tip Bagaj | Greutate Max | Taxă |
|-----------|--------------|------|
| De mână | 10 kg | Gratis |
| Cabină | 10 kg | 20 EUR |
| Cală Mic | 23 kg | 35 EUR |
| Cală Mare | 32 kg | 50 EUR |

### 🎫 Sistemul de Bilete

Aplicația suportă **4 clase de bilete**:

| Clasă | Taxa Bază | Beneficii |
|-------|-----------|-----------|
| Economic | 30.00 EUR | Standard |
| Premium | 55.00 EUR | Băutură + Prioritate îmbarcare |
| Business | 35.50 EUR | Acces lounge + Confort extra |
| First Class | 74.75 EUR | Masă + Prioritate + Luxury |

**Funcționalități:**
- Detectare automată bagaje supraponderale
- Taxă extra: **15 EUR/kg** peste limită
- Actualizare dinamică a prețului de bilet atunci când se adăugă un bagaj

## 5. Ierarhie Excepții: 
Ierarhie excepții derivate din `std::exception`:
```cpp
ExceptieZboruri (baza)
  ├─ ExceptieValidare    # Date invalide (loc, poarta, discount)
  ├─ ExceptieCapacitate  # Zbor plin
  └─ ExceptieOperatie    # Operatii invalide (pasager duplicat,..)
```
### 6. Interfață Utilizator
- Meniu intuitiv cu opțiuni numerotate
- Bară de progres pentru încărcare date
- Formatare automată prețuri (ex: 125.50 EUR)
- Afișare tabelară organizată

## 7. Structura Proiectului
```
AirBooking/
├── headers/
│   ├── Bilet.h              # Ierarhie clase bilete (abstract + 4 derivate)
│   ├── Pasager.h            # Gestiune pasageri
│   ├── Zbor.h               # Gestiune zboruri
│   ├── CompanieAeriana.h    # Container zboruri + operații
│   ├── Bagaj.h              # Sistem bagaje
│   ├── CheckIn.h            # Sistem check-in
│   ├── Exceptii.h           # Ierarhie exceptii custom
│   └── Utils.h              # Functii utilitate (formatare, validare, UI)
├── Pattern/
│   └── BiletFactory.h       # Factory Pattern pentru creare bilete
├── input/
│   ├── populareDate.h/cpp   # Incarcare date din fisier
│   └── saveData.h           # Salvare date in fisier
├── src/
│   ├── Bilet.cpp
│   ├── Pasager.cpp
│   ├── Zbor.cpp
│   ├── CompanieAeriana.cpp
│   ├── Bagaj.cpp
│   └── CheckIn.cpp
├── main.cpp                 # Meniu interactiv
└── date.txt            # Date intiale
└── date2.txt           # Salvare date dupa ce se inchide terminalul
```
-----
### Folosiți template-ul corespunzător grupei voastre!

| Laborant  | Link template                                |
|-----------|----------------------------------------------|
| Dragoș B  | https://github.com/Ionnier/oop-template      |
| Tiberiu M | https://github.com/MaximTiberiu/oop-template |
| Marius MC | https://github.com/mcmarius/oop-template     |

### Important!

Aveți voie cu cod generat de modele de limbaj la care nu ați contribuit semnificativ doar dacă documentați riguros acest proces.
Codul generat pus "ca să fie"/pe care nu îl înțelegeți se punctează doar pentru puncte bonus, doar în contextul
în care oferă funcționalități ajutătoare și doar dacă are sens.

Codul din proiect trebuie să poată fi ușor de înțeles și de modificat de către altcineva. Pentru detalii, veniți la ore.

O cerință nu se consideră îndeplinită dacă este realizată doar prin cod generat.

- **Fără cod de umplutură/fără sens!**
- **Fără copy-paste!**
- **Fără variabile globale!**
- **Fără atribute publice!**
- **Pentru T2 și T3, fără date în cod!** Datele vor fi citite din fișier, aveți exemple destule.
- **Obligatoriu** fișiere cu date mai multe din care să citiți, obligatoriu cu biblioteci externe: fișiere (local sau server) sau baze de date
- obligatoriu (TBD) să integrați cel puțin două biblioteci externe pe lângă cele pentru stocare

### Tema 0

- [ ] Nume proiect (poate fi schimbat ulterior)
- [ ] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [ ] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [ ] constructori de inițializare cu parametri pentru fiecare clasă
- [ ] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [ ] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`
- [ ] cât mai multe `const` (unde este cazul) și funcții `private`
- [ ] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [ ] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `date.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [ ] minim 50-55% din codul propriu să fie C++, `.gitattributes` configurat corect
- [ ] tag de `git`: de exemplu `v0.1`
- [ ] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions
- [ ] code review #1 2 proiecte

## Tema 2

#### Cerințe
- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ] minim 75-80% din codul propriu să fie C++
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`
- [ ] code review #2 2 proiecte

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] minim 85% din codul propriu să fie C++
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`
- [ ] code review #3 2 proiecte

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC folosind Git Bash:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

Pentru a configura cu ASan, avem opțiunea `-DUSE_ASAN=ON` (nu merge pe Windows cu GCC):
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DUSE_ASAN=ON
# sau ./scripts/cmake.sh configure -e "-DUSE_ASAN=ON"
```


La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## Instrucțiuni pentru a rula executabilul

Există mai multe variante:

1. Din directorul de build (implicit `build`). Executabilul se află la locația `./build/oop` după ce a fost rulat pasul de compilare al proiectului (`./scripts/cmake.sh build` - pasul 2 de mai sus).

```sh
./build/oop
```

2. Din directorul `install_dir`. Executabilul se află la locația `./install_dir/bin/oop` după ce a fost rulat pasul de instalare (`./scripts/cmake.sh install` - pasul 3 de mai sus).

```sh
./install_dir/bin/oop
```

3. Rularea programului folosind Valgrind se poate face executând script-ul `./scripts/run_valgrind.sh` din rădăcina proiectului. Pe Windows acest script se poate rula folosind WSL (Windows Subsystem for Linux). Valgrind se poate rula în modul interactiv folosind: `RUN_INTERACTIVE=true ./scripts/run_valgrind.sh`

Implicit, nu se rulează interactiv, iar datele pentru `std::cin` sunt preluate din fișierul `date.txt`.

```sh
RUN_INTERACTIVE=true ./scripts/run_valgrind.sh
# sau
./scripts/run_valgrind.sh
```

4. Pentru a rula executabilul folosind ASan, este nevoie ca la pasul de configurare (vezi mai sus) să fie activat acest sanitizer. Ar trebui să meargă pe macOS și Linux. Pentru Windows, ar merge doar cu MSVC (nerecomandat).

Comanda este aceeași ca la pasul 1 sau 2. Nu merge combinat cu Valgrind.

```sh
./build/oop
# sau
./install_dir/bin/oop
```

## Resurse

- adăugați trimiteri **detaliate** către resursele externe care v-au ajutat sau pe care le-ați folosit
