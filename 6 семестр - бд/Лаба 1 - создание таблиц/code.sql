create user first_user password 'first_user' login;

create type public.occupation_type_enum as enum (
'lecture', 'laboratory work', 'practical lesson', 'seminar');

create type public.position_type_enum as enum (
'docent', 'professors', 'senior lecturer', 'instructor');

create table public.group(
id bigserial primary key,
name varchar(30) not null unique,
number_of_students int not null check (number_of_students >= 1)
);

create table public.student(
id bigserial primary key,
first_name varchar(30) not null,
second_name varchar(30) not null,
middle_name varchar(30),
id_group bigint not null references public.group(id),
address varchar(100),
cource int check (cource >= 1 and cource <=5)
);


create table public.teacher(
id bigserial primary key,
first_name varchar(30) not null,
second_name varchar(30) not null,
middle_name varchar(30),
position public.position_type_enum not null default 'instructor',
phone_number varchar(30)
);


create table public.object(
	id bigserial primary key,
	objectt_name varchar(30) not null,
	hours int
);


create table public.grade(
grad int check (grad >= 1 and grad <=5),
id_student bigint not null references public.student(id),
id_object bigint not null references public.object(id)
);


grant all on schema public to first_user;






