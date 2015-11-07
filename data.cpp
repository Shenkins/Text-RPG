//source file for game data
#include "data.h"

using namespace MUD ;

//Item Class
Item::Item( string name, Item::TYPE type, int power, int vitality, int health ) 
  : mName(name), mType(type), mPower(power), mVitality(vitality), 
	mHealth(health)
{
	mAvailiable = true ;
}
Item Item::operator=( Item& newItem )
{
	setName( newItem.getName() ) ;
	setType( newItem.getType() ) ;
	setPower( newItem.getPower() ) ;
	setVitality( newItem.getVitality() ) ;
	setHealth( newItem.getHealth() ) ;
	mAvailiable = newItem.mAvailiable ;

	return *this ;
}

Item::Item( void )
{
	setName( "" ) ;
	setType( Item::WEAPON ) ;
	setPower( 0 ) ;
	setVitality( 0 ) ;
	setHealth( 0 ) ;
	mAvailiable = true ;
}

//sets item power
void Item::setPower( int value )
{
	mPower = value ;
}

//gets item power
int Item::getPower( void )
{
	return mPower ;
}

//sets item vit
void Item::setVitality( int value )
{
	mVitality = value ;
}

//gets item vit
int Item::getVitality( void )
{
	return mVitality ;
}

//sets health
void Item::setHealth( int value )
{
	mHealth = value ;
}

//gets health
int Item::getHealth( void )
{
	return mHealth ;
}

//sets name
void Item::setName( string name )
{
	mName = name ;
}

//returns item name
string Item::getName( void )
{
	return mName ;
}

//sets item type - weapon or armor
void Item::setType( Item::TYPE newType )
{
	mType = newType ;
}

//gets item type
Item::TYPE Item::getType( void )
{
	return mType ;
}











//Monster Class
Monster::Monster( string name, int maxHp, int strength, int defense )
  : mName(name), mMaxHp(maxHp), mStrength(strength), mDefense(defense)
{
	setHp(maxHp);
	inCombat = false ;
}

//sets monster health
void Monster::setHp( int newHp )
{
	mHp = newHp ;
}

//gets monster health
int Monster::getHp( void ) const
{
	return mHp ;
}

//sets monster strength
void Monster::setStrength( int newStrength )
{
	mStrength = newStrength ;
}

//gets monster strength
int Monster::getStrength( void ) const
{
	return mStrength ;
}

//sets monster defense
void Monster::setDefense( int newDefense )
{
	mDefense = newDefense ;
}

//gets monster defense
int Monster::getDefense( void ) const
{
	return mDefense ;
}

//sets monster name
void Monster::setName( string newName ) 
{
	mName = newName ;
}

//gets monster name
string Monster::getName( void ) const
{
	return mName ;
}

//set monster maxhealth
void Monster::setMaxHp( const int newMaxHp ) 
{
	mMaxHp = newMaxHp ;
}










//Room Class
Room::Room( string name, string description, Item* item )
  : mName(name), mDescription(description), mItem(item)
{
	mNorth = NULL ;
	mSouth = NULL ;
	mEast = NULL ;
	mWest = NULL ;
}

//link room function
bool Room::link( char direction, MUD::Room& room )
{
	bool flag = false ;

	switch( direction )
	{
		case 'n':
		case 'N':
			mNorth = &room ;
			flag = true ;
		break ;

		case 's':
		case 'S':
			mSouth = &room ;
			flag = true ;
		break ;

		case 'e':
		case 'E':
			mEast = &room ;
			flag = true ;
		break ;

		case 'w':
		case 'W':
			mWest = &room ;
			flag = true ;
		break ;
	}

	return flag ;
}

//North
Room& Room::north( void ) 
{
	return *mNorth ;
}

//South
Room& Room::south( void )
{
	return *mSouth ;
}

//East
Room& Room::east( void )
{
	return *mEast ;
}

//West
Room& Room::west( void )
{
	return *mWest ;
}

//Set room name
void Room::setName( string newName )
{
	mName = newName ;
}

//get room name
string Room::getRoomName( void ) const
{
	return mName ;
}

//adds a monster to the room monster vector - vector to allow for multiple monsters per room
void Room::addMonster( Monster* newMonster )
{
	mMonsters.push_back( newMonster ) ;
}

//gets monster
Monster& Room::getMonsterRef( string monsterName ) 
{
	list< Monster* >::iterator iter ;
	Monster* monsterRef = NULL ;
	
	for( iter = mMonsters.begin() ; iter != mMonsters.end() ; ++iter )
	{
		if( (*iter)->getName() == monsterName )
		{
			monsterRef = *iter ;
			break ;
		}
	}

	return *monsterRef ;
}

//destroy monster in room
Room::success Room::killMonster( string monsterName )
{
	list< Monster* >::iterator iter ;
	bool flag = false ;

	for( iter = mMonsters.begin() ; iter != mMonsters.end() ; ++iter )
	{
		if( (*iter)->getName() == monsterName )
		{
			mMonsters.erase( iter ) ;
			flag = true ;

			break ;
		}
	}

	return flag ;
}

//if holy room
bool Room::getHoly()
{
	return false ;
}

//if evil room
bool Room::getEvil()
{
	return false ;
}

//if warp room
bool Room::getWarp()
{
	return false ;
}






//Holy Room SubClass
HolyRoom::HolyRoom( string name, string description, Item* item ) : Room( name, description, item )
{
}
//holy room toggle on
bool HolyRoom::getHoly()
{
	return true ;
}







//Evil Room SubClass
EvilRoom::EvilRoom( string name, string description, Item* item ) : Room( name, description, item )
{
}
//evil room toggle on
bool EvilRoom::getEvil()
{
	return true ;
}








//Warp Room SubClass
WarpRoom::WarpRoom( string name, string description, Item* item ) : Room( name, description, item )
{
}
//warp room toggle on
bool WarpRoom::getWarp()
{
	return true ;
}







//if item in room has been taken
void Room::itemTaken( void )
{
	mItem->mAvailiable = false ;
}

//place item
void Room::setItem( Item* newItem )
{
	mItem = newItem ;
}

//room description
void Room::setDescription( string newDescription )
{
	mDescription = newDescription ;
}

//get room description
string Room::getDescription( void ) const
{
	return mDescription ;
}

//search room for items and monsters
void Room::searchResponse( void )
{
	string response ;

	if( mItem != NULL && true == mItem->mAvailiable )
	{
		response = "\n\nThere is a " + mItem->getName() + " in this room." ;
	}

	if( !mMonsters.empty() )
	{
		response = response + "\n\nYou sense danger nearby..." ;

		list< Monster* >::iterator iter ;
		
		for( iter = mMonsters.begin() ; iter != mMonsters.end() ; ++iter )
		{
			if( false == (*iter)->inCombat )
			{
				response = response + "\nA " + (*iter)->getName() + " stands poised to fight." ;
			}
		}
	}

	cout << response ;
	return ;
}












//Player Class
Player::Player( string name, Room* start ) 
	: mName(name), mLocation(start), mWeapon(NULL), mArmor(NULL),
	mHp(10), mMaxHp(10), mStrength(1), mDefense(0)
{
}

//set health
void Player::setHp( int newHp )
{
	mHp = newHp ;
}

//get health
int Player::getHp( void ) const
{
	return mHp ;
}

//set str
void Player::setStrength( int newStrength )
{
	mStrength = newStrength ;
}

//get str
int Player::getStrength( void ) const
{
	return mStrength ;
}

//set def
void Player::setDefense( int newDefense )
{
	mDefense = newDefense ;
}

//get def
int Player::getDefense( void ) const
{
	return mDefense ;
}

//get player location
string Player::getLocation( void )
{
	return mLocation->mName ;
}

//set player name
void Player::setName( string newName )
{
	mName = newName ;
}

//get player name
string Player::getName( void ) const 
{
	return mName ;
}

//attack monster function
string Player::attack( string monsterName )
{
	list< Monster* >::iterator iter ;
	int damage = 0 ;
	string response( "\nThe " + monsterName + " is not here" ) ; 
	stringstream ss ;
	string strDamage ;

	//if no monster to attack
	if( mLocation->mMonsters.empty() )
	{
		return "\nThere are no monsters in this room to fight" ;
	}

	//attack!
	for( iter = mLocation->mMonsters.begin() ; iter != mLocation->mMonsters.end() ; ++iter )
	{
		if( (*iter)->getName() == monsterName )
		{
			damage = getStrength() - (*iter)->getDefense() ;
			ss << damage ;
			ss >> strDamage ;
			ss.clear() ;
			
			//if damage taken
			if( damage > 0 )
			{
				(*iter)->setHp( (*iter)->getHp() - damage ) ;
				response = (*iter)->getName() + " was dealt " + strDamage + " damage" ;
			}
			else
			{
				response = (*iter)->getName() + " took no damage" ;
			}

			break ;
		}
	}

	return response ;
}

//equip item
void Player::equip( string itemName )
{
	if( mLocation->mItem != NULL && mLocation->mItem->getName() == itemName )
	{
		//if item is a weapon, equip it and adjust player str to reflect new item
		if( Item::WEAPON == mLocation->mItem->getType() && true == mLocation->mItem->mAvailiable )
		{
			mWeapon = mLocation->mItem ;
			mLocation->itemTaken() ;
			setStrength( mWeapon->getPower() ) ;
			cout << "\nYou equipped the " << mWeapon->getName() ;
		}

		//if item is armor, equip it and adjust player defense and max hp to reflect new item
		else if( Item::ARMOR == mLocation->mItem->getType() && true == mLocation->mItem->mAvailiable )
		{
			mArmor = mLocation->mItem ;
			mLocation->itemTaken() ;
			setDefense( mArmor->getVitality() ) ;
			mMaxHp += mArmor->getHealth() ;
			cout << "\nYou equipped the " << mArmor->getName() ;
		}
	}
	//else item error
	else
	{
		cout << "\nTo equip an item you must type its full name correctly" ;
	}

	return ;
}

//move function
void Player::move( char direction )
{
	switch( direction )
	{
		//North
		case 'n':
		case 'N':
			if( NULL == mLocation->mNorth )
			{
				cout << "\nThere is nothing in that direction." ;
				break ;
			}
			mLocation = &(mLocation->north()) ;
			cout << "\nYou have traveled North" ;
			cout << "\n\nYou have reached the " << mLocation->getRoomName() << ".\n" ;
			cout << mLocation->getDescription() ;

			if (mLocation->getHoly())
			{
				cout << "\nYou feel a soothing warmth radiating from the room." ;
				setHp( mMaxHp ) ;
				cout << "\nYour health has been regained." ;
			}
			if (mLocation->getEvil())
			{
				cout << "\nYou are suddenly overwhelmed by an evil pressure in the room." ;
				cout << "\nYou lose 3 health." ;
				int evilHpNorth = getHp() ;
				evilHpNorth = evilHpNorth - 3 ;
				setHp( evilHpNorth ) ;
			}

			mLocation->searchResponse() ;

			break ;

		//South
		case 's':
		case 'S':
			if( NULL == mLocation->mSouth )
			{
				cout << "\nThere is nothing in that direction." ;
				break ;
			}
			mLocation = &(mLocation->south()) ;
			cout << "\nYou have traveled South." ;
			cout << "\n\nYou have reached the " << mLocation->getRoomName() << ".\n" ;
			cout << mLocation->getDescription() ;

			if (mLocation->getHoly())
			{
				cout << "\nYou feel a soothing warmth radiating from the room." ;
				setHp( mMaxHp ) ;
				cout << "\nYour health has been regained." ;
			}
			if (mLocation->getEvil())
			{
				cout << "\nYou are suddenly overwhelmed by an evil pressure in the room." ;
				cout << "\nYou lose 3 health." ;
				int evilHpSouth = getHp() ;
				evilHpSouth = evilHpSouth - 3 ;
				setHp( evilHpSouth ) ;
			}

			mLocation->searchResponse() ;
			break ;

		//East
		case 'e':
		case 'E':
			if( NULL == mLocation->mEast )
			{
				cout << "\nThere is nothing in that direction." ;
				break ;
			}
			mLocation = &(mLocation->east()) ;
			cout << "\nYou have traveled East." ;
			cout << "\n\nYou have reached the " << mLocation->getRoomName() << ".\n" ;
			cout << mLocation->getDescription() ;

			if (mLocation->getHoly())
			{
				int healHP = getHp() ;

				cout << "\nYou feel a soothing warmth radiating from the room." ;
				setHp( mMaxHp ) ;
				cout << "\nYour health has been regained." ;
			}
			if (mLocation->getEvil())
			{
				cout << "\nYou are suddenly overwhelmed by an evil pressure in the room." ;
				cout << "\nYou lose 3 health." ;
				int evilHpEast = getHp() ;
				evilHpEast = evilHpEast - 3 ;
				setHp( evilHpEast ) ;
			}

			mLocation->searchResponse() ;
			break ;

		//West
		case 'w':
		case 'W':
			if( NULL == mLocation->mWest )
			{
				cout << "\nThere is nothing in that direction." ;
				break ;
			}
			mLocation = &(mLocation->west()) ;
			cout << "\nYou have traveled West." ;
			cout << "\n\nYou have reached the " << mLocation->getRoomName() + ".\n" ;
			cout << mLocation->getDescription() ;

			if (mLocation->getHoly())
			{
				cout << "\nYou feel a soothing warmth radiating from the room." ;
				setHp( mMaxHp ) ;
				cout << "\nYour health has been regained." ;
			}
			if (mLocation->getEvil())
			{
				cout << "\nYou are suddenly overwhelmed by an evil pressure in the room." ;
				cout << "\nYou lose 3 health." ;
				int evilHpWest = getHp() ;
				evilHpWest = evilHpWest - 3 ;
				setHp( evilHpWest ) ;
			}

			mLocation->searchResponse() ;
			break ;

		//Error catching, should not show up in game
		default:
			cout << "\nYou have transcended time and space." ;
	}

	return;
}

//Checks if player is dead
Player::dead Player::death( void )
{
	if( getHp() <= 0 )
	{
		return true ;
	}
	
	return false ;
}









//Dungeon Class
Dungeon::Dungeon( int maxRooms ) 
	: mMaxRooms(maxRooms)
{
	mRooms.reserve( maxRooms ) ;
}

//Checks Dungeon Completion
bool Dungeon::isComplete( void )
{
	bool flag = true ;

	//Checks each room to make sure there are no monsters remaining
	for( unsigned int i = 0 ; i < mRooms.size() ; ++i )
	{
		if( mRooms[i]->mMonsters.empty() )
		{
			continue ;
		}
		else
		{
			flag = false ;
			break ;
		}
	}

	return flag ;
}

//add player to dungeon
void Dungeon::addPlayer( Player *newPlayer )
{
	mPlayers.push_back( newPlayer ) ;
	generatePlayerStats( newPlayer ) ;

	return;
}

//initializes the player stats
void Dungeon::generatePlayerStats( Player* newPlayer )
{
	newPlayer->mMaxHp = 10 ;
	newPlayer->setHp( newPlayer->mMaxHp ) ;
	newPlayer->setStrength( 2 ) ;
	newPlayer->setDefense( 2 ) ;
}
//add room to dungeon
void Dungeon::addRoom( Room *newRoom )
{
	mRooms.push_back( newRoom ) ;

	return ;
}

//remove player from dungeon
void Dungeon::removePlayer( std::string playerName )
{

	for( unsigned int i = 0 ; i < mPlayers.size() ; ++i )
	{
		if( playerName == mPlayers[i]->getName() )
		{
			mPlayers.erase( mPlayers.begin() + i ) ;
			break ;
		}
	}

	return ;
}

//combat looping
void Dungeon::combatLoop( Player& hero, Monster& villain )
{
	villain.inCombat = true ;

	while( true )
	{
		cout << hero.attack( villain.getName() ) << endl ;
		if( villain.getHp() <= 0 )
		{
			cout << villain.getName() + " was slain by the valiant " << hero.getName() << endl;
			hero.mLocation->killMonster( villain.getName() ) ;
			return ;
		}
		else
		{
			int damage = 0 ;
			damage = villain.getStrength() - hero.getDefense() ;

			if( damage > 0 )
			{
				hero.setHp( hero.getHp() - damage ) ;
				cout << hero.getName() + " was dealt " << damage << " damage" << endl ;
			}
			else
			{
				cout << hero.getName() + " dodged the attack" << endl ;
			}

			if( hero.death() )
			{
				cout << hero.getName() + " was slain by the horrible " + villain.getName() << endl;
				return ;
			}
		}
	}
}

//returns player info
string* Dungeon::playerStatus( Player& player )
{
	stringstream ss ;
	string temp ;
	const int statusCount = 7 ;
	string* response = new string[statusCount] ;

	response[0] = "Name: " + player.getName() ;

	ss << player.getHp() ;
	ss >> temp ;
	response[1] = "HP: " + temp ;
	ss.clear() ;
	temp.clear() ;
	ss << player.mMaxHp ;
	ss >> temp ;
	response[1] = response[1] + " / " + temp ;
	temp.clear() ;
	ss.clear() ;

	ss << player.getStrength() ;
	ss >> temp ;
	response[2] = "Strength: " + temp ;
	ss.clear() ;
	temp.clear() ;

	ss << player.getDefense() ;
	ss >> temp ;
	response[3] = "Defense: " + temp ;
	ss.clear() ;
	temp.clear() ;

	if( NULL == player.mLocation )
	{
		//error catching
		response[4] = "Error: BAD LOCATION" ;
	}
	else
	{
		response[4] = "Current Location: " + player.getLocation() ;
	}

	if( NULL == player.mWeapon )
	{
		response[5] = "Equipped Weapon: none" ;
	}
	else
	{
		response[5] = "Equipped Weapon: " + player.mWeapon->getName() ;
	}

	if( NULL == player.mArmor )
	{	
		response[6] = "Equipped Armor: none" ;
	}
	else
	{
		response[6] = "Equipped Armor: " + player.mArmor->getName() ;
	}

	return response ;
}









//Validation Class
Validation::valid Validation::validateMessage( std::string message )
{
	//to lowercase
	locale lower ;
	for( unsigned int i = 0 ; i < message.length() ; ++i )
	{
		message [ i ] = tolower( message[ i ], lower ) ;
	}

	bool keywordTest = false ; 
	bool commandTest = false ; 
	bool moveCommandTest = true ; // Checks for a valid direction
	unsigned int inputIndex = 0;

	//checks first letter in the command
	switch( message[ 0 ] )
	{
		case 'a': //Attack 
		case 'm': //Move
		case 'e': //Equip
		case 'y': //You
		case 'r': //Room Info
			keywordTest = true ;
			break ;	

		default:
			keywordTest = false ;
	}

	//if the first letter of the command is not a, n, e, y, or r then false
	if( false == keywordTest )
	{
		return false ;
	}

	//checks the command before ":" is received
	string subMessage ;

	for( unsigned int i = 0 ; i < message.size() ; ++i )
	{
		if( message[ i ] == ':' )
		{
			inputIndex = i;
			subMessage += message[ i ] ;
			break ;
		}
		else
		{
			subMessage += message[ i ] ;
			continue ;
		}
	}

	//makes sure the command is one of the below
	if( subMessage == "a:" ||
		subMessage == "mv:" ||
		subMessage == "eq:" ||
		subMessage == "you:" ||
		subMessage == "rm:" )
	{
		commandTest = true ;
	}
	else
	{
		return false;
	}

	//Checks to make sure the cardinal direction is input correctly
	if( subMessage == "mv:" )
	{
		if( inputIndex + 1 == message.size() )
		{
			moveCommandTest = false;
		}

		while( inputIndex < message.size() )
		{
			if( false == moveCommandTest )
			{
				break ;
			}

			if(message[ inputIndex ] == ' ')
			{
				moveCommandTest = false;
				break ;
			}

			++inputIndex ;
		}	
	}

	//if all three checks are true, then the command is valid
	if( true == commandTest && true == keywordTest && true == moveCommandTest )
	{
		return true ;
	}
	//else if one of the three validation tests doesn't check out, then false
	else
	{
		return false ;
	}
}

//command extraction function
char CommandHelper::extractCommand(std::string fromValidation)
{
	//Gets first letter from string
	return fromValidation[ 0 ] ;
}

//parses command input after the :
string CommandHelper::extractValue(std::string fromValidation)
{
	if( fromValidation[ 1 ] == ':' )
	{
		return fromValidation.substr( 2, fromValidation.length() ) ;
	}

	return fromValidation.substr( 3, fromValidation.length() ) ;
}