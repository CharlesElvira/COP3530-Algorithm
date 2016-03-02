/* 
 * File:   main.cpp
 * Author: celvira
 *
 * Created on February 17, 2016, 4:16 PM
 */

#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <sstream>
#include <math.h>
#include <stdexcept>

using namespace std;

/*
 * 
 */
string deleteWhiteSpace( string expression )
{
    int n = expression.size( );
    string temp;

    for ( int i = 0; i < n; i++ )
    {
        if ( expression.at( i ) != ' ' )
        {
            temp.push_back( expression.at( i ) );
        }
    }
    return temp;
}

double calculate( char operators, double num1, double num2 )
{
    switch ( operators )
    {
        case '+':
            return ( num1 + num2 );
            break;
        case '-':
            return ( num1 - num2 );
            break;
        case '*':
            return ( num1 * num2 );
            break;
        case '/':
            if ( num2 == 0 )
            {
                throw invalid_argument( "Division By Zero" );
            }
            return ( num1 / num2 );
            break;
        case '^':
            return ( pow( num1, num2 ) );
            break;

    }
}

string replaceVariable( unordered_map<string, string> &var, string expression )
{

    string temp;
    int n = expression.size( ), begin = 0;
    if ( var.size( ) > 0 )
    {
        for ( int i = 0; i < n; i++ )//look for previous declared variable and replace them
        {
            if ( isalpha( expression.at( i ) ) )
            {

                temp.push_back( expression.at( i ) );

            }
            if ( temp.size( ) > 0 && var.size( ) > 0 )
            {
                unordered_map<string, string>::const_iterator name = var.find( temp );

                if ( name != var.end( ) )
                {
                    string tmp;
                    tmp = expression.substr( 0, begin ) + name->second + expression.substr( i, expression.size( ) - 1 );
                    expression = tmp;
                    begin = 0;
                }
            }
            temp.clear( );
        }
    }
    else
    {
        throw invalid_argument( "Variable Undefined" );
    }

    return expression;
}

string infix2postfix( string expression, unordered_map<string, string> &var )
{
    unordered_map<char, int > priority = {
        {'+', 1 },
        {'-', 1 },
        {'*', 2 },
        {'/', 2 },
        {'^', 3 }
    };

    int n = expression.size( );
    stack<char> evalu;
    string postfix, temp, tempVariable;

    for ( int i = 0; i < n; i++ )
    {
        char char_temp = expression.at( i );

        if ( !isdigit( char_temp ) && temp.size( ) > 0 )
        {
            postfix.append( temp );
            postfix.push_back( ' ' );
            temp.clear( );
        }
        if ( !isalpha( char_temp ) && tempVariable.size( ) > 0 )
        {
            postfix.append( replaceVariable( var, tempVariable ) );
            postfix.push_back( ' ' );
            tempVariable.clear( );
        }
        if ( isdigit( char_temp ) )
        {
            temp.push_back( char_temp );
        }
        else if ( isalpha( char_temp ) )
        {
            tempVariable.push_back( char_temp );
        }
        else if ( char_temp == '(' )
        {
            evalu.push( char_temp );
        }
        else if ( char_temp == ')' )
        {
            while ( !evalu.empty( ) && evalu.top( ) != '(' )
            {
                postfix.push_back( evalu.top( ) );
                evalu.pop( );
            }
            evalu.pop( );
        }
        else if ( char_temp == '+' || char_temp == '-' || char_temp == '*' || char_temp == '/' || char_temp == '^' )
        {
            if ( evalu.empty( ) || evalu.top( ) == '(' )
            {
                evalu.push( char_temp );
            }

            else
            {

                while ( !evalu.empty( ) && evalu.top( ) != '(' && !isdigit( evalu.top( ) ) && char_temp != '^' && priority.at( char_temp ) <= priority.at( evalu.top( ) ) )
                {
                    postfix.push_back( evalu.top( ) );
                    evalu.pop( );
                }

                evalu.push( char_temp );
            }
        }

    }
    if ( temp.size( ) > 0 )
    {
        postfix.append( temp );
        postfix.push_back( ' ' );
        temp.clear( );
    }
    while ( !evalu.empty( ) )
    {
        char tmp = evalu.top( );
        evalu.pop( );

        postfix.push_back( tmp );


    }

    return postfix;

}

double evalExpression( string expression )
{
    stack<string> operand;
    int n = expression.size( );
    string temp;

    for ( int i = 0; i < n; i++ )
    {

        if ( expression.at( i ) == '+' || expression.at( i ) == '-' || expression.at( i ) == '*' || expression.at( i ) == '/' || expression.at( i ) == '^' )
        {
            if ( operand.size( ) > 1 )
            {
                double num2 = atof( operand.top( ).c_str( ) );
                operand.pop( );
                double num1 = atof( operand.top( ).c_str( ) );
                operand.pop( );

                operand.push( to_string( calculate( expression.at( i ), num1, num2 ) ) );

            }
        }
        else if ( isdigit( expression.at( i ) ) )
        {
            while ( i < n && isdigit( expression.at( i ) ) )
            {
                temp.push_back( expression.at( i ) );
                i++;
            }
        }
        if ( temp.size( ) > 0 )
        {
            operand.push( temp );
            temp.clear( );
        }
    }
    return atof( operand.top( ).c_str( ) );
}

int main( int argc, char** argv )
{
    unordered_map<string, string > var;

    string expression, variable, input;

        while ( input != "quit" )
        {
            getline( cin, input );
            size_t let = input.find( "let" );
    
            if ( let != string::npos )
            {
    
                input = deleteWhiteSpace( input );
                input.erase( let, let + 3 );
    
                while ( input.at( 0 ) != '=' )
                {
                    variable.push_back( input.at( 0 ) );
                    input.erase( input.begin( ) );
                }
                expression.append( input.substr( 1, input.size( ) - 1 ) );
    
                expression = infix2postfix(expression, var );
    
                var.insert( make_pair<std::string, string>( variable.c_str( ), to_string( evalExpression( expression ) ) ) );
            }
            else
            {
                if(var.size() > 0)
                {
                    expression = infix2postfix(input, var );
                    cout << evalExpression(expression) << endl;
                }
                else
                {
                    cout << evalExpression(infix2postfix(input, var))<<endl;
                }
            }

        }

    return 0;
}

