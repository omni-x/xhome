#ifndef _xsqlDef_h__
#define _xsqlDef_h__


#define X_SQL_USER_CREATE           \
    "create table user( id integer primary key autoincrement, name nvarchar(32), password nvarchar(32))"
#define X_SQL_USER_INSERT_ADMIN     \
    "insert into user(name, password) values('admin', 'secret')"
#define X_SQL_USER_INSERT_XXX       \
    "insert into user(name, password) values('%s', '%s')"
#define X_SQL_USER_QUERY_XXX        \
    "select * from user where name = '&s';"

#define X_SQL_CUSTOMER_CREATE       \
    "create table customer( id integer primary key autoincrement, name nvarchar(32), tel nvarchar(32), qq nvarchar(32))"
#define X_SQL_CUSTOMER_INSERT_XXX   \
    "insert into customer(name, tel, qq) values('%s', '%s', '%s')"

#define X_SQL_MATERIALS_CREATE      \
    "create table materials( id integer primary key autoincrement, name nvarchar(32), val int)"

#endif