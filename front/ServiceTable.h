#include <string>

#ifndef SERVICE_TABLE
namespace ServiceTable {

    /*
        const unsigned long id;
        const unsigned int serviceType;
        const std::string name;
        const double commission;
    */
    const std::string TABLE_NAME = "services";
    const std::string COLUMN_1_ID = "service_id";
    const std::string COLUMN_2_NAME = "service_name";
    const std::string COLUMN_3_COMMISSION = "service_commission";
    const std::string COLUMN_4_TYPE = "service_type";

    const std::string CREATE_TABLE = "create table if not exists " + TABLE_NAME + "( " +
        COLUMN_1_ID         + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
        COLUMN_2_NAME       + " TEXT NOT NULL UNIQUE, " +
        COLUMN_3_COMMISSION + " REAL NOT NULL, " +
        COLUMN_4_TYPE       + " INTEGER NOT NULL " +
        ");";

    const std::string INSERT = "INSERT INTO " + TABLE_NAME + "(" + COLUMN_2_NAME + ", " + COLUMN_3_COMMISSION + ", " + COLUMN_4_TYPE + ") VALUES (?,?,?)";
    const std::string SELECT = "SELECT * FROM " + TABLE_NAME;
    const std::string SELECT_BY_TYPE = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_4_TYPE + "=?";
    const std::string DELETE = "DELETE FROM " + TABLE_NAME + " WHERE " + COLUMN_1_ID + "=?";

    const std::string GET = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_2_NAME + "=?";

    const std::string UPDATE_BY_ID = "UPDATE " + TABLE_NAME + " SET " + COLUMN_3_COMMISSION + "=? WHERE " + COLUMN_1_ID + "=?";
}
#define SERVICE_TABLE
#endif
