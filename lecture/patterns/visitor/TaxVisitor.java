package com.cstaley.patterns.visitor;

public interface TaxVisitor {
   void addTax(BasicFood item);
   void addTax(LuxuryFood item);
   void addTax(General item);
   void addTax(Alcohol item);
}
