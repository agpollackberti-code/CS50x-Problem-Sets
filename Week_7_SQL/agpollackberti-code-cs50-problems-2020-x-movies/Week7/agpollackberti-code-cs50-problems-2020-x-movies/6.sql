SELECT AVG(rating) from ratings
INNER JOIN movies on movies.id = ratings.movie_id
where movies.year = 2012