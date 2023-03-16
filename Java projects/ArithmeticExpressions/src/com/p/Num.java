package com.p;

import java.util.HashSet;

public class Num extends Expressions { // - это класс числа который наследуется от Expressions
    protected double value;

    public Num(double v){
        this.value = v;
    }

    @Override
    public Expressions differentiation(Variable variable) {
        return new Num(0);
    }

    @Override
    public String toString() {
        return ""+value;
    }

    @Override
    public Expressions clone() {
        return new Num(value);
    }

    @Override
    public double expressionValue(double arg) {
        return value;
    }

    @Override
    public Expressions expressionValue(double arg, String name) {
        return new Num(value);
    }

    @Override
    public HashSet hsArgs(HashSet<String> hs) {
        return hs;
    }



//    @Override
//    public void checkNumberOfVariables() {
//    }
}
