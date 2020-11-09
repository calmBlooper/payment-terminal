#pragma once

#include<vector>

#include "Identifiable.h"

template <class T, class K>
class Repository
{
private:

public:
    virtual ~Repository() {
        return;
    };
    virtual T getByKey(const K& key) = 0;
    virtual std::vector<T> getAll() = 0;
    virtual void insert(const T& entity) = 0;
    virtual void remove(const T& entity) = 0;
    virtual void update(const T& entity) = 0;
};