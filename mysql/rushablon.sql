-- MySQL dump 10.13  Distrib 8.0.35, for Linux (x86_64)
--
-- Host: localhost    Database: rumailing
-- ------------------------------------------------------
-- Server version	8.0.35-0ubuntu0.22.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `acces_photosn`
--

DROP TABLE IF EXISTS `acces_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `acces_photosn` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `prime` int NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT NULL,
  `small_body` varchar(255) DEFAULT NULL,
  `medium_body` varchar(255) DEFAULT NULL,
  `body` varchar(255) DEFAULT NULL,
  `peron_body` varchar(255) DEFAULT NULL,
  `object` int DEFAULT NULL,
  `titl` varchar(255) DEFAULT NULL,
  `alt` varchar(255) DEFAULT NULL,
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `acces_photosn`
--

LOCK TABLES `acces_photosn` WRITE;
/*!40000 ALTER TABLE `acces_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `acces_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `access`
--

DROP TABLE IF EXISTS `access`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `access` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_type` varchar(255) DEFAULT NULL,
  `access` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `access`
--

LOCK TABLES `access` WRITE;
/*!40000 ALTER TABLE `access` DISABLE KEYS */;
INSERT INTO `access` VALUES (1,'Администратор',10),(2,'Заблокирован',1),(3,'Пользователь',2),(4,'Редактро',4),(5,'Модератор',5);
/*!40000 ALTER TABLE `access` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `article_photosn`
--

DROP TABLE IF EXISTS `article_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `article_photosn` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `prime` int NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT NULL,
  `small_body` varchar(255) DEFAULT NULL,
  `medium_body` varchar(255) DEFAULT NULL,
  `body` varchar(255) DEFAULT NULL,
  `peron_body` varchar(255) DEFAULT NULL,
  `titl` varchar(255) DEFAULT NULL,
  `alt` varchar(255) DEFAULT NULL,
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `article_photosn`
--

LOCK TABLES `article_photosn` WRITE;
/*!40000 ALTER TABLE `article_photosn` DISABLE KEYS */;
INSERT INTO `article_photosn` VALUES (1,53439595,0,'','',NULL,'3076922.png',NULL,NULL,NULL,0),(3,47101967,0,'','',NULL,'3163770.png',NULL,NULL,NULL,0),(4,1425537,0,'','',NULL,'6444619.png',NULL,NULL,NULL,0),(5,2,0,'','',NULL,'1375599.png',NULL,NULL,NULL,0),(6,3,0,'','',NULL,'2827018.png',NULL,NULL,NULL,0),(7,5,0,'','',NULL,'7258951.png',NULL,NULL,NULL,0),(8,6,0,'','',NULL,'5215624.png',NULL,NULL,NULL,0),(9,27394397,0,'','',NULL,'1723737.png',NULL,NULL,NULL,0),(10,90372692,0,'','',NULL,'2202846.png',NULL,NULL,NULL,0),(11,22935406,0,'','',NULL,'6372390.png',NULL,NULL,NULL,0),(12,22935406,0,'','',NULL,'4445389.png',NULL,NULL,NULL,0),(13,76040838,0,'','',NULL,'8173951.png',NULL,NULL,NULL,0),(14,32677117,0,'','',NULL,'7880454.png',NULL,NULL,NULL,0),(15,59142302,0,'','',NULL,'5718099.png',NULL,NULL,NULL,0),(16,34561574,0,'','',NULL,'4075341.png',NULL,NULL,NULL,0),(17,14402489,0,'','',NULL,'6658720.png',NULL,NULL,NULL,0),(18,78574251,0,'','',NULL,'1459353.png',NULL,NULL,NULL,0),(19,19536702,0,'','',NULL,'3298260.png',NULL,NULL,NULL,0),(20,56454935,0,'','',NULL,'5915827.png',NULL,NULL,NULL,0),(21,51251272,0,'','',NULL,'6048765.png',NULL,NULL,NULL,0),(22,66651808,0,'','',NULL,'3348246.png',NULL,NULL,NULL,0),(23,66651808,0,'','',NULL,'3779000.png',NULL,NULL,NULL,0),(24,66651808,0,'','',NULL,'8978585.png',NULL,NULL,NULL,0),(25,40556864,0,'','',NULL,'2322592.png',NULL,NULL,NULL,0),(26,51192208,0,'','',NULL,'8249132.png',NULL,NULL,NULL,0),(27,97318964,0,'','',NULL,'2912142.png',NULL,NULL,NULL,0),(28,97318964,0,'','',NULL,'8111382.png',NULL,NULL,NULL,0),(29,98697876,0,'','',NULL,'3996004.png',NULL,NULL,NULL,0),(30,53903556,0,'','',NULL,'5054345.png',NULL,NULL,NULL,0),(31,53903556,0,'','',NULL,'7291731.png',NULL,NULL,NULL,0),(32,10071733,0,'','',NULL,'3554200.png',NULL,NULL,NULL,0),(33,20799603,0,'','',NULL,'10083764.png',NULL,NULL,NULL,0),(34,88226750,0,'','',NULL,'4393294.png',NULL,NULL,NULL,0),(35,18443117,0,'','',NULL,'7255168.png',NULL,NULL,NULL,0),(36,44073948,0,'','',NULL,'9067338.png',NULL,NULL,NULL,0),(37,4647594,0,'','',NULL,'4392507.png',NULL,NULL,NULL,0),(38,29187417,0,'','',NULL,'10642883.png',NULL,NULL,NULL,0),(39,2152322,0,'','',NULL,'7669324.png',NULL,NULL,NULL,0);
/*!40000 ALTER TABLE `article_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `articles`
--

DROP TABLE IF EXISTS `articles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `articles` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `lid` text,
  `body` text,
  `block` int NOT NULL DEFAULT '0',
  `access` int NOT NULL DEFAULT '7',
  `product_id` int NOT NULL DEFAULT '0',
  `subsubcategory_id` int NOT NULL DEFAULT '0',
  `subcategory_id` int NOT NULL DEFAULT '0',
  `category_id` int NOT NULL DEFAULT '0',
  `autor` varchar(255) DEFAULT NULL,
  `date_create` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `user_id` int NOT NULL DEFAULT '0',
  `lk` int NOT NULL DEFAULT '0',
  `wv` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `articles`
--

LOCK TABLES `articles` WRITE;
/*!40000 ALTER TABLE `articles` DISABLE KEYS */;
INSERT INTO `articles` VALUES (1,'выаыва','ываыва','',0,0,0,0,0,0,'','2017-01-12 04:13:37',0,0,0),(2,'sdfsdf','dsfsdf','',0,0,0,0,0,0,'','2017-01-12 06:30:59',0,0,0),(3,'sdfsd','fsdfs','',0,0,0,0,0,0,'','2017-01-12 06:34:23',0,0,0),(4,'sdfsd','fsdfs','',0,0,0,0,0,0,'','2017-01-12 06:36:05',0,0,0),(5,'sdf','sdfsdf','',0,0,0,0,0,0,'','2017-01-12 06:37:57',0,0,0),(6,'dfsdf','sdfsdf','',0,0,0,0,0,0,'','2017-01-12 06:42:56',0,0,0),(7,'','','',0,0,0,0,0,0,'','2017-01-17 13:11:38',0,0,0);
/*!40000 ALTER TABLE `articles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `back_photosn`
--

DROP TABLE IF EXISTS `back_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `back_photosn` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `prime` int NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT NULL,
  `small_body` varchar(255) DEFAULT NULL,
  `medium_body` varchar(255) DEFAULT NULL,
  `body` varchar(255) DEFAULT NULL,
  `peron_body` varchar(255) DEFAULT NULL,
  `object` int DEFAULT NULL,
  `titl` varchar(255) DEFAULT NULL,
  `alt` varchar(255) DEFAULT NULL,
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `back_photosn`
--

LOCK TABLES `back_photosn` WRITE;
/*!40000 ALTER TABLE `back_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `back_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `category` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `chat`
--

DROP TABLE IF EXISTS `chat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `chat` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `parent_id` int NOT NULL DEFAULT '0',
  `body` text NOT NULL,
  `date_create` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `lk` int NOT NULL DEFAULT '0',
  `vote_up` int NOT NULL DEFAULT '0',
  `vote_down` int NOT NULL DEFAULT '0',
  `lk_cn` int NOT NULL DEFAULT '1',
  `rd` int NOT NULL DEFAULT '0',
  `lot_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chat`
--

LOCK TABLES `chat` WRITE;
/*!40000 ALTER TABLE `chat` DISABLE KEYS */;
/*!40000 ALTER TABLE `chat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `color`
--

DROP TABLE IF EXISTS `color`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `color` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `shema` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `color`
--

LOCK TABLES `color` WRITE;
/*!40000 ALTER TABLE `color` DISABLE KEYS */;
/*!40000 ALTER TABLE `color` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `comments_article`
--

DROP TABLE IF EXISTS `comments_article`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `comments_article` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `article_id` int NOT NULL DEFAULT '0',
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `body` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `comments_article`
--

LOCK TABLES `comments_article` WRITE;
/*!40000 ALTER TABLE `comments_article` DISABLE KEYS */;
/*!40000 ALTER TABLE `comments_article` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `delivemetod`
--

DROP TABLE IF EXISTS `delivemetod`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `delivemetod` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `sale` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `delivemetod`
--

LOCK TABLES `delivemetod` WRITE;
/*!40000 ALTER TABLE `delivemetod` DISABLE KEYS */;
/*!40000 ALTER TABLE `delivemetod` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `javames`
--

DROP TABLE IF EXISTS `javames`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `javames` (
  `id` int NOT NULL AUTO_INCREMENT,
  `file` int DEFAULT NULL,
  `st` int DEFAULT NULL,
  `phrase` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `javames`
--

LOCK TABLES `javames` WRITE;
/*!40000 ALTER TABLE `javames` DISABLE KEYS */;
INSERT INTO `javames` VALUES (1,1,1,'Данные сохранены'),(2,1,2,'Пароль успешно изменен'),(3,1,3,'Ваш закакз оформлен'),(4,1,4,'Заявка на вывод принята'),(5,1,5,'Заявка не принята Обратитесь в службу поддрежки'),(6,1,6,'Проверьте почтовый ящик который вы указывали при регистрации'),(7,1,8,'Почта отправлена'),(8,1,7,'Ваша учетная запись успешно создана на сервере'),(9,2,9,'Заполните все поля'),(10,1,9,'Такой пользователь уже существует');
/*!40000 ALTER TABLE `javames` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `message_admin`
--

DROP TABLE IF EXISTS `message_admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `message_admin` (
  `id` int NOT NULL AUTO_INCREMENT,
  `lid` varchar(255) DEFAULT NULL,
  `body` text,
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `deliv` int NOT NULL DEFAULT '0',
  `sms` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `message_admin`
--

LOCK TABLES `message_admin` WRITE;
/*!40000 ALTER TABLE `message_admin` DISABLE KEYS */;
/*!40000 ALTER TABLE `message_admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `message_photosn`
--

DROP TABLE IF EXISTS `message_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `message_photosn` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `prime` int NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT NULL,
  `small_body` varchar(255) DEFAULT NULL,
  `medium_body` varchar(255) DEFAULT NULL,
  `body` varchar(255) DEFAULT NULL,
  `peron_body` varchar(255) DEFAULT NULL,
  `object` int DEFAULT NULL,
  `titl` varchar(255) DEFAULT NULL,
  `alt` varchar(255) DEFAULT NULL,
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `message_photosn`
--

LOCK TABLES `message_photosn` WRITE;
/*!40000 ALTER TABLE `message_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `message_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `messages`
--

DROP TABLE IF EXISTS `messages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `messages` (
  `id` int NOT NULL AUTO_INCREMENT,
  `tems_id` int NOT NULL DEFAULT '0',
  `autor_id` int NOT NULL DEFAULT '0',
  `recepient_id` int NOT NULL DEFAULT '0',
  `rd` int NOT NULL DEFAULT '0',
  `body` text,
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `messages`
--

LOCK TABLES `messages` WRITE;
/*!40000 ALTER TABLE `messages` DISABLE KEYS */;
/*!40000 ALTER TABLE `messages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `messages_tems`
--

DROP TABLE IF EXISTS `messages_tems`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `messages_tems` (
  `id` int NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `user_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `messages_tems`
--

LOCK TABLES `messages_tems` WRITE;
/*!40000 ALTER TABLE `messages_tems` DISABLE KEYS */;
/*!40000 ALTER TABLE `messages_tems` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `page_photosn`
--

DROP TABLE IF EXISTS `page_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `page_photosn` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `prime` int NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT NULL,
  `small_body` varchar(255) DEFAULT NULL,
  `medium_body` varchar(255) DEFAULT NULL,
  `body` varchar(255) DEFAULT NULL,
  `peron_body` varchar(255) DEFAULT NULL,
  `object` int DEFAULT NULL,
  `titl` varchar(255) DEFAULT NULL,
  `alt` varchar(255) DEFAULT NULL,
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `page_photosn`
--

LOCK TABLES `page_photosn` WRITE;
/*!40000 ALTER TABLE `page_photosn` DISABLE KEYS */;
INSERT INTO `page_photosn` VALUES (1,1,0,'','',NULL,'4587521.jpg',NULL,NULL,NULL,NULL,0),(3,30874174,0,'','',NULL,'2636013.jpg',NULL,NULL,NULL,NULL,0),(6,6,0,NULL,NULL,NULL,'4205847.png',NULL,NULL,'','',0);
/*!40000 ALTER TABLE `page_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pages`
--

DROP TABLE IF EXISTS `pages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pages` (
  `id` int NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `positions` int NOT NULL DEFAULT '0',
  `region_id` int NOT NULL DEFAULT '0',
  `access` int NOT NULL DEFAULT '0',
  `edit` int NOT NULL DEFAULT '1',
  `title2` varchar(255) DEFAULT NULL,
  `text_iner` int NOT NULL DEFAULT '0',
  `parent_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pages`
--

LOCK TABLES `pages` WRITE;
/*!40000 ALTER TABLE `pages` DISABLE KEYS */;
INSERT INTO `pages` VALUES (1,'Главная',2,1,0,1,NULL,0,0),(2,'Авторизация',10,0,0,1,NULL,0,0),(3,'Страницы',10,10,10,1,NULL,0,0);
/*!40000 ALTER TABLE `pages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pagewords`
--

DROP TABLE IF EXISTS `pagewords`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pagewords` (
  `id` int NOT NULL AUTO_INCREMENT,
  `str` int NOT NULL DEFAULT '0',
  `pstr` int NOT NULL DEFAULT '0',
  `posit` int NOT NULL DEFAULT '0',
  `phrase` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pagewords`
--

LOCK TABLES `pagewords` WRITE;
/*!40000 ALTER TABLE `pagewords` DISABLE KEYS */;
INSERT INTO `pagewords` VALUES (1,1,0,1,'Авторизация'),(2,1,0,2,'Логин'),(3,1,0,3,'Пароль'),(4,1,0,4,'Выход'),(5,2,0,1,'Ссылка'),(6,2,0,2,'Ключевые слова'),(7,2,0,3,'Title'),(8,2,0,4,'Description'),(9,2,0,5,'Название'),(10,2,0,6,'Анонс'),(11,2,0,7,'Сохранить'),(12,2,0,8,'Главное фото'),(13,2,0,9,'Анонс'),(14,2,0,10,'Текст статьи'),(15,2,0,11,'Превью');
/*!40000 ALTER TABLE `pagewords` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `products`
--

DROP TABLE IF EXISTS `products`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `products` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int NOT NULL DEFAULT '0',
  `access` int NOT NULL DEFAULT '0',
  `name` varchar(255) DEFAULT NULL,
  `articl` varchar(255) DEFAULT NULL,
  `category_id` int NOT NULL DEFAULT '0',
  `subcategory_id` int NOT NULL DEFAULT '0',
  `manufacturers_id` int DEFAULT NULL,
  `lid` text,
  `descr` text,
  `dat` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `user_id` int DEFAULT NULL,
  `main` int NOT NULL DEFAULT '0',
  `subsubcategory_id` int NOT NULL DEFAULT '0',
  `lider` int NOT NULL DEFAULT '0',
  `super_sale` int NOT NULL DEFAULT '0',
  `new` int NOT NULL DEFAULT '0',
  `recomend` int NOT NULL DEFAULT '0',
  `count_view` int NOT NULL DEFAULT '0',
  `select_custom` int NOT NULL DEFAULT '0',
  `min_opt` int NOT NULL DEFAULT '0',
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `products`
--

LOCK TABLES `products` WRITE;
/*!40000 ALTER TABLE `products` DISABLE KEYS */;
/*!40000 ALTER TABLE `products` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `seotexts`
--

DROP TABLE IF EXISTS `seotexts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `seotexts` (
  `id` int NOT NULL AUTO_INCREMENT,
  `titl` varchar(255) DEFAULT NULL,
  `keyw` text,
  `descr` text,
  `tegs` text,
  `link` text,
  `arti` int NOT NULL DEFAULT '0',
  `str` int NOT NULL DEFAULT '0',
  `pstr` int NOT NULL DEFAULT '0',
  `ppstr` int NOT NULL DEFAULT '0',
  `reg` int NOT NULL DEFAULT '0',
  `shablon` varchar(255) NOT NULL DEFAULT '',
  `level` int NOT NULL DEFAULT '0',
  `user_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `seotexts`
--

LOCK TABLES `seotexts` WRITE;
/*!40000 ALTER TABLE `seotexts` DISABLE KEYS */;
INSERT INTO `seotexts` VALUES (1,'Входящие',' ',' ','<style type=\"text/css\">.wrap_main{\r\nwidth: 100vw;\r\nheight: 100vh;\r\ndisplay: flex;\r\nalign-items: center;\r\njustify-content: center;}\r\nh1{font-size:5em; color:red;}\r\n</style>\r\n<div class=\"wrap_main\">\r\n<h1>The site is under construction</h1>\r\n</div>\r\n','',0,1,0,0,0,'textpage.rhtml',0,0),(2,'Авторизация',NULL,NULL,NULL,'auch',0,2,0,0,0,'auch.rhtml',0,0),(3,'Страницы',NULL,NULL,NULL,'pages',0,3,0,0,0,'pagesadmin.rhtml',10,0);
/*!40000 ALTER TABLE `seotexts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `subcategory`
--

DROP TABLE IF EXISTS `subcategory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `subcategory` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `subcategory`
--

LOCK TABLES `subcategory` WRITE;
/*!40000 ALTER TABLE `subcategory` DISABLE KEYS */;
/*!40000 ALTER TABLE `subcategory` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `subpage_photosn`
--

DROP TABLE IF EXISTS `subpage_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `subpage_photosn` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `prime` int NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT NULL,
  `small_body` varchar(255) DEFAULT NULL,
  `medium_body` varchar(255) DEFAULT NULL,
  `body` varchar(255) DEFAULT NULL,
  `peron_body` varchar(255) DEFAULT NULL,
  `object` int DEFAULT NULL,
  `titl` varchar(255) DEFAULT NULL,
  `alt` varchar(255) DEFAULT NULL,
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `subpage_photosn`
--

LOCK TABLES `subpage_photosn` WRITE;
/*!40000 ALTER TABLE `subpage_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `subpage_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `subsubpage_photosn`
--

DROP TABLE IF EXISTS `subsubpage_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `subsubpage_photosn` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int DEFAULT NULL,
  `prime` int NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT NULL,
  `small_body` varchar(255) DEFAULT NULL,
  `medium_body` varchar(255) DEFAULT NULL,
  `body` varchar(255) DEFAULT NULL,
  `peron_body` varchar(255) DEFAULT NULL,
  `object` int DEFAULT NULL,
  `titl` varchar(255) DEFAULT NULL,
  `alt` varchar(255) DEFAULT NULL,
  `color_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `subsubpage_photosn`
--

LOCK TABLES `subsubpage_photosn` WRITE;
/*!40000 ALTER TABLE `subsubpage_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `subsubpage_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `video`
--

DROP TABLE IF EXISTS `video`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `video` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `code` varchar(255) DEFAULT NULL,
  `parent_admin` int NOT NULL DEFAULT '0',
  `descr` text,
  `date_start` varchar(255) DEFAULT NULL,
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `spiker_id` int DEFAULT NULL,
  `category_id` int NOT NULL DEFAULT '0',
  `lk` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `video`
--

LOCK TABLES `video` WRITE;
/*!40000 ALTER TABLE `video` DISABLE KEYS */;
/*!40000 ALTER TABLE `video` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `view_article`
--

DROP TABLE IF EXISTS `view_article`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `view_article` (
  `id` int NOT NULL AUTO_INCREMENT,
  `article_id` int NOT NULL DEFAULT '0',
  `user_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `view_article`
--

LOCK TABLES `view_article` WRITE;
/*!40000 ALTER TABLE `view_article` DISABLE KEYS */;
/*!40000 ALTER TABLE `view_article` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-11-07 14:15:28
