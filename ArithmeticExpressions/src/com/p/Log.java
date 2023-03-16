package com.p;

import java.util.HashSet;
import java.util.Objects;

public class Log extends Expressions{
    protected Expressions expr;

    public Log(Expressions expr) {
        this.expr = expr;
    }

    @Override
    public HashSet hsArgs(HashSet<String> hs) {
        expr.hsArgs(hs);
        return hs;
    }

    @Override
    public double expressionValue(double arg) {
//        try {
//            this.checkNumberOfVariables();
//        } catch (IllegalArgumentException e){
//            System.out.println("  выражении более одной переменной");
//        }
        if(this.createHs().size() == 1) {
            return Math.log(expr.expressionValue(arg));
        }
        else throw new IllegalArgumentException();
    }

    @Override
    public Expressions differentiation(Variable variable) {
        return mult(divide(new Num(1), expr), expr.differentiation(variable));
    }

    @Override
    public String toString() {
        return "ln("+expr+")";
    }

    @Override
    public Expressions clone() {
        return new Log(expr);
    }


    public static Expressions correctLog(Expressions expr){
        if (expr.getClass() == Num.class){
            return new Num(Math.log(((Num)expr).value));
        }
        if (expr.getClass() == Exponentiation.class){
            return new Multiply(((Exponentiation)expr).deg, new Log(((Exponentiation)expr).base));
        }
        else return new Log(expr);
    }

//    @Override
//    public void checkNumberOfVariables() {
//        expr.checkNumberOfVariables();
//    }

}
