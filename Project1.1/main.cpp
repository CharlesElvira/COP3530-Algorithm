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

using namespace std;

/*
 * 
 */
string deleteWhiteSpace(string expression) {
    int n = expression.size();
    string temp;

    for (int i = 0; i < n; i++) {
        if (expression.at(i) != ' ') {
            temp.push_back(expression.at(i));
        }
    }
    return temp;
}

double calculate(char operators, double num1, double num2) {
    switch (operators) {
        case '+':
            return ( num1 + num2);
            break;
        case '-':
            return ( num1 - num2);
            break;
        case '*':
            return ( num1 * num2);
            break;
        case '/':
            return ( num1 / num2);
            break;
        case '^':
            return ( pow(num1, num2));
            break;
            
    }
}

double evalExpression(string expression) {
    unordered_map<char, int > priority= {{'+',1},{'-',1},{'*',2},{'/',2},{'^',3}};
    
    std::stack<string> operators;
    string temp;
    int n = expression.size();
    for (int i = 0; i < n; i++) {
                
        if (expression.at(i) == '+' || expression.at(i) == '-' || expression.at(i) == '*' || expression.at(i) == '/' || expression.at(i) == '^') {
            operators.push(expression.substr(i,i-1));
            
            if (temp.size() > 0) {
                operators.push(temp);
            }
            temp.clear();
        }
        else 
        {
            if (isdigit(i)) 
            {
                temp.push_back(i);
                
            }
            
        }
        std::cout << n++;
    }
    
    if (temp.size() != 0) {
        operators.push(temp.c_str());
        temp.clear();
    }
    
    while (!operators.empty()) {
        if (operators.size() > 0 ) {
            double num1 = operand.top();
            operand.pop();
            double num2 = operand.top();
            operand.pop();
            operand.push(calculate(operators.top(), num1, num2));
            operators.pop();
        }
    }
    if(operators.size() == 0 && operand.size() == 1)
    {
        double result =  operand.top();
        operators.pop();
        return result;
    }
    //    
    //    for ( int i = 0; i < n; i ++ )
    //    {
    //        if ( expression.at( i ) == '+' || expression.at( i ) == '-' || expression.at( i ) == '*' || expression.at( i ) == '/' )
    //        {
    //            operators.push(expression.at(i));
    //           
    //        }
    //        else
    //        {
    //            string temp;
    //
    //            while ( (i+1) <= n && isdigit( expression.at( i )) )
    //            {
    //                temp.push_back( expression.at( i ) );
    //                if(i+ 1<= n){
    //                i ++;
    //                }
    //            }
    //            if(temp.size() > 0){
    //                operand.push( atoi( temp.c_str( ) ) );
    //            }
    //        }
    //         if ( operand.size( ) == 2 )
    //            {
    //                int num1 = operand.top( );
    //                operand.pop( );
    //                int num2 = operand.top( );
    //                operand.pop( );
    //                
    //                switch ( operators.top() )
    //                {
    //                    case '+':
    //                        operand.push( num1 + num2 );
    //                        break;
    //                    case '-':
    //                        operand.push( num1 - num2 );
    //                        break;
    //                    case '*':
    //                        operand.push( num1 * num2 );
    //                        break;
    //                    case '/':
    //                        operand.push( num1 / num2 );
    //                        break;
    //                }
    //                operators.pop();
    //            }
    //    }
    //    return operand.top();


}

string evalParenthesis(string expression) {
    stack<char> parentheses;
    int begin = 0, end = 0;
    string result;
    if (expression.at(0) == '(') {
        for (char& i : expression) {
            int count = 0;

            switch (i) {
                case '(':
                    begin = count;
                    parentheses.push(i);
                    break;
                case ')':
                    if (!parentheses.empty() || parentheses.top() == '(') {
                        end = count;
                        result = to_string(evalExpression(expression.substr(begin + 1, end - 1)));
                        parentheses.pop();
                        break;
                    }
            }
            count++;
        }
    }
    return result;

}

int main(int argc, char** argv) {
    unordered_map<string, string > var;

    string expression, variable;

    string input;

    evalExpression("2*4+5-6/2^3^4^5");
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

