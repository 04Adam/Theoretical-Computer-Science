--zad1
select nazwa from produkty where id_kategoria = (select id_kategoria from produkty where nazwa = 'Piórnik duży');
----
--zad2
select nazwa
from produkty
where id_kategoria in (
    select id_kategoria
    from kategorie
    where nadkategoria is not null
);
----
--zad3a
SELECT nazwa 
FROM kategorie 
WHERE id_kategoria IN (
    SELECT id_kategoria 
    FROM produkty 
    GROUP BY id_kategoria 
    HAVING COUNT(kod_produktu) >= 3
)
order by nazwa;
----
--zad3b
SELECT
    (SELECT nazwa FROM kategorie WHERE kategorie.id_kategoria = produkty.id_kategoria)
FROM produkty
GROUP BY id_kategoria
HAVING COUNT(kod_produktu) >= 3;
----
--zad3c
select kategorie.nazwa from produkty join kategorie using(id_kategoria) group by kategorie.nazwa having count(kod_produktu)>2 order by kategorie.nazwa;
----
--zad4
select * from rabaty 
where data_do - data_od = (
    select max(data_do - data_od) 
    from rabaty
);
----
--zad5
select * from kategorie k1 where vat < any(select vat from kategorie k2 where k1.id_kategoria = k2.nadkategoria);
----
--zad6
select id_zamowienia
from produkty_zamowienia
group by id_zamowienia
having sum(ilosc) >= all (
    select sum(ilosc)
    from produkty_zamowienia
    group by id_zamowienia
);
----
--zad7 
select p.nazwa, podz.liczba
from produkty p
join (
    select kod_produktu, count(*) as liczba
    from historia_cen
    where extract(month from data_wprowadzenia) = 4
    group by kod_produktu
    having count(*) >= 2
) podz on p.kod_produktu = podz.kod_produktu;
----
--zad8
with recursive hierarchia as (
    select id_kategoria as id_startowe, nazwa as kategoria_startowa, nadkategoria, id_kategoria, nazwa
    from kategorie
    union all
    select h.id_startowe, h.kategoria_startowa, k.nadkategoria, k.id_kategoria, k.nazwa
    from hierarchia h
    join kategorie k on h.nadkategoria = k.id_kategoria
)
select kategoria_startowa, nazwa
from hierarchia
where nadkategoria is null;
----
--zad9
select
    p.nazwa,
    round(hc.cena_netto * (1 + k.vat / 100.0), 2)
from produkty p
join kategorie k on p.id_kategoria = k.id_kategoria
join historia_cen hc on p.kod_produktu = hc.kod_produktu
where hc.data_wprowadzenia = (
    select max(data_wprowadzenia)
    from historia_cen hc2
    where hc2.kod_produktu = p.kod_produktu
);
----
--zad10
select
    p.nazwa,
    round(hc.cena_netto * (1 + k.vat / 100.0) - coalesce(sum(r.znizka), 0), 2)
from produkty p
join kategorie k on p.id_kategoria = k.id_kategoria
join historia_cen hc on p.kod_produktu = hc.kod_produktu
left join rabaty_produkty rp on p.kod_produktu = rp.id_produktu
left join rabaty r on rp.id_rabatu = r.id_rabatu
                  and r.data_od <= hc.data_wprowadzenia
                  and (r.data_do is null or r.data_do >= hc.data_wprowadzenia)
where hc.data_wprowadzenia = (
    select max(data_wprowadzenia)
    from historia_cen hc2
    where hc2.kod_produktu = p.kod_produktu
)
group by p.kod_produktu, p.nazwa, hc.cena_netto, k.vat;
----
--zad11
select
    z.id_zamowienia,
    round(sum(pz.ilosc * hc.cena_netto * (1 + k.vat / 100.0)), 2)
from zamowienia z
join produkty_zamowienia pz on z.id_zamowienia = pz.id_zamowienia
join produkty p on pz.produkt = p.kod_produktu
join kategorie k on p.id_kategoria = k.id_kategoria
join historia_cen hc on p.kod_produktu = hc.kod_produktu
where hc.data_wprowadzenia = (
    select max(data_wprowadzenia)
    from historia_cen hc2
    where hc2.kod_produktu = p.kod_produktu
      and hc2.data_wprowadzenia <= z.data_zlozenia
)
group by z.id_zamowienia;
----
--zad12
with wartosc_bazowa as (
    select z.id_zamowienia, z.data_zlozenia, pz.produkt, pz.ilosc,
           hc.cena_netto * (1 + k.vat / 100.0) as cena_j
    from zamowienia z
    join produkty_zamowienia pz on z.id_zamowienia = pz.id_zamowienia
    join produkty p on pz.produkt = p.kod_produktu
    join kategorie k on p.id_kategoria = k.id_kategoria
    join historia_cen hc on p.kod_produktu = hc.kod_produktu
    where hc.data_wprowadzenia = (
        select max(data_wprowadzenia) from historia_cen hc2
        where hc2.kod_produktu = p.kod_produktu and hc2.data_wprowadzenia <= z.data_zlozenia
    )
),
rabaty_produktowe as (
    select wb.id_zamowienia, coalesce(sum(wb.ilosc * r.znizka), 0) as s_rp
    from wartosc_bazowa wb
    join rabaty_produkty rp on wb.produkt = rp.id_produktu and wb.ilosc >= rp.min_ilosc
    join rabaty r on rp.id_rabatu = r.id_rabatu
                 and r.data_od <= wb.data_zlozenia
                 and (r.data_do is null or r.data_do >= wb.data_zlozenia)
    group by wb.id_zamowienia
),
rabaty_klienckie as (
    select z.id_zamowienia, coalesce(sum(r.znizka), 0) as s_rk
    from zamowienia z
    join rabaty_klienci rk on z.id_zamowienia = rk.id_zamowienia or z.id_klienta = rk.id_klienta
    join rabaty r on rk.id_rabatu = r.id_rabatu
                 and r.data_od <= z.data_zlozenia
                 and (r.data_do is null or r.data_do >= z.data_zlozenia)
    group by z.id_zamowienia
)
select
    wb.id_zamowienia,
    round(sum(wb.ilosc * wb.cena_j) - coalesce(max(rp.s_rp), 0) - coalesce(max(rkl.s_rk), 0), 2)
from wartosc_bazowa wb
left join rabaty_produktowe rp on wb.id_zamowienia = rp.id_zamowienia
left join rabaty_klienckie rkl on wb.id_zamowienia = rkl.id_zamowienia
group by wb.id_zamowienia;
----
