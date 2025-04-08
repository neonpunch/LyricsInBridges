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
	Bridges bridges(1001, "neonpunch", "1574857604435");

	bridges.setTitle("Lyrics in Bridges");
	bridges.setDescription("Artist: AJR, Song: God is Really Real");

	// THE TODO BELOW IS KENWAR'S RESPONSIBILITY

	/* TODO:
	 * Grab a song from the bridges server and get its lyrics
	 * use the data source method - getSong()
	 *
	 * Upon doing so, call the lyrics tokenize function, passing the lyrics
	 * to remove any punctuation or tags in the lyrics, returning
	 * an array of single cleaned up terms
	 *
	 * After that, create a new Bridges ColorGrid object, passing
	 * in the word count of the lyrics in as the dimensions.
	 * You may also specify a default color if you wish, if not
	 * it defaults to white
	 */
	// ANSWER:-KD
	DataSource ds;
	Song s = ds.getSong("God is Really Real", "AJR");

	auto words = s.getLyrics();

	vector<string> wordArray = lyrics_tokenize(words);

	ColorGrid grid(wordArray.size(), wordArray.size());

	// input your own RGBA values if you wish
	Color matchColor (0, 0, 0, 255);

	//THE TODO BELOW IS MILO'S RESPONSIBILITY

	/* TODO:
	 * Iterate over the lyrics, checking to see if there are matching terms
	 * if so, set that coordinate to a color representing a match.
	 *
	 * Each row and colum will represent an individual word in the lyrics,
	 * meaning your main diagonal of your matrix should be completely filled in
	 * as that represents each word compared against itself.
	 */

	for (size_t i = 0; i < wordArray.size(); ++i) {
		for (size_t j = 0; j < wordArray.size(); ++j) {
			if (wordArray.at(i) == wordArray.at(j)) {
				grid.set(i, j, matchColor);
				grid.set(j, i, matchColor);
			}
		}
	}
	// replace YourGridHere with your ColorGrid object and uncomment the line below
	bridges.setDataStructure(&grid);
	// visualize the grid
	bridges.visualize();

	return 0;
}
