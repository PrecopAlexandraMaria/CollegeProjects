#include "gtest/gtest.h"
#include "Artwork.h"
#include "CsvRepository.h"
#include "Controller.h"
#include "Command.h"
#include <QFile>
#include <QString>

void printArtworksForDebug(const std::string& title, const std::vector<Artwork>& artworks) {
    std::cout << "--- " << title << " ---" << std::endl;
    if (artworks.empty()) {
        std::cout << "  (Empty)" << std::endl;
    } else {
        for (const auto& art : artworks) {
            std::cout << "  Title: " << art.getTitle().toStdString()
            << ", Artist: " << art.getArtist().toStdString()
            << ", Year: " << art.getYear()
            << ", Type: " << art.getType().toStdString() << std::endl;
        }
    }
    std::cout << "--------------------" << std::endl;
}

class ControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
        testFilename = "test_artworks.csv";
        repo = std::make_unique<CsvRepository>(testFilename);
        controller = std::make_unique<Controller>(*repo);

        std::vector<Artwork> currentArtworks = repo->getAll();
        for (const auto& art : currentArtworks) {
            repo->remove(art.getTitle());
        }
        ASSERT_TRUE(controller->getAllArtworks().empty()) << "Repository not empty after SetUp clear!";
    }

    void TearDown() override {
        QFile file(testFilename);
        if (file.exists()) {
            file.remove();
        }
    }

    QString testFilename;
    std::unique_ptr<CsvRepository> repo;
    std::unique_ptr<Controller> controller;
};


TEST_F(ControllerTest, AddArtwork) {
    Artwork art1("Starry Night", "Vincent van Gogh", 1889, "Painting");
    controller->addArtwork(art1);

    std::vector<Artwork> artworks = controller->getAllArtworks();
    ASSERT_EQ(artworks.size(), 1);
    EXPECT_EQ(artworks[0].getTitle(), "Starry Night");
    EXPECT_EQ(artworks[0].getArtist(), "Vincent van Gogh");
}

TEST_F(ControllerTest, RemoveArtwork) {
    Artwork art1("Starry Night", "Vincent van Gogh", 1889, "Painting");
    controller->addArtwork(art1);
    ASSERT_EQ(controller->getAllArtworks().size(), 1);

    controller->removeArtwork("Starry Night");
    EXPECT_TRUE(controller->getAllArtworks().empty());
}

TEST_F(ControllerTest, UpdateArtwork) {
    Artwork originalArt("Mona Lisa", "Leonardo da Vinci", 1503, "Painting");
    controller->addArtwork(originalArt);
    ASSERT_EQ(controller->getAllArtworks().size(), 1);

    Artwork updatedArt("Mona Lisa", "Leonardo da Vinci", 1503, "Oil Painting");
    controller->updateArtwork(originalArt, updatedArt);

    std::vector<Artwork> artworks = controller->getAllArtworks();
    ASSERT_EQ(artworks.size(), 1);
    EXPECT_EQ(artworks[0].getType(), "Oil Painting");
}

TEST_F(ControllerTest, UndoRedoAdd) {
    Artwork art1("Starry Night", "Vincent van Gogh", 1889, "Painting");
    controller->addArtwork(art1);
    ASSERT_EQ(controller->getAllArtworks().size(), 1);

    controller->undo(); // Undo add
    EXPECT_TRUE(controller->getAllArtworks().empty());

    controller->redo(); // Redo add
    ASSERT_EQ(controller->getAllArtworks().size(), 1);
    EXPECT_EQ(controller->getAllArtworks()[0].getTitle(), "Starry Night");
}

TEST_F(ControllerTest, UndoRedoRemove) {
    Artwork art1("Starry Night", "Vincent van Gogh", 1889, "Painting");
    controller->addArtwork(art1);
    ASSERT_EQ(controller->getAllArtworks().size(), 1);

    controller->removeArtwork("Starry Night");
    EXPECT_TRUE(controller->getAllArtworks().empty());

    controller->undo(); // Undo remove
    ASSERT_EQ(controller->getAllArtworks().size(), 1);
    EXPECT_EQ(controller->getAllArtworks()[0].getTitle(), "Starry Night");

    controller->redo(); // Redo remove
    EXPECT_TRUE(controller->getAllArtworks().empty());
}

TEST_F(ControllerTest, UndoRedoUpdate) {
    Artwork originalArt("Mona Lisa", "Leonardo da Vinci", 1503, "Painting");
    controller->addArtwork(originalArt);
    ASSERT_EQ(controller->getAllArtworks().size(), 1);

    Artwork updatedArt("Mona Lisa", "Leonardo da Vinci", 1503, "Oil Painting");
    controller->updateArtwork(originalArt, updatedArt);
    ASSERT_EQ(controller->getAllArtworks()[0].getType(), "Oil Painting");

    controller->undo(); // Undo update
    EXPECT_EQ(controller->getAllArtworks()[0].getType(), "Painting");

    controller->redo(); // Redo update
    EXPECT_EQ(controller->getAllArtworks()[0].getType(), "Oil Painting");
}

TEST_F(ControllerTest, UndoRedoClearsRedoStackOnNewAction) {
    Artwork art1("Starry Night", "Vincent van Gogh", 1889, "Painting");
    controller->addArtwork(art1);
    ASSERT_EQ(controller->getAllArtworks().size(), 1);

    controller->undo();
    EXPECT_TRUE(controller->getAllArtworks().empty());

    Artwork art2("The Scream", "Edvard Munch", 1893, "Painting");
    controller->addArtwork(art2);
    ASSERT_EQ(controller->getAllArtworks().size(), 1);
    EXPECT_EQ(controller->getAllArtworks()[0].getTitle(), "The Scream");

    controller->redo();
    ASSERT_EQ(controller->getAllArtworks().size(), 1);
    EXPECT_EQ(controller->getAllArtworks()[0].getTitle(), "The Scream");
}


TEST_F(ControllerTest, FilterByArtist) {
    controller->addArtwork(Artwork("Starry Night", "Vincent van Gogh", 1889, "Painting"));
    controller->addArtwork(Artwork("The Potato Eaters", "Vincent van Gogh", 1885, "Painting"));
    controller->addArtwork(Artwork("Guernica", "Pablo Picasso", 1937, "Painting"));

    std::vector<Artwork> filtered = controller->filterByArtist("Vincent van Gogh");
    ASSERT_EQ(filtered.size(), 2);
    EXPECT_EQ(filtered[0].getArtist(), "Vincent van Gogh");
    EXPECT_EQ(filtered[1].getArtist(), "Vincent van Gogh");

    std::vector<Artwork> noResult = controller->filterByArtist("Non Existent Artist");
    EXPECT_TRUE(noResult.empty());
}

TEST_F(ControllerTest, FilterByYear) {
    controller->addArtwork(Artwork("Starry Night", "Vincent van Gogh", 1889, "Painting"));
    controller->addArtwork(Artwork("Mona Lisa", "Leonardo da Vinci", 1503, "Painting"));
    controller->addArtwork(Artwork("The Last Supper", "Leonardo da Vinci", 1495, "Painting"));

    std::vector<Artwork> filtered = controller->filterByYear(1503);
    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].getTitle(), "Mona Lisa");

    std::vector<Artwork> noResult = controller->filterByYear(2023);
    EXPECT_TRUE(noResult.empty());
}

TEST_F(ControllerTest, CsvRepositoryLoadSave) {
    repo->add(Artwork("Test Art 1", "Test Artist 1", 2000, "Test Type 1"));
    repo->add(Artwork("Test Art 2", "Test Artist 2", 2001, "Test Type 2"));

    std::vector<Artwork> loadedArtworks = repo->getAll();
    ASSERT_EQ(loadedArtworks.size(), 2);
    EXPECT_EQ(loadedArtworks[0].getTitle(), "Test Art 1");
    EXPECT_EQ(loadedArtworks[1].getArtist(), "Test Artist 2");
}
