SELECT DISTINCT People.name FROM People
JOIN Stars
    ON Stars.person_id = People.id
JOIN Movies
    ON Stars.movie_id = Movies.id
WHERE Movies.id IN
    (
        SELECT Movies.Id
        FROM People
        JOIN Stars
            ON Stars.person_id = People.id
        JOIN Movies
            ON Stars.movie_id = Movies.id
        WHERE People.name = "Kevin Bacon" AND People.birth = "1958"
    )
    AND People.name != "Kevin Bacon"