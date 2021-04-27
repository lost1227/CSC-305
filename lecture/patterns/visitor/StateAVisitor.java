package com.cstaley.patterns.visitor;

public class StateAVisitor implements TaxVisitor {

   @Override
   public void addTax(BasicFood item) {}

   @Override
   public void addTax(LuxuryFood item) {
      item.setPrice((int)Math.ceil(item.getPrice() * 1.05));
   }

   @Override
   public void addTax(General item) {
      item.setPrice((int)Math.round(item.getPrice() * 1.07));
   }

   @Override
   public void addTax(Alcohol item) {
      item.setPrice((int)Math.round(item.getPrice() * 1.10));
   }
}
