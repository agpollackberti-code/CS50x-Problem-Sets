SELECT movies.title from movies
INNER JOIN stars on stars.movie_id = movies.id
INNER JOIN people on people.id = stars.person_id
WHERE people.name = "Johnny Depp"
INTERSECT
SELECT movies.title from movies
INNER JOIN stars on stars.movie_id = movies.id
INNER JOIN people on people.id = stars.person_id
WHERE people.name = "Helena Bonham Carter"