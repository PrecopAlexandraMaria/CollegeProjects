#include "Command.h"
#include <algorithm>

AddCommand::AddCommand(Repository& repo, const Artwork& artwork)
    : repo(repo), artwork(artwork) {}

void AddCommand::execute() {
    repo.add(artwork);
}

void AddCommand::undo() {
    repo.remove(artwork.getTitle());
}

RemoveCommand::RemoveCommand(Repository& repo, const QString& title): repo(repo) {
    auto artworks = repo.getAll();
    auto it = std::find_if(artworks.begin(), artworks.end(), [&title](const Artwork& a)
    {
        return a.getTitle() == title;
    });
    if (it != artworks.end()) {
        backup = *it;
    }
}

void RemoveCommand::execute() {
    repo.remove(backup.getTitle());
}

void RemoveCommand::undo() {
    repo.add(backup);
}

UpdateCommand::UpdateCommand(Repository& repo, const Artwork& old, const Artwork& updated): repo(repo), oldArtwork(old), newArtwork(updated) {}

void UpdateCommand::execute() {
    repo.update(newArtwork);
}

void UpdateCommand::undo() {
    repo.update(oldArtwork);
}
