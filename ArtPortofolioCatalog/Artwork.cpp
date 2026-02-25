#include "Artwork.h"

Artwork::Artwork(const QString& title, const QString& artist, int year, const QString& type): title(title), artist(artist), year(year), type(type) {}

Artwork::Artwork(): title(""), artist(""), year(1000), type("") {}

QString Artwork::getTitle() const {
    return title;
}

QString Artwork::getArtist() const {
    return artist;
}

int Artwork::getYear() const {
    return year;
}

QString Artwork::getType() const {
    return type;
}

void Artwork::setTitle(const QString& title) {
    this->title = title;
}

void Artwork::setArtist(const QString& artist) {
    this->artist = artist;
}

void Artwork::setYear(int year) {
    this->year = year;
}

void Artwork::setType(const QString& type) {
    this->type = type;
}
