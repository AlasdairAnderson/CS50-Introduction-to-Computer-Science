-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Look at what crimes took place on July 28 2021 at Hunphrey Street
SELECT *
    FROM crime_scene_reports
        WHERE year = 2021
            AND month = 7
            AND day = 28
            AND street = 'Humphrey Street';
-- id = 295 | Description =  Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Look at interview records to gain evidance of what happened during the crime
SELECT id, name, transcript
    FROM  interviews
        WHERE year = 2021
            AND month = 7
            AND day = 28;
-- id = 161 | name = Ruth | Transcript = Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- id = 162 | name = Eugene | Transcript = I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- id = 163 | name = Raymond | Transcript = As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Look at bakey_bakey_security_logs for thief getting into car in the bakery parking lot and gain as much information as possible
SELECT b.minute, b.activity, b.license_plate, p.name, p.phone_number, p.passport_number
    FROM bakery_security_logs AS b
        INNER JOIN people AS p
        ON b.license_plate=p.license_plate
        WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25;

-- +--------+----------+---------------+---------+----------------+-----------------+
-- | minute | activity | license_plate |  name   |  phone_number  | passport_number |
-- +--------+----------+---------------+---------+----------------+-----------------+
-- | 16     | exit     | 5P2BI95       | Vanessa | (725) 555-4692 | 2963008352      |
-- | 18     | exit     | 94KL13X       | Bruce   | (367) 555-5533 | 5773159633      | --
-- | 18     | exit     | 6P58WS2       | Barry   | (301) 555-4174 | 7526138472      |
-- | 19     | exit     | 4328GD8       | Luca    | (389) 555-5198 | 8496433585      | ---
-- | 20     | exit     | G412CB7       | Sofia   | (130) 555-0289 | 1695452385      | --
-- | 21     | exit     | L93JTIZ       | Iman    | (829) 555-5269 | 7049073643      |
-- | 23     | exit     | 322W7JE       | Diana   | (770) 555-1861 | 3592750733      | --
-- | 23     | exit     | 0NTHK55       | Kelsey  | (499) 555-9472 | 8294398571      | --
-- +--------+----------+---------------+---------+----------------+-----------------+

-- Look at phone_calls to see if any person from who exited the car park phoned anyone
SELECT p.name, pc.duration
    FROM people AS p
        INNER JOIN phone_calls AS pc
        ON p.phone_number = pc.caller
        WHERE pc.year = 2021
        AND pc.month = 7
        AND pc.day = 28
        AND pc.duration <= 60
        AND p.license_plate IN
            (SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute >= 15
                AND minute <= 25);

-- +--------+----------+
-- |  name  | duration |
-- +--------+----------+
-- | Sofia  | 51       |
-- | Kelsey | 36       |
-- | Bruce  | 45       |
-- | Kelsey | 50       |
-- | Diana  | 49       |
-- +--------+----------+
-- names in commen are: Bruce, Sofia, Diana, Kelsey

-- see if anyone in the car park recieved calls during this time frame to see who might be the accomplise
SELECT p.name, pc.duration
    FROM people AS p
        INNER JOIN phone_calls AS pc
        WHERE pc.year = 2021
        AND pc.month = 7
        AND pc.day = 28
        AND pc.duration <= 60;

-- +------------+----------+
-- |    name    | duration |
-- +------------+----------+
-- | Jack       | 51       |
-- | Larry      | 36       |
-- | Robin      | 45       | --
-- | Luca       | 60       |
-- | Melissa    | 50       |
-- | James      | 43       |
-- | Philip     | 49       | --
-- | Jacqueline | 38       |
-- | Doris      | 55       |
-- | Anna       | 54       |
-- +------------+----------+

-- Luca recived a call and was in the car park at the same time but this call was from Kathryn who was not at the car park

-- Look at atm_transactions at Legget Street
SELECT account_number, amount, transaction_type
    FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street';

-- +----------------+--------+------------------+
-- | account_number | amount | transaction_type |
-- +----------------+--------+------------------+
-- | 28500762       | 48     | withdraw         |
-- | 28296815       | 20     | withdraw         |
-- | 76054385       | 60     | withdraw         |
-- | 49610011       | 50     | withdraw         |
-- | 16153065       | 80     | withdraw         |
-- | 86363979       | 10     | deposit          |
-- | 25506511       | 20     | withdraw         |
-- | 81061156       | 30     | withdraw         |
-- | 26013199       | 35     | withdraw         |
-- +----------------+--------+------------------+

-- Look at bank acounts link bank accounts to persons who where calling and in the car park
SELECT p.name, bc.account_number
    FROM people AS p
    INNER JOIN bank_accounts AS bc
    ON p.id = bc.person_id
        WHERE bc.account_number IN
            (SELECT account_number FROM atm_transactions
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND atm_location = 'Leggett Street')
        AND p.phone_number IN (
            SELECT caller FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration <= 60)
        AND p.license_plate IN
            (SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute >= 15
                AND minute <= 25);
-- +-------+----------------+
-- | name  | account_number |
-- +-------+----------------+
-- | Bruce | 49610011       |
-- | Diana | 26013199       |
-- +-------+----------------+

-- see if Bruce or Diana where passengers on a flight and the flight detials
SELECT f.id, a1.full_name, a2.full_name, a2.city, f.year, f.month, f.day, f.hour, f.minute, pp1.name
FROM flights as f
    INNER JOIN airports a1 ON a1.id = f.origin_airport_id
    INNER JOIN airports a2 ON a2.id = f.destination_airport_id
    INNER JOIN passengers p1 ON p1.flight_id = f.id
    INNER JOIN people pp1 ON pp1.passport_number = p1.passport_number
        WHERE pp1.name = 'Bruce'
        OR pp1.name ='Diana'
ORDER BY f.day ASC, f.hour ASC;

-- +----+-----------------------------+-----------------------------------------+---------------+------+-------+-----+------+--------+-------+
-- | id |          full_name          |                full_name                |     city      | year | month | day | hour | minute | name  |
-- +----+-----------------------------+-----------------------------------------+---------------+------+-------+-----+------+--------+-------+
-- | 36 | Fiftyville Regional Airport | LaGuardia Airport                       | New York City | 2021 | 7     | 29  | 8    | 20     | Bruce |
-- | 18 | Fiftyville Regional Airport | Logan International Airport             | Boston        | 2021 | 7     | 29  | 16   | 0      | Diana |
-- | 54 | Fiftyville Regional Airport | Dallas/Fort Worth International Airport | Dallas        | 2021 | 7     | 30  | 10   | 19     | Diana |
-- | 24 | Dubai International Airport | Fiftyville Regional Airport             | Fiftyville    | 2021 | 7     | 30  | 16   | 27     | Diana |
-- +----+-----------------------------+-----------------------------------------+---------------+------+-------+-----+------+--------+-------+

-- Look at who took the flight from the 28th onwards who also was in the car park

SELECT f.id, a1.full_name, a2.full_name, a2.city, f.day, f.hour, f.minute, pp1.name
FROM flights as f
    INNER JOIN airports a1 ON a1.id = f.origin_airport_id
    INNER JOIN airports a2 ON a2.id = f.destination_airport_id
    INNER JOIN passengers p1 ON p1.flight_id = f.id
    INNER JOIN people pp1 ON pp1.passport_number = p1.passport_number
        WHERE year = 2021
        AND month >= 7
        AND day >= 28
        AND pp1.license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25)
        AND pp1.id IN (
            SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND atm_location = 'Leggett Street'
            )
        )
        AND pp1.phone_number IN (
            SELECT caller FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration <= 60
        )
ORDER BY f.day ASC, f.hour ASC;

-- +----+-----------------------------+-----------------------------------------+---------------+-----+------+--------+-------+
-- | id |          full_name          |                full_name                |     city      | day | hour | minute | name  |
-- +----+-----------------------------+-----------------------------------------+---------------+-----+------+--------+-------+
-- | 36 | Fiftyville Regional Airport | LaGuardia Airport                       | New York City | 29  | 8    | 20     | Bruce |
-- | 18 | Fiftyville Regional Airport | Logan International Airport             | Boston        | 29  | 16   | 0      | Diana |
-- | 54 | Fiftyville Regional Airport | Dallas/Fort Worth International Airport | Dallas        | 30  | 10   | 19     | Diana |
-- | 24 | Dubai International Airport | Fiftyville Regional Airport             | Fiftyville    | 30  | 16   | 27     | Diana |
-- +----+-----------------------------+-----------------------------------------+---------------+-----+------+--------+-------+

-- The thief is Bruce due to the fact that he has on a call for the for lest than a miniute the day of the crime, He was also at the atm the day of the robery, and left the car park within 10 munties of the bulgary
-- He then left on the earliest flight the next day to New York City. Robin is his accoplice for that is the person who recived his call on the day of the robbery.


