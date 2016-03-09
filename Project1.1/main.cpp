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
#define TABLE_SIZE 100
using namespace std;

/*
 * 
 */

template <typename Ke, typename Va>
class Node {
public:
    Node(const Ke &key, const Va &value) :
    key(key), value(value), next(NULL) {
    }

    Ke getKey() const {
        return key;
    }

    Va getValue() const {
        return value;
    }

    void setValue(Va value) {
        Node::value = value;
    }

    Node *getNext() const {
        return next;
    }

    void setNext(Node *next) {
        Node::next = next;
    }

private:
    
    Ke key;
    Va value;
    
    Node *next;
};

template <typename Ke>
struct Key2Hash {
    unsigned long operator()(const Ke& key) const
    {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};
template < typename Ke, typename Va, typename Fq = Key2Hash< Ke > >
class HashMap {
public:
    HashMap() {
        
        table = new Node<Ke, Va> *[TABLE_SIZE]();
    }

    bool get(const Ke &key, Va &value) {
        unsigned long hashValue = hashFunc(key);
        Node<Ke, Va> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void put(const Ke &key, const Va &value) {
        unsigned long hashValue = hashFunc(key);
        Node<Ke, Va> *prev = NULL;
        Node<Ke, Va> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            entry = new Node<Ke, Va>(key, value);
            if (prev == NULL) {
                
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            entry->setValue(value);
        }
    }

    void remove(const Ke &key) {
        unsigned long hashValue = hashFunc(key);
        Node<Ke, Va> *prev = NULL;
        Node<Ke, Va> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            
            return;
        }
        else {
            if (prev == NULL) {
                
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }
    
    ~HashMap() {
        
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node<Ke, Va> *entry = table[i];
            while (entry != NULL) {
                Node<Ke, Va> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
        
        delete [] table;
    }

private:
    
    Node<Ke, Va> **table;
    Fq hashFunc;
};
string deleteWhiteSpace( string expression )
{
    int n = expression.size( ), i =0;
    string temp;
    
    while(i < n)
    {
        if ( expression.at( i ) != ' ' )
        {
            
            if (i == 0 && (expression.at(i) == '-' || expression.at(i) == '+')) {
                temp.push_back('(');
                temp.push_back('0');
                temp.push_back( expression.at( i ) );
                i++;
                while(i<n && (isdigit(expression.at( i ))))
                {
                    temp.push_back( expression.at( i ) );
                    i++;
                }
                temp.push_back(')');
            } else if ( i >= 1 && temp.size()> 0 && (temp.at(temp.size() - 1) == '(' || temp.at(temp.size()-1) == '/'  || temp.at(temp.size()-1) == '*'|| temp.at(temp.size()-1) == '^')&& (expression.at(i) == '-' || expression.at(i) == '+')) {
                temp.push_back('(');
                temp.push_back('0');
                temp.push_back( expression.at( i ) );
                i++;
                while(i<n && (isdigit(expression.at( i )) ))
                {
                    
                    temp.push_back( expression.at( i ) );
                    i++;
                }
                temp.push_back(')');
            } else if(i +1<n && (expression.at(i) == 'e' ) && (expression.at(i+1) == '-' || expression.at(i+1) == '+'))
            {
                temp.push_back('*');
                temp.push_back('1');
                temp.push_back('0');
                temp.push_back('^');
                
                temp.push_back('(');
                temp.push_back('0');
                i++;
                temp.push_back( expression.at( i ) );              
                i++;
               
                while(i<n && (isdigit(expression.at( i )) ))
                {
                    
                    temp.push_back( expression.at( i ) );
                    i++;
                }
                temp.push_back(')');
            }
            else
            {
                temp.push_back( expression.at( i ) );
                i++;
                
            }
            
        }
        else if(expression.at( i ) == ' ')
            {
                i++;
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
        expression = deleteWhiteSpace(name->second);
    }
    else
    {
        error = 1;
    }
    
    return expression;
}

string infix2postfix( string expression, unordered_map<string, string> &var, int &error )
{
    unordered_map<char, int > priority = { {'+', 1 }, {'-', 1 }, {'*', 2 }, {'/', 2 }, {'^', 3 } };

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
            string str = replaceVariable( var, tempVariable, error );
            
            
            if(error != 0)
            {
                return "";
            }
            else
            {
                
                postfix.append( str );
                
                if(error!=0)
                {
                    return "";
                }
                postfix.push_back( ' ' );
                tempVariable.clear( );
            }
            
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
        string str1 = replaceVariable( var, tempVariable, error );
        if(error !=0)
        {
            return "";
        }
        string str = infix2postfix(str1, var, error);
        if (error !=0)
        {
            return "";
        }
        postfix.append( str );
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

string evalExpression( string expression, unordered_map<string, string > &var, int &error )
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
            else if(operand.size( ) == 1 )
            {
                double num2 = stod( operand.top( ).c_str( ) );
                operand.pop( );
                double num1 = 0;

                operand.push( calculate( expression.at( i ), num1, num2, error ) );
                
                if(error != 0)
                {
                    return "";
                }
            }
            
            
        }
        else if ( isdigit( expression.at( i ) ) || expression.at( i ) == '.')
        {
            while ( i < n && ( isdigit( expression.at( i ) ) || expression.at( i ) == '.' || (i+1< n && (expression.at( i ) == 'e' && expression.at( i+1 ) == '+') ||(expression.at( i ) == '+' && expression.at( i-1 ) == 'e') ) ) )
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
            var.insert( make_pair<std::string, string>( variable.c_str( ), evalExpression( expression, var, error ) ) );
        }
        else
        {
            var.insert( make_pair<std::string, string>( variable.c_str( ), evalExpression( expression, var, error ) ) );
        }
    }
    return error;
}

int main( int argc, char** argv )
{
    unordered_map<string, string > var;
    HashMap<string,string,Key2Hash<string>> var1;
    
    string input;

    while ( input != "quit" )
    {
        getline( cin, input );
        
        string expression;
        string temp;
        int error = 0;
        
        int i=0;
        while(i<input.size())
        {
            if(input.at(i) != ' ')
            {
                input = input.substr(i,input.size());
                break;
            }
            i++;
        }
        
        size_t let = input.find( "let " );
        int quit = input.compare( "quit" );
        input = deleteWhiteSpace( input );
        if ( quit ==  0)
            break;
        if (  let != string::npos )
        {

            
            input.erase( let, let + 3 );
            addVariable( input, var );
            
            
        }
        else if(input.size()>0 )
        {
            input = deleteWhiteSpace( input );
            if ( var.size( ) > 0 )
            {
                expression = infix2postfix( input, var, error );
                
                if(error == 0)
                {
                    
                    string tmp = evalExpression( expression,var, error );
                        
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
                    tmp = evalExpression( tmp ,var, error );
                    
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

