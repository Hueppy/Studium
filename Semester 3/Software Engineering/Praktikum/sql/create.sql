drop database pfotenfreunde;

create database pfotenfreunde;
use pfotenfreunde;

create table address (
       id     int         not null auto_increment,
       street varchar(50) not null,
       zip    varchar(10) not null,
       city   varchar(60) not null,

       constraint pk_address primary key (id)
);

create table login (
       email         varchar(50)  not null,
       password_hash varchar(256) not null,
       role          int          not null,

       constraint pk_login      primary key (email)
);

create table user (
       id           int          not null auto_increment,
       name         varchar(50)  not null,
       telephone    varchar(30)  not null,
       email        varchar(50)  not null,
       address_id   int          not null,
       active       bit          not null default true,
       locked_until datetime     not null,
       status       int          not null,

       constraint pk_user         primary key (id),
       constraint fk_user_address foreign key (address_id) references address (id),
       constraint fk_user_login   foreign key (email)      references login (email),
       constraint uc_user_login   unique (email)
);

create table institution (
       id       int          not null,
       homepage varchar(100),

       constraint pk_institution      primary key (id),
       constraint fk_institution_user foreign key (id) references user (id)
);

create table person (
       id             int         not null,
       surname        varchar(50) not null,
       age            int         not null,
       sex            varchar(20) not null,
       institution_id int         null,

       constraint pk_person             primary key (id),
       constraint fk_person_user        foreign key (id)             references user (id),
       constraint fk_person_institution foreign key (institution_id) references institution (id)
);

create table friend_request (
       id          int      not null auto_increment,
       send_at     datetime not null,
       seen_at     datetime not null,
       sender_id   int      not null,
       receiver_id int      not null,
       state       int      not null,

       constraint pk_friendrequest primary key (id),
       constraint fk_friendrequest_sender   foreign key (sender_id)   references user (id),
       constraint fk_friendrequest_receiver foreign key (receiver_id) references user (id)
);

create table rating (
       id        int not null auto_increment,
       type      int not null,
       user_id   int not null,
       sender_id int not null,

       constraint pk_rating        primary key (id),
       constraint fk_rating_user   foreign key (user_id)   references user (id),
       constraint fk_rating_sender foreign key (sender_id) references user (id)
);

create table report (
       id         int      not null auto_increment,
       comment    text     not null,
       type       int      not null,
       state      int      not null,
       send_at    datetime not null,
       updated_at datetime not null,
       user_id    int      not null,
       sender_id  int      not null,

       constraint pk_report        primary key (id),
       constraint fk_report_user   foreign key (user_id)   references user (id),
       constraint fk_report_sender foreign key (sender_id) references user (id)
);

create table chronicle (
       id int not null auto_increment,

       constraint pk_chronicle primary key (id)
);

create table post (
       id           int      not null auto_increment,
       posted_at    datetime not null,
       message      text     not null,
       user_id      int      not null,
       chronicle_id int      not null,

       constraint pk_post           primary key (id),
       constraint fk_post_user      foreign key (user_id)      references user (id),
       constraint fk_post_chronicle foreign key (chronicle_id) references chronicle (id)
);

create table pet (
       id          int         not null auto_increment,
       name        varchar(50) not null,
       description text,
       owner_id    int         not null,
       species     int         not null,

       constraint pk_pet         primary key (id),
       constraint fk_pet_owner   foreign key (owner_id) references person (id)
);

create table preference (
       id     int         not null auto_increment,
       name   varchar(30) not null,
       value  varchar(60) not null,
       pet_id int         not null,

       constraint pk_preference     primary key (id),
       constraint fk_preference_pet foreign key (pet_id) references pet (id)
);

create table attribute (
       id     int         not null auto_increment,
       name   varchar(30) not null,
       value  varchar(60) not null,
       pet_id int         not null,

       constraint pk_attribute     primary key (id),
       constraint fk_attribute_pet foreign key (pet_id) references pet (id)
);

create table chatroom (
       id         int      not null auto_increment,
       started_at datetime not null,

       constraint pk_chatroom primary key (id)
);

create table chatroom_user (
       id      int not null,
       user_id int not null,

       constraint pk_chatroom_user          primary key (id, user_id),
       constraint fk_chatroom_user_chatroom foreign key (id)           references chatroom (id),
       constraint fk_chatroom_user_user     foreign key (user_id)      references user (id)
);

create table message (
       id          int      not null auto_increment,
       send_at     datetime not null,
       seen_at     datetime not null,
       message     text     not null,
       sender_id   int      not null,
       chatroom_id int      not null,

       constraint pk_message          primary key (id),
       constraint fk_message_user     foreign key (sender_id)   references user (id),
       constraint fk_message_chatroom foreign key (chatroom_id) references chatroom (id)
);

create table picture (
       id          int          not null auto_increment,
       uploader_id int          not null,
       upload_date datetime     not null,
       data        mediumblob   not null,

       constraint pk_picture      primary key (id),
       constraint fk_picture_user foreign key (uploader_id) references user (id)
);

create table picture_pet (
       id     int not null,
       pet_id int not null,

       constraint pk_picture_pet         primary key (id),
       constraint fk_picture_pet_picture foreign key (id)     references picture (id),
       constraint fk_picture_pet_pet     foreign key (pet_id) references pet (id)
);

create table picture_user (
       id      int not null,
       user_id int not null,

       constraint pk_picture_user         primary key (id),
       constraint fk_picture_user_picture foreign key (id)      references picture (id),
       constraint fk_picture_user_user    foreign key (user_id) references user (id)
);

create table picture_post (
       id      int not null,
       post_id int not null,

       constraint pk_picture_post         primary key (id),
       constraint fk_picture_post_picture foreign key (id)      references picture (id),
       constraint fk_picture_post_post    foreign key (post_id) references post (id)
);
