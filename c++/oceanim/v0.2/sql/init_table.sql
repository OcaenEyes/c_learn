-- DROP DATABASE IF EXISTS oceanim;
-- CREATE DATABASE oceanim;
USE oceanim;
-- COMMENT  用户表
DROP TABLE IF EXISTS user;
CREATE TABLE user(
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(50) NOT NULL,
    state ENUM('online', 'offline') DEFAULT 'offline',
    registime VARCHAR(50)
);
-- COMMENT 好友请求表
DROP TABLE IF EXISTS friendreq;
CREATE TABLE friendreq(
    id INT AUTO_INCREMENT PRIMARY KEY,
    fromid INT NOT NULL,
    toid INT NOT NULL,
    state ENUM('noop', 'send', 'accept', 'refuse', 'ignore') DEFAULT 'noop'
);
-- COMMENT 好友表
DROP TABLE IF EXISTS friend;
CREATE TABLE friend(
    userid INT NOT NULL,
    friendid INT NOT NULL,
    PRIMARY KEY(userid, friendid)
);
-- COMMENT 群组表
DROP TABLE IF EXISTS allgroup;
CREATE TABLE allgroup(
    id INT AUTO_INCREMENT PRIMARY KEY,
    groupname VARCHAR(50) NOT NULL UNIQUE,
    groupdesc VARCHAR(200) DEFAULT '..'
);
-- COMMENT 群组成员表
DROP TABLE IF EXISTS groupuser;
CREATE TABLE groupuser(
    groupid INT NOT NULL,
    userid INT NOT NULL,
    grouprole ENUM('creator', 'admin', 'normal') DEFAULT 'normal',
    PRIMARY KEY(groupid, userid)
);
-- COMMENT 单聊消息表
DROP TABLE IF EXISTS onechat;
CREATE TABLE onechat(
    id INT AUTO_INCREMENT PRIMARY KEY,
    fromid INT NOT NULL,
    toid INT NOT NULL,
    msgtype ENUM('text', 'audio', 'video', 'image') DEFAULT 'text',
    readtype ENUM('read', 'noread') DEFAULT 'noread',
    message VARCHAR(500) NOT NULL,
    sendtime VARCHAR(50)
);
-- COMMENT 群聊消息表
DROP TABLE IF EXISTS groupchat;
CREATE TABLE groupchat(
    id INT AUTO_INCREMENT PRIMARY KEY,
    fromid INT NOT NULL,
    groupid INT NOT NULL,
    msgtype ENUM('text', 'audio', 'video', 'image') DEFAULT 'text',
    -- readtype ENUM('read', 'noread') DEFAULT 'noread',
    message VARCHAR(500) NOT NULL,
    sendtime VARCHAR(50)
);
-- 查看数据库字符集
-- show variables like "%character%";