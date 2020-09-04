SELECT name from people
INNER JOIN stars on stars.person_id = people.id
INNER JOIN movies on movies.id = stars.movie_id
WHERE movies.title = "Toy Story"