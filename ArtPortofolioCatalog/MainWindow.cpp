#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(Controller& controller) : controller(controller) {
    setWindowTitle("Art Portfolio Catalog");
    resize(800, 600);
    setupUI();
    connectSignals();
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    artworkList = new QListWidget(this);
    mainLayout->addWidget(artworkList);

    QFormLayout* formLayout = new QFormLayout();

    titleEdit = new QLineEdit(this);
    artistEdit = new QLineEdit(this);
    yearEdit = new QSpinBox(this);
    yearEdit->setRange(1000, 2100);
    typeEdit = new QLineEdit(this);

    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Artist:", artistEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Type:", typeEdit);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* crudButtonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add", this);
    updateButton = new QPushButton("Update", this);
    removeButton = new QPushButton("Remove", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);

    crudButtonLayout->addWidget(addButton);
    crudButtonLayout->addWidget(updateButton);
    crudButtonLayout->addWidget(removeButton);
    crudButtonLayout->addWidget(undoButton);
    crudButtonLayout->addWidget(redoButton);

    mainLayout->addLayout(crudButtonLayout);

    QHBoxLayout* filterLayout = new QHBoxLayout();
    QLabel* filterByArtistLabel = new QLabel("Filter by Artist:", this);
    filterArtistEdit = new QLineEdit(this);
    filterArtistEdit->setPlaceholderText("Enter artist name");
    filterArtistButton = new QPushButton("Filter Artist", this);

    QLabel* filterByYearLabel = new QLabel("Filter by Year:", this);
    filterYearEdit = new QSpinBox(this);
    filterYearEdit->setRange(0, 9999);
    filterYearEdit->setSpecialValueText("Any");
    filterYearEdit->setValue(0);
    filterYearButton = new QPushButton("Filter Year", this);

    clearFilterButton = new QPushButton("Clear Filters", this);

    filterLayout->addWidget(filterByArtistLabel);
    filterLayout->addWidget(filterArtistEdit);
    filterLayout->addWidget(filterArtistButton);
    filterLayout->addSpacing(20);
    filterLayout->addWidget(filterByYearLabel);
    filterLayout->addWidget(filterYearEdit);
    filterLayout->addWidget(filterYearButton);
    filterLayout->addStretch();
    filterLayout->addWidget(clearFilterButton);

    mainLayout->addLayout(filterLayout);

    setCentralWidget(centralWidget);
    refreshArtworkList();
}

void MainWindow::connectSignals() {
    connect(addButton, &QPushButton::clicked, this, [this]() {
        Artwork artwork(
            titleEdit->text(),
            artistEdit->text(),
            yearEdit->value(),
            typeEdit->text()
            );
        controller.addArtwork(artwork);
        refreshArtworkList();
    });

    connect(updateButton, &QPushButton::clicked, this, [this]() {
        auto selected = artworkList->currentItem();
        if (selected) {
            QString oldTitle = selected->text().split(" - ")[0];
            Artwork oldArt = findArtworkByTitle(oldTitle);
            Artwork newArt(
                titleEdit->text(),
                artistEdit->text(),
                yearEdit->value(),
                typeEdit->text()
                );
            controller.updateArtwork(oldArt, newArt);
            refreshArtworkList();
        } else {
            QMessageBox::warning(this, "Update Error", "Please select an artwork to update.");
        }
    });

    connect(removeButton, &QPushButton::clicked, this, [this]() {
        auto selected = artworkList->currentItem();
        if (selected) {
            QString title = selected->text().split(" - ")[0];
            controller.removeArtwork(title);
            refreshArtworkList();
        } else {
            QMessageBox::warning(this, "Remove Error", "Please select an artwork to remove.");
        }
    });

    connect(undoButton, &QPushButton::clicked, this, [this]() {
        controller.undo();
        refreshArtworkList();
    });

    connect(redoButton, &QPushButton::clicked, this, [this]() {
        controller.redo();
        refreshArtworkList();
    });

    connect(artworkList, &QListWidget::itemSelectionChanged, this, [this]() {
        auto selected = artworkList->currentItem();
        if (selected) {
            QString title = selected->text().split(" - ")[0];
            Artwork art = findArtworkByTitle(title);
            titleEdit->setText(art.getTitle());
            artistEdit->setText(art.getArtist());
            yearEdit->setValue(art.getYear());
            typeEdit->setText(art.getType());
        }
    });

    connect(filterArtistButton, &QPushButton::clicked, this, &MainWindow::applyArtistFilter);
    connect(filterYearButton, &QPushButton::clicked, this, &MainWindow::applyYearFilter);
    connect(clearFilterButton, &QPushButton::clicked, this, &MainWindow::clearFilters);
}

void MainWindow::refreshArtworkList() {
    artworkList->clear();
    auto artworks = controller.getAllArtworks();
    for (const auto& artwork : artworks) {
        artworkList->addItem(
            artwork.getTitle() + " - " +
            artwork.getArtist() + " (" +
            QString::number(artwork.getYear()) + ") - " +
            artwork.getType()
            );
    }
}

void MainWindow::applyArtistFilter() {
    artworkList->clear();
    QString artist = filterArtistEdit->text();
    if (artist.isEmpty()) {
        QMessageBox::information(this, "Filter", "Please enter an artist name to filter.");
        refreshArtworkList();
        return;
    }
    std::vector<Artwork> filteredArtworks = controller.filterByArtist(artist);
    for (const auto& artwork : filteredArtworks) {
        artworkList->addItem(
            artwork.getTitle() + " - " +
            artwork.getArtist() + " (" +
            QString::number(artwork.getYear()) + ") - " +
            artwork.getType()
            );
    }
}

void MainWindow::applyYearFilter() {
    artworkList->clear();
    int year = filterYearEdit->value();
    if (year == 0 && filterYearEdit->specialValueText() == "Any") {
        QMessageBox::information(this, "Filter", "Please enter a valid year (or use 'Any' by setting to 0) to filter.");
        refreshArtworkList();
        return;
    }
    std::vector<Artwork> filteredArtworks = controller.filterByYear(year);
    for (const auto& artwork : filteredArtworks) {
        artworkList->addItem(
            artwork.getTitle() + " - " +
            artwork.getArtist() + " (" +
            QString::number(artwork.getYear()) + ") - " +
            artwork.getType()
            );
    }
}

void MainWindow::clearFilters() {
    filterArtistEdit->clear();
    filterYearEdit->setValue(0);
    refreshArtworkList();
}

Artwork MainWindow::findArtworkByTitle(const QString& title) {
    auto artworks = controller.getAllArtworks();
    for (const auto& artwork : artworks) {
        if (artwork.getTitle() == title) {
            return artwork;
        }
    }
    return Artwork("", "", 0, "");
}
