package com.cstaley.patterns.visitor;

public class General extends Item {
   public General(int price) {super(price);}

   @Override
   public void accept(TaxVisitor vst) {vst.addTax(this);}
}
