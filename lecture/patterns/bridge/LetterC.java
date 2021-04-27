package com.cstaley.patterns.bridge;

import java.io.Writer;

public class LetterC extends Letter {

   public LetterC(Writer out) {
      super(out);
   }

   @Override
   public void drawLetter() {
      out.println("*****");
      out.println("*   *");
      out.println("*   *");
      out.println("*   *");
   }
}
