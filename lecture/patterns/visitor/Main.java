package com.cstaley.patterns.visitor;

public class Main {
   public static void main(String[] args) {
      Item[] receiptA = new Item[] {
         new BasicFood(100), new LuxuryFood(600), new Alcohol(1000) 
      };
      Item[] receiptB = new Item[] {
         new BasicFood(200), new General(600), new LuxuryFood(1000)
      };
      
      TaxVisitor taxA = new StateAVisitor();
      TaxVisitor taxB = new StateBVisitor();
    
      System.out.print("Receipt A: ");
      for (Item itm: receiptA) { 
         itm.accept(taxA);
         System.out.printf("%d ", itm.getPrice());
      }
      
      System.out.print("\nReceipt B: ");
      for (Item itm: receiptB) {
         itm.accept(taxB);
         System.out.printf("%d ", itm.getPrice());
      }
      System.out.println();
   }
}
