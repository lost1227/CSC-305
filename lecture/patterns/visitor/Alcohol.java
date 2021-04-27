package com.cstaley.patterns.visitor;

public class Alcohol extends Item {
   public Alcohol(int price) {super(price);}

   @Override
   public void accept(TaxVisitor vst) {vst.addTax(this);}
}
