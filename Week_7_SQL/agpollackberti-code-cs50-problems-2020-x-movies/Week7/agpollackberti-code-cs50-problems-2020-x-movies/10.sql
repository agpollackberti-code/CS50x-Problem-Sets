SELECT name from people
INNER JOIN movies on movies.id=directors.movie_id
INNER JOIN ratings on ratings.movie_id=movies.id
INNER JOIN directors on people.id=directors.person_id
WHERE ratings.rating >= 9.0