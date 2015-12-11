create table User(
  id rowid not null,
  password text not null,
  name text not null,
  additionalInfo text
);

create table Post(
  id rowid not null,
  author_id integer not null,
  answer_to integer,
  body text,
  attachments text,
  foreign key (author_id) references User(id),
  foreign key (answer_to) references Post(id)
);

create table Like(
  id rowid not null,
  liker_id integer not null,
  post_id integer not null,
  foreign key (liker_id) references User(id),
  foreign key (post_id) references Post(id)
);

create table Friends(
  user_a integer not null,
  user_b integer not null,
  foreign key (user_a) references User(id),
  foreign key (user_b) references User(id)
);

create table Message(
  id rowid not null,
  sender_id integer not null,
  receiver_id integer not null,
  attachments text,
  foreign key(sender_id) references User(id),
  foreign key(receiver_id) references User(id)
);
