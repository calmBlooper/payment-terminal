#include <string>

#include "AccountTable.h"

#ifndef PAYCARD_TABLE
namespace PaycardTable {

	/*
		const unsigned long id;
	    const unsigned long accountId;
	    const std::string cardNumber;
	    const unsigned short cvv;
	    const unsigned short expMonth;
	    const unsigned short expYear;
	    unsigned short pin;
	*/
	const std::string TABLE_NAME = "paycards";
	const std::string COLUMN_1_ID = "paycard_id";
	const std::string COLUMN_2_ACCOUNT_ID = PrivateAccountTable::COLUMN_1_ID;
	const std::string COLUMN_3_CARD_NUMBER = "paycard_number";
	const std::string COLUMN_4_CVV = "paycard_cvv";
	const std::string COLUMN_5_EXP_MONTH = "paycard_exp_month";
	const std::string COLUMN_6_EXP_YEAR = "paycard_exp_year";
	const std::string COLUMN_7_PIN = "paycard_pin";

	const std::string CREATE_TABLE = "create table if not exists " + TABLE_NAME + "( " +
		COLUMN_1_ID          + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
		COLUMN_2_ACCOUNT_ID  + " INTEGER NOT NULL, " +
		COLUMN_3_CARD_NUMBER + " TEXT NOT NULL UNIQUE, " +
		COLUMN_4_CVV         + " INTEGER NOT NULL, " +
		COLUMN_5_EXP_MONTH   + " INTEGER NOT NULL, " +
		COLUMN_6_EXP_YEAR    + " INTEGER NOT NULL, " +
		COLUMN_7_PIN         + " INTEGER NOT NULL, " +
		"FOREIGN KEY (" + COLUMN_2_ACCOUNT_ID + ") REFERENCES " + PrivateAccountTable::TABLE_NAME + "(" + COLUMN_2_ACCOUNT_ID + ") ON DELETE CASCADE " +
		");";

	const std::string INSERT = "INSERT INTO " + TABLE_NAME + "(" +
		COLUMN_2_ACCOUNT_ID + ", " +
		COLUMN_3_CARD_NUMBER + ", " +
		COLUMN_4_CVV + ", " +
		COLUMN_5_EXP_MONTH + ", " +
		COLUMN_6_EXP_YEAR + ", " +
		COLUMN_7_PIN + ") VALUES (?,?,?,?,?,?)";
	const std::string SELECT = "SELECT * FROM " + TABLE_NAME;
	const std::string DELETE = "DELETE FROM " + TABLE_NAME + " WHERE " + COLUMN_1_ID + "=?";

	const std::string GET = "SELECT * FROM " + TABLE_NAME + " WHERE " + COLUMN_3_CARD_NUMBER + "=?";

	const std::string UPDATE_PIN_BY_ID = "UPDATE " + TABLE_NAME + " SET " + COLUMN_7_PIN + "=? WHERE " + COLUMN_1_ID + "=?";
}
#define PAYCARD_TABLE
#endif