#ifndef __MLEX_H
#define __MLEX_H

#include<cstdio>
#include"lex.h"


#define T_INT 257
#define T_FLO 258
#define T_IDE 259


#define MAX_CHARS 5000

class mlex_t : public lex_t
{
	public:
		mlex_t() {in=NULL;};
		mlex_t(const mlex_t &s) {in=s.in;cchar=s.cchar;l=s.l;c=s.c;};
		void setInput(input_t *i) {in=i;getNextChar();l=c=1;};
		virtual int nextToken();
		virtual char *text() {return yytext;};

		virtual int line() {return l;};
		virtual int col() {return c;};
		virtual input_t * getInput() {return in;};
		virtual ~mlex_t() {};

	protected:
		bool match_blank(int c);
		bool match_sop(int c);
		bool match_int(int c);
		bool match_id_first(int c);
		bool match_id_rest(int c);
		bool match_comment(int c);
		bool match_end_comment(int c);
		bool match_float(char *s);
		void getNextChar() 
				{ if(cchar=='\n') {c=1;l++;} else c++;cchar=in->getNextChar();};
		int l,c;
		input_t *in;
		int cchar;
		char yytext[MAX_CHARS+1];
};

#endif
