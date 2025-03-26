-- MySQL dump 10.13  Distrib 8.0.35, for Linux (x86_64)
--
-- Host: localhost    Database: mailing
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
-- Table structure for table `acess_block`
--

DROP TABLE IF EXISTS `acess_block`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `acess_block` (
  `id` int NOT NULL AUTO_INCREMENT,
  `id_block` int NOT NULL DEFAULT '0',
  `access` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `acess_block`
--

LOCK TABLES `acess_block` WRITE;
/*!40000 ALTER TABLE `acess_block` DISABLE KEYS */;
/*!40000 ALTER TABLE `acess_block` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `action_link_mail`
--

DROP TABLE IF EXISTS `action_link_mail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `action_link_mail` (
  `id` int NOT NULL AUTO_INCREMENT,
  `mail_id` int NOT NULL DEFAULT '0',
  `link` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `action_link_mail`
--

LOCK TABLES `action_link_mail` WRITE;
/*!40000 ALTER TABLE `action_link_mail` DISABLE KEYS */;
/*!40000 ALTER TABLE `action_link_mail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `activity`
--

DROP TABLE IF EXISTS `activity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `activity` (
  `id` int NOT NULL AUTO_INCREMENT,
  `action` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `activity`
--

LOCK TABLES `activity` WRITE;
/*!40000 ALTER TABLE `activity` DISABLE KEYS */;
/*!40000 ALTER TABLE `activity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `activity_users`
--

DROP TABLE IF EXISTS `activity_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `activity_users` (
  `id` int NOT NULL AUTO_INCREMENT,
  `activity_id` int DEFAULT NULL,
  `user_id` int DEFAULT NULL,
  `hesh_user` int DEFAULT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `object_id` int DEFAULT NULL,
  `object_type` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `activity_users`
--

LOCK TABLES `activity_users` WRITE;
/*!40000 ALTER TABLE `activity_users` DISABLE KEYS */;
/*!40000 ALTER TABLE `activity_users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `antibot_tmp`
--

DROP TABLE IF EXISTS `antibot_tmp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `antibot_tmp` (
  `id` int NOT NULL AUTO_INCREMENT,
  `checksum` varchar(255) DEFAULT NULL,
  `pid` int DEFAULT NULL,
  `datcrea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `antibot_tmp`
--

LOCK TABLES `antibot_tmp` WRITE;
/*!40000 ALTER TABLE `antibot_tmp` DISABLE KEYS */;
/*!40000 ALTER TABLE `antibot_tmp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `antibotpics`
--

DROP TABLE IF EXISTS `antibotpics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `antibotpics` (
  `id` int NOT NULL AUTO_INCREMENT,
  `body` mediumblob,
  `text` varchar(255) DEFAULT NULL,
  `datcrea` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `checksum` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `antibotpics`
--

LOCK TABLES `antibotpics` WRITE;
/*!40000 ALTER TABLE `antibotpics` DISABLE KEYS */;
INSERT INTO `antibotpics` VALUES (1,NULL,'88123','2020-01-05 14:05:49','f7c50c800b07867bb364137476444d5f');
/*!40000 ALTER TABLE `antibotpics` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `class`
--

DROP TABLE IF EXISTS `class`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `class` (
  `id` int NOT NULL AUTO_INCREMENT,
  `class` int NOT NULL DEFAULT '0',
  `id_str` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `class`
--

LOCK TABLES `class` WRITE;
/*!40000 ALTER TABLE `class` DISABLE KEYS */;
INSERT INTO `class` VALUES (1,14,3),(2,16,3),(3,12,1),(4,4,4),(5,14,4),(6,16,1),(7,12,1);
/*!40000 ALTER TABLE `class` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `class_name`
--

DROP TABLE IF EXISTS `class_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `class_name` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `class_name`
--

LOCK TABLES `class_name` WRITE;
/*!40000 ALTER TABLE `class_name` DISABLE KEYS */;
INSERT INTO `class_name` VALUES (1,'Vdcgi'),(2,'VdMainapp'),(3,'VdUser'),(4,'VdArticle'),(5,'VdKassa'),(6,'VdBitcoin'),(7,'VdStatistic'),(8,'VdChat'),(9,'VdVideo'),(10,'VdRobo_kassa'),(11,'VdProduct'),(12,'VdNet'),(13,'VdInter_kassa'),(14,'VdAdmin'),(15,'VdMessages'),(16,'VdImg');
/*!40000 ALTER TABLE `class_name` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contacts`
--

DROP TABLE IF EXISTS `contacts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `contacts` (
  `adress` varchar(255) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  `phone` varchar(255) DEFAULT NULL,
  `mail` varchar(255) DEFAULT NULL,
  `icq` varchar(255) DEFAULT NULL,
  `skype` varchar(255) DEFAULT NULL,
  `director` varchar(255) DEFAULT NULL,
  `about` text,
  `contract` text,
  `frommail` varchar(255) DEFAULT NULL,
  `server` varchar(255) DEFAULT NULL,
  `port` varchar(255) DEFAULT NULL,
  `login` varchar(255) DEFAULT NULL,
  `passwd` varchar(255) DEFAULT NULL,
  `sendmail` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contacts`
--

LOCK TABLES `contacts` WRITE;
/*!40000 ALTER TABLE `contacts` DISABLE KEYS */;
INSERT INTO `contacts` VALUES (NULL,'VD Studio',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0);
/*!40000 ALTER TABLE `contacts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `countries`
--

DROP TABLE IF EXISTS `countries`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `countries` (
  `country_id` int NOT NULL,
  `name` varchar(255) NOT NULL,
  `currency_code` varchar(5) NOT NULL,
  `currency` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`country_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `countries`
--

LOCK TABLES `countries` WRITE;
/*!40000 ALTER TABLE `countries` DISABLE KEYS */;
INSERT INTO `countries` VALUES (19,'Австралия','AUD','Австралийский доллар'),(20,'Австрия','EUR','Евро'),(5,'Азербайджан','AZN','Азербайджанский манат'),(21,'Албания','ALB','Лек'),(22,'Алжир','DZD','Алжирский динар'),(23,'Американское Самоа','USD','Доллар США'),(24,'Ангилья','XCD','Восточно-карибский доллар'),(25,'Ангола','AOA','Кванза'),(26,'Андорра','EUR','Евро'),(27,'Антигуа и Барбуда','XCD','Восточно-карибский доллар'),(28,'Аргентина','ARS','Аргентинское песо'),(6,'Армения','AMD','Армянский драм'),(29,'Аруба','AWG','Арубанский флорин'),(30,'Афганистан','AFN','Афгани'),(31,'Багамы','BSD','Багамский доллар'),(32,'Бангладеш','BTD','Така'),(33,'Барбадос','BBD','Барбадосский доллар'),(34,'Бахрейн','BHD','Бахрейнский динар'),(3,'Беларусь','BYR','Белорусский рубль'),(35,'Белиз','BZD','Белизский доллар '),(36,'Бельгия','Евро','EUR'),(37,'Бенин','XOF','Франк КФА BCEAO'),(38,'Бермуды','BMD','Бермудский доллар'),(39,'Болгария','BGN','Болгарский лев'),(40,'Боливия','BOB','Боливиано'),(41,'Босния и Герцеговина','BAM','Конвертируемая марка'),(42,'Ботсвана','BWP','Пула'),(43,'Бразилия','BRL','Бразильский реал'),(44,'Бруней-Даруссалам','BND','Брунейский доллар'),(45,'Буркина-Фасо','XOF','Франк КФА BCEAO'),(46,'Бурунди','BIF','Бурундийский франк'),(47,'Бутан','BTN','Нгултрум'),(48,'Вануату','VUV','Вату'),(49,'Великобритания','GBP','Фунт стерлингов'),(50,'Венгрия','HUF','Форинт'),(51,'Венесуэла','VEF','Боливар фуэрте'),(52,'Виргинские острова, Британские','USD','Доллар США'),(53,'Виргинские острова, США','USD','Доллар США'),(54,'Восточный Тимор','USD','Доллар США'),(55,'Вьетнам','VND','Донг'),(56,'Габон','XAF','Франк КФА BEAC'),(57,'Гаити','HTG','Гурд'),(58,'Гайана','GYD','Гайанский доллар'),(59,'Гамбия','GMD','Даласи'),(60,'Гана','GHC','Седи'),(61,'Гваделупа','EUR','Евро'),(62,'Гватемала','GTQ','Кетсаль'),(63,'Гвинея','GNF','Гвинейский франк'),(64,'Гвинея-Бисау','XFO','Франк КФА BCEAO'),(65,'Германия','EUR','Евро'),(66,'Гибралтар','GIP','Гибралтарский фунт'),(67,'Гондурас','HNL','Лемпира'),(68,'Гонконг','HKD','Гонконгский доллар'),(69,'Гренада','XCD','Восточно-карибский доллар'),(70,'Гренландия','DKK','Датская крона'),(71,'Греция','EUR','Евро'),(7,'Грузия','GEL','Лари'),(72,'Гуам','USD','Доллар США'),(73,'Дания','DKK','Датская крона'),(231,'Джибути','DJF','Франк Джибути'),(74,'Доминика','XCD','Восточно-карибский доллар'),(75,'Доминиканская Республика','DOP','Доминиканское песо'),(76,'Египет','EGP','Египетский фунт'),(77,'Замбия','ZMK','Замбийская квача'),(78,'Западная Сахара','MAD','Марокканский дирхам'),(79,'Зимбабве','ZWL','Доллар Зимбабве'),(8,'Израиль','ILS','Новый израильский шекель'),(80,'Индия','INR','Индийская рупия'),(81,'Индонезия','IDR','Рупия'),(82,'Иордания','JOD','Иорданский динар'),(83,'Ирак','IQD','Иракский динар'),(84,'Иран','IRR','Иранский риал'),(85,'Ирландия','IEP','Ирландский фунт'),(86,'Исландия','ISK','Исландская крона'),(87,'Испания','EUR','Евро'),(88,'Италия','EUR','Евро'),(89,'Йемен','YER','Йеменский риал'),(90,'Кабо-Верде','CVE','Эскудо Кабо-Верде'),(4,'Казахстан','KZT','Тенге'),(91,'Камбоджа','KHR','Риель'),(92,'Камерун','XAF','Франк КФА BEAC'),(10,'Канада','CAD','Канадский доллар'),(93,'Катар','QAR','Катарский риал'),(94,'Кения','KES','Кенийский шиллинг'),(95,'Кипр','CYP','Кипрский фунт'),(96,'Кирибати','AUD','Австралийский доллар'),(97,'Китай','CNY','Юань'),(98,'Колумбия','COP','Колумбийское песо'),(99,'Коморы','KMF','Франк Комор'),(100,'Конго','CDF','Конголезский франк'),(101,'Конго, демократическая республика','XAF','Франк КФА BEAC'),(102,'Коста-Рика','CRC','Костариканский колон'),(103,'Кот д`Ивуар','XOF','Франк КФА BCEAO'),(104,'Куба','CUP','Кубинское песо'),(105,'Кувейт','KWD','Кувейтский динар'),(11,'Кыргызстан','KGS','Сом'),(106,'Лаос','LAK','Кип'),(12,'Латвия','LVL','Латвийский лат'),(107,'Лесото','LSL','Лоти'),(108,'Либерия','LRD','Либерийский доллар'),(109,'Ливан','LBP','Ливанский фунт'),(110,'Ливийская Арабская Джамахирия','LYD','Ливийский динар'),(13,'Литва','LTL','Литовский лит'),(111,'Лихтенштейн','CHF','Швейцарский франк'),(112,'Люксембург','EUR','Евро'),(113,'Маврикий','MUR','Маврикийская рупия'),(114,'Мавритания','MRO','Угия'),(115,'Мадагаскар','MGA','Ариари'),(116,'Макао','MOP','Патака'),(117,'Македония','MKD','Денар'),(118,'Малави','MWK','Квача'),(119,'Малайзия','MYR','Малайзийский ринггит'),(120,'Мали','XOF','Франк КФА BCEAO'),(121,'Мальдивы','MVR','Руфия'),(122,'Мальта','EUR','Евро'),(123,'Марокко','MAD','Марокканский дирхам'),(124,'Мартиника','EUR','Евро'),(125,'Маршалловы Острова','USD','Доллар США'),(126,'Мексика','MXN','Мексиканское песо'),(127,'Микронезия, федеративные штаты','USD','Доллар США'),(128,'Мозамбик','MZN','Мозамбикский метикал'),(15,'Молдова','MDL','Молдавский лей'),(129,'Монако','EUR','Евро'),(130,'Монголия','MNT','Тугрик'),(131,'Монтсеррат','XCD','Восточно-карибский доллар'),(132,'Мьянма','MMK','Кьят'),(133,'Намибия','NAD','Доллар Намибии'),(134,'Науру','AUD','Австралийский доллар'),(135,'Непал','NPR','Непальская рупия'),(136,'Нигер','XOF','Франк КФА BCEAO'),(137,'Нигерия','NGN','Найра'),(138,'Нидерландские Антилы','ANG','Нидерландский антильский гульден'),(139,'Нидерланды','EUR','Евро'),(140,'Никарагуа','NIO','Золотая кордоба'),(141,'Ниуэ','NZD','Новозеландский доллар'),(142,'Новая Зеландия','NZD','Новозеландский доллар'),(143,'Новая Каледония','XPF','Франк КФП'),(144,'Норвегия','NOK','Норвежская крона'),(145,'Объединенные Арабские Эмираты','AED','Дирхам'),(146,'Оман','OMR','Оманский риал'),(147,'Остров Мэн','GBP','Фунт стерлингов'),(148,'Остров Норфолк','AUD','Австралийский доллар'),(149,'Острова Кайман','KYD','Доллар Островов Кайман'),(150,'Острова Кука','NZD','Новозеландский доллар'),(151,'Острова Теркс и Кайкос','USD','Доллар США'),(152,'Пакистан','PKR','Пакистанская рупия'),(153,'Палау','USD','Доллар США'),(154,'Палестинская автономия','ILS','Новый израильский шекель'),(155,'Панама','PAB','Бальбоа'),(156,'Папуа - Новая Гвинея','PGK','Кина'),(157,'Парагвай','PYG','Гуарани'),(158,'Перу','PEN','Новый соль'),(159,'Питкерн','NZD','Новозеландский доллар'),(160,'Польша','PLN','Злотый'),(161,'Португалия','EUR','Евро'),(162,'Пуэрто-Рико','USD','Доллар США'),(163,'Реюньон','EUR','Евро'),(1,'Россия','RUB','Российский рубль'),(164,'Руанда','RWF','Франк Руанды'),(165,'Румыния','ROL','Лей'),(9,'США','USD','Доллар США'),(166,'Сальвадор','SVC','Сальвадорский колон'),(167,'Самоа','WST','Тала'),(168,'Сан-Марино','EUR','Евро'),(169,'Сан-Томе и Принсипи','STD','Добра'),(170,'Саудовская Аравия','SAR','Саудовский риял'),(171,'Свазиленд','SZL','Лилангени'),(172,'Святая Елена','SHP','Фунт Святой Елены'),(173,'Северная Корея','KPW','Северокорейская вона'),(174,'Северные Марианские острова','USD','Доллар США'),(175,'Сейшелы','SCR','Сейшельская рупия'),(176,'Сенегал','XOF','Франк КФА BCEAO'),(177,'Сент-Винсент','XCD','Восточно-карибский доллар'),(178,'Сент-Китс и Невис','XCD','Восточно-карибский доллар'),(179,'Сент-Люсия','XCD','Восточно-карибский доллар'),(180,'Сент-Пьер и Микелон','EUR','Евро'),(181,'Сербия','RSD','Сербский динар'),(182,'Сингапур','SGD','Сингапурский доллар'),(183,'Сирийская Арабская Республика','SYP','Сирийский фунт'),(184,'Словакия','EUR','Евро'),(185,'Словения','EUR','Евро'),(186,'Соломоновы Острова','SBD','Доллар Соломоновых Островов'),(187,'Сомали','SOS','Сомалийский шиллинг'),(188,'Судан','SDG','Суданский фунт'),(189,'Суринам','SRD','Суринамский доллар'),(190,'Сьерра-Леоне','SLL','Леоне'),(16,'Таджикистан','TJS','Сомони'),(191,'Таиланд','THB','Бат'),(192,'Тайвань','TWD','Новый тайваньский доллар'),(193,'Танзания','TZS','Танзанийский шиллинг'),(194,'Того','XOF','Франк КФА BCEAO'),(195,'Токелау','NZD','Новозеландский доллар'),(196,'Тонга','TOP','Паанга'),(197,'Тринидад и Тобаго','TTD','Доллар Тринидада и Тобаго'),(198,'Тувалу','AUD','Австралийский доллар'),(199,'Тунис','TND','Тунисский динар'),(17,'Туркмения','TMM','Манат'),(200,'Турция','TRL','Турецкая лира'),(201,'Уганда','UGS','Угандийский шиллинг'),(18,'Узбекистан','UZS','Узбекский сум'),(2,'Украина','UAH','Гривна'),(202,'Уоллис и Футуна','XPF','Франк КФП'),(203,'Уругвай','UYP','Уругвайское песо'),(204,'Фарерские острова','DKK','Датская крона'),(205,'Фиджи','FJD','Доллар Фиджи'),(206,'Филиппины','PHP','Филиппинское песо'),(207,'Финляндия','EUR','Евро'),(208,'Фолклендские острова','FKP','Фунт Фолклендских островов'),(209,'Франция','EUR','Евро'),(210,'Французская Гвиана','EUR','Евро'),(211,'Французская Полинезия','XPF','Франк КФП'),(212,'Хорватия','HRK','Хорватская куна'),(213,'Центрально-Африканская Республика','XAF','Франк КФА BEAC'),(214,'Чад','XAF','Франк КФА BEAC'),(230,'Черногория','EUR','Евро'),(215,'Чехия','CZK','Чешская крона'),(216,'Чили','CLP','Чилийское песо'),(217,'Швейцария','CHF','Швейцарский франк'),(218,'Швеция','SEK','Шведская крона'),(219,'Шпицберген и Ян Майен','NOK','Норвежская крона'),(220,'Шри-Ланка','LKR','Шри-ланкийская рупия'),(221,'Эквадор','USD','Доллар США'),(222,'Экваториальная Гвинея','XAF','Франк КФА BEAC'),(223,'Эритрея','ERN','Накфа'),(14,'Эстония','EUR','Евро'),(224,'Эфиопия','ETB','Эфиопия'),(226,'Южная Корея','KRW','Вона'),(227,'Южно-Африканская Республика','ZAR','Рэнд'),(228,'Ямайка','JMD','Ямайский доллар'),(229,'Япония','JPY','Иена');
/*!40000 ALTER TABLE `countries` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `country_activ`
--

DROP TABLE IF EXISTS `country_activ`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `country_activ` (
  `id` int NOT NULL AUTO_INCREMENT,
  `country_id` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `country_activ`
--

LOCK TABLES `country_activ` WRITE;
/*!40000 ALTER TABLE `country_activ` DISABLE KEYS */;
INSERT INTO `country_activ` VALUES (1,1),(2,160);
/*!40000 ALTER TABLE `country_activ` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `file_mail`
--

DROP TABLE IF EXISTS `file_mail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `file_mail` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int NOT NULL DEFAULT '0',
  `file` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `file_mail`
--

LOCK TABLES `file_mail` WRITE;
/*!40000 ALTER TABLE `file_mail` DISABLE KEYS */;
/*!40000 ALTER TABLE `file_mail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `js`
--

DROP TABLE IF EXISTS `js`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `js` (
  `id` int NOT NULL AUTO_INCREMENT,
  `js` varchar(255) DEFAULT NULL,
  `css` varchar(255) DEFAULT NULL,
  `id_str` int NOT NULL DEFAULT '0',
  `id_pstr` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `js`
--

LOCK TABLES `js` WRITE;
/*!40000 ALTER TABLE `js` DISABLE KEYS */;
INSERT INTO `js` VALUES (1,'admin','admin',3,0),(2,'jqueryui',NULL,3,0),(3,'ckeditor/ckeditor',NULL,3,0),(4,'ckeditor/ckeditor','admin',4,0),(5,'admin',NULL,4,0),(6,'jqueryui',NULL,4,0),(7,'admin','admin',11,0),(8,'admin','admin',13,0);
/*!40000 ALTER TABLE `js` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kassa_order`
--

DROP TABLE IF EXISTS `kassa_order`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kassa_order` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `summ` float(10,2) NOT NULL DEFAULT '0.00',
  `way` int NOT NULL DEFAULT '1',
  `data_order` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `data_exec` datetime DEFAULT NULL,
  `sign` varchar(50) NOT NULL DEFAULT '',
  `plat_id` int NOT NULL DEFAULT '0',
  `status` int NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kassa_order`
--

LOCK TABLES `kassa_order` WRITE;
/*!40000 ALTER TABLE `kassa_order` DISABLE KEYS */;
/*!40000 ALTER TABLE `kassa_order` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kassa_user`
--

DROP TABLE IF EXISTS `kassa_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kassa_user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `sum` float(10,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kassa_user`
--

LOCK TABLES `kassa_user` WRITE;
/*!40000 ALTER TABLE `kassa_user` DISABLE KEYS */;
/*!40000 ALTER TABLE `kassa_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `keys_shablon`
--

DROP TABLE IF EXISTS `keys_shablon`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `keys_shablon` (
  `id` int NOT NULL AUTO_INCREMENT,
  `shablon_id` int NOT NULL DEFAULT '0',
  `ky` varchar(255) DEFAULT NULL,
  `vl` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `keys_shablon`
--

LOCK TABLES `keys_shablon` WRITE;
/*!40000 ALTER TABLE `keys_shablon` DISABLE KEYS */;
/*!40000 ALTER TABLE `keys_shablon` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `lang_photosn`
--

DROP TABLE IF EXISTS `lang_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lang_photosn` (
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
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `lang_photosn`
--

LOCK TABLES `lang_photosn` WRITE;
/*!40000 ALTER TABLE `lang_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `lang_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `langs`
--

DROP TABLE IF EXISTS `langs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `langs` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `pref` varchar(10) DEFAULT NULL,
  `vl` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `langs`
--

LOCK TABLES `langs` WRITE;
/*!40000 ALTER TABLE `langs` DISABLE KEYS */;
INSERT INTO `langs` VALUES (1,'Русский','ru','7');
/*!40000 ALTER TABLE `langs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `log_action`
--

DROP TABLE IF EXISTS `log_action`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `log_action` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `action_id` int NOT NULL DEFAULT '0',
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log_action`
--

LOCK TABLES `log_action` WRITE;
/*!40000 ALTER TABLE `log_action` DISABLE KEYS */;
/*!40000 ALTER TABLE `log_action` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mail`
--

DROP TABLE IF EXISTS `mail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mail` (
  `id` int NOT NULL AUTO_INCREMENT,
  `from_id` int NOT NULL DEFAULT '0',
  `from_mail` varchar(255) DEFAULT NULL,
  `to_id` int NOT NULL DEFAULT '0',
  `to_mail` varchar(255) DEFAULT NULL,
  `head` text,
  `body` text,
  `type` int NOT NULL DEFAULT '0',
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `rd` int NOT NULL DEFAULT '0',
  `spam` int NOT NULL DEFAULT '0',
  `mailing_id` int NOT NULL DEFAULT '0',
  `status` int DEFAULT NULL,
  `open_action` int NOT NULL DEFAULT '0',
  `link_action` int NOT NULL DEFAULT '0',
  `user_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mail`
--

LOCK TABLES `mail` WRITE;
/*!40000 ALTER TABLE `mail` DISABLE KEYS */;
/*!40000 ALTER TABLE `mail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mailbox`
--

DROP TABLE IF EXISTS `mailbox`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `mailbox` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `dkim` text,
  `dmarc` text,
  `spf` text,
  `pass` varchar(20) DEFAULT NULL,
  `mail` varchar(255) DEFAULT NULL,
  `v_dkim` int NOT NULL DEFAULT '0',
  `v_dmarc` int NOT NULL DEFAULT '0',
  `v_spf` int NOT NULL DEFAULT '0',
  `server_id` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mailbox`
--

LOCK TABLES `mailbox` WRITE;
/*!40000 ALTER TABLE `mailbox` DISABLE KEYS */;
/*!40000 ALTER TABLE `mailbox` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `network`
--

DROP TABLE IF EXISTS `network`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `network` (
  `id` int NOT NULL AUTO_INCREMENT,
  `network` varchar(255) NOT NULL DEFAULT '',
  `soc_id` int NOT NULL DEFAULT '0',
  `user_id` int NOT NULL DEFAULT '0',
  `hash` varchar(255) DEFAULT NULL,
  `ferst_name` varchar(255) DEFAULT NULL,
  `last_name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `network`
--

LOCK TABLES `network` WRITE;
/*!40000 ALTER TABLE `network` DISABLE KEYS */;
/*!40000 ALTER TABLE `network` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `order_prouct`
--

DROP TABLE IF EXISTS `order_prouct`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `order_prouct` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `product_id` int NOT NULL DEFAULT '0',
  `status` int NOT NULL DEFAULT '0',
  `date_order` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_prouct`
--

LOCK TABLES `order_prouct` WRITE;
/*!40000 ALTER TABLE `order_prouct` DISABLE KEYS */;
/*!40000 ALTER TABLE `order_prouct` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `order_unit`
--

DROP TABLE IF EXISTS `order_unit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `order_unit` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` varchar(255) NOT NULL DEFAULT '0',
  `product_id` int DEFAULT NULL,
  `order_id` int DEFAULT NULL,
  `status` int NOT NULL DEFAULT '0',
  `data` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `coun` int NOT NULL DEFAULT '1',
  `shop_id` int DEFAULT NULL,
  `deliver` int NOT NULL DEFAULT '1',
  `temp_user` varchar(255) NOT NULL DEFAULT '',
  `size` int NOT NULL DEFAULT '0',
  `prezent` int NOT NULL DEFAULT '0',
  `prezent_name` varchar(255) NOT NULL DEFAULT '',
  `prezent_phone` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_unit`
--

LOCK TABLES `order_unit` WRITE;
/*!40000 ALTER TABLE `order_unit` DISABLE KEYS */;
/*!40000 ALTER TABLE `order_unit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `orders` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int DEFAULT NULL,
  `status` int NOT NULL DEFAULT '1',
  `chek_conf` varchar(255) DEFAULT NULL,
  `sum` varchar(255) DEFAULT NULL,
  `deliver` int NOT NULL DEFAULT '0',
  `chek` varchar(255) DEFAULT NULL,
  `plat_id` int NOT NULL DEFAULT '0',
  `shop_id` int NOT NULL DEFAULT '0',
  `data_order` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `packages`
--

DROP TABLE IF EXISTS `packages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `packages` (
  `id` int NOT NULL AUTO_INCREMENT,
  `drop_id` int NOT NULL DEFAULT '0',
  `drp` varchar(255) DEFAULT NULL,
  `reciver` varchar(255) DEFAULT NULL,
  `reciver_id` int NOT NULL DEFAULT '0',
  `price` int NOT NULL DEFAULT '0',
  `pay` int NOT NULL DEFAULT '0',
  `status` int NOT NULL DEFAULT '0',
  `product` varchar(255) DEFAULT NULL,
  `source` int NOT NULL DEFAULT '0',
  `id_in_source` int NOT NULL DEFAULT '0',
  `tracking` varchar(255) DEFAULT NULL,
  `ems_track` varchar(255) DEFAULT NULL,
  `ftf` int NOT NULL DEFAULT '0',
  `paid` int NOT NULL DEFAULT '0',
  `lable` varchar(255) DEFAULT NULL,
  `holder` varchar(255) DEFAULT NULL,
  `date_post` varchar(255) DEFAULT NULL,
  `tarck_link` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `packages`
--

LOCK TABLES `packages` WRITE;
/*!40000 ALTER TABLE `packages` DISABLE KEYS */;
/*!40000 ALTER TABLE `packages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `param_ak`
--

DROP TABLE IF EXISTS `param_ak`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `param_ak` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `login_y` varchar(255) DEFAULT NULL,
  `pass_y` varchar(255) DEFAULT NULL,
  `mail` varchar(255) DEFAULT NULL,
  `server` varchar(255) DEFAULT NULL,
  `login_m` varchar(255) DEFAULT NULL,
  `passwd_m` varchar(255) DEFAULT NULL,
  `port` varchar(255) DEFAULT NULL,
  `pass_vps` varchar(255) DEFAULT NULL,
  `ip_vps` varchar(255) DEFAULT NULL,
  `pass_baza` varchar(255) DEFAULT NULL,
  `login_pay` varchar(255) DEFAULT NULL,
  `pass_pay` varchar(255) DEFAULT NULL,
  `confirm_pay` varchar(255) DEFAULT NULL,
  `backdata` datetime DEFAULT NULL,
  `froze` int NOT NULL DEFAULT '0',
  `count_user` int NOT NULL DEFAULT '100000000',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `param_ak`
--

LOCK TABLES `param_ak` WRITE;
/*!40000 ALTER TABLE `param_ak` DISABLE KEYS */;
/*!40000 ALTER TABLE `param_ak` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `parser`
--

DROP TABLE IF EXISTS `parser`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `parser` (
  `id` int NOT NULL AUTO_INCREMENT,
  `url` varchar(255) DEFAULT NULL,
  `login` varchar(255) DEFAULT NULL,
  `passwd` varchar(255) DEFAULT NULL,
  `date_scan` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `status_scan` int NOT NULL DEFAULT '0',
  `file` varchar(255) DEFAULT NULL,
  `comment` text,
  `rules` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parser`
--

LOCK TABLES `parser` WRITE;
/*!40000 ALTER TABLE `parser` DISABLE KEYS */;
/*!40000 ALTER TABLE `parser` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `payment_system_item`
--

DROP TABLE IF EXISTS `payment_system_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `payment_system_item` (
  `id` int NOT NULL AUTO_INCREMENT,
  `parent_id` int NOT NULL DEFAULT '0',
  `name` varchar(255) DEFAULT NULL,
  `descr` text,
  `ord` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `payment_system_item`
--

LOCK TABLES `payment_system_item` WRITE;
/*!40000 ALTER TABLE `payment_system_item` DISABLE KEYS */;
/*!40000 ALTER TABLE `payment_system_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `payment_systems`
--

DROP TABLE IF EXISTS `payment_systems`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `payment_systems` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `cod` varchar(255) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `payment_systems`
--

LOCK TABLES `payment_systems` WRITE;
/*!40000 ALTER TABLE `payment_systems` DISABLE KEYS */;
/*!40000 ALTER TABLE `payment_systems` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `retriv_pas`
--

DROP TABLE IF EXISTS `retriv_pas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `retriv_pas` (
  `id` int NOT NULL AUTO_INCREMENT,
  `check_sum` varchar(255) DEFAULT NULL,
  `mail` varchar(255) DEFAULT NULL,
  `date_create` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `retriv_pas`
--

LOCK TABLES `retriv_pas` WRITE;
/*!40000 ALTER TABLE `retriv_pas` DISABLE KEYS */;
/*!40000 ALTER TABLE `retriv_pas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roboks`
--

DROP TABLE IF EXISTS `roboks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `roboks` (
  `id` int NOT NULL AUTO_INCREMENT,
  `login` varchar(255) DEFAULT NULL,
  `passwd` varchar(255) DEFAULT NULL,
  `passwd_vn` varchar(255) DEFAULT NULL,
  `url_answer1` varchar(255) DEFAULT NULL,
  `url_answer2` varchar(255) DEFAULT NULL,
  `url_answer3` varchar(255) DEFAULT NULL,
  `com` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roboks`
--

LOCK TABLES `roboks` WRITE;
/*!40000 ALTER TABLE `roboks` DISABLE KEYS */;
/*!40000 ALTER TABLE `roboks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roboks_order`
--

DROP TABLE IF EXISTS `roboks_order`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `roboks_order` (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL DEFAULT '0',
  `sum` float(10,2) NOT NULL DEFAULT '0.00',
  `descr` varchar(255) DEFAULT NULL,
  `data_order` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `status` int NOT NULL DEFAULT '0',
  `sign` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roboks_order`
--

LOCK TABLES `roboks_order` WRITE;
/*!40000 ALTER TABLE `roboks_order` DISABLE KEYS */;
/*!40000 ALTER TABLE `roboks_order` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shop_photosn`
--

DROP TABLE IF EXISTS `shop_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `shop_photosn` (
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
-- Dumping data for table `shop_photosn`
--

LOCK TABLES `shop_photosn` WRITE;
/*!40000 ALTER TABLE `shop_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `shop_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shops`
--

DROP TABLE IF EXISTS `shops`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `shops` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `url` varchar(255) DEFAULT NULL,
  `coment` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shops`
--

LOCK TABLES `shops` WRITE;
/*!40000 ALTER TABLE `shops` DISABLE KEYS */;
/*!40000 ALTER TABLE `shops` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `size`
--

DROP TABLE IF EXISTS `size`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `size` (
  `id` int NOT NULL AUTO_INCREMENT,
  `size` varchar(255) DEFAULT NULL,
  `sale` int NOT NULL DEFAULT '0',
  `sale_old` int NOT NULL DEFAULT '0',
  `sale_two` int NOT NULL DEFAULT '0',
  `sale_three` int NOT NULL DEFAULT '0',
  `sale_opt` int NOT NULL DEFAULT '0',
  `product_id` int NOT NULL DEFAULT '0',
  `balance` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `size`
--

LOCK TABLES `size` WRITE;
/*!40000 ALTER TABLE `size` DISABLE KEYS */;
/*!40000 ALTER TABLE `size` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `social_networks`
--

DROP TABLE IF EXISTS `social_networks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `social_networks` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `login` varchar(255) DEFAULT NULL,
  `passwd` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `social_networks`
--

LOCK TABLES `social_networks` WRITE;
/*!40000 ALTER TABLE `social_networks` DISABLE KEYS */;
/*!40000 ALTER TABLE `social_networks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `status_mail`
--

DROP TABLE IF EXISTS `status_mail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `status_mail` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `status_mail`
--

LOCK TABLES `status_mail` WRITE;
/*!40000 ALTER TABLE `status_mail` DISABLE KEYS */;
/*!40000 ALTER TABLE `status_mail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `temp_user`
--

DROP TABLE IF EXISTS `temp_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `temp_user` (
  `id` int NOT NULL DEFAULT '0',
  `check_sum` varchar(255) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  `passwd` varchar(255) DEFAULT NULL,
  `mail` varchar(255) DEFAULT NULL,
  `phone` int DEFAULT NULL,
  `adress` varchar(255) DEFAULT NULL,
  `data` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `temp_user`
--

LOCK TABLES `temp_user` WRITE;
/*!40000 ALTER TABLE `temp_user` DISABLE KEYS */;
/*!40000 ALTER TABLE `temp_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_photosn`
--

DROP TABLE IF EXISTS `user_photosn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user_photosn` (
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
-- Dumping data for table `user_photosn`
--

LOCK TABLES `user_photosn` WRITE;
/*!40000 ALTER TABLE `user_photosn` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_photosn` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id` int NOT NULL AUTO_INCREMENT,
  `old_user_id` varchar(255) NOT NULL DEFAULT '',
  `region_id` int DEFAULT NULL,
  `login` varchar(255) DEFAULT NULL,
  `passwd` varchar(255) DEFAULT NULL,
  `level` int DEFAULT NULL,
  `mail` varchar(255) DEFAULT NULL,
  `activity` datetime DEFAULT NULL,
  `checksum` varchar(255) DEFAULT NULL,
  `count_of_err` int DEFAULT NULL,
  `antibot` int DEFAULT NULL,
  `antispam` int NOT NULL DEFAULT '0',
  `name` varchar(255) DEFAULT NULL,
  `gender` int NOT NULL DEFAULT '0',
  `phone` varchar(255) DEFAULT NULL,
  `icq` varchar(255) DEFAULT NULL,
  `www` varchar(255) DEFAULT NULL,
  `skype` varchar(150) DEFAULT NULL,
  `city_id` int NOT NULL DEFAULT '0',
  `street` varchar(255) NOT NULL DEFAULT '',
  `hous` varchar(255) NOT NULL DEFAULT '',
  `building` varchar(255) NOT NULL DEFAULT '',
  `apartament` varchar(255) NOT NULL DEFAULT '',
  `about_me` text,
  `confirm` int NOT NULL DEFAULT '0',
  `user_type` int DEFAULT NULL,
  `bank_account` varchar(255) DEFAULT NULL,
  `web_money` varchar(255) DEFAULT NULL,
  `yandex_money` varchar(255) DEFAULT NULL,
  `oldname` varchar(255) DEFAULT NULL,
  `midlename` varchar(255) DEFAULT NULL,
  `spam` int NOT NULL DEFAULT '0',
  `parent_id` int NOT NULL DEFAULT '0',
  `country_id` int NOT NULL DEFAULT '0',
  `birthday` varchar(255) DEFAULT NULL,
  `adress` varchar(255) DEFAULT NULL,
  `date_reg` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `post` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'',NULL,'admin','0d31616d0759857128adc8990b6fd69c',10,NULL,'2023-11-07 14:03:07','019a3f1c861d6a96905a81705b5ad4f9',NULL,NULL,0,'Администратор',0,NULL,NULL,NULL,NULL,0,'','','','',NULL,0,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,NULL,NULL,'2016-09-28 12:30:01',NULL);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-11-07 14:15:19
