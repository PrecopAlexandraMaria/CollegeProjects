#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Artwork.h"
#include <vector>
#include <memory>

class Repository {
public:
    virtual void add(const Artwork&) = 0;
    virtual void remove(const QString&) = 0;
    virtual void update(const Artwork&) = 0;
    virtual std::vector<Artwork> getAll() const = 0;
    virtual ~Repository() = default;
};

#endif
