SELECT movies.title, ratings.rating from ratings
INNER JOIN movies on movies.id = ratings.movie_id
where movies.year = 2010
order by ratings.rating desc, movies.title ASC