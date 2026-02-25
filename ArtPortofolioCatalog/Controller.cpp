#include "Controller.h"

Controller::Controller(Repository& repo) : repo(repo) {}

void Controller::addArtwork(const Artwork& artwork) {
    auto cmd = std::make_shared<AddCommand>(repo, artwork);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

void Controller::removeArtwork(const QString& title) {
    auto cmd = std::make_shared<RemoveCommand>(repo, title);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

void Controller::updateArtwork(const Artwork& oldArt, const Artwork& newArt) {
    auto cmd = std::make_shared<UpdateCommand>(repo, oldArt, newArt);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

void Controller::undo() {
    if (!undoStack.empty()) {
        auto cmd = undoStack.top();
        cmd->undo();
        redoStack.push(cmd);
        undoStack.pop();
    }
}

void Controller::redo() {
    if (!redoStack.empty()) {
        auto cmd = redoStack.top();
        cmd->execute();
        undoStack.push(cmd);
        redoStack.pop();
    }
}

std::vector<Artwork> Controller::filterByArtist(const QString& artist) const {
    auto all = repo.getAll();
    std::vector<Artwork> result;
    std::copy_if(all.begin(), all.end(), std::back_inserter(result), [&artist](const Artwork& a) {
        return a.getArtist() == artist;
    });
    return result;
}

std::vector<Artwork> Controller::filterByYear(int year) const {
    auto all = repo.getAll();
    std::vector<Artwork> result;
    std::copy_if(all.begin(), all.end(), std::back_inserter(result),[year](const Artwork& a) {
                     return a.getYear() == year;
    });
    return result;
}

std::vector<Artwork> Controller::getAllArtworks() const {
    return repo.getAll();
}
