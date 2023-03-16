package com.p;

import java.util.HashSet;

import static com.p.Sum.correctSum;
import static com.p.Multiply.correctMulti;
import static com.p.Exponentiation.correctExponentional;
import static com.p.Log.correctLog;
import static com.p.Division.correctDivision;

public abstract class Expressions{

    public abstract Expressions differentiation(Variable variable);

    public abstract Expressions clone();

    public static Expressions add(Expressions e1, Expressions e2){
        return correctSum(e1, e2);
    }

    public static Expressions mult(Expressions e1, Expressions e2){
        return correctMulti(e1,e2);
    }

    public static Expressions divide(Expressions e1, Expressions e2){
        return correctDivision(e1,e2);
    }

    public static Expressions expon(Expressions e1, Expressions e2){
        return correctExponentional(e1, e2);
    }

    public static Expressions log(Expressions x){
        return correctLog(x);
    }

    public abstract double expressionValue(double arg);

    public abstract Expressions expressionValue(double arg, String name);

    public abstract HashSet hsArgs(HashSet<String> hs);

    public HashSet createHs(){
        HashSet<String> hs = new HashSet<>();
        return hsArgs(hs);
    }
    //public abstract
//    public Expressions divide(Expressions e1, Expressions e2){
//        return new Division(e1,e2).correctDivision();
//    }

//    public Expressions log(Expressions x){
//        return new Log(x).correctLog();
//    }

    //public abstract void checkNumberOfVariables();
}
