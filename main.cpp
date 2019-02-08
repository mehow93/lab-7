#include <iostream>

using namespace std;

void pointersDemo1()
{
    int x = 1;
    int *p1 = &x;
    int **pp1 = &p1;

    printf("&x = %p, x = %d\n", reinterpret_cast<void*>(&x), x);
    printf("&p1 = %p, p1 = %p\n",
           reinterpret_cast<void*>(&p1),
           reinterpret_cast<void*>(p1));
    printf("&pp1 = %p, pp1 = %p\n",
           reinterpret_cast<void*>(&pp1),
           reinterpret_cast<void*>(pp1));

    printf("*p1 = %d\n", *p1);
    printf("**pp1 = %d\n", **pp1);

    printf("About to execute *p1 = 2...\n");
    *p1 = 2;
    printf("x = %d\n", x);

    printf("About to execute **pp1 = 3...\n");
    **pp1 = 3;
    printf("x = %d\n", x);
}

void pointersDemo2()
{
    int a[] = {1, 2, 3, 4, 5};
    //int b[] = {1, 2, 3, 4, 5, 6};
    int *p1 = a;

    printf("&a = %p, a = %p, a[0] = %p\n",
           reinterpret_cast<void*>(&a),
           reinterpret_cast<void*>(a),
           reinterpret_cast<void*>(&a[0]));

    printf("a[0] = %d, *p1 = %d\n", a[0], *p1);

    //int (*p2)[] = &a;
    //int (*p2)[5] = &b;
    int (*p2)[5] = &a;
    printf("&p2 = %p, p2 = %p, *p2 = %p\n",
           reinterpret_cast<void*>(&p2),
           reinterpret_cast<void*>(p2),
           reinterpret_cast<void*>(*p2));
}

int f1(int i) { return i; }
int f2(int i) { return 10 * i; }
int f3(int i) { return 100 * i; }

double f4(char c)
{
    return (c == 'a') ? 3.14 : 2.71;
}

int* f5(double *x)
{
    int *res = new int;
    *res = (*x > 0) ? -1 : 1;
    return res;
}

int* f6(double *x)
{
    int *res = new int;
    *res = (*x > 0) ? 10 : 0;
    return res;
}

int* (*f7(double (*pf)(char), int *p1))(double *)
{
    double res1 = (*p1 > 0) ? pf('a') : pf('b');
    if (res1 > 0) return f5;
    else return f6;
}

void pointersDemo3()
{
    typedef int (*PInt_Fun_Int_T)(int);
    PInt_Fun_Int_T fs[] = { f1, f2, f3 };

    for (int i = 0; i < 3; ++i) {
        printf("fs[%d](%d) = %d\n", i, i, fs[i](i));
    }
    printf("\n");

//    You cannot increment a function pointer in C++
//    PInt_Fun_Int_T pf = fs[0];
//    for (int i = 0; i < 3; ++i) {
//        printf("pf(%d) = %d\n", i, pf(i));
//        pf++;
//    }

    // Let's do some low-level hacking :)
    printf("sizeof(PInt_Fun_Int_T) = %lu\n", sizeof(PInt_Fun_Int_T));
    void *pv = reinterpret_cast<void*>(fs[0]);
    for (int i = 0; i < 3; ++i) {
        printf("reinterpret_cast<PInt_Fun_Int_T>(pv)(%d) = %d\n",
               i, reinterpret_cast<PInt_Fun_Int_T>(pv)(i));
    }
}

void pointersDemo4()
{
    double x = 1;
    int* (*(*p7)(double(*)(char), int*)) (double*) = f7;
    printf("*f7(f4,f6(&x))(&x) = %d\n", *f7(f4,f6(&x))(&x));
    printf("*f7(f4,f6(&x))(&x) = %d\n", *p7(f4,f6(&x))(&x));
}
void swap2ints(int  & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;



}
void swap2ints_2(int * pX, int * pY){
    int temp = *pX;
    *pX = *pY;
    *pY = temp;
}

void swap2ints_3(int * const pX, int * const  pY){
    int temp = *pX;
    *pX = *pY;
    *pY = temp;
}

int main()
{
    //pointersDemo1();
    //pointersDemo2();
    pointersDemo3();
    /*pointersDemo4();*/
/*int x =1;
int y=2;
cout<<"x = "<< x <<" a y = "<<y<<endl;
cout<< "A teraz:"<<endl;
swap2ints(x,y);
cout<<"x = "<< x <<" a y = "<<y<<endl;
cout<< "Na wskazniki : "<<endl;
swap2ints_2(&x, &y);
cout<<"x = "<< x <<" a y = "<<y<<endl;
cout<< "Na wskazniki const : "<<endl;
swap2ints_3(&x, &y);
cout<<"x = "<< x <<" a y = "<<y<<endl;*/

    return 0;
}
