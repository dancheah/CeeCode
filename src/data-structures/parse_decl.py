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
f4 = "int* foobar(int* b, int* c);"
f5 = "int* foobar(int* b, int* c, int* d);"
f6 = "unsigned int* foobar(int* b, unsigned int* c, int* d);"
f7 = "int foobar(bit_vector_t* bv);"

def tokenize(str):
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

def test_tokenize():
    """ Test tokenize function. Use nosetests 
        for testing from command line or ipython
        to test from the REPL
    """
    assert(tokenize(f1) == [Token('Int', 'int'),
                            Token('Name', 'foobar'),
                            Token('LPar', '('),
                            Token('Void', 'void'),
                            Token('RPar', ')'),
                            Token('SemiColon', ';')])

def parse(tokens):
    t = lambda s: some(lambda tok: tok.type == s)

    inttype      = t('Int')
    chartype     = t('Char')
    unsignedtype = t('Unsigned') 
    name         = t('Name')
    star         = t('Star')
    void         = t('Void')
    lpar         = skip(t('LPar'))
    rpar         = skip(t('RPar'))
    comma        = skip(t('Comma'))
    semicolon    = skip(t('SemiColon'))

    def collapse(x):
        bp()
        if len(x[1]) > 0:
            # TODO: handle multiple stars
            return Token("UserTypePointer", x[0].value + " " + x[1][0].value)
        else:
            return Token("UserType", x[0].value)


    def make_func(x):
        return Token('Function', x.value)


    def make_type(x):
        if len(x) == 3: 
            return Token("UnsignedTypePointer", x)
        elif len(x) == 2: 
            if x[0].type == "Unsigned":
                return Token("UnsignedType", x)
            else:
                return Token("TypePointer", x)
        else:
            return Token("Type", x)


    udt      = name + many(star) >> collapse
    prim     = (inttype | chartype | unsignedtype + inttype | unsignedtype + chartype ) + many(star) >> make_type
    voidptr  = void + star + many(star)
    func     = name >> make_func

    accepted_types = voidptr | prim | udt

    # Return Type
    rettype = void | accepted_types 

    # Argument List
    decl      = accepted_types + name
    decl_list = decl + many(comma + decl)

    arg_list  = void | decl_list

    func_decl = rettype + func + lpar + arg_list + rpar + semicolon

    return func_decl.parse(tokens)


def parse1(tokens):
    """ 
    Experimenting with collapsing part of the parse tree
    to make it easier to work with.
    """
    t = lambda s: some(lambda tok: tok.type == s)

    name         = t('Name')
    star         = t('Star')

    def collapse(x):
        if len(x[1]) > 0:
            # TODO: handle multiple stars
            return Token("UserTypePointer", x[0].value + " " + x[1].value)
        else:
            return Token("UserType", x[0].value)

    udt = name + many(star) >> collapse

    return udt.parse(tokens)
