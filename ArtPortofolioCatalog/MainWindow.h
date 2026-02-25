#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include "Controller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Controller& controller;

    QListWidget* artworkList;
    QLineEdit* titleEdit;
    QLineEdit* artistEdit;
    QSpinBox* yearEdit;
    QLineEdit* typeEdit;
    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* removeButton;
    QPushButton* undoButton;
    QPushButton* redoButton;

    QLineEdit* filterArtistEdit;
    QSpinBox* filterYearEdit;
    QPushButton* filterArtistButton;
    QPushButton* filterYearButton;
    QPushButton* clearFilterButton;

    void setupUI();
    void connectSignals();

    void applyArtistFilter();
    void applyYearFilter();
    void clearFilters();

public:
    MainWindow(Controller& controller);
    void refreshArtworkList();
    Artwork findArtworkByTitle(const QString& title);
};

#endif
