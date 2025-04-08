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
	Bridges bridges(1, "neonpunch", "1574857604435");

	bridges.setTitle("Lyrics in Bridges");
	bridges.setDescription("Artist: Jeff Rosenstock, Song: Festival Song");

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
	Song s = ds.getSong("Festival Song", "Jeff Rosenstock");
	cout << "Song Title: " << s.getSongTitle() << endl;
	cout << "Artist: " << s.getArtist() << endl;

	s.setLyrics("It feels completely ridiculous That I'm a willing participant Gazing at the purples and pinks In the shadow of a bank-sponsored skyline Unite against the establishment! (While drones transmit the images To a server farm in the valley For a culture that'll eat its own insides) Oh, they wouldn't be your friend if you weren't worth something. They wouldn't be your friend if you weren't worth something They wouldn't be your friend if it wasn't worth it If you didn't have something they could take... ... a long look at the billboards That swallow the air so you can't ignore 'em And glamorize department store crust-punk-chic 'Cause Satan's trending up and it's fashion week But this is not a movement It's just careful entertainment For an easy demographic In our sweatshop denim jackets And we'll wonder what just happened When the world becomes Manhattan Where the banks steal the apartments Just to render them abandoned Oh, they wouldn't be your friend if you weren't worth something They wouldn't be your friend if you weren't worth something They wouldn't be your friend if it wasn't worth it If you didn't have something they could take We're not stupid people, but this financial depression Has got everyone believing all that we can do is nothing 'Cause we organize through avenues they lace with advertisements So the ones we try to rage against are still lining their pockets Oh, they wouldn't be your friend if you weren't worth something They wouldn't be your friend if you weren't worth something They wouldn't be your friend if it wasn't worth it If you didn't have something they could take");

	//cout << "Lyrics Retrieved: " << s.getLyrics() << endl;

	auto words = s.getLyrics();
	
	//cout << "Lyrics: " << words << endl;
	vector<string> wordArray = lyrics_tokenize(words);
	cout << "Total words: " << wordArray.size() << endl;

	ColorGrid grid(wordArray.size(), wordArray.size(), Color(255, 105, 200));

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

	for (size_t i = 0; i < wordArray.size(); i++) {
		for (size_t j = i + 1; j < wordArray.size(); j++) {
			if (wordArray.at(i) != wordArray.at(j)) {
				grid.set(j, i, Color(0, 0, 0));
				grid.set(i, j, Color(0, 0, 0));
			}
		}
	}
	// replace YourGridHere with your ColorGrid object and uncomment the line below
	bridges.setDataStructure(&grid);
	// visualize the grid
	bridges.visualize();

	return 0;
}
