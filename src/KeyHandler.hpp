/**                                                                                                                                        
 * The MIT License (MIT)                                                                                                                   
 *                                                                                                                                         
 * Copyright (c) 2014 Julio Delgado                                                                                                        
                                                                                                                                           
 * Permission is hereby granted, free of charge, to any person obtaining a copy                                                            
 * of this software and associated documentation files (the "Software"), to deal                                                           
 * in the Software without restriction, including without limitation the rights                                                            
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                                                               
 * copies of the Software, and to permit persons to whom the Software is                                                                   
 * furnished to do so, subject to the following conditions:                                                                                
 *                                                                                                                                         
 * The above copyright notice and this permission notice shall be included in all                                                          
 * copies or substantial portions of the Software.                                                                                         
 *                                                                                                                                         
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                                                              
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                                                                
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                                                             
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                                                                  
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                                                           
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                                                           
 * SOFTWARE.                                                                                                                               
 **/

#ifndef KEY_HANDLER
#define KEY_HANDLER

#include <string>
#include <store/Storage.hpp>
#include <http/Response.hpp>

/**
 * This class handles basic operations related to Key/Value, including add/get.
 */
class KeyHandler {
public:
  KeyHandler(Storage * const storage);
  http::Response *  put(const std::string &  key,
			const std::string & jsonValue,
			const unsigned char * pwd1,
			const unsigned char * pwd2);
  http::Response *  get(const std::string & key,
			const unsigned char * pwd1,
			const unsigned char * pwd2);

  http::Response * listKeys(const unsigned char * pwd);
private:
  Storage * const _storage; 
};

#endif // ADD_KEY_HANDLDER
