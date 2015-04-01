#ifndef _xsqlDef_h__
#define _xsqlDef_h__


#define X_SQL_USER_CREATE           \
    "create table user( id integer primary key autoincrement, name nvarchar(32), password nvarchar(32), type integer)"
#define X_SQL_USER_INSERT_ADMIN     \
    "insert into user(name, password, type) values('admin', 'secret', 0)"
#define X_SQL_USER_INSERT_XXX       \
    "insert into user(name, password, type) values('%s', '%s', '%d')"
#define X_SQL_USER_QUERY_XXX        \
    "select * from user where name='%s'"
#define X_SQL_USER_DELETE_NAME       \
    "delete from user where name='%s'"


#define X_SQL_CUSTOMER_CREATE       \
    "create table customer( id integer primary key autoincrement, name nvarchar(32), tel nvarchar(32), qq nvarchar(32))"
#define X_SQL_CUSTOMER_QUERY_XXX        \
    "select * from customer where name='%s'"
#define X_SQL_CUSTOMER_INSERT_XXX   \
    "insert into customer(name, tel, qq) values('%s', '%s', '%s')"
#define X_SQL_CUSTOMER_DELETE_NAME       \
    "delete from customer where name='%s'"
#define X_SQL_CUSTOMER_QUERY_ALL   \
    "select * from customer"
#define X_SQL_CUSTOMER_QUERY_NAME       \
    "select * from customer where name='%s'"

#define X_SQL_CUSTOMERGROUP_CREATE  \
    "create table customergroup( id integer primary key autoincrement, name nvarchar(32))"
#define X_SQL_CUSTOMERGROUP_INSERT_XXX   \
    "insert into customergroup(name) values('%s')"


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
#define X_SQL_MATERIALS_UPDATE_WHERE_ID   \
    "update materials set name = '%s', color = %d, weight = %d, where id = %d"
#define X_SQL_MATERIALS_UPDATE_WEIGHT_WHERE_ID   \
    "update materials set weight = %d, where id = %d"
#define X_SQL_MATERIALS_DELETE_WHERE_ID   \
    "delete from materials where id = %d"
#define X_SQL_MATERIALS_QUERY_ALL   \
    "select * from materials"

#define X_SQL_USEOFMATERIALS_CREATE      \
    "create table useofmaterial( id integer primary key autoincrement, material integer, weight double)"


#define X_SQL_ORDER_CREATE  \
    "create table orders( id integer primary key autoincrement, place nvarchar(32), wall nvarchar(32))"

// 工艺
#define X_SQL_ORDER_INSERT_CRAFTS  \
    "alter table orders add crafts nvarchar(32)"
// 型号
#define X_SQL_ORDER_INSERT_MODEL  \
    "alter table orders add model nvarchar(32)"
// 底色
#define X_SQL_ORDER_INSERT_BACKGROUND  \
    "alter table orders add background nvarchar(32)"
// 面色
#define X_SQL_ORDER_INSERT_FACE  \
    "alter table orders add face nvarchar(32)"
// 印花底
#define X_SQL_ORDER_INSERT_BOTTOM  \
    "alter table orders add bottom nvarchar(32)"
// 面积
#define X_SQL_ORDER_INSERT_AREA  \
    "alter table orders add area nvarchar(32)"

#define X_SQL_DESIGNER_CREATE  \
    "create table designer( id integer primary key autoincrement, name nvarchar(32), tel nvarchar(32), qq nvarchar(32), rebate integer)"


#define X_SQL_PLACE_CREATE   \
    "create table place( id integer primary key autoincrement, name nvarchar(32))"
#define X_SQL_WALL_CREATE   \
    "create table wall( id integer primary key autoincrement, name nvarchar(32))"
#define X_SQL_PLACE_INSERT_XXX  \
    "insert into place(name) values('%s')"
#define X_SQL_WALL_INSERT_XXX  \
    "insert into wall(name) values('%s')"

#endif