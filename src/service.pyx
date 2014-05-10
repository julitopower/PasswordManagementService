 ##                                                                                                                                        
 # The MIT License (MIT)                                                                                                                   
 #                                                                                                                                         
 # Copyright (c) 2014 Julio Delgado                                                                                                        
                                                                                                                                           
 # Permission is hereby granted, free of charge, to any person obtaining a copy                                                            
 # of this software and associated documentation files (the "Software"), to deal                                                           
 # in the Software without restriction, including without limitation the rights                                                            
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                                                               
 # copies of the Software, and to permit persons to whom the Software is                                                                   
 # furnished to do so, subject to the following conditions:                                                                                
 #                                                                                                                                         
 # The above copyright notice and this permission notice shall be included in all                                                          
 # copies or substantial portions of the Software.                                                                                         
 #                                                                                                                                         
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                                                              
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                                                                
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                                                             
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                                                                  
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                                                           
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                                                           
 # SOFTWARE.                                                                                                                               
 ##/
from libcpp.string cimport string
from libcpp cimport bool

cdef extern from "Adder.hpp":
    cdef cppclass Adder:
        Adder()
        int add(string json)

cdef class adder:
    cdef Adder* ptr
    def __cinit__(self):
        self.ptr = new Adder()

    def __dealloc__(self):
        del self.ptr

    cpdef int add(self, string json):
        return self.ptr.add(json)

cdef extern from "AddKeyHandler.hpp":
    cdef cppclass AddKeyHandler:
        bool handle(string key, string jsonValue)

cdef class addkeyhandler:
    cdef AddKeyHandler * ptr
    def __cinit__(self):
        self.ptr = new AddKeyHandler()

    def __dealloc__(self):
        del self.ptr

    cpdef bool handle(self, string key, string jsonValue):
        return self.ptr.handle(key, jsonValue)

cdef extern from "auth/BasicAuthenticator.cpp" namespace "auth":
    cdef cppclass BasicAuthenticator: 
        BasicAuthenticator()
        bool authenticate(string key, string password)

cdef class basicauthenticator:
    cdef BasicAuthenticator * ptr
    def __cinit__(self):
        self.ptr = new BasicAuthenticator()

    def __dealloc__(self):
        del self.ptr

    cpdef bool authenticate(self, string key, string value):
        return self.ptr.authenticate(key, value)
