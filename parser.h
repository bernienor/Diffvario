/**
@author Bernt Hustad Hembre, bernienor@github

Simple textparser. Written for a minimalistic project on an Arduino. Where a lot of objects, and highlevel
mambo jambo would use up all the resources before I even got to do the fun stuff. Parsing GPS strings is
a simple task, and imho should be handled as one. 

A set of tests are added to facilitate test driven programming even on small and simple embedded systems.
**/



/**
@brief parses a char array into an array of char pointers. 
Useful for parsing GPS-strings or CVS files with minimal effort from the CPU.
None of the original data is copyied, separators are replaced by NULL. Remember to
use the result before the input string is overwritten (Ie if it's a serial receive
buffer or similar). 
@returns 0 if ok, 1 if maxbuf is reached before NULL termination, 2 if maxsub is reached.
**/
int parsecsv( char *s, char sep, char **subs, int maxsub, int maxbuf);

/**
@brief Tests for testing the parser. Also usefull as example of use.
As it is written for Arduino, the output is the serial port. 
**/
int test_parsecsv(void);

