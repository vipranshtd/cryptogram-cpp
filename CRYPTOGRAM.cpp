#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <map>
using namespace std;
class morsecode
{
    map<char, string> morse_map = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"}, {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}};
    map<char, string>::iterator it;

public:
    string morse_decoder(ifstream &encoded, ofstream &data)
    {
        string code;
        string output = "";
        while (getline(encoded, code))
        {
            string letter = "";
            for (int i = 0; i < code.length(); i++)
            {
                if (code[i] == '/')
                {
                    data << ' ';
                    output += ' ';
                }
                else if (code[i] == ' ')
                {
                    for (it = morse_map.begin(); it != morse_map.end(); ++it)
                    {
                        if (letter == it->second)
                        {
                            data << it->first;
                            output += it->first;
                            break;
                        }
                    }
                    letter = "";
                }
                else
                {
                    letter += code[i];
                }
            }
            if (letter != "")
            {
                for (it = morse_map.begin(); it != morse_map.end(); ++it)
                {
                    if (letter == it->second)
                    {
                        data << it->first;
                        output += it->first;
                        break;
                    }
                }
            }
        }
        cout << endl
             << "DECODED AND SAVED INTO THE FILE SUCCESSFULLY!" << endl;
        return output;
    };
    void morse_encoder_input(string content, ofstream &enco)
    {
        for (int i = 0; i < content.length(); i++)
        {
            char ch;
            ch = content[i];
            if (ch == ' ')
            {
                enco << "/ ";
            }
            else
            {
                for (it = morse_map.begin(); it != morse_map.end(); ++it)
                {
                    if (ch == it->first || (char)(ch - 32) == it->first)
                    {
                        enco << it->second << " ";
                        break;
                    }
                }
            }
        }
        cout << "ENCODED AND SAVED SUCCESSFULLY!" << endl;
    }
    void morse_encoder(ifstream &data, ofstream &encoded2)
    {
        char ch;
        while (data.get(ch))
        {
            if (ch == ' ')
            {
                encoded2 << "/ ";
            }
            else
            {
                for (it = morse_map.begin(); it != morse_map.end(); ++it)
                {
                    if (ch == it->first || (char)(ch - 32) == it->first)
                    {
                        encoded2 << it->second << " ";
                        break;
                    }
                }
            }
        }
        cout << "ENCODED AND SAVED SUCCESSFULLY!" << endl;
    };
};

vector<string> split_into_words(string text)
{
    istringstream iss(text);
    vector<string> words;
    string word;
    while (iss >> word)
    {
        words.push_back(word);
    }
    return words;
};
char rotate_char(char ch, int rotation)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return 'a' + (ch - 'a' + rotation + 26) % 26;
    }
    else
    {
        return ch;
    }
};
int letter_check(string wd, vector<string> vs)
{
    for (int i = 0; i < vs.size(); i++)
    {
        if (wd == vs[i])
        {
            return 1;
            break;
        }
    }
    return 0;
};
string decoded_text(string txt, int rotation)
{
    string data = "";
    for (char c : txt)
    {
        data += rotate_char(c, rotation);
    }
    return data;
}

string word_rotation(string wd, int rot)
{
    string r_wd = "";
    for (char c : wd)
    {
        r_wd += rotate_char(c, rot);
    }
    return r_wd;
}
class caeser_cypher
{
    vector<string> two_letter_words = {
        "am", "an", "as", "at", "be", "by", "do", "go", "he", "if", "in", "is",
        "it", "me", "my", "no", "of", "on", "or", "so", "to", "up", "us", "we"};
    vector<string> three_letter_words = {
        "the", "and", "are", "but", "not", "you", "all", "any", "can", "had", "her", "was", "one", "our", "out", "day",
        "get", "has", "how", "man", "new", "now", "old", "see", "two", "way", "who", "why", "use", "she", "him", "his",
        "its", "let", "put", "ace", "act", "add", "age", "ago", "aid", "aim", "air", "ale", "ant", "ape", "apt", "arc",
        "arm", "art", "ash", "ask", "ate", "awe", "axe", "bad", "bag", "bar", "bat", "bay", "bed", "bee", "beg", "bet",
        "big", "bin", "bit", "boa", "bob", "bog", "boo", "bop", "bow", "box", "boy", "bun", "bus", "buy", "bye", "cab",
        "cap", "car", "cat", "cob", "cod", "cog", "cop", "cow", "cry", "cub", "cup", "cut", "dad", "dam", "den", "dew",
        "did", "dig", "dim", "din", "dip", "doc", "dog", "dot", "dry", "dub", "dug", "duo", "dye", "ear", "eat", "ebb",
        "eel", "egg", "ego", "elf", "elk", "end", "era", "eve", "eye", "fab", "fad", "fan", "far", "fat", "fax", "fed",
        "fee", "few", "fig", "fin", "fit", "fix", "fly", "fog", "for", "fox", "fun", "fur", "gad", "gag", "gap", "gas",
        "gel", "gem", "get", "gig", "gin", "got", "gum", "gun", "gut", "guy", "gym", "hat", "hay", "hem", "hen", "hey",
        "hid", "hip", "hit", "hop", "hot", "hug", "hum", "hut", "ice", "ill", "imp", "ink", "inn", "ion", "ire", "ivy",
        "jab", "jam", "jar", "jaw", "jay", "jet", "jig", "job", "jog", "jot", "joy", "jug", "jut", "ken", "key", "kid",
        "kin", "kit", "lab", "lad", "lag", "lap", "law", "lay", "led", "leg", "lid", "lie", "lip", "lit", "lob", "log",
        "lot", "low", "lug", "mad", "map", "mat", "may", "men", "met", "mix", "mob", "mop", "mud", "mug", "mut", "nab",
        "nag", "nap", "net", "nib", "nil", "nip", "nod", "nor", "not", "nub", "nut", "oak", "oar", "odd", "off", "oft",
        "oil", "orb", "ore", "owl", "own", "opt", "pad", "pal", "pan", "pat", "paw", "pay", "pea", "peg", "pen", "pet",
        "pie", "pig", "pin", "pit", "ply", "pod", "pop", "pot", "pro", "pry", "pub", "pun", "pup", "put", "qua", "rag",
        "ram", "ran", "rap", "rat", "raw", "ray", "red", "ref", "rib", "rid", "rig", "rim", "rip", "rob", "rod", "roe",
        "rot", "row", "rub", "rue", "rug", "run", "rut", "rye", "sac", "sad", "sag", "sap", "sat", "saw", "say", "sea",
        "see", "set", "sew", "shy", "sic", "sin", "sip", "sir", "sit", "six", "sky", "sly", "sob", "son", "sop", "sow",
        "spa", "spy", "sub", "sue", "sum", "sun", "sup", "tab", "tad", "tag", "tan", "tap", "tar", "tat", "tea", "tee",
        "ten", "thy", "tic", "tie", "tin", "tip", "toe", "tog", "ton", "too", "top", "toy", "try", "tub", "tug", "urn",
        "van", "vat", "vet", "vex", "via", "vie", "vow", "wad", "wag", "war", "wax", "web", "wed", "wee", "wet", "wig",
        "win", "wit", "woe", "won", "woo", "wow", "wrt", "yak", "yam", "yap", "yaw", "yay", "yep", "yes", "yet", "zap",
        "zip", "zoo"};
    vector<string> four_letter_words = {
        "able", "acid", "adds", "ages", "airy", "alms", "also", "area", "army", "arts", "asks", "atom",
        "aunt", "away", "bake", "ball", "band", "bark", "barn", "base", "bath", "bean", "beer", "bell",
        "bend", "best", "bill", "bind", "bird", "blow", "blue", "bold", "bone", "book", "boom", "bore",
        "born", "bowl", "bulk", "burn", "bush", "busk", "cake", "call", "calf", "camp", "card", "care",
        "cart", "cast", "cats", "chip", "clam", "clip", "clay", "coal", "coat", "code", "cool", "copy",
        "cord", "cork", "corn", "cost", "coup", "cure", "curl", "damn", "dare", "dark", "dash", "date",
        "deal", "dear", "deck", "dense", "done", "door", "dust", "earn", "ease", "easy", "edge", "else",
        "exit", "fact", "fade", "fail", "fair", "fake", "fame", "fare", "farm", "fast", "fear", "feed",
        "feel", "fell", "find", "fire", "fish", "fit", "flow", "food", "foot", "ford", "form", "fort",
        "free", "frog", "from", "gain", "game", "gave", "gear", "gift", "girl", "give", "glad", "goes",
        "gold", "good", "gram", "grey", "grip", "grow", "half", "hair", "hand", "hard", "have", "head",
        "heal", "hear", "heat", "help", "here", "hero", "hire", "hold", "hope", "hour", "idea", "idle",
        "inch", "iron", "item", "jail", "jump", "just", "keen", "kick", "kind", "king", "knee", "know",
        "lack", "lady", "lake", "land", "late", "lead", "leaf", "leak", "left", "lend", "less", "life",
        "lift", "line", "link", "list", "live", "load", "lock", "look", "lose", "love", "luck", "made",
        "mail", "main", "make", "male", "map", "mask", "mast", "meal", "mean", "meet", "mine", "more",
        "most", "move", "muse", "near", "neck", "need", "news", "nice", "nine", "nope", "note", "nude",
        "open", "oppo", "only", "ones", "oral", "over", "pace", "pack", "page", "palm", "park", "part",
        "pass", "path", "peak", "pear", "pend", "pens", "perk", "pick", "pill", "pine", "plan", "play",
        "plus", "poor", "port", "pose", "post", "pull", "pump", "pure", "race", "rack", "raft", "rain",
        "rare", "rate", "read", "real", "rear", "rest", "ride", "rift", "risk", "rose", "rude", "rule",
        "rush", "rust", "safe", "sale", "salt", "sand", "seam", "sear", "seat", "sell", "send", "sent",
        "side", "sign", "silk", "sill", "sink", "site", "skin", "slim", "slow", "smart", "snow", "soap",
        "sort", "sore", "star", "stay", "stop", "stun", "suck", "tail", "take", "tale", "tank", "task",
        "team", "tear", "tell", "that", "them", "then", "this", "time", "toes", "tone", "tool", "town",
        "true", "turn", "type", "unit", "used", "user", "vast", "verb", "very", "view", "vote", "wait",
        "walk", "wall", "want", "warm", "warn", "wash", "wave", "wear", "week", "weir", "well", "when",
        "where", "wide", "will", "wind", "wine", "wing", "wish", "with", "wolf", "wood", "word", "work",
        "worn", "year", "yell"};
    vector<string> common_five_letter_words = {
        "about", "above", "apple", "anger", "beach", "brave", "break", "bring", "brush", "build",
        "cabin", "candy", "catch", "cause", "clean", "climb", "close", "cloud", "count", "cover",
        "dance", "death", "dream", "drive", "drink", "earth", "enemy", "enter", "equal", "event",
        "faith", "fault", "field", "fight", "first", "floor", "force", "found", "frame", "fresh",
        "glass", "glory", "grace", "great", "green", "group", "guide", "happy", "heart", "heavy",
        "house", "human", "ideal", "image", "judge", "knife", "laugh", "learn", "light", "limit",
        "lunch", "magic", "match", "metal", "money", "music", "night", "noise", "north", "novel",
        "ocean", "offer", "order", "paint", "party", "peace", "phone", "plant", "point", "power",
        "quick", "quiet", "raise", "reach", "ready", "reply", "right", "river", "round", "rough",
        "scale", "score", "serve", "sharp", "shirt", "short", "skill", "sleep", "smart", "smile",
        "solid", "sound", "south", "space", "speak", "spend", "spice", "spoon", "stage", "stand",
        "start", "stone", "storm", "story", "style", "sugar", "sweet", "table", "teach", "thank",
        "thing", "throw", "tight", "today", "topic", "touch", "train", "trust", "truth", "uncle",
        "under", "union", "value", "visit", "voice", "voter", "waste", "watch", "water", "white",
        "whole", "woman", "world", "worry", "worth", "write", "wrong", "youth"};

public:
    void decode_cypher(ifstream &encoded, ofstream &decoded)
    {
        int no_rotate = 0;
        int a_rotate;
        int i_rotate;
        int neg_a = 0;
        int neg_i = 0;
        string encoded_text;
        getline(encoded, encoded_text);
        // converting all letters to small.
        vector<int> vec;
        for (int i = 0; i < encoded_text.length(); i++)
        {
            if (encoded_text[i] >= 65 && encoded_text[i] <= 90)
            {
                encoded_text[i] = (char)(encoded_text[i] + 32);
                vec.push_back(i);
            }
        };
        int f = 0;
        vector<string> words = split_into_words(encoded_text);
        // checking for single letters
        for (int i = 0; i < words.size(); i++)
        {
            if (words[i].size() == 1)
            {
                string ch = words[i];
                a_rotate = 97 - ch[0];
                i_rotate = 105 - ch[0];
                // if -ve -> right rotated
                // if +ve -> left rotated
                if (a_rotate < 0)
                {
                    a_rotate = 26 + a_rotate;
                    neg_a = 1;
                }
                if (i_rotate < 0)
                {
                    i_rotate = 26 + i_rotate;
                    neg_i = 1;
                }
                vector<string> test1(words.size());
                for (int j = 0; j < words.size(); j++)
                {
                    test1[j] = word_rotation(words[j], a_rotate);
                }
                vector<string> test2(words.size());
                for (int j = 0; j < words.size(); j++)
                {
                    test2[j] = word_rotation(words[j], i_rotate);
                }
                // checking wrt a
                int flag = 0;
                for (int j = 0; j < test1.size(); j++)
                {
                    if (test1[j].length() == 2)
                    {
                        flag = letter_check(test1[j], two_letter_words);
                        break;
                    }
                    else if (test1[j].length() == 3)
                    {
                        flag = letter_check(test1[j], three_letter_words);
                        break;
                    }
                    else if (test1[j].length() == 4)
                    {
                        flag = letter_check(test1[j], four_letter_words);
                        break;
                    }
                    else if (test1[j].length() == 5)
                    {
                        flag = letter_check(test1[j], common_five_letter_words);
                        break;
                    }
                }
                if (flag == 1)
                {
                    no_rotate = a_rotate;
                    f = 1;
                    break;
                }
                // checking wrt to i
                else
                {
                    for (int j = 0; j < test2.size(); j++)
                    {
                        if (test2[j].length() == 2)
                        {
                            flag = letter_check(test2[j], two_letter_words);
                            break;
                        }
                        else if (test2[j].length() == 3)
                        {
                            flag = letter_check(test2[j], three_letter_words);
                            break;
                        }
                        else if (test2[j].length() == 4)
                        {
                            flag = letter_check(test2[j], four_letter_words);
                            break;
                        }
                        else if (test2[j].length() == 5)
                        {
                            flag = letter_check(test2[j], common_five_letter_words);
                            break;
                        }
                    }
                }
                if (flag == 1)
                {
                    no_rotate = i_rotate;
                    f = 1;
                    break;
                }
            }
        }
        if (f != 1)
        {
            int best_score = -1;
            int best_rotation = 0;
            for (int r = 1; r <= 26; r++)
            {
                int score = 0;
                for (int j = 0; j < words.size(); j++)
                {
                    string rotated_word = word_rotation(words[j], r);
                    if (rotated_word.length() == 2 && letter_check(rotated_word, two_letter_words))
                    {
                        score++;
                    }
                    else if (rotated_word.length() == 3 && letter_check(rotated_word, three_letter_words))
                    {
                        score++;
                    }
                    else if (rotated_word.length() == 4 && letter_check(rotated_word, four_letter_words))
                    {
                        score++;
                    }
                    else if (rotated_word.length() == 5 && letter_check(rotated_word, common_five_letter_words))
                    {
                        score++;
                    }
                }
                if (score > best_score)
                {
                    best_score = score;
                    best_rotation = r;
                }
            }
            no_rotate = best_rotation;
        }
        // final rotated string
        string rotated;
        rotated = decoded_text(encoded_text, no_rotate);
        // converting into original format
        for (int z = 0; z < vec.size(); z++)
        {
            rotated[vec[z]] = (char)(rotated[vec[z]] - 32);
        }
        // writing into the file
        decoded << rotated;
        cout << "DECODED AND SAVED SUCCESSFULLY!" << endl;
        cout << "Do you want to see the decoded text? yes or no" << endl;
        string ch2;
        cin >> ch2;
        if (ch2 == "yes" || ch2 == "Yes" || ch2 == "YES")
        {
            cout << "ROTATION: " << no_rotate << "(in left direction) or " << abs(26 - no_rotate) << "( in right direction)" << endl;
            cout << rotated << endl;
        }
    };
    void encode_cypher(string data, int n, ofstream &encoded)
    {
        for (int i = 0; i < data.length(); i++)
        {
            if ((data[i] >= 65 && data[i] <= 90) || (data[i] >= 97 && data[i] <= 122))
            {
                int c = data[i] + n;
                if (c > 90 && (data[i] >= 65 && data[i] <= 90))
                {
                    c = 65 + c - 90 - 1;
                }
                else if (c > 122 && (data[i] >= 97 && data[i] <= 122))
                {
                    c = 97 + c - 122 - 1;
                }
                encoded << (char)(c);
            }
            else
            {
                encoded << data[i];
            }
        }
        cout << "ENCODED AND SAVED SUCCESSFULLY!";
    };
};

void displayMenu()
{
    cout << endl;
    cout << "  /$$$$$$                                  /$$           /$$$$$$           /$$$$$$                                  " << endl;
    cout << " /$$__  $$                                | $$          /$$__  $$         /$$__  $$                                 " << endl;
    cout << "| $$  \\__/  /$$$$$$  /$$   /$$  /$$$$$$  /$$$$$$       | $$  \\ $$        | $$  \\__/  /$$$$$$  /$$$$$$  /$$$$$$/$$$$ " << endl;
    cout << "| $$       /$$__  $$| $$  | $$ /$$__  $$|_  $$_//$$$$$$| $$  | $$ /$$$$$$| $$ /$$$$ /$$__  $$|____  $$| $$_  $$_  $$" << endl;
    cout << "| $$      | $$  \\__/| $$  | $$| $$  \\ $$  | $$ |______/| $$  | $$|______/| $$|_  $$| $$  \\__/ /$$$$$$$| $$ \\ $$ \\ $$" << endl;
    cout << "| $$    $$| $$      | $$  | $$| $$  | $$  | $$ /$$     | $$  | $$        | $$  \\ $$| $$      /$$__  $$| $$ | $$ | $$" << endl;
    cout << "|  $$$$$$/| $$      |  $$$$$$$| $$$$$$$/  |  $$$$/     |  $$$$$$/        |  $$$$$$/| $$     |  $$$$$$$| $$ | $$ | $$" << endl;
    cout << "\\______/ |__/       \\____  $$| $$____/    \\___/        \\______/          \\______/ |__/     \\_______/|__/ |__/ |__/" << endl;
    cout << "                    /$$  | $$| $$                                                                                  " << endl;
    cout << "                   |  $$$$$$/| $$                                                                                  " << endl;
    cout << "                    \\______/ |__/                                                                                  " << endl;
    cout << "=====================================================================================" << endl;
    cout << "                               CRYPT-O-GRAM MENU                                   " << endl;
    cout << "=====================================================================================" << endl;
    cout << " 1. Morse Code Encryption/Decryption      (... --- ...)" << endl;
    cout << " 2. Caesar Cipher Encryption/Decryption   (Shift your secrets!)" << endl;
    cout << " 3. Exit                                                             "<<endl;
    cout << "=====================================================================================" << endl;
    cout << " Enter your choice (1-3): ";
}
void performMorseCode()
{
    cout << "\n  You chose Morse Code!" << endl;
    cout << "$$\\      $$\\  $$$$$$\\  $$$$$$$\\   $$$$$$\\  $$$$$$$$\\        $$$$$$\\   $$$$$$\\  $$$$$$$\\  $$$$$$$$\\ " << endl;
    cout << "$$$\\    $$$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|      $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|" << endl;
    cout << "$$$$\\  $$$$ |$$ /  $$ |$$ |  $$ |$$ /  \\__|$$ |            $$ /  \\__|$$ /  $$ |$$ |  $$ |$$ |      " << endl;
    cout << "$$\\$$\\$$ $$ |$$ |  $$ |$$$$$$$  |\\$$$$$$\\  $$$$$\\          $$ |      $$ |  $$ |$$ |  $$ |$$$$$\\    " << endl;
    cout << "$$ \\$$$  $$ |$$ |  $$ |$$  __$$<  \\____$$\\ $$  __|         $$ |      $$ |  $$ |$$ |  $$ |$$  __|   " << endl;
    cout << "$$ |\\$  /$$ |$$ |  $$ |$$ |  $$ |$$\\   $$ |$$ |            $$ |  $$\\ $$ |  $$ |$$ |  $$ |$$ |      " << endl;
    cout << "$$ | \\_/ $$ | $$$$$$  |$$ |  $$ |\\$$$$$$  |$$$$$$$$\\       \\$$$$$$  | $$$$$   |$$$$$$$  |$$$$$$$$\\" << endl;
    cout << "\\__|     \\__| \\______/ \\__|  \\__| \\______/ \\________|       \\______/  \\______/ \\_______/ \\________|" << endl;
    cout << endl
         << "MENU:" << endl;
    cout << "1: TO DECODE AN MORSE ENCRYPTED FILE." << endl;
    cout << "2: TO ENCODE DATA INTO MORSE CODE." << endl;
    cout << "3. TO ENCODE DATA FROM A TEXT FILE INTO MORSE CODE." << endl;
    cout << endl
         << "Enter choice:" << endl;
    int ch;
    cin >> ch;
    cin.ignore();
    if (ch == 1)
    {
        morsecode obj1;
        cout << "Enter MORSE ENCRYPTED FILE in .txt format:" << endl;
        string e_filename;
        getline(cin, e_filename);
        ifstream encoded(e_filename, ios::in);
        if (!encoded)
        {
            cout << "Error opening file for reading!" << endl;
            cout << "Enter again!" << endl;
            getline(cin, e_filename);
            ifstream encoded(e_filename, ios::in);
            if (!encoded)
            {
                cout << "Error opening file for reading!" << endl;
                cout << "Going back to morse code menu!" << endl;
                performMorseCode();
            }
        }
        cout << "Enter TEXT FILE name in .txt format to store the decoded text:" << endl;
        string d_filename;
        getline(cin, d_filename);
        ofstream data(d_filename, ios::out | ios::trunc);
        if (!data)
        {
            cout << "Error opening file for writing!" << endl;
        }
        string otp;
        otp = obj1.morse_decoder(encoded, data);
        cout << endl
             << "Do you want to see the decoded text? yes or no" << endl;
        string ch2;
        cin >> ch2;
        if (ch2 == "yes" || ch2 == "Yes" || ch2 == "YES")
        {
            cout << otp << endl;
        }
        data.close();
        encoded.close();
    }
    else if (ch == 2)
    {
        morsecode obj2;
        cout << "ENTER DATA TO ENCRYPT:" << endl;
        string content;
        getline(cin, content);
        cout << "Enter MORSE ENCRYPTION FILE name in .txt format to store the encryption:" << endl;
        string e_filename;
        getline(cin, e_filename);
        ofstream encoded2(e_filename, ios::out | ios::trunc);
        if (!encoded2)
        {
            cout << "Error opening file for writing!" << endl;
        }
        obj2.morse_encoder_input(content, encoded2);
        encoded2.close();
    }
    else if (ch == 3)
    {
        morsecode obj3;
        cout << "Enter TEXT FILE name in .txt format to get the data: " << endl;
        string d_filename;
        getline(cin, d_filename);
        ifstream data2(d_filename, ios::in);
        if (!data2)
        {
            cout << "Error opening file for reading!" << endl;
            cout << "Enter again!" << endl;
            getline(cin, d_filename);
            ifstream data2(d_filename, ios::in);
            if (!data2)
            {
                cout << "Error opening file for reading!" << endl;
                cout << "Going back to morse code menu!" << endl;
                performMorseCode();
            }
        }
        cout << "Enter MORSE ENCRYPTION FILE name in .txt format to store the encryption:" << endl;
        string e_filename;
        getline(cin, e_filename);
        ofstream encoded3(e_filename, ios::out | ios::trunc);
        if (!encoded3)
        {
            cout << "Error opening file for writing!" << endl;
        }
        obj3.morse_encoder(data2, encoded3);
        encoded3.close();
        data2.close();
    }
    else
    {
        cout << "INVALID CHOICE!" << endl;
        performMorseCode();
    }
}
void performCaesarCipher()
{
    cout << "\n  You chose Caesar Cipher!" << endl;
    cout << " $$$$$$\\   $$$$$$\\  $$$$$$$$\\  $$$$$$\\  $$$$$$$$\\ $$$$$$$\\         $$$$$$\\ $$\\     $$\\ $$$$$$$\\  $$\\   $$\\ $$$$$$$$\\ $$$$$$$\\  " << endl;
    cout << "$$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\ $$  _____|$$  __$$\\       $$  __$$\\\\$$\\   $$  |$$  __$$\\ $$ |  $$ |$$  _____|$$  __$$\\ " << endl;
    cout << "$$ /  \\__|$$ /  $$ |$$ |      $$ /  \\__|$$ |      $$ |  $$ |      $$ /  \\__|\\$$\\ $$  / $$ |  $$ |$$ |  $$ |$$ |      $$ |  $$ |" << endl;
    cout << "$$ |      $$$$$$$$ |$$$$$\\    \\$$$$$$\\  $$$$$\\    $$$$$$$  |      $$ |       \\$$$$  /  $$$$$$$  |$$$$$$$$ |$$$$$\\    $$$$$$$  |" << endl;
    cout << "$$ |      $$  __$$ |$$  __|    \\____$$\\ $$  __|   $$  __$$<       $$ |        \\$$  /   $$  ____/ $$  __$$ |$$  __|   $$  __$$< " << endl;
    cout << "$$ |  $$\\ $$ |  $$ |$$ |      $$\\   $$ |$$ |      $$ |  $$ |      $$ |  $$\\    $$ |    $$ |      $$ |  $$ |$$ |      $$ |  $$ |" << endl;
    cout << "\\$$$$$$  |$$ |  $$ |$$$$$$$$\\ \\$$$$$$  |$$$$$$$$\\ $$ |  $$ |      \\$$$$$$  |   $$ |    $$ |      $$ |  $$ |$$$$$$$$\\ $$ |  $$ |" << endl;
    cout << " \\______/ \\__|  \\__|\\________| \\______/ \\________|\\__|  \\__|       \\______/    \\__|    \\__|      \\__|  \\__|\\________|\\__|  \\__|" << endl;
    cout << endl
         << "MENU:" << endl;
    cout << "1: TO DECODE AN CAESER CYPHER ENCRYPTED FILE." << endl;
    cout << "2: TO ENCODE DATA INTO CAESER CYPHER ENCRYPTION." << endl;
    cout << "3. TO ENCODE DATA FROM A TEXT FILE INTO CAESER CYPHER." << endl;
    cout << endl
         << "Enter choice:" << endl;
    int gbg;
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice == 1)
    {
        caeser_cypher obj1;
        cout << "Enter CAESER CYPHER ENCRYPTED FILE in .txt format:" << endl;
        string e_filename;
        getline(cin, e_filename);
        ifstream encoded(e_filename, ios::in);
        if (!encoded)
        {
            cout << "Error opening file for reading!" << endl;
            cout << "Enter again!" << endl;
            getline(cin, e_filename);
            ifstream encoded(e_filename, ios::in);
            if (!encoded)
            {
                cout << "Error opening file for reading!" << endl;
                cout << "Going back to caeser cypher menu!" << endl;
                performCaesarCipher();
            }
        }
        cout << "Enter TEXT FILE name in .txt format to store the decoded text:" << endl;
        string d_filename;
        getline(cin, d_filename);
        ofstream data(d_filename, ios::out | ios::trunc);
        if (!data)
        {
            cout << "Error opening file for writing!" << endl;
        }
        string otp;
        obj1.decode_cypher(encoded, data);
        data.close();
        encoded.close();
    }
    else if (choice == 2)
    {
        caeser_cypher obj2;
        cout << "ENTER DATA TO ENCRYPT:" << endl;
        string content;
        getline(cin, content);
        cout << "Enter CAESER CYPHER ENCRYPTION FILE name in .txt format to store the encryption:" << endl;
        string e_filename;
        getline(cin, e_filename);
        ofstream encoded2(e_filename, ios::out | ios::trunc);
        if (!encoded2)
        {
            cout << "Error opening file for writing!" << endl;
        }
        int number_of_rotations = 0;
        cout << "Enter no. of rotations:" << endl;
        cin >> number_of_rotations;
        cin.ignore();
        if (abs(number_of_rotations) != number_of_rotations)
        {
            number_of_rotations = 26 - (abs(number_of_rotations) % 26);
        }
        else
        {
            number_of_rotations = number_of_rotations % 26;
        }
        obj2.encode_cypher(content, number_of_rotations, encoded2);
        encoded2.close();
    }
    else if (choice == 3)
    {
        caeser_cypher obj3;
        cout << "Enter TEXT FILE name in .txt format to get the data: " << endl;
        string d_filename;
        getline(cin, d_filename);
        ifstream data2(d_filename, ios::in);
        if (!data2)
        {
            cout << "Error opening file for reading!" << endl;
            cout << "Enter again!" << endl;
            getline(cin, d_filename);
            ifstream data2(d_filename, ios::in);
            if (!data2)
            {
                cout << "Error opening file for reading!" << endl;
                cout << "Going back to caeser cypher menu!" << endl;
                performCaesarCipher();
            }
        }
        cout << "Enter CAESER CYPHER ENCRYPTION FILE name in .txt format to store the encryption:" << endl;
        string e_filename;
        getline(cin, e_filename);
        ofstream encoded3(e_filename, ios::out | ios::trunc);
        if (!encoded3)
        {
            cout << "Error opening file for writing!" << endl;
        }
        int number_of_rotations = 0;
        cout << "Enter no. of rotations:" << endl;
        cin >> number_of_rotations;
        cin.ignore();
        if (abs(number_of_rotations) != number_of_rotations)
        {
            number_of_rotations = 26 - (abs(number_of_rotations) % 26);
        }
        else
        {
            number_of_rotations = number_of_rotations % 26;
        }
        string content2;
        getline(data2, content2);
        obj3.encode_cypher(content2, number_of_rotations, encoded3);
        encoded3.close();
    }
    else
    {
        cout << "INVALID CHOICE!";
        performCaesarCipher();
    }
}

int main()
{
    int choice;
    char again;
    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            performMorseCode();
            break;
        case 2:
            performCaesarCipher();
            break;
        case 3:
            cout << "THANKYOU!" << endl;
            cout << "exiting.";
            return 0;
            break;
        default:
            cout << "\n  Invalid choice. Please enter 1, 2, or 3." << endl;
        }
        cout << "\nDo you want to perform another operation? (Y/N): ";
        cin >> again;
        again = tolower(again);
        cout << "\n";
    } while (again == 'y');
    cout << "  Exiting Crypt-O-Gram. Stay encrypted!" << endl;
    return 0;
}