CREATE TABLE IF NOT EXISTS author (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    firstName TEXT NOT NULL,
    lastName TEXT NOT NULL,
    emailAddress TEXT,
    affiliation TEXT,
    UNIQUE(firstName, lastName)
);

CREATE TABLE IF NOT EXISTS publication (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    abstract TEXT,
    year INTEGER,
    conference TEXT,
    journal TEXT,
    publisher TEXT,
    series TEXT,
    subseries TEXT,
    volume INTEGER,
    number INTEGER,
    url TEXT,
    doi TEXT,
    isbn TEXT,
    localURL TEXT,                        -- Full path to file on the local filesystem.
    type INTEGER
);

CREATE TABLE IF NOT EXISTS publication_author (
    publicationId INTEGER,
    authorId INTEGER,
    FOREIGN KEY(publicationId) references publication(id),
    FOREIGN KEY(authorId) references author(id),
    PRIMARY KEY(publicationId, authorId)
);

--CREATE TABLE IF NOT EXISTS reference (
--    publicationId INTEGER,
--    referenceId INTEGER,
--    FOREIGN KEY(publicationId) references publication(id),
--    FOREIGN KEY(referenceId) references publication(id)
--);

INSERT INTO author(firstName, lastName, emailAddress) VALUES('Matias', 'Valdenegro', 'hunts@kde.cl');
INSERT INTO author(firstName, lastName, emailAddress) VALUES('Roy', 'Fokker', 'roy@kde.cl');

INSERT INTO publication (title, year, journal, publisher) VALUES ('Mad cow theory', 1994, 'Journal of Cow Studies', 'Springer');
INSERT INTO publication (title, year, journal, publisher) VALUES ('Mad cow: practical applications', 1997, 'Journal of Cow Studies', 'Springer');
INSERT INTO publication (title, year, journal, publisher) VALUES ('Why cows go berserk?', 2000, 'Journal of Cow Studies', 'Springer');
INSERT INTO publication (title, year, conference, journal, publisher) VALUES ('Mad max vs Mad cows', 2009, 'XXVI Conference on Mad Cow Study', 'Proceedings of the XXVI Conference on Mad Cow Study', 'Elsevier');

INSERT INTO publication_author (publicationId, authorId) VALUES (1, 1);
INSERT INTO publication_author (publicationId, authorId) VALUES (1, 2);
INSERT INTO publication_author (publicationId, authorId) VALUES (2, 1);
INSERT INTO publication_author (publicationId, authorId) VALUES (3, 1);
INSERT INTO publication_author (publicationId, authorId) VALUES (4, 2);