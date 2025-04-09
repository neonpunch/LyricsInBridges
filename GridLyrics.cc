#include "Bridges.h"
#include "DataSource.h"
#include "Array.h"
#include "SLelement.h"
#include "ColorGrid.h"
#include <sstream>
using namespace std;
using namespace bridges;

//Tokenize a string into individual word, removing punctuation at the
//end of words
vector<string> lyrics_tokenize(const string& lyrics) {
	vector<string> ret;

	stringstream ss (lyrics);

	string line;

	//For each line
	while (getline(ss, line, '\n')) {
		//Skip all like starting with [
		if (line[0] == '[')
			continue;

		stringstream ssline (line);
		//For all words
		while (ssline) {
			string word;
			ssline >> word;
			if (ssline) {

				//remove punctuation at the end of word
				while (word.length() > 0
						&& ispunct(word[word.length() - 1])) {
					word.pop_back();
				}
				ret.push_back(word);
			}
		}
	}

	return ret;
}

int main() {

	//create the Bridges object, set credentials
	Bridges bridges(3, "neonpunch", "1574857604435");

	bridges.setTitle("Lyrics in Bridges");
	bridges.setDescription("Artist: Lil Nas X, Song: VOID");
	
	DataSource ds;
	Song s = ds.getSong("VOID", "Lil Nas X");
	cout << "Song Title: " << s.getSongTitle() << endl;
	cout << "Artist: " << s.getArtist() << endl;

	s.setLyrics("Hello, friend from the road I wanted to write a note To let you know that, all in all, it ain't all what it seems I feel like I've hit a low One I've never hit before Lately, I been feelin' small as the salt in the sea Oh, it's so much to do in so little of time I feel like I fell a little behind Hold up, hold up, hold up It seems so out of reach to place upon the bay Whoever thought I'd get there anyway? Hold up, hold up, hold up I find it hard to get Way too hard to live Tell me what you know Now before I go Oh Blue, I wrote for you To say I'm gonna run away from home Oh, Blue, I love you too But today I'm gonna run away from home Oh, I weep through the night Can't find a love who loves me the same Or as much as you do Hold up, hold up, hold up Oh, I reach out my hand, open the door See, I'm more than what everyone tells me Hold up, hold up, hold up See, I'm gettin' tired of the way I been livin' I'd rather die than to live with these feelings Stuck in this world where there's so much to prove Every win gives you more room to lose It's too many ups and downs on the ride I spent inordinate 'mounts of time Trapped in the lonely, loner life Lookin' for lover on the night I find it hard to get Way too hard to live Tell me what you know Now before I go Oh Blue, I wrote for you To say I'm gonna run away from home Oh, Blue, I love you too But today I'm gonna run away from home Away from home Oh, oh Today, I'm gonna run away Today, I'm gonna run away");

	//cout << "Lyrics Retrieved: " << s.getLyrics() << endl;
	auto words = s.getLyrics();
	//cout << "Lyrics: " << words << endl;
	vector<string> wordArray = lyrics_tokenize(words);
	cout << "Total words: " << wordArray.size() << endl;

	ColorGrid grid(wordArray.size(), wordArray.size(), Color(0, 0, 0));
	// input your own RGBA values if you wish
	Color matchColor (0, 0, 0, 255);
	
	for (size_t i = 0; i < wordArray.size(); i++) {
		for (size_t j = i + 1; j < wordArray.size(); j++) {
			if (wordArray.at(i) != wordArray.at(j)) {
				grid.set(j, i, Color(255, 90, 160));
				grid.set(i, j, Color(255, 90, 160));
			}
		}
	}
	// replace YourGridHere with your ColorGrid object and uncomment the line below
	bridges.setDataStructure(&grid);
	// visualize the grid
	bridges.visualize();

	return 0;
}
