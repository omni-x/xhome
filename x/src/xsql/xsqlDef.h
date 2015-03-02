#ifndef _xsqlDef_h__
#define _xsqlDef_h__

#define X_SQL_CREATE_USER   "create table user( id integer primary key autoincrement, name nvarchar(32) )"
#define X_SQL_INSERT_ADMIN  "insert into user(name) values('admin')"

#endif