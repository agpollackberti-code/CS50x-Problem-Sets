Select distinct(name) from stars
INNER JOIN people on people.id = stars.person_id
WHERE stars.movie_id in
(SELECT movie_id from movies
INNER JOIN stars on stars.movie_id = movies.id
INNER JOIN people on people.id = stars.person_id
WHERE name = "Kevin Bacon"
AND people.birth = 1958)
AND NOT name = "Kevin Bacon"