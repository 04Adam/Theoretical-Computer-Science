--zad1
create or replace function sprawdz_pesel() returns trigger as $$
begin
  if length(trim(new.pesel)) != 11 then
    raise exception 'Niepoprawny PESEL';
  end if;
  return new;
end;
$$ language plpgsql;

create trigger sprawdz_pesel_trg
before insert or update on pacjenci
for each row execute procedure sprawdz_pesel();

----
--zad2
create or replace function uzupelnij_czas_wizyty() returns trigger as $$
begin
  if new.data_zakonczenia is null then
    new.data_zakonczenia := new.data_rozpoczecia + interval '30 minutes';
  end if;
  return new;
end;
$$ language plpgsql;

create trigger uzupelnij_czas_wizyty_trg
before insert on wizyty
for each row execute procedure uzupelnij_czas_wizyty();

----
--zad3
create or replace function chron_nowe_wizyty() returns trigger as $$
begin
  if old.data_rozpoczecia >= (now() - interval '5 years') then
    return null;
  end if;
  return old;
end;
$$ language plpgsql;

create trigger chron_nowe_wizyty_trg
before delete on wizyty
for each row execute procedure chron_nowe_wizyty();

----
--zad4
create or replace function waliduj_wizyte() returns trigger as $$
declare
  liczba_kolizji integer;
begin
  if (new.data_zakonczenia - new.data_rozpoczecia) > interval '1 hour' then
    return null;
  end if;

  select count(*) into liczba_kolizji
  from wizyty
  where lekarz = new.lekarz
    and data_rozpoczecia < new.data_zakonczenia
    and data_zakonczenia > new.data_rozpoczecia;

  if liczba_kolizji > 0 then
    return null;
  end if;

  return new;
end;
$$ language plpgsql;

create trigger waliduj_wizyte_trg
before insert on wizyty
for each row execute procedure waliduj_wizyte();

----
--zad5
create table lekarze_prowadzacy (
  pesel char(11) not null references pacjenci(pesel),
  lekarz integer not null references lekarze(id),
  primary key (pesel, lekarz)
);

create or replace function przypisz_lekarza_rodzinnego() returns trigger as $$
declare
  wybrany_lekarz integer;
begin
  select l.id into wybrany_lekarz
  from lekarze l
  join specjalizacje s on l.id = s.id_lekarza
  where s.specjalizacja = 'Medycyna rodzinna'
  order by (
    select count(*) 
    from lekarze_prowadzacy lp 
    where lp.lekarz = l.id
  ) asc, l.id asc
  limit 1;

  if wybrany_lekarz is not null then
    insert into lekarze_prowadzacy (pesel, lekarz)
    values (new.pesel, wybrany_lekarz);
  end if;

  return new;
end;
$$ language plpgsql;

create trigger przypisz_lekarza_rodzinnego_trg
after insert on pacjenci
for each row execute procedure przypisz_lekarza_rodzinnego();
----
--zad6
create view pediatrzy as
select l.id, l.imie, l.nazwisko
from lekarze l
join specjalizacje s on l.id = s.id_lekarza
where s.specjalizacja = 'Pediatria';

create rule dodaj_pediatre as 
on insert to pediatrzy
do instead (
  insert into lekarze (id, imie, nazwisko) 
  values (new.id, new.imie, new.nazwisko);
  
  insert into specjalizacje (id_lekarza, specjalizacja) 
  values (new.id, 'Pediatria');
);
----
--zad7
create view chirurdzy as
select l.id, l.imie, l.nazwisko
from lekarze l
join specjalizacje s on l.id = s.id_lekarza
where s.specjalizacja = 'Chirurgia';

create rule chron_widok_chirurdzy as 
on delete to chirurdzy
do instead nothing;
----
--zad8
create rule chron_tabela_chirurdzy as 
on delete to lekarze
where old.id in (
  select id_lekarza 
  from specjalizacje 
  where specjalizacja = 'Chirurgia'
)
do instead nothing;
----
--zad9
create rule usun_kaskadowo_wizyty as 
on delete to pacjenci
do also
delete from wizyty where pacjent = old.pesel;

----
--zad10
create view terminarz as
select 
  cast(null as char(11)) as pacjent,
  cast(null as varchar(80)) as specjalista,
  cast(null as timestamp) as termin_od,
  cast(null as timestamp) as termin_do
where false;

create rule umawiaj_pacjenta as 
on insert to terminarz
do instead
insert into wizyty (lekarz, pacjent, data_rozpoczecia, data_zakonczenia)
select 
  l.id, 
  new.pacjent, 
  new.termin_od, 
  new.termin_do
from lekarze l
join specjalizacje s on l.id = s.id_lekarza
where s.specjalizacja = new.specjalista
  and not exists (
    select 1 
    from wizyty w
    where w.lekarz = l.id
      and w.data_rozpoczecia < new.termin_do
      and w.data_zakonczenia > new.termin_od
  )
order by l.id asc
limit 1;
----
