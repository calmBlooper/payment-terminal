#include <string>

#ifndef ACCOUNT_TABLE
namespace AccountTable {
	/*
	    const __int64 id;
        const std::string currency;
        double balance;
	*/
	const std::string COLUMN_1_ID = "account_id";
	const std::string COLUMN_2_CURRENCY = "account_currency";
	const std::string COLUMN_3_BALANCE = "account_balance";
}
#define ACCOUNT_TABLE
#endif

#ifndef PRIVATE_ACCOUNT_TABLE
namespace PrivateAccountTable {

	using namespace AccountTable;

	/*
		const std::string name;
	    const std::string surename;
	*/
	const std::string TABLE_NAME = "private_accounts";
	const std::string COLUMN_4_NAME = "account_name";
	const std::string COLUMN_5_SURENAME = "account_surename";

	const std::string CREATE_TABLE = "create table if not exists " + TABLE_NAME +"( " +
		              COLUMN_1_ID       + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
		              COLUMN_2_CURRENCY + " TEXT NOT NULL, " +
		              COLUMN_3_BALANCE  + " REAL NOT NULL, " +
		              COLUMN_4_NAME     + " TEXT NOT NULL , " +
		              COLUMN_5_SURENAME + " TEXT NOT NULL ," + 
		              "UNIQUE ( " + COLUMN_4_NAME + ", " + COLUMN_5_SURENAME + " )" +
		              ");";

	const std::string INSERT = "INSERT INTO " + TABLE_NAME + "(" + COLUMN_2_CURRENCY + ", " + COLUMN_3_BALANCE + ", " + COLUMN_4_NAME + ", " + COLUMN_5_SURENAME + ") VALUES (?,?,?,?)";
	const std::string SELECT = "SELECT * FROM " + TABLE_NAME;
	const std::string DELETE = "DELETE FROM " + TABLE_NAME + " WHERE " + COLUMN_1_ID + "=?";

	const std::string GET = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_4_NAME + "=? AND " + COLUMN_5_SURENAME + "=?";
	//const std::string GET_BY_ID = "SELECT * FROM " + TABLE_NAME + "  WHERE " + COLUMN_1_ID + "=?";

	//const std::string UPDATE = "UPDATE " + TABLE_NAME + " SET " + COLUMN_2_LOGIN + "=? AND " + COLUMN_3_PASSWORD + "=? WHERE" + COLUMN_2_LOGIN + "=? AND " + COLUMN_3_PASSWORD + "=?";
	const std::string UPDATE_BY_ID = "UPDATE " + TABLE_NAME + " SET " + COLUMN_3_BALANCE + "=? WHERE " + COLUMN_1_ID + "=?";
	}
#define PRIVATE_ACCOUNT_TABLE
#endif

#ifndef PUBLIC_ACCOUNT_TABLE
namespace PublicAccountTable {

	using namespace AccountTable;

	/*
		const std::string name;
	    const std::string address;
	*/
	const std::string TABLE_NAME = "public_accounts";
	const std::string COLUMN_4_NAME = "account_name";
	const std::string COLUMN_5_ADDRESS = "account_address";

	const std::string CREATE_TABLE = "create table if not exists " + TABLE_NAME + "( " +
		COLUMN_1_ID       + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
		COLUMN_2_CURRENCY + " TEXT NOT NULL, " +
		COLUMN_3_BALANCE  + " REAL NOT NULL, " +
		COLUMN_4_NAME     + " TEXT NOT NULL UNIQUE, " +
		COLUMN_5_ADDRESS  + " TEXT NOT NULL UNIQUE" +
		");";

	const std::string INSERT = "INSERT INTO " + TABLE_NAME + "(" + COLUMN_2_CURRENCY + ", " + COLUMN_3_BALANCE + ", " + COLUMN_4_NAME + ", " + COLUMN_5_ADDRESS + ") VALUES (?,?,?,?)";
	const std::string SELECT = "SELECT * FROM " + TABLE_NAME;
	const std::string DELETE = "DELETE FROM " + TABLE_NAME + " WHERE " + COLUMN_1_ID + "=?";

	const std::string GET = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_4_NAME + "=?";

	const std::string UPDATE_BY_ID = "UPDATE " + TABLE_NAME + " SET " + COLUMN_2_CURRENCY + "=?, " + COLUMN_3_BALANCE + "=? WHERE " + COLUMN_1_ID + "=?";
}
#define PUBLIC_ACCOUNT_TABLE
#endif

#ifndef MOBILE_ACCOUNT_TABLE
namespace MobileAccountTable {

	using namespace AccountTable;

	/*
		const std::string telephoneNumber;
	*/
	const std::string TABLE_NAME = "mobile_accounts";
	const std::string COLUMN_4_TELEPHONE_NUMBER = "account_telephone_number";

	const std::string CREATE_TABLE = "create table if not exists " + TABLE_NAME + "( " +
		COLUMN_1_ID               + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
		COLUMN_2_CURRENCY         + " TEXT NOT NULL, " +
		COLUMN_3_BALANCE          + " REAL NOT NULL, " +
		COLUMN_4_TELEPHONE_NUMBER + " TEXT NOT NULL UNIQUE " +
		");";

	const std::string INSERT = "INSERT INTO " + TABLE_NAME + "(" + COLUMN_2_CURRENCY + ", " + COLUMN_3_BALANCE + ", " + COLUMN_4_TELEPHONE_NUMBER + ") VALUES (?,?,?)";
	const std::string SELECT = "SELECT * FROM " + TABLE_NAME;
	const std::string DELETE = "DELETE FROM " + TABLE_NAME + " WHERE " + COLUMN_1_ID + "=?";

	const std::string GET = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_4_TELEPHONE_NUMBER + "=?";

	const std::string UPDATE_BY_ID = "UPDATE " + TABLE_NAME + " SET " + COLUMN_2_CURRENCY + "=?, " + COLUMN_3_BALANCE + "=? WHERE " + COLUMN_1_ID + "=?";
}
#define MOBILE_ACCOUNT_TABLE
#endif

#ifndef EWALLET_ACCOUNT_TABLE
namespace EWalletAccountTable {

	using namespace AccountTable;

	/*
		const std::string login;
	    const std::string email;
	*/
	const std::string TABLE_NAME = "ewallet_accounts";
	const std::string COLUMN_4_LOGIN = "account_login";
	const std::string COLUMN_5_EMAIL = "account_email";

	const std::string CREATE_TABLE = "create table if not exists " + TABLE_NAME + "( " +
		COLUMN_1_ID       + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
		COLUMN_2_CURRENCY + " TEXT NOT NULL, " +
		COLUMN_3_BALANCE  + " REAL NOT NULL, " +
		COLUMN_4_LOGIN    + " TEXT NOT NULL UNIQUE, " +
		COLUMN_5_EMAIL    + " TEXT NOT NULL UNIQUE " +
		");";

	const std::string INSERT = "INSERT INTO " + TABLE_NAME + "(" + COLUMN_2_CURRENCY + ", " + COLUMN_3_BALANCE + ", " + COLUMN_4_LOGIN + ", " + COLUMN_5_EMAIL + ") VALUES (?,?,?,?)";
	const std::string SELECT = "SELECT * FROM " + TABLE_NAME;
	const std::string DELETE = "DELETE FROM " + TABLE_NAME + " WHERE " + COLUMN_1_ID + "=?";
	
	const std::string GET_BY_LOGIN_EMAIL = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_4_LOGIN + "=? AND " + COLUMN_5_EMAIL + "=?";
	const std::string GET_BY_LOGIN = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_4_LOGIN + "=?";
	const std::string GET_BY_EMAIL = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_5_EMAIL + "=?";

	const std::string UPDATE_BY_ID = "UPDATE " + TABLE_NAME + " SET " + COLUMN_2_CURRENCY + "=?, " + COLUMN_3_BALANCE + "=? WHERE " + COLUMN_1_ID + "=?";
}
#define EWALLET_ACCOUNT_TABLE
#endif