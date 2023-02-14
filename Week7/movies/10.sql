
SELECT DISTINCT(People.name)
FROM People
JOIN Directors
    ON Directors.person_id = People.id
JOIN Ratings
    ON Ratings.movie_id = Directors.movie_id
WHERE Ratings.rating >= 9.0;