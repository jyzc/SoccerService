/*
Navicat MySQL Data Transfer

Source Server         : 192.168.93.129_3306
Source Server Version : 50547
Source Host           : 192.168.93.129:3306
Source Database       : sina_football_db

Target Server Type    : MYSQL
Target Server Version : 50547
File Encoding         : 65001

Date: 2016-06-07 11:28:25
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `T_AREA`
-- ----------------------------
DROP TABLE IF EXISTS `T_AREA`;
CREATE TABLE `T_AREA` (
  `AREA_ID` tinyint(4) NOT NULL,
  `AREA_NAME` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`AREA_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_AREA
-- ----------------------------

-- ----------------------------
-- Table structure for `T_COMPANY`
-- ----------------------------
DROP TABLE IF EXISTS `T_COMPANY`;
CREATE TABLE `T_COMPANY` (
  `COMPANY_ID` smallint(6) NOT NULL DEFAULT '0',
  `COMPANY_NAME` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`COMPANY_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_COMPANY
-- ----------------------------

-- ----------------------------
-- Table structure for `T_COUNTRY`
-- ----------------------------
DROP TABLE IF EXISTS `T_COUNTRY`;
CREATE TABLE `T_COUNTRY` (
  `COUNTRY_ID` smallint(6) NOT NULL,
  `COUNTRY_NAME` varchar(40) DEFAULT NULL,
  `AREA_ID` tinyint(4) DEFAULT NULL,
  PRIMARY KEY (`COUNTRY_ID`),
  KEY `AREA_ID` (`AREA_ID`),
  CONSTRAINT `T_COUNTRY_ibfk_1` FOREIGN KEY (`AREA_ID`) REFERENCES `T_AREA` (`AREA_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_COUNTRY
-- ----------------------------

-- ----------------------------
-- Table structure for `T_EVENT`
-- ----------------------------
DROP TABLE IF EXISTS `T_EVENT`;
CREATE TABLE `T_EVENT` (
  `EVENT_ID` smallint(6) NOT NULL,
  `EVENT_NAME` varchar(40) DEFAULT NULL COMMENT '赛事名称',
  `TYPE_ID` tinyint(4) DEFAULT NULL,
  `COUNTRY_ID` smallint(6) DEFAULT NULL COMMENT '国家ID',
  `MATCH_ROUNDS` tinyint(4) DEFAULT NULL COMMENT '球队比赛总轮次',
  `SEASON_NAME` varchar(40) DEFAULT NULL COMMENT '赛季名称',
  `TEAM_COUNT` tinyint(4) DEFAULT NULL COMMENT '球队数量',
  PRIMARY KEY (`EVENT_ID`),
  KEY `TYPE_ID` (`TYPE_ID`),
  KEY `COUNTRY_ID` (`COUNTRY_ID`),
  CONSTRAINT `T_EVENT_ibfk_1` FOREIGN KEY (`TYPE_ID`) REFERENCES `T_TYPE` (`TYPE_ID`),
  CONSTRAINT `T_EVENT_ibfk_2` FOREIGN KEY (`COUNTRY_ID`) REFERENCES `T_COUNTRY` (`COUNTRY_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_EVENT
-- ----------------------------

-- ----------------------------
-- Table structure for `T_GOAL`
-- ----------------------------
DROP TABLE IF EXISTS `T_GOAL`;
CREATE TABLE `T_GOAL` (
  `MATCH_ID` int(11) NOT NULL DEFAULT '0' COMMENT '比赛ID',
  `GOAL_MINUTE` tinyint(4) NOT NULL DEFAULT '0' COMMENT '进球时间',
  `GOAL_TEAM_ID` int(11) NOT NULL DEFAULT '0' COMMENT '进球球队ID',
  `MATCH_STATUS` tinyint(4) NOT NULL DEFAULT '0' COMMENT '比赛状态：1-上半；2-上半补时；3-下半；4-下半补时；5-加时上半；6-加时上半补时；7-加时下半；8-加时下半补时',
  PRIMARY KEY (`GOAL_TEAM_ID`,`GOAL_MINUTE`,`MATCH_ID`,`MATCH_STATUS`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_GOAL
-- ----------------------------

-- ----------------------------
-- Table structure for `T_MATCH`
-- ----------------------------
DROP TABLE IF EXISTS `T_MATCH`;
CREATE TABLE `T_MATCH` (
  `MATCH_ID` int(11) NOT NULL COMMENT '比赛ID',
  `EVENT_ID` smallint(6) DEFAULT NULL COMMENT '赛事ID',
  `SEASON_NAME` varchar(40) DEFAULT NULL COMMENT '赛季名称',
  `SEASON_ROUND` tinyint(3) unsigned DEFAULT NULL COMMENT '联赛轮次',
  `MATCH_DATE` datetime DEFAULT NULL,
  `MATCH_RESULT` tinyint(4) DEFAULT NULL,
  `MATCH_STATUS` tinyint(4) DEFAULT NULL,
  `HOME_TEAM_ID` int(11) DEFAULT NULL,
  `GUEST_TEAM_ID` int(11) DEFAULT NULL,
  `HOME_SCORE_HARF` tinyint(4) DEFAULT NULL,
  `GUEST_SCORE_HARF` tinyint(4) DEFAULT NULL,
  `HOME_SCORE` tinyint(4) DEFAULT NULL,
  `GUEST_SCORE` tinyint(4) DEFAULT NULL,
  `PARAMETER_FULLY` float DEFAULT NULL,
  PRIMARY KEY (`MATCH_ID`),
  KEY `EVENT_ID` (`EVENT_ID`),
  KEY `HOME_TEAM_ID` (`HOME_TEAM_ID`),
  KEY `GUEST_TEAM_ID` (`GUEST_TEAM_ID`),
  CONSTRAINT `T_MATCH_ibfk_1` FOREIGN KEY (`EVENT_ID`) REFERENCES `T_EVENT` (`EVENT_ID`),
  CONSTRAINT `T_MATCH_ibfk_2` FOREIGN KEY (`HOME_TEAM_ID`) REFERENCES `T_TEAM` (`TEAM_ID`),
  CONSTRAINT `T_MATCH_ibfk_3` FOREIGN KEY (`GUEST_TEAM_ID`) REFERENCES `T_TEAM` (`TEAM_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_MATCH
-- ----------------------------

-- ----------------------------
-- Table structure for `T_ODDS_DAXIAOQIU`
-- ----------------------------
DROP TABLE IF EXISTS `T_ODDS_DAXIAOQIU`;
CREATE TABLE `T_ODDS_DAXIAOQIU` (
  `MATCH_ID` int(11) NOT NULL DEFAULT '0',
  `COMPANY_ID` smallint(6) NOT NULL DEFAULT '0',
  `ODDS_DATE` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ODDS_WIN` float DEFAULT NULL,
  `ODDS_DROW` float DEFAULT NULL,
  `ODDS_LOSE` float DEFAULT NULL,
  PRIMARY KEY (`MATCH_ID`,`COMPANY_ID`,`ODDS_DATE`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_ODDS_DAXIAOQIU
-- ----------------------------

-- ----------------------------
-- Table structure for `T_ODDS_OUZHI`
-- ----------------------------
DROP TABLE IF EXISTS `T_ODDS_OUZHI`;
CREATE TABLE `T_ODDS_OUZHI` (
  `MATCH_ID` int(11) NOT NULL DEFAULT '0',
  `COMPANY_ID` smallint(6) NOT NULL DEFAULT '0',
  `ODDS_DATE` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ODDS_WIN` float DEFAULT NULL,
  `ODDS_DROW` float DEFAULT NULL,
  `ODDS_LOSE` float DEFAULT NULL,
  PRIMARY KEY (`MATCH_ID`,`COMPANY_ID`,`ODDS_DATE`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_ODDS_OUZHI
-- ----------------------------

-- ----------------------------
-- Table structure for `T_ODDS_YAZHI`
-- ----------------------------
DROP TABLE IF EXISTS `T_ODDS_YAZHI`;
CREATE TABLE `T_ODDS_YAZHI` (
  `MATCH_ID` int(11) NOT NULL DEFAULT '0',
  `COMPANY_ID` smallint(6) NOT NULL DEFAULT '0',
  `ODDS_DATE` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ODDS_WIN` float DEFAULT NULL,
  `ODDS_DROW` float DEFAULT NULL,
  `ODDS_LOSE` float DEFAULT NULL,
  PRIMARY KEY (`MATCH_ID`,`COMPANY_ID`,`ODDS_DATE`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_ODDS_YAZHI
-- ----------------------------

-- ----------------------------
-- Table structure for `T_PARAMETER`
-- ----------------------------
DROP TABLE IF EXISTS `T_PARAMETER`;
CREATE TABLE `T_PARAMETER` (
  `MATCH_ID` int(11) NOT NULL,
  `PARAMETER_J` smallint(6) DEFAULT NULL,
  `PARAMETER_F` float DEFAULT NULL,
  `PARAMETER_K` float DEFAULT NULL,
  `PARAMETER_H` float DEFAULT NULL,
  `PARAMETER_D` float DEFAULT NULL,
  `PARAMETER_T` float DEFAULT NULL,
  PRIMARY KEY (`MATCH_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_PARAMETER
-- ----------------------------

-- ----------------------------
-- Table structure for `T_TEAM`
-- ----------------------------
DROP TABLE IF EXISTS `T_TEAM`;
CREATE TABLE `T_TEAM` (
  `TEAM_ID` int(11) NOT NULL,
  `TEAM_NAME` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`TEAM_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_TEAM
-- ----------------------------

-- ----------------------------
-- Table structure for `T_TEAMDATA`
-- ----------------------------
DROP TABLE IF EXISTS `T_TEAMDATA`;
CREATE TABLE `T_TEAMDATA` (
  `SEASON_ID` int(11) NOT NULL,
  `TEAM_ID` int(11) NOT NULL,
  `MATCH_ROUND` tinyint(4) NOT NULL,
  `WIN_HOME` tinyint(4) DEFAULT NULL,
  `DROW_HOME` tinyint(4) DEFAULT NULL,
  `LOSE_HOME` tinyint(4) DEFAULT NULL,
  `WIN_GUEST` tinyint(4) DEFAULT NULL,
  `DROW_GUEST` tinyint(4) DEFAULT NULL,
  `LOSE_GUEST` tinyint(4) DEFAULT NULL,
  `SCORE_WIN_HOME` tinyint(4) DEFAULT NULL,
  `SCORE_LOSE_HOME` tinyint(4) DEFAULT NULL,
  `SCORE_WIN_GUEST` tinyint(4) DEFAULT NULL,
  `SCORE_LOSE_GUEST` tinyint(4) DEFAULT NULL,
  `JIFEN_HOME` tinyint(4) DEFAULT NULL,
  `JIFEN_GUEST` tinyint(4) DEFAULT NULL,
  `ORDER_HOME` tinyint(4) DEFAULT NULL,
  `ORDER_GUEST` tinyint(4) DEFAULT NULL,
  `TEAM_ORDER` tinyint(4) DEFAULT NULL,
  PRIMARY KEY (`SEASON_ID`,`TEAM_ID`,`MATCH_ROUND`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_TEAMDATA
-- ----------------------------

-- ----------------------------
-- Table structure for `T_TYPE`
-- ----------------------------
DROP TABLE IF EXISTS `T_TYPE`;
CREATE TABLE `T_TYPE` (
  `TYPE_ID` tinyint(4) NOT NULL COMMENT '赛事类型ID',
  `TYPE_NAME` varchar(20) DEFAULT NULL COMMENT '赛事类型名称',
  PRIMARY KEY (`TYPE_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of T_TYPE
-- ----------------------------
