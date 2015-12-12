insert into User(id, name, password) values(
  1, 'admin', 'pass'
);

insert into Post(id, author_id, answer_to, post_date) values(
  1,1,1,strftime('%s','now')
);
