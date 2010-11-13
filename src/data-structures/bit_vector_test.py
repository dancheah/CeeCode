# A test harness for my bit vector implementation
from ctypes import *

mylib = CDLL("build/libds.dylib")

# Create bindings for the various c apis
mylib.new_bit_vector.restype = c_void_p 
mylib.new_bit_vector.argtypes = [ c_uint ]

mylib.delete_bit_vector.restype = None
mylib.delete_bit_vector.argtypes = [ c_void_p ]

mylib.set_bit.restype = None
mylib.set_bit.argtypes = [ c_void_p, c_uint, c_ubyte ]

mylib.get_bit.restype = c_ubyte
mylib.get_bit.argtypes = [ c_void_p, c_uint ]

# Test function
def test_all():
    bv = mylib.new_bit_vector(32)

    for i in range(0, 32):
        mylib.set_bit(bv, i, 1)
        v = mylib.get_bit(bv, i)
        print "test on %s %s" % (i, v)

        mylib.set_bit(bv, i, 0)
        v = mylib.get_bit(bv, i)
        print "test off %s %s" % (i, v)

    mylib.delete_bit_vector(bv)


# vim: sts=4 sw=4 ts=4 et ft=python
