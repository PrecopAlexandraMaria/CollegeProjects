#ifndef ARTWORK_H
#define ARTWORK_H

#include <QString>

class Artwork {
private:
    QString title;
    QString artist;
    int year;
    QString type;

public:
    Artwork(const QString& title, const QString& artist, int year, const QString& type);
    Artwork();

    QString getTitle() const;
    QString getArtist() const;
    int getYear() const;
    QString getType() const;

    void setTitle(const QString& title);
    void setArtist(const QString& artist);
    void setYear(int year);
    void setType(const QString& type);
};

#endif
