IF DB_ID('ArtMuseum') IS NOT NULL
BEGIN
    ALTER DATABASE ArtMuseum SET SINGLE_USER WITH ROLLBACK IMMEDIATE;
    DROP DATABASE ArtMuseum;
END
GO

CREATE DATABASE ArtMuseum;
GO
USE ArtMuseum;
GO

-- Lista de tari
CREATE TABLE Country (
    CountryID INT IDENTITY PRIMARY KEY,
    Name VARCHAR(100) NOT NULL UNIQUE
);

-- Lista de orase (fiecare oras apartine unei tari)
CREATE TABLE City (
    CityID INT IDENTITY PRIMARY KEY,
    CountryID INT NOT NULL,
    Name VARCHAR(100) NOT NULL,
    CONSTRAINT FK_City_Country FOREIGN KEY (CountryID) REFERENCES Country(CountryID)
);

-- Muzee (fiecare muzeu se afla intr-un oras)
CREATE TABLE Museum (
    MuseumID INT IDENTITY PRIMARY KEY,
    CityID INT NOT NULL,
    Name VARCHAR(150) NOT NULL,
    FoundedYear INT,
    CONSTRAINT FK_Museum_City FOREIGN KEY (CityID) REFERENCES City(CityID)
);

-- Sali din muzee (cu etaj si nume)
CREATE TABLE Room (
    RoomID INT IDENTITY PRIMARY KEY,
    MuseumID INT NOT NULL,
    Name VARCHAR(100) NOT NULL,
    Floor INT,
    CONSTRAINT FK_Room_Museum FOREIGN KEY (MuseumID) REFERENCES Museum(MuseumID)
);

-- Curatori (angajati la muzee)
CREATE TABLE Curator (
    CuratorID INT IDENTITY PRIMARY KEY,
    MuseumID INT NOT NULL,
    FullName VARCHAR(150) NOT NULL,
    Email VARCHAR(100),
    CONSTRAINT FK_Curator_Museum FOREIGN KEY (MuseumID) REFERENCES Museum(MuseumID)
);

-- Artisti
CREATE TABLE Artist (
    ArtistID INT IDENTITY PRIMARY KEY,
    FullName VARCHAR(150) NOT NULL,
    Country VARCHAR(100),
    BirthYear INT,
    DeathYear INT
);

-- Stiluri de arta (ex: Renastere, Realism)
CREATE TABLE ArtStyle (
    StyleID INT IDENTITY PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Period VARCHAR(100)
);

-- Opere de arta (fiecare are artist si stil)
CREATE TABLE Artwork (
    ArtworkID INT IDENTITY PRIMARY KEY,
    ArtistID INT NOT NULL,
    StyleID INT,
    Title VARCHAR(200) NOT NULL,
    YearCreated INT,
    Value DECIMAL(10,2),
    CONSTRAINT FK_Artwork_Artist FOREIGN KEY (ArtistID) REFERENCES Artist(ArtistID),
    CONSTRAINT FK_Artwork_Style FOREIGN KEY (StyleID) REFERENCES ArtStyle(StyleID)
);

-- Expozitii (organizate in muzee, cu curator)
CREATE TABLE Exhibition (
    ExhibitionID INT IDENTITY PRIMARY KEY,
    MuseumID INT NOT NULL,
    CuratorID INT,
    Name VARCHAR(150) NOT NULL,
    StartDate DATE,
    EndDate DATE,
    CONSTRAINT FK_Exhibition_Museum FOREIGN KEY (MuseumID) REFERENCES Museum(MuseumID),
    CONSTRAINT FK_Exhibition_Curator FOREIGN KEY (CuratorID) REFERENCES Curator(CuratorID)
);

-- Legatura intre opere si expozitii (many-to-many)
CREATE TABLE ArtworkExhibition (
    ArtworkID INT NOT NULL,
    ExhibitionID INT NOT NULL,
    PRIMARY KEY (ArtworkID, ExhibitionID),
    CONSTRAINT FK_AE_Artwork FOREIGN KEY (ArtworkID) REFERENCES Artwork(ArtworkID),
    CONSTRAINT FK_AE_Exhibition FOREIGN KEY (ExhibitionID) REFERENCES Exhibition(ExhibitionID)
);

-- 1. INSERARE DATE
-- (Adaugam informatii initiale in tabele)
INSERT INTO Country (Name) VALUES ('Italy'), ('France'), ('Romania');
INSERT INTO City (CountryID, Name) VALUES 
(1, 'Florence'), (2, 'Paris'), (3, 'Bucharest');

INSERT INTO Museum (CityID, Name, FoundedYear) VALUES 
(1, 'Uffizi Gallery', 1581),
(2, 'Louvre Museum', 1793),
(3, 'National Art Museum', 1950);

INSERT INTO Room (MuseumID, Name, Floor) VALUES 
(1, 'Renaissance Hall', 1),
(2, 'Impressionism Room', 2),
(3, 'Modern Art Hall', 1);

INSERT INTO Curator (MuseumID, FullName, Email) VALUES
(2, 'Marie Dupont', 'marie@louvre.fr'),
(3, 'Andrei Ionescu', 'andrei@artmuseum.ro');

INSERT INTO Artist (FullName, Country, BirthYear, DeathYear) VALUES
('Leonardo da Vinci', 'Italy', 1452, 1519),
('Claude Monet', 'France', 1840, 1926),
('Nicolae Grigorescu', 'Romania', 1838, 1907);

INSERT INTO ArtStyle (Name, Period) VALUES 
('Renaissance', '1400-1600'),
('Impressionism', '1800-1900'),
('Realism', '1800-1900');

INSERT INTO Artwork (ArtistID, StyleID, Title, YearCreated, Value) VALUES
(1, 1, 'Mona Lisa', 1503, 1000000),
(2, 2, 'Water Lilies', 1906, 500000),
(3, 3, 'Peasant Girl', 1885, 150000);

INSERT INTO Exhibition (MuseumID, CuratorID, Name, StartDate, EndDate) VALUES
(2, 1, 'Masters of Painting', '2025-05-01', '2025-08-31'),
(3, 2, 'Romanian Classics', '2025-06-15', '2025-09-30');

INSERT INTO ArtworkExhibition (ArtworkID, ExhibitionID) VALUES
(1, 1), (2, 1), (3, 2);

-- Inseram si alte date (Spania)
INSERT INTO Country (Name) VALUES ('Spain');
INSERT INTO City (CountryID, Name) VALUES (4, 'Madrid');
INSERT INTO Museum (CityID, Name, FoundedYear) VALUES (4, 'Prado Museum', 1819);
INSERT INTO Artist (FullName, Country, BirthYear, DeathYear) VALUES ('Francisco Goya', 'Spain', 1746, 1828);

-- 2. UPDATE
-- (Schimba valoarea operelor vechi cu 10% in plus)
UPDATE Artwork
SET Value = Value * 1.10
WHERE YearCreated < 1900 AND Value IS NOT NULL;

-- 3. DELETE
-- (Sterge salile de la etajul 1 din orase care se termina in 't')
DELETE FROM Room
WHERE Floor = 1 AND MuseumID IN (
    SELECT m.MuseumID FROM Museum m
    JOIN City c ON m.CityID = c.CityID
    WHERE c.Name LIKE '%t'
);

-- 4. SELECT QUERIES
-- (Cautari si afisari de informatii)

-- a) UNION / INTERSECT / EXCEPT
-- UNION = combina 2 liste fara duplicate
SELECT ci.Name FROM City ci
UNION
SELECT co.Name FROM Country co;

-- INTERSECT = elemente comune intre doua liste
SELECT ar.Country FROM Artist ar
INTERSECT
SELECT co.Name FROM Country co;

-- EXCEPT = elemente care sunt doar in prima lista
SELECT co.Name FROM Country co
EXCEPT
SELECT co2.Name FROM City ci
JOIN Country co2 ON ci.CountryID = co2.CountryID;

-- b) JOIN-uri (combinam tabele)
-- INNER JOIN = doar datele care se potrivesc in toate tabelele
SELECT a.Title, ar.FullName AS Artist, s.Name AS Style, m.Name AS Museum
FROM Artwork a
INNER JOIN Artist ar ON a.ArtistID = ar.ArtistID
INNER JOIN ArtStyle s ON a.StyleID = s.StyleID
INNER JOIN ArtworkExhibition ae ON a.ArtworkID = ae.ArtworkID
INNER JOIN Exhibition e ON ae.ExhibitionID = e.ExhibitionID
INNER JOIN Museum m ON e.MuseumID = m.MuseumID;

-- LEFT JOIN = toate muzeele, chiar daca nu au curator
SELECT m.Name AS Museum, c.FullName AS Curator
FROM Museum m
LEFT JOIN Curator c ON m.MuseumID = c.MuseumID;

-- RIGHT JOIN = toti curatorii, chiar daca muzeul lipseste
SELECT m.Name AS Museum, c.FullName AS Curator
FROM Museum m
RIGHT JOIN Curator c ON m.MuseumID = c.MuseumID;

-- FULL JOIN = toate orasele si toate muzeele
SELECT ci.Name AS City, m.Name AS Museum
FROM City ci
FULL JOIN Museum m ON ci.CityID = m.CityID;

-- c) IN si EXISTS
-- IN = cauta opere din Paris
SELECT a.Title
FROM Artwork a
WHERE a.ArtworkID IN (
    SELECT ae.ArtworkID
    FROM ArtworkExhibition ae
    JOIN Exhibition e ON ae.ExhibitionID = e.ExhibitionID
    JOIN Museum m ON e.MuseumID = m.MuseumID
    JOIN City c ON m.CityID = c.CityID
    WHERE c.Name = 'Paris'
);

-- EXISTS = artisti care au opere expuse
SELECT ar.FullName
FROM Artist ar
WHERE EXISTS (
    SELECT 1
    FROM Artwork aw
    JOIN ArtworkExhibition ae ON aw.ArtworkID = ae.ArtworkID
    WHERE aw.ArtistID = ar.ArtistID
);

-- d) Subquery in FROM
-- Stiluri cu valoare medie mai mare decat media generala
SELECT st.Name AS StyleName, s.AvgValue
FROM (
    SELECT StyleID, AVG(Value) AS AvgValue
    FROM Artwork
    GROUP BY StyleID
) s
JOIN ArtStyle st ON s.StyleID = st.StyleID
WHERE s.AvgValue > (SELECT AVG(Value) FROM Artwork);

-- e) GROUP BY si HAVING
-- GROUP BY = grupeaza datele
-- HAVING = filtreaza grupurile
SELECT ar.FullName, COUNT(a.ArtworkID) AS ArtworkCount
FROM Artist ar
JOIN Artwork a ON ar.ArtistID = a.ArtistID
GROUP BY ar.FullName;

SELECT s.Name AS Style, AVG(a.Value) AS AvgValue
FROM ArtStyle s
JOIN Artwork a ON s.StyleID = a.StyleID
GROUP BY s.Name
HAVING AVG(a.Value) > 200000;

SELECT m.Name AS Museum, SUM(a.Value) AS TotalValue
FROM Museum m
JOIN Exhibition e ON m.MuseumID = e.MuseumID
JOIN ArtworkExhibition ae ON e.ExhibitionID = ae.ExhibitionID
JOIN Artwork a ON ae.ArtworkID = a.ArtworkID
GROUP BY m.Name
HAVING SUM(a.Value) > (SELECT AVG(Value) FROM Artwork);

-- 7. DISTINCT, TOP, ORDER BY

-- DISTINCT = elimina duplicate
SELECT DISTINCT Country FROM Artist;

-- TOP = afiseaza doar prima linie
SELECT TOP 1 * FROM Artwork ORDER BY Value DESC;

-- ORDER BY = sorteaza rezultatele
SELECT * FROM Artwork ORDER BY Value DESC;
SELECT * FROM Museum ORDER BY FoundedYear;

GO
--UPDATE / DELETE

UPDATE Artwork
SET Value = Value * 1.10
WHERE YearCreated < 1900;

DELETE FROM Room
WHERE Floor = 1;

--SELECTURI

SELECT DISTINCT Country FROM Artist;
SELECT TOP 1 * FROM Artwork ORDER BY Value DESC;
SELECT * FROM Museum ORDER BY FoundedYear;



--TABEL VERSIONARE
-- Tabel in care se pastreaza versiunea curenta a bazei de date
CREATE TABLE DatabaseVersion (
    VersionNr INT NOT NULL
);

-- Setam versiunea initiala a bazei de date la 0
INSERT INTO DatabaseVersion VALUES (0);



--PROCEDURI VERSIONARE

-- VERSION 1

-- ADD COLUMN
-- Adaugam o noua coloana "Phone" in tabelul Curator
IF OBJECT_ID('SetVersion1','P') IS NOT NULL DROP PROCEDURE SetVersion1;
GO
CREATE PROCEDURE SetVersion1 AS
BEGIN
    ALTER TABLE Curator ADD Phone VARCHAR(20); --add
    UPDATE DatabaseVersion SET VersionNr = 1;
END;
GO

-- REMOVE COLUMN
-- Stergem coloana "Phone" din tabelul Curator
IF OBJECT_ID('SetVersion0_From1','P') IS NOT NULL DROP PROCEDURE SetVersion0_From1;
GO
CREATE PROCEDURE SetVersion0_From1 AS
BEGIN
    ALTER TABLE Curator DROP COLUMN Phone; --remove
    UPDATE DatabaseVersion SET VersionNr = 0; --update
END;
GO

-- VERSION 2

-- ADD DEFAULT CONSTRAINT
-- Adaugam o valoare implicita de 1000 pentru coloana Value din tabelul Artwork
IF OBJECT_ID('SetVersion2','P') IS NOT NULL DROP PROCEDURE SetVersion2;
GO
CREATE PROCEDURE SetVersion2 AS
BEGIN
    ALTER TABLE Artwork
    ADD CONSTRAINT DF_Artwork_Value DEFAULT 1000 FOR Value;
    UPDATE DatabaseVersion SET VersionNr = 2;
END;
GO

-- REMOVE DEFAULT CONSTRAINT
-- Stergem constrangerea DEFAULT de pe coloana Value
IF OBJECT_ID('SetVersion1_From2','P') IS NOT NULL DROP PROCEDURE SetVersion1_From2;
GO
CREATE PROCEDURE SetVersion1_From2 AS
BEGIN
    ALTER TABLE Artwork DROP CONSTRAINT DF_Artwork_Value;
    UPDATE DatabaseVersion SET VersionNr = 1;
END;
GO

-- VERSION 3

-- CREATE TABLE
-- Se creeaza un nou tabel numit Sponsor in baza de date
IF OBJECT_ID('SetVersion3','P') IS NOT NULL DROP PROCEDURE SetVersion3;
GO
CREATE PROCEDURE SetVersion3 AS
BEGIN
    CREATE TABLE Sponsor (
        SponsorID INT IDENTITY PRIMARY KEY,
        Name VARCHAR(100)
    );
    UPDATE DatabaseVersion SET VersionNr = 3;
END;
GO

-- DROP TABLE
-- Se sterge tabelul Sponsor din baza de date
IF OBJECT_ID('SetVersion2_From3','P') IS NOT NULL DROP PROCEDURE SetVersion2_From3;
GO
CREATE PROCEDURE SetVersion2_From3 AS
BEGIN
    DROP TABLE Sponsor;
    UPDATE DatabaseVersion SET VersionNr = 2;
END;
GO

-- VERSION 4

-- ADD FOREIGN KEY
-- Adaugam o cheie straina intre Sponsor si Museum
IF OBJECT_ID('SetVersion4','P') IS NOT NULL DROP PROCEDURE SetVersion4;
GO
CREATE PROCEDURE SetVersion4 AS
BEGIN
    ALTER TABLE Sponsor ADD MuseumID INT;
    ALTER TABLE Sponsor
    ADD CONSTRAINT FK_Sponsor_Museum FOREIGN KEY (MuseumID) REFERENCES Museum(MuseumID);
    UPDATE DatabaseVersion SET VersionNr = 4;
END;
GO

-- REMOVE FOREIGN KEY
-- Eliminam cheia straina dintre Sponsor si Museum
IF OBJECT_ID('SetVersion3_From4','P') IS NOT NULL DROP PROCEDURE SetVersion3_From4;
GO
CREATE PROCEDURE SetVersion3_From4 AS
BEGIN
    ALTER TABLE Sponsor DROP CONSTRAINT FK_Sponsor_Museum;
    UPDATE DatabaseVersion SET VersionNr = 3;
END;
GO



--PROCEDURA PRINCIPALA
-- Procedura principala care primeste ca parametru o versiune si aduce baza de date la versiunea respectiva (UP sau DOWN)
IF OBJECT_ID('GoToVersion','P') IS NOT NULL
    DROP PROCEDURE GoToVersion;
GO

CREATE PROCEDURE GoToVersion (@TargetVersion INT)
AS
BEGIN
    DECLARE @CurrentVersion INT;
    DECLARE @MaxVersion INT = 4;  -- numarul MAXIM de versiuni definite

    --VALIDARE PARAMETRU
    IF @TargetVersion < 0 OR @TargetVersion > @MaxVersion
    BEGIN
        RAISERROR(
            'Versiune invalida. Versiuni permise intre 0 si %d.',
            16, 1, @MaxVersion
        );
        RETURN;
    END

    --CITIM VERSIUNEA CURENTA
    SELECT @CurrentVersion = VersionNr
    FROM DatabaseVersion;

    --UPGRADE
    WHILE @CurrentVersion < @TargetVersion
    BEGIN
        IF @CurrentVersion = 0 EXEC SetVersion1;
        ELSE IF @CurrentVersion = 1 EXEC SetVersion2;
        ELSE IF @CurrentVersion = 2 EXEC SetVersion3;
        ELSE IF @CurrentVersion = 3 EXEC SetVersion4;

        SELECT @CurrentVersion = VersionNr FROM DatabaseVersion;
    END

    --DOWNGRADE
    WHILE @CurrentVersion > @TargetVersion
    BEGIN
        IF @CurrentVersion = 4 EXEC SetVersion3_From4;
        ELSE IF @CurrentVersion = 3 EXEC SetVersion2_From3;
        ELSE IF @CurrentVersion = 2 EXEC SetVersion1_From2;
        ELSE IF @CurrentVersion = 1 EXEC SetVersion0_From1;

        SELECT @CurrentVersion = VersionNr FROM DatabaseVersion;
    END
END;
GO

EXEC GoToVersion 4;
SELECT * FROM DatabaseVersion;

EXEC GoToVersion 1;
SELECT * FROM DatabaseVersion;

GO
--USER DEFINED FUNCTION Valideaza anul unei opere de arta
IF OBJECT_ID('dbo.fn_CheckYear','FN') IS NOT NULL
    DROP FUNCTION dbo.fn_CheckYear;
GO

CREATE FUNCTION dbo.fn_CheckYear (@Year INT)
RETURNS BIT
AS
BEGIN
    IF @Year >= 1000 AND @Year <= YEAR(GETDATE())
        RETURN 1;
    RETURN 0;
END;
GO


--STORED PROCEDURE INSERARE IN 2 TABELE (Artwork + ArtworkExhibition)
IF OBJECT_ID('AddArtworkWithExhibition','P') IS NOT NULL
    DROP PROCEDURE AddArtworkWithExhibition;
GO

CREATE PROCEDURE AddArtworkWithExhibition
    @ArtistID INT,
    @StyleID INT,
    @Title VARCHAR(200),
    @YearCreated INT,
    @Value DECIMAL(10,2),
    @ExhibitionID INT
AS
BEGIN
    -- Validare folosind functia definita de utilizator
    IF dbo.fn_CheckYear(@YearCreated) = 0
    BEGIN
        RAISERROR('Anul creatiei este invalid', 16, 1);
        RETURN;
    END

    -- Inserare opera de arta
    INSERT INTO Artwork (ArtistID, StyleID, Title, YearCreated, Value)
    VALUES (@ArtistID, @StyleID, @Title, @YearCreated, @Value);

    -- Legare opera de expozitie
    INSERT INTO ArtworkExhibition (ArtworkID, ExhibitionID)
    VALUES (SCOPE_IDENTITY(), @ExhibitionID);
END;
GO

-- Inseram opera
EXEC AddArtworkWithExhibition
    @ArtistID = 1,
    @StyleID = 1,
    @Title = 'Test Procedura Artwork',
    @YearCreated = 2020,
    @Value = 3000,
    @ExhibitionID = 2;

-- Verificam daca opera a fost inserata
SELECT * FROM Artwork
WHERE Title = 'Test Procedura Artwork';

-- Verificam daca exista legatura cu expozitia
SELECT * FROM ArtworkExhibition
WHERE ArtworkID = (
    SELECT ArtworkID FROM Artwork
    WHERE Title = 'Test Procedura Artwork'
);


--VIEW EXTRAGE DATE DIN MAI MULT DE 3 TABELE
IF OBJECT_ID('View_ArtworkDetails','V') IS NOT NULL
    DROP VIEW View_ArtworkDetails;
GO

CREATE VIEW View_ArtworkDetails
AS
SELECT
    a.Title,
    ar.FullName AS Artist,
    s.Name AS ArtStyle,
    m.Name AS Museum
FROM Artwork a
JOIN Artist ar ON a.ArtistID = ar.ArtistID
JOIN ArtStyle s ON a.StyleID = s.StyleID
JOIN ArtworkExhibition ae ON a.ArtworkID = ae.ArtworkID
JOIN Exhibition e ON ae.ExhibitionID = e.ExhibitionID
JOIN Museum m ON e.MuseumID = m.MuseumID;
GO

-- Executie SELECT pe View (Punctul b)
SELECT * FROM View_ArtworkDetails;


--LOG TABLE PENTRU TRIGGER
IF OBJECT_ID('AuditLog','U') IS NOT NULL
    DROP TABLE AuditLog;
GO

CREATE TABLE AuditLog (
    LogID INT IDENTITY PRIMARY KEY,
    TableName VARCHAR(50),
    OperationType VARCHAR(10),
    OperationDate DATETIME,
    AffectedRows INT
);
GO


--TRIGGER INSERT / UPDATE / DELETE
-- LOG TABLE
IF OBJECT_ID('Logs','U') IS NOT NULL
    DROP TABLE Logs;
GO

CREATE TABLE Logs (
    lid INT IDENTITY PRIMARY KEY,
    TriggerDate DATETIME NOT NULL,         -- Data și ora declarației
    TriggerType VARCHAR(10) NOT NULL,      -- INSERT / UPDATE / DELETE
    NameAffectedTable VARCHAR(50) NOT NULL, -- Numele tabelei
    NoAMDRows INT NOT NULL                 -- Numărul de rânduri adăugate/modificate/șterse
);
GO


-- TRIGGER INSERT / UPDATE / DELETE
IF OBJECT_ID('AuditLog','U') IS NOT NULL DROP TABLE AuditLog;
IF OBJECT_ID('Logs','U') IS NOT NULL DROP TABLE Logs;
IF OBJECT_ID('trg_Artwork_Log', 'TR') IS NOT NULL DROP TRIGGER trg_Artwork_Log;
IF OBJECT_ID('trg_Artwork_Audit', 'TR') IS NOT NULL DROP TRIGGER trg_Artwork_Audit;
GO

-- 1. TABELA DE LOG (Punctul c)
IF OBJECT_ID('DatabaseLogs', 'U') IS NOT NULL
    DROP TABLE DatabaseLogs;
GO

CREATE TABLE DatabaseLogs (
    LogID INT IDENTITY PRIMARY KEY,
    LogDate DATETIME,
    TriggerType VARCHAR(10),
    TableName VARCHAR(50),
    AffectedRows INT
);
GO

-- 2. TRIGGER PE TABELA Artwork (INSERT/UPDATE/DELETE)
CREATE TRIGGER trg_Artwork_Log
ON Artwork
AFTER INSERT, UPDATE, DELETE
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @AffectedRows_Count INT;

    -- INSERT
    IF EXISTS (SELECT 1 FROM inserted)
       AND NOT EXISTS (SELECT 1 FROM deleted)
    BEGIN
        SELECT @AffectedRows_Count = COUNT(*) FROM inserted;
        INSERT INTO DatabaseLogs (LogDate, TriggerType, TableName, AffectedRows)
        VALUES (GETDATE(), 'INSERT', 'Artwork', @AffectedRows_Count);
    END

    -- DELETE
    IF EXISTS (SELECT 1 FROM deleted)
       AND NOT EXISTS (SELECT 1 FROM inserted)
    BEGIN
        SELECT @AffectedRows_Count = COUNT(*) FROM deleted;
        INSERT INTO DatabaseLogs (LogDate, TriggerType, TableName, AffectedRows)
        VALUES (GETDATE(), 'DELETE', 'Artwork', @AffectedRows_Count);
    END

    -- UPDATE
    IF EXISTS (SELECT 1 FROM inserted)
       AND EXISTS (SELECT 1 FROM deleted)
    BEGIN
        SELECT @AffectedRows_Count = COUNT(*) FROM inserted; 
        INSERT INTO DatabaseLogs (LogDate, TriggerType, TableName, AffectedRows)
        VALUES (GETDATE(), 'UPDATE', 'Artwork', @AffectedRows_Count);
    END
END
GO

-- Test 1: UPDATE
UPDATE Artwork SET Value = Value * 1.05;

-- Test 2: INSERT
INSERT INTO Artwork (ArtistID, StyleID, Title, YearCreated, Value)
VALUES (1, 1, 'Test Log Insert', 2025, 100.00);

-- Test 3: DELETE
DELETE FROM ArtworkExhibition WHERE ArtworkID = (SELECT ArtworkID FROM Artwork WHERE Title = 'Test Log Insert');
DELETE FROM Artwork WHERE Title = 'Test Log Insert';


-- VERIFICAREA LOG-URILOR
SELECT * FROM DatabaseLogs;


--INDEX
IF EXISTS (
    SELECT name FROM sys.indexes
    WHERE name = 'IDX_Artwork_Year'
)
DROP INDEX IDX_Artwork_Year ON Artwork;
GO

CREATE NONCLUSTERED INDEX IDX_Artwork_Year
ON Artwork (YearCreated);
GO


--QUERY PENTRU EXECUTION PLAN (index seek / scan, order by)
SELECT *
FROM Artwork
WHERE YearCreated < 1900
ORDER BY Value DESC;
GO