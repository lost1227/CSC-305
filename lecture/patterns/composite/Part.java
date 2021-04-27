package com.cstaley.patterns.composite;

import java.util.HashMap;
import java.util.Map;
import java.util.SortedSet;

public class Part implements Component {
   private String name;
   private double weight;
   
   public Part(String name, double weight) {
      this.name = name;
      this.weight = weight;
   }

   @Override
   public String getName() {return name;}

   @Override
   public double getWeight() {return weight;}
}

