#include "PropertyManager.hpp"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   for(int i = 0; i < argc; i++)
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

   cout << "\n";
   return 0;
}

PropertyManager::PropertyManager()
{
//   status=Connect();
}

int PropertyManager::Init()
{
    currentTrack = "1";
    status = Connect();
    return 0;//QUI
}

int PropertyManager::Connect()
{
    status = sqlite3_open_v2("./mydb.db", &db, SQLITE_OPEN_READWRITE, NULL);
    if(status!= SQLITE_OK)
        cout << "Database failed to open" << endl;
    else
        cout << "Database opened" << endl;

    return status;
}

int PropertyManager::getStatus()
{
    return status;
}

void PropertyManager::setTrack(std::string currentTrack)
{
    this->currentTrack = currentTrack;
}

std::string PropertyManager::getTrack()
{
    return currentTrack;
}

void PropertyManager::Query()
{
    int rc;
	char *sql;
	char *zErrMsg = 0;

    // Create SQL statement
    sql = "INSERT INTO user (id,name,lastname) "
         "VALUES (1, 'Mathy', 'Pat'); " 
         "INSERT INTO user (id,name,lastname) "  
         "VALUES (2, 'Mathy1', 'Pat1'); ";
    
    if(status != SQLITE_OK)
        cout << "Database failed to insert data" << endl;
    else
    {
        // Execute SQL statement
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK)
        {
            cout<<"SQL error:"<<zErrMsg<<"\n";
            sqlite3_free(zErrMsg);
        }
        else
            cout<<"Records created successfully\n";
    }
}

std::string PropertyManager::getTrackProperty(std::string propName)
{
    int rc;
    std::string  sql,prop="NONE";
    sqlite3_stmt *stmt;
    // Create SQL statement
    sql = "select value from chg_prop as p,challenge as c where p.id_chall=c.id"
          " and c.name = '"+ currentTrack + "' and p.name = '" + propName + "';";

    if(status!= SQLITE_OK)
        cout << "Database failed to read data" << endl;
    else
    {
        // Execute SQL statement
        rc=sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK)
            cout<<"SQL error, Failed to fetch data: "<< sqlite3_errmsg(db);
        else
            cout<<"Records read successfully\n";
        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE)
            prop=(char *)sqlite3_column_text(stmt, 0);

        sqlite3_finalize(stmt);
    }
    return prop;
}

std::string PropertyManager::getCurrentTrack(std::string trackID)
{
    int rc;
    std::string  sql,value="NONE";
    sqlite3_stmt *stmt;
    // Create SQL statement
    sql = "select name from challenge as c where c.id = '" + trackID + "';";

    return sendQuery(sql);
}

std::string PropertyManager::sendQuery(std::string sql)
{
    int rc;

    std::string  prop="NONE";
    sqlite3_stmt *stmt;

    if(status!= SQLITE_OK)
        cout << "Database failed to read data" << endl;
    else
    {
        // Execute SQL statement
        rc=sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK)
            cout<<"SQL error, Failed to fetch data: "<< sqlite3_errmsg(db);
        else  {
            cout<<"Records read successfully\n";
        }
        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE)
            prop=(char *)sqlite3_column_text(stmt, 0);

        sqlite3_finalize(stmt);
    }
    return prop;
}

void PropertyManager::Close()
{
    sqlite3_close(db);
}