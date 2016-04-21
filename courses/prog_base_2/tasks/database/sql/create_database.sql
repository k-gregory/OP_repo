create table Driver(
  id integer primary key autoincrement not null,

  name text not null,
  surname text not null,

  car_manufacturer text,
  car_model text,
  car_average_speed double not null,

  km_fare double not null,

  satisfied_clients integer,
  unsatisfied_clients integer,

  hired_at datetime default (strftime('%s', 'now')) not null
);
