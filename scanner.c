#include "scanner.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>

Scanner scanner;

void scanner_init(const char *source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

static bool is_at_end()
{
    return *scanner.current == '\0';
}

static Token make_token(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token error_token(const char *message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static char advance()
{
    scanner.current++;
    return scanner.current[-1];
}

static bool match(char expected)
{
    if (is_at_end())
    {
        return false;
    }
    if (*scanner.current != expected)
    {
        return false;
    }

    scanner.current++;
    return true;
}

static char peek()
{
    return *scanner.current;
}

static char peek_next()
{
    if (is_at_end())
        return '\0';

    return scanner.current[1];
}

static void skip_whitespace()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            scanner.line++;
            advance();
            break;
        case '/':
            if (peek_next() == '/')
            {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !is_at_end())
                    advance();
            }
            else
            {
                return;
            }
            break;
        default:
            return;
        }
    }
}

static Token string()
{
    while (peek() != '"' && !is_at_end())
    {
        if (peek() == '\n')
            scanner.line++;
        advance();
    }

    if (is_at_end())
        return error_token("Unterminated string.");

    // The closing quote.
    advance();
    return make_token(TOKEN_STRING);
}

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static Token number()
{
    while (is_digit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && is_digit(peek_next()))
    {
        // Consume the "."
        advance();

        while (is_digit(peek()))
            advance();
    }

    return make_token(TOKEN_NUMBER);
}

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

static TokenType check_keyword(int start, int length, const char *rest, TokenType type)
{
    if (scanner.current - scanner.start == start + length &&
        memcmp(scanner.start + start, rest, length) == 0)
    {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type()
{
    switch (scanner.start[0])
    {
    case 'a':
        return check_keyword(1, 2, "nd", TOKEN_AND);
    case 'c':
        return check_keyword(1, 4, "lass", TOKEN_CLASS);
    case 'd':
        return check_keyword(1, 2, "ef", TOKEN_DEF);
    case 'e':
        return check_keyword(1, 3, "lse", TOKEN_ELSE);
    case 'f':
        return check_keyword(1, 2, "or", TOKEN_FOR);
    case 'F':
        return check_keyword(1, 4, "alse", TOKEN_FALSE);
    case 'i':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'f':
                return check_keyword(2, 1, "", TOKEN_IF);
            case 's':
                return check_keyword(2, 1, "s", TOKEN_IS);
            }
        }
        break;
    case 'N':
        return check_keyword(1, 3, "one", TOKEN_NONE);
    case 'n':
        return check_keyword(1, 2, "ot", TOKEN_NOT);
    case 'o':
        return check_keyword(1, 1, "r", TOKEN_OR);
    case 'p':
        return check_keyword(1, 4, "rint", TOKEN_PRINT);
    case 'r':
        return check_keyword(1, 5, "eturn", TOKEN_RETURN);
    case 'T':
        return check_keyword(1, 3, "rue", TOKEN_TRUE);
    case 'w':
        return check_keyword(1, 4, "hile", TOKEN_WHILE);
    }

    return TOKEN_IDENTIFIER;
}

static Token identifier()
{
    while (is_alpha(peek()) || is_digit(peek()))
        advance();

    return make_token(identifier_type());
}

Token scan_token()
{
    skip_whitespace();

    scanner.start = scanner.current;

    if (is_at_end())
    {
        return make_token(TOKEN_EOF);
    }

    char c = advance();

    if (is_alpha(c))
    {
        return identifier();
    }
    else if (is_digit(c))
    {
        return number();
    }

    switch (c)
    {
    case '(':
        return make_token(TOKEN_LEFT_PAREN);
    case ')':
        return make_token(TOKEN_RIGHT_PAREN);
    case '{':
        return make_token(TOKEN_LEFT_BRACE);
    case '}':
        return make_token(TOKEN_RIGHT_BRACE);
    case ';':
        return make_token(TOKEN_SEMICOLON);
    case ',':
        return make_token(TOKEN_COMMA);
    case '.':
        return make_token(TOKEN_DOT);
    case '-':
        return make_token(TOKEN_MINUS);
    case '+':
        return make_token(TOKEN_PLUS);
    case '/':
        return make_token(TOKEN_SLASH);
    case '*':
        return make_token(TOKEN_STAR);
    case '!':
        return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
        return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
        return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
        return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    case '"':
        return string();
    }

    return error_token("Unexpected character.");
}