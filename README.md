
**LyricsInBridges**

This program will visualize song lyrics into a piece of artwork via 
coupling similar words into clusters and painting them to the screen
in specific patterns.

### /----------------------/


**THE BELOW PORTION IN LYRICS.CC IS KENWAR'S RESPONSIBILITY**

Grab a song from the bridges server and get its lyrics
use the data source method - getSong()

Upon doing so, call the lyrics tokenize function, passing the lyrics
to remove any punctuation or tags in the lyrics, returning
an array of single cleaned up terms
   
After that, create a new Bridges ColorGrid object, passing
in the word count of the lyrics in as the dimensions.
You may also specify a default color if you wish, if not
it defaults to white.


**THE BELOW PORTION IN LYRICS.CC IS MILO'S RESPONSIBILITY**

Iterate over the lyrics, checking to see if there are matching terms
if so, set that coordinate to a color representing a match.

Each row and colum will represent an individual word in the lyrics,
meaning your main diagonal of your matrix should be completely filled in
as that represents each word compared against itself.


### /----------------------/
