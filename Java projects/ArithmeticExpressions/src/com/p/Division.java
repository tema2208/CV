package com.p;

import java.util.HashSet;
import java.util.Objects;

//import static jdk.nashorn.internal.objects.NativeMath.exp;

public class Division extends Expressions{
    protected Expressions numerator;
    protected Expressions denomerator;

    public Division(Expressions numer, Expressions denom) {
        this.numerator = numer;
        this.denomerator = denom;
    }

    @Override
    public HashSet hsArgs(HashSet<String> hs) {
        numerator.hsArgs(hs);
        denomerator.hsArgs(hs);
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
            return numerator.expressionValue(arg) / denomerator.expressionValue(arg);
        }
        else throw new IllegalArgumentException();
    }

    @Override
    public Expressions differentiation(Variable variable) {
        return divide(add(mult(numerator.differentiation(variable), denomerator), mult(mult(numerator, denomerator.differentiation(variable)), new Num(-1))), expon(denomerator, new Num(2)));
    }

    @Override
    public String toString() {
        return numerator+"/"+denomerator;
    }

    @Override
    public Expressions clone() {
        return new Division(numerator,denomerator);
    }

    public static Expressions correctDivision(Expressions numerator, Expressions denomerator ){
        if(denomerator.getClass()==Num.class && ((Num)denomerator).value==0){
            throw new ArithmeticException();
        }
        if(denomerator.getClass()==Num.class && ((Num)denomerator).value==1){
            return numerator;
        }
        if(numerator.getClass()==Num.class && denomerator.getClass()==Num.class &&((Num)denomerator).value!=0){
            return new Num(((Num)numerator).value/((Num)denomerator).value);
        }
        if ((numerator.getClass()==Num.class && ((Num)numerator).value==0)){
            return new Num(0);
        }
        if(numerator.getClass()==Variable.class && denomerator.getClass()==Variable.class && Objects.equals(((Variable) numerator).name, ((Variable) denomerator).name))return new Num(1);
        else return new Division(numerator, denomerator);
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
//        if (numerator.getClass() == Variable.class && denomerator.getClass() == Variable.class && !Objects.equals(((Variable) numerator).name, ((Variable) denomerator).name)){
//            count += 1;
//        }
//        numerator.checkNumberOfVariables();
//        denomerator.checkNumberOfVariables();
//        return count;
//    }

}
