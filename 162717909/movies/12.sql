-- SELECT title
-- FROM movies
-- WHERE id IN
-- (
--     SELECT movie_id
--     FROM stars
--     WHERE person_id IN
--     (
--         SELECT id
--         FROM people
--         WHERE name = 'Bradley Cooper'
--     )
-- )
-- AND id IN
-- (
--    SELECT movie_id
--     FROM stars
--     WHERE person_id IN
--     (
--         SELECT id
--         FROM people
--         WHERE name = 'Jennifer Lawrence'
--     )
-- )
-- SELECT title
-- FROM movies
-- JOIN stars s1 ON movies.id = s1.movie_id
-- JOIN people p1 ON p1.id = s1.person_id
-- JOIN stars s2 ON movies.id = s2.movie_id
-- JOIN people p2 ON p2.id = s2.person_id
-- WHERE (p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence')

SElECT title
FROM movies
WHERE id IN
(
    SELECT s1.movie_id
    FROM stars s1
    JOIN stars s2 ON s1.movie_id = s2.movie_id
    WHERE s1.person_id IN
    (
        SELECT id FROM people WHERE name = 'Bradley Cooper'
    )AND s2.person_id IN
    (
        SELECT id FROM people WHERE name = 'Jennifer Lawrence'
    )

)
