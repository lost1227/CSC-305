package com.cstaley.patterns.bridge;

import java.io.PrintWriter;
import java.io.Writer;

public abstract class Letter {
    protected PrintWriter out;

   public Letter(Writer os) {
      out = new PrintWriter(os);
   }
   
   public void draw() {
      drawLetter();
      out.println();
   }
   
   public abstract void drawLetter(); // Template Method
}
