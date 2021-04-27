package com.cstaley.patterns.visitor;

public class LuxuryFood extends Item {
   public LuxuryFood(int price) {super(price);}

   @Override
   public void accept(TaxVisitor vst) {vst.addTax(this);}
}
