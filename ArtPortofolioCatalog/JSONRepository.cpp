#include "JsonRepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

JsonRepository::JsonRepository(const QString& filename) : filename(filename) {}

std::vector<Artwork> JsonRepository::loadFromFile() const {
    std::vector<Artwork> artworks;
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray array = doc.array();

        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            artworks.emplace_back(
                obj["title"].toString(),
                obj["artist"].toString(),
                obj["year"].toInt(),
                obj["type"].toString()
                );
        }
        file.close();
    }
    return artworks;
}

void JsonRepository::saveToFile(const std::vector<Artwork>& artworks) const {
    QJsonArray array;
    for (const auto& artwork : artworks) {
        QJsonObject obj;
        obj["title"] = artwork.getTitle();
        obj["artist"] = artwork.getArtist();
        obj["year"] = artwork.getYear();
        obj["type"] = artwork.getType();
        array.append(obj);
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(array);
        file.write(doc.toJson());
        file.close();
    }
}

void JsonRepository::add(const Artwork& artwork) {
    auto artworks = loadFromFile();
    artworks.push_back(artwork);
    saveToFile(artworks);
}

void JsonRepository::remove(const QString& title) {
    auto artworks = loadFromFile();
    artworks.erase(
        std::remove_if(artworks.begin(), artworks.end(), [&title](const Artwork& a) {
            return a.getTitle() == title;
        }),
        artworks.end());
    saveToFile(artworks);
}

void JsonRepository::update(const Artwork& artwork) {
    auto artworks = loadFromFile();
    for (auto& a : artworks) {
        if (a.getTitle() == artwork.getTitle()) {
            a = artwork;
            break;
        }
    }
    saveToFile(artworks);
}

std::vector<Artwork> JsonRepository::getAll() const {
    return loadFromFile();
}
