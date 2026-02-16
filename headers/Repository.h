#pragma once
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

template <typename T>
class Repository {
protected:
    std::vector<T> items;

public:
    Repository() = default;

    virtual ~Repository() = default;

    virtual void add(const T& item) {
        items.push_back(item);
    }

    const std::vector<T>& getAll() const {
        return items;
    }

    std::vector<T>& getAllModifiable() {
        return items;
    }

    size_t size() const {
        return items.size();
    }

    T* findByKey(const std::string& key) {
        for (T& item : items) {
            if (item.getKey() == key) {
                return &item;
            }
        }
        return nullptr;
    }

    const T* findByKey(const std::string& key) const {
        for (const T& item : items) {
            if (item.getKey() == key) {
                return &item;
            }
        }
        return nullptr;
    }

    std::vector<T*> filter(std::function<bool(const T&)> predicate) {
        std::vector<T*> result;
        for (T& item : items) {
            if (predicate(item)) {
                result.push_back(&item);
            }
        }
        return result;
    }

    T& operator[](size_t index) {
        if (index >= items.size()) {
            throw std::out_of_range("Invalid index in Repository");
        }
        return items[index];
    }

    const T& operator[](size_t index) const {
        if (index >= items.size()) {
            throw std::out_of_range("Invalid index in Repository");
        }
        return items[index];
    }

};

template <typename T>
T* findFirstWhere(Repository<T>& repo, std::function<bool(const T&)> predicate) {
    for (T& item : repo.getAllModifiable()) {
        if (predicate(item)) {
            return &item;
        }
    }
    return nullptr;
}

template <typename T>
size_t countWhere(const Repository<T>& repo, std::function<bool(const T&)> predicate) {
    size_t count = 0;
    for (const T& item : repo.getAll()) {
        if (predicate(item)) {
            count++;
        }
    }
    return count;
}