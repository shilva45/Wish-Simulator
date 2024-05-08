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
// add epitomized path for chronicle
// save inventory

using namespace std;

string bannerType = "weapon";
string characterBannerVersion = "arlecchino-1";
vector<string> characterRateupBanner = {"Arlecchino (5-Star)", "Freminet (4-Star)", "Lynette (4-Star)", "Xiangling (4-Star)"};
string weaponBannerKeyword = "Crimson Moon's Semblance - The First Great Magic";
vector<string> weaponRateupBanner = {"Crimson Moon's Semblance (5-Star)", "The First Great Magic (5-Star)",  "The Dockhand's Assistant (4-Star)", "Portable Power Saw (4-Star)", "Dragon's Bane (4-Star)", "Eye of Perception (4-Star)", "Favonius Warbow (4-Star)"};

vector<string> threeStarWeaponPool = {"Black Tassel (3-Star)", "Bloodstained Greatsword (3-Star)", "Cool Steel (3-Star)", 
"Debate Club (3-Star)", "Emerald Orb (3-Star)", "Ferrous Shadow (3-Star)", "Harbinger of Dawn (3-Star)", "Magic Guide (3-Star)", 
"Raven Bow (3-Star)", "Sharpshooter's Oath (3-Star)", "Skyrider Sword (3-Star)", "Slingshot (3-Star)", "Thrilling Tales of Dragon Slayers (3-Star)"};

vector<string> fourStarCharacterPool = {"Barbara (4-Star)", "Beidou (4-Star)", "Bennett (4-Star)", "Chongyun (4-Star)", "Fischl (4-Star)", 
"Ningguang (4-Star)", "Noelle (4-Star)", "Razor (4-Star)", "Sucrose (4-Star)", "Xiangling (4-Star)", "Xingqiu (4-Star)", "Diona (4-Star)", 
"Xinyan (4-Star)", "Rosaria (4-Star)", "Yanfei (4-Star)", "Sayu (4-Star)", "Kujou Sara (4-Star)", "Thoma (4-Star)", "Gorou (4-Star)", 
"Yun Jin (4-Star)", "Kuki Shinobu (4-Star)", "Shikanoin Heizou (4-Star)", "Collei (4-Star)", "Dori (4-Star)", "Candace (4-Star)", 
"Layla (4-Star)", "Faruzan (4-Star)", "Yaoyao (4-Star)", "Mika (4-Star)", "Kaveh (4-Star)", "Kirara (4-Star)", "Freminet (4-Star)", 
"Lynette (4-Star)", "Charlotte (4-Star)", "Chevreuse (4-Star)", "Gaming (4-Star)"};

vector<string> fourStarWeaponPool = {"Dragon's Bane (4-Star)", "Eye of Perception (4-Star)", "Favonius Codex (4-Star)", 
"Favonius Greatsword (4-Star)", "Favonius Lance (4-Star)", "Favonius Sword (4-Star)", "Favonius Warbow (4-Star)", "Lion's Roar (4-Star)", 
"Rainslasher (4-Star)", "Rust (4-Star)", "Sacrificial Bow (4-Star)", "Sacrificial Fragments (4-Star)", "Sacrificial Greatsword (4-Star)", 
"Sacrificial Sword (4-Star)", "The Bell (4-Star)", "The Flute (4-Star)", "The Stringless (4-Star)", "The Widsith (4-Star)"};

vector<string> fiveStarCharacterPool = {"Diluc (5-Star)", "Jean (5-Star)", "Keqing (5-Star)", "Mona (5-Star)", "Qiqi (5-Star)", 
"Tighnari (5-Star)", "Dehya (5-Star)"};

vector<string> fiveStarWeaponPool = {"Amos' Bow (5-Star)", "Aquila Favonia (5-Star)", "Lost Prayer to the Sacred Winds (5-Star)", 
"Primodial Jade-Winged Spear (5-Star)", "Skyward Atlas (5-Star)", "Skyward Blade (5-Star)", "Skyward Harp (5-Star)", "Skyward Pride (5-Star)",
"Skyward Spine (5-Star)", "Wolf's Gravestone (5-Star)"};

unordered_map<string, int> fourStarPity;
unordered_map<string, bool> fourStarGuarantee;
unordered_map<string, int> fourStarRate;
unordered_map<string, int> fiveStarPity;
unordered_map<string, bool> fiveStarGuarantee;
unordered_map<string, int> fiveStarRate;

unordered_map<string, int> fatePointCounter = {
	{"weapon", -1}, {"chronicle", -1}
};

unordered_map<string, string> epitomizedPath = {
	{"weapon", "-"}, {"chronicle", "-"}
};

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
	{"ayaka-1", {"Kamisato Ayaka (5-Star)", "Ningguang (4-Star)", "Chongyun (4-Star)", "Yanfei (4-Star)"}},
	{"yoimiya-1", {"Yoimiya (5-Star)", "Sayu (4-Star)", "Diona (4-Star)", "Xinyan (4-Star)"}},
	{"shogun-1", {"Raiden Shogun (5-Star)", "Kujou Sara (4-Star)", "Xiangling (4-Star)", "Sucrose (4-Star)"}},
	{"kokomi-1", {"Sangonomiya Kokomi (5-Star)", "Rosaria (4-Star)", "Beidou (4-Star)", "Xingqiu (4-Star)"}},
	{"tartaglia-3", {"Tartaglia (5-Star)", "Ningguang (4-Star)", "Chongyun (4-Star)", "Yanfei (4-Star)"}},
	{"tao-2", {"Hu Tao (5-Star)", "Thoma (4-Star)", "Diona (4-Star)", "Sayu (4-Star)"}},
	{"albedo-2", {"Albedo (5-Star)", "Bennett (4-Star)", "Noelle (4-Star)", "Rosaria (4-Star)"}},
	{"eula-2", {"Eula (5-Star)", "Bennett (4-Star)", "Noelle (4-Star)", "Rosaria (4-Star)"}},
	{"itto-1", {"Arataki Itto (5-Star)", "Gorou (4-Star)", "Barbara (4-Star)", "Xiangling (4-Star)"}},
	{"shenhe-1", {"Shenhe (5-Star)", "Yun Jin (4-Star)", "Ningguang (4-Star)", "Chongyun (4-Star)"}},
	{"xiao-2", {"Xiao (5-Star)", "Yun Jin (4-Star)", "Ningguang (4-Star)", "Chongyun (4-Star)"}},
	{"zhongli-3", {"Zhongli (5-Star)", "Xingqiu (4-Star)", "Beidou (4-Star)", "Yanfei (4-Star)"}},
	{"ganyu-2", {"Ganyu (5-Star)", "Xingqiu (4-Star)", "Beidou (4-Star)", "Yanfei (4-Star)"}},
	{"miko-1", {"Yae Miko (5-Star)", "Fischl (4-Star)", "Diona (4-Star)", "Thoma (4-Star)"}},
	{"shogun-2", {"Raiden Shogun (5-Star)", "Bennett (4-Star)", "Xinyan (4-Star)", "Kujou Sara (4-Star)"}},
	{"kokomi-2", {"Sangonomiya Kokomi (5-Star)", "Bennett (4-Star)", "Xinyan (4-Star)", "Kujou Sara (4-Star)"}},
	{"ayato-1", {"Kamisato Ayato (5-Star)", "Sucrose (4-Star)", "Xiangling (4-Star)", "Yun Jin (4-Star)"}},
	{"venti-3", {"Venti (5-Star)", "Sucrose (4-Star)", "Xiangling (4-Star)", "Yun Jin (4-Star)"}},
	{"ayaka-2", {"Kamisato Ayaka (5-Star)", "Razor (4-Star)", "Rosaria (4-Star)", "Sayu (4-Star)"}},
	{"yelan-1", {"Yelan (5-Star)", "Barbara (4-Star)", "Yanfei (4-Star)", "Noelle (4-Star)"}},
	{"xiao-3", {"Xiao (5-Star)", "Barbara (4-Star)", "Yanfei (4-Star)", "Noelle (4-Star)"}},
	{"itto-2", {"Arataki Itto (5-Star)", "Kuki Shinobu (4-Star)", "Chongyun (4-Star)", "Gorou (4-Star)"}},
	{"kazuha-2", {"Kaedehara Kazuha (5-Star)", "Shikanoin Heizou (4-Star)", "Ningguang (4-Star)", "Thoma (4-Star)"}},
	{"klee-3", {"Klee (5-Star)", "Shikanoin Heizou (4-Star)", "Ningguang (4-Star)", "Thoma (4-Star)"}},
	{"yoimiya-2", {"Yoimiya (5-Star)", "Bennett (4-Star)", "Xinyan (4-Star)", "Yun Jin (4-Star)"}},
	{"tighnari-1", {"Tighnari (5-Star)", "Collei (4-Star)", "Diona (4-Star)", "Fischl (4-Star)"}},
	{"zhongli-4", {"Zhongli (5-Star)", "Collei (4-Star)", "Diona (4-Star)", "Fischl (4-Star)"}},
	{"ganyu-3", {"Ganyu (5-Star)", "Dori (4-Star)", "Sucrose (4-Star)", "Xingqiu (4-Star)"}},
	{"kokomi-3", {"Sangonomiya Kokomi (5-Star)", "Dori (4-Star)", "Sucrose (4-Star)", "Xingqiu (4-Star)"}},
	{"cyno-1", {"Cyno (5-Star)", "Candace (4-Star)", "Kuki Shinobu (4-Star)", "Sayu (4-Star)"}},
	{"venti-4", {"Venti (5-Star)", "Candace (4-Star)", "Kuki Shinobu (4-Star)", "Sayu (4-Star)"}},
	{"nilou-1", {"Nilou (5-Star)", "Barbara (4-Star)", "Beidou (4-Star)", "Xiangling (4-Star)"}},
	{"albedo-3", {"Albedo (5-Star)", "Barbara (4-Star)", "Beidou (4-Star)", "Xiangling (4-Star)"}},
	{"nahida-1", {"Nahida (5-Star)", "Razor (4-Star)", "Noelle (4-Star)", "Bennett (4-Star)"}},
	{"yoimiya-3", {"Yoimiya (5-Star)", "Razor (4-Star)", "Noelle (4-Star)", "Bennett (4-Star)"}},
	{"miko-2", {"Yae Miko (5-Star)", "Layla (4-Star)", "Thoma (4-Star)", "Shikanoin Heizou (4-Star)"}},
	{"tartaglia-4", {"Tartaglia (5-Star)", "Layla (4-Star)", "Thoma (4-Star)", "Shikanoin Heizou (4-Star)"}},
	{"wanderer-1", {"Wanderer (5-Star)", "Faruzan (4-Star)", "Gorou (4-Star)", "Yanfei (4-Star)"}},
	{"itto-3", {"Arataki Itto (5-Star)", "Faruzan (4-Star)", "Gorou (4-Star)", "Yanfei (4-Star)"}},
	{"shogun-3", {"Raiden Shogun (5-Star)", "Rosaria (4-Star)", "Sayu (4-Star)", "Kujou Sara (4-Star)"}},
	{"ayato-2", {"Kamisato Ayato (5-Star)", "Rosaria (4-Star)", "Sayu (4-Star)", "Kujou Sara (4-Star)"}},
	{"alhaitham-1", {"Alhaitham (5-Star)", "Yaoyao (4-Star)", "Yun Jin (4-Star)", "Xinyan (4-Star)"}},
	{"xiao-4", {"Xiao (5-Star)", "Yaoyao (4-Star)", "Yun Jin (4-Star)", "Xinyan (4-Star)"}},
	{"tao-3", {"Hu Tao (5-Star)", "Xingqiu (4-Star)", "Ningguang (4-Star)", "Beidou (4-Star)"}},
	{"yelan-2", {"Yelan (5-Star)", "Xingqiu (4-Star)", "Ningguang (4-Star)", "Beidou (4-Star)"}},
	{"dehya-1", {"Dehya (5-Star)", "Bennett (4-Star)", "Barbara (4-Star)", "Collei (4-Star)"}},
	{"cyno-2", {"Cyno (5-Star)", "Bennett (4-Star)", "Barbara (4-Star)", "Collei (4-Star)"}},
	{"shenhe-2", {"Shenhe (5-Star)", "Diona (4-Star)", "Sucrose (4-Star)", "Mika (4-Star)"}},
	{"ayaka-3", {"Kamisato Ayaka (5-Star)", "Diona (4-Star)", "Sucrose (4-Star)", "Mika (4-Star)"}},
	{"nahida-2", {"Nahida (5-Star)", "Kuki Shinobu (4-Star)", "Dori (4-Star)", "Layla (4-Star)"}},
	{"nilou-2", {"Nilou (5-Star)", "Kuki Shinobu (4-Star)", "Dori (4-Star)", "Layla (4-Star)"}},
	{"baizhu-1", {"Baizhu (5-Star)", "Kaveh (4-Star)", "Candace (4-Star)", "Fischl (4-Star)"}},
	{"ganyu-4", {"Ganyu (5-Star)", "Kaveh (4-Star)", "Candace (4-Star)", "Fischl (4-Star)"}},
	{"yoimiya-4", {"Yoimiya (5-Star)", "Kirara (4-Star)", "Yun Jin (4-Star)", "Chongyun (4-Star)"}},
	{"miko-3", {"Yae Miko (5-Star)", "Kirara (4-Star)", "Yun Jin (4-Star)", "Chongyun (4-Star)"}},
	{"alhaitham-2", {"Alhaitham (5-Star)", "Shikanoin Heizou (4-Star)", "Xiangling (4-Star)", "Yaoyao (4-Star)"}},
	{"kazuha-3", {"Kaedehara Kazuha (5-Star)", "Shikanoin Heizou (4-Star)", "Xiangling (4-Star)", "Yaoyao (4-Star)"}},
	{"eula-3", {"Eula (5-Star)", "Mika (4-Star)", "Razor (4-Star)", "Thoma (4-Star)"}},
	{"klee-4", {"Klee (5-Star)", "Mika (4-Star)", "Razor (4-Star)", "Thoma (4-Star)"}},
	{"kokomi-4", {"Sangonomiya Kokomi (5-Star)", "Faruzan (4-Star)", "Rosaria (4-Star)", "Yanfei (4-Star)"}},
	{"wanderer-2", {"Wanderer (5-Star)", "Faruzan (4-Star)", "Rosaria (4-Star)", "Yanfei (4-Star)"}},
	{"lyney-1", {"Lyney (5-Star)", "Lynette (4-Star)", "Bennett (4-Star)", "Barbara (4-Star)"}},
	{"yelan-3", {"Yelan (5-Star)", "Lynette (4-Star)", "Bennett (4-Star)", "Barbara (4-Star)"}},
	{"zhongli-5", {"Zhongli (5-Star)", "Freminet (4-Star)", "Sayu (4-Star)", "Noelle (4-Star)"}},
	{"tartaglia-5", {"Tartaglia (5-Star)", "Freminet (4-Star)", "Sayu (4-Star)", "Noelle (4-Star)"}},
	{"neuvillette-1", {"Neuvillette (5-Star)", "Fischl (4-Star)", "Xingqiu (4-Star)", "Diona (4-Star)"}},
	{"tao-4", {"Hu Tao (5-Star)", "Fischl (4-Star)", "Xingqiu (4-Star)", "Diona (4-Star)"}},
	{"wriothesley-1", {"Wriothesley (5-Star)", "Chongyun (4-Star)", "Thoma (4-Star)", "Dori (4-Star)"}},
	{"venti-5", {"Venti (5-Star)", "Chongyun (4-Star)", "Thoma (4-Star)", "Dori (4-Star)"}},
	{"furina-1", {"Furina (5-Star)", "Charlotte (4-Star)", "Collei (4-Star)", "Beidou (4-Star)"}},
	{"baizhu-2", {"Baizhu (5-Star)", "Charlotte (4-Star)", "Collei (4-Star)", "Beidou (4-Star)"}},
	{"cyno-3", {"Cyno (5-Star)", "Kirara (4-Star)", "Kuki Shinobu (4-Star)", "Xiangling (4-Star)"}},
	{"ayato-3", {"Kamisato Ayato (5-Star)", "Kirara (4-Star)", "Kuki Shinobu (4-Star)", "Xiangling (4-Star)"}},
	{"navia-1", {"Navia (5-Star)", "Sucrose (4-Star)", "Rosaria (4-Star)", "Candace (4-Star)"}},
	{"ayaka-4", {"Kamisato Ayaka (5-Star)", "Sucrose (4-Star)", "Rosaria (4-Star)", "Candace (4-Star)"}},
	{"shogun-4", {"Raiden Shogun (5-Star)", "Chevreuse (4-Star)", "Kujou Sara (4-Star)", "Bennett (4-Star)"}},
	{"yoimiya-5", {"Yoimiya (5-Star)", "Chevreuse (4-Star)", "Kujou Sara (4-Star)", "Bennett (4-Star)"}},
	{"xianyun-1", {"Xianyun (5-Star)", "Gaming (4-Star)", "Faruzan (4-Star)", "Noelle (4-Star)"}},
	{"nahida-3", {"Nahida (5-Star)", "Gaming (4-Star)", "Faruzan (4-Star)", "Noelle (4-Star)"}},
	{"xiao-5", {"Xiao (5-Star)", "Yaoyao (4-Star)", "Xinyan (4-Star)", "Ningguang (4-Star)"}},
	{"miko-4", {"Yae Miko (5-Star)", "Yaoyao (4-Star)", "Xinyan (4-Star)", "Ningguang (4-Star)"}},
	{"chiori-1", {"Chiori (5-Star)", "Gorou (4-Star)", "Yun Jin (4-Star)", "Dori (4-Star)"}},
	{"itto-4", {"Arataki Itto (5-Star)", "Gorou (4-Star)", "Yun Jin (4-Star)", "Dori (4-Star)"}},
	{"neuvillette-2", {"Neuvillette (5-Star)", "Barbara (4-Star)", "Xingqiu (4-Star)", "Yanfei (4-Star)"}},
	{"kazuha-4", {"Kaedehara Kazuha (5-Star)", "Barbara (4-Star)", "Xingqiu (4-Star)", "Yanfei (4-Star)"}},
	{"arlecchino-1", {"Arlecchino (5-Star)", "Freminet (4-Star)", "Lynette (4-Star)", "Xiangling (4-Star)"}},
	{"lyney-2", {"Lyney (5-Star)", "Freminet (4-Star)", "Lynette (4-Star)", "Xiangling (4-Star)"}}
};

unordered_map<string, vector<string>> weaponBannerList = {
	{"Aquila Favonia - Amos' Bow", {"Aquila Favonia (5-Star)", "Amos' Bow (5-Star)", "The Flute (4-Star)", "The Bell (4-Star)", "The Widsith (4-Star)", "The Stringless (4-Star)", "Favonius Lance (4-Star)"}},
	{"Lost Prayer to the Sacred Winds - Wolf's Gravestone", {"Lost Prayer to the Sacred Winds (5-Star)", "Wolf's Gravestone (5-Star)", "Sacrificial Sword (4-Star)", "Sacrificial Bow (4-Star)", "Sacrificial Fragments (4-Star)", "Sacrificial Fragments (4-Star)", "Dragon's Bane (4-Star)"}},
	{"Memory of Dust - Skyward Harp", {"Memory of Dust (5-Star)", "Skyward Harp (5-Star)",  "The Flute (4-Star)", "Rainslasher (4-Star)", "Eye of Perception (4-Star)", "Rust (4-Star)", "Favonius Lance (4-Star)"}},
	{"Vortex Vanquisher - The Unforged", {"Vortex Vanquisher (5-Star)", "The Unforged (5-Star)",  "Lion's Roar (4-Star)", "The Bell (4-Star)", "Favonius Codex (4-Star)", "Favonius Warbow (4-Star)", "Dragon's Bane (4-Star)"}},
	{"Summit Shaper - Skyward Atlas", {"Summit Shaper (5-Star)", "Skyward Atlas (5-Star)",  "Favonius Sword (4-Star)", "Favonius Greatsword (4-Star)", "Favonius Lance (4-Star)", "Sacrificial Fragments (4-Star)", "The Stringless (4-Star)"}},
	{"Skyward Pride - Amos' Bow", {"Skyward Pride (5-Star)", "Amos' Bow (5-Star)",  "Sacrificial Sword (4-Star)", "The Bell (4-Star)", "Dragon's Bane (4-Star)", "Eye of Perception (4-Star)", "Favonius Warbow (4-Star)"}},
	{"Primordial Jade Cutter - Primordial Jade Winged-Spear", {"Primordial Jade Cutter (5-Star)", "Primordial Jade Winged-Spear (5-Star)",  "The Flute (4-Star)", "Sacrificial Greatsword (4-Star)", "Rust (4-Star)", "Eye of Perception (4-Star)", "Favonius Lance (4-Star)"}},
	{"Staff of Homa - Wolf's Gravestone", {"Staff of Homa (5-Star)", "Wolf's Gravestone (5-Star)",  "Lithic Blade (4-Star)", "Lithic Spear (4-Star)", "Lion's Roar (4-Star)", "Sacrificial Bow (4-Star)", "The Widsith (4-Star)"}},
	{"Elegy for the End - Skyward Blade", {"Elegy for the End (5-Star)", "Skyward Blade (5-Star)",  "The Alley Flash (4-Star)", "Wine and Song (4-Star)", "Favonius Greatsword (4-Star)", "Favonius Warbow (4-Star)", "Dragon's Bane (4-Star)"}},
	{"Skyward Harp - Lost Prayer to the Sacred Winds", {"Skyward Harp (5-Star)", "Lost Prayer to the Sacred Winds (5-Star)",  "Alley Hunter (4-Star)", "Favonius Sword (4-Star)", "Sacrificial Greatsword (4-Star)", "Favonius Codex (4-Star)", "Favonius Lance (4-Star)"}},
	{"Summit Shaper - Memory of Dust", {"Summit Shaper (5-Star)", "Memory of Dust (5-Star)",  "Lithic Blade (4-Star)", "Lithic Spear (4-Star)", "The Flute (4-Star)", "Eye of Perception (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"Song of Broken Pines - Aquila Favonia", {"Song of Broken Pines (5-Star)", "Aquila Favonia (5-Star)",  "Sacrificial Sword (4-Star)", "Rainslasher (4-Star)", "Dragon's Bane (4-Star)", "Sacrificial Fragments (4-Star)", "Rust (4-Star)"}},
	{"Skyward Pride - Lost Prayer to the Sacred Winds", {"Skyward Pride (5-Star)", "Lost Prayer to the Sacred Winds (5-Star)",  "Mitternachts Waltz (4-Star)", "Lion's Roar (4-Star)", "The Bell (4-Star)", "Favonius Lance (4-Star)", "The Widsith (4-Star)"}},
	{"Freedom-Sworn - Skyward Atlas", {"Freedom-Sworn (5-Star)", "Skyward Atlas (5-Star)",  "The Alley Flash (4-Star)", "Wine and Song (4-Star)", "Alley Hunter (4-Star)", "Dragon's Bane (4-Star)", "Favonius Greatsword (4-Star)"}},
	{"Mistsplitter Reforged - Skyward Spine", {"Mistsplitter Reforged (5-Star)", "Skyward Spine (5-Star)",  "Sacrificial Greatsword (4-Star)", "Favonius Lance (4-Star)", "Favonius Codex (4-Star)", "Favonius Sword (4-Star)", "The Stringless (4-Star)"}},
	{"Thundering Pulse - Skyward Blade", {"Thundering Pulse (5-Star)", "Skyward Blade (5-Star)",  "Sacrificial Sword (4-Star)", "Rainslasher (4-Star)", "Dragon's Bane (4-Star)", "Sacrificial Fragments (4-Star)", "Favonius Warbow (4-Star)"}},
	{"Engulfing Lightning - The Unforged", {"Engulfing Lightning (5-Star)", "The Unforged (5-Star)",  "Lion's Roar (4-Star)", "The Bell (4-Star)", "Favonius Lance (4-Star)", "The Widsith (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"Everlasting Moonglow - Primordial Jade Cutter", {"Everlasting Moonglow (5-Star)", "Primordial Jade Cutter (5-Star)",  "The Flute (4-Star)", "Favonius Greatsword (4-Star)", "Dragon's Bane (4-Star)", "Favonius Codex (4-Star)", "The Stringless (4-Star)"}},
	{"Polar Star - Memory of Dust", {"Polar Star (5-Star)", "Memory of Dust (5-Star)",  "Akuoumaru (4-Star)", "Favonius Sword (4-Star)", "Favonius Lance (4-Star)", "Eye of Perception (4-Star)", "Rust (4-Star)"}},
	{"Staff of Homa - Elegy for the End", {"Staff of Homa (5-Star)", "Elegy for the End (5-Star)",  "Wavebreaker's Fin (4-Star)", "Mouun's Moon (4-Star)", "Sacrificial Sword (4-Star)", "Rainslasher (4-Star)", "The Widsith (4-Star)"}},
	{"Freedom-Sworn - Song of Broken Pines", {"Freedom-Sworn (5-Star)", "Song of Broken Pines (5-Star)",  "Wine and Song (4-Star)", "Alley Hunter (4-Star)", "Lion's Roar (4-Star)", "Sacrificial Greatsword (4-Star)", "Dragon's Bane (4-Star)"}},
	{"Redhorn Stonethresher - Skyward Harp", {"Redhorn Stonethresher (5-Star)", "Skyward Harp (5-Star)",  "The Alley Flash (4-Star)", "Mitternachts Waltz (4-Star)", "The Bell (4-Star)", "Favonius Lance (4-Star)", "Sacrificial Fragments (4-Star)"}},
	{"Calamity Queller - Primordial Jade Winged-Spear", {"Calamity Queller (5-Star)", "Primordial Jade Winged-Spear (5-Star)",  "Lithic Spear (4-Star)", "The Flute (4-Star)", "Favonius Greatsword (4-Star)", "The Widsith (4-Star)", "Favonius Warbow (4-Star)"}},
	{"Vortex Vanquisher - Amos' Bow", {"Vortex Vanquisher (5-Star)", "Amos' Bow (5-Star)",  "Lithic Blade (4-Star)", "Favonius Sword (4-Star)", "Dragon's Bane (4-Star)", "Favonius Codex (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"Kagura's Verity - Primordial Jade Cutter", {"Kagura's Verity (5-Star)", "Primordial Jade Cutter (5-Star)",  "Wavebreaker's Fin (4-Star)", "Sacrificial Sword (4-Star)", "Rainslasher (4-Star)", "Eye of Perception (4-Star)", "The Stringless (4-Star)"}},
	{"Engulfing Lightning - Everlasting Moonglow", {"Engulfing Lightning (5-Star)", "Everlasting Moonglow (5-Star)",  "Akuoumaru (4-Star)", "Mouun's Moon (4-Star)", "Lion's Roar (4-Star)", "Favonius Lance (4-Star)", "Sacrificial Fragments (4-Star)"}},
	{"Haran Geppaku Futsu - Elegy for the End", {"Haran Geppaku Futsu (5-Star)", "Elegy for the End (5-Star)",  "The Flute (4-Star)", "Sacrificial Greatsword (4-Star)", "Dragon's Bane (4-Star)", "The Widsith (4-Star)", "Rust (4-Star)"}},
	{"Mistsplitter Reforged - The Unforged", {"Mistsplitter Reforged (5-Star)", "The Unforged (5-Star)",  "Favonius Sword (4-Star)", "The Bell (4-Star)", "Favonius Lance (4-Star)", "Favonius Codex (4-Star)", "Favonius Warbow (4-Star)"}},
	{"Aqua Simulacra - Primordial Jade Winged-Spear", {"Aqua Simulacra (5-Star)", "Primordial Jade Winged-Spear (5-Star)",  "Lithic Spear (4-Star)", "Eye of Perception (4-Star)", "Favonius Greatsword (4-Star)", "Sacrificial Bow (4-Star)", "Sacrificial Sword (4-Star)"}},
	{"Redhorn Stonethresher - Memory of Dust", {"Redhorn Stonethresher (5-Star)", "Memory of Dust (5-Star)",  "Lithic Blade (4-Star)", "Lion's Roar (4-Star)", "Dragon's Bane (4-Star)", "Sacrificial Fragments (4-Star)", "The Stringless (4-Star)"}},
	{"Freedom-Sworn - Lost Prayer to the Sacred Winds", {"Freedom-Sworn (5-Star)", "Lost Prayer to the Sacred Winds (5-Star)",  "The Alley Flash (4-Star)", "Mitternachts Waltz (4-Star)", "Rainslasher (4-Star)", "Favonius Lance (4-Star)", "The Widsith (4-Star)"}},
	{"Thundering Pulse - Summit Shaper", {"Thundering Pulse (5-Star)", "Summit Shaper (5-Star)",  "Wine and Song (4-Star)", "Alley Hunter (4-Star)", "The Flute (4-Star)", "Sacrificial Greatsword (4-Star)", "Dragon's Bane (4-Star)"}},
	{"Hunter's Path - Vortex Vanquisher", {"Hunter's Path (5-Star)", "Vortex Vanquisher (5-Star)",  "Favonius Sword (4-Star)", "The Bell (4-Star)", "Favonius Lance (4-Star)", "Favonius Codex (4-Star)", "The Stringless (4-Star)"}},
	{"Everlasting Moonglow - Amos' Bow", {"Everlasting Moonglow (5-Star)", "Amos' Bow (5-Star)",  "Sacrificial Sword (4-Star)", "Favonius Greatsword (4-Star)", "Dragon's Bane (4-Star)", "Eye of Perception (4-Star)", "Rust (4-Star)"}},
	{"Staff of the Scarlet Sands - Elegy for the End", {"Staff of the Scarlet Sands (5-Star)", "Elegy for the End (5-Star)",  "Makhaira Aquamarine (4-Star)", "Lion's Roar (4-Star)", "Favonius Lance (4-Star)", "Sacrificial Fragments (4-Star)", "Favonius Warbow (4-Star)"}},
	{"Key of Khaj-Nisut - Primordial Jade Cutter", {"Key of Khaj-Nisut (5-Star)", "Primordial Jade Cutter (5-Star)",  "Xiphos' Moonlight (4-Star)", "Wandering Evenstar (4-Star)", "Rainslasher (4-Star)", "Dragon's Bane (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"A Thousand Floating Dreams - Thundering Pulse", {"A Thousand Floating Dreams (5-Star)", "Thundering Pulse (5-Star)",  "The Flute (4-Star)", "Sacrificial Greatsword (4-Star)", "Favonius Lance (4-Star)", "The Widsith (4-Star)", "Rust (4-Star)"}},
	{"Kagura's Verity - Polar Star", {"Kagura's Verity (5-Star)", "Polar Star (5-Star)",  "Favonius Sword (4-Star)", "The Bell (4-Star)", "Dragon's Bane (4-Star)", "Favonius Codex (4-Star)", "The Stringless (4-Star)"}},
	{"Tulaytullah's Remembrance - Redhorn Stonethresher", {"Tulaytullah's Remembrance (5-Star)", "Redhorn Stonethresher (5-Star)",  "Wavebreaker's Fin (4-Star)", "Sacrificial Sword (4-Star)", "Favonius Greatsword (4-Star)", "Eye of Perception (4-Star)", "Favonius Warbow (4-Star)"}},
	{"Engulfing Lightning - Haran Geppaku Futsu", {"Engulfing Lightning (5-Star)", "Haran Geppaku Futsu (5-Star)",  "Akuoumaru (4-Star)", "Mouun's Moon (4-Star)", "Lion's Roar (4-Star)", "Favonius Lance (4-Star)", "Sacrificial Fragments (4-Star)"}},
	{"Light of Foliar Incision - Primordial Jade Winged-Spear", {"Light of Foliar Incision (5-Star)", "Primordial Jade Winged-Spear (5-Star)",  "Lithic Spear (4-Star)", "The Flute (4-Star)", "Rainslasher (4-Star)", "The Widsith (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"Staff of Homa - Aqua Simulacra", {"Staff of Homa (5-Star)", "Aqua Simulacra (5-Star)",  "Lithic Blade (4-Star)", "Favonius Sword (4-Star)", "Dragon's Bane (4-Star)", "Favonius Codex (4-Star)", "Rust (4-Star)"}},
	{"Beacon of the Reed Sea - Staff of the Scarlet Sands", {"Beacon of the Reed Sea (5-Star)", "Staff of the Scarlet Sands (5-Star)",  "The Alley Flash (4-Star)", "Alley Hunter (4-Star)", "Sacrificial Greatsword (4-Star)", "Dragon's Bane (4-Star)", "Eye of Perception (4-Star)"}},
	{"Calamity Queller - Mistsplitter Reforged", {"Calamity Queller (5-Star)", "Mistsplitter Reforged (5-Star)",  "Wine and Song (4-Star)", "Sacrificial Sword (4-Star)", "The Bell (4-Star)", "Favonius Lance (4-Star)", "Favonius Warbow (4-Star)"}},
	{"A Thousand Floating Dreams - Key of Khaj-Nisut", {"A Thousand Floating Dreams (5-Star)", "Key of Khaj-Nisut (5-Star)",  "Xiphos' Moonlight (4-Star)", "Favonius Greatsword (4-Star)", "Dragon's Bane (4-Star)", "Sacrificial Fragments (4-Star)", "The Stringless (4-Star)"}},
	{"Jadefall's Splendor - Amos' Bow", {"Jadefall's Splendor (5-Star)", "Amos' Bow (5-Star)",  "Makhaira Aquamarine (4-Star)", "Wandering Evenstar (4-Star)", "Lion's Roar (4-Star)", "Favonius Lance (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"Thundering Pulse - Kagura's Verity", {"Thundering Pulse (5-Star)", "Kagura's Verity (5-Star)",  "Akuoumaru (4-Star)", "The Flute (4-Star)", "Dragon's Bane (4-Star)", "The Widsith (4-Star)", "Rust (4-Star)"}},
	{"Light of Foliar Incision - Freedom-Sworn", {"Light of Foliar Incision (5-Star)", "Freedom-Sworn (5-Star)",  "Favonius Codex (4-Star)", "Favonius Sword (4-Star)", "Mouun's Moon (4-Star)", "Sacrificial Greatsword (4-Star)", "Wavebreaker's Fin (4-Star)"}},
	{"Song of Broken Pines - Lost Prayer to the Sacred Winds", {"Song of Broken Pines (5-Star)", "Lost Prayer to the Sacred Winds (5-Star)",  "The Alley Flash (4-Star)", "Alley Hunter (4-Star)", "Rainslasher (4-Star)", "Favonius Lance (4-Star)", "Eye of Perception (4-Star)"}},
	{"Everlasting Moonglow - Tulaytullah's Remembrance", {"Everlasting Moonglow (5-Star)", "Tulaytullah's Remembrance (5-Star)",  "Wine and Song (4-Star)", "Lion's Roar (4-Star)", "The Bell (4-Star)", "Dragon's Bane (4-Star)", "Favonius Warbow (4-Star)"}},
	{"The First Great Magic - Aqua Simulacra", {"The First Great Magic (5-Star)", "Aqua Simulacra (5-Star)",  "Sacrificial Sword (4-Star)", "Favonius Greatsword (4-Star)", "Favonius Lance (4-Star)", "Sacrificial Fragments (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"Vortex Vanquisher - Polar Star", {"Vortex Vanquisher (5-Star)", "Polar Star (5-Star)",  "The Flute (4-Star)", "Sacrificial Greatsword (4-Star)", "Dragon's Bane (4-Star)", "The Widsith (4-Star)", "Rust (4-Star)"}},
	{"Tome of the Eternal Flow - Staff of Homa", {"Tome of the Eternal Flow (5-Star)", "Staff of Homa (5-Star)",  "The Dockhand's Assistant (4-Star)", "Portable Power Saw (4-Star)", "Mitternachts Waltz (4-Star)", "Favonius Lance (4-Star)", "Favonius Codex (4-Star)"}},
	{"Cashflow Supervision - Elegy for the End", {"Cashflow Supervision (5-Star)", "Elegy for the End (5-Star)",  "Prospector's Drill (4-Star)", "Range Gauge (4-Star)", "Favonius Sword (4-Star)", "Rainslasher (4-Star)", "Eye of Perception (4-Star)"}},
	{"Splendor of Tranquil Waters - Jadefall's Splendor", {"Splendor of Tranquil Waters (5-Star)", "Jadefall's Splendor (5-Star)",  "Sacrificial Sword (4-Star)", "The Bell (4-Star)", "Dragon's Bane (4-Star)", "Sacrificial Fragments (4-Star)", "The Stringless (4-Star)"}},
	{"Staff of the Scarlet Sands - Haran Geppaku Futsu", {"Staff of the Scarlet Sands (5-Star)", "Haran Geppaku Futsu (5-Star)",  "Lion's Roar (4-Star)", "Favonius Greatsword (4-Star)", "Favonius Lance (4-Star)", "The Widsith (4-Star)", "Favonius Warbow (4-Star)"}},
	{"Verdict - Mistsplitter Reforged", {"Verdict (5-Star)", "Mistsplitter Reforged (5-Star)",  "Akuoumaru (4-Star)", "Mouun's Moon (4-Star)", "The Flute (4-Star)", "Dragon's Bane (4-Star)", "Favonius Codex (4-Star)"}},
	{"Engulfing Lightning - Thundering Pulse", {"Engulfing Lightning (5-Star)", "Thundering Pulse (5-Star)",  "Wavebreaker's Fin (4-Star)", "Favonius Sword (4-Star)", "Rainslasher (4-Star)", "Eye of Perception (4-Star)", "Rust (4-Star)"}},
	{"Crane's Echoing Call - A Thousand Floating Dreams", {"Crane's Echoing Call (5-Star)", "A Thousand Floating Dreams (5-Star)",  "Lithic Spear (4-Star)", "Sacrificial Sword (4-Star)", "Sacrificial Greatsword (4-Star)", "Sacrificial Fragments (4-Star)", "Sacrificial Bow (4-Star)"}},
	{"Kagura's Verity - Primordial Jade Winged-Spear", {"Kagura's Verity (5-Star)", "Primordial Jade Winged-Spear (5-Star)",  "Lithic Blade (4-Star)", "Lion's Roar (4-Star)", "Favonius Lance (4-Star)", "The Widsith (4-Star)", "The Stringless (4-Star)"}},
	{"Uraku Misugiri - Redhorn Stonethresher", {"Uraku Misugiri (5-Star)", "Redhorn Stonethresher (5-Star)",  "The Alley Flash (4-Star)", "Alley Hunter (4-Star)", "The Bell (4-Star)", "Dragon's Bane (4-Star)", "Favonius Codex (4-Star)"}},
	{"Tome of the Eternal Flow - Freedom-Sworn", {"Tome of the Eternal Flow (5-Star)", "Freedom-Sworn (5-Star)",  "Wine and Song (4-Star)", "Mitternachts Waltz (4-Star)", "The Flute (4-Star)", "Favonius Greatsword (4-Star)", "Favonius Lance (4-Star)"}},
	{"Crimson Moon's Semblance - The First Great Magic", {"Crimson Moon's Semblance (5-Star)", "The First Great Magic (5-Star)",  "The Dockhand's Assistant (4-Star)", "Portable Power Saw (4-Star)", "Dragon's Bane (4-Star)", "Eye of Perception (4-Star)", "Favonius Warbow (4-Star)"}}
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
	vector<string> availablePool;
	int odds;
	
	switch(rarity){
		case 3:
			rnd = rand() % threeStarWeaponPool.size();
			
			cout << "(   + + +   )   You got " << threeStarWeaponPool[rnd] << "!\n";
			break;
		case 4:
			odds = rand() % 100;
			
			if(odds < 50){
				availablePool = fourStarCharacterPool;
				
				if(bannerType == "character"){
					for(int i = 1; i < characterRateupBanner.size(); i++){
						for(int j = 0; j < availablePool.size(); j++){
							if(availablePool[j] == characterRateupBanner[i]) availablePool.erase(availablePool.begin() + j);
						}
					}
				} else if(bannerType == "weapon"){
					for(int i = 2; i < weaponRateupBanner.size(); i++){
						for(int j = 0; j < availablePool.size(); j++){
							if(availablePool[j] == weaponRateupBanner[i]) availablePool.erase(availablePool.begin() + j);
						}
					}
				} else if(bannerType == "standard"){
					availablePool.push_back("Amber (4-Star)");
					availablePool.push_back("Kaeya (4-Star)");
					availablePool.push_back("Lisa (4-Star)");
				} else if(bannerType == "chronicle"){
					availablePool.clear();
					availablePool = characterRateupBanner;
					
					for(int i = availablePool.size() - 1; i >= 0; i--){
						size_t found = availablePool[i].find("5-Star");
					
						if(found != string::npos){
							availablePool.erase(availablePool.begin() + i);
						}
					}
				}
			} else {
				availablePool = fourStarWeaponPool;
				
				if(bannerType == "character"){
					for(int i = 1; i < characterRateupBanner.size(); i++){
						for(int j = 0; j < availablePool.size(); j++){
							if(availablePool[j] == characterRateupBanner[i]) availablePool.erase(availablePool.begin() + j);
						}
					}
				} else if(bannerType == "weapon"){
					for(int i = 2; i < weaponRateupBanner.size(); i++){
						for(int j = 0; j < availablePool.size(); j++){
							if(availablePool[j] == weaponRateupBanner[i]) availablePool.erase(availablePool.begin() + j);
						}
					}
				} else if(bannerType == "chronicle"){
					availablePool.clear();
					availablePool = weaponRateupBanner;
					
					for(int i = availablePool.size() - 1; i >= 0; i--){
						size_t found = availablePool[i].find("5-Star");
					
						if(found != string::npos){
							availablePool.erase(availablePool.begin() + i);
						}
					}
				}
			}
			
			rnd = rand() % availablePool.size();
			
			cout << "(  + + + +  )   You got " << availablePool[rnd] << "!\n";
			fourStarInventory[availablePool[rnd]]++;
			
			break;
		case 5:
			if(bannerType == "character"){
				availablePool = fiveStarCharacterPool;
			
				for(int j = 0; j < availablePool.size(); j++){
					if(availablePool[j] == characterRateupBanner[0]) availablePool.erase(availablePool.begin() + j);
				}
			} else if(bannerType == "weapon"){
				availablePool = fiveStarWeaponPool;
				
				for(int j = availablePool.size() - 1; j >= 0; j--){
					if(availablePool[j] == weaponRateupBanner[0] || availablePool[j] == weaponRateupBanner[1]) availablePool.erase(availablePool.begin() + j);
				}
			} else if(bannerType == "standard"){
				odds = rand() % 100;
				
				if(odds < 50){
					availablePool.clear();
					availablePool = fiveStarCharacterPool;
				} else {
					availablePool.clear();
					availablePool = fiveStarWeaponPool;
				}
			} else if(bannerType == "chronicle"){
				odds = rand() % 100;
				
				if(odds < 50){
					availablePool.clear();
					availablePool = characterRateupBanner;
					
					for(int i = availablePool.size() - 1; i >= 0; i--){
						size_t found = availablePool[i].find("4-Star");
					
						if(found != string::npos){
							availablePool.erase(availablePool.begin() + i);
						}
					}
				} else {
					availablePool.clear();
					availablePool = weaponRateupBanner;
					
					for(int i = availablePool.size() - 1; i >= 0; i--){
						size_t found = availablePool[i].find("4-Star");
					
						if(found != string::npos){
							availablePool.erase(availablePool.begin() + i);
						}
					}
				}
			}
			
			rnd = rand() % availablePool.size();
			
			cout << "( + + + + + )   You got " << availablePool[rnd] << "!\n";
			fiveStarInventory[availablePool[rnd]]++;
			break;
		default:
			break;
	}
}

void wishResultSelect(int rarity){
	int odds = rand() % 100;
	int rnd = 0;
	vector<string> availablePool;
	
	if(bannerType == "character"){
		switch(rarity){
			case 3:
				wishRandomizeLoss(rarity);
				break;
			case 4:
				if(fourStarGuarantee[bannerType] || odds >= 50){
					fourStarGuarantee[bannerType] = false;
					
					int fourStarRateup = rand() % (characterRateupBanner.size() - 1);
					
					cout << "(  + + + +  )   You got " << characterRateupBanner[fourStarRateup + 1] << "!\n";
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
					
					cout << "( + + + + + )   You got " << characterRateupBanner[0] << "!\n";
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
	} else if(bannerType == "weapon"){
		switch(rarity){
			case 3:
				wishRandomizeLoss(rarity);
				break;
			case 4:
				if(fourStarGuarantee[bannerType] || odds >= 50){
					fourStarGuarantee[bannerType] = false;
					
					int fourStarRateup = rand() % (weaponRateupBanner.size() - 2);
					
					cout << "(  + + + +  )   You got " << weaponRateupBanner[fourStarRateup + 2] << "!\n";
					fourStarInventory[weaponRateupBanner[fourStarRateup + 2]]++;
					
					return;
				}
				
				else {
					fourStarGuarantee[bannerType] = true;
					
					wishRandomizeLoss(rarity);
				}
				break;
			case 5:
				if(fatePointCounter[bannerType] == 2){
					cout << "( + + + + + )   You got " << epitomizedPath[bannerType] << "!\n";
					fiveStarInventory[epitomizedPath[bannerType]]++;
					fiveStarGuarantee[bannerType] = false;
					fatePointCounter[bannerType] = 0;
					
					return;
				}
					
				if(fiveStarGuarantee[bannerType] || odds >= 75){
					fiveStarGuarantee[bannerType] = false;
					
					odds = rand() % 100;
					
					if(odds >= 50){
						cout << "( + + + + + )   You got " << weaponRateupBanner[0] << "!\n";
						fiveStarInventory[weaponRateupBanner[0]]++;
						
						if(weaponRateupBanner[0] == epitomizedPath[bannerType]){
							fatePointCounter[bannerType] = 0;
						} else {
							fatePointCounter[bannerType]++;
						}
					} else {
						cout << "( + + + + + )   You got " << weaponRateupBanner[1] << "!\n";						
						fiveStarInventory[weaponRateupBanner[1]]++;
						
						if(weaponRateupBanner[1] == epitomizedPath[bannerType]){
							fatePointCounter[bannerType] = 0;
						} else {
							fatePointCounter[bannerType]++;
						}
					}
					
					return;
				}
				
				else {
					fiveStarGuarantee[bannerType] = true;
					fatePointCounter[bannerType]++;
					
					wishRandomizeLoss(rarity);
				}
				break;
			default:
				break;
			}
	} else if(bannerType == "standard" || bannerType == "chronicle"){
		wishRandomizeLoss(rarity);
	}
}

void wishRaritySelect(){
	if(bannerType != "weapon"){
		if(fourStarPity[bannerType] >= 8) fourStarRate[bannerType] += 510;
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
	} else {
		if(fourStarPity[bannerType] >= 8) fourStarRate[bannerType] += 600;
		if(fiveStarPity[bannerType] >= 63) fiveStarRate[bannerType] += 70;
		
		int rarity = rand() % 1000;
		
		if(rarity < fiveStarRate[bannerType]){
			fiveStarRate[bannerType] = 7;
			fiveStarPity[bannerType] = 0;
			
			fourStarPity[bannerType]++;
			
			wishResultSelect(5);
		} else if(rarity < fiveStarRate[bannerType] + fourStarRate[bannerType]){
			fourStarRate[bannerType] = 60;
			fourStarPity[bannerType] = 0;
			
			fiveStarPity[bannerType]++;
			
			wishResultSelect(4);
		} else {
			fourStarPity[bannerType]++;
			fiveStarPity[bannerType]++;
			
			wishResultSelect(3);
		}
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
			
			cout << "\nPlease select the character banner you would wish to access.\n";
			cout << "The format for a character's banner is [name]-[banner #].\n";
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
					
					cout << "\nIs this your desired banner? [type 'yes' to confirm]\n>> ";
					
					cin >> bannerInput;
					
					if(bannerInput == "yes"){
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
		case 2:
			bannerType = "weapon";
			
			cout << "\nPlease select the weapon banner you would wish to access.\n";
			cout << "The format for a weapon banner is [weapon name].\n";
			cout << "The search is case-sensitive; 'freedom-sworn' will fail to find banners containing Freedom-Sworn.\n";
			cout << "You are allowed to use a substring to search for banners.\n";
			cout << "For example, to access 3.6 phase 1's weapon banner, 'Key' is a valid keyword, among others.";
			
			while(true){
				cout << "\n>> ";
				cin >> bannerInput;
				
				vector<string> validBanners;
				
				for(auto& wb : weaponBannerList){
					size_t found = wb.first.find(bannerInput);
					
					if(found != string::npos){
						validBanners.push_back(wb.first);
					}
				}
				
				if(validBanners.empty()) cout << "There are no banners containing the keyword '" << bannerInput << "'. Please check for spelling errors.\n";
				else {
					cout << "Here are the list of banners containing the keyword '" << bannerInput << "':\n";
					
					for(int i = 0; i < validBanners.size(); i++){
						cout << i+1 << ". " << validBanners[i] << "\n";
					}
					
					cout << "\nPlease choose a banner. [1-" << validBanners.size() << "]\n>> ";
					cin >> input;
					
					if(input <= 0 || input > validBanners.size()){
						cout << "Invalid banner. Please enter your banner keyword again.";
						continue;
					}
					
					string chosenBanner = validBanners[input-1];
					auto& bannerItems = weaponBannerList.find(chosenBanner)->second;
					chosenBanner = weaponBannerList.find(chosenBanner)->first;
					
					cout << "Banner found. The items in the banner are:\n";
					for(auto& item : bannerItems){
						cout << item << "\n";
					}
					
					cout << "\nIs this your desired banner? [type 'yes' to confirm]\n>> ";
					
					cin >> bannerInput;
					
					if(bannerInput == "yes"){
						weaponBannerKeyword = chosenBanner;
						weaponRateupBanner = bannerItems;
						
						epitomizedPath[bannerType] = "-";
						fatePointCounter[bannerType] = -1;
						
						cout << "Banner selected.\n";
						break;
					} else {
						cout << "Please select the weapon banner you wish to access.\n";
					}
				}
			}
			
			break;
		case 3:
			bannerType = "standard";
			break;
		case 4:
			bannerType = "chronicle";
			
			cout << "\nPlease select the chronicled banner you would wish to access.\n";
			cout << "1. Mondstadt\n";
			cout << "2. Liyue\n";
			cout << "3. Inazuma\n";
			cout << "4. Sumeru\n";
			cout << "5. Fontaine";
			
			while(true){
				cout << "\n>> ";
				cin >> bannerInput;
				
				if(bannerInput == "1"){
					characterRateupBanner = {"Albedo (5-Star)", "Diluc (5-Star)", "Eula (5-Star)", "Jean (5-Star)", "Klee (5-Star)", "Mona (5-Star)", 
					"Venti (5-Star)", 
					
					"Amber (4-Star)", "Barbara (4-Star)", "Bennett (4-Star)", "Fischl (4-Star)", "Kaeya (4-Star)", 
					"Lisa (4-Star)", "Noelle (4-Star)", "Razor (4-Star)", "Sucrose (4-Star)", "Diona (4-Star)", "Rosaria (4-Star)", "Mika (4-Star)"};
					characterBannerVersion = "mondstadt";
					
					weaponRateupBanner = {"Aquila Favonia (5-Star)", "Elegy for the End (5-Star)", "Freedom-Sworn (5-Star)", 
					"Lost Prayer to the Sacred Winds (5-Star)", "Skyward Atlas (5-Star)", "Skyward Blade (5-Star)", "Skyward Harp (5-Star)", 
					"Skyward Pride (5-Star)", "Skyward Spine (5-Star)", "Song of Broken Pines (5-Star)", "Wolf's Gravestone (5-Star)", 
					
					"The Alley Flash (4-Star)", "Lion's Roar (4-Star)", "Sacrificial Sword (4-Star)", 
					"The Flute (4-Star)", "Favonius Sword (4-Star)", "Rainslasher (4-Star)", "Sacrificial Greatsword (4-Star)", "The Bell (4-Star)", 
					"Favonius Greatsword (4-Star)", "Favonius Lance (4-Star)", "Dragon's Bane (4-Star)", "Wine and Song (4-Star)", 
					"Eye of Perception (4-Star)", "Sacrificial Fragments (4-Star)", "The Widsith (4-Star)", "Favonius Codex (4-Star)", 
					"Mitternachts Waltz (4-Star)", "Alley Hunter (4-Star)", "Rust (4-Star)", "Sacrificial Bow (4-Star)", "The Stringless (4-Star)", 
					"Favonius Warbow (4-Star)"};
					weaponBannerKeyword = "mondstadt";
				} else if(bannerInput == "2"){
					characterRateupBanner = {"Baizhu (5-Star)", "Ganyu (5-Star)", "Hu Tao (5-Star)", "Keqing (5-Star)", "Qiqi (5-Star)", 
					"Shenhe (5-Star)", "Xianyun (5-Star)", "Xiao (5-Star)", "Yelan (5-Star)", "Zhongli (5-Star)", 
					
					"Beidou (4-Star)", "Chongyun (4-Star)", "Gaming (4-Star)", "Ningguang (4-Star)", "Xiangling (4-Star)", "Xingqiu (4-Star)", 
					"Xinyan (4-Star)", "Yanfei (4-Star)", "Yanfei (4-Star)", "Yaoyao (4-Star)", "Yun Jin (4-Star)"};
					characterBannerVersion = "liyue";
					
					weaponRateupBanner = {"Amos' Bow (5-Star)", "Aqua Simulacra (5-Star)", "Calamity Queller (5-Star)", "Crane's Echoing Call (5-Star)", 
					"Jadefall's Splendor (5-Star)", "Memory of Dust (5-Star)", "Primordial Jade Cutter (5-Star)", 
					"Primordial Jade-Winged Spear (5-Star)", "Staff of Homa (5-Star)", "Summit Shaper (5-Star)", "The Unforged (5-Star)", 
					"Vortex Vanquisher (5-Star)", 
					
					"Dragon's Bane (4-Star)", "Lion's Roar (4-Star)", "Lithic Blade (4-Star)", "Lithic Spear (4-Star)", "Rainslasher (4-Star)"};
					weaponBannerKeyword = "liyue";
				} else if(bannerInput == "3"){
					characterRateupBanner = {"Arataki Itto (5-Star)", "Chiori (5-Star)", "Kaedehara Kazuha (5-Star)", "Kamisato Ayaka (5-Star)", 
					"Kamisato Ayato (5-Star)", "Raiden Shogun (5-Star)", "Sangonomiya Kokomi (5-Star)", "Yae Miko (5-Star)", "Yoimiya (5-Star)", 
					
					"Gorou (4-Star)", "Kirara (4-Star)", "Kujou Sara (4-Star)", "Kuki Shinobu (4-Star)", "Sayu (4-Star)", 
					"Shikanoin Heizou (4-Star)", "Thoma (4-Star)"};
					characterBannerVersion = "inazuma";
					
					weaponRateupBanner = {"Engulfing Lightning (5-Star)", "Everlasting Moonglow (5-Star)", "Haran Geppaku Futsu (5-Star)", 
					"Kagura's Verity (5-Star)", "Mistsplitter Reforged (5-Star)", "Redhorn Stonethresher (5-Star)", "Thundering Pulse (5-Star)", 
					"Uraku Misagiri (5-Star)", 
					
					"Akuoumaru (4-Star)", "Mouun's Moon (4-Star)", "Wavebreaker's Fin (4-Star)"};
					weaponBannerKeyword = "inazuma";
				} else if(bannerInput == "4"){
					characterRateupBanner = {"Alhaitham (5-Star)", "Cyno (5-Star)", "Dehya (5-Star)", "Nahida (5-Star)", "Nilou (5-Star)", 
					"Tighnari (5-Star)", "Wanderer (5-Star)",  
					
					"Candace (4-Star)", "Collei (4-Star)", "Dori (4-Star)", "Faruzan (4-Star)", "Kaveh (4-Star)", "Layla (4-Star)"};
					characterBannerVersion = "sumeru";
					
					weaponRateupBanner = {"A Thousand Floating Dreams (5-Star)", "Beacon of the Reed Sea (5-Star)", "Hunter's Path (5-Star)", 
					"Key of Khaj-Nisut (5-Star)", "Light of Foliar Incision (5-Star)", "Staff of the Scarlet Sands (5-Star)", 
					"Tulaytullah's Remembrance (5-Star)", 
					
					"Makhaira Aquamarine (4-Star)", "Wandering Evenstar (4-Star)", "Xiphos' Moonlight (4-Star)"};
					weaponBannerKeyword = "sumeru";
				} else if(bannerInput == "5"){
					characterRateupBanner = {"Furina (5-Star)", "Lyney (5-Star)", "Navia (5-Star)", "Neuvillette (5-Star)", "Wriothesley (5-Star)", 
					
					"Charlotte (4-Star)", "Chevreuse (4-Star)", "Freminet (4-Star)", "Lynette (4-Star)"};
					characterBannerVersion = "fontaine";
					
					weaponRateupBanner = {"A Thousand Floating Dreams (5-Star)", "Beacon of the Reed Sea (5-Star)", "Hunter's Path (5-Star)", 
					"Key of Khaj-Nisut (5-Star)", "Light of Foliar Incision (5-Star)", "Staff of the Scarlet Sands (5-Star)", 
					"Tulaytullah's Remembrance (5-Star)", 
					
					"Portable Power Saw (4-Star)", "Prospector's Drill (4-Star)", "Range Gauge (4-Star)"};
					weaponBannerKeyword = "fontaine";
				} else {
					cout << "Invalid banner. Please enter a valid banner.";
					continue;
				}
					
				break;
			}
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
		if(fatePointCounter[bannerType] == 2) cout << " ( ! )";
		else if(fiveStarGuarantee[bannerType]) cout << " ( + )";
		
		if(bannerType == "weapon" || bannerType == "chronicle"){
			if(epitomizedPath[bannerType] != "-") cout << "\nCurrent Path: " << epitomizedPath[bannerType] << " | Fate Points [" << fatePointCounter[bannerType] << "/2]";
		}
		
		cout << "\n\n";
		
		cout << "1. Do 1 Pull\n";
		cout << "2. Do 10 Pulls\n";
		cout << "3. View inventory\n";
		cout << "4. Change banner type\n";
		if(bannerType == "weapon" || bannerType == "chronicle"){
			cout << "5. Set Epitomized Path\n";
		}
		cout << ">> ";
		
		cin >> input;
		
		puts("");
		puts("");
		puts("");
		puts("");
		puts("");
		
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
			case 5:
				if(bannerType == "weapon" || bannerType == "chronicle"){
					for(int i = 0; i < 2; i++){
						cout << i+1 << ". " << weaponRateupBanner[i] << "\n";
					}
					
					puts("");
					
					cout << "Please choose the weapon you would like to set your path on.\n";
					
					while(true){
						cout << ">> ";
						cin >> input;
						
						if(input == 1){
							epitomizedPath[bannerType] = weaponRateupBanner[0];
							break;
						} else if(input == 2){
							epitomizedPath[bannerType] = weaponRateupBanner[1];
							break;						
						}
						
						puts("");
						cout << "Please choose a valid option.\n";
					}
					fatePointCounter[bannerType] = 0;
				}
				break;
			default:
				break;	
		}
		
		puts("");
	}
	
    return 0;
}
