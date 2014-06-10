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
#define BOOST_TEST_MODULE MapStorageTest
#include <boost/test/unit_test.hpp>

# include <store/Storage.hpp>
# include <store/MapStorage.hpp>

BOOST_AUTO_TEST_CASE( TestConstructor )
{
  Storage * st = new MapStorage();
  delete st;
}

BOOST_AUTO_TEST_CASE( TestWhatYouPutIsWhatYouGet )
{ 
  Storage * st = new MapStorage();
  const std::string & key = "key";
  const std::string & value = "value";
  st->put(key, value, nullptr, nullptr);
  const std::string & output = st->get(key, nullptr, nullptr);
  BOOST_CHECK_EQUAL(value, output);
  delete st;
}

BOOST_AUTO_TEST_CASE( TestPutGetEmtpyString )
{ 
  Storage * st = new MapStorage();
  const std::string & key = "key";
  const std::string & value = "";
  st->put(key, value, nullptr, nullptr);
  const std::string & output = st->get(key, nullptr, nullptr);
  BOOST_CHECK_EQUAL(value, output);
  delete st;
}

BOOST_AUTO_TEST_CASE( TestGetNonExistingKey )
{ 
  Storage * st = new MapStorage();
  const std::string & key = "key";
  const std::string & value = "value";
  st->put(key, value, nullptr, nullptr);
  const std::string & output = st->get("Nope", nullptr, nullptr);
  BOOST_CHECK(output == "");
  delete st;
}

BOOST_AUTO_TEST_CASE( TestPutTwiceThenGet )
{ 
  Storage * st = new MapStorage();
  const std::string & key = "key";
  const std::string & value = "value";
  const std::string & value2 = "other_value";
  st->put(key, value, nullptr, nullptr);
  st->put(key, value2, nullptr, nullptr);
  const std::string & output = st->get(key, nullptr, nullptr);
  BOOST_CHECK_EQUAL(value2, output);
  delete st;
}

