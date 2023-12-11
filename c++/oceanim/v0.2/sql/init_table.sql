DROP DATABASE IF EXISTS oceanim;
CREATE DATABASE oceanim;
USE oceanim;
-- COMMENT  用户表
DROP TABLE IF EXISTS users;
CREATE TABLE users(
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE,
    state ENUM('oneline', 'offline') DEFAULT 'offline'
);
-- COMMENT 好友表
DROP TABLE IF EXISTS friends;
CREATE TABLE friends(
    userid INT NOT NULL,
    friendid INT NOT NULL,
    PRIMARY KEY(userid, friendid)
);
-- COMMENT 群组表
DROP TABLE IF EXISTS allgroups;
CREATE TABLE allgroups(
    id INT AUTO_INCREMENT PRIMARY KEY,
    groupname VARCHAR(50) NOT NULL,
    groupdesc VARCHAR(200) DEFAULT '..'
);
-- COMMENT 群组成员表
DROP TABLE IF EXISTS groupusers;
CREATE TABLE groupusers(
    groupid INT PRIMARY KEY,
    userid INT NOT NULL,
    grouprole ENUM('creator', 'admin', 'normal') DEFAULT 'normal'
);
-- COMMENT 单聊消息表
DROP TABLE IF EXISTS singlmessages;
CREATE TABLE singlmessages(
    id INT AUTO_INCREMENT PRIMARY KEY,
    fromid INT NOT NULL,
    toid INT NOT NULL,
    msgtype ENUM('text', 'audio', 'video', 'image') DEFAULT 'text',
    readtype ENUM('read', 'noread') DEFAULT 'noread',
    message VARCHAR(500) NOT NULL
);
-- COMMENT 群聊消息表
DROP TABLE IF EXISTS groupmessages;
CREATE TABLE groupmessages(
    id INT AUTO_INCREMENT PRIMARY KEY,
    fromid INT NOT NULL,
    groupid INT NOT NULL,
    msgtype ENUM('text', 'audio', 'video', 'image') DEFAULT 'text',
    message VARCHAR(500) NOT NULL
);
-- COMMENT 离线消息表
DROP TABLE IF EXISTS offlinemessages;
CREATE TABLE offlinemessages(
    userid INT PRIMARY KEY,
    message VARCHAR(500) NOT NULL
);