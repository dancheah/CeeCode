#!/usr/bin/python
import sys, os, re, logging
import pdb
from re import VERBOSE
import token
from tokenize import generate_tokens
#from funcparserlib.lexer import make_tokenizer, Token, LexerError
from funcparserlib.lexer import Token, make_tokenizer
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

def tokenize1(str):
    """str -> Sequence(Token)
    This is the tokenize function inspired from the json
    example.
    """
    specs = [
        ('Space',     (r'[ \t\r\n]+',)),
        ('Int',       ('int',)),
        ('Char',      ('char',)),
        ('Unsigned',  ('unsigned',)),
        ('Void',      ('void',)),
        ('Name',      (r'[A-Za-z_][A-Za-z_0-9]*',)),
        ('SemiColon', (r';',)),
        ('LPar',      ('\(',)),
        ('RPar',      ('\)',)),
        ('Comma',     (r',',)),
        ('Star',      (r'\*',)),
    ]
    useless = ['Space', 0]
    t = make_tokenizer(specs)
    return [x for x in t(str) if x.type not in useless]

def typeid(tokens):
    t = lambda s: some(lambda tok: tok.type == s)
    inttype      = t('Int')
    chartype     = t('Char')
    unsignedtype = t('Unsigned') 
    name         = t('Name')
    star         = t('Star')
    void         = t('Void')

    udt      = name + many(star)
    prim     = (inttype | chartype | unsignedtype) + many(star)
    voidptr  = void + star + many(star)

    accepted_types = voidptr | prim | udt

    return accepted_types.parse(tokens)


# funcdecl = typec identifier ( many(args) ) ;

def parse_funcdecl(tok):
    pass
