#ifndef JSONREPOSITORY_H
#define JSONREPOSITORY_H

#include "Repository.h"
#include <QString>

class JsonRepository : public Repository {
private:
    QString filename;
    std::vector<Artwork> loadFromFile() const;
    void saveToFile(const std::vector<Artwork>& artworks) const;

public:
    JsonRepository(const QString& filename);
    void add(const Artwork&) override;
    void remove(const QString&) override;
    void update(const Artwork&) override;
    std::vector<Artwork> getAll() const override;
};

#endif
