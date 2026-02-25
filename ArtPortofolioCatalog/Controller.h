#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Repository.h"
#include "Command.h"
#include <stack>
#include <memory>

class Controller {
private:
    Repository& repo;
    std::stack<std::shared_ptr<Command>> undoStack;
    std::stack<std::shared_ptr<Command>> redoStack;

public:
    Controller(Repository& repo);

    void addArtwork(const Artwork&);
    void removeArtwork(const QString&);
    void updateArtwork(const Artwork& oldArt, const Artwork& newArt);

    void undo();
    void redo();

    std::vector<Artwork> filterByArtist(const QString& artist) const;
    std::vector<Artwork> filterByYear(int year) const;

    std::vector<Artwork> getAllArtworks() const;
};

#endif
