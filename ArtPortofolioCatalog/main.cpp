#include <QApplication>
#include "MainWindow.h"
#include "CsvRepository.h"
#include "JsonRepository.h"
#include "Controller.h"
#include "Repository.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    bool useJsonRepository = false;

    std::unique_ptr<Repository> repo;

    if (useJsonRepository) {
        repo = std::make_unique<JsonRepository>("artworks.json");
        qDebug() << "Using JsonRepository for data storage.";
    } else {
        repo = std::make_unique<CsvRepository>("artworks.csv");
        qDebug() << "Using CsvRepository for data storage.";
    }

    Controller controller(*repo);
    MainWindow mainWin(controller);
    mainWin.show();

    return app.exec();
}
