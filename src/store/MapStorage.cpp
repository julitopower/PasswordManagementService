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

#include "MapStorage.hpp"
#include <openssl/evp.h>
#include <iostream>

static std::vector<char> encrypt(const std::vector<char> text, const unsigned char * k);
static std::vector<char> decrypt(const std::vector<char> text, const unsigned char * k);

MapStorage::MapStorage() :  _serializer(),
			    _map(_serializer.read()) {}

void MapStorage::put(const std::string & key,
		     const std::string & value,
		     const unsigned char * pwd1,
		     const unsigned char * pwd2) {
  std::vector<char> rawKeyVector(key.begin(), key.end());
  std::vector<char> keyVector = encrypt(rawKeyVector, pwd1);

  std::vector<char> rawValueVector(value.begin(), value.end());
  std::vector<char> valueVector(encrypt(rawValueVector, pwd2));

  (*_map)[keyVector] = valueVector;
  _serializer.write(*_map);
}

std::string MapStorage::get(const std::string & key,
			    const unsigned char * pwd1,
			    const unsigned char * pwd2) {
  std::vector<char> rawKeyVector(key.begin(), key.end());
  std::vector<char> encryptedKey = encrypt(rawKeyVector, pwd1);
  if(_map->find(encryptedKey) != _map->end()) {
     std::vector<char> valueVector  = decrypt((*_map)[encryptedKey], pwd2);
     
     return std::string(valueVector.begin(), valueVector.end());
  }
  std::cout << "Key " << key << " Not found" << std::endl;
  return "";
}

std::list<std::string> MapStorage::searchKeys(const std::string &  pattern,
					      const unsigned char * pwd1) {
  std::list<std::string> results;
  return results;
}

MapStorage::~MapStorage() {
  delete _map;
}

// Encrypt/Decrypt functions here

static std::vector<char> encrypt(const std::vector<char> text, const unsigned char * k) {
  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);

  int outlen, tmplen;
  unsigned char * outbuf = new unsigned char[text.size() * 100];
  const unsigned char iv[] = {'i','e','n','c','t','y','e','k'};
  EVP_EncryptInit_ex(&ctx, EVP_bf_cbc(), NULL, k, iv);

  EVP_EncryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)text.data(), text.size());

  EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen);
  outlen += tmplen;
  EVP_CIPHER_CTX_cleanup(&ctx);
  
  std::vector<char> s(outbuf, outbuf + outlen);
  return s;
}

static std::vector<char> decrypt(const std::vector<char> text, const unsigned char * k) {
  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);

  int outlen, tmplen;
  unsigned char * outbuf = new unsigned char[text.size() * 100];
  const unsigned char iv[] = {'i','e','n','c','t','y','e','k'};
  EVP_DecryptInit_ex(&ctx, EVP_bf_cbc(), NULL, k, iv);

  EVP_DecryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)&text[0], text.size());
  EVP_DecryptFinal_ex(&ctx, outbuf + outlen, &tmplen);
  outlen += tmplen;
  EVP_CIPHER_CTX_cleanup(&ctx);

  std::vector<char> s(outbuf, outbuf + outlen);
  return s;
}
