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
from cython.operator cimport dereference as deref

# Http Response
cdef extern from "http/Response.hpp" namespace "http":
    cdef cppclass Response: 
        Response()
        string & getStatus() const
        string & getBody() const

cdef class response:
    cdef Response * ptr

    def __cinit__(self, create_ptr = True):
        if create_ptr:
            self.ptr = new Response()

    def __dealloc__(self):
        del self.ptr
        pass

    cpdef string getStatus(self):
        return self.ptr.getStatus()

    cpdef string getBody(self):
        return self.ptr.getBody()

    cdef setPtr(self, Response * resp):
        del self.ptr
        self.ptr = resp
# Trying to implement CPP polymorphism using Cython
cdef extern from "store/Storage.hpp":
    cdef cppclass Storage:
        pass
cdef class storage:
    cdef Storage * ptr

cdef extern from "store/MapStorage.hpp":
    cdef cppclass MapStorage(Storage):
        pass

cdef class mapstorage(storage):
    def __cinit__(self):
        self.ptr = new MapStorage()
    def __dealloc__(self):
        del self.ptr


cdef extern from "KeyHandler.hpp":
    cdef cppclass KeyHandler:
        KeyHandler(Storage * const storage)
        Response * put(string key, string jsonValue, unsigned char* pwd1, unsigned char* pwd2)
        Response * get(string key, unsigned char * pwd1, unsigned char * pwd2)
        Response * listKeys(unsigned char * pwd)

cdef class keyhandler:
    cdef KeyHandler * ptr
    def __cinit__(self, storage storage):
        self.ptr = new KeyHandler(storage.ptr)

    def __dealloc__(self):
        del self.ptr
        pass

    cpdef response put(self, string key, string jsonValue, unsigned char * pwd1, unsigned char * pwd2):
        r = response(False)
        cdef Response * resp = self.ptr.put(key, jsonValue, pwd1, pwd2)
        r.setPtr(resp)
        return r

    cpdef response get(self, string key, unsigned char * pwd1, unsigned char * pwd2):
        r = response(False)
        cdef Response * resp = self.ptr.get(key, pwd1, pwd2)
        r.setPtr(resp)
        return r

    cpdef response listKeys(self, unsigned char * pwd):
        r = response(False)
        cdef Response * resp = self.ptr.listKeys(pwd)
        r.setPtr(resp)
        return r

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

#############################################################

