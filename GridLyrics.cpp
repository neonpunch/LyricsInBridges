#include "Bridges.h"
#include "DataSource.h"
#include "Array.h"
#include "SLelement.h"
#include "ColorGrid.h"
#include <sstream>

using namespace bridges;

//Tokenize a string into individual word, removing punctuation at the
//end of words
std::vector<std::string> lyrics_tokenize(const std::string& lyrics) {
  std::vector<std::string> ret;

  std::stringstream ss (lyrics);

  std::string line;

  //For each line
  while (getline(ss, line, '\n')) {
    //Skip all like starting with [
    if (line[0] == '[')
      continue;

    std::stringstream ssline (line);
    //For all words
    while (ssline) {
      std::string word;
      ssline >> word;
      if (ssline) {

        //remove punctuation at the end of word
        while (word.length() > 0
               && std::ispunct(word[word.length() - 1])) {
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
  Bridges bridges(107, "USER_NAME", "API_KEY");

  bridges.setTitle("Song Grid");
  bridges.setDescription("Artist: Taylor Swift, Song: Delicate");

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


  // input your own RGBA values if you wish
  Color matchColor (0, 0, 0, 255);

  /* TODO:
   * Iterate over the lyrics, checking to see if there are matching terms
   * if so, set that coordinate to a color representing a match.
   *
   * Each row and colum will represent an individual word in the lyrics,
   * meaning your main diagonal of your matrix should be completely filled in
   * as that represents each word compared against itself.
   */

  // replace YourGridHere with your ColorGrid object and uncomment the line below
  //bridges::setDataStructure(&YourGridHere);
  // visualize the grid
  bridges.visualize();

  return 0;
}
