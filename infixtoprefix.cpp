#include <iostream>
#include <vector>
using namespace std;

int out_order(string symbol)
{
    if(symbol == "(")
        return 0;
    else if(symbol == "#")
        return -1;
    else if(symbol == "+" || symbol == "-")
        return 6;
    else if(symbol == "*" || symbol == "/")
        return 7;
    else
        return -1;
}

int in_order(string symbol)
{

    if(symbol == "(")
        return 9;
    else if(symbol == "#")
        return -1;
    else if(symbol == "+" || symbol == "-")
        return 6;
    else if(symbol == "*" || symbol == "/")
        return 7;
    else
        return -1;
}

string InToPost(string In)
{
    string::size_type p_oper = 0, p_start = 0;
    //to show the index of string, one point to operator, one point to the start of numbers
    vector<string> operators;
    string ans;
    operators.push_back("#");
    while(p_oper != In.size())
    {
        //p_start is usually left to p_oper
        p_oper = In.find_first_of("+-*/()", p_start); //start from p_start, find the first operator and save index into p_oper
        //set two indicators, to get the front index and the end index of long numbers, ex:123
        //of course this method could also apply to short string like operators
        //in the if else below, we have to do the in_stack_or_not check in both situation...


        if(p_oper >= In.size())         //if all of the operator has been found...
        {
            ans += In.substr(p_start, In.size()-p_start);
            break;
        }
        //this condition checking is to fix : "find_first_of has set p_oper out of strlen"

        if(p_oper != p_start)
            ans += In.substr(p_start, p_oper-p_start);


        if(In.substr(p_oper, 1) == ")")    //check if it is ")"
        {
            while(operators.back() != "(")
            {
                ans += operators.back();
                operators.pop_back();
            }
            operators.pop_back();   //avoid appending "(" into ans string
        }
        else if(in_order(In.substr(p_oper, 1)) > out_order(operators.back()))
            {operators.push_back(In.substr(p_oper, 1));}
        else
        {
            while(in_order(In.substr(p_oper, 1)) <= out_order(operators.back()))
            {
                //如果我始終都比人家小，我就要讓給人家一直出來
                ans += operators.back();
                operators.pop_back();
            }
            operators.push_back(In.substr(p_oper, 1));
        }
        p_start = p_oper + 1;
    }
    while(operators.back() != "#")
    {
        ans += operators.back();
        operators.pop_back();
    }
    return ans;
}

void pop_and_set(vector<string> &operators, vector<string> &alpha)
{
    string temp, temp_back, temp_oper;
    temp_back = alpha.back();
    alpha.pop_back();
    temp = alpha.back();
    alpha.pop_back();
    temp_oper = operators.back();
    operators.pop_back();
    alpha.push_back(temp_oper+temp+temp_back);
}

string InToPre(string s)
{
    vector<string> operators;
    vector<string> alpha;
    operators.push_back("#");  //initialize stack -"operators"
    string::size_type p_oper = 0, p_start = 0;
    string oper_temp;          //needed while compareing in_order & out_order
    while(p_oper != string::npos)
    {
        p_oper = s.find_first_of("+-*/()", p_start); //start from p_start, find the first operator and save index into p_oper
        if(p_oper == string::npos)
        {
            alpha.push_back(s.substr(p_start, p_oper-p_start));
            while(alpha.size() != 1)
            {
                pop_and_set(operators, alpha);
            }
            return alpha[0];
        }
        if(p_oper != p_start)
            alpha.push_back(s.substr(p_start, p_oper-p_start));
        oper_temp = s.substr(p_oper, 1);
        if(oper_temp == ")")
        {
            while(operators.back() != "(")
            {
                pop_and_set(operators, alpha);
            }
            operators.pop_back();   //pop掉"("
        }
        else if(in_order(oper_temp) > out_order(operators.back()))
        {
            operators.push_back(oper_temp);
        }
        else
        {
            while(in_order(oper_temp) <= out_order(operators.back()))
            {
                pop_and_set(operators, alpha);
            }
            operators.push_back(oper_temp);

        }
        p_start = p_oper + 1;


    }

}


int main()
{
    string s = "A/B-(C+D)*E+F*G";
    string ans;
    ans = InToPre(s);
    cout << ans << endl;

}
