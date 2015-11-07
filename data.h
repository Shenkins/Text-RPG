//header file for game data
#pragma once //Ensures only read and processed once

//library declarations
#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<map>
#include<algorithm>
#include<iterator>
#include<locale>
#include<sstream>

using namespace std ;

//declares custom namespace
namespace MUD
{
	class Player ;
	class Item ;
	class Room ;
	class HolyRoom ;
	class EvilRoom ;
	class WarpRoom ;
	class Dungeon ;
	class Monster ;
	class Validation ;
	class CommandHelper ;

	//Item Class
	class Item
	{
	public:
		enum TYPE { WEAPON, ARMOR, HEALTH } ;
		
		Item( string name, Item::TYPE type, int power, int vitality, int health ) ;
		Item operator=( Item& newItem ) ;
		Item( void ) ;
		//~Item()
	
		void setPower( int value ) ;
		int getPower( void ) ;

		void setVitality( int value ) ;
		int getVitality( void ) ;

		void setHealth( int value ) ;
		int getHealth( void ) ;

		void setName( string name ) ;
		string getName( void ) ;

		void setType( TYPE newType ) ;
		TYPE getType( void ) ;

		string mName ;
		int mPower ;
		int mVitality ;
		int mHealth ;
		TYPE mType ;
		bool mAvailiable ;
	} ;

	//Monster Class
	class Monster
	{
	public:
		Monster( string name, int maxHp, int strength, int defense ) ;

		void setHp( int newHp ) ;
		int getHp( void ) const ;

		void setStrength( int newStrength ) ;
		int getStrength( void ) const ;

		void setDefense( int newDefense ) ;
		int getDefense( void ) const ;

		void setName( string newName ) ;
		string getName( void ) const ;

		void setMaxHp( int newMaxHp ) ;

		int mMaxHp ;
		int mHp ;
		int mStrength ;
		int mDefense ;
		string mName ;
		bool inCombat ;
	} ;

	// Room Class
	class Room 
	{
	public:
		Room( string name, string description, Item* item = NULL ) ;

		typedef bool success ;

		void addMonster( Monster* newMonster ) ;
		Monster& getMonsterRef( string monsterName ) ;
		success killMonster( string monsterName ) ;
		void itemTaken( void ) ;
		void searchResponse( void ) ;
		success link( char direction, Room& room ) ;
		Room& north( void ) ;
		Room& south( void ) ;
		Room& east( void ) ;
		Room& west( void ) ;
		
		void setName( string newName ) ;
		string getRoomName( void ) const ;
		
		void setDescription( string newDescription ) ;
		string getDescription( void ) const ;
		
		void setItem( Item* newItem ) ;

		virtual bool getHoly() ;
		virtual bool getEvil() ;
		virtual bool getWarp() ;
		
		Item* mItem ;
		Room* mNorth ;
		Room* mSouth ;
		Room* mEast ;
		Room* mWest ;
		list< Monster* > mMonsters ;
		string mName ;
		string mDescription ; 
	} ;

	//HolyRoom SubClass
	class HolyRoom : public Room
	{
    public:
        HolyRoom( string name, string description, Item* item ) ;
        virtual bool getHoly() ;
	};

	//EvilRoom SubClass
	class EvilRoom : public Room
	{
    public:
        EvilRoom( string name, string description, Item* item ) ;
        virtual bool getEvil() ;
	};

	//WarpRoom SubClass
	class WarpRoom : public Room
	{
    public:
        WarpRoom( string name, string description, Item* item ) ;
        virtual bool getWarp() ;
	};

	//Player Class
	class Player
	{
	public:
		Player( string name, Room* start = NULL ) ;

		typedef bool dead ;

		void setHp( int newHp ) ;
		int getHp( void ) const ;

		void setStrength( int newStrength ) ;
		int getStrength( void ) const ;

		void setDefense( int newDefense ) ;
		int getDefense( void ) const ;

		string getLocation( void ) ;

		void setName( string newName ) ;
		string getName( void ) const ;

		void equip( string itemName ) ;
		string attack( string monsterName ) ;
		void move( char direction ) ;
		dead death( void ) ;

		int mMaxHp ;
		int mHp ;
		int mStrength ;
		int mDefense ;
		Room* mLocation ;
		string mName ;
		Item* mWeapon ;
		Item* mArmor ;
		dead mLife ;
	} ;

	//Dungeon Class
	class Dungeon
	{
	public:
		Dungeon( int maxRooms ) ;

		bool isComplete( void ) ;
		void addPlayer( Player* newPlayer ) ;
		void addRoom( Room* newRoom ) ;
		void removePlayer( string playerName ) ;
		void generatePlayerStats( Player* newPlayer ) ;
		void combatLoop( Player& hero, Monster& villain ) ;
		string* playerStatus( Player& player ) ;

		int mMaxRooms ;
		vector< Room* > mRooms ;
		vector< Player* > mPlayers ;
	} ;

	//Validation Class
	class Validation
	{
	public:
		typedef bool valid ;
		valid validateMessage( string message ) ;
	} ;

	//CommandHelper Class
	class CommandHelper
	{
	public:
		char extractCommand( string fromValidation ) ;
		string extractValue( string fromValidation ) ;
	} ;
}