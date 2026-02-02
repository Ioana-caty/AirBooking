#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>

template <typename T>
class Repository {
protected:
    std::vector<T> elemente;

public:
    Repository() = default;

    virtual ~Repository() = default;

	virtual void adauga(const T& elem) {
        elemente.push_back(elem);
    }


    bool adaugaDacaUnic(const T& elem) {
        if (cautaDupaCheie(elem.getCheie()) != nullptr) {
            return false;
        }
        elemente.push_back(elem);
        return true;
    }

    const std::vector<T>& getAll() const {
        return elemente;
    }

    std::vector<T>& getAllModificabil() {
        return elemente;
    }

    size_t size() const {
        return elemente.size();
    }

    bool esteGol() const {
        return elemente.empty();
    }


    T* cautaDupaCheie(const std::string& cheie) {
        for (T& elem : elemente) {
            if (elem.getCheie() == cheie) {
                return &elem;
            }
        }
        return nullptr;
    }


    const T* cautaDupaCheie(const std::string& cheie) const {
        for (const T& elem : elemente) {
            if (elem.getCheie() == cheie) {
                return &elem;
            }
        }
        return nullptr;
    }

    bool stergeDupaCheie(const std::string& cheie) {
        auto it = std::find_if(elemente.begin(), elemente.end(),
            [&cheie](const T& elem) { return elem.getCheie() == cheie; });

        if (it != elemente.end()) {
            elemente.erase(it);
            return true;
        }
        return false;
    }


    std::vector<T*> filtreaza(std::function<bool(const T&)> predicat) {
        std::vector<T*> rezultat;
        for (T& elem : elemente) {
            if (predicat(elem)) {
                rezultat.push_back(&elem);
            }
        }
        return rezultat;
    }

    T& operator[](size_t index) {
        if (index >= elemente.size()) {
            throw std::out_of_range("Index invalid în Repository");
        }
        return elemente[index];
    }

    const T& operator[](size_t index) const {
        if (index >= elemente.size()) {
            throw std::out_of_range("Index invalid în Repository");
        }
        return elemente[index];
    }

    void goleste() {
        elemente.clear();
    }
};

template <typename T>
T* gasestePrimulCare(Repository<T>& repo, std::function<bool(const T&)> predicat) {
    for (T& elem : repo.getAllModificabil()) {
        if (predicat(elem)) {
            return &elem;
        }
    }
    return nullptr;
}


template <typename T>
size_t numaraElementeCare(const Repository<T>& repo, std::function<bool(const T&)> predicat) {
    size_t count = 0;
    for (const T& elem : repo.getAll()) {
        if (predicat(elem)) {
            count++;
        }
    }
    return count;
}


template <typename T, typename R>
R calculeazaTotalDin(const Repository<T>& repo, std::function<R(const T&)> extractor) {
    R total = R();  // Inițializare default (0 pentru numere)
    for (const T& elem : repo.getAll()) {
        total += extractor(elem);
    }
    return total;
}

template <typename T>
class RepositoryLimitat : public Repository<T> {
private:
    size_t capacitateMaxima;

public:
    explicit RepositoryLimitat(size_t capacitate) : capacitateMaxima(capacitate) {}

    bool adauga(const T& elem) {
        if (this->elemente.size() >= capacitateMaxima) {
            return false; // Capacitate depășită
        }
        this->elemente.push_back(elem);
        return true;
    }

    size_t getCapacitateMaxima() const {
        return capacitateMaxima;
    }

    size_t getLocuriDisponibile() const {
        return capacitateMaxima - this->elemente.size();
    }

    bool estePlin() const {
        return this->elemente.size() >= capacitateMaxima;
    }
};