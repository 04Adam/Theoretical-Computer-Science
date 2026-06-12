--zad1
CREATE OR REPLACE FUNCTION remove_duplicates(t_name text)
RETURNS void AS $$
BEGIN
    EXECUTE format('
        DELETE FROM %I
        WHERE ctid NOT IN (
            SELECT min(ctid)
            FROM %I
            GROUP BY %I::text
        )
    ', t_name, t_name, t_name);
END;
$$ LANGUAGE plpgsql;
----
--zad2
SELECT string_to_array(trim(tab::text, '()'), ',') AS wynik 
FROM tab;
----
--zad3
CREATE OR REPLACE FUNCTION nulls(VARIADIC arr anyarray)
RETURNS int AS $$
    SELECT (count(*) - count(val))::int
    FROM unnest(arr) AS val;
$$ LANGUAGE sql;
----
--zad4
CREATE OR REPLACE FUNCTION remove_duplicates(t_name text)
RETURNS void AS $$
BEGIN
    EXECUTE format('
        DELETE FROM %I
        WHERE ctid NOT IN (
            SELECT min(ctid)
            FROM %I
            GROUP BY %I::text
        )'
        , t_name, t_name, t_name);
END;
$$ LANGUAGE plpgsql;
----
--zad5
create or replace function array_intersect(tab1 anyarray, tab2 anyarray) returns anyarray as $$
    begin 
        return array(
            select unnest(tab1) as el intersect select unnest(tab2)
            order by el
        );
    end;
$$ language plpgsql;
SELECT array_intersect(array['a','b','a','e','d'],array['a','c','d']);
----
--zad6
create or replace function array_sort(tab anyarray) returns anyarray as $$
    begin
    return array(
        select element from unnest(tab) as element order by element
    );
    end;
$$ language plpgsql;
----
--zad7
SELECT id, imie, nazwisko, numer
FROM (
    SELECT tab.*, row_number() OVER (ORDER BY ctid) AS numer
    FROM tab
) sub
WHERE (numer - 1) % 3 = 0;
----
--zad8
SELECT nazwa, rodzaj FROM zwierzeta
ORDER BY
    CASE rodzaj
        WHEN 'pies' THEN 1
        WHEN 'kot' THEN 2
        ELSE 3
    END,
    nazwa;
----
--zad9
ALTER TABLE tab
DROP CONSTRAINT tab_b_check,
ALTER COLUMN b TYPE boolean USING (b = 'tak');
----
--zad10
SELECT tablename
FROM pg_tables
WHERE schemaname = 'public';
----
--zad11
CREATE OR REPLACE FUNCTION remove_all()
RETURNS void AS $$
DECLARE
    t text;
BEGIN
    FOR t IN (SELECT tablename FROM pg_tables WHERE schemaname = 'public') LOOP
        EXECUTE format('DROP TABLE IF EXISTS public.%I CASCADE', t);
    END LOOP;
END;
$$ LANGUAGE plpgsql;
--SELECT remove_all();
----
--zad12
SELECT tablename AS nazwa_tabeli,
       pg_total_relation_size('public.' || quote_ident(tablename)) AS rozmiar
FROM pg_tables
WHERE schemaname = 'public';
----
