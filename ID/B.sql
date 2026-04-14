--ZAD1
select MIN(round(cena_netto+cena_netto*vat*0.01,2)) as min,
MAX(round(cena_netto+cena_netto*vat*0.01,2)) as max
from produkty;
----
--ZAD2
SELECT 
    zamowienia.id_zamowienia,
    sum(produkty_zamowienia.ile)
FROM zamowienia
JOIN produkty_zamowienia ON zamowienia.id_zamowienia = produkty_zamowienia.id_zamowienia
GROUP BY zamowienia.id_zamowienia;
----
--ZAD3
select produkt from produkty_zamowienia
group by produkt
having sum(ile)>39
order by produkt asc;
----
--ZAD4
select kategoria, round(AVG(waga),2) from produkty
group by kategoria
having count(kategoria)>1;
----
--ZAD5
select kategoria, MAX(cena_netto), MIN(cena_netto), MAX(cena_netto)-MIN(cena_netto) from produkty
group by kategoria;
----
--ZAD6
select kategoria, count(kod_produktu) as "liczba produktów" from produkty
where vat <> 18
group by kategoria;
----
--ZAD7
select count(kod_produktu) from produkty
where waga<1000;
----
--ZAD8
select sum(cena_netto) from produkty
having max(cena_netto)>300 or max(cena_netto)=300;
----
--ZAD9
select case when count(id_zamowienia) = count(distinct adres_dostawy) then 'TAK'
else 'NIE'
end
from zamowienia;
----
--ZAD10
select id_klienta from zamowienia
group by id_klienta
having count(id_klienta)>1;
----
--ZAD11
select kategoria from produkty
where rabat is not null
group by kategoria;
----
--ZAD12
select kategoria from produkty
where vat = 8
group by kategoria
having min(rabat)>0;
----
--ZAD13
SELECT
    kategoria,
    ROUND(COALESCE(VAR_SAMP(cena_netto), 0)::numeric, 2) AS wariancja,
    ROUND(COALESCE(STDDEV_SAMP(cena_netto), 0)::numeric, 2) AS "odchylenie standardowe"
FROM produkty
GROUP BY kategoria;
----
--ZAD14
select count(kod_produktu) from produkty
where nazwa like 'Długopis%' or nazwa like 'Ołówki%';
----
--ZAD15a
select array_agg(numer_telefonu::text) as "lista telefonów" from klienci
where numer_telefonu is not null;
----
--ZAD15b
select array_agg(numer_telefonu::text order by numer_telefonu asc) as "lista telefonów" from klienci
where numer_telefonu is not null;
----
--ZAD16
select produkt,count(id_zamowienia) from produkty_zamowienia
group by produkt
order by count(id_zamowienia) desc, produkt asc;
----
--ZAD17
SELECT
    CASE
        WHEN nip IS NULL THEN 'Brak'
        ELSE 'Podany'
    END AS "NIP",
    COUNT(*) AS "liczba klientów"
FROM klienci
group by 1
order by 1 asc;
----
--ZAD18
select count(*) from klienci
where email like '%onet.eu%';
----
--ZAD19
SELECT
    to_char(data_zlozenia, 'Month') AS "miesiąc",
    COUNT(*) AS "liczba zamówień"
FROM zamowienia
GROUP BY 1
ORDER BY 1 ASC;
----

