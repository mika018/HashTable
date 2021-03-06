# HashTable

This reposirtory includes a single module writen in C which compares two ways of storing and
retrieving data records. A program stores data records in a linked list and a hash table
with direct chaining as collision resolution strategy. To load a file you can send it as
an argument into the main(), ie:

./hash file.txt

Once the program has read the input text file, you can use the interface in order to
prompt queries. A sample output is shown below.

## Sample Output

it052593:Hash$ gcc -std=c99 -O3 -Wall -Werror hash.c -o hash 
it052593:Hash$ ./hash file.txt  

Reading into a list took 1.76s for 85888 words  
Reading into a table took 0.01s for 85888 words  

Hash table details:  
Size in bites: 8072.  
Total nuber of indexes: 1009.  
Empty indexes: 39.  
Longest index: 30 nodes.  
Percentage of hash table used: 96.13%  

Enter word for retreival:looking  
'looking' occurs 24 times  
Retreival from the list took 9305 comparisons.  
Retreival from the hash table took 13 comparisons.  

Another query? [y/n] y  
Enter word for retreival:me  
'me' occurs 138 times  
Retreival from the list took 8808 comparisons.  
Retreival from the hash table took 6 comparisons.  

Another query? [y/n] y  
Enter word for retreival:epiphany  
Word not found.  

Another query? [y/n] y  
Enter word for retreival:seraphim  
'seraphim' occurs 5 times  
Retreival from the list took 4472 comparisons.  
Retreival from the hash table took 7 comparisons.  

Another query? [y/n] y  
Enter word for retreival:ardent  
'ardent' occurs 12 times  
Retreival from the list took 861 comparisons.  
Retreival from the hash table took 3 comparisons.  

Another query? [y/n] y  
Enter word for retreival:windless  
'windless' occurs 2 times  
Retreival from the list took 873 comparisons.  
Retreival from the hash table took 1 comparisons.  

Another query? [y/n] y  
Enter word for retreival:esthetic  
'esthetic' occurs 30 times  
Retreival from the list took 2016 comparisons.  
Retreival from the hash table took 3 comparisons.  

Another query? [y/n] y  
Enter word for retreival:computer  
Word not found.  

Another query? [y/n] n  
