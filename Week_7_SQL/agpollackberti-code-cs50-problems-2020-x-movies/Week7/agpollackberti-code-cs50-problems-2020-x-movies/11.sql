Select title from movies
INNER JOIN stars on stars.movie_id = movies.id
INNER JOIN people on people.id = stars.person_id
INNER JOIN ratings on movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5