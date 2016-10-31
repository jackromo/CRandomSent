#C Sentence Generator

This program generates random sentences.

eg. The bald eagle attacked the big mean businessman.


#Semantics

Sentences use the following semantics:


Sentence ::= NounPhrase TVerbPhrase ;

NounPhrase ::= The Adverb\* Noun ;

The ::= "the" ;

Noun ::= "eagle" | "businessman" | "cat" | "dog" ;

Adverb ::= "quick" | "small" | "angry" | "strong" | "bald" | "mean" ;

TVerbPhrase ::= Verb The Nounphrase Adj ;

Verb ::= "fought" | "attacked" | "annoyed" | "ate" ;

Adj ::= "strongly" | "easily" | "angrily" ;

