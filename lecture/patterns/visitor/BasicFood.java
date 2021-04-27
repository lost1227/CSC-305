package com.cstaley.patterns.visitor;

public class BasicFood extends Item {
   public BasicFood(int price) {super(price);}

   @Override
   public void accept(TaxVisitor vst) {vst.addTax(this);}
}
