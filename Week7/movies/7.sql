SELECT Movies.title, Ratings.rating
FROM Ratings
JOIN Movies
    ON Ratings.movie_id = Movies.id
WHERE Movies.year = 2010
ORDER BY rating DESC, title ASC;
