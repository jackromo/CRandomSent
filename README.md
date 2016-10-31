#C Sentence Generator

This program generates random sentences.

eg. The bald eagle attacked the big mean businessman.


#Semantics

Sentences use the following semantics:


Sentence ::= NounPhrase TVerbPhrase ;

NounPhrase ::= "The" Adverb\* Noun ;

Noun ::= "eagle" | "businessman" | "cat" | "dog" | "duck" ;

Adverb ::= "lazy" | "stray" | "mean" | "big" | "bald" ;

TVerbPhrase ::= Verb "the" Nounphrase Adj ;

Verb ::= "fought" | "attacked" | "drank" | "ate" ;

Adj ::= "majestically" | "quickly" | "effortlessly" | "viciously" ;

