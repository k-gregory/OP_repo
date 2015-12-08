create table User(
  id integer primary key autoincrement not null,
  password text not null,
  additionalInfo text
);

create table Post(
  id integer primary key autoincrement not null,
  author_id integer not null,
  answer_to integer not null,
  body text,
  attachments text,
  foreign key (author_id) references User(id),
  foreign key (answer_to) references Post(id)
);

create table Friends(
  user_a integer not null,
  user_b integer not null,
  foreign key (user_a) references User(id),
  foreign key (user_b) references User(id)
);

create table Message(
  id integer primary key autoincrement not null,
  sender_id integer not null,
  receiver_id integer not null,
  attachments text,
  foreign key(sender_id) references User(id),
  foreign key(receiver_id) references User(id)
);
