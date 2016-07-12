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

	sql = "delete from company where ID = 2;\
		select * from company;";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(SQLITE_OK != rc)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	}
	else
	{
		fprintf(stdout, "delete table successfully\n");
	}

	sqlite3_close(db);
	return 0;
}
