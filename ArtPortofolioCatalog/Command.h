#ifndef COMMAND_H
#define COMMAND_H

#include "Repository.h"
#include "Artwork.h"
#include <memory>

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class AddCommand : public Command {
    Repository& repo;
    Artwork artwork;
public:
    AddCommand(Repository& repo, const Artwork& artwork);
    void execute() override;
    void undo() override;
};

class RemoveCommand : public Command {
    Repository& repo;
    Artwork backup;
public:
    RemoveCommand(Repository& repo, const QString& title);
    void execute() override;
    void undo() override;
};

class UpdateCommand : public Command {
    Repository& repo;
    Artwork oldArtwork;
    Artwork newArtwork;
public:
    UpdateCommand(Repository& repo, const Artwork& old, const Artwork& updated);
    void execute() override;
    void undo() override;
};

#endif
