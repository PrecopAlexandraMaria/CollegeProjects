#include "CsvRepository.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

CsvRepository::CsvRepository(const QString& filename) : filename(filename) {}

std::vector<Artwork> CsvRepository::loadFromFile() const {
    std::vector<Artwork> artworks;
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');
            if (parts.size() == 4) {
                artworks.emplace_back(
                    parts[0],
                    parts[1],
                    parts[2].toInt(),
                    parts[3]
                    );
            }
        }
        file.close();
    }
    return artworks;
}

void CsvRepository::saveToFile(const std::vector<Artwork>& artworks) const {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (const auto& artwork : artworks) {
            out << artwork.getTitle() << ","
                << artwork.getArtist() << ","
                << artwork.getYear() << ","
                << artwork.getType() << "\n";
        }
        file.close();
    }
}

void CsvRepository::add(const Artwork& artwork) {
    auto artworks = loadFromFile();
    artworks.push_back(artwork);
    saveToFile(artworks);
}

void CsvRepository::remove(const QString& title) {
    auto artworks = loadFromFile();
    artworks.erase(
        std::remove_if(artworks.begin(), artworks.end(), [&title](const Artwork& a) {
            return a.getTitle() == title;
        }),
        artworks.end());
    saveToFile(artworks);
}

void CsvRepository::update(const Artwork& artwork) {
    auto artworks = loadFromFile();
    for (auto& a : artworks) {
        if (a.getTitle() == artwork.getTitle()) {
            a = artwork;
            break;
        }
    }
    saveToFile(artworks);
}

std::vector<Artwork> CsvRepository::getAll() const {
    return loadFromFile();
}
