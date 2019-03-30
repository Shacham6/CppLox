#pragma once

#include <types.hh>
#include <token.hh>

namespace Shach {

  class Scanner {
    public:
      explicit Scanner(string source);

      vector<Token> ScanTokens();

      bool IsAtEnd() const;

    private:
      void ScanToken();

      char Advance();

      void AddToken(TokenType type);

      void AddToken(TokenType type, string literal);

      bool Match(char expected);

      char Peek() const;

      void String();

      bool IsDigit(char character);

      void Number();

      char PeekNext() const;

      void Identifier();

      optional<TokenType> GetKeyword(string text);

    private:
      string source;
      vector<Token> tokens;

      int start = 0;
      int current = 0;
      int line = 1;

      unordered_map<string, TokenType> keywords = {
          {"and",    AND},
          {"class",  CLASS},
          {"else",   ELSE},
          {"false",  FALSE},
          {"for",    FOR},
          {"fun",    FUN},
          {"if",     IF},
          {"nil",    NIL},
          {"or",     OR},
          {"print",  PRINT},
          {"return", RETURN},
          {"super",  SUPER},
          {"this",   THIS},
          {"true",   TRUE},
          {"var",    VAR},
          {"while",  WHILE},
      };
  };

}