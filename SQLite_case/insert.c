#include<stdio.h>
#include<sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i = 0;
	for(i = 0; i < argc; i++)
	{
		printf("%s = %s\n",azColName[i], argv[i]?argv[i]:"NULL");
	}

	printf("\n");
	return 0;
}

int main()
{
	sqlite3* db;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	rc = sqlite3_open("test.db", &db);
	if(rc)
	{
		fprintf(stderr, "Can't open database:%s\n", sqlite3_errmsg(db));
//		exit(0);
		return -1;
	}
	else
	{
		fprintf(stderr,"open database succeddfully\n");
	}

//	sql = "create table company(ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL, AGE TEXT NOT NULL, ADDRESS CHAR(50))";

	sql = "insert into company(ID, NAME, AGE, ADDRESS) values(1, 'Paul', 25, 'USA');\
		insert into company(ID, NAME, AGE, ADDRESS) values(2, 'James', 28, 'JAP');\
		insert into company(ID, NAME, AGE, ADDRESS) values(3, 'Yao', 30, 'CHA');\
		insert into company(ID, NAME, AGE, ADDRESS) values(4, 'kobe', 38, 'USA');";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(SQLITE_OK != rc)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	}
	else
	{
		fprintf(stdout, "insert table successfully\n");
	}

	sqlite3_close(db);
	return 0;
}
