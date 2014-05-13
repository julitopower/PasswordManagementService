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

# Import CPP class definition. Declare methods needed in this
# particular file
cdef extern from "Adder.hpp":
    cdef cppclass Adder:
        Adder()
        int add(string json)

# Python class that we use to wrap the CPP one.
cdef class adder:
    cdef Adder* ptr
    def __cinit__(self):
        self.ptr = new Adder()

    def __dealloc__(self):
        del self.ptr

    cpdef int add(self, string json):
        return self.ptr.add(json)

# Http Response
cdef extern from "http/Response.cpp" namespace "http":
    cdef cppclass Response: 
        Response()
        string getStatus() const
        string getBody() const
        void setStatus(string status)
        void setBody(string body)

cdef class response:
    cdef Response * ptr

    def __cinit__(self):
        self.ptr = new Response()

    def __dealloc__(self):
        #del self.ptr
        pass

    cpdef setStatus(self, string st):
        self.ptr.setStatus(st);

    cpdef string getStatus(self):
        return self.ptr.getStatus()

    cpdef setBody(self, string body):
        self.ptr.setBody(body)

    cpdef string getBody(self):
        return self.ptr.getBody()

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


cdef extern from "AddKeyHandler.hpp":
    cdef cppclass AddKeyHandler:
        AddKeyHandler(Storage * const storage)
        Response handle(string key, string jsonValue)
        Response get(string key)

cdef class addkeyhandler:
    cdef AddKeyHandler * ptr
    def __cinit__(self, storage storage):
        self.ptr = new AddKeyHandler(storage.ptr)

    def __dealloc__(self):
        del self.ptr
        pass

    cpdef response handle(self, string key, string jsonValue):
        r = response()
        cdef Response resp = self.ptr.handle(key, jsonValue)
        r.setStatus(resp.getStatus())
        r.setBody(resp.getBody())
        return r

    cpdef response get(self, string key):
        r = response()
        cdef Response resp = self.ptr.get(key)
        r.setStatus(resp.getStatus())
        r.setBody(resp.getBody())
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

