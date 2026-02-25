#ifndef CSVREPOSITORY_H
#define CSVREPOSITORY_H

#include "Repository.h"
#include <QString>

class CsvRepository : public Repository {
private:
    QString filename;
    std::vector<Artwork> loadFromFile() const;
    void saveToFile(const std::vector<Artwork>& artworks) const;

public:
    CsvRepository(const QString& filename);
    void add(const Artwork&) override;
    void remove(const QString&) override;
    void update(const Artwork&) override;
    std::vector<Artwork> getAll() const override;
};

#endif
