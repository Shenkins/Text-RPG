//****************************************************************************//
//  Author:           Andrew Shen
//  Date Created:     March 4, 2015
//  Last Modified:    March 18, 2015
//  Assignment:       Final Project
//  Filename:         final.cpp
//
//  Overview:         This is a dungeon crawling game in the classic text-based
//					  RPG format. User can move in four cardinal directions,
//					  from room to room, equip items, and attack monsters. The
//					  goal of the game is to cleanse the dungeon of all evil
//					  creatures but the boss monster is essentially invincible.
//					  There are two hidden rooms that can be reached that
//					  contain the necessary equipment pieces to actually defeat
//					  the invincible monster. The trick is to be meticulous in
//					  searching the rooms using the room info action!
//                   
//  Input:            User is asked for various inputs of commands that allow
//					  the user to navigate through the labyrinth.
//
//  Output:           The output of the game will let the user know his or her
//					  player status, attack results, room information.
//
//****************************************************************************//

#include "data.h"	//data.h header file
#include <stdio.h>	//for timing implementation
#include <time.h>	//
#include <chrono> 	//

using namespace MUD ; //custom namespace from header

//Main function
int main(void)
{

	//Clear screen
	cout << string(50, '\n');

	//Program Title
	cout << "   *       *       *   \n"
	   	 << "   *       *       *   \n"
	   	 << "  ***     ***     ***  \n"
		 << "*** *** *** *** *** ***\n"
		 << "  |||     |||     |||  \n"
		 << "  |||     |||     |||  \n"
		 << "  |||     |||     |||  \n"
		 << "  |||     |||     |||  \n"
		 << "  |||     |||     |||  \n"
		 << "  |||     |||     |||  \n"
		 << "  |||     |||     |||  \n"
		 << "   v       v       v   \n";

	cout << "\n________________________  "
		 << "\n\\ The Cursed Labyrinth  \\ "
		 << "\n/_______________________/ "
		 << "\nCreated by: Andrew Shen   "
		 << "\nshena@engr.oregonstate.edu"
		 << endl << endl ;

	//Display needed info for the players
	cout << "<<- The Adventure Begins -------------------------------------<<<<<" << endl
		 << "  After a great earthquake tore the world asunder, an ancient "      << endl
		 << "  labyrinth became unsealed. Malevolent creatures long forgotten "   << endl
		 << "  began to spill to the surface, plunging the world a dark age. "    << endl
		 << "  Brave heroes ventured forth to the cleanse the source of evil, "   << endl
		 << "  traveling to the world's end to defeat the great evils that lay "  << endl
		 << "  within the Cursed Labyrinth. Many those that came before you "     << endl
		 << "  perished but without their sacrifice, the world would have long "  << endl
		 << "  been lost. The time has come for you to enter the Cursed "         << endl
		 << "  Labyrinth and put an end to the evil that lies within and save "   << endl
		 << "  the world once and for all."                                       << endl
		 << ">>>>>------------------------------------------------------------>>" << endl;

	//Create the dungeon
	Dungeon labyrinth( 28 ) ;

	//Create items
	Item* trainingsword = new Item( "trainingsword", Item::WEAPON, 6, 0, 0) ;
	Item* sharpsword = new Item( "sharpsword", Item::WEAPON, 12, 0, 0 ) ;
	Item* temperedblade = new Item( "temperedblade", Item::WEAPON, 50, 0, 0 ) ;
	Item* hearteatersword = new Item( "hearteatersword", Item::WEAPON, 100, 0, 0 ) ;
	Item* longclaw = new Item( "longclaw", Item::WEAPON, 350, 0, 0 ) ;
	Item* ultimaweapon = new Item( "ultimaweapon", Item::WEAPON, 1000, 1000, 1000 ) ;
	Item* haxsword = new Item( "haxsword", Item::WEAPON, 9999, 0, 0 ) ;

	Item* trainingarmor = new Item( "trainingarmor", Item::ARMOR, 0, 0, 5) ;
	Item* leatherarmor = new Item( "leatherarmor", Item::ARMOR, 0, 5, 15 ) ;
	Item* bronzearmor = new Item( "bronzearmor", Item::ARMOR, 0, 7, 20 ) ;
	Item* steelplate = new Item( "steelplate", Item::ARMOR, 0, 12, 30 ) ;
	Item* obsidianmail = new Item( "obsidianmail", Item::ARMOR, 0, 15, 35 ) ;
	Item* dragonplate = new Item( "dragonplate", Item::ARMOR, 0, 20, 100 ) ;
	Item* hackerplate = new Item( "hackerplate", Item::ARMOR, 0, 9999, 9999 ) ;
	
	//Create Monsters
	Monster* giantmolerat = new Monster( "giantmolerat", 15, 2, 3 ) ;
	Monster* goblin = new Monster( "goblin", 5, 3, 1 ) ;
	Monster* imp = new Monster( "imp", 5, 5, 2 ) ;
	Monster* hobgoblin = new Monster( "hobgoblin", 5, 5, 5 ) ;
	Monster* orc = new Monster( "orc", 6, 3, 7 ) ;
	Monster* lesserdemon = new Monster( "lesserdemon", 10, 10, 9 ) ;
	Monster* stonegiant = new Monster( "stonegiant", 20, 15, 3 ) ;
	Monster* manfacedspider = new Monster( "manfacedspider", 25, 20, 15 ) ;
	Monster* willowisp = new Monster( "willowisp", 50, 21, 9 ) ;
	Monster* dullahan = new Monster( "dullahan", 100, 10, 10 ) ;
	Monster* jiangsi = new Monster( "jiangsi", 150, 90, 0 ) ;
	Monster* vampire = new Monster( "vampire", 250, 30, 40 ) ;
	Monster* creeper = new Monster( "creeper", 50, 21, 4 ) ;
	Monster* skeletonhorde = new Monster( "skeletonhorde", 55, 40, 1 ) ;
	Monster* slenderman = new Monster( "slenderman", 300, 100, 100 ) ;
	Monster* corruptedking = new Monster( "corruptedking", 500, 300, 1 ) ;
	Monster* coredump = new Monster( "coredump", 5000, 5000, 5000 ) ;

	//Create Rooms
	Room* A = new Room( "The Stone Gateway", "an intimidating passage" ) ;
	Room* B = new Room( "The Atrium", "a room that once welcomed visitors", sharpsword ) ;
	Room* C = new Room( "The Mossy Cavern", "a moss covered room"  ) ;
	Room* D = new HolyRoom( "The Verdant Growth", "a room filled with strange plants", leatherarmor ) ;
	Room* E = new Room( "The Abyss", "an endless pit" ) ;
	Room* F = new Room( "The Mausoleum", "a room with a heavy atmosphere", bronzearmor ) ;
	Room* G = new Room( "The Ballroom", "a once grand room that now lies in shambles", temperedblade ) ;
	Room* H = new Room( "The Noxious Room", "a rotten smelling room", hearteatersword ) ;
	Room* I = new EvilRoom( "The Spider's Lair", "a room covered in webs", NULL ) ;
	Room* J = new Room( "The Stygian River", "a dark and ominous river" ) ;
	Room* K = new Room( "The Battlements", "a room filled with broken armor and rusty weapons" ) ;
	Room* L = new HolyRoom( "The Crystal Cavern", "a radiant room", NULL ) ;
	Room* M = new Room( "The Frost Cave", "a frigid chamber", steelplate ) ;
	Room* N = new Room( "The Chilling Chamber", "a cold room" ) ;
	Room* O = new HolyRoom( "The Sacred Spring", "a calming pool of clear water", NULL ) ;
	Room* P = new Room( "The Thorny Hall", "a room filled with thorny vines" ) ;
	Room* Q = new Room( "The Forlorn Cavern", "a room of sorrow and longing", longclaw ) ;
	Room* R = new WarpRoom( "The Ethereal Gate", "a strange and ominous portal", NULL ) ;
	Room* S = new Room( "The Fiery Traverse", "a passage of searing flames", obsidianmail ) ;
	Room* T = new Room( "The Library", "a room filled with musty books written in an ancient language" ) ;
	Room* U = new Room( "The Treasury", "an empty room" ) ;
	Room* V = new Room( "The Mirrored Haunt", "a room of eerie reflections", dragonplate ) ;
	Room* W = new EvilRoom( "The Molten Core", "a sweltering chamber", ultimaweapon ) ;
	Room* X = new Room( "The Room of Whispers", "a room that gives you the chills" ) ;
	Room* Y = new Room( "The Throne of Lies", "a grand chamber where a greedy king once sat" ) ;
	Room* Z = new Room( "The End", "the source of darkness" ) ;

	Room* HiddenRoom = new Room("Westeros", "somewhere in a completely different dimension", haxsword ) ;
	Room* HiddenRoom2 = new Room("Middle Earth", "a land of elves and hobbits", hackerplate ) ;


	//Link the rooms up
	A->link( 's', *B ) ;

	B->link( 'e', *C ) ;
	B->link( 's', *D ) ;
	B->link( 'n', *A ) ;
	
	C->link( 'w', *B ) ;
	C->link( 'e', *G ) ;
	C->link( 's', *E ) ;

	D->link( 'n', *B ) ;

	E->link( 'n', *C ) ;
	E->link( 'e', *F ) ;
	
	F->link( 'w', *E ) ;

	G->link( 'w', *C ) ;
	G->link( 'e', *J ) ;
	G->link( 'n', *H ) ;

	H->link( 'w', *I ) ;
	H->link( 's', *G ) ;
	H->link( 'e', *K ) ;

	I->link( 'e', *H ) ;

	J->link( 'n', *K ) ;
	J->link( 's', *L ) ;
	J->link( 'e', *M ) ;
	J->link( 'w', *G ) ;

	K->link( 's', *J ) ;
	K->link( 'w', *H ) ;

	L->link( 'n', *J ) ;

	M->link( 'n', *N ) ;
	M->link( 'e', *P ) ;

	N->link( 'n', *O ) ;
	N->link( 's', *M ) ;

	O->link( 's', *N ) ;

	P->link( 'w', *M ) ;
	P->link( 's', *Q ) ;

	Q->link( 'n', *P ) ;
	Q->link( 'S', *R ) ;
	Q->link( 'e', *S ) ;

	R->link( 'n', *Q ) ;

	S->link( 'w', *Q ) ;
	S->link( 's', *T ) ;

	T->link( 'n', *S ) ;
	T->link( 'e', *U ) ;

	U->link( 'n', *V ) ;
	U->link( 'e', *W ) ;

	V->link( 'n', *Y ) ;
	V->link( 's', *U ) ;
	V->link( 'e', *X ) ;

	W->link( 'w', *U ) ;

	X->link( 'w', *V ) ;

	Y->link( 'n', *Z ) ;
	Y->link( 's', *V ) ;

	HiddenRoom->link( 'n', *L ) ;
	HiddenRoom->link( 's', *L ) ;
	HiddenRoom->link( 'e', *L ) ;
	HiddenRoom->link( 'w', *L ) ;

	HiddenRoom2->link( 'n', *O ) ;
	HiddenRoom2->link( 's', *O ) ;
	HiddenRoom2->link( 'e', *O ) ;
	HiddenRoom2->link( 'w', *O ) ;
	
	//Populate rooms with monsters
	B->addMonster( giantmolerat ) ;
	E->addMonster( goblin ) ;
	G->addMonster( imp ) ;
	H->addMonster( hobgoblin ) ;
	F->addMonster( orc ) ;
	D->addMonster( lesserdemon ) ;
	K->addMonster( stonegiant ) ;
	I->addMonster( manfacedspider ) ;
	P->addMonster( willowisp ) ;
	Q->addMonster( dullahan ) ;
	T->addMonster( jiangsi ) ;
	T->addMonster( vampire ) ;
	P->addMonster( creeper ) ;
	U->addMonster( skeletonhorde ) ;
	S->addMonster( slenderman ) ;
	Y->addMonster( corruptedking ) ;
	Z->addMonster( coredump ) ;

	//Add rooms to labyrinth
	labyrinth.addRoom( A ) ;
	labyrinth.addRoom( B ) ;
	labyrinth.addRoom( C ) ;
	labyrinth.addRoom( D ) ;
	labyrinth.addRoom( E ) ;
	labyrinth.addRoom( F ) ;
	labyrinth.addRoom( G ) ;
	labyrinth.addRoom( H ) ;
	labyrinth.addRoom( I ) ;
	labyrinth.addRoom( J ) ;
	labyrinth.addRoom( K ) ;
	labyrinth.addRoom( L ) ;
	labyrinth.addRoom( M ) ;
	labyrinth.addRoom( N ) ;
	labyrinth.addRoom( O ) ;
	labyrinth.addRoom( P ) ;
	labyrinth.addRoom( Q ) ;
	labyrinth.addRoom( R ) ;
	labyrinth.addRoom( S ) ;
	labyrinth.addRoom( T ) ;
	labyrinth.addRoom( U ) ;
	labyrinth.addRoom( V ) ;
	labyrinth.addRoom( W ) ;
	labyrinth.addRoom( X ) ;
	labyrinth.addRoom( Y ) ;
	labyrinth.addRoom( Z ) ;
	labyrinth.addRoom( HiddenRoom ) ;
	labyrinth.addRoom( HiddenRoom2 ) ;
	
	//for warp room input
	char WarpInput ;

	//Create validation object
	Validation validation ;

	//Create a commandhelper object
	CommandHelper commandhelper ;
	char command ;
	string value ;

	//Get player name
	string input ;
	cout << "\nBrave Hero, before you purge the Cursed Labyrinth of all evil creatures,\n" ;
	cout << "let us hear your name so that the bards can sing songs of your heroism.\n" ;
	cout << "\nPlease enter your name: " ;
	getline(cin, input, '\n');

	//Clear screen
	cout << string(20, '\n');

	//Create player
	Player* one = new Player( input, A ) ;
	labyrinth.addPlayer( one ) ;

	//Equip initial armor and weapon
	one->mArmor = trainingarmor ;
	one->setDefense( one->mArmor->getVitality() ) ;
	one->mMaxHp += one->mArmor->getHealth() ;
	one->mWeapon = trainingsword ;
	one->setStrength( one->mWeapon->getPower() ) ;
	one->setHp( one->mMaxHp ) ;

	//Print out initial player stats
	string* playerStats = new string ;
	playerStats = labyrinth.playerStatus( *one ) ;
	for( int i = 0 ; i < 7 ; ++i )
	{
		cout << playerStats[i] << endl ;
	}	

	//Print initial location
	cout << "\nYou have entered the labyrinth and find yourself standing in " ;
	cout << one->mLocation->getRoomName() ;
	cout << "\n" ;
	cout << one->mLocation->getDescription() ;
	one -> mLocation->searchResponse() ;

	//Print warning message. 20 seconds per turn or health penalty!
	cout << "\nThe air is heavy; you feel an evil miasma rising up around you." ;
	cout << "Better move quick. Any more than 20 seconds of standing still might be dangerous!" ;

	//Print possible actions
	cout << "\n\n------------" << endl ;
	cout << "Command List" << endl ;
	cout << "------------" << endl ;
	cout << "Attack monster - 'a:monster_name'" << endl ;
	cout << "Move - 'mv:direction' (n, s, e, w)" << endl ;
	cout << "Equip new items type - 'eq:weapon_or_armor_name'" << endl ;
	cout << "View player status - you:" << endl ;
	cout << "Get room info - 'rm:'" << endl ;
	cout << "Quit - quit" << endl ;
	//Get command
	cout << "\nInput Command: " ;
	//Start timing command time
	auto startTime= chrono::high_resolution_clock::now();
	getline(cin, input, '\n');

	//Start game
	while( input != "quit" )
	{
		//Clear screen
		cout << string(20, '\n') ;
		//Validate Message
		if( validation.validateMessage( input ) )
		{
			//Parse the command
			command = commandhelper.extractCommand( input ) ;
			value = commandhelper.extractValue( input ) ;

			//End Turn Timer
			auto finishTime = chrono::high_resolution_clock::now() ;
			auto elapsedTime = chrono::duration_cast<chrono::seconds>(finishTime-startTime).count() ;
			cout << "Your turn took " << elapsedTime << " seconds.\n" ;
			// Penalty for taking more than 10 seconds to input a command
			if (elapsedTime > 10)
			{
				cout << "You were idle for took long.\n" ;
				cout << "Your health drops by 1 point due to accumulation of evil energy.\n" ;
				int tempHP = one->getHp() ;
				tempHP = tempHP - 1 ;
				cout << "You now have " << tempHP << " health.\n" ;
				one->setHp( tempHP ) ;
			}
			//Command switch
			switch( command )
			{
				
				case 'a': //Attack a monster!
					cout << "\nCombat Results:\n" ;
					//Monster doesn't exist
					if( &(one->mLocation->getMonsterRef( value )) == NULL )
					{
						cout << "There is no " + value + " at this location" << endl ;
						break ;
					}
					if( one->mLocation->getMonsterRef( value ).inCombat == true )
					{
						cout << "\n\nThe " + value + " is currently fighting" << endl ;
						break ;
					}
					//Start combat loop
					labyrinth.combatLoop( *one, one->mLocation->getMonsterRef( value ) ) ;
					break ;
					
				case 'm': //Move to another room
					one->move( value[ 0 ] ) ;
					cout << endl ;
					break ;
				
				case 'e': //Equip an item
					one->equip( value ) ;
					cout << endl ;
					break ;

				case 'r': //Get Room Info
					cout << "\nYou are currently in " ;
					cout << one->mLocation->getRoomName() ;
					cout << ", " ;
					cout << one->mLocation->getDescription() ;
					one -> mLocation->searchResponse() ;
					cout << endl ;
					break ;

				case 'y': //Player stats
					{
						string* playerStats = new string ;
						playerStats = labyrinth.playerStatus( *one ) ;
						cout << endl;
						for( int i = 0 ; i < 7 ; ++i )
						{
							cout << playerStats[i] << endl ;
						}	
					}
					break ;
			}
		}
		//If invalid command is received or something strange happened!
		else
		{
			cout << "Invalid Command?" << endl ;
			cout << "Make sure your input is correct." << endl ;
			cout << "(secret hint make sure to use 'rm:' command often!)" << endl ;
		}

		//If labyrinth is fully purged!
		if( labyrinth.isComplete() )
		{
			cout << "Dungeon Cleared, YOU WIN!" << endl ;
			break ;
		}

		//If user reaches warp room
		if( one->mLocation->getWarp())
		{
			cout << "\n1- Fame\n"  
			 	 << "2- Wealth\n" 
				 << "3- Power\n"
				 << "4- ?\n"
				 << "5- ??\n"
				 << "What do you seek? " ;
			cin  >> WarpInput ;

			//Correct input of 4 warps user to HiddenRoom
			if (WarpInput == '4')
			{
				one->mLocation = HiddenRoom ;
			}
			//Correct input of 5 warps user to HiddenRoom2
			else if (WarpInput == '5')
			{
				one->mLocation = HiddenRoom2 ;
			}
			//All other inputs warps user to first room
			else
			{
				one->mLocation = A ;
			}
		}

		//If user dies, game over!
		if( one->death() )
		{
			cout << "\n\n" + one->getName() + " has fallen." + "\n\n" ;
			cout << "   GAME OVER        \n" ;
    		cout << " |     '       /    \n" ;
    		cout << " /__      ___ (  /  \n" ;
    		cout << " \\ --`-'-|`---\\ |  \n" ;
    		cout << "  |' _/   ` __/ /   \n" ;
    		cout << "  '._  W    ,--'    \n" ;
    		cout << "     |_:_._/        \n\n" ;
			one->mLocation->getMonsterRef( value ).inCombat = false ;
			input = "quit" ;
		}
		//Otherwise get the next command
		else
		{
			//Display needed info for the players
			cout << "\n\n------------" << endl ;
			cout << "Command List" << endl ;
			cout << "------------" << endl ;
			cout << "Attack monster - 'a:monster_name'" << endl ;
			cout << "Move - 'mv:direction' (n, s, e, w)" << endl ;
			cout << "Equip new item - 'eq:weapon_or_armor_name'" << endl ;
			cout << "View player status - 'you:'" << endl ;
			cout << "Get room info - 'rm:'" << endl ;
			cout << "Quit - quit" << endl ;
			//Get next command
			cout << "\nInput Command: " ;
			startTime= chrono::high_resolution_clock::now();
			getline(cin, input, '\n') ;
		}
	}

	//Clear dungeon of player
	labyrinth.removePlayer( one->getName() ) ;
	cout << "\n\nExiting Game... Good bye!\n\n" ;

	return 0;
}
