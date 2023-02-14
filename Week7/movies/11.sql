SELECT Movies.title
FROM Movies
JOIN Stars
    ON Movies.id = Stars.movie_id
JOIN People
    ON People.id = Stars.person_id
WHERE People.name = "Chadwick Boseman"
LIMIT 5;