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

#include "KeyHandler.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <sstream>

KeyHandler::KeyHandler(Storage * const storage) : _storage(storage) {}

http::Response * KeyHandler::put(const std::string &  key, const std::string & jsonValue) {

  // Load Json in a StringStream, for some reason the read_json
  // method does not work with a "raw" string
  std::stringstream ss;
  ss << jsonValue;

  // Create our Json tree
  using boost::property_tree::ptree;
  ptree tree;

  // Read Json and return appropiate value
  http::Response * r = new http::Response();
  try {
    read_json(ss, tree);
    std::string value = tree.get<std::string>("value");
    _storage->put(key, value);    

    r->setStatus(201);
    r->setBody(ss.str());
  } catch(...) {
    r->setStatus(400);
    r->setBody("Not Valid Json");
  }
  return r;
}

http::Response * KeyHandler::get(const std::string & key) {
  http::Response * r = new http::Response();;
  r->setStatus(200);
  r->setBody(_storage->get(key));
  return r;
}
