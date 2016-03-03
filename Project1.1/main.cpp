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

    for ( int i = 0; i < n; i ++ )
    {
        if ( expression.at( i ) != ' ' )
        {
            temp.push_back( expression.at( i ) );
        }
    }
    return temp;
}

string calculate( char operators, double num1, double num2, int &error )
{
    double result;
    stringstream ss;

    switch ( operators )
    {
        case '+':
            result = ( num1 + num2 );
            break;
        case '-':
            result = ( num1 - num2 );
            break;
        case '*':
            result = ( num1 * num2 );
            break;
        case '/':
            if ( num2 == 0 )
            {
                error = 2;
                break;
            }
            result = ( num1 / num2 );
            break;
        case '^':
            result = ( pow( num1, num2 ) );
            break;

    }
    ss << result;
    return ss.str( );
}

string replaceVariable( unordered_map<string, string> &var, string expression, int &error )
{

    unordered_map<string, string>::const_iterator name = var.find( expression );
    
    if ( name != var.end( ) )
    {
        expression = name->second;
    }
    else
    {
        error = 1;
    }

    return expression;
}

string infix2postfix( string expression, unordered_map<string, string> &var, int &error )
{
    unordered_map<char, int > priority = {
        {'+', 1 },
        {'-', 1 },
        {'*', 2 },
        {'/', 2 },
        {'^', 3 } };

    int n = expression.size( );
    stack<char> evalu;
    string postfix, temp, tempVariable;

    for ( int i = 0; i < n; i ++ )
    {
        char char_temp = expression.at( i );

        if ( ! isdigit( char_temp ) && temp.size( ) > 0 && char_temp != '.' )
        {
            postfix.append( temp );
            postfix.push_back( ' ' );
            temp.clear( );
        }
        if ( ! isalpha( char_temp ) && tempVariable.size( ) > 0 )
        {
            postfix.append( replaceVariable( var, tempVariable, error ) );
            
            if(error != 0)
            {
                return "";
            }
            
            postfix.push_back( ' ' );
            tempVariable.clear( );
        }
        if ( isdigit( char_temp ) || char_temp == '.' )
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
            while ( ! evalu.empty( ) && evalu.top( ) != '(' )
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

                while ( ! evalu.empty( ) && evalu.top( ) != '(' && ! isdigit( evalu.top( ) ) && char_temp != '^' && priority.at( char_temp ) <= priority.at( evalu.top( ) ) )
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
    if ( tempVariable.size( ) > 0 )
    {
        postfix.append( replaceVariable( var, tempVariable, error ) );
        postfix.push_back( ' ' );
        tempVariable.clear( );
    }
    while ( ! evalu.empty( ) )
    {
        char tmp = evalu.top( );
        evalu.pop( );

        postfix.push_back( tmp );


    }

    return postfix;

}

string evalExpression( string expression, int &error )
{
    stack<string> operand;
    int n = expression.size( );
    string temp;

    for ( int i = 0; i < n; i ++ )
    {

         if ( expression.at( i ) == '+' || expression.at( i ) == '-' || expression.at( i ) == '*' || expression.at( i ) == '/' || expression.at( i ) == '^' )
        {
            if ( operand.size( ) > 1 )
            {
                double num2 = stod( operand.top( ).c_str( ) );
                operand.pop( );
                double num1 = stod( operand.top( ).c_str( ) );
                operand.pop( );

                operand.push( calculate( expression.at( i ), num1, num2, error ) );
                
                if(error != 0)
                {
                    return "";
                }
            }
        }
        else if ( isdigit( expression.at( i ) ) || expression.at( i ) == '.' )
        {
            while ( i < n && ( isdigit( expression.at( i ) ) || expression.at( i ) == '.' ) )
            {
                temp.push_back( expression.at( i ) );
                i ++;
            }
        }
        if ( temp.size( ) > 0 )
        {
            operand.push( temp );
            temp.clear( );
        }
    }
    return operand.top( ).c_str( );
}

int addVariable( string input, unordered_map<string, string > &var )
{
    string variable, expression;
    int error = 0;
    
    while ( input.at( 0 ) != '=' )
    {
        variable.push_back( input.at( 0 ) );
        input.erase( input.begin( ) );
    }

    unordered_map<string, string>::const_iterator name = var.find( variable );

    expression.append( input.substr( 1, input.size( ) - 1 ) );
    
    expression = infix2postfix( expression, var, error );
    
    if ( error == 0 )
    {
        if ( name != var.end( ) )
        {
            var.erase( variable );
            var.insert( make_pair<std::string, string>( variable.c_str( ), evalExpression( expression, error ) ) );
        }
        else
        {
            var.insert( make_pair<std::string, string>( variable.c_str( ), evalExpression( expression, error ) ) );
        }
    }
    return error;
}

int main( int argc, char** argv )
{
    unordered_map<string, string > var;
    
    string input;

    while ( input != "quit" )
    {
        getline( cin, input );
        size_t let = input.find( "let" );
        size_t quit = input.find( "quit" );
        string expression;
        int error = 0;
        if (quit != string::npos )
            break;
        if ( let != string::npos )
        {

            input = deleteWhiteSpace( input );
            input.erase( let, let + 3 );
            addVariable( input, var );
            
            
        }
        else
        {
            if ( var.size( ) > 0 )
            {
                expression = infix2postfix( input, var, error );
                
                if(error == 0)
                {
                    
                    string tmp = evalExpression( expression, error );
                        
                    if(error == 0)
                    {
                        cout << tmp << endl;
                    }
                    else
                    {
                        cout << "Division-By-Zero" << endl;
                    }
                }
                else
                {
                    cout << "Undeclared-Variable" << endl;
                }
                
            }
            else
            {
                
                string tmp = infix2postfix( input, var, error );
                
                if(error == 0)
                {
                    tmp = evalExpression( tmp , error );
                    
                    if(error == 0)
                    {
                        cout << tmp << endl;
                    }
                    else
                    {
                        cout << "Division-By-Zero" << endl;
                    }
                }
                else
                {
                    cout << "Undeclared-Variable" << endl;
                }
            }
        }

    }

    return 0;
}

