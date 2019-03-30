#include <types.hh>
#include <scanner.hh>
#include <error.hh>
#include <fmt/format.h>


Shach::Scanner::Scanner(string source)
    : source(move(source)),
      tokens(vector<Token>{}) {}


vector<Shach::Token> Shach::Scanner::ScanTokens() {
  while (!IsAtEnd()) {
    start = current;
    ScanToken();
  }

  tokens.emplace_back(TokenType::EOF_, "", "", line);
  return tokens;
}

bool Shach::Scanner::IsAtEnd() const {
  return current > source.length();
}

#define __token(CHAR, TYPE)  case CHAR: AddToken(TYPE); break;

void Shach::Scanner::ScanToken() {
  char c = Advance();
  switch (c) {
    case '/':
      if (Match('*')) {
        while (!(Peek() == '*' && PeekNext() == '/') && !IsAtEnd()) {
          Advance();
        }
        Advance();
        Advance();
        break;
      }

      if (!Match('/')) {
        AddToken(SLASH);
        break;
      }
      while (Peek() != '\n' && !IsAtEnd()) {
        Advance();
      }
      break;

    __token('(', LEFT_PAREN)
    __token(')', RIGHT_PAREN)
    __token('{', LEFT_BRACE)
    __token('}', RIGHT_BRACE)
    __token(',', COMMA)
    __token('.', DOT)
    __token('-', MINUS)
    __token('+', PLUS)
    __token(';', SEMICOLON)
    __token('*', STAR)
    __token('!', Match('=') ? BANG_EQUAL : BANG)
    __token('=', Match('=') ? EQUAL_EQUAL : EQUAL)
    __token('<', Match('=') ? LESS_EQUAL : LESS)
    __token('>', Match('=') ? GREATER_EQUAL : GREATER)


    case ' ':
    case '\r':
    case '\t':
    case '\0':
      // Ignore whitespace
      break;

    case '\n':
      line++;
      break;

    case '"':
      String();
      break;

//    case 'o':
//      if (Peek() == 'r') {
//        AddToken(OR);
//      }
//      break;

    default:
      if (IsDigit(c)) {
        Number();
      } else if (std::isalpha(c)) {
        Identifier();
      } else {
        Err::Error(line, fmt::format("Unexpected character : {}.", c));
      }
      break;
  }
}

#undef __token


char Shach::Scanner::Advance() {
  current++;
  return source[current - 1];
}


void Shach::Scanner::AddToken(Shach::TokenType type) {
  AddToken(type, "");
}


void Shach::Scanner::AddToken(Shach::TokenType type, string literal) {
  auto text = source.substr(static_cast<unsigned long>(start),
                            static_cast<unsigned long>(current));
  tokens.emplace_back(Token(type, text, std::move(literal), line));
}


bool Shach::Scanner::Match(char expected) {
  if (IsAtEnd()) {
    return false;
  }

  if (source[current] != expected) {
    return false;
  }

  current++;
  return true;
}


char Shach::Scanner::Peek() const {
  if (IsAtEnd()) return '\0';
  return source[current];
}


void Shach::Scanner::String() {
  while (Peek() != '"' && !IsAtEnd()) {
    if (Peek() == '\n') line++;
    Advance();
  }

  // Unterminated String
  if (!IsAtEnd()) {
    Shach::Err::Error(line, "Unterminated string.");
    return;
  }

  // The closing '"'
  Advance();

  // Trim the surrounding quotes.
  auto value = source.substr(static_cast<unsigned long>(start + 1),
                             static_cast<unsigned long>(current - 1));

  AddToken(STRING, value);
}


bool Shach::Scanner::IsDigit(char character) {
  return character > '0' && character < '9';
}


void Shach::Scanner::Number() {
  while (IsDigit(Peek())) Advance();

  // Look for fractional part.
  if (Peek() == '.' && IsDigit(PeekNext())) {
    Advance();

    while (IsDigit(Peek())) Advance();
  }

  AddToken(NUMBER, source.substr(static_cast<unsigned long>(start),
                                 static_cast<unsigned long>(current)));
}


char Shach::Scanner::PeekNext() const {
  if (current + 1 >= source.length()) return '\0';
  return source[current + 1];
}


void Shach::Scanner::Identifier() {
  while (std::isalnum(Peek())) Advance();

  // See if the identifier is a reserved word.
  auto text = source.substr(static_cast<unsigned long>(start),
                            static_cast<unsigned long>(current));

  auto type = GetKeyword(text);

  if (!type) {
    AddToken(IDENTIFIER);
    return;
  }

  AddToken(*type);
}


optional<Shach::TokenType> Shach::Scanner::GetKeyword(string text) {
  if (keywords.count(text) == 0) {
    return std::nullopt;
  }
  return keywords[text];
}
