#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <time.h>
#include <cstdlib>
#include <random>

// todo
// remove characters on rateup from character pool
// save inventory
// add the rest of banner options lol

using namespace std;

string bannerType = "character";
string characterBannerVersion = "arlecchino-1";
vector<string> characterRateupBanner = {"Arlecchino (5-Star)", "Freminet (4-Star)", "Lynette (4-Star)", "Xiangling (4-Star)"};

vector<string> threeStarWeaponPool = {"Black Tassel (3-Star)", "Bloodstained Greatsword (3-Star)", "Cool Steel (3-Star)", 
"Debate Club (3-Star)", "Emerald Orb (3-Star)", "Ferrous Shadow (3-Star)", "Harbinger of Dawn (3-Star)", "Magic Guide (3-Star)", 
"Raven Bow (3-Star)", "Sharpshooter's Oath (3-Star)", "Skyrider Sword (3-Star)", "Slingshot (3-Star)", "Thrilling Tales of Dragon Slayers (3-Star)"};

vector<string> fourStarCharacterPool = {"Barbara (4-Star)", "Beidou (4-Star)", "Bennett (4-Star)", "Chongyun (4-Star)", "Fischl (4-Star)", 
"Ningguang (4-Star)", "Noelle (4-Star)", "Razor (4-Star)", "Sucrose (4-Star)", "Xiangling (4-Star)", "Xingqiu (4-Star)", "Diona (4-Star)", 
"Xinyan (4-Star)", "Rosaria (4-Star)", "Yanfei (4-Star)", "Sayu (4-Star)", "Kujou Sara (4-Star)", "Thoma (4-Star)", "Gorou (4-Star)", 
"Yun Jin (4-Star)", "Kuki Shinobu (4-Star)", "Shikanoin Heizou (4-Star)", "Collei (4-Star)", "Dori (4-Star)", "Candace (4-Star)", 
"Layla (4-Star)", "Faruzan (4-Star)", "Yaoyao (4-Star)", "Mika (4-Star)", "Kaveh (4-Star)", "Kirara (4-Star)", "Freminet (4-Star)", 
"Lynette (4-Star)", "Charlotte (4-Star)", "Chevreuse (4-Star)", "Gaming (4-Star)"};

vector<string> fiveStarCharacterPool = {"Diluc (5-Star)", "Jean (5-Star)", "Keqing (5-Star)", "Mona (5-Star)", "Qiqi (5-Star)", 
"Tighnari (5-Star)", "Dehya (5-Star)"};

unordered_map<string, int> fourStarPity;
unordered_map<string, bool> fourStarGuarantee;
unordered_map<string, int> fourStarRate;
unordered_map<string, int> fiveStarPity;
unordered_map<string, bool> fiveStarGuarantee;
unordered_map<string, int> fiveStarRate;

unordered_map<string, int> fourStarInventory;
unordered_map<string, int> fiveStarInventory;

unordered_map<string, vector<string>> characterBannerList = {
	{"venti-1", {"Venti (5-Star)", "Barbara (4-Star)", "Fischl (4-Star)", "Xiangling (4-Star)"}},
	{"klee-1", {"Klee (5-Star)", "Xingqiu (4-Star)", "Noelle (4-Star)", "Sucrose (4-Star)"}},
	{"tartaglia-1", {"Tartaglia (5-Star)", "Diona (4-Star)", "Beidou (4-Star)", "Ningguang (4-Star)"}},
	{"zhongli-1", {"Zhongli (5-Star)", "Xinyan (4-Star)", "Razor (4-Star)", "Chongyun (4-Star)"}},
	{"albedo-1", {"Albedo (5-Star)", "Fischl (4-Star)", "Sucrose (4-Star)", "Bennett (4-Star)"}},
	{"ganyu-1", {"Ganyu (5-Star)", "Xiangling (4-Star)", "Xingqiu (4-Star)", "Noelle (4-Star)"}},
	{"xiao-1", {"Xiao (5-Star)", "Diona (4-Star)", "Beidou (4-Star)", "Xinyan (4-Star)"}},
	{"keqing-1", {"Keqing (5-Star)", "Ningguang (4-Star)", "Bennett (4-Star)", "Barbara (4-Star)"}},
	{"tao-1", {"Hu Tao (5-Star)", "Xingqiu (4-Star)", "Xiangling (4-Star)", "Chongyun (4-Star)"}},
	{"venti-2", {"Venti (5-Star)", "Sucrose (4-Star)", "Razor (4-Star)", "Noelle (4-Star)"}},
	{"tartaglia-2", {"Tartaglia (5-Star)", "Rosaria (4-Star)", "Barbara (4-Star)", "Fischl (4-Star)"}},
	{"zhongli-2", {"Zhongli (5-Star)", "Yanfei (4-Star)", "Noelle (4-Star)", "Diona (4-Star)"}},
	{"eula-1", {"Eula (5-Star)", "Xinyan (4-Star)", "Xingqiu (4-Star)", "Beidou (4-Star)"}},
	{"klee-2", {"Klee (5-Star)", "Barbara (4-Star)", "Sucrose (4-Star)", "Fischl (4-Star)"}},
	{"kazuha-1", {"Kaedehara Kazuha (5-Star)", "Rosaria (4-Star)", "Bennett (4-Star)", "Razor (4-Star)"}},
	{"arlecchino-1", {"Arlecchino (5-Star)", "Freminet (4-Star)", "Lynette (4-Star)", "Xiangling (4-Star)"}},
	{"lyney-2", {"Lyney (5-Star)", "Freminet (4-Star)", "Lynette (4-Star)", "Xiangling (4-Star)"}}
};

void setup(){
	vector<string> banners = {"character", "weapon", "standard", "mondstadt", "liyue", "inazuma", "sumeru", "fontaine"};
	
	for(auto& s : banners){
		fourStarPity[s] = 0;
		fourStarGuarantee[s] = false;
		fourStarRate[s] = 51;
		fiveStarPity[s] = 0;
		fiveStarGuarantee[s] = false;
		fiveStarRate[s] = 6;
	}
	
	string filename = "pulls_inventory.txt";
	ifstream Check;
	
	Check.open(filename);
	
	if(!Check.is_open()){
		ofstream File;
		File.open(filename);
		File.close();
		cout << "File was created\n";
	} else {
		cout << "File exists\n";
	}
}

void wishRandomizeLoss(int rarity){
	int rnd = 0;
	switch(rarity){
		case 3:
			rnd = rand() % threeStarWeaponPool.size();
			
			cout << "+ + +       You got " << threeStarWeaponPool[rnd] << "!\n";
			break;
		case 4:
			rnd = rand() % fourStarCharacterPool.size();
			
			cout << "+ + + +     You got " << fourStarCharacterPool[rnd] << "!\n";
			fourStarInventory[fourStarCharacterPool[rnd]]++;
			break;
		case 5:
			rnd = rand() % fiveStarCharacterPool.size();
			
			cout << "+ + + + +   You got " << fiveStarCharacterPool[rnd] << "!\n";
			fiveStarInventory[fiveStarCharacterPool[rnd]]++;
			break;
		default:
			break;
	}
}

void wishResultSelect(int rarity){
	int odds = rand() % 100;
	
	switch(rarity){
		case 3:
			wishRandomizeLoss(rarity);
			break;
		case 4:
			if(fourStarGuarantee[bannerType] || odds >= 50){
				fourStarGuarantee[bannerType] = false;
				
				int fourStarRateup = rand() % (characterRateupBanner.size() - 1);
				
				cout << "+ + + +     You got " << characterRateupBanner[fourStarRateup + 1] << "!\n";
				fourStarInventory[characterRateupBanner[fourStarRateup + 1]]++;
				
				return;
			}
			
			else {
				fourStarGuarantee[bannerType] = true;
				
				wishRandomizeLoss(rarity);
			}
			
			break;
		case 5:
			if(fiveStarGuarantee[bannerType] || odds >= 50){
				fiveStarGuarantee[bannerType] = false;
				
				cout << "+ + + + +   You got " << characterRateupBanner[0] << "!\n";
				fiveStarInventory[characterRateupBanner[0]]++;
				
				return;
			}
			
			else {
				fiveStarGuarantee[bannerType] = true;
				
				wishRandomizeLoss(rarity);
			}
			break;
		default:
			break;
	}
}

void wishRaritySelect(){
	if(fourStarPity[bannerType] >= 9) fourStarRate[bannerType] += 943;
	if(fiveStarPity[bannerType] >= 74) fiveStarRate[bannerType] += 60;
	
	int rarity = rand() % 1000;
	
	if(rarity < fiveStarRate[bannerType]){
		fiveStarRate[bannerType] = 6;
		fiveStarPity[bannerType] = 0;
		
		fourStarPity[bannerType]++;
		
		wishResultSelect(5);
	} else if(rarity < fiveStarRate[bannerType] + fourStarRate[bannerType]){
		fourStarRate[bannerType] = 51;
		fourStarPity[bannerType] = 0;
		
		fiveStarPity[bannerType]++;
		
		wishResultSelect(4);
	} else {
		fourStarPity[bannerType]++;
		fiveStarPity[bannerType]++;
		
		wishResultSelect(3);
	}
}

void checkInventory(){
	cout << "~~~~~~~~~~~ 5-stars ~~~~~~~~~~~\n";
	if(fiveStarInventory.empty()) cout << "             EMPTY\n";
	for(auto& i : fiveStarInventory){
		cout << i.first << ": x" << i.second << "\n";
	}
	
	cout << "~~~~~~~~~~~ 4-stars ~~~~~~~~~~~\n";
	if(fourStarInventory.empty()) cout << "             EMPTY\n";
	for(auto& i : fourStarInventory){
		cout << i.first << ": x" << i.second << "\n";
	}
}

void changeBannerType(){
	int input = 0;
	string bannerInput = "";
	
	cout << "Current setting: " << bannerType << "\n\n";
	
	cout << "1. Limited Character Banner\n";
	cout << "2. Limited Weapon Banner\n";
	cout << "3. Standard Banner\n";
	cout << "4. Chronicled Banner (Regional)\n";
	cout << ">> ";
	
	cin >> input;
	
	switch(input){
		case 1:
			bannerType = "character";
			
			cout << "\nPlease select the character banner you wish to access.\n";
			cout << "The format for a character's banner is [name]-[banner #]\n";
			cout << "Should the character have a space in their name, please pick the latter name.\n";
			cout << "For example, to access Hu Tao's first rerun, type in 'tao-2'.";
			
			while(true){
				cout << "\n>> ";
				cin >> bannerInput;
				
				if(characterBannerList.find(bannerInput) == characterBannerList.end()){
					cout << "Banner was not found. Please check for spelling or format errors.\n";
				} else {
					auto& bannerItems = characterBannerList.find(bannerInput)->second;
					
					cout << "Banner found. The items in the banner are:\n";
					for(auto& item : bannerItems){
						cout << item << "\n";
					}
					
					cout << "\nIs this your desired banner? [1 = yes]\n>> ";
					
					cin >> input;
					
					if(input == 1){
						characterBannerVersion = bannerInput;
						characterRateupBanner = bannerItems;
						
						cout << "Banner selected.\n";
						break;
					} else {
						cout << "Please select the character banner you wish to access.\n";
					}
				}
			}
			
			break;
		case 3:
			bannerType = "standard";
			break;
		default:
			cout << "Cancelled menu.\n";
			return;
	}
	
	cout << "Change success.\n";
}

int main(){
	srand(time(NULL));
	setup();
	
	int input = 0;
	
	while(true){
		cout << "4-star pity: " << fourStarPity[bannerType];
		if(fourStarGuarantee[bannerType]) cout << " ( + )";
		cout << "\n5-star pity: " << fiveStarPity[bannerType];
		if(fiveStarGuarantee[bannerType]) cout << " ( + )";
		cout << "\n\n";
		
		cout << "1. Do 1 Pull\n";
		cout << "2. Do 10 Pulls\n";
		cout << "3. View inventory\n";
		cout << "4. Change banner type\n";
		cout << ">> ";
		
		cin >> input;
		
		switch(input){
			case 1:
				wishRaritySelect();
				break;
			case 2:
				for(int i = 0; i < 10; i++) wishRaritySelect();
				break;
			case 3:
				checkInventory();
				break;
			case 4:
				changeBannerType();
				break;
			default:
				break;	
		}
		
		puts("");
	}
	
    return 0;
}
