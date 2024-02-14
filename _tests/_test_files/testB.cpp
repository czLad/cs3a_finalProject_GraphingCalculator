#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/token/token.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"

#include "../../includes/queue/MyQueue.h"

#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/domain.h"

#include "../../includes/tokenizer.h"
#include "../../includes/filein.h"
#include "../../includes/graph_payload.h"

using namespace std;

void print_postfix(const Queue<Token*>& postfix)
{
  for(Queue<Token*>::Iterator it = postfix.begin(); it != postfix.end(); ++it)
  {
    switch ((*it)->get_integer_type())
    {
    case 1:
      cout << static_cast<Integer*>(*it)->get_val();
    break;
    default:
      cout << static_cast<Operator*>(*it)->get_operator();
      break;
    }
  }
}

void print_infix(const Queue<Token*>& infix)
{
  for(Queue<Token*>::Iterator it = infix.begin(); it != infix.end(); ++it)
  {
      switch ((*it)->get_integer_type())
      {
      case 1:
          cout <<"case: "<<1<<"\n";
          cout << static_cast<Integer*>(*it)->get_val()<<"\n";
      break;
      case 2:
          cout <<"case: "<<2<<"\n";
          if(static_cast<Operator*>(*it)->get_op_type() == 2)
            cout << "x"<<"\n";
          else
            cout << static_cast<Operator*>(*it)->get_operator()<<"\n";
      break;
      case 3:
          cout <<"case: "<<3<<"\n";
          cout << "(\n";
      break;
      case 4:
          cout <<"case: "<<4<<"\n";
          cout << ")\n";
      break;
      }
  }
}

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_rpn(bool debug = false)
{
  if (debug){
    cout << "testB:: test-rpn() entering test_rpn" << endl;
  }
  //Test multiply
  Queue<Token *> postfix;
  Queue<Token *> postfix1;
  Queue<Token *> postfix2;
  Queue<Token *> postfix3;
  for(int i = 0; i < 2; i++)
  {
    postfix.push(new Integer(3));
    postfix.push(new Integer(5));
    postfix.push(new Operator("*"));
    postfix.push(new Integer(3));
    postfix.push(new Integer(5));
    postfix.push(new Operator("*"));
    postfix.push(new Operator("*"));
  }
  postfix.push(new Operator("*"));
  postfix.push(new Integer(3));
  postfix.push(new Integer(5));
  postfix.push(new Operator("*"));
  postfix.push(new Operator("*"));
  RPN rpn(postfix);
  cout << "rpn(): " << rpn() << "\n";
  //Test add
  for(int i = 0; i < 2; i++)
  {
    postfix1.push(new Integer(3));
    postfix1.push(new Integer(5));
    postfix1.push(new Operator("+"));
    postfix1.push(new Integer(3));
    postfix1.push(new Integer(5));
    postfix1.push(new Operator("+"));
    postfix1.push(new Operator("+"));
  }
  postfix1.push(new Operator("+"));
  postfix1.push(new Integer(3));
  postfix1.push(new Integer(5));
  postfix1.push(new Operator("+"));
  postfix1.push(new Operator("+"));
  postfix1.push(new Integer("3")); 
  postfix1.push(new Operator("^"));
  RPN rpn1(postfix1);
  cout << "rpn1(): " << rpn1() << "\n";
  for(int i = 0; i < 2; i++)
  {
    postfix2.push(new Integer(3));
    postfix2.push(new Integer(5));
    postfix2.push(new Operator("+"));
  }
  postfix2.push(new Operator("*"));
  postfix2.push(new Integer(5));
  postfix2.push(new Operator("+"));
  postfix2.push(new Integer(3));
  postfix2.push(new Operator("*"));
  postfix2.push(new Integer("1")); 
  postfix2.push(new Operator("^"));
  RPN rpn2(postfix2);
  cout << "rpn2(): " << rpn2() << "\n";
  //Test Mixed
  postfix3.push(new Integer(5));
  postfix3.push(new Integer(3));
  postfix3.push(new Operator("-"));
  postfix3.push(new Integer(6));
  postfix3.push(new Integer(2));
  postfix3.push(new Operator("/"));
  postfix3.push(new Integer(3));
  postfix3.push(new Operator("*"));
  postfix3.push(new Operator("*"));
  postfix3.push(new Integer("5")); //postfix3.push(new Integer(5));
  postfix3.push(new Integer("6")); //postfix3.push(new Integer(6));
  postfix3.push(new Integer("9")); //postfix3.push(new Integer(9));
  postfix3.push(new Operator("-"));
  postfix3.push(new Operator("*"));
  postfix3.push(new Operator("/"));
  postfix3.push(new Integer("3")); 
  postfix3.push(new Operator("^"));
  RPN rpn3(postfix3);
  cout << "rpn3(): " << rpn3() << "\n";

  return true;
}

bool test_shunting_yard(bool debug = false)
{
  if (debug){
    cout << "testB:: test-shunting_yard() entering test_shunting_yard" << endl;
  }
  Queue<Token *> infix;
  infix.push(new Integer(3));
  infix.push(new Operator("*"));
  infix.push(new Integer(5));
  infix.push(new Operator("+"));
  infix.push(new Integer(4));
  ShuntingYard sy(infix);
  Queue<Token*> postfix = sy.postfix();
  cout<<"postfix: ";
  for(Queue<Token*>::Iterator it = postfix.begin(); it != postfix.end(); ++it)
  {
    switch ((*it)->get_integer_type())
    {
    case 1:
      cout << static_cast<Integer*>(*it)->get_val();
    break;
    default:
      cout << static_cast<Operator*>(*it)->get_operator();
      break;
    }
  }
  cout<<"\n";
  RPN rpn(postfix);
  cout << "3 * 5 + 4 :" << rpn() << endl;

  Queue<Token *> infix1;
  infix1.push(new Integer(3));
  infix1.push(new Operator("+"));
  infix1.push(new Integer(5));
  infix1.push(new Operator("*"));
  infix1.push(new Integer(4));
  ShuntingYard sy1(infix1);
  Queue<Token*> postfix1 = sy1.postfix();
  cout<<"postfix1: ";
  for(Queue<Token*>::Iterator it = postfix1.begin(); it != postfix1.end(); ++it)
  {
    switch ((*it)->get_integer_type())
    {
    case 1:
      cout << static_cast<Integer*>(*it)->get_val();
    break;
    default:
      cout << static_cast<Operator*>(*it)->get_operator();
      break;
    }
  }
  cout<<"\n";
  RPN rpn1(postfix1);
  cout << "3 + 5 * 4 :" << rpn1() << endl;

  ShuntingYard sy2;
  // sy2.postfix(infix1);
  Queue<Token*>postfix2 = sy2.postfix(infix1);
  cout<<"postfix2: ";
  for(Queue<Token*>::Iterator it = postfix2.begin(); it != postfix2.end(); ++it)
  {
    switch ((*it)->get_integer_type())
    {
    case 1:
      cout << static_cast<Integer*>(*it)->get_val();
    break;
    default:
      cout << static_cast<Operator*>(*it)->get_operator();
      break;
    }
  }
  cout<<"\n";
  RPN rpn2(sy2.postfix(infix1));
  cout << "3 + 5 * 4 :" << rpn2() << endl;

  ShuntingYard sy3;
  RPN rpn3(sy3.postfix(infix));
  cout << "3 * 5 + 4 :" << rpn3() << endl;

  Queue<Token *> infix4;
  infix4.push(new Integer(3));
  infix4.push(new Operator("+"));
  infix4.push(new Integer(5));
  infix4.push(new Operator("+"));
  infix4.push(new Integer(4));
  ShuntingYard sy4(infix4);
  Queue<Token*> postfix4 = sy4.postfix();
  cout<<"postfix4: ";
  for(Queue<Token*>::Iterator it = postfix4.begin(); it != postfix4.end(); ++it)
  {
    switch ((*it)->get_integer_type())
    {
    case 1:
      cout << static_cast<Integer*>(*it)->get_val();
    break;
    default:
      cout << static_cast<Operator*>(*it)->get_operator();
      break;
    }
  }
  cout<<"\n";
  RPN rpn4(postfix4);
  cout << "3 + 5 + 4 :" << rpn4() << endl;

  
  return true;
}

bool test_sy_case_operators(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sy_case_operators() entering test_sy_case_operators" << endl;
  }
  Queue<Token*> infix;
  infix.push(new Integer(2));
  infix.push(new Operator("+"));
  infix.push(new Integer(4));
  infix.push(new Operator("*"));
  infix.push(new Integer("5"));
  infix.push(new Operator("/"));
  infix.push(new Integer("2"));
  infix.push(new Operator("^"));
  infix.push(new Integer(2));
  infix.push(new Operator("+"));
  infix.push(new Integer("10"));

  ShuntingYard sy(infix);
  Queue<Token*> postfix = sy.postfix();
  cout<<"postfix: ";
  print_postfix(postfix);
  cout<<"\n";
  RPN rpn(postfix);
  cout << "2 + 4 * 5 / 2 ^ 2 + 10 :" << rpn() << endl;

  //Test 2
  Queue<Token *> infix1;
  infix1.push(new Integer(2));
  infix1.push(new Operator("/"));
  infix1.push(new Integer(4));
  infix1.push(new Operator("+"));
  infix1.push(new Integer("5"));
  infix1.push(new Operator("*"));
  infix1.push(new Integer("3"));

  ShuntingYard sy1(infix1);
  Queue<Token*> postfix1 = sy1.postfix();
  cout<<"postfix1: ";
  print_postfix(postfix1);
  cout<<"\n";
  RPN rpn1(postfix1);
  cout << "2 / 4 + 5 * 3 :" << rpn1() << endl;


  return true;
}

bool test_sy_case_paren(bool debug = false)
{
  if (debug){
    cout << "testB:: test-case_paren() entering test_case_paren()" << endl;
  }
  Queue<Token*> infix;
  infix.push(new Integer(3));
  infix.push(new Operator("*"));
  infix.push(new LeftParen());
  infix.push(new Integer(5));
  infix.push(new Operator("+"));
  infix.push(new Integer("8"));
  infix.push(new RightParen());
  infix.push(new Operator("/"));
  infix.push(new Integer(2));

  ShuntingYard sy(infix);
  Queue<Token*> postfix = sy.postfix();
  cout<<"postfix: ";
  print_postfix(postfix);
  cout<<"\n";
  RPN rpn(postfix);
  cout << "3 * (5 + 8) / 2 :" << rpn() << endl;

  Queue<Token*> infix1;
  infix1.push(new Integer(3));
  infix1.push(new Operator("*"));
  infix1.push(new LeftParen());
  infix1.push(new Integer(5));
  infix1.push(new Operator("*"));
  infix1.push(new Integer("7"));
  infix1.push(new Operator("+"));
  infix1.push(new Integer("2"));
  infix1.push(new RightParen());
  infix1.push(new Operator("*"));
  infix1.push(new LeftParen());
  infix1.push(new Integer(5));
  infix1.push(new Operator("*"));
  infix1.push(new Integer("2"));
  infix1.push(new Operator("/"));
  infix1.push(new Integer("1"));
  infix1.push(new RightParen());
  infix1.push(new Operator("/"));
  infix1.push(new Integer(2));

  ShuntingYard sy1(infix1);
  Queue<Token*> postfix1 = sy1.postfix();
  cout<<"postfix1: ";
  print_postfix(postfix1);
  cout<<"\n";
  RPN rpn1(postfix1);
  cout << "3 * (5 * 7 + 2) * (5 * 2 / 2) / 2 :" << rpn1() << endl;

}

bool test_sy_case_function(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sy_case_function entering test_sy_case_function" << endl;
  }
  
  Queue<Token *> infix;
  infix.push(new Integer(3));
  infix.push(new Operator("*"));
  infix.push(new LeftParen());
  infix.push(new Integer(5));
  infix.push(new Operator("+"));
  infix.push(new Integer(6));
  infix.push(new Operator("-"));
  infix.push(new Function("X"));
  infix.push(new RightParen());
  infix.push(new Operator("/"));
  infix.push(new Integer(9));
  ShuntingYard sy;
  sy.infix(infix);
  Queue<Token*> postfix = sy.postfix();
  cout<<"postfix: ";
  print_postfix(postfix);
  cout<<"\n";
  RPN rpn;
  rpn.set_input(postfix);
  cout << "3*(5+6-X)/9 (x=4): " << rpn(4) << endl;

  Queue<Token *> infix1;
  infix1.push(new LeftParen());
  infix1.push(new Function("X"));
  infix1.push(new Operator("+"));
  infix1.push(new Integer(5));
  infix1.push(new RightParen());
  infix1.push(new Operator("^"));
  infix1.push(new Integer(2));
  ShuntingYard sy1;
  sy1.infix(infix1);
  Queue<Token*> postfix1 = sy1.postfix();
  cout<<"postfix1: ";
  print_postfix(postfix1);
  cout<<"\n";
  RPN rpn1;
  rpn1.set_input(postfix1);
  cout << "(x+5)^2 (x=5): " << rpn1(5) << endl;

  Queue<Token *> infix2;
  infix2.push(new LeftParen());
  infix2.push(new Function("X"));
  infix2.push(new Operator("+"));
  infix2.push(new Integer(5));
  infix2.push(new RightParen());
  infix2.push(new Operator("*"));
  infix2.push(new LeftParen());
  infix2.push(new Function("X"));
  infix2.push(new Operator("-"));
  infix2.push(new Integer(5));
  infix2.push(new RightParen());
  ShuntingYard sy2;
  sy2.infix(infix2);
  Queue<Token*> postfix2 = sy2.postfix();
  cout<<"postfix2: ";
  print_postfix(postfix2);
  cout<<"\n";
  RPN rpn2;
  rpn2.set_input(postfix2);
  cout << "(x+5)*(x-5) (x=5): " << rpn2(5) << endl;

  Queue<Token *> infix3;
  infix3.push(new Function("sin"));
  infix3.push(new LeftParen());
  infix3.push(new Integer(M_PI));
  infix3.push(new Operator("-"));
  infix3.push(new Function("X"));
  infix3.push(new RightParen());
  ShuntingYard sy3;
  sy3.infix(infix3);
  Queue<Token*> postfix3 = sy3.postfix();
  cout<<"postfix3: ";
  print_postfix(postfix3);
  cout<<"\n";
  RPN rpn3;
  rpn3.set_input(postfix3);
  cout << "sin(pi - x) (x=pi/2): " << rpn3(M_PI/2) << endl; 
  
  Queue<Token*> infix4;
  infix4.push(new Function("X"));
  infix4.push(new Operator("*"));
  // infix4.push(new LeftParen());
  infix4.push(new Function("cos"));
  infix4.push(new LeftParen());
  infix4.push(new Integer(1));
  infix4.push(new Operator("/"));
  infix4.push(new Function("X"));
  infix4.push(new RightParen());
  // infix4.push(new RightParen());
  ShuntingYard sy4;
  sy4.infix(infix4);
  Queue<Token*> postfix4 = sy4.postfix();
  cout<<"postfix4: ";
  print_postfix(postfix4);
  cout<<"\n";
  RPN rpn4;
  rpn4.set_input(postfix4);
  cout <<"x*cos(1 / x) (x=5): " << rpn4(5) << endl;

  Queue<Token *> infix5;
  infix5.push(new LeftParen());
  infix5.push(new Function("cos"));
  infix5.push(new LeftParen());
  infix5.push(new Function("X"));
  infix5.push(new RightParen());
  infix5.push(new RightParen());
  infix5.push(new Operator("^"));
  infix5.push(new Integer(2));
  infix5.push(new Operator("+"));
  infix5.push(new LeftParen());
  infix5.push(new Function("sin"));
  infix5.push(new LeftParen());
  infix5.push(new Function("X"));
  infix5.push(new RightParen());
  infix5.push(new RightParen());
  infix5.push(new Operator("^"));
  infix5.push(new Integer(2));

  ShuntingYard sy5;
  sy5.infix(infix5);
  Queue<Token*> postfix5 = sy5.postfix();
  cout<<"postfix5: ";
  print_postfix(postfix5);
  cout<<"\n";
  RPN rpn5;
  rpn5.set_input(postfix5);
  cout <<"(cos(x))^2 + (sin(x))^2 (x=5): " << rpn5(5) << endl;
  
  return true;

}

bool test_sy_ins_op(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sy_ins_function entering test_sy_ins_function" << endl;
  }
  // cout << "Enter an infix expression\n";

  //v Have not tested
  // const int size = 100;
  // char infix_str[size];
  // char delim[] = " ";
  // cin.getline(infix_str, size);

  // string infix_str;
  // cin >> infix_str;
  // const int char_arr_size = strlen(infix_str);
  // char infix_arr[char_arr_size];
  // for(int i = 0; i < char_arr_size; i++)
  // {
  //   infix_arr[i] = infix_str[i];
  // }

  // char* token;
  // token = strtok(infix_str, delim);
  // token = strtok(infix_arr, delim);
  char ans;
  do
  {
    cout << "Enter an infix expression\n";
    const int size = 100;
    char infix_str[size];
    char delim[] = " ";
    cin.getline(infix_str, size);

    char* token;
    token = strtok(infix_str, delim);

    bool variable = false;
    Queue<Token*>infix_queue;
    while(token)
    {
      // cout << token << "\n";
      if(isdigit(token[0]))
      {
        infix_queue.push(new Integer(token));
      }
      else if(isalpha(token[0]))
      {
        if(strlen(token) == 1)
          variable = true;
        infix_queue.push(new Function(token));
      }
      else
      {
        // cout<<"strlen(token): "<<strlen(token)<<"\n";
        // cout<<"token: "<<token<<"\n";
        if(strlen(token) == 1 && token[0] == '(')
        {
          // cout << "LeftParen\n";
          infix_queue.push(new LeftParen());
        }
        else if (strlen(token) == 1 && token[0] == ')')
        {
          // cout << "RightParen\n";
          infix_queue.push(new RightParen());
        }
        else
          infix_queue.push(new Operator(token));
      }

      token = strtok(NULL, delim);  
    }
    ShuntingYard sy_test(infix_queue);
    Queue<Token*> postfix = sy_test.postfix();

    double x_value = 0;
    if(variable)
    {
      cout<<"Enter a value for x: ";
      cin>>x_value;
    }

    cout<<"postfix: ";
    print_postfix(postfix);
    cout<<"\n";

    RPN result(postfix);
    cout<<"Result: "<<result(x_value)<<"\n";

    cout<<"Enter y for again x to exit: ";
    cin>> ans;
    cin.ignore();
  }while(tolower(ans) == 'y');
  // ShuntingYard sy_test(infix_queue);
  // print_postfix(sy_test.postfix());
  return true;
}

bool test_domain(bool debug = false)
{
  Domain d1(-2, 2);
  cout << d1 << "\n";
  if (debug){
    cout << "testB:: test-domain entering test_domain" << endl;
  }
  return true;
}

bool test_tokenizer(bool debug = false)
{
  if (debug){
    cout << "testB:: test-tokenizer entering test_tokenizer_function" << endl;
  }
  string equation = "x ^ 2";
  char eq_str[] = " ";
  char delim[] = " ";
  cout << equation << "\n";
  cout << equation.c_str() << "\n";
  strcpy(eq_str, equation.c_str());
  cout <<"eq_str: "<<eq_str <<"\n";
  char* token = strtok(eq_str, delim);

  Queue<Token*>infix_queue;
  while(token)
  {
    cout <<"|"<< token <<"|"<< "\n";
    if(isdigit(token[0]))
    {
      cout << "isdigit(token[0])\n";
      cout <<"token: "<<token << "\n";
      string token_str = token;
      cout <<"token_str |"<< token_str << "|\n";
      cout <<"static_cast<int>(token[0]): " <<static_cast<int>(token[0])<<"\n";
      cout <<"stod(token_str) "<< stod(token_str)<< "\n";
      cout <<"stod(token) "<< stod(token)<< "\n";
      infix_queue.push(new Integer(string(token)));
      cout << "After Integer\n";
    }
    else if(isalpha(token[0]))
    {
      if(strlen(token) == 1)
      cout << "isalpha(token[0])\n";
      infix_queue.push(new Function(token));
    }
    else
    {
        cout<<"strlen(token): "<<strlen(token)<<"\n";
        cout<<"token: "<<token<<"\n";
        if(strlen(token) == 1 && token[0] == '(')
        {
          // cout << "LeftParen\n";
          infix_queue.push(new LeftParen());
        }
        else if (strlen(token) == 1 && token[0] == ')')
        {
          // cout << "RightParen\n";
          infix_queue.push(new RightParen());
        }
        else
            infix_queue.push(new Operator(token));
      }
            token = strtok(NULL, delim);  
  }
  cout <<"infix_queue: "<<infix_queue<<"\n";
  
  return true;
}

bool test_tokenizer_obj_call(bool debug = false)
{
  if (debug){
    cout << "testB:: test-tokenizer entering test_tokenizer_function" << endl;
  }
  Tokenizer t;
  //Test 0

  string equation = "-(-5)";
  Queue<Token*> infix_queue;
  infix_queue = t(equation);
  cout <<"equation: "<<equation<<"<-\n";
  cout <<"Tokenized infix_queue: \n";
  print_infix(infix_queue);
  cout<<"\n";  
  ShuntingYard sy(infix_queue);
  print_postfix(sy.postfix());
  cout<<"\n";

  RPN rpn(sy.postfix());
  cout <<"rpn(2): "<<rpn(2)<<"\n";
  //Test 1

  string equation1 = "-sin(-x)";
  Queue<Token*> infix_queue1;
  infix_queue1 = t(equation1);
  cout <<"equation1: "<<equation1<<"<-\n";
  cout <<"Tokenized infix_queue1: \n";
  print_infix(infix_queue1);
  cout<<"\n";  
  sy.set_input(infix_queue1);
  print_postfix(sy.postfix());
  cout<<"\n";
  rpn.set_input(sy.postfix());
  cout <<"rpn(2): -sin(-x) = "<<rpn(2)<<"\n";
  if(rpn(2) - (-sin(-2)) <= 0.00001);
  {
    cout<<"rpn(2): -sin(-x)"<<"VERIFIED\n";
  }
  //Test 2

  string equation2 = "-x^2";
  Queue<Token*> infix_queue2;
  infix_queue2 = t(equation2);
  cout <<"equation2: "<<equation2<<"<-\n";
  cout <<"Tokenized infix_queue1: \n";
  print_infix(infix_queue2);
  cout<<"\n";  
  sy.set_input(infix_queue2);
  print_postfix(sy.postfix());
  cout<<"\n";
  rpn.set_input(sy.postfix());
  cout <<"rpn(3): -x^2 = "<<rpn(3)<<"\n";
  //Test 3

  string equation3 = "-(-(-x^2))";
  Queue<Token*> infix_queue3;
  infix_queue3 = t(equation3);
  cout <<"equation3: "<<equation3<<"<-\n";
  cout <<"Tokenized infix_queue3: \n";
  print_infix(infix_queue3);
  cout<<"\n";  
  sy.set_input(infix_queue3);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): -(-(-x^2)) = "<<rpn(3)<<"\n";
  //Test 4

  string equation4 = "2*(-x)";
  Queue<Token*> infix_queue4;
  infix_queue4 = t(equation4);
  cout <<"equation4: "<<equation4<<"<-\n";
  cout <<"Tokenized infix_queue4: \n";
  print_infix(infix_queue4);
  cout<<"\n";  
  sy.set_input(infix_queue4);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): 2*(-x) = "<<rpn(3)<<"\n";
  //Test 5

  string equation5 = "2^(-x)";
  Queue<Token*> infix_queue5;
  infix_queue5 = t(equation5);
  cout <<"equation5: "<<equation5<<"<-\n";
  cout <<"Tokenized infix_queue5: \n";
  print_infix(infix_queue5);
  cout<<"\n";  
  sy.set_input(infix_queue5);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): 2^(-x) = "<<rpn(3)<<"\n";
  //Test 6

  string equation6 = "e^(-x)";
  Queue<Token*> infix_queue6;
  infix_queue6 = t(equation6);
  cout <<"equation6: "<<equation6<<"<-\n";
  cout <<"Tokenized infix_queue6: \n";
  print_infix(infix_queue6);
  cout<<"\n";  
  sy.set_input(infix_queue6);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): e^(-x) = "<<rpn(3)<<"\n";
  //Test 7

  string equation7 = "(e^x-e^(-x))/2";
  Queue<Token*> infix_queue7;
  infix_queue7 = t(equation7);
  cout <<"equation7: "<<equation7<<"<-\n";
  cout <<"Tokenized infix_queue7: \n";
  print_infix(infix_queue7);
  cout<<"\n";  
  sy.set_input(infix_queue7);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): (e^x-e^(-x))/2 = "<<rpn(3)<<"\n";
  //Test 8

  string equation8 = "x-2";
  Queue<Token*> infix_queue8;
  infix_queue8 = t(equation8);
  cout <<"equation8: "<<equation8<<"<-\n";
  cout <<"Tokenized infix_queue8: \n";
  print_infix(infix_queue8);
  cout<<"\n";  
  sy.set_input(infix_queue8);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): x-2 = "<<rpn(3)<<"\n";
  //Test 9

  string equation9 = "cos(x)-x^2";
  Queue<Token*> infix_queue9;
  infix_queue9 = t(equation9);
  cout <<"equation9: "<<equation9<<"<-\n";
  cout <<"Tokenized infix_queue9: \n";
  print_infix(infix_queue9);
  cout<<"\n";  
  sy.set_input(infix_queue9);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): x-2 = "<<rpn(3)<<"\n";
  //Test 10

  string equation10 = "x";
  Queue<Token*> infix_queue10;
  infix_queue10 = t(equation10);
  cout <<"equation10: "<<equation10<<"<-\n";
  cout <<"Tokenized infix_queue10: \n";
  print_infix(infix_queue10);
  cout<<"\n";  
  sy.set_input(infix_queue10);
  print_postfix(sy.postfix());
  cout<<"\n";

  rpn.set_input(sy.postfix());
  cout <<"rpn(3): x = " <<rpn(3)<<"\n";


  return true;
}

bool test_Filein_obj(bool debug = false)
{
  if (debug){
    cout << "testB:: test-test_Filein_obj entering test_test_Filein_obj" << endl;
  }
  Filein f_test_history("history.txt");
  f_test_history.open_file();
  for(int i = 0; i < 4; i++)
    cout << f_test_history.read_from_file();
  f_test_history.close_file();


  return true;
}

bool test_graph_payload_obj(bool debug = false)
{
  graph_payload g_pyld_1;
  cout<<"Before tokenizer: "<<g_pyld_1<<"\n";
  string eq_test_str = "eq:x^2";
  string eq_test_domain = "d:-3,3";
  for(int i = 0; i < g_pyld_1._size; i++)
  {
    if(i==0)
      g_pyld_1.tokenizer(eq_test_str);
    else
      g_pyld_1.tokenizer(eq_test_domain);
  }
  cout<<"After tokenizer: "<<g_pyld_1<<"\n";

  vector<graph_payload> g_pyld_vector;
  g_pyld_vector.push_back(g_pyld_1);
  cout << g_pyld_vector[0] << "\n";

  return true;
}



//   return true;
// }
TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_RPN, TestRpn) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_rpn(false));
}

TEST(TEST_SHUNTING_YARD, TestSY) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_shunting_yard(false));
}

TEST(TEST_SHUNTING_YARD, TestSYCaseOp) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_sy_case_operators(false));
}

TEST(TEST_SHUNTING_YARD, TestSYCaseParen) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_sy_case_paren(false));
}

TEST(TEST_SHUNTING_YARD, TestSYCaseFunc) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_sy_case_function(false));
}

TEST(TEST_SHUNTING_YARD, TestTokenizer) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_tokenizer(false));
}

TEST(TEST_GRAPHING_CALC, TestTokenizerCall) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_tokenizer_obj_call(false));
}

TEST(TEST_GRAPHING_CALC, TestFileInOutObj) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_Filein_obj(false));
}

TEST(TEST_GRAPHING_CALC, TestGraphPayloadObj) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_graph_payload_obj(false));
}

TEST(TEST_SHUNTING_YARD, TestDomain){

  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_domain(false));

}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

