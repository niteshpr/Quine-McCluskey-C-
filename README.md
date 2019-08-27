# Quine-McCluskey-CPP-
This is a Simple implementation of Quine-McCluskey method of boolean reduction using C++.

## This code is made By : Nitesh Kumar Prasad
### Roll : 18CS8053
### Section : CS-X
## Guided by : Mr. Bibhash Sen

In this Program First Number of variable is taken from user.
The code than asks for the MinTerms seperated by commas(,).

Our code First stores the binary form of the minterms in a map of int mapped to vector of strings.
Here basically the mappind is done from integer which contains number of Set bits, to the vector of 
string of binary form of minterm. This mapping is Displayed.

Then our Reduction process Starts.
Here first we check if two string of minterm are in grey form or not i.e, the hamington distance between 
the two is 1. If the condition is true, we replace the complementry term with "-" and push it to a new vector.
after checking for all complementry terms the other remaning minterms are pushed to this new vector and displayed.

This process continues untill even after reduction there is no change in out vector which is checked by our method
VectorEqual(vector<string>,vector<string>);.
  
 Oncompletion of reduction process, for alphabetical representation, variable are taken from getVars() nd depending 
 on the final value of minterm, it is stored and displayed.
