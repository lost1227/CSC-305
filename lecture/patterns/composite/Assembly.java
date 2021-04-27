package com.cstaley.patterns.composite;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.SortedSet;
import java.util.TreeMap;

public class Assembly implements Component {
   private String name;
   private List<Component> pieces;  // Upgrade to Map<Component, Integer>...
   
   public Assembly(String name, List<Component> pieces) {
      this.name = name;
      this.pieces = pieces;
   }

   @Override
   public String getName() {return name;}

   @Override
   public double getWeight() {
      double weight = 0.0;

      for (Component cmp: pieces)
         weight += cmp.getWeight();
      
      return weight;
   }
}