package com.cstaley.patterns.composite;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeMap;

public class ProcessOrders {
   // Read a set of named components, each either a Part or an Assembly.  Parts
   // have lines of format:
   //
   // <name> <weight>
   //
   // Assemblies have lines of format:
   //
   // <name> <pieceName> <pieceName>....  (with zero or more pieceNames)
   //
   // Piece names must have been defined in earlier lines, and may be either a
   // Part or an Assembly.  ReadComponents does no error checking, as it's just
   // a conceptual illustration; be sure the input is correct, or suffer 
   // uncaught exceptions.
   static Map<String, Component> getCatalog(InputStream iStr) {
      Scanner in = new Scanner(iStr);
      String name;
      List<Component> pieces;
      Map<String, Component> rtn = new HashMap<String, Component>();
      
      while (in.hasNext()) {
         name = in.next();
         if (in.hasNextDouble()) // Part specification
            rtn.put(name, new Part(name, in.nextDouble()));
         else {
            pieces = new LinkedList<Component>();
            for (String pieceName: in.nextLine().split(" ")) {
               if (rtn.containsKey(pieceName))
                  pieces.add(rtn.get(pieceName));
            }
            rtn.put(name, new Assembly(name, pieces));
         }
      }
      in.close();
      
      return rtn;
   }
   
   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      Map<String, Component> catalog;
      Set<String> keys;
      Component cmp;
      
      try {
         catalog = getCatalog(new FileInputStream("Catalog.txt"));
         keys = catalog.keySet();
         for (String cmpName: keys) {
            cmp = catalog.get(cmpName);
            System.out.printf("%s has weight %.3f\n", cmpName, cmp.getWeight());
         }
      }
      catch (Exception err) {
         System.out.println("Error: " + err.getMessage());
         err.printStackTrace();
      }
      in.close();
   }
}