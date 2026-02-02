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

    const std::vector<T>& getAll() const {
        return elemente;
    }

    std::vector<T>& getAllModificabil() {
        return elemente;
    }

    size_t size() const {
        return elemente.size();
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