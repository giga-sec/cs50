SELECT Movies.title FROM Movies
JOIN Stars
    ON Stars.movie_id = Movies.id
JOIN People
    ON People.id = Stars.person_id
WHERE People.name in ("Johnny Depp", "Helena Bonham Carter")
GROUP BY Movies.title
HAVING COUNT(Movies.title) = 2;
