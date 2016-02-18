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

int evalExpression( string expression )
{
    int n = expression.size( );
    stack<string> operators;
    stack<int> operand;

    for ( int i = 0; i < n; i ++ )
    {
        if ( expression.at( i ) == '+' || expression.at( i ) == '-' || expression.at( i ) == '*' || expression.at( i ) == '/' )
        {
            operators.push(expression.substr(i,i-1));
           
        }
        else
        {
            string temp;

            while ( (i+1) <= n && isdigit( expression.at( i )) )
            {
                temp.push_back( expression.at( i ) );
                if(i+ 1<= n){
                i ++;
                }
            }
            if(temp.size() > 0){
                operand.push( atoi( temp.c_str( ) ) );
            }
        }
         if ( operand.size( ) == 2 )
            {
                int num1 = operand.top( );
                operand.pop( );
                int num2 = operand.top( );
                operand.pop( );
                
                switch ( operators.top().at(0) )
                {
                    case '+':
                        operand.push( num1 + num2 );
                        break;
                    case '-':
                        operand.push( num1 - num2 );
                        break;
                    case '*':
                        operand.push( num1 * num2 );
                        break;
                    case '/':
                        operand.push( num1 / num2 );
                        break;
                }
                operators.pop();
            }
    }
    return operand.top();

}

int main( int argc, char** argv )
{
    unordered_map<string, string > var;

    string expression, variable;

    string input;

    cout<<evalExpression( "51 + 5556 * 25 +65" );
    /*
    while(input != "quit")
    {
        getline(cin, input);
        
        if(input.find("let") < input.size())
        {
            input = deleteWhiteSpace(input);
            input.erase(input.begin(), input.begin()+ input.find("let")+3);
            while(input.at(0) != '=')
            {
                variable.push_back(input.at(0));
                input.erase(input.begin());
            }
            expression.append(input.substr(1,input.size()-1));
            var.insert(make_pair<std::string,string>(variable.c_str(),expression.c_str()));
        }
    }*/

    return 0;
}

