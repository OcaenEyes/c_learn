drop database if exists `testtest`;

create database `testtest`;

use `testtest`;

drop table if exists `users`;

create table `users` (
    `id` int(11) not null auto_increment,
    `username` varchar(50) not null,
    `password` varchar(50) not null,
    `email` varchar(255) not null,
    `created_at` datetime default null,
    `updated_at` datetime default null,
    primary key (`id`)
) engine = innodb auto_increment = 1 default charset = utf8mb4;