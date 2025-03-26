# Vdcgi

Welcome to your new gem! In this directory, you'll find the files you need to be able to package up your Ruby library into a gem. Put your Ruby code in the file `lib/vdcgi`. To experiment with that code, run `bin/console` for an interactive prompt.

## Installation

```bash
bundle add UPDATE_WITH_YOUR_GEM_NAME_IMMEDIATELY_AFTER_RELEASE_TO_RUBYGEMS_ORG
```

If bundler is not being used to manage dependencies, install the gem by executing:

```bash
gem install UPDATE_WITH_YOUR_GEM_NAME_IMMEDIATELY_AFTER_RELEASE_TO_RUBYGEMS_ORG
```

## Usage

Gem vdcgi is designed to help in the rapid development of web sites. It contains all the necessary functionality that allows you to quickly implement everything that is usually required in web development. Gem is completely written in the C language, respectively, all the functionality that it provides works many times faster than analogs written in Ruby
To work with gem, you need to connect it require 'vdcgi'. After that, you will have access to the classes
Vdcgi
VdMainapp
VdUser
VdArticle
VdKassa
VdBitcoin
VdStatistic
VdVideo
VdRobo_kassa
VdProduct
VdNet
VdInter_kassa
VdAdmin
VdMessages
VdImg
You can add your own methods to each class
When initializing the main Vdcgi class, it is passed the path to the configuration file (vd = Vdcgi.new("the path/to/the file")). All other classes are initialized with a Vdcgi instance (e.g. VdMainapp.new(vd))
Example config file
mysql database user=user
mysql database password=passwd
port=port
host=host
database name=db
database name=ip
domain where the site is hosted=domain
base url=url
number of initialized connections to the database=limit
if 1 then the folder /path to the root folder of the site/congifapp/ creates a config file in which a full log is written including all requests to the database=devel
here the trusted access level of the connecting user is specified, starting from which the injectionmysql prevention functions are disabled at the user level from 0 to 10 0 - not authorized 1 - blocked ... 10 administrator=access

Please note = the value of the parameters comes before the parameter. This is done intentionally.

To work gem-mu needs at least 2 databases templates can be downloaded here in the mysql folder. Template shablon.sql is the main one. Templates rushablon.sql enshablon.sql and so on are used to support multilingualism

After requiring 'vdcgi' the following classes become available
Vdcgi
VdMainapp
VdUser
VdArticle
VdKassa
VdBitcoin
VdStatistic
VdVideo
VdRobo_kassa
VdProduct
VdNet
VdInter_kassa
VdAdmin
VdMessages
VdImg

When the main class (Vdcgi) is initialized the following happens
1 Parsing all parameters passed by the POST and GET methods they become available globally as hash in the variable vdcgi.param
2 An array of connections to the mysq database is initialized
3 The access level of the connected user is checked (if the login and pass parameters are passed) their id is determined. Both also become available globally as vdcgi.level and vdcgi.user_id respectively. If the user is not authorized, both = 0.

In addition, the Vdcgi class contains the following functions

getCockP
Returns the cock cps when authorized
Passed parameters
Does not accept parameters

translitEnglR
Converts a Russian string to English transliteration
Passed parameters
String to be converted
Return value
string in transliteration

exsql qw, par
Executes a query on the select database. Returns the query result.
Passed parameters
qv — query string where values ​​should be substituted - ~
par — array of parameters
for example
ar = exsq «select id, adress from users where phone = '~' or name = '~'», ['222222','Vasya']
will execute the query «select id, adress from users where phone = '222222' or name = 'Vasya'»
Return value
Array of arrays. Nested array — indexes of returned values ​​coincide with the ordinal number of the name in the table
In the example above, the id — of the first «Vasya» can be obtained as ar[0][0] Its address as ar[0][1]
And for the second Vasya (if there is one) as ar[1][0] and ar[1][1]

exsql_h qw, par
The same as exsql qw, par but returns an array of hashes — the parameter values ​​are the names of the columns in the database

execsql qw, par
Executes a query on the insert, update database.

Passed parameters
qv — query string in the place where the values ​​should be substituted - ~
par — array of parameters
for example
ar = exsq «insert users set phone = '~', name = '~'», ['222222','Vasya']
will execute the query « insert users set phone = '222222', name = 'Vasya'»
Return value
parent class

insert_id
Does not accept parameters
Return value
Returns the Id of the last record inserted by the Insert query

lang
Does not accept parameters
Return value
Returns a string of the langbaza type.
where lang is the language prefix for the database (ru and so on)
baza is the database name
Can be used in queries to language database tables

route idstr, parent_id, level, id_usr

Passed parameters: idstr — page id
parent_id — parent id or 0 if the root page
level — minimum access level
id_usr — user id if the page is only available to one user or 9
Return value
Template name

header
Does not accept parameters
Return value
Prints html header

user_param
Does not accept parameters
Return value
Returns a hash with the parameters of the current user. The following elements are present
name, login, level (int), post, address, gender, birthday, phone, id (int), pagewords

pagewords idstr, parent_id, posit
Passed parameters page id
parent_id — page parent id
posit — position on the page
Return value
phrase

get_config
Does not accept parameters
Return value
Returns the contents of the config file as a hash
Fields: "user", "passwd", "port", "host", "db", "ip", "domain", "url", "limit"

The remaining classes contain the following functions

VdMainapp class

write_title tg, idstr, idpstr
Gets information from the seotexts table. Most often used to get SEO information keywords description title, but can be used to get any fields of this table. Full list of fields: id, titl, keyw, descr, tegs, link, arti, str, pstr, ppstr, reg, shablon, level, user_id
Passed parameters: tg — name of the table field we want to get
idstr - page id
idpstr — page parent id
Return value
Contents of the corresponding field in the seotexts table

listcontacts
Gets data from the contacts table
Does not accept parameters
Return value
Hash with the fields name, adress, phone, mail, icq, skype, director, about, contract, frommail, server, port, login, passwd, sendmail

regionpage str
Gets the value of the region_id field for the specified page
Passed parameters: str — page id
Return value
value of the region_id field as int

menu region, parent
Selects all pages from the pages table with the specified region_id and parent_id
Passed parameters: region - corresponding region_id,
parent - corresponding parent_id
Return value
Array of hashes
Each array element (hash) contains the fields: id, title, text_iner, positions, link, img, parent_id
for the corresponding page

javames
outputs a javascript array of service messages (from the javames table)

Does not accept parameters
Return value
outputs a javascript array of service messages (from the javames table)

namepage str
Gets the name of the pages
Passed parameters: str — page id
Return value
String — page name

accesspage str
Gets the access level for the page
Passed parameters: str — page id
Return value
Number — access level

fotos table, id, size, plase, slider, microdata
Returns an array of strings, each of which is ready <img> tag for one image associated with the requested object
Passed parameters:
table name of the table of objects whose image you want to get (for example, page — page icons, user — user avatars, product — product photos)
id — id of the object in the table whose image you want to get
size — index of the folder from which to get the image (the size usually depends on the index and is set when loading the image) Possible values ​​from 1 to 6
plase - limit on the number of images received 0 = 1
slider - if not 0, then tags for the highslide slide show are added (the large image is taken from the folder with the number = slider)
microdata — if not 0, then tags of the Google markup microdata are added
Return value
Array of strings, each of which is an <img> tag

fotoslink table, id, size, plase
Returns an array of strings, each of which is a link starting from the root of the web server for one image associated with the requested object
Passed parameters: id — object id in the table whose image we want to get
size — index of the folder from which to get the image (the size usually depends on the index and is set when loading the image) Possible values ​​from 1 to 6
plase — limit on the number of images received 0 = 1
Return value
Array of strings, each of which is a link starting from the root of the web server for one image associated with the requested object

sendmail to, them, message, frommail

Sends a message via postfix (the corresponding software must be installed)
Passed parameters
to — who the message is for. Can be either an email address or a user ID on the site
them — message subject
message — message body
frommail — from whom (optional)

Return value
Parent class

listcounryactin
Get active countries
Does not accept parameters
Return value
Returns an array of hashes. Each hash has the fields country_id, name

listlang
Get a list of languages ​​and prefixes for language bases
Does not accept parameters
Return value
Returns an array of hashes. Each hash has the fields id, name, pref

getlang id
Get language parameters and prefix for the database
Passed parameters: id — language id from the lang table
Return value
Hash with the fields id, name, pref

writelink str, parent, level, user
Get a link to the page
Passed parameters:

str — page id
parent — parent id
level — access level
user — user id 0 — for all
Return value
Value of the link field in the seotexts table for a given page

region_ex
Get a list of active regions (from the region_exist and sity tables)
Does not accept parameters
Return value
Array of hashes. Each hash has the fields id, region_exist. region_exist_sity_id, sity

cityname id
Get the name of the city from the sity table
Passed parameters:
id — city id
Return value
String — city name

get_class id
Get a list of classes for the page from the class table
Passed parameters:
id — page id
Return value
Array of hashes. Each hash has id, class fields

get_js id
Get a list of js and css classes for the page
Passed parameters:
id — page id
Return value
Array of hashes. Each hash has fields id, js, css (js and css - without extension)

VdUser class
username id
Get user name
Passed parameters: id - user id
Return value
If the user is found, the name field is filled in, then it is returned. If it is not filled in, then the login field is returned. If the user is not found, then "Guest"

userparam id
Get all user parameters
Passed parameters: id - user id
Return value
Hash with fields: id, old_user_id, region_id, login, level, mail, activity, checksum, count_of_err, antibot, antispam, name, gender, phone, icq, www, skype, city_id, street, hous, building, apartament, about_me, confirm, user_type, bank_account, web_money, yandex_money, oldname, midlename, spam, parent_id, country_id, birthday, adress, date_reg
VdArticle class
conuntarticle
Get the number of articles for the language we are in
Does not accept parameters
Return value
Number of articles for the language we are in (int)

conuntarticlenew period
Get the number of articles added for period days starting from the current date
Passed parameters: period — number of days
Return value
Number of articles added for the language we are in for period days starting from the current date (int)

listarticles sort, start
Get the list of articles
Passed parameters:

sort — sort order 1 — name, 2 — lid, 3 — body, 4 — lk, 5 — user_id, 6 — descr
start — starting from which id to display the number of articles in the output is determined by the limit value in the config file
Return value
Array of hashes. Each hash contains the fields id, name, lid, body, lk, user_id, dt

set_readarticle user, article
Mark the article as read by this user
Passed parameters: user — user id, article — article id
Return value
Parent class

get_readarticle user, article
Check if the user has read the article
Passed parameters:
user — user id
article — article id
Return value
If read, then the number is > 0, if not, then 0

get_article id
Get the article
Passed parameters:
id — article id
Return value
Hash with the fields: id, name, lid, body, user_id, product_id, category_id, subcategory_id, subsubcategory_id, dt, wv, autor, access, lk

set_comment_article article_id, user_id, body
Write a comment to the article
Passed parameters:
article_id - article id
user_id — user id
body — comment text
Return value
parent class

set_wiewart id
Increase the number of views for the article by 1
Passed parameters:
id — article id
Return value
parent class

set_articles idr, name, lid, body, autor, access, block, user_id, product_id, category_id, subcategory_id, subsubcategory_id, titl, keyw, descr
Add or edit an article
Passed parameters:
idr — article id If = 0 then the article is added if not then edited
titl, keyw, descr — corresponding fields in the seotexts table
other parameters — fields in the articles table
Return value
parent class

countcomentrticle id
Get the number of comments to the article
Passed parameters:
id — article id
Return value
Number of comments (int)

listcomentrticle id
Get all comments to the article
Passed parameters:
id — article id
Return value
Array of hashes. Each hash has the fields id, user_id, dt, body, rd

VdKassa class
unitbascet usr
Get the cost of all orders in the user's cart
Passed parameters:
usr — user id
Return value
Cost of all orders in the user's cart (int)

listpayemtsystem
Get a list of all available payment methods
Does not accept parameters
Return value
Array of hashes. Each hash has the fields id, name

listorderuser usr, status
We get all user orders with a breakdown
Passed parameters:
usr — user id
status — order status 1 — formed 2 — paid 3 — delivered 4 — closed (optional)
Return value
array of hashes. Each hash contains the fields: id, status, sum, data_order, deliver, plat_id, shop_id, shop_name, list_prod
The last is an array of hashes, each of which contains the fields: product_id, size, shop_id, deliver, name, category_id, sale

balansuser usr
Get the user's balance
Passed parameters:
usr — user id
Return value
How much money is in the user's account (float)

listorderkassausers
Output a list of all cash transactions for all users
Does not accept parameters
Return value

Returns an array of hashes. Each hash has the fields: id, summ, user_id, way, user_name, data_order, data_exec, plat_id, status

conunt_order type
Returns the number of transactions at the cash desk
Passed parameters:
type — transaction type (input — 1/output — 2)
Return value
Number of transactions as int

outsumadmin
Returns the amount entered by the admin
Does not accept parameters
Return value
Amount as a string

orderinerall
Total amount of deposits at the cash desk for all time
Does not accept parameters
Return value
Amount as a string

orderoutall
Total amount of withdrawn funds at the cash desk for all time
Does not accept parameters
Return value
Amount as a string

listdepositout
Returns a list of all withdrawn funds for all time
Passed parameters
Does not accept parameters
Return value
Array of hashes. Each hash has the fields: id, summ, user_id, way, user_name, data_order, data_exec, plat_id, status

VdNet class

chekMailbox domain, port, mail
Checks if a mailbox exists by opening an smtp session
Passed parameters
domain — server domain
port — server port
mail — the mailbox being checked
Return value
If successful, the string SUCCESS
If unsuccessful, the response from the remote server

getHttpGet url, prt, script, header, param
We execute a get request via simple http
Passed parameters
url — address
prt - port
script — path to the file
header — array of strings. Each line is an http header
param is a parameter string in the form parameter=value&parameter2=value
Return value
Remote server response with headers

getHttpGets url, prt, script, header, param
Execute a get request over https
Passed parameters
url is an address
prt is a port
script is a path to the file
header is an array of strings. Each line is an http header
param is a parameter string in the form parameter=value&parameter2=value
Return value
Remote server response with headers

getHttpPosts url, prt, script, header, param
Execute a post request over https
Passed parameters
url is an address
prt is a port
script is a path to the file
header is an array of strings. Each line is an http header
param is a parameter string in the form parameter=value&parameter2=value
Return value
Remote server response with headers

getPost url, prt, script, header, param
Execute post request via http
Passed parameters
url is address
prt is port
script is path to file
header is an array of strings. Each line is an http header
param is a parameter string in the form parameter=value&parameter2=value
Return value
Remote server response with headers

getHttpJson url, prt, script, header, json
Execute request via http
Passed parameters
url is address
prt is port
script is path to file
header is an array of strings. Each line is an http header
json is data in json format
Return value
Remote server response with headers

The list of created classes and functions is constantly being added. Therefore, this description may not be complete. For the most current version, write to aleksandrshved@gmai.com

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake test` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and the created tag, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/[USERNAME]/vdcgi. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/[USERNAME]/vdcgi/blob/master/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the Vdcgi project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/[USERNAME]/vdcgi/blob/master/CODE_OF_CONDUCT.md).
