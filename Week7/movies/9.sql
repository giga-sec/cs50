SELECT DISTINCT(People.name)
FROM People
JOIN Movies
    ON Movies.id = Stars.movie_id
JOIN Stars
    ON People.id = Stars.person_id
WHERE Movies.year = 2004
ORDER BY People.birth ASC;
