#ifndef _xsqlDef_h__
#define _xsqlDef_h__


#define X_SQL_USER_CREATE           \
    "create table user( id integer primary key autoincrement, name nvarchar(32), password nvarchar(32), type integer)"
#define X_SQL_USER_INSERT_ADMIN     \
    "insert into user(name, password, type) values('admin', 'secret', 0)"
#define X_SQL_USER_INSERT_XXX       \
    "insert into user(name, password, type) values('%s', '%s', '%d')"
#define X_SQL_USER_QUERY_XXX        \
    "select * from user where name = '&s';"

#define X_SQL_CUSTOMER_CREATE       \
    "create table customer( id integer primary key autoincrement, name nvarchar(32), tel nvarchar(32), qq nvarchar(32))"
#define X_SQL_CUSTOMER_INSERT_XXX   \
    "insert into customer(name, tel, qq) values('%s', '%s', '%s')"


#define X_SQL_COLOR_CREATE      \
    "create table color( id integer primary key autoincrement, card integer, name nvarchar(32), rgb integer)"
#define X_SQL_COLOR_INSERT_XXX  \
    "insert into color(card, name, rgb) values('%d', '%s', '%d')"
#define X_SQL_COLOR_DELETE_WHERE_CARD  \
    "delete from color where card = %d"
#define X_SQL_COLOR_UPDATE_WHERE_ID   \
    "update color set card = %d, name = '%s', rgb = %d where id = %d"
#define X_SQL_COLOR_QUERY_ALL   \
    "select * from color"

#define X_SQL_MATERIALS_CREATE      \
    "create table materials( id integer primary key autoincrement, name nvarchar(32), color integer, weight double)"
#define X_SQL_MATERIALS_INSERT_XXX  \
    "insert into materials(name, color, weight) values('%s', '%d', '%d')"

#endif