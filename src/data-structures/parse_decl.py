#!/usr/bin/python
import sys, os, re, logging
import pdb
from re import VERBOSE
import token
from tokenize import generate_tokens
#from funcparserlib.lexer import make_tokenizer, Token, LexerError
from funcparserlib.lexer import Token
from funcparserlib.parser import some, a, maybe, many, finished, skip, forward_decl, NoParseError
from StringIO import StringIO
from pprint import pformat

def d(s):
    print s.__doc__

def bp():
    pdb.set_trace()

f1 = "int foobar(void);"
f2 = "int foobar(int a);"
f3 = "int* foobar(int* b);"

def tokenize(s):
    'str -> [Token]'
    return list(Token(*t[0:4]) 
                for t in generate_tokens(StringIO(s).readline)
                if t[0] not in [token.NEWLINE])

def typeid(t):
    'Sequence[Token] -> Token'
    tokvalue = lambda t: some(lambda x: x.value == t)
    void     = tokvalue("void")
    inttype  = tokvalue("int")
    chartype = tokvalue("char") 
    unsigned = tokvalue("unsigned")
    def make_unsigned(x):
        if x[1].value == "int":
            return Token(1, 'unsigned int')
        else:
            return Token(1, 'unsigned char')

    tokstart = lambda t: some(lambda x: x.value.startswith(t))

    def ptr(tokens):
        a = [ t.value for t in tokens ]
        a = reduce(lambda x, y: x + y, a, '')
        return Token(51, a)

    star = many(tokstart('*')) >> ptr

    unsignedint  = unsigned + inttype  >> make_unsigned
    unsignedchar = unsigned + chartype >> make_unsigned
    voidptr      = void + star 
    primtypes    = unsignedint | unsignedchar | inttype | chartype
    primtypesptr = primtypes + star

    typeid =  voidptr | primtypesptr
    
# typeid = 'unsigned int' | 'unsigned char' | 'char' | 'int' | identfier followed by zero or more stars
    return typeid.parse(t)



# identifier = 


# funcdecl = typec identifier ( many(args) ) ;

def parse_funcdecl(tok):
    pass