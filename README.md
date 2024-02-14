![Alt text](<ezgif.com-video-to-gif-converted (1).gif>)
# Work Report
Graphing Calculator
Gif is in 3.2 times speed
## Name: <ins> Min Phone Myat Zaw </ins>

## Features:

- Not Implemented:
  - what features have been implemented

<br><br>

- Implemented:
  - User Guide
  - Saving a graph's equation, domain, panning and zoom factors using a text file
  - Having history recorded to redisplay, redisplay and reaccess after program is closed
  - Can scroll up, down, default on sidebar
  - Remembers the last place user left sidebar at and reload it at the position when program opened

<br><br>

- Partly implemented:
  - Utility buttons on sidebar. Mechanism there has not implemented

<br><br>

- Bugs
  - Non Known 

<br><br>

# Reflections:

- A good design can go a long way.

# **output**
<pre>
<br/><br/><br/><br/>

----------running basic_test.cpp---------


[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from BASIC_TEST
[ RUN      ] BASIC_TEST.BasicTest
[       OK ] BASIC_TEST.BasicTest (0 ms)
[----------] 1 test from BASIC_TEST (1 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (1 ms total)
[  PASSED  ] 1 test.
PS C:\Users\myatz\Downloads\CS3A Projects\99_00_final_project-czLad\build\bin>


----------running testB.cpp---------


[==========] Running 11 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 1 test from TEST_STUB
[ RUN      ] TEST_STUB.TestStub
[       OK ] TEST_STUB.TestStub (0 ms)
[----------] 1 test from TEST_STUB (0 ms total)

[----------] 1 test from TEST_RPN
[ RUN      ] TEST_RPN.TestRpn
rpn(): 759375
rpn1(): 64000
rpn2(): 207
rpn3(): -1.728
[       OK ] TEST_RPN.TestRpn (2 ms)
[----------] 1 test from TEST_RPN (2 ms total)

[----------] 6 tests from TEST_SHUNTING_YARD
[ RUN      ] TEST_SHUNTING_YARD.TestSY
postfix: 35*4+
3 * 5 + 4 :19
postfix1: 354*+
3 + 5 * 4 :23
postfix2: 354*+
3 + 5 * 4 :23
3 * 5 + 4 :19
postfix4: 35+4+
3 + 5 + 4 :12
[       OK ] TEST_SHUNTING_YARD.TestSY (2 ms)
[ RUN      ] TEST_SHUNTING_YARD.TestSYCaseOp
postfix: 245*22^/+10+
2 + 4 * 5 / 2 ^ 2 + 10 :17
postfix1: 24/53*+
2 / 4 + 5 * 3 :15.5
[       OK ] TEST_SHUNTING_YARD.TestSYCaseOp (2 ms)
[ RUN      ] TEST_SHUNTING_YARD.TestSYCaseParen
postfix: 358+*2/
3 * (5 + 8) / 2 :19.5
postfix1: 357*2+*52*1/*2/
3 * (5 * 7 + 2) * (5 * 2 / 2) / 2 :555
[       OK ] TEST_SHUNTING_YARD.TestSYCaseParen (1 ms)
[ RUN      ] TEST_SHUNTING_YARD.TestSYCaseFunc
postfix: 356+X-*9/
3*(5+6-X)/9 (x=4): 2.33333
postfix1: X5+2^
(x+5)^2 (x=5): 100
postfix2: X5+X5-*
(x+5)*(x-5) (x=5): 0
postfix3: 3.14159X-sin
sin(pi - x) (x=pi/2): 1
postfix4: X1X/cos*
x*cos(1 / x) (x=5): 4.90033
postfix5: Xcos2^Xsin2^+
(cos(x))^2 + (sin(x))^2 (x=5): 1
[       OK ] TEST_SHUNTING_YARD.TestSYCaseFunc (3 ms)
[ RUN      ] TEST_SHUNTING_YARD.TestTokenizer
x ^ 2
x ^ 2
eq_str: x ^ 2
|x|
isalpha(token[0])
|^|
strlen(token): 1
token: ^
|2|
isdigit(token[0])
token: 2
token_str |2|
static_cast<int>(token[0]): 50
stod(token_str) 2
stod(token) 2
After Integer
infix_queue: Queue:Head-> [0x2b635b0] -> [0x2b61f20] -> [0x2b628d8] -> |||

[       OK ] TEST_SHUNTING_YARD.TestTokenizer (3 ms)
[ RUN      ] TEST_SHUNTING_YARD.TestDomain
Domain: [ -2 | 2 ]
[       OK ] TEST_SHUNTING_YARD.TestDomain (1 ms)
[----------] 6 tests from TEST_SHUNTING_YARD (12 ms total)

[----------] 3 tests from TEST_GRAPHING_CALC
[ RUN      ] TEST_GRAPHING_CALC.TestTokenizerCall
equation: -(-5)<-
Tokenized infix_queue:
case: 2
&
case: 3
(
case: 2
&
case: 1
5
case: 4
)

5&&
rpn(2): 5
equation1: -sin(-x)<-
Tokenized infix_queue1:
case: 2
&
case: 2
sin
case: 3
(
case: 2
&
case: 2
x
case: 4
)

x&sin&
rpn(2): -sin(-x) = 0.909297
rpn(2): -sin(-x)VERIFIED
equation2: -x^2<-
Tokenized infix_queue1:
case: 2
&
case: 2
x
case: 2
^
case: 1
2

x2^&
rpn(3): -x^2 = -9
equation3: -(-(-x^2))<-
Tokenized infix_queue3:
case: 2
&
case: 3
(
case: 2
&
case: 3
(
case: 2
&
case: 2
x
case: 2
^
case: 1
2
case: 4
)
case: 4
)

x2^&&&
rpn(3): -(-(-x^2)) = -9
equation4: 2*(-x)<-
Tokenized infix_queue4:
case: 1
2
case: 2
*
case: 3
(
case: 2
&
case: 2
x
case: 4
)

2x&*
rpn(3): 2*(-x) = -6
equation5: 2^(-x)<-
Tokenized infix_queue5:
case: 1
2
case: 2
^
case: 3
(
case: 2
&
case: 2
x
case: 4
)

2x&^
rpn(3): 2^(-x) = 0.125
equation6: e^(-x)<-
Tokenized infix_queue6:
case: 1
2.71828
case: 2
^
case: 3
(
case: 2
&
case: 2
x
case: 4
)

2.71828x&^
rpn(3): e^(-x) = 0.0497871
equation7: (e^x-e^(-x))/2<-
Tokenized infix_queue7:
case: 3
(
case: 1
2.71828
case: 2
^
case: 2
x
case: 2
-
case: 1
2.71828
case: 2
^
case: 3
(
case: 2
&
case: 2
x
case: 4
)
case: 4
)
case: 2
/
case: 1
2

2.71828x^2.71828x&^-2/
rpn(3): (e^x-e^(-x))/2 = 10.0179
equation8: x-2<-
Tokenized infix_queue8:
case: 2
x
case: 2
-
case: 1
2

x2-
rpn(3): x-2 = 1
equation9: cos(x)-x^2<-
Tokenized infix_queue9:
case: 2
cos
case: 3
(
case: 2
x
case: 4
)
case: 2
-
case: 2
x
case: 2
^
case: 1
2

xcosx2^-
rpn(3): x-2 = -9.98999
equation10: x<-
Tokenized infix_queue10:
case: 2
x

x
rpn(3): x = 3
[       OK ] TEST_GRAPHING_CALC.TestTokenizerCall (26 ms)
[ RUN      ] TEST_GRAPHING_CALC.TestFileInOutObj
x^2-x+2-e^x-2^(-x)[       OK ] TEST_GRAPHING_CALC.TestFileInOutObj (0 ms)
[ RUN      ] TEST_GRAPHING_CALC.TestGraphPayloadObj
Before tokenizer: Eq:
Domain: [ 0 | 0 ]
After tokenizer: Eq: x^2
Domain: [ -3 | 3 ]
Eq: x^2
Domain: [ -3 | 3 ]
[       OK ] TEST_GRAPHING_CALC.TestGraphPayloadObj (1 ms)
[----------] 3 tests from TEST_GRAPHING_CALC (28 ms total)

[----------] Global test environment tear-down
[==========] 11 tests from 4 test suites ran. (43 ms total)
[  PASSED  ] 11 tests.
PS C:\Users\myatz\Downloads\CS3A Projects\99_00_final_project-czLad\build\bin>
</pre>


<br/><br/>

# basic_test.cpp output:
<pre>
<br/><br/><br/><br/>
</pre>
# testB.cpp output:
<pre>
<br/><br/><br/><br/>
</pre>


