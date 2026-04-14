--zad1
select * from ksiazki where autor = 'J.R.R. Tolkien';
----
--zad2
select kategorie.nazwa, count(id_ksiazki) from ksiazki
join kategorie using(id_kategorii)
group by kategorie.nazwa;
----
--zad3
select distinct tytul, autor from ksiazki
join egzemplarze using(id_ksiazki)
join wypozyczenia on wypozyczenia.id_egzemplarza = egzemplarze.id_egzemplarza
where data_oddania is not null
order by tytul, autor;
----
--zad4
-----
