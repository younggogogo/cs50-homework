-- SELECT title
-- FROM movies
-- WHERE id IN
-- (
--     SELECT movie_id
--     FROM ratings
--     WHERE movie_id IN
--     (
--         SELECT movie_id
--         FROM stars
--         WHERE person_id =
--         (
--             SELECT id
--             FROM people
--             WHERE name = 'Chadwick Boseman'
--         )
--     )
-- )
-- ORDER BY
-- (
--     SELECT rating
--     FROM ratings
--     WHERE movie_id = movies.id
-- )DESC
-- LIMIT 5;


SELECT title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN ratings ON ratings.movie_id = movieS.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5
