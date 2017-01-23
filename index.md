### Welcome to Polynomial Pages.

### Function:
The executable will consume two filenames from the command line and will print to stdout the sum of the two polynomials found in those files. 

the code have two choice, operation"sum" or "multiplication" 

These polynomials will be stored in the following format: 5 9 8 7 6 5 represents 9*x^4 + 8*x^3 + 7*x^2 + 6*x^1 + 5. 

More formally there will be a single line which begins with an integer that represents the length of the polynomial (the degree plus 1) follow



### Details
# introduction of code
1. First, save two numbers like 510012, 3102 in two files --f1.txt, f2,txt.
2. The source codeint num_first(int i) to get the first number of 510012, it means the highest power and use to create the expn array. void inttoarr(int i,int arr[]) and void change(int array[],int n) use to change the int number saved in the file to array.
3. The function “change” use to abandon the first number of 510012. These two functions will create the coef array.
4. After create these two arrays, use the function “createpoly” to create the linked list of two polynomial.
5. use the function “addpoly” to plus two polynomials, then create a new linked list. The create method is linked the list of polynomial 2 to follow the list of polynomial 1. Then, use the function "Poly::SortList()" to sort the new linked list. Because we need to conbine the term which has same coef, so we need to sort the new linked list.
6. void Poly::mulpoly(Poly &po1,Term *p2) used to do the multiple of two polynomials.
7. At last, use void change() to convert the array to int. Then display, the result is 510114(add) or 71021224(multiple).

### How to use it:

1. wirte two number in ‘f1.txt’ and ‘f2.txt’ to represent two polynomial(eg 510012 and 3102)

2.  write “g++ project.cpp” in the bash field;

3. "./a.out " after that , it will print the two number which has been write down, what you have to do is choose if you want to add or multi(1=add and 2=multi) and then Enter;

4. then you can get answer, if you to do it again, write’./a.out’ and do it again.
