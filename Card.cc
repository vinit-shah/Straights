#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

Card::Card( Card::Rank r, Card::Suit s ) : suit_{s}, rank_{r} {}

Card::Suit Card::suit() const { return suit_; }
Card::Rank Card::rank() const { return rank_; }

bool Card::operator==( const Card & c ) const {
	return ( suit().suit() == c.suit().suit() && rank().rank() == c.rank().rank() );
}

ostream & operator<<( ostream & out, const Card::Suit & s ) {
	static string suits = "CDHS";
	out << suits[ s.suit() ];
	return out;
} // operator<<

ostream & operator<<( ostream & out, const Card::Rank & r ) {
	static string ranks = "A23456789TJQK";
	out << ranks[ r.rank() ];
	return out;
} // operator<<

ostream & operator<<( ostream & out, const Card & c ) {
	out << c.rank() << c.suit();	
	return out;
} // operator<<

istream & operator>>( istream & in, Card::Rank & r ) {
	static string ranks = "A23456789TJQK";
	char c;
	in >> c;
	assert ( !in.fail() );

	//Read in the rank, make sure it's valid
    size_t index = ranks.find( c );
	assert ( index != string::npos );
	r = Card::Rank( index );
	return in;
} // operator>>

istream & operator>>( istream & in, Card::Suit & s ) {
	static string suits = "CDHS";
	char c;
	in >> c;
	assert ( !in.fail() );

	// Read in the suit, make sure it's valid
    size_t index = suits.find( c );
	assert ( index != string::npos );
	s = Card::Suit( index );
	return in;
}  // operator>>

istream & operator>>( istream & in, Card & c ) {	
	Card::Rank r{0};
	Card::Suit s{0};
	in >> r >> s;
	assert ( !in.fail() );
	
	c = Card( r, s );
	return in;
} // operator>>

Card::Suit::Suit( int s ) {
	if ( s < 0 || s >= Card::Suit::MAX_SUIT ) throw "Invalid suit";
	suit_ = s;
}

int Card::Suit::suit() const { return suit_; }

Card::Rank::Rank( int r ) {
	if ( r < 0 || r >= Card::Rank::MAX_RANK ) throw "Invalid rank";
	rank_ = r;	
}

int Card::Rank::rank() const { return rank_; }
