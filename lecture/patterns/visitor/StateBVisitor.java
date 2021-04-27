package com.cstaley.patterns.visitor;

public class StateBVisitor implements TaxVisitor {
   static final int cLuxuryFoodLimit = 500;
   
   @Override
   public void addTax(BasicFood item) {}

   @Override
   public void addTax(LuxuryFood item) {
      int price = item.getPrice();
      
      item.setPrice((int)Math.round(price > cLuxuryFoodLimit ? 
       price*1.05 : price)); 
   }

   @Override
   public void addTax(General item) {
      item.setPrice((int)Math.round(item.getPrice() * 1.08));
   }

   @Override
   public void addTax(Alcohol item) {
      item.setPrice((int)Math.round(item.getPrice() * 1.09));
   }
}
