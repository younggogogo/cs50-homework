-- Keep a log of any SQL queries you execute as you solve the mystery.

-- look format of the tables

-- SELECT *
-- FROM
-- crime_scene_reports;

-- SELECT *
-- FROM
-- crime_scene_reports
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28;

--the id of crime is 295,
-- Humphrey Street bakery (place)
 -- TIME 10:15am
 -- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

-- SELECT *
-- FROM
-- interviews
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28;

-- ﻿--EVENT
-- -- | 161 | Ruth    Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- -- | 162 | Eugene   I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- -- | 163 | Raymond  As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--  The thief then asked the person on the other end of the phone to purchase the flight ticket.

--THE suspicious plate

-- SELECT license_plate
-- FROM
-- bakery_security_logs
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28
-- AND activity = 'exit' ;


--THE atm man in leggett street

-- SELECT *
-- FROM
-- atm_transactions
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28
-- AND atm_location = 'Leggett Street'
-- AND transaction_type = 'withdraw'

--find the suspicious man information

-- SELECT person_id
-- FROM bank_accounts
-- WHERE account_number in
-- (
--     SELECT account_number
--     FROM
--     atm_transactions
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND atm_location = 'Leggett Street'
--     AND transaction_type = 'withdraw'
-- )

--find the suspicious people information
-- SELECT *
-- FROM people
-- WHERE ID in
-- (
--     SELECT person_id
--     FROM bank_accounts
--     WHERE account_number in
--     (
--         SELECT account_number
--         FROM
--         atm_transactions
--         WHERE year = 2023
--         AND month = 7
--         AND day = 28
--         AND atm_location = 'Leggett Street'
--         AND transaction_type = 'withdraw'
--     )
-- );


--结合在那条街道和进入过停车场的人得出的可疑人物和当天打过电话的人找到犯人bruce
-- SELECT *
-- FROM people
-- WHERE ID in
-- (
--     SELECT person_id
--     FROM bank_accounts
--     WHERE account_number in
--     (
--         SELECT account_number
--         FROM
--         atm_transactions
--         WHERE year = 2023
--         AND month = 7
--         AND day = 28
--         AND atm_location = 'Leggett Street'
--         AND transaction_type = 'withdraw'
--     )
-- ) AND license_plate IN
-- (
--     SELECT license_plate
--     FROM
--     bakery_security_logs
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND activity = 'exit'
--     AND hour = 10
--     AND minute <= 25

-- )AND phone_number IN
--     (
--         SELECT caller
--         FROM
--         phone_calls
--         WHERE year = 2023
--         AND month = 7
--         AND day = 28
--         AND duration <= 60
--     )AND passport_number IN
--     (
--         SELECT passport_number
--         FROM passengers
--         WHERE flight_id IN
--         (
--             SELECT
--             id
--             FROM
--             flights
--             WHERE year = 2023
--             AND month = 7
--             AND day = 29
--             AND id = 36
--         )
--     );

--the thief is:Bruce
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |


-- SELECT receiver
-- FROM phone_calls
-- WHERE caller = '(367) 555-5533'
-- AND year = 2023
-- AND month = 7
-- AND day = 28
-- AND duration <= 60


--teammate
-- +----------------+
-- |    receiver    |
-- +----------------+
-- | (375) 555-8161 |
-- SELECT name
-- FROM people
-- WHERE phone_number = '(375) 555-8161'


SELECT city
FROM airports
WHERE id =
(
    SELECT destination_airport_id
    FROM flights
    WHERE id = 36
)
