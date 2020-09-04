SELECT DISTINCT(name) from people
INNER JOIN stars on stars.person_id = people.id
INNER JOIN movies on movies.id = stars.movie_id
WHERE movies.year = 2004
ORDER BY people.birth