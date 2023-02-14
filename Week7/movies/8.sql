SELECT People.name
FROM People
JOIN Stars
    ON Movies.id = Stars.movie_id
JOIN Movies
    ON People.id = Stars.person_id
WHERE Movies.title = "Toy Story";