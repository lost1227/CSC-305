package com.cstaley.patterns.visitor;

public abstract class Item {
   private int price;
   
   public Item(int price) {this.price = price;}
   
   public int getPrice() {return price;}
   public void setPrice(int price) {this.price = price;}


   abstract public void accept(TaxVisitor vst);
}
