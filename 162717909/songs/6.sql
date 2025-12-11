-- SELECT id
-- FROM artists
-- WHERE name = 'Post Malone';

-- SELECT name
-- FROM songs
-- WHERE artist_id = 54;

SELECT name
FROM songs
WHERE artist_id =
(
    SELECT id
    FROM artists
    WHERE name = 'Post Malone'
);
