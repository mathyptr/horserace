#include "PropertyManager.hpp"

PropertyManager::PropertyManager(bool autoConnect)
{
    if(autoConnect)
        connect();
}

int PropertyManager::connect()
{
    status = sqlite3_open_v2("./mydb.db", &db, SQLITE_OPEN_READWRITE, NULL);
    if(status != SQLITE_OK)
        cout << "Database failed to open" << endl;
    else
        cout << "Database opened" << endl;

    return status;
}

void PropertyManager::close()
{
    sqlite3_close(db);
}

int PropertyManager::getStatus()
{
    return status;
}

std::string PropertyManager::getTrackProperty(int trackID, std::string propName)
{
    std::string sql = "select " + propName + " from track where track.id = " + std::to_string(trackID) + ";";
    return sendQuery(sql);
}

std::string PropertyManager::getTrackProperty(std::string trackName, std::string propName)
{
    std::string sql = "select " + propName + " from track where track.name = '" + trackName + "';";
    return sendQuery(sql);
}

int PropertyManager::getTrackCount()
{
    std::string sql = "select count(*) from track";
    return std::stoi(sendQuery(sql));
}

std::string PropertyManager::getHorseProperty(int horseID, std::string propName)
{
    std::string sql = "select " + propName + " from horse where horse.id = " + std::to_string(horseID) + ";";
    return sendQuery(sql);
}

std::string PropertyManager::sendQuery(std::string sql)
{
    int rc;
    std::string prop="NONE";
    sqlite3_stmt *stmt;
    if(status != SQLITE_OK)
        cout << "Database failed to read data" << endl;
    else
    {
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK)
            cout<<"SQL error, Failed to fetch data: "<< sqlite3_errmsg(db);
        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE)
            prop=std::string((char *)sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);
    }
    return prop;
}

std::string PropertyManager::getCurrentWeatherTexture(std::string weatherId)
{
    std::string  sql;
    sql="select main_texture from weather as w where w.id= '"+weatherId+"';";
    return sendQuery(sql);
}

std::string PropertyManager::getCurrentWeatherExplosion(std::string weatherId)
{
std::string  sql;
sql="select explosion_texture from weather as w where w.id= '"+weatherId+"';";
return sendQuery(sql);
}

std::string PropertyManager::getProbability(std::string trackID, std::string weatherId)
{
    std::string  sql;
    sql="select probability from weather_prob where track_id= '" + trackID + "' and weather_id= '"+weatherId+"';";
    return sendQuery(sql);
}