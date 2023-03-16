package com.p;

import java.util.HashSet;

import static com.p.Expressions.add;
import static com.p.Expressions.mult;
import static com.p.Expressions.expon;
import static com.p.Expressions.divide;
import static com.p.Expressions.log;

public class third_task {
    public static void main(String[] args) {
        // тестируем клона
        Num test = new Num(5001);
        Num clone = (Num) test.clone();
        System.out.println(clone.value);

        Variable x = new Variable("x");
        Variable y = new Variable("y");
        Variable x1 = new Variable("x1");
        Variable y1 = new Variable("y1");

        Num value1 = new Num(5);
        Num value2 = new Num(10);

        Sum sum_x_y = new Sum(x, y);
        Sum sum_x1_y1 = new Sum(x1, y1);


        System.out.println(sum_x_y);
        System.out.println(sum_x_y.differentiation(x));
        Sum sum_res = new Sum(sum_x1_y1, sum_x_y);
        System.out.println(sum_res.differentiation(x));

        Multiply mult_x_value1 = new Multiply(value1, x);
        Multiply mult_x_value2 = new Multiply(x, value2);
        Multiply mult_x_y = new Multiply(mult_x_value1, mult_x_value2);
        Multiply mult_x_3 = new Multiply(mult_x_y, y);

        System.out.println(mult_x_value1);
        System.out.println(mult_x_value2);
        System.out.println(mult_x_y);
        System.out.println("mult = " + mult_x_y.differentiation(x));
        System.out.println("new mult = " + mult_x_3.differentiation(x));

        Sum sum_x = new Sum(x, x);
        Multiply new_mult = new Multiply(sum_x, x);
        System.out.println("new sum_mult = " + new_mult.differentiation(x));

        Division div = new Division(sum_x, x);
        System.out.println(div.differentiation(x));

        Log log = new Log(x);
        System.out.println(log.differentiation(x));

        Exponentiation x_x = new Exponentiation(x,x);
        System.out.println(x_x.differentiation(x));

        // проверка на работу выбора ошибок
        Expressions ex1 = add(x,x);
        Expressions ex2 = expon(ex1, x);
        Expressions ex3 = mult(ex2, x);
        Expressions e4 = log(ex3);
        Expressions e5 = divide(e4, x);
        //e5.checkNumberOfVariables();

        System.out.println(e5.expressionValue(2));

        HashSet<String> hs = new HashSet();
        System.out.println(e5.hsArgs(hs));
        System.out.println(hs);
        //System.out.println(e5);
    }
}
