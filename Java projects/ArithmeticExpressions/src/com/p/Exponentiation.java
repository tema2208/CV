package com.p;

import java.util.HashSet;
import java.util.Objects;

import static java.lang.Math.pow;

public class Exponentiation extends Expressions{
    protected Expressions base;
    protected Expressions deg;

    public Exponentiation(Expressions val, Expressions deg){
        this.base = val;
        this.deg = deg;
    }

    @Override
    public HashSet hsArgs(HashSet<String> hs) {
        base.hsArgs(hs);
        deg.hsArgs(hs);
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
            return pow(base.expressionValue(arg), deg.expressionValue(arg));
        }
        else throw new IllegalArgumentException();
    }

    @Override
    public Expressions differentiation(Variable variable) {
        if (base.getClass() == Variable.class && deg.getClass() == Variable.class){ // например x^x
            return mult(expon(base, deg), mult(deg, log(variable)).differentiation(variable));
        }
        if (base.getClass() == Num.class && deg.getClass() == Variable.class){
            return mult(mult(log(base), expon(base, deg)), deg.differentiation(variable));
        }
        else return mult(deg, expon(base, new Num(((Num)deg).value - 1)));
    }

    @Override
    public String toString() {
        return ""+ base +"^"+deg;
    }

    @Override
    public Expressions clone() {
        return new Exponentiation(base, deg);
    }

    public static Expressions correctExponentional(Expressions base, Expressions deg){
        if (base.getClass() == Num.class && (((Num) base).value == 1 || ((Num) base).value == 0)){
            return new Num(((Num) base).value);
        }
        if (deg.getClass() == Num.class && ((Num)deg).value == 1){
            return base;
        }
        if (deg.getClass() == Num.class && ((Num)deg).value == 0){
            return new Num(1);
        }
        else return new Exponentiation(base, deg);
    }

//    @Override
//    public void checkNumberOfVariables() {
//        if (this.helperMethod() != 0){
//            throw new IllegalArgumentException();
//        }
//    }
//
//    public int helperMethod(){
//        int count = 0;
//        if (base.getClass() == Variable.class && deg.getClass() == Variable.class && !Objects.equals(((Variable) base).name, ((Variable) deg).name)){
//            count += 1;
//        }
//        base.checkNumberOfVariables();
//        deg.checkNumberOfVariables();
//        return count;
//    }

}

