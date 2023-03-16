package com.p;

import java.util.HashSet;
import java.util.Objects;

public class Multiply extends Expressions {
    protected Expressions expr1;
    protected Expressions expr2;

    public Multiply(Expressions val1, Expressions val2){
        this.expr1 = val1;
        this.expr2 = val2;
    }

    @Override
    public HashSet hsArgs(HashSet<String> hs) {
        expr1.hsArgs(hs);
        expr2.hsArgs(hs);
        return hs;
    }

    @Override
    public double expressionValue(double arg) {
//        try {
//            this.checkNumberOfVariables();
//        } catch (IllegalArgumentException e){
//            System.out.println("в выражении более одной переменной");
//        }
        if(this.createHs().size() == 1) {
            return expr1.expressionValue(arg) * expr2.expressionValue(arg);
        }
        else throw new IllegalArgumentException();
    }

    @Override
    public Expressions differentiation(Variable variable) {
//        System.out.println("----------------------------------");
//        System.out.println("aue1 = "+ expr1);
//        System.out.println("aue2 = "+ expr2);
//        System.out.println("result of test1 = "+ expr1.test());
//        System.out.println("result of test2 = "+ expr2.test());
//        System.out.println("all result = "+ expr1.test().differentiation(variable));
//        System.out.println("result = " +new Multiply(expr1.test().differentiation(variable),expr2));
//        System.out.println("----------------------------------");
        return add(mult(expr1.differentiation(variable),expr2), mult(expr1, expr2.differentiation(variable)));
    }

    @Override
    public String toString() {
        return "("+expr1 + "*" +expr2+")";
    }

    @Override
    public Expressions clone() {
        return new Multiply(expr1,expr2);
    }

    @Override
    public Expressions expressionValue(double arg, String name) {
        return mult(expr1.expressionValue(arg, name), expr2.expressionValue(arg, name));
    }
//    @Override
//    public void checkNumberOfVariables() {
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

    public static Expressions correctMulti(Expressions expr1, Expressions expr2){
        if(expr1.getClass() == Num.class && expr2.getClass() == Num.class){
            return new Num(((Num)expr1).value * ((Num)expr2).value);
        }
        if(expr1.getClass() == Num.class && ((Num)expr1).value == 0){
            return new Num(0);
        }
        if(expr2.getClass() == Num.class && ((Num)expr2).value == 0){
            return new Num(0);
        }
        if(expr1.getClass() == Num.class && ((Num)expr1).value== 1){
            return expr2;
        }
        if(expr2.getClass() == Num.class && ((Num)expr2).value== 1){
            return expr1;
        }
        if(expr1.getClass() == Division.class && ((Division)expr1).denomerator == expr2){
            return new Num(1);
        }
        if(expr2.getClass() == Division.class && ((Division)expr2).denomerator == expr1){
            return new Num(1);
        }
        else{
            return new Multiply(expr1,expr2);
        }
    }
}

