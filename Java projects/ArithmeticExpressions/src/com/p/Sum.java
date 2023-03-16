package com.p;

import java.util.HashSet;
import java.util.Objects;

public class Sum extends Expressions{
    protected Expressions expr1;
    protected Expressions expr2;

    public Sum(Expressions val1, Expressions val2){
        this.expr1 = val1;
        this.expr2 = val2;
    }

    @Override
    public Expressions differentiation(Variable variable) {
        return add(expr1.differentiation(variable), expr2.differentiation(variable));
    }

    @Override
    public String toString() {
        return "("+expr1+" + "+expr2+")";
    }

    @Override
    public Expressions clone() {
        return new Sum(expr1,expr2);
    }

    @Override
    public double expressionValue(double arg) {
//        try {
//            this.checkNumberOfVariables();
//        } catch (IllegalArgumentException e){
//            System.out.println("в выражении более одной переменной");
//        }
        if(this.createHs().size() == 1) {
            return expr1.expressionValue(arg) + expr2.expressionValue(arg);
        }
        else throw new IllegalArgumentException();
    }

    @Override
    public Expressions expressionValue(double arg, String name) {
        return add(expr1.expressionValue(arg, name), expr2.expressionValue(arg, name));
    }

    @Override
    public HashSet hsArgs(HashSet<String> hs) {
        expr1.hsArgs(hs);
        expr2.hsArgs(hs);
        return hs;
    }

//    @Override
//    public void checkNumberOfVariables(){
//        if (this.helperMethod() != 0){
//            throw new IllegalArgumentException();
//        }
//    }

//    public int helperMethod(){
//        int count = 0;
//        if (expr1.getClass() == Variable.class && expr2.getClass() == Variable.class && !Objects.equals(((Variable) expr1).name, ((Variable) expr2).name)){
//            count += 1;
//        }
//        expr1.checkNumberOfVariables();
//        expr2.checkNumberOfVariables();
//        return count;
//    }

    public static Expressions correctSum(Expressions expr1,Expressions expr2){
        if(expr1.getClass() == Num.class && ((Num)expr1).value == 0){
            return expr2;
        }
        if(expr2.getClass() == Num.class && ((Num)expr2).value == 0){
            return expr1;
        }
        if(expr1.getClass() == Num.class && expr2.getClass() == Num.class){
            return new Num(((Num)expr1).value + ((Num)expr2).value);
        }
        if(expr1.getClass() == Variable.class && expr2.getClass() == Variable.class && Objects.equals(((Variable) expr1).name, ((Variable) expr2).name)){
            System.out.println("aue");
            Num tmp = new Num(2);
            return new Multiply(expr1,tmp);
        }
        else return new Sum(expr1, expr2);
    }

}
