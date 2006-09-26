#include<cstdio>
#include<ostream>
#include "mlex.h"
#define ISLET(c) ((((c)>='a') && ((c)<='z')) || (((c)>='A') && ((c)<='Z'))) 
#define ISDIG(c) ((((c)>='0') && ((c)<='9')) || ((c) == '.'))

static char sops[]={
				'(',
				')',
				'=',
				'+',
				'-',
				'*',
				'/',
        '%',
				'^',
				';',
        ',',
        ':',
				0 };

bool mlex_t::match_blank(int c)
{
	if(c==' ') return true;
	if(c=='\t') return true;
	if(c=='\n') return true;
	if(c=='\r') return true;
	return false;
}

bool mlex_t::match_sop(int c)
{
	for(int i=0;sops[i]!=0;++i)
		if(sops[i]==c) return true;
	return false;
}

bool mlex_t::match_id_first(int c)
{
	if(ISLET(c)) return true;
  return false;
}

bool mlex_t::match_id_rest(int c)
{
	if(ISLET(c)) return true;
	if(ISDIG(c)) return true;
	if(c=='_') return true;
	return false;
}

bool mlex_t::match_int(int c)
{
	if(ISDIG(c)) return true;
	return false;
}

bool mlex_t::match_comment(int c)
{
	return (c=='#');
}

bool mlex_t::match_end_comment(int c)
{
	return (c=='\n');
}


int mlex_t::nextToken()
{
	if(in==NULL) return T_EOF;

	while(match_comment(cchar) || match_blank(cchar))
	{
		while(match_blank(cchar))
			getNextChar();
		if(match_comment(cchar))
		{
			getNextChar();
			while(!match_end_comment(cchar))
				getNextChar();
			getNextChar();
		}
	}
	
	if(match_sop(cchar))
	{
		yytext[0]=cchar;
		yytext[1]=0;
		getNextChar();
		return yytext[0];
	}
	if(match_int(cchar))
	{
    bool real = false;
		yytext[0]=cchar;
    if( cchar == '.' )
      real = true;
    getNextChar();
		int i;
		for(i=1;match_int(cchar) && (i<MAX_CHARS);++i,getNextChar()){
      if( cchar == '.' )
        real = true;
			yytext[i]=cchar;
    }
		yytext[i]=0;
    if( real )
      return T_FLO;
    else
      return T_INT;
	}
	if(match_id_first(cchar))
	{
		yytext[0]=cchar;
		getNextChar();
		int i;
		for(i=1;match_id_rest(cchar) && (i<MAX_CHARS);++i,getNextChar())
			yytext[i]=cchar;
		yytext[i]=0;
		return T_IDE;
	}
	if(cchar==EOF)
	{
		yytext[0]=0;
		return T_EOF;
	}
	yytext[0]=cchar;
	yytext[1]=0;
	getNextChar();
	return 0;
}

