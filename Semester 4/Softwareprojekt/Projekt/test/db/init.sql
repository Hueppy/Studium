-- Adminer 4.8.1 MySQL 8.0.29 dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

SET NAMES utf8mb4;

CREATE DATABASE `education` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `education`;

CREATE TABLE `assessment` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `education_id` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FKnh02wl4a7yaobj81i94673crw` (`education_id`),
  CONSTRAINT `FKnh02wl4a7yaobj81i94673crw` FOREIGN KEY (`education_id`) REFERENCES `education` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


CREATE TABLE `education` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `description` varchar(255) DEFAULT NULL,
  `title` varchar(255) DEFAULT NULL,
  `location_id` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FKhi034ag0lgmn9jbcv4jhko0u1` (`location_id`),
  CONSTRAINT `FKhi034ag0lgmn9jbcv4jhko0u1` FOREIGN KEY (`location_id`) REFERENCES `location` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `education` (`id`, `description`, `title`, `location_id`) VALUES
(1,	'Beschreibung Bildungsangebot 1',	'Bildungsangebot 1',	1),
(2,	'Beschreibung Bildungsangebot 2',	'Bildungsangebot 2',	1),
(3,	'Beschreibung Bildungsangebot 3',	'Bildungsangebot 3',	2),
(4,	'Beschreibung Bildungsangebot 4',	'Bildungsangebot 4',	2),
(5,	'Beschreibung Bildungsangebot 5',	'Bildungsangebot 5',	3),
(6,	'Beschreibung Bildungsangebot 6',	'Bildungsangebot 6',	3),
(7,	'Beschreibung Bildungsangebot 7',	'Bildungsangebot 7',	4),
(8,	'Beschreibung Bildungsangebot 8',	'Bildungsangebot 8',	4),
(9,	'Beschreibung Bildungsangebot 9',	'Bildungsangebot 9',	5),
(10,	'Beschreibung Bildungsangebot 10',	'Bildungsangebot 10',	5),
(11,	'Beschreibung Bildungsangebot 11',	'Bildungsangebot 11',	6),
(12,	'Beschreibung Bildungsangebot 12',	'Bildungsangebot 12',	6);

CREATE TABLE `education_qualifications` (
  `education_id` bigint NOT NULL,
  `qualifications_id` bigint NOT NULL,
  KEY `FKble3ne4r6a8fcvjjwys5iummd` (`qualifications_id`),
  KEY `FKl5v74yv2w8ife3pyabbk1q1ou` (`education_id`),
  CONSTRAINT `FKble3ne4r6a8fcvjjwys5iummd` FOREIGN KEY (`qualifications_id`) REFERENCES `qualification` (`id`),
  CONSTRAINT `FKl5v74yv2w8ife3pyabbk1q1ou` FOREIGN KEY (`education_id`) REFERENCES `education` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


CREATE TABLE `hibernate_sequence` (
  `next_val` bigint DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `hibernate_sequence` (`next_val`) VALUES
(1);

CREATE TABLE `institution` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `institution` (`id`, `name`) VALUES
(1,	'Institution A'),
(2,	'Institution B'),
(3,	'Institution C');

CREATE TABLE `location` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `address` varchar(255) DEFAULT NULL,
  `city` varchar(255) DEFAULT NULL,
  `zip` varchar(255) DEFAULT NULL,
  `institution_id` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK36swemrssl15v8m1ta3yf9efj` (`institution_id`),
  CONSTRAINT `FK36swemrssl15v8m1ta3yf9efj` FOREIGN KEY (`institution_id`) REFERENCES `institution` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `location` (`id`, `address`, `city`, `zip`, `institution_id`) VALUES
(1,	'Campus A1',	'Musterstadt',	'12345',	1),
(2,	'Campus A2',	'Musterstadt',	'12345',	1),
(3,	'Campus A3',	'Musterstadt',	'12345',	1),
(4,	'Campus B1',	'Musterstadt',	'12345',	2),
(5,	'Campus B2',	'Musterstadt',	'12345',	2),
(6,	'Campus C1',	'Musterstadt',	'12345',	3);

CREATE TABLE `matriculation` (
  `id` bigint NOT NULL,
  `date` datetime(6) DEFAULT NULL,
  `education_id` bigint DEFAULT NULL,
  `student_id` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FKs2d00pjh79m5g8qnyy4phwmgt` (`education_id`),
  KEY `FKim453x6hd60iptjv1eg60ky6n` (`student_id`),
  CONSTRAINT `FKim453x6hd60iptjv1eg60ky6n` FOREIGN KEY (`student_id`) REFERENCES `student` (`id`),
  CONSTRAINT `FKs2d00pjh79m5g8qnyy4phwmgt` FOREIGN KEY (`education_id`) REFERENCES `education` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


CREATE TABLE `qualification` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `description` varchar(255) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


CREATE TABLE `qualification_educations` (
  `qualification_id` bigint NOT NULL,
  `educations_id` bigint NOT NULL,
  KEY `FKpocyts10oodfqmscpahlhrt4a` (`educations_id`),
  KEY `FK4gcwvx71xk4p9jtsv0j4o7cwj` (`qualification_id`),
  CONSTRAINT `FK4gcwvx71xk4p9jtsv0j4o7cwj` FOREIGN KEY (`qualification_id`) REFERENCES `qualification` (`id`),
  CONSTRAINT `FKpocyts10oodfqmscpahlhrt4a` FOREIGN KEY (`educations_id`) REFERENCES `education` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


CREATE TABLE `student` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `student` (`id`, `name`) VALUES
(1,	'Schüler A');

CREATE TABLE `user` (
  `email` varchar(255) NOT NULL,
  `is_admin` bit(1) NOT NULL,
  `institution_id` bigint DEFAULT NULL,
  `student_id` bigint DEFAULT NULL,
  PRIMARY KEY (`email`),
  KEY `FKjbkkfl7f3ffm66dmg5aw4yfv3` (`institution_id`),
  KEY `FK4dcom0y59k6tvg3yrguh8wjla` (`student_id`),
  CONSTRAINT `FK4dcom0y59k6tvg3yrguh8wjla` FOREIGN KEY (`student_id`) REFERENCES `student` (`id`),
  CONSTRAINT `FKjbkkfl7f3ffm66dmg5aw4yfv3` FOREIGN KEY (`institution_id`) REFERENCES `institution` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `user` (`email`, `is_admin`, `institution_id`, `student_id`) VALUES
('foo@example.com',	CONV('1', 2, 10) + 0,	1,	1);

-- 2022-06-12 15:04:19
