--ZAD1
select * from kierowcy;
----
--ZAD2
select * from wykroczenia
order by kwota, nazwa;
----
--ZAD3
select imie, nazwisko from kierowcy;
----
--ZAD4
select distinct imie, nazwisko from kierowcy
order by nazwisko, imie desc;
----
--ZAD5
SELECT
    imie,
    nazwisko,
    wynagrodzenie * 12 AS roczne_wynagrodzenie
FROM straznicy;
----
--ZAD6
SELECT
    imie,
    nazwisko,
    (wynagrodzenie + COALESCE(premia, 0)) * 12 AS roczne_wynagrodzenie
FROM straznicy;
----
--ZAD7
select * from straznicy where wynagrodzenie <= 8000 and wynagrodzenie >= 6000;
----
--ZAD8
select * from straznicy where wynagrodzenie >= 6000 and id_przelozonego is not null;
----
--ZAD9
SELECT *
FROM wykroczenia
WHERE punkty <= 10 OR punkty IS NULL;
----
--ZAD10
SELECT *
FROM kierowcy
WHERE data_od > '2000-12-31';
----
--ZAD11
select * from wykroczenia where nazwa like 'Przekroczenie prędkości%';
----
--ZAD12
SELECT *
FROM kierowcy
WHERE adres LIKE '%Grudziądz%' AND data_do IS NULL;
----
--ZAD13
select imie, nazwisko, adres from kierowcy where data_od <= '2012-01-01' and (data_do is null or data_do >= '2012-01-01');
----
--ZAD14
SELECT
    imie || ' ' || LEFT(nazwisko, 1) || '.' AS kierowca_bez_uprawnien
FROM kierowcy
WHERE data_do < CURRENT_DATE;
----
--ZAD15
select nazwisko || ' pracuje jako ' || lower(stanowisko) || ' i zarabia ' || wynagrodzenie as "STRAŻNICY MIEJSCY" from straznicy
order by wynagrodzenie desc;
----
--ZAD16
SELECT
    nazwisko,
    ROUND(wynagrodzenie * 1.15)
FROM straznicy
ORDER BY 1;
----
--ZAD17
SELECT
    RPAD(nazwisko, 20, '.') || LPAD(stanowisko, 20, '.') AS "nazwisko i stanowisko"
FROM straznicy
ORDER BY id;
----
--ZAD18
SELECT
    UPPER(LEFT(stanowisko, 2)) || id AS "wygenerowany kod",
    id AS "id strażnika",
    nazwisko,
    stanowisko
FROM straznicy;
----
--ZAD19
SELECT
    nazwisko,
    REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(
        nazwisko,
        'K', 'X'),
        'k', 'X'),
        'L', 'X'),
        'l', 'X'),
        'M', 'X'),
        'm', 'X') AS "zmienione nazwisko"
FROM straznicy;
----
--ZAD20
SELECT
    imie || ' ' || nazwisko AS "imię i nazwisko",
    TO_CHAR(data_od, 'Month, DD YYYY') AS "uzyskanie uprawnień"
FROM kierowcy
WHERE
    (data_do IS NOT NULL AND data_do - data_od < 5 * 365)
    OR (data_do IS NULL AND CURRENT_DATE - data_od < 5 * 365)
ORDER BY
    COALESCE(data_do, CURRENT_DATE) - data_od ASC;
----
--ZAD21
SELECT
    id,
    CASE
        WHEN kwota * 2 < 400 THEN 'mniej'
        WHEN kwota * 2 = 400 THEN 'równa'
        WHEN kwota * 2 > 400 THEN 'więcej'
    END
FROM wykroczenia
WHERE recydywa = true;
----
--ZAD22
select imie, nazwisko, premia from straznicy
order by premia desc nulls last, id;
----
--ZAD23
SELECT
    imie,
    nazwisko,
    pesel
FROM straznicy
ORDER BY
    CASE
        WHEN SUBSTRING(pesel, 3, 2)::int > 12
        THEN (SUBSTRING(pesel, 1, 2)::int + 2000)::text
        ELSE (SUBSTRING(pesel, 1, 2)::int + 1900)::text
    END,
    CASE
        WHEN SUBSTRING(pesel, 3, 2)::int > 12
        THEN (SUBSTRING(pesel, 3, 2)::int - 20)::int
        ELSE SUBSTRING(pesel, 3, 2)::int
    END,
    SUBSTRING(pesel, 5, 2)::int
LIMIT 5;
----
--ZAD24
SELECT
    imie,
    nazwisko,
    pesel
FROM kierowcy

INTERSECT

SELECT
    imie,
    nazwisko,
    pesel
FROM straznicy
ORDER BY 1, 2, 3;
----
