#include "propertyManager.hpp"



static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   cout<<"\n";
   return 0;
}


propertyManager::propertyManager()
{
   mstatus=Connect();
}

int propertyManager::Connect()
{
 mstatus = sqlite3_open_v2("./mydb.db", &mdb,SQLITE_OPEN_READWRITE,NULL);
   if(mstatus!= SQLITE_OK)
        //database failed to open
//		root << log4cpp::Priority::ERROR << "Database failed to open" ;
        cout << "Database failed to open" << endl;
    else
            cout << "Database opened" << endl;
   return mstatus;
}

int propertyManager::getStatus()
{
    mstatus=Connect();
}


void propertyManager::setChall(std::string actChall)
{
 mactChall = actChall;
}

std::string  propertyManager::getChall()
{
   return mactChall;
}


void propertyManager::Query()
{
    int rc;
	char *sql;
	char *zErrMsg = 0;

// Create SQL statement 
   sql = "INSERT INTO user (id,name,lastname) "  
         "VALUES (1, 'Mathy', 'Pat'); " 
         "INSERT INTO user (id,name,lastname) "  
         "VALUES (2, 'Mathy1', 'Pat1'); ";
    
    if(mstatus!= SQLITE_OK)
        //database failed to open
//		root << log4cpp::Priority::ERROR << "Database failed to open" ;
        cout << "Database failed to insert data" << endl;
    else
    {
        //your database code here
//    sqlite3_exec(mdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);

// Execute SQL statement
       rc = sqlite3_exec(mdb, sql, callback, 0, &zErrMsg);
   
       if( rc != SQLITE_OK ){
          cout<<"SQL error:"<<zErrMsg<<"\n";
          sqlite3_free(zErrMsg);
       } else {
          cout<<"Records created successfully\n";
        }
//   sqlite3_exec(mdb, "END TRANSACTION;", NULL, NULL, NULL);

    }
}


std::string   propertyManager::getChallProperty(std::string propName)
{
   int rc;

   std::string  sql,prop="NONE";
   sqlite3_stmt *stmt;
// Create SQL statement 
   sql = "select value from chg_prop as p,challenge as c where p.id_chall=c.id"
         " and c.name = '"+ mactChall + "' and p.name = '" + propName + "';";
           
    if(mstatus!= SQLITE_OK)
        //database failed to open
//		root << log4cpp::Priority::ERROR << "Database failed to open" ;
        cout << "Database failed to read data" << endl;
    else
    {
        //your database code here
//    sqlite3_exec(mdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);

   // Execute SQL statement 
        rc=sqlite3_prepare_v2(mdb, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK)
             cout<<"SQL error, Failed to fetch data: "<< sqlite3_errmsg(mdb);
        else  {
             cout<<"Records read successfully\n";
        }
//   sqlite3_exec(mdb, "END TRANSACTION;", NULL, NULL, NULL);
        rc = sqlite3_step(stmt);
   
        if (rc != SQLITE_DONE) {
/*      int i;
		int num_cols = sqlite3_column_count(stmt);
      for (i = 0; i < num_cols; i++)
		{
			switch (sqlite3_column_type(stmt, i))
			{
			case (SQLITE3_TEXT):
            prop=(char *)sqlite3_column_text(stmt, i);
				printf("column %s ", prop.c_str());
				break;
			case (SQLITE_INTEGER):
				printf("column %d, ", sqlite3_column_int(stmt, i));
				break;
			case (SQLITE_FLOAT):
				printf("column %g, ", sqlite3_column_double(stmt, i));
				break;
			default:
				break;
			}
         printf("\n");
         
		}
      */
          prop=(char *)sqlite3_column_text(stmt, 0);

//       cout<< sqlite3_column_text(stmt, 0);
     }
    
     sqlite3_finalize(stmt);
    }

    return prop;
}


std::string   propertyManager::getActualChall(std::string challId)
{
    int rc;

    std::string  sql,value="NONE";
    sqlite3_stmt *stmt;
// Create SQL statement
    sql = "select name from challenge as c where c.id = '"+challId + "';";

    return sendQuery(sql);
}


std::string   propertyManager::sendQuery(std::string sql)
{
    int rc;

    std::string  prop="NONE";
    sqlite3_stmt *stmt;

    if(mstatus!= SQLITE_OK)
        //database failed to open
//		root << log4cpp::Priority::ERROR << "Database failed to open" ;
        cout << "Database failed to read data" << endl;
    else
    {
        //your database code here
//    sqlite3_exec(mdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);

        // Execute SQL statement
        rc=sqlite3_prepare_v2(mdb, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK)
            cout<<"SQL error, Failed to fetch data: "<< sqlite3_errmsg(mdb);
        else  {
            cout<<"Records read successfully\n";
        }
//   sqlite3_exec(mdb, "END TRANSACTION;", NULL, NULL, NULL);
        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE) {
            prop=(char *)sqlite3_column_text(stmt, 0);

//       cout<< sqlite3_column_text(stmt, 0);
        }

        sqlite3_finalize(stmt);
    }

    return prop;
}


void propertyManager::Close()
{
  sqlite3_close(mdb);
}